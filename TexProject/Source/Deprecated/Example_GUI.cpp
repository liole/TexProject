#include <TexProject/TexProject.h>
using namespace TexProject;


Texture* tex;


#include <atomic>
#include <thread>
#include <list>


namespace TexProject
{
	namespace Tool
	{
		struct Basic:
			public Helper::Structure::ListClassArray<Basic,true,true>
		{
		protected:
			Interface::GUIPanel**				panel = nullptr;
			Interface::GUIButton**				button = nullptr;
			Texture**							texture = nullptr;

		public:
			virtual void						Create(Window::Render* window);
			virtual void						Delete();		
			virtual void						Loop();

			virtual void						Refresh();

			virtual Texture*					GetInput(uint32 slot = 0);
			virtual Basic*						GetOutput(uint32 slot = 0);
		};
		struct InputOutputData
		{
			Tool::Basic*						tool = nullptr;
			Texture*							tex = nullptr;

			inline								InputOutputData(Tool::Basic* tool_,Texture* tex_):
				tool(tool_),tex(tex_)
			{
			}
		};
		struct OutputData
		{
			Tool::Basic*						tool = nullptr;
			Texture*							texture = nullptr;

			inline								OutputData(Tool::Basic* tool_,Texture* texture_):
				tool(tool_),texture(texture_)
			{
			}
		};

		namespace Generator
		{
			namespace Noise
			{
				struct Default: public Tool::Basic
				{
				protected:
					std::atomic<bool>			textureRebuilderFlag					= false;
					std::thread					textureRebuilderThread;
					Texture*					textureRebuilderStorage					= nullptr;
					bool						textureIsReady							= true;
					Texture*					texture									= nullptr;
				public:
					virtual void				Create(Window::Render* window) override;
					virtual void				Loop() override;

					virtual void				Refresh() override;
				};
			}
		}
		namespace Filter
		{
			namespace Correction
			{
				struct ChannelMixer: public Tool::Basic
				{
				protected:
					std::atomic<bool>			textureRebuilderFlag					= false;
					std::thread					textureRebuilderThread;
					Texture*					textureRebuilderStorage					= nullptr;
					bool						textureIsReady							= true;
					Texture*					texture = nullptr;
				public:
					virtual void				Create(Window::Render* window) override;
					virtual void				Loop() override;

					virtual void				Refresh() override;

					virtual Texture*			GetInput(uint32 slot = 0) override;
				};
			}
		}

		template<typename T>
		inline T*								Add(Window::Render* window);
		inline void								Remove(Basic* source);
		void									Loop();
	}
}

// Tool
template<typename T>
inline typename T*							TexProject::Tool::Add(Window::Render* window)
{
	auto t = new T();
	t->Create(window);
	return t;
}
inline void									TexProject::Tool::Remove(Basic* source)
{
	source->Delete();
	delete source;
}
inline void									TexProject::Tool::Loop()
{
	for(auto i = Tool::Basic::Begin(); i != Tool::Basic::End(); ++i)
	{
		auto tool = (*i);
		tool->Loop();
	}
}


// Tool::Basic
void					Tool::Basic::Create(Window::Render* window)
{
}
void					Tool::Basic::Delete()
{
}
void					Tool::Basic::Loop()
{
}
void					Tool::Basic::Refresh()
{
}
Texture*				Tool::Basic::GetInput(uint32 slot)
{
	return nullptr;
}
Tool::Basic*			Tool::Basic::GetOutput(uint32 slot)
{
	return nullptr;
}


// Tool::Generator::Noise::Default
void					Tool::Generator::Noise::Default::Create(Window::Render* window)
{
	panel = new Interface::GUIPanel*[2];
	button = new Interface::GUIButton*[3];

	auto p1 = (Interface::GUIPanelDefault*)window->AddPanel(Interface::PanelTypes::Default); panel[0] = p1;
	p1->SetSize(vec2(200.0f));
	p1->SetPos(vec2(150.0f,200.0f));

	auto p2 = (Interface::GUIPanelImage*)p1->AddPanel(Interface::PanelTypes::Image); panel[1] = p2;
	p2->SetSize(vec2(128.0f));

	auto bClose = p1->AddButton(Interface::ButtonTypes::Close); button[0] = bClose;

	auto conOut1 = (Interface::GUIButtonConnector*)p1->AddButton(Interface::ButtonTypes::OutputConnector); button[1] = conOut1;
	conOut1->SetSize(vec2(8.0f));
	conOut1->SetPos(vec2(((p1->GetSize().x - conOut1->GetSize().x)*0.5f - 4.0f),0.0f));
	conOut1->connectDirection = vec2(100.0f,0.0f);
	conOut1->SetUserData(new OutputData(this,nullptr));

	auto bRefresh = (Interface::GUIButtonDefault*)p1->AddButton(Interface::ButtonTypes::Default); button[2] = bRefresh;
	bRefresh->SetSize(vec2(60.0f,24.0f));
	bRefresh->SetPos(vec2(0.0f,p1->GetSize().y*0.5f-16.0f));
	bRefresh->SetUserData(this);
	bRefresh->SetAction
	(
		Interface::Item::ActionTypes::Click,
		[](Interface::Item* item)
		{
			auto tool = (Tool::Generator::Noise::Default*)item->GetUserData();
			if(tool) tool->Refresh();
		}
	);
}
void					Tool::Generator::Noise::Default::Loop()
{
	if(!textureIsReady)
	{
		if(textureRebuilderFlag)
		{
			//Message("Generation complete!");

			//textureRebuilderThread.detach();
			textureRebuilderThread.join();

			texture = textureRebuilderStorage;
			textureRebuilderStorage = nullptr;

			if(texture) texture->Build(panel[0]->GetWindow());

			((Interface::GUIPanelImage*)panel[1])->SetImage(texture);

			auto conOut1 = ((Interface::GUIButtonConnector*)button[1]);
			((OutputData*)conOut1->GetUserData())->texture = texture;
			textureIsReady = true;

			conOut1->RefreshObservers();
		}
	}
}
void					Tool::Generator::Noise::Default::Refresh()
{
	if(textureIsReady)
	{
		auto conOut1 = ((Interface::GUIButtonConnector*)button[1]);

		if(texture) { delete texture; texture = nullptr; }			// delete prev texture
		((Interface::GUIPanelImage*)panel[1])->SetImage(nullptr);	// null image on panel
		((OutputData*)conOut1->GetUserData())->texture = nullptr;	// null data in output connector
		conOut1->RefreshObservers();								// refresh users

		textureIsReady = false;
		textureRebuilderFlag = false;
		textureRebuilderStorage = nullptr;
		uint32 seed = rand();
		textureRebuilderThread = std::thread
		(
			[&seed](Texture** tex, std::atomic<bool>* flag)
			{
				srand(seed);
				*tex = TexProject::Generator::Noise::SimpleMono(uvec3(128,128,1));
				*flag = true;
			},
			&textureRebuilderStorage,
			&textureRebuilderFlag
		);
	}
}


// Tool::Filter::Correction::ChannelMixer
void					Tool::Filter::Correction::ChannelMixer::Create(Window::Render* window)
{
	panel = new Interface::GUIPanel*[2];
	button = new Interface::GUIButton*[4];

	auto pMain = (Interface::GUIPanelDefault*)window->AddPanel(Interface::PanelTypes::Default); panel[0] = pMain;
	pMain->SetSize(vec2(200.0f));
	pMain->SetPos(vec2(150.0f,200.0f));

	auto pImage = (Interface::GUIPanelImage*)pMain->AddPanel(Interface::PanelTypes::Image); panel[1] = pImage;
	pImage->SetSize(vec2(128.0f));

	auto bClose = pMain->AddButton(Interface::ButtonTypes::Close); button[0] = bClose;

	auto conIn1 = (Interface::GUIButtonConnector*)pMain->AddButton(Interface::ButtonTypes::InputConnector); button[1] = conIn1;
	conIn1->SetSize(vec2(8.0f));
	conIn1->SetPos(vec2(-((pMain->GetSize().x - conIn1->GetSize().x)*0.5f - 4.0f),0.0f));
	conIn1->connectDirection = vec2(-100.0f,0.0f);
	conIn1->SetUserData(this);
	conIn1->SetAction
	(
		Interface::Item::ActionTypes::Refresh,
		[](Interface::Item* item) -> void
		{
			auto tool = ((Tool::Basic*)item->GetUserData());
			if(tool) tool->Refresh();
		}
	);

	auto conOut1 = (Interface::GUIButtonConnector*)pMain->AddButton(Interface::ButtonTypes::OutputConnector); button[2] = conOut1;
	conOut1->SetSize(vec2(8.0f));
	conOut1->SetPos(vec2(((pMain->GetSize().x - conIn1->GetSize().x)*0.5f - 4.0f),0.0f));
	conOut1->connectDirection = vec2(100.0f,0.0f);
	conOut1->SetUserData(new OutputData(this,nullptr));

	auto bRefresh = (Interface::GUIButtonDefault*)pMain->AddButton(Interface::ButtonTypes::Default); button[3] = bRefresh;
	bRefresh->SetSize(vec2(60.0f,24.0f));
	bRefresh->SetPos(vec2(0.0f,pMain->GetSize().y*0.5f-16.0f));
	bRefresh->SetUserData(this);
	bRefresh->SetAction
	(
		Interface::Item::ActionTypes::Click,
		[](Interface::Item* item) -> void
		{
			auto tool = (Tool::Filter::Correction::ChannelMixer*)item->GetUserData();
			if(tool) tool->Refresh();
		}
	);
}
void					Tool::Filter::Correction::ChannelMixer::Loop()
{
	if(!textureIsReady)
	{
		if(textureRebuilderFlag)
		{
			textureRebuilderThread.join();

			texture = textureRebuilderStorage;
			textureRebuilderStorage = nullptr;

			if(texture) texture->Build(panel[0]->GetWindow());

			((Interface::GUIPanelImage*)panel[1])->SetImage(texture);

			auto conOut1 = ((Interface::GUIButtonConnector*)button[2]);
			((OutputData*)conOut1->GetUserData())->texture = texture;
			conOut1->RefreshObservers();

			textureIsReady = true;
		}
	}
}
void					Tool::Filter::Correction::ChannelMixer::Refresh()
{
	if(textureIsReady)
	{
		auto t = GetInput();

		if(t)
		{
			auto conOut1 = ((Interface::GUIButtonConnector*)button[2]);

			if(texture) { delete texture; texture = nullptr; }			// delete prev texture
			((Interface::GUIPanelImage*)panel[1])->SetImage(nullptr);	// null image on panel
			((OutputData*)conOut1->GetUserData())->texture = nullptr;	// null data in output connector
			conOut1->RefreshObservers();								// refresh users

			textureIsReady = false;
			textureRebuilderFlag = false;

			//textureRebuilderStorage = new Texture(*t);
			textureRebuilderStorage = t->Copy();

			textureRebuilderThread = std::thread
			(
				[](Texture** tex,std::atomic<bool>* flag)
				{
					auto source = *tex;
					*tex = TexProject::Filter::Noise::Perlin(source,6);
					delete source;
					*flag = true;
				},
				&textureRebuilderStorage,
				&textureRebuilderFlag
			);
		}
	}
	/*Message("Refresh Filter::Correction::ChannelMixer");

	if(texture) { delete texture; texture = nullptr; }

	auto t = GetInput();

	if(t)
	{
		texture = new Texture;
		texture = TexProject::Filter::Noise::Perlin(t,6);
	}

	if(texture)
	{
		texture->Build(panel[0]->GetWindow());
		((Interface::GUIPanelImage*)panel[1])->SetImage(texture);
	}

	auto conOut1 = (Interface::GUIButtonConnector*)button[2];
	((OutputData*)conOut1->GetUserData())->texture = texture;
	conOut1->RefreshObservers();*/
}
Texture*				Tool::Filter::Correction::ChannelMixer::GetInput(uint32 slot)
{
	if(button)
	{
		auto t = ((Interface::GUIButtonConnector*)button[1])->GetTarget();
		if(t) return ((OutputData*)t->GetUserData())->texture;
	}
	return nullptr;
}


Tool::Basic* t[3] = { nullptr, nullptr, nullptr };

void windowInit(Window::Render* window)
{

	auto p1 = window->AddPanel(Interface::PanelTypes::Default);
	p1->SetPos(vec2(32.0f,16.0f));
	p1->SetSize(vec2(32.0f*2,32.0f));
	p1->LockMove();

	auto b1 = p1->AddButton(Interface::ButtonTypes::Default);
	b1->SetPos(vec2(-16.0f,0.0f));
	b1->SetSize(vec2(28.0f));
	b1->SetAction
	(
		Interface::Item::ActionTypes::Click,
		[](Interface::Item* item) -> void
		{
			Tool::Add<Tool::Generator::Noise::Default>(item->GetWindow());
		}
	);

	auto b2 = p1->AddButton(Interface::ButtonTypes::Default);
	b2->SetPos(vec2(16.0f,0.0f));
	b2->SetSize(vec2(28.0f));
	b2->SetAction
	(
		Interface::Item::ActionTypes::Click,
		[](Interface::Item* item) -> void
		{
			Tool::Add<Tool::Filter::Correction::ChannelMixer>(item->GetWindow());
		}
	);
	//auto t1 = Tool::Add<Tool::Generator::Noise::Default>(window);
	//auto t2 = Tool::Add<Tool::Filter::Correction::ChannelMixer>(window);
}


Geometry::Mesh tMesh;
OpenGL::Shader tShader;
OpenGL::Model tModel;
GLint uniformRMatrix,uniformMMatrix,uniformMVPMatrix;
Texture texDif,texNor,texMat;
Helper::VMat cam;
Helper::MMat obj(vec3(0.0f), vec3(0.0f), vec3(1.0f));

void tInit(Window::Render* window)
{
	{
		cam.SetPos(vec3(0.0f,0.0f,-10.0f));
		cam.SetAng(vec3(0.0f));
		cam.SetPerspective(80.0f,float32(window->GetSize().x) / float32(window->GetSize().y),0.1f,1000.0f);
	}

	texDif.Load("Media/Images/Brick1_D.png"); texDif.Build(window);
	texNor.Load("Media/Images/Brick1_N.png"); texNor.Build(window);
	texMat.Load("Media/Images/Brick1_M.png"); texMat.Build(window);

	tShader.Load
	(
		"Media/Shaders/3D/Material/Basic/V1/1.vs",
		"",
		"",
		"",
		"Media/Shaders/3D/Material/Basic/V1/1.ps"
	);
	tShader.Use();
	tShader.SetInt("TextureDiffuse",0);
	tShader.SetInt("TextureNormal",1);
	tShader.SetInt("TextureMaterial",2);
	uniformRMatrix = tShader.PrepareUniform("RotateMatrix");
	uniformMMatrix = tShader.PrepareUniform("ModelMatrix");
	uniformMVPMatrix = tShader.PrepareUniform("ModelViewProjectionMatrix");

	tMesh.CreateBox(vec3(5.0f),vec3(2.0f),uvec3(10));

	tModel.Create(&tMesh,&tShader);

	OpenGL::ErrorTest();
}
void tFree(Window::Render* window)
{
	tMesh.Delete();
}
void tLoop(Window::Render* window)
{
	glClearColor(0,0,0,0);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{
		float32 aSpeed = 1.0f;
		vec3 rotate(0.0f);
		if(KeyState(Keys::RIGHT)) rotate.y += aSpeed;
		if(KeyState(Keys::LEFT)) rotate.y -= aSpeed;
		if(KeyState(Keys::UP)) rotate.x += aSpeed;
		if(KeyState(Keys::DOWN)) rotate.x -= aSpeed;
		if(KeyState(Keys::Q)) rotate.z -= aSpeed;
		if(KeyState(Keys::E)) rotate.z += aSpeed;
		cam.Rotate(rotate);
	}

	{
		float32 mSpeed = 0.05f;
		vec3 move(0.0f);
		if(KeyState(Keys::W)) move.z += mSpeed;
		if(KeyState(Keys::S)) move.z -= mSpeed;
		if(KeyState(Keys::A)) move.x -= mSpeed;
		if(KeyState(Keys::D)) move.x += mSpeed;
		if(KeyState(Keys::SPACE)) move.y += mSpeed;
		if(KeyState(Keys::L_CTRL)) move.y -= mSpeed;
		cam.Move(move);
	}


	obj.Rotate(vec3(0.0f,0.5f,0.0f));

	tShader.Use();

	tShader.SetVec3("lightPos",vec3(2.0f,2.0f,-8.0f) - cam.GetPos());

	texDif.glUse(0);
	texNor.glUse(1);
	texMat.glUse(2);

	tShader.SetMat3(uniformRMatrix,obj.GetRMat());
	tShader.SetMat4(uniformMMatrix,obj.GetMMat() * mat4::move(-cam.GetPos()));
	tShader.SetMat4(uniformMVPMatrix,obj.GetMMat() * cam.GetVPMat());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	tModel.Draw();

	OpenGL::Shader::UseNull();
}


void TexProject::Main()
{
	/*Window::Render tWindow;

	tWindow.SetFunc(Window::Render::FuncTypes::Init,windowInit);
	tWindow.Create();
	tWindow.SetSize(uvec2(800,600));
	tWindow.SetRenderContext(Window::RenderContext::Types::Default);*/

	Window::Render wnd;
	wnd.SetFunc(Window::Render::FuncTypes::Init,tInit);
	wnd.SetFunc(Window::Render::FuncTypes::Free,tFree);
	wnd.SetFunc(Window::Render::FuncTypes::Loop,tLoop);
	wnd.Create();
	wnd.SetSize(uvec2(512,512));
	wnd.SetRenderContext(Window::RenderContext::Types::OpenGL);

	while(Window::Process())
	{
		//Tool::Loop();
		if(KeyState(Keys::ESC)) break;
	}

	//tWindow.Delete();
	wnd.Delete();
}













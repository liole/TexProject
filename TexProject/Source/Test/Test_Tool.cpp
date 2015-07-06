#include <TexProject/TexProject.h>
using namespace TexProject;




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
			struct OutputData
			{
				Tool::Basic*				tool = nullptr;
				Texture::Type				textureType = Texture::Type::D2;
				void*						texture = nullptr;

				inline OutputData(Tool::Basic* tool_,Texture::Type texType_,void* tex_):
					tool(tool_),
					textureType(texType_),
					texture(tex_)
				{
				}
			};

			Window::Render*const				window;

		public:
												Basic(Window::Render* window_);
			virtual								~Basic();

			virtual void						Loop();
			virtual void						Refresh();
		};
		struct D2:
			public Basic
		{
		protected:
		public:
			D2(Window::Render* window_):
				Basic(window_)
			{
			}
		};

		namespace Generator
		{
			namespace D2
			{
				struct Blank:
					public Tool::D2
				{
				protected:
					Interface::Panel::Default*					panelBase = nullptr;
					Interface::Panel::Image*					panelImage = nullptr;
					Interface::Button::Default*					buttonRefresh = nullptr;
					Interface::Button::Connector*				buttonConnectorOut = nullptr;
					Interface::Button::Default*					buttonClose = nullptr;

					Texture::D2*								texture = nullptr;

				public:

					Blank(Window::Render* window_);
					~Blank();

					virtual void								Refresh() override;
				};
			}
		}
		namespace Filter
		{
			namespace D2
			{
				namespace Correction
				{
					struct Color:
						public Tool::D2
					{
					protected:
						Interface::Panel::Default*					panelBase = nullptr;
						Interface::Panel::Image*					panelImage = nullptr;
						Interface::Button::Default*					buttonRefresh = nullptr;
						Interface::Button::Connector*				buttonConnectorIn = nullptr;
						Interface::Button::Connector*				buttonConnectorOut = nullptr;
						Interface::Button::Default*					buttonClose = nullptr;

						Texture::D2*								texture = nullptr;

						Texture::D2*								GetInput();

					public:

						Color(Window::Render* window_);
						~Color();

						virtual void								Refresh() override;
					};
				}
			}
		}
	}
}


// Tool::Basic
TexProject::Tool::Basic::Basic(Window::Render* window_):
	window(window_)
{
}
TexProject::Tool::Basic::~Basic()
{
}
void					TexProject::Tool::Basic::Loop()
{
}
void					TexProject::Tool::Basic::Refresh()
{
}


// Tool::Generator::D2::Blank
TexProject::Tool::Generator::D2::Blank::Blank(Window::Render* window_):
	Tool::D2(window_)
{
	panelBase = (Interface::Panel::Default*)window->AddPanel(Interface::PanelTypes::Default);
	panelBase->SetSize(vec2(200.0f));

	panelImage = (Interface::Panel::Image*)panelBase->AddPanel(Interface::PanelTypes::Image);
	panelImage->SetSize(vec2(128.0f));

	buttonRefresh = (Interface::Button::Default*)panelBase->AddButton(Interface::ButtonType::Default);
	buttonRefresh->SetSize(vec2(64.0f,18.0f));
	buttonRefresh->SetPos(vec2(0.0f,84.0f));
	buttonRefresh->SetUserData(this);
	buttonRefresh->SetAction
	(
		Interface::Item::ActionTypes::Click,
		[](Interface::Item* item)
		{
			((Tool::Generator::D2::Blank*)item->GetUserData())->Refresh();
		}
	);

	buttonConnectorOut = (Interface::Button::Connector*)panelBase->AddButton(Interface::ButtonType::OutputConnector);
	buttonConnectorOut->SetSize(vec2(8.0f));
	buttonConnectorOut->SetPos(vec2(94.0f,0.0f));
	buttonConnectorOut->connectDirection = vec2(64.0f,0.0f);
	buttonConnectorOut->SetUserData(new OutputData(this,Texture::Type::D2,nullptr),true);

	buttonClose = (Interface::Button::Default*)panelBase->AddButton(Interface::ButtonTypes::Close);
	buttonClose->SetPos(vec2(84.0f,-84.0f));
	buttonClose->SetSize(vec2(16.0f));
}
TexProject::Tool::Generator::D2::Blank::~Blank()
{
}
void					TexProject::Tool::Generator::D2::Blank::Refresh()
{
	panelImage->SetImage(nullptr);
	auto data_ = (OutputData*)buttonConnectorOut->GetUserData();
	data_->texture = nullptr;

	if(texture) { delete texture; texture = nullptr; }

	texture = new Texture::D2;
	texture->Create(uvec2(256));
	texture->Fill(vec4(1.0f,0.5f,0.0f,1.0f));

	data_->texture = texture;

	panelImage->SetImage(texture);

	//buttonConnectorOut->Refresh();
	buttonConnectorOut->RefreshObservers();
}


// Tool::Filter::D2::Correction::Color
TexProject::Tool::Filter::D2::Correction::Color::Color(Window::Render* window_):
	Tool::D2(window_)
{
	panelBase = (Interface::Panel::Default*)window->AddPanel(Interface::PanelTypes::Default);
	panelBase->SetSize(vec2(200.0f));

	panelImage = (Interface::Panel::Image*)panelBase->AddPanel(Interface::PanelTypes::Image);
	panelImage->SetSize(vec2(128.0f));

	buttonRefresh = (Interface::Button::Default*)panelBase->AddButton(Interface::ButtonType::Default);
	buttonRefresh->SetSize(vec2(64.0f,18.0f));
	buttonRefresh->SetPos(vec2(0.0f,84.0f));
	buttonRefresh->SetUserData(this);
	buttonRefresh->SetAction
	(
		Interface::Item::ActionTypes::Click,
		[](Interface::Item* item)
		{
			((Tool::Filter::D2::Correction::Color*)item->GetUserData())->Refresh();
		}
	);

	buttonConnectorIn = (Interface::Button::Connector*)panelBase->AddButton(Interface::ButtonType::InputConnector);
	buttonConnectorIn->SetSize(vec2(8.0f));
	buttonConnectorIn->SetPos(vec2(-94.0f,0.0f));
	buttonConnectorIn->connectDirection = vec2(-64.0f,0.0f);
	buttonConnectorIn->SetUserData(this);
	buttonConnectorIn->SetAction
	(
		Interface::Item::ActionTypes::Refresh,
		[](Interface::Item* item)
		{
			((Tool::Filter::D2::Correction::Color*)item->GetUserData())->Refresh();
		}
	);

	buttonConnectorOut = (Interface::Button::Connector*)panelBase->AddButton(Interface::ButtonType::OutputConnector);
	buttonConnectorOut->SetSize(vec2(8.0f));
	buttonConnectorOut->SetPos(vec2(94.0f,0.0f));
	buttonConnectorOut->connectDirection = vec2(64.0f,0.0f);
	buttonConnectorOut->SetUserData(new OutputData(this,Texture::Type::D2,nullptr),true);

	buttonClose = (Interface::Button::Default*)panelBase->AddButton(Interface::ButtonTypes::Close);
	buttonClose->SetPos(vec2(84.0f,-84.0f));
	buttonClose->SetSize(vec2(16.0f));
}
TexProject::Tool::Filter::D2::Correction::Color::~Color()
{
}
TexProject::Texture::D2*					TexProject::Tool::Filter::D2::Correction::Color::GetInput()
{
	if(buttonConnectorIn)
	{
		auto t = ((Interface::Button::Connector*)buttonConnectorIn)->GetTarget();
		if(t)
		{
			auto data_ = (OutputData*)t->GetUserData();
			if(data_->textureType == Texture::Type::D2)
			{
				return (Texture::D2*)data_->texture;
			}
		}
	}
	return nullptr;
}
void										TexProject::Tool::Filter::D2::Correction::Color::Refresh()
{
	panelImage->SetImage(nullptr);
	auto data_ = (OutputData*)buttonConnectorOut->GetUserData();
	data_->texture = nullptr;

	if(texture) { delete texture; texture = nullptr; }

	{
		auto source = GetInput();
		if(source)
		{
			auto sample = new Texture::D2(*source);

			texture = new Texture::D2;
			texture->Create(sample->GetSize());

			for(uint32 x = 0; x < texture->GetSize().x; ++x)
			for(uint32 y = 0; y < texture->GetSize().y; ++y)
			{
				auto sourcePixel = sample->GetPixel(uvec2(x,y));
				texture->SetPixel(uvec2(x,y),vec4(vec3(1.0f) - sourcePixel.xyz(),1.0f));
			}

			delete sample;
		}
	}
	/*texture = new Texture::D2;
	texture->Create(uvec2(128));
	texture->Fill(vec4(1.0f,0.5f,0.0f,1.0f));*/

	data_->texture = texture;

	panelImage->SetImage(texture);

	//buttonConnectorOut->Refresh();
	buttonConnectorOut->RefreshObservers();
}


#if _OLOLO_
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
			[&seed](Texture** tex,std::atomic<bool>* flag)
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
#endif




void fInit(Window::Render* window)
{
	auto panelTollbar = window->AddPanel(Interface::PanelTypes::Default);
	panelTollbar->SetSize(vec2(200.0f,32.0f));
	panelTollbar->SetPos(vec2(180.0f + panelTollbar->GetSize().x*0.5f,window->GetSize().y - panelTollbar->GetSize().y*0.5f));
	panelTollbar->LockMove();

	{
		auto b1 = (Interface::Button::Default*)panelTollbar->AddButton(Interface::ButtonTypes::Default);
		b1->SetPos(vec2(-panelTollbar->GetSize().x*0.5f + 16.0f + 32.0f*0,0.0f));
		b1->SetSize(vec2(24.0f));
		b1->SetAction
		(
			Interface::Item::ActionTypes::Click,
			[](Interface::Item* item)
			{
				auto t = new Tool::Generator::D2::Blank(item->GetWindow());
			}
		);

		auto b2 = (Interface::Button::Default*)panelTollbar->AddButton(Interface::ButtonTypes::Default);
		b2->SetPos(vec2(-panelTollbar->GetSize().x*0.5f + 16.0f + 32.0f*1,0.0f));
		b2->SetSize(vec2(24.0f));
		b2->SetAction
		(
			Interface::Item::ActionTypes::Click,
			[](Interface::Item* item)
			{
				auto t = new Tool::Filter::D2::Correction::Color(item->GetWindow());
			}
		);
	}

	auto panelConfig = window->AddPanel(Interface::PanelTypes::Default);
	panelConfig->SetSize(vec2(180.0f,window->GetSize().y));
	panelConfig->SetPos(panelConfig->GetSize()*0.5f);
	panelConfig->LockMove();
}
void fFree(Window::Render* window)
{
}
void fLoop(Window::Render* window)
{
}


void TexProject::Main()
{
	Window::Render wnd;

	wnd.SetFunc(Window::Render::FuncTypes::Init,fInit);
	wnd.SetFunc(Window::Render::FuncTypes::Free,fFree);
	wnd.SetFunc(Window::Render::FuncTypes::Loop,fLoop);
	wnd.Create("window");
	wnd.SetSize(uvec2(800,600));
	wnd.SetRenderContext(Window::RenderContext::Type::Default);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	wnd.Delete();
}













/*
Це кінцева функція-користувач, яка отримує доступ до
нашої програми. Достатньо лише підключити файл TexProject.h
і увесь функціонал буде доступний з неймспейсу TexProject
*/
#include <TexProject/TexProject.h>
using namespace TexProject;


Texture* tex;


namespace Tool
{
	struct Basic
	{
	protected:
		Interface::GUIPanel**				panel = nullptr;
		Interface::GUIButton**				button = nullptr;

	public:
		virtual void						Create(Window::Render* window);
		//virtual void						Delete();
		//virtual void						Loop();

		virtual Texture*					GetInput()
		{
			return nullptr;
		}
	};
	namespace Generator
	{
		namespace Noise
		{
			struct Default: public Tool::Basic
			{
			protected:
				static void					RegenerateTexture(Default* gen,Window::Render* window);

				Texture*					texture = nullptr;
			public:
				virtual void				Create(Window::Render* window) override;
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
				static void					RegenerateTexture(ChannelMixer* gen,Window::Render* window);

				Texture*					texture = nullptr;
			public:
				virtual void				Create(Window::Render* window) override;

				virtual Texture*			GetInput()
				{
					if(button)
					{
						auto t = ((Interface::GUIButtonConnector*)button[2])->GetTarget();
						if(t) return (Texture*)t->GetUserData();
					}
					return nullptr;
				}
			};
		}
	}
}

void					Tool::Basic::Create(Window::Render* window)
{
}

void					Tool::Generator::Noise::Default::RegenerateTexture(Default* gen,Window::Render* window)
{
	if(gen)
	{
		((Interface::GUIPanelImage*)gen->panel[1])->SetImage(nullptr);
		gen->button[2]->SetUserData(nullptr);

		if(gen->texture) delete gen->texture;

		gen->texture = new Texture;
		gen->texture = TexProject::Generator::Noise::SimpleMono(uvec3(128,128,1));

		if(gen->texture)
		{
			gen->texture->Build(window);
			((Interface::GUIPanelImage*)gen->panel[1])->SetImage(gen->texture);

			gen->button[2]->SetUserData(gen->texture);
		}
	}
}
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

	auto b1 = (Interface::GUIButtonConnector*)p1->AddButton(Interface::ButtonTypes::OutputConnector); button[1] = b1;
	b1->SetSize(vec2(8.0f));
	b1->SetPos(vec2(((p1->GetSize().x - b1->GetSize().x)*0.5f - 4.0f),0.0f));
	b1->connectDirection = vec2(100.0f,0.0f);

	auto b2 = (Interface::GUIButtonDefault*)p1->AddButton(Interface::ButtonTypes::Default); button[2] = b2;
	b2->SetSize(vec2(60.0f,24.0f));
	b2->SetPos(vec2(0.0f,p1->GetSize().y*0.5f-16.0f));
	b2->SetUserData(this);
	b2->SetAction(Interface::Item::ActionTypes::Click,
		[](Interface::Item* item)
		{
			auto gen = (Tool::Generator::Noise::Default*)item->GetUserData();
			if(gen) RegenerateTexture(gen,item->GetWindow());
		});
}

void					Tool::Filter::Correction::ChannelMixer::RegenerateTexture(ChannelMixer* gen,Window::Render* window)
{
	if(gen)
	{
		((Interface::GUIPanelImage*)gen->panel[1])->SetImage(nullptr);
		gen->button[2]->SetUserData(nullptr);

		if(gen->texture) delete gen->texture;

		gen->texture = new Texture;
		gen->texture = TexProject::Generator::Noise::SimpleMono(uvec3(128,128,1));
		gen->texture = TexProject::Filter::Noise::Perlin(gen->texture);

		if(gen->texture)
		{
			gen->texture->Build(window);
			((Interface::GUIPanelImage*)gen->panel[1])->SetImage(gen->texture);

			gen->button[2]->SetUserData(gen->texture);
		}
	}
}
void					Tool::Filter::Correction::ChannelMixer::Create(Window::Render* window)
{
	panel = new Interface::GUIPanel*[2];
	button = new Interface::GUIButton*[3];

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

	auto conOut1 = (Interface::GUIButtonConnector*)pMain->AddButton(Interface::ButtonTypes::OutputConnector); button[2] = conOut1;
	conOut1->SetSize(vec2(8.0f));
	conOut1->SetPos(vec2(((pMain->GetSize().x - conIn1->GetSize().x)*0.5f - 4.0f),0.0f));
	conOut1->connectDirection = vec2(100.0f,0.0f);

	auto bRefresh = (Interface::GUIButtonDefault*)pMain->AddButton(Interface::ButtonTypes::Default); button[3] = bRefresh;
	bRefresh->SetSize(vec2(60.0f,24.0f));
	bRefresh->SetPos(vec2(0.0f,pMain->GetSize().y*0.5f-16.0f));
	bRefresh->SetUserData(this);
	bRefresh->SetAction(Interface::Item::ActionTypes::Click,
		[](Interface::Item* item)
		{
			auto gen = (Tool::Filter::Correction::ChannelMixer*)item->GetUserData();
			RegenerateTexture(gen,item->GetWindow());;
		});

	/*for(uint32 i = 0; i < 5; ++i)
	{
		auto b1 = (Interface::GUIButtonConnector*)p1->AddButton(Interface::ButtonTypes::InputConnector); //button[0] = b1;
		b1->SetSize(vec2(8.0f));
		b1->SetPos(vec2( -((p1->GetSize().x - b1->GetSize().x)*0.5f - 4.0f) , i*12.0f ));
		b1->connectDirection = vec2(-100.0f,0.0f);

		auto b2 = (Interface::GUIButtonConnector*)p1->AddButton(Interface::ButtonTypes::OutputConnector); //button[0] = b2;
		b2->SetSize(vec2(8.0f));
		b2->SetPos(vec2( ((p1->GetSize().x - b2->GetSize().x)*0.5f - 4.0f) , i*12.0f ));
		b2->connectDirection = vec2(100.0f,0.0f);
	}*/
}


void windowInit(Window::Render* window)
{
	auto t1 = new Tool::Generator::Noise::Default;
	t1->Create(window);

	auto t2 = new Tool::Filter::Correction::ChannelMixer;
	t2->Create(window);
}


void TexProject::Main()
{
	Window::Render tWindow;

	tWindow.SetFunc(Window::Render::FuncTypes::Init,windowInit);
	tWindow.Create();
	tWindow.SetSize(uvec2(800,600));
	tWindow.SetRenderContext(Window::RenderContext::Types::Default);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	tWindow.Delete();
}













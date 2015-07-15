#include "TexProject_Tools.h"
using namespace TexProject;




// Tool
std::list<TexProject::Tool::Basic*>			TexProject::Tool::tool;
std::list<TexProject::Tool::Basic*>			TexProject::Tool::clean;

TexProject::Window::Render*					TexProject::Tool::window = nullptr;
TexProject::Interface::Panel::Default*		TexProject::Tool::panelConfig = nullptr;

TexProject::Tool::Basic*					TexProject::Tool::focus = nullptr;


void					TexProject::Tool::SetFocus(Basic* source)
{
	if(panelConfig && focus != source)
	{
		if(focus)
		{
			focus->FreeFocus(panelConfig);
			focus = nullptr;
		}
		if(source)
		{
			focus = source;
			focus->InitFocus(panelConfig);
		}
	}
}
void					TexProject::Tool::UnsetFocus(Basic* source)
{
	if(panelConfig && focus == source)
	{
		if(focus)
		{
			focus->FreeFocus(panelConfig);
			focus = nullptr;
		}
	}
}


void TexProject::Tool::Init(Window::Render* window_)
{
	window = window_;

	panelConfig = (Interface::Panel::Default*)window->AddPanel(Interface::PanelTypes::Default);
	panelConfig->SetSize(vec2(180.0f,float32(window->GetSize().y)));
	panelConfig->SetPos(panelConfig->GetSize()*0.5f);
	panelConfig->LockMove();
}
void TexProject::Tool::Free()
{
	for(auto i: tool)
	{
		delete i;
	}
	tool.clear();
}
void TexProject::Tool::Loop()
{
	{
		auto i = tool.begin();
		while(i != tool.end())
		{
			try
			{
				(*i)->Loop();
			}
			catch(Tool::Destruction)
			{
				(*i)->FlushFocus();
				clean.push_back(*i); //delete *i;
				(*i)->iter = tool.end();
				i = tool.erase(i);
				continue;
			}
			++i;
		}
	}
	{
		auto i = clean.begin();
		while(i != clean.end())
		{
			if( (*i)->IsClean() )
			{
				delete *i;
				i = clean.erase(i);
				continue;
			}
			++i;
		}
	}
}


// Tool::Basic
TexProject::Tool::Basic::Basic(Window::Render* window_):
	window(window_),
	iter(tool.end())
{
}
TexProject::Tool::Basic::~Basic()
{
	FlushFocus();
}
void					TexProject::Tool::Basic::Loop()
{
	if(destruction)
	{
		throw Tool::Destruction();
	}
}
void					TexProject::Tool::Basic::Refresh()
{
}
bool					TexProject::Tool::Basic::IsClean()
{
	return true;
}
void					TexProject::Tool::Basic::InitFocus(Interface::Panel::Default* panel)
{
}
void					TexProject::Tool::Basic::FreeFocus(Interface::Panel::Default* panel)
{
}


// Tool::Generator::D2::Blank
TexProject::Tool::Generator::D2::Blank::Blank(Window::Render* window_):
Tool::D2(window_)
{
	panelBase = (Interface::Panel::Default*)window->AddPanel(Interface::PanelTypes::Default);
	panelBase->SetColor(vec4(0.64f,0.64f,0.64f,1.0f));
	panelBase->SetSize(vec2(200.0f));
	panelBase->SetUserData(this);
	panelBase->SetAction
	(
		Interface::Item::ActionTypes::Click,
		[](Interface::Item* item)
		{
			Tool::SetFocus( (Tool::Generator::D2::Blank*)item->GetUserData() );
		}
	);
	panelBase->SetAction
	(
		Interface::Item::ActionTypes::Destruction,
		[](Interface::Item* item)
		{
			((Tool::Generator::D2::Blank*)item->GetUserData())->destruction = true;
		}
	);

	panelTitle = (Interface::Panel::Text*)panelBase->AddPanel(Interface::PanelTypes::Text);
	panelTitle->SetSize(vec2(160.0f,14.0f));
	panelTitle->SetPos(vec2(0.0f,-panelBase->GetSize().y*0.5f + panelTitle->GetSize().y*0.5f));
	panelTitle->SetText("Blank");
	panelTitle->SetAlignment(Interface::Panel::Text::Alignment::CenterTop);

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
	if(generationFlag)
	{
		while(!generationFinish);
		generationThread.join();

		if(generationTexture) delete generationTexture;
	}

	if(texture) delete texture;
}
void					TexProject::Tool::Generator::D2::Blank::Loop()
{
	Basic::Loop();

	if(focusPanel)
	{
		focusPanelSizeXText->SetText(std::to_string(size.x));
		focusPanelSizeYText->SetText(std::to_string(size.y));

		color.x = focusButtonSliderColorRed->GetValue();
		color.y = focusButtonSliderColorGreen->GetValue();
		color.z = focusButtonSliderColorBlue->GetValue();
		color.w = focusButtonSliderColorAlpha->GetValue();
	}

	if(generationFlag)
	{
		if(generationFinish)
		{
			generationThread.join();
			generationFlag = false;

			texture = generationTexture;
			generationTexture = nullptr;

			((OutputData*)buttonConnectorOut->GetUserData())->texture = texture;

			panelImage->SetImage(texture);

			buttonConnectorOut->RefreshObservers();
		}
	}
}
void					TexProject::Tool::Generator::D2::Blank::Refresh()
{
	if(!generationFlag)
	{
		panelImage->SetImage(nullptr);

		((OutputData*)buttonConnectorOut->GetUserData())->texture = nullptr;

		if(texture) { delete texture; texture = nullptr; }

		generationSize = size;
		generationColor = color;
		generationFlag = true;
		generationFinish = false;
		generationThread = std::thread
		(
			[this]()
			{
				generationTexture = new Texture::D2;
				generationTexture->Create(generationSize);
				generationTexture->Fill(generationColor);

				generationFinish = true;
			}
		);
	}
}
bool					TexProject::Tool::Generator::D2::Blank::IsClean()
{
	return !generationFlag || generationFinish;
}
void					TexProject::Tool::Generator::D2::Blank::InitFocus(Interface::Panel::Default* panel)
{
	focusPanel = (Interface::Panel::Default*)panel->AddPanel(Interface::PanelTypes::Default);
	focusPanel->SetColor(vec4(vec3(0.32f),1.0f));
	focusPanel->SetSize(vec2(160.0f,300.0f));

	auto size_ = focusPanel->GetSize();

	focusPanelSizeX = (Interface::Panel::Default*)focusPanel->AddPanel(Interface::PanelTypes::Default);
	focusPanelSizeX->SetSize(vec2(64.0f,16.0f));
	focusPanelSizeX->SetPos(vec2(0.0f,-size_.y*0.5f + 16.0f + 32.0f*1));

	focusPanelSizeXText = (Interface::Panel::Text*)focusPanelSizeX->AddPanel(Interface::PanelTypes::Text);
	focusPanelSizeXText->SetSize(vec2(40.0f,14.0f));
	focusPanelSizeXText->SetPos(vec2(-focusPanelSizeX->GetSize().x*0.5f + focusPanelSizeXText->GetSize().x*0.5f + 2.0f,0.0f));
	focusPanelSizeXText->SetText("test");
	focusPanelSizeXText->SetColor(vec4(vec3(0.5f),1.0f));

	{
		auto t1 = focusPanelSizeX->AddButton(Interface::ButtonTypes::Default);
		t1->SetSize(vec2(10.0f,5.0f));
		t1->SetPos(vec2(focusPanelSizeX->GetSize().x*0.5f - 6.0f,-4.0f));
		t1->SetUserData(this);
		auto ft1 = [](Interface::Item* item)
		{
			auto &t = ((Tool::Generator::D2::Blank*)item->GetUserData())->size.x;
			if(t < 1024) ++t;
		};
		t1->SetAction(Interface::Item::ActionTypes::Click,ft1);
		t1->SetAction(Interface::Item::ActionTypes::Clamp,ft1);
		auto t2 = focusPanelSizeX->AddButton(Interface::ButtonTypes::Default);
		t2->SetSize(vec2(10.0f,5.0f));
		t2->SetPos(vec2(focusPanelSizeX->GetSize().x*0.5f - 6.0f,+4.0f));
		t2->SetUserData(this);
		auto ft2 = [](Interface::Item* item)
		{
			auto &t = ((Tool::Generator::D2::Blank*)item->GetUserData())->size.x;
			if(t > 0) --t;
		};
		t2->SetAction(Interface::Item::ActionTypes::Click,ft2);
		t2->SetAction(Interface::Item::ActionTypes::Clamp,ft2);
	}

	focusPanelSizeY = (Interface::Panel::Default*)focusPanel->AddPanel(Interface::PanelTypes::Default);
	focusPanelSizeY->SetSize(vec2(64.0f,16.0f));
	focusPanelSizeY->SetPos(vec2(0.0f,-size_.y*0.5f + 16.0f + 32.0f*2));

	focusPanelSizeYText = (Interface::Panel::Text*)focusPanelSizeY->AddPanel(Interface::PanelTypes::Text);
	focusPanelSizeYText->SetSize(vec2(40.0f,14.0f));
	focusPanelSizeYText->SetPos(vec2(-focusPanelSizeY->GetSize().x*0.5f + focusPanelSizeYText->GetSize().x*0.5f + 2.0f,0.0f));
	focusPanelSizeYText->SetText("test");
	focusPanelSizeYText->SetColor(vec4(vec3(0.5f),1.0f));

	{
		auto t1 = focusPanelSizeY->AddButton(Interface::ButtonTypes::Default);
		t1->SetSize(vec2(10.0f,5.0f));
		t1->SetPos(vec2(focusPanelSizeY->GetSize().x*0.5f - 6.0f,-4.0f));
		t1->SetUserData(this);
		auto ft1 = [](Interface::Item* item)
		{
			auto &t = ((Tool::Generator::D2::Blank*)item->GetUserData())->size.y;
			if(t < 1024) ++t;
		};
		t1->SetAction(Interface::Item::ActionTypes::Click,ft1);
		t1->SetAction(Interface::Item::ActionTypes::Clamp,ft1);
		auto t2 = focusPanelSizeY->AddButton(Interface::ButtonTypes::Default);
		t2->SetSize(vec2(10.0f,5.0f));
		t2->SetPos(vec2(focusPanelSizeY->GetSize().x*0.5f - 6.0f,+4.0f));
		t2->SetUserData(this);
		auto ft2 = [](Interface::Item* item)
		{
			auto &t = ((Tool::Generator::D2::Blank*)item->GetUserData())->size.y;
			if(t > 0) --t;
		};
		t2->SetAction(Interface::Item::ActionTypes::Click,ft2);
		t2->SetAction(Interface::Item::ActionTypes::Clamp,ft2);
	}

	focusButtonRefresh = (Interface::Button::Default*)focusPanel->AddButton(Interface::ButtonType::Default);
	focusButtonRefresh->SetSize(vec2(80.0f,20.0f));
	focusButtonRefresh->SetPos(vec2(0.0f,-size_.y*0.5f + 16.0f));
	focusButtonRefresh->SetUserData(this);
	focusButtonRefresh->SetAction
	(
		Interface::Item::ActionTypes::Click,
		[](Interface::Item* item)
		{
			((Tool::Generator::D2::Blank*)item->GetUserData())->Refresh();
		}
	);

	focusButtonSliderColorRed = (Interface::Button::Slider*)focusPanel->AddButton(Interface::ButtonType::Slider);
	focusButtonSliderColorRed->SetSize(vec2(120.0f,20.0f));
	focusButtonSliderColorRed->SetPos(vec2(0.0f,-size_.y*0.5f + 16.0f + 32.0f*3));
	focusButtonSliderColorRed->SetValue(color.x);

	focusButtonSliderColorGreen = (Interface::Button::Slider*)focusPanel->AddButton(Interface::ButtonType::Slider);
	focusButtonSliderColorGreen->SetSize(vec2(120.0f,20.0f));
	focusButtonSliderColorGreen->SetPos(vec2(0.0f,-size_.y*0.5f + 16.0f + 32.0f*4));
	focusButtonSliderColorGreen->SetValue(color.y);

	focusButtonSliderColorBlue = (Interface::Button::Slider*)focusPanel->AddButton(Interface::ButtonType::Slider);
	focusButtonSliderColorBlue->SetSize(vec2(120.0f,20.0f));
	focusButtonSliderColorBlue->SetPos(vec2(0.0f,-size_.y*0.5f + 16.0f + 32.0f*5));
	focusButtonSliderColorBlue->SetValue(color.z);

	focusButtonSliderColorAlpha = (Interface::Button::Slider*)focusPanel->AddButton(Interface::ButtonType::Slider);
	focusButtonSliderColorAlpha->SetSize(vec2(120.0f,20.0f));
	focusButtonSliderColorAlpha->SetPos(vec2(0.0f,-size_.y*0.5f + 16.0f + 32.0f*6));
	focusButtonSliderColorAlpha->SetValue(color.w);
}
void					TexProject::Tool::Generator::D2::Blank::FreeFocus(Interface::Panel::Default* panel)
{
	if(focusPanel)
	{
		panel->RemovePanel(focusPanel);
		focusPanel = nullptr;
	}
	/*if(focusButtonRefresh)
	{
		panel->RemoveButton(focusButtonRefresh);
		focusButtonRefresh = nullptr;
	}
	if(focusButtonSliderColorRed)
	{
		panel->RemoveButton(focusButtonSliderColorRed);
		focusButtonSliderColorRed = nullptr;
	}
	if(focusButtonSliderColorGreen)
	{
		panel->RemoveButton(focusButtonSliderColorGreen);
		focusButtonSliderColorGreen = nullptr;
	}
	if(focusButtonSliderColorBlue)
	{
		panel->RemoveButton(focusButtonSliderColorBlue);
		focusButtonSliderColorBlue = nullptr;
	}
	if(focusButtonSliderColorAlpha)
	{
		panel->RemoveButton(focusButtonSliderColorAlpha);
		focusButtonSliderColorAlpha = nullptr;
	}*/
}


// Tool::Filter::D2::Correction::Color
TexProject::Tool::Filter::D2::Correction::Color::Color(Window::Render* window_):
Tool::D2(window_)
{
	panelBase = (Interface::Panel::Default*)window->AddPanel(Interface::PanelTypes::Default);
	panelBase->SetColor(vec4(0.64f,0.64f,0.64f,1.0f));
	panelBase->SetSize(vec2(200.0f));
	panelBase->SetUserData(this);
	panelBase->SetAction
	(
		Interface::Item::ActionTypes::Click,
		[](Interface::Item* item)
		{
			Tool::SetFocus( (Tool::Generator::D2::Blank*)item->GetUserData() );
		}
	);
	panelBase->SetAction
	(
		Interface::Item::ActionTypes::Destruction,
		[](Interface::Item* item)
		{
			((Tool::Generator::D2::Blank*)item->GetUserData())->destruction = true;
		}
	);

	panelTitle = (Interface::Panel::Text*)panelBase->AddPanel(Interface::PanelTypes::Text);
	panelTitle->SetSize(vec2(160.0f,14.0f));
	panelTitle->SetPos(vec2(0.0f,-panelBase->GetSize().y*0.5f + panelTitle->GetSize().y*0.5f));
	panelTitle->SetText("Color Correction");
	panelTitle->SetAlignment(Interface::Panel::Text::Alignment::CenterTop);

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
	if(generationFlag)
	{
		while(!generationFinish);
		generationThread.join();

		if(generationTexture) delete generationTexture;
	}

	if(texture) delete texture;
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
void										TexProject::Tool::Filter::D2::Correction::Color::Loop()
{
	Basic::Loop();

	if(generationFlag)
	{
		if(generationFinish)
		{
			generationThread.join();
			generationFlag = false;

			texture = generationTexture;
			generationTexture = nullptr;

			((OutputData*)buttonConnectorOut->GetUserData())->texture = texture;

			panelImage->SetImage(texture);

			buttonConnectorOut->RefreshObservers();
		}
	}
}
void										TexProject::Tool::Filter::D2::Correction::Color::Refresh()
{
	if(!generationFlag)
	{

		panelImage->SetImage(nullptr);

		((OutputData*)buttonConnectorOut->GetUserData())->texture = nullptr;

		if(texture) { delete texture; texture = nullptr; }

		auto source = GetInput();
		if(source)
		{
			if(!generationInputTexture) delete generationInputTexture;
			generationInputTexture = new Texture::D2(*source);

			generationFlag = true;
			generationFinish = false;
			generationThread = std::thread
			(
				[this]()
				{
					generationTexture = new Texture::D2;
					generationTexture->Create(generationInputTexture->GetSize());
					
					for(uint32 x = 0; x < generationTexture->GetSize().x; ++x)
					for(uint32 y = 0; y < generationTexture->GetSize().y; ++y)
					{
						auto sourcePixel = generationInputTexture->GetPixel(uvec2(x,y));
						generationTexture->SetPixel(uvec2(x,y),vec4(vec3(1.0f) - sourcePixel.xyz(),1.0f));
					}

					delete generationInputTexture;
					generationInputTexture = nullptr;

					generationFinish = true;
				}
			);
		}
	}
}
bool										TexProject::Tool::Filter::D2::Correction::Color::IsClean()
{
	return !generationFlag || generationFinish;
}





























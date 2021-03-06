#include "TexProject_Tools.h"
using namespace TexProject;

#pragma region
#pragma endregion

#pragma region ToolSet
TexProject::ToolSet::ToolSet(Window* window_):
	WindowBind(window_)
{
	auto gui = window->GetGUI();

	panelConfig = (GUI::Panels::Default*)gui->AddPanel(GUI::PanelTypes::Default);
	{
		panelConfig->DisableDragging();
		panelConfig->EnableTopMost();
		panelConfig->SetSize(vec2(180.0f,float32(window->GetSize().y)));
		panelConfig->SetPos(vec2(0.0f));
	}
	panelTools = (GUI::Panels::Default*)gui->AddPanel(GUI::PanelTypes::Default);
	{
		panelTools->DisableDragging();
		panelTools->EnableTopMost();
		panelTools->EnableScrolling();
		panelTools->SetScrollingSize(vec2(100.0f,0.0f));
		panelTools->SetSize(vec2(window->GetSize().x - panelConfig->GetSize().x - 16.0f,40.0f));
		panelTools->SetPos(vec2(panelConfig->GetSize().x + 8.0f,window->GetSize().y - panelTools->GetSize().y));
		{
			auto SummonButton = [this](const string& tip, GUI::Item::Action action)
			{
				static uint32 pos = 0;
				auto button = (GUI::Buttons::Default*)panelTools->AddButton(GUI::ButtonTypes::Default);
				{
					button->SetTip(tip);
					button->SetUserData(this);
					button->SetColor(vec4(0,1,0,1));
					button->SetSize(vec2(32.0f));
					button->SetPos(vec2(20.0f - button->GetSize().x*0.5f + 40.0f * pos,(panelTools->GetSize().y - button->GetSize().y)*0.5f));
					button->SetAction(GUI::Item::ActionType::Click,action);
				}
				++pos;
				return button;
			};

			SummonButton("Empty", [](GUI::Item* item) { new Tools::Generator::Empty((ToolSet*)item->GetUserData()); });
			SummonButton("Simple Noise", [](GUI::Item* item) { new Tools::Generator::Noise::Simple((ToolSet*)item->GetUserData()); });
			SummonButton("Perlin Noise",[](GUI::Item* item) { new Tools::Generator::Noise::Perlin((ToolSet*)item->GetUserData()); });
			SummonButton("Worley Noise",[](GUI::Item* item) { new Tools::Generator::Noise::Worley((ToolSet*)item->GetUserData()); });
			SummonButton("Grayscale", [](GUI::Item* item) { new Tools::Filter::Correction::Grayscale((ToolSet*)item->GetUserData()); });
			SummonButton("Blur", [](GUI::Item* item) { new Tools::Filter::Correction::Blur((ToolSet*)item->GetUserData()); });
			SummonButton("Function", [](GUI::Item* item) { new Tools::Filter::Correction::Function((ToolSet*)item->GetUserData()); });
			SummonButton("Mix", [](GUI::Item* item) { new Tools::Filter::Correction::Mix((ToolSet*)item->GetUserData()); });
			SummonButton("Height To Normal", [](GUI::Item* item) { new Tools::Filter::Physics::HeightToNormal((ToolSet*)item->GetUserData()); });
			SummonButton("Slope Factor", [](GUI::Item* item) { new Tools::Filter::Physics::NormalsToSlopeFactor((ToolSet*)item->GetUserData()); });
			SummonButton("Viewer Simple", [](GUI::Item* item) { new Tools::Viewer::Simple((ToolSet*)item->GetUserData()); });
			SummonButton("Viewer Bump", [](GUI::Item* item) { new Tools::Viewer::BumpMapping((ToolSet*)item->GetUserData()); });
		}
	}
}
TexProject::ToolSet::~ToolSet()
{
	auto i = tool.begin();
	while(i != tool.end())
	{
		auto del = *i;
		i = tool.erase(i);
		delete del;
		continue;
	}
}
void										TexProject::ToolSet::FocusSet(Tool* tool)
{
	if(focus)
	{
		focus->FocusFree();
	}
	focus = tool;
	if(focus)
	{
		focus->FocusInit();
	}
}
void										TexProject::ToolSet::Loop()
{
	panelConfig->SetSize(vec2(180.0f,float32(window->GetSize().y)));
	panelConfig->SetPos(vec2(0.0f));

	panelTools->SetSize(vec2(window->GetSize().x - panelConfig->GetSize().x - 16.0f,40.0f));
	panelTools->SetPos(vec2(panelConfig->GetSize().x + 8.0f,window->GetSize().y - panelTools->GetSize().y));

	oMouse = nMouse;
	nMouse = vec2(MousePos());

	if(KeyState(Key::SPACE))
	{
		if(MouseLState())
		{
			anchor += nMouse - oMouse;
		}
	}

	auto i = tool.begin();
	while(i != tool.end())
	{		
		try
		{
			(*i)->Loop();
		}
		catch(Tool::Destruction)
		{
			auto del = *i;
			i = tool.erase(i);
			delete del;
			continue;
		}
		++i;
	}
}
#pragma endregion
#pragma region ToolSetBind
TexProject::ToolSetBind::ToolSetBind(ToolSet* toolSet_):
	toolSet(toolSet_)
{
}
#pragma endregion
#pragma region Tool
TexProject::Tool::Tool(ToolSet* toolSet_):
	ToolSetBind(toolSet_)
{
	toolSet->tool.push_back(this);

	auto gui = toolSet->GetWindow()->GetGUI();

	panelFieldBase = (GUI::Panels::Default*)gui->AddPanel(GUI::PanelTypes::Default);
	{
		panelFieldBase->SetUserData(this);
		panelFieldBase->EnableClosing();
		panelFieldBase->SetAction
		(
			GUI::Item::ActionType::Destruction,
			[](GUI::Item* item)
			{
				((Tool*)item->GetUserData())->panelFieldBase = nullptr;
			}
		);
		panelFieldBase->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				auto tool = (Tool*)item->GetUserData();
				tool->toolSet->FocusSet(tool);
			}
		);
		panelFieldBase->SetSize(vec2(180.0f));
		panelFieldBase->SetPos(vec2(toolSet->GetWindow()->GetSize())*0.5f - toolSet->anchor - panelFieldBase->GetSize()*0.5f);
		panelFieldBase->SetColor(vec4(vec3(0.32f),1.0f));
	}

	panelFieldTitle = (GUI::Panels::Text*)panelFieldBase->AddPanel(GUI::PanelTypes::Text);
	{
		panelFieldTitle->SetText("Title");
		panelFieldTitle->SetSize(vec2(120.0f,20.0f));
		panelFieldTitle->SetPos(vec2((panelFieldBase->GetSize().x - panelFieldTitle->GetSize().x)*0.5f,panelFieldBase->GetSize().y - panelFieldTitle->GetSize().y));
	}

	panelFieldImage = (GUI::Panels::Image*)panelFieldBase->AddPanel(GUI::PanelTypes::Image);
	{
		panelFieldImage->DisableDragging();
		panelFieldImage->SetSize(vec2(128.0f));
		panelFieldImage->SetPos(vec2((panelFieldBase->GetSize() - panelFieldImage->GetSize())*0.5f));
		panelFieldImage->SetColor(vec4(1,0,0,1));
	}

	buttonFieldRefresh = (GUI::Buttons::Default*)panelFieldBase->AddButton(GUI::ButtonTypes::Default);
	{
		buttonFieldRefresh->DisableDragging();
		buttonFieldRefresh->SetColor(vec4(0,1,0,1));
		buttonFieldRefresh->SetSize(vec2(80.0f,12.0f));
		buttonFieldRefresh->SetPos(vec2((panelFieldBase->GetSize().x - buttonFieldRefresh->GetSize().x)*0.5f,4.0f));
	}
}
TexProject::Tool::~Tool()
{
	if(toolSet->focus == this)
	{
		toolSet->FocusSet(nullptr);
	}

	toolSet->tool.remove(this);
}
void										TexProject::Tool::Loop()
{
	if(panelFieldBase)
	{
		panelFieldBase->SetAnchor(toolSet->anchor);
	}
	else
	{
		throw Destruction();
	}
}
void										TexProject::Tool::FocusInit()
{
	panelConfigBase = (GUI::Panels::Default*)toolSet->panelConfig->AddPanel(GUI::PanelTypes::Default);
	{
		panelConfigBase->SetColor(vec4(1,0,0,1));
		panelConfigBase->SetSize(vec2(toolSet->panelConfig->GetSize().x - 8.0f,100.0f));
		panelConfigBase->SetPos(vec2(4.0f,toolSet->panelConfig->GetSize().y - panelConfigBase->GetSize().y - 4.0f));
	}
	panelConfigTitle = (GUI::Panels::Text*)panelConfigBase->AddPanel(GUI::PanelTypes::Text);
	{
		panelConfigTitle->SetText("Title");
		panelConfigTitle->SetSize(vec2(160.0f,20.0f));
		panelConfigTitle->SetPos(vec2((panelConfigBase->GetSize().x - panelConfigTitle->GetSize().x)*0.5f,panelConfigBase->GetSize().y - panelConfigTitle->GetSize().y));
	}
}
void										TexProject::Tool::FocusFree()
{
	if(panelConfigBase)
	{
		toolSet->panelConfig->RemoveItem(panelConfigBase);
		panelConfigBase = nullptr;
	}
}
#pragma endregion
#pragma region Tools

TexProject::GUI::Item*						TexProject::Tools::CreateSizer(GUI* gui)
{
	auto panelBase = (GUI::Panels::Default*)gui->AddPanel(GUI::PanelTypes::Default);
	{
		auto data = new SizerData;
		{
			data->minVal = 16;
		}

		panelBase->SetSize(vec2(160.0f,20.0f));
		panelBase->SetColor(vec4(0,0,1,1));
		panelBase->SetUserData(data,true);

		auto panelText = (GUI::Panels::Text*)panelBase->AddPanel(GUI::PanelTypes::Text);
		{
			panelText->SetUserData(panelBase);
			panelText->SetAction
			(
				GUI::Item::ActionType::Refresh,
				[](GUI::Item* item)
				{
					auto data = (SizerData*)((GUI::Panels::Default*)item->GetUserData())->GetUserData();
					((GUI::Panels::Text*)item)->SetText(std::to_string(data->val));
				}
			);
			panelText->SetText("999");
			panelText->SetSize(vec2(40.0f,20.0f));
			panelText->SetPos(vec2(0.0f));
		}

		auto buttonInc = (GUI::Buttons::Default*)panelBase->AddButton(GUI::ButtonTypes::Default);
		{
			buttonInc->SetUserData(panelBase);
			buttonInc->SetAction
			(
				GUI::Item::ActionType::Click,
				[](GUI::Item* item)
				{
					auto data = (SizerData*)((GUI::Buttons::Default*)item->GetUserData())->GetUserData();
					if(data->val + 1 <= data->maxVal) ++data->val;
					data->buttonSlider->SetValue(float32(data->val - data->minVal) / float32(data->maxVal - data->minVal));
				}
			);
			buttonInc->SetSize(vec2(16.0f,8.0f));
			buttonInc->SetPos(vec2(panelText->GetSize().x,11.0f));
		}
		auto buttonDec = (GUI::Buttons::Default*)panelBase->AddButton(GUI::ButtonTypes::Default);
		{
			buttonDec->SetUserData(panelBase);
			buttonDec->SetAction
			(
				GUI::Item::ActionType::Click,
				[](GUI::Item* item)
				{
					auto data = (SizerData*)((GUI::Buttons::Default*)item->GetUserData())->GetUserData();
					if(data->val - 1 >= data->minVal) --data->val;
					data->buttonSlider->SetValue(float32(data->val - data->minVal) / float32(data->maxVal - data->minVal));
				}
			);
			buttonDec->SetSize(vec2(16.0f,8.0f));
			buttonDec->SetPos(vec2(panelText->GetSize().x,1.0f));
		}

		auto buttonSlider = (GUI::Buttons::Slider*)panelBase->AddButton(GUI::ButtonTypes::Slider);
		{
			buttonSlider->SetUserData(panelBase);
			buttonSlider->SetAction
			(
				GUI::Item::ActionType::Refresh,
				[](GUI::Item* item)
				{
					auto data = (SizerData*)((GUI::Buttons::Default*)item->GetUserData())->GetUserData();
					auto val = ((GUI::Buttons::Slider*)item)->GetValue();
					data->val = clamp(int32(data->minVal + val * float32(data->maxVal - data->minVal)),data->minVal,data->maxVal);
				}
			);
			buttonSlider->SetColor(vec4(0,1,0,1));
			buttonSlider->SetSize(vec2(panelBase->GetSize().x - panelText->GetSize().x - 16.0f - 8.0f,16.0f));
			buttonSlider->SetPos(vec2(panelBase->GetSize().x - buttonSlider->GetSize().x - 4.0f,2.0f));
		}

		data->panelBase = panelBase;
		data->buttonSlider = buttonSlider;
	}
	return panelBase;
}
TexProject::GUI::Item*						TexProject::Tools::CreateFloatSizer(GUI* gui)
{
	auto panelBase = (GUI::Panels::Default*)gui->AddPanel(GUI::PanelTypes::Default);
	{
		auto data = new SizerFloatData;
		{
		}

		panelBase->SetSize(vec2(160.0f,20.0f));
		panelBase->SetColor(vec4(0,0,1,1));
		panelBase->SetUserData(data,true);

		auto panelText = (GUI::Panels::Text*)panelBase->AddPanel(GUI::PanelTypes::Text);
		{
			panelText->SetUserData(panelBase);
			panelText->SetAction
			(
				GUI::Item::ActionType::Refresh,
				[](GUI::Item* item)
				{
					auto data = (SizerFloatData*)((GUI::Panels::Default*)item->GetUserData())->GetUserData();
					((GUI::Panels::Text*)item)->SetText(std::to_string(data->val).substr(0,4));
				}
			);
			panelText->SetText("999");
			panelText->SetSize(vec2(40.0f,20.0f));
			panelText->SetPos(vec2(0.0f));
		}

		auto buttonInc = (GUI::Buttons::Default*)panelBase->AddButton(GUI::ButtonTypes::Default);
		{
			buttonInc->SetUserData(panelBase);
			buttonInc->SetAction
			(
				GUI::Item::ActionType::Click,
				[](GUI::Item* item)
				{
					auto data = (SizerFloatData*)((GUI::Buttons::Default*)item->GetUserData())->GetUserData();
					if(data->val + 1 <= data->maxVal) ++data->val;
					data->buttonSlider->SetValue((data->val - data->minVal) / (data->maxVal - data->minVal));
				}
			);
			buttonInc->SetSize(vec2(16.0f,8.0f));
			buttonInc->SetPos(vec2(panelText->GetSize().x,11.0f));
		}
		auto buttonDec = (GUI::Buttons::Default*)panelBase->AddButton(GUI::ButtonTypes::Default);
		{
			buttonDec->SetUserData(panelBase);
			buttonDec->SetAction
			(
				GUI::Item::ActionType::Click,
				[](GUI::Item* item)
				{
					auto data = (SizerFloatData*)((GUI::Buttons::Default*)item->GetUserData())->GetUserData();
					if(data->val - 1 >= data->minVal) --data->val;
					data->buttonSlider->SetValue((data->val - data->minVal) / (data->maxVal - data->minVal));
				}
			);
			buttonDec->SetSize(vec2(16.0f,8.0f));
			buttonDec->SetPos(vec2(panelText->GetSize().x,1.0f));
		}

		auto buttonSlider = (GUI::Buttons::Slider*)panelBase->AddButton(GUI::ButtonTypes::Slider);
		{
			buttonSlider->SetUserData(panelBase);
			buttonSlider->SetAction
			(
				GUI::Item::ActionType::Refresh,
				[](GUI::Item* item)
				{
					auto data = (SizerFloatData*)((GUI::Buttons::Default*)item->GetUserData())->GetUserData();
					auto val = ((GUI::Buttons::Slider*)item)->GetValue();
					data->val = clamp(float32(data->minVal + val * float32(data->maxVal - data->minVal)),data->minVal,data->maxVal);
				}
			);
			buttonSlider->SetColor(vec4(0,1,0,1));
			buttonSlider->SetSize(vec2(panelBase->GetSize().x - panelText->GetSize().x - 16.0f - 8.0f,16.0f));
			buttonSlider->SetPos(vec2(panelBase->GetSize().x - buttonSlider->GetSize().x - 4.0f,2.0f));
		}

		data->panelBase = panelBase;
		data->buttonSlider = buttonSlider;
	}
	return panelBase;
}

#pragma region Generator
#pragma region Empty
TexProject::Tools::Generator::Empty::Empty(ToolSet* toolSet_):
	Tool(toolSet_)
{
	panelFieldTitle->SetText("Empty");
	buttonOutput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonOutput->SetUserData
		(
			new OutputData
			{
				OutputData::Type::Texture2D,
				nullptr
			},
			true
		);
		buttonOutput->DisableDragging();
		buttonOutput->SetSize(vec2(8.0f));
		buttonOutput->SetPos(vec2(panelFieldBase->GetSize().x - buttonOutput->GetSize().x - 4.0f, (panelFieldBase->GetSize().y - buttonOutput->GetSize().y)*0.5f));
		buttonOutput->direction = vec2(100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				((Tools::Generator::Empty*)item->GetUserData())->Refresh();
			}
		);
	}
}
TexProject::Tools::Generator::Empty::~Empty()
{
	if(texture) delete texture;
}
void										TexProject::Tools::Generator::Empty::Refresh()
{
	//texture->Create(uvec2(256));
	{
		OPENFILENAME ofn;
		{
			static char szFile[100];
			memset(&ofn,0,sizeof(ofn));
			ofn.lStructSize = sizeof (ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			{
				ofn.lpstrInitialDir = GetEXEPath().c_str();
			}
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		}
		GetOpenFileName(&ofn);
		string filename = ofn.lpstrFile;

		if(filename.length() > 0) texture->Load(filename);
	}
	panelFieldImage->SetImage(texture);
	((OutputData*)buttonOutput->GetUserData())->data = texture;
	buttonOutput->RefreshObservers();
}
#pragma endregion
#pragma region Noise
#pragma region Simple
TexProject::Tools::Generator::Noise::Simple::Simple(ToolSet* toolSet_):
	Tool(toolSet_)
{
	panelFieldTitle->SetText("Simple Noise");
	buttonOutput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonOutput->SetUserData
		(
			new OutputData
			{
				OutputData::Type::Texture2D,
				nullptr
			},
			true
		);
		buttonOutput->DisableDragging();
		buttonOutput->SetSize(vec2(8.0f));
		buttonOutput->SetPos(vec2(panelFieldBase->GetSize().x - buttonOutput->GetSize().x - 4.0f, (panelFieldBase->GetSize().y - buttonOutput->GetSize().y)*0.5f));
		buttonOutput->direction = vec2(100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				((Tools::Generator::Noise::Simple*)item->GetUserData())->Refresh();
			}
		);
	}
}
TexProject::Tools::Generator::Noise::Simple::~Simple()
{
	if(texture) delete texture;
}
void										TexProject::Tools::Generator::Noise::Simple::FocusInit()
{
	panelConfigBase = (GUI::Panels::Default*)toolSet->panelConfig->AddPanel(GUI::PanelTypes::Default);
	{
		panelConfigBase->SetColor(vec4(vec3(0.16f),1));
		panelConfigBase->SetSize(vec2(toolSet->panelConfig->GetSize().x - 8.0f,400.0f));
		panelConfigBase->SetPos(vec2(4.0f,toolSet->panelConfig->GetSize().y - panelConfigBase->GetSize().y - 4.0f));
	}
	panelConfigTitle = (GUI::Panels::Text*)panelConfigBase->AddPanel(GUI::PanelTypes::Text);
	{
		panelConfigTitle->SetText("Simple Noise");
		panelConfigTitle->SetSize(vec2(160.0f,20.0f));
		panelConfigTitle->SetPos(vec2((panelConfigBase->GetSize().x - panelConfigTitle->GetSize().x)*0.5f,panelConfigBase->GetSize().y - panelConfigTitle->GetSize().y));
	}
	buttonConfigMonochrome = (GUI::Buttons::Trigger*)panelConfigBase->AddButton(GUI::ButtonTypes::Trigger);
	{
		buttonConfigMonochrome->SetState(paramMonochrome);
		buttonConfigMonochrome->SetUserData(this);
		buttonConfigMonochrome->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				auto &param = ((Tools::Generator::Noise::Simple*)item->GetUserData())->paramMonochrome;
				param = !param;
			}
		);
		buttonConfigMonochrome->SetSize(vec2(20.0f));
		buttonConfigMonochrome->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f*1));
		{
			auto t = (GUI::Panels::Text*)panelConfigBase->AddPanel(GUI::PanelTypes::Text);
			t->SetSize(vec2(100.0f,buttonConfigMonochrome->GetSize().y));
			t->SetPos(buttonConfigMonochrome->GetLocalPos() + vec2(buttonConfigMonochrome->GetSize().x + 4.0f,0.0f));
			t->SetText("Monochrome");
		}
	}
	panelConfigSizerX = (GUI::Panels::Default*)CreateSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigSizerX);
		panelConfigSizerX->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 2));
		((SizerData*)panelConfigSizerX->GetUserData())->val = paramSize.x;
	}
	panelConfigSizerY = (GUI::Panels::Default*)CreateSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigSizerY);
		panelConfigSizerY->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 3));
		((SizerData*)panelConfigSizerY->GetUserData())->val = paramSize.y;
	}
}
void										TexProject::Tools::Generator::Noise::Simple::Refresh()
{
	if(panelConfigBase)
	{
		paramSize.x = uint32(((SizerData*)panelConfigSizerX->GetUserData())->val);
		paramSize.y = uint32(((SizerData*)panelConfigSizerY->GetUserData())->val);
	}

	texture->Create(uvec2(paramSize));
	{
		if(paramMonochrome)
		{
			for(uint32 x = 0; x < texture->GetSize().x; ++x)
			for(uint32 y = 0; y < texture->GetSize().y; ++y)
			{
				texture->SetPixel(uvec2(x,y),vec4(vec3(rnd()),1.0f));
			}
		}
		else
		{
			for(uint32 x = 0; x < texture->GetSize().x; ++x)
			for(uint32 y = 0; y < texture->GetSize().y; ++y)
			{
				texture->SetPixel(uvec2(x,y),vec4(rnd(),rnd(),rnd(),1.0f));
			}
		}
	}
	panelFieldImage->SetImage(texture);
	((OutputData*)buttonOutput->GetUserData())->data = texture;
	buttonOutput->RefreshObservers();
}
#pragma endregion
#pragma region Simple
TexProject::Tools::Generator::Noise::Perlin::Perlin(ToolSet* toolSet_):
Tool(toolSet_)
{
	panelFieldTitle->SetText("Perlin Noise");
	buttonOutput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonOutput->SetUserData
		(
			new OutputData
			{
				OutputData::Type::Texture2D,
				nullptr
			},
			true
		);
		buttonOutput->DisableDragging();
		buttonOutput->SetSize(vec2(8.0f));
		buttonOutput->SetPos(vec2(panelFieldBase->GetSize().x - buttonOutput->GetSize().x - 4.0f,(panelFieldBase->GetSize().y - buttonOutput->GetSize().y)*0.5f));
		buttonOutput->direction = vec2(100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				((Tools::Generator::Noise::Perlin*)item->GetUserData())->Refresh();
			}
		);
	}
}
TexProject::Tools::Generator::Noise::Perlin::~Perlin()
{
	if(texture) delete texture;
}
void										TexProject::Tools::Generator::Noise::Perlin::FocusInit()
{
	panelConfigBase = (GUI::Panels::Default*)toolSet->panelConfig->AddPanel(GUI::PanelTypes::Default);
	{
		panelConfigBase->SetColor(vec4(vec3(0.16f),1));
		panelConfigBase->SetSize(vec2(toolSet->panelConfig->GetSize().x - 8.0f,400.0f));
		panelConfigBase->SetPos(vec2(4.0f,toolSet->panelConfig->GetSize().y - panelConfigBase->GetSize().y - 4.0f));
	}
	panelConfigTitle = (GUI::Panels::Text*)panelConfigBase->AddPanel(GUI::PanelTypes::Text);
	{
		panelConfigTitle->SetText("Perlin Noise");
		panelConfigTitle->SetSize(vec2(160.0f,20.0f));
		panelConfigTitle->SetPos(vec2((panelConfigBase->GetSize().x - panelConfigTitle->GetSize().x)*0.5f,panelConfigBase->GetSize().y - panelConfigTitle->GetSize().y));
	}
	panelConfigSizerX = (GUI::Panels::Default*)CreateSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigSizerX);
		panelConfigSizerX->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 2));
		((SizerData*)panelConfigSizerX->GetUserData())->val = paramSize.x;
	}
	panelConfigSizerY = (GUI::Panels::Default*)CreateSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigSizerY);
		panelConfigSizerY->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 3));
		((SizerData*)panelConfigSizerY->GetUserData())->val = paramSize.y;
	}
	panelConfigBasisCount = (GUI::Panels::Default*)CreateSizer(panelConfigBase->GetGUI());
	{
		auto data = (SizerData*)panelConfigBasisCount->GetUserData();
		{
			data->minVal = 4;
			data->maxVal = 256;
		}
		panelConfigBase->AttachItem(panelConfigBasisCount);
		panelConfigBasisCount->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 4));
		((SizerData*)panelConfigBasisCount->GetUserData())->val = paramBasisCount;
	}		
	panelConfigNoiseSize = (GUI::Panels::Default*)CreateFloatSizer(panelConfigBase->GetGUI());
	{
		auto data = (SizerFloatData*)panelConfigNoiseSize->GetUserData();
		{
			data->minVal = 1.0f;
			data->maxVal = 64.0f;
			data->val = paramNoiseSize;
		}
		panelConfigBase->AttachItem(panelConfigNoiseSize);
		panelConfigNoiseSize->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 5));
	}
}
void										TexProject::Tools::Generator::Noise::Perlin::Refresh()
{
	if(panelConfigBase)
	{
		paramSize.x = uint32(((SizerData*)panelConfigSizerX->GetUserData())->val);
		paramSize.y = uint32(((SizerData*)panelConfigSizerY->GetUserData())->val);
		paramBasisCount = uint32(((SizerData*)panelConfigBasisCount->GetUserData())->val);
		paramNoiseSize = ((SizerFloatData*)panelConfigNoiseSize->GetUserData())->val;
	}

	texture->Create(uvec2(paramSize));
	{
		uvec2 gridSize = uvec2(paramBasisCount);
		vec2* grid = new vec2[gridSize.x*gridSize.y];
		{
			for(uint32 x = 0; x < gridSize.x; ++x)
			for(uint32 y = 0; y < gridSize.y; ++y)
			{
				grid[x + y*gridSize.x] = normalize(vec2(rnd(),rnd())*2.0f-1.0f);
			}
		}
		auto getGrid = [&grid,&gridSize](vec2 v) -> float32
		{
			auto getTile = [&gridSize](uvec2 t) -> uvec2
			{
				return uvec2
				(
					t.x >= gridSize.x ? 0 : t.x,
					t.y >= gridSize.y ? 0 : t.y
				);
			};
			auto getVal = [&grid,&gridSize](uvec2 t) -> vec2
			{
				return grid[t.x + t.y*gridSize.x];
			};

			v.x = wrap(v.x,0.0f,float32(gridSize.x));
			v.y = wrap(v.y,0.0f,float32(gridSize.y));

			uvec2 g00 = uvec2((uint32)floor(v.x),(uint32)floor(v.y));
			uvec2 g10 = uvec2((uint32)ceil(v.x),(uint32)floor(v.y));
			uvec2 g01 = uvec2((uint32)floor(v.x),(uint32)ceil(v.y));
			uvec2 g11 = uvec2((uint32)ceil(v.x),(uint32)ceil(v.y));

			v = vec2
			(
				v.x - floor(v.x),
				v.y - floor(v.y)
			);

			vec2 v00 = vec2(0.0f,0.0f) - v;
			vec2 v10 = vec2(1.0f,0.0f) - v;
			vec2 v01 = vec2(0.0f,1.0f) - v;
			vec2 v11 = vec2(1.0f,1.0f) - v;

			vec2 p00 = getVal(getTile(g00));
			vec2 p10 = getVal(getTile(g10));
			vec2 p01 = getVal(getTile(g01));
			vec2 p11 = getVal(getTile(g11));

			float32 q00 = dot(p00,v00);
			float32 q10 = dot(p10,v10);
			float32 q01 = dot(p01,v01);
			float32 q11 = dot(p11,v11);

			vec2 i = vec2
			(
				sinDg((v.x*2.0f - 1.0f)*90.0f),
				sinDg((v.y*2.0f - 1.0f)*90.0f)
			)*0.5f + 0.5f;

			return bezier
			(
				bezier(q00,q01,i.y),
				bezier(q10,q11,i.y),
				i.x
			);
		};

		for(uint32 x = 0; x < texture->GetSize().x; ++x)
		for(uint32 y = 0; y < texture->GetSize().y; ++y)
		{
			texture->SetPixel
			(
				uvec2(x,y),
				vec4
				(
					vec3
					(
						getGrid(vec2(float32(x),float32(y)) / vec2(paramSize) * paramNoiseSize)*0.5f + 0.5f
					),
					1.0f
				)
			);
		}

		delete grid;
	}
	panelFieldImage->SetImage(texture);
	((OutputData*)buttonOutput->GetUserData())->data = texture;
	buttonOutput->RefreshObservers();
}
#pragma endregion
#pragma region Worley
TexProject::Tools::Generator::Noise::Worley::Worley(ToolSet* toolSet_):
Tool(toolSet_)
{
	panelFieldTitle->SetText("Worley Noise");
	buttonOutput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonOutput->SetUserData
		(
			new OutputData
			{
				OutputData::Type::Texture2D,
				nullptr
			},
			true
		);
			buttonOutput->DisableDragging();
			buttonOutput->SetSize(vec2(8.0f));
			buttonOutput->SetPos(vec2(panelFieldBase->GetSize().x - buttonOutput->GetSize().x - 4.0f,(panelFieldBase->GetSize().y - buttonOutput->GetSize().y)*0.5f));
			buttonOutput->direction = vec2(100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
			(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
		{
			((Tools::Generator::Noise::Worley*)item->GetUserData())->Refresh();
		}
		);
	}
}
TexProject::Tools::Generator::Noise::Worley::~Worley()
{
	if(texture) delete texture;
}
void										TexProject::Tools::Generator::Noise::Worley::FocusInit()
{
	panelConfigBase = (GUI::Panels::Default*)toolSet->panelConfig->AddPanel(GUI::PanelTypes::Default);
	{
		panelConfigBase->SetColor(vec4(vec3(0.16f),1));
		panelConfigBase->SetSize(vec2(toolSet->panelConfig->GetSize().x - 8.0f,400.0f));
		panelConfigBase->SetPos(vec2(4.0f,toolSet->panelConfig->GetSize().y - panelConfigBase->GetSize().y - 4.0f));
	}
	panelConfigTitle = (GUI::Panels::Text*)panelConfigBase->AddPanel(GUI::PanelTypes::Text);
	{
		panelConfigTitle->SetText("Worley Noise");
		panelConfigTitle->SetSize(vec2(160.0f,20.0f));
		panelConfigTitle->SetPos(vec2((panelConfigBase->GetSize().x - panelConfigTitle->GetSize().x)*0.5f,panelConfigBase->GetSize().y - panelConfigTitle->GetSize().y));
	}
	panelConfigSizerX = (GUI::Panels::Default*)CreateSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigSizerX);
		panelConfigSizerX->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 1));
		((SizerData*)panelConfigSizerX->GetUserData())->val = paramSize.x;
	}
	panelConfigSizerY = (GUI::Panels::Default*)CreateSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigSizerY);
		panelConfigSizerY->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 2));
		((SizerData*)panelConfigSizerY->GetUserData())->val = paramSize.y;
	}
	panelConfigCount = (GUI::Panels::Default*)CreateSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigCount);
		panelConfigCount->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 3));
		auto data = (SizerData*)panelConfigCount->GetUserData();
		data->val = paramDotsCount;
		data->minVal = 1;
		data->maxVal = 200;
	}	
}
void										TexProject::Tools::Generator::Noise::Worley::Refresh()
{
	if(panelConfigBase)
	{
		paramSize.x = uint32(((SizerData*)panelConfigSizerX->GetUserData())->val);
		paramSize.y = uint32(((SizerData*)panelConfigSizerY->GetUserData())->val);
		paramDotsCount = uint32(((SizerData*)panelConfigCount->GetUserData())->val);
	}

	texture->Create(uvec2(paramSize));
	{
		uint32 width = texture->GetSize().x;
		float32 wcoef = 1.0f / width;

		uint32 height = texture->GetSize().y;
		float32 hcoef = 1.0f / height;
		vec2* dotArr = new vec2[paramDotsCount];

		for(uint32 i = 0; i < paramDotsCount; ++i)
		{
			dotArr[i].x = rnd(0.0f, 1.0f);// (rand() % width)*wcoef;
			dotArr[i].y = rnd(0.0f, 1.0f);
		}


		vec4 color;
		for (uint32 x = 0; x < width; ++x)
		{
			for (uint32 y = 0; y < height; ++y)
			{
				float32 mindist = 2.0f;


				for (int i = 0; i < int32(paramDotsCount); ++i)
				{
					float32 absx = fabs(float32(x)*wcoef - dotArr[i].x);
					float32 absy = fabs(float32(y)*hcoef - dotArr[i].y);
					if (absx > 1.0f / 2) absx = 1.0f - absx;
					if (absy > 1.0f / 2) absy = 1.0f - absy;
					float32 dist = sqrtf(absx*absx + absy*absy);
					if (dist < mindist) mindist = dist;
				}


				color.x = (1.0f - mindist)*1.0f;
				color.y = (1.0f - mindist)*1.0f;
				color.z = (1.0f - mindist)*1.0f;
				color.w = (1.0f - mindist)*1.0f;

				texture->SetPixel(uvec2(x, y), color);
			}
		}
	}
	panelFieldImage->SetImage(texture);
	((OutputData*)buttonOutput->GetUserData())->data = texture;
	buttonOutput->RefreshObservers();
}
#pragma endregion
#pragma endregion
#pragma endregion
#pragma region Filter
#pragma region Correction
#pragma region Grayscale
TexProject::Tools::Filter::Correction::Grayscale::Grayscale(ToolSet* toolSet_):
	Tool(toolSet_)
{
	panelFieldTitle->SetText("Grayscale Filter");
	buttonInput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonInput->SetRecipient();
		buttonInput->SetUserData(this);
		buttonInput->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Filter::Correction::Grayscale*)item->GetUserData())->Refresh();
			}
		);
		buttonInput->SetAction
		(
			GUI::Item::ActionType::Check,
			[](GUI::Item* item)
			{
				if(item->GetBase() == GUI::Buttons::Connector::checkConnector->GetBase())
				{
					GUI::Buttons::Connector::checkValidate = false;
				}
			}
		);
		buttonInput->DisableDragging();
		buttonInput->SetSize(vec2(8.0f));
		buttonInput->SetPos(vec2(4.0f,(panelFieldBase->GetSize().y - buttonInput->GetSize().y)*0.5f));
		buttonInput->direction = vec2(-100.0f,0.0f);
	}
	buttonOutput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonOutput->SetUserData
		(
			new OutputData
			{
				OutputData::Type::Texture2D,
				nullptr
			},
			true
		);
		buttonOutput->DisableDragging();
		buttonOutput->SetSize(vec2(8.0f));
		buttonOutput->SetPos(vec2(panelFieldBase->GetSize().x - buttonOutput->GetSize().x - 4.0f, (panelFieldBase->GetSize().y - buttonOutput->GetSize().y)*0.5f));
		buttonOutput->direction = vec2(100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				((Tools::Filter::Correction::Grayscale*)item->GetUserData())->Refresh();
			}
		);
	}
}
TexProject::Tools::Filter::Correction::Grayscale::~Grayscale()
{

}
void										TexProject::Tools::Filter::Correction::Grayscale::Refresh()
{
	auto source = GetInput();

	if(source)
	{
		texture->Create(source->GetSize());
		{
			for(uint32 x = 0; x < texture->GetSize().x; ++x)
			for(uint32 y = 0; y < texture->GetSize().y; ++y)
			{
				auto color = source->GetPixel(uvec2(x,y));
				color = vec4(vec3(color.xyz().length() / sqrt(3.0f)),color.w);
				texture->SetPixel(uvec2(x,y),color);
			}
		}
		panelFieldImage->SetImage(texture);
		((OutputData*)buttonOutput->GetUserData())->data = texture;
		buttonOutput->RefreshObservers();
	}
	else
	{
		panelFieldImage->SetImage(nullptr);
		((OutputData*)buttonOutput->GetUserData())->data = nullptr;
		buttonOutput->RefreshObservers();
	}
}
TexProject::Texture::D2*					TexProject::Tools::Filter::Correction::Grayscale::GetInput()
{
	auto t = buttonInput->GetTarget();
	auto d = t ? (OutputData*)t->GetUserData() : nullptr;
	return	d ? (d->type == OutputData::Type::Texture2D) ? (Texture::D2*)d->data : nullptr : nullptr;
}
#pragma endregion
#pragma region Blur
TexProject::Tools::Filter::Correction::Blur::Blur(ToolSet* toolSet_):
	Tool(toolSet_)
{
	panelFieldTitle->SetText("Blur Filter");
	buttonFieldInput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldInput->SetRecipient();
		buttonFieldInput->SetUserData(this);
		buttonFieldInput->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Filter::Correction::Blur*)item->GetUserData())->Refresh();
			}
		);
		buttonFieldInput->DisableDragging();
		buttonFieldInput->SetSize(vec2(8.0f));
		buttonFieldInput->SetPos(vec2(4.0f,(panelFieldBase->GetSize().y - buttonFieldInput->GetSize().y)*0.5f));
		buttonFieldInput->direction = vec2(-100.0f,0.0f);
	}
	buttonFieldOutput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldOutput->SetUserData
		(
			new OutputData
			{
				OutputData::Type::Texture2D,
				nullptr
			},
			true
		);
		buttonFieldOutput->DisableDragging();
		buttonFieldOutput->SetSize(vec2(8.0f));
		buttonFieldOutput->SetPos(vec2(panelFieldBase->GetSize().x - buttonFieldOutput->GetSize().x - 4.0f,(panelFieldBase->GetSize().y - buttonFieldOutput->GetSize().y)*0.5f));
		buttonFieldOutput->direction = vec2(100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				((Tools::Filter::Correction::Blur*)item->GetUserData())->Refresh();
			}
		);
	}
}
TexProject::Tools::Filter::Correction::Blur::~Blur()
{

}
void										TexProject::Tools::Filter::Correction::Blur::FocusInit()
{
	panelConfigBase = (GUI::Panels::Default*)toolSet->panelConfig->AddPanel(GUI::PanelTypes::Default);
	{
		panelConfigBase->SetColor(vec4(vec3(0.16f),1));
		panelConfigBase->SetSize(vec2(toolSet->panelConfig->GetSize().x - 8.0f,400.0f));
		panelConfigBase->SetPos(vec2(4.0f,toolSet->panelConfig->GetSize().y - panelConfigBase->GetSize().y - 4.0f));
	}
	panelConfigTitle = (GUI::Panels::Text*)panelConfigBase->AddPanel(GUI::PanelTypes::Text);
	{
		panelConfigTitle->SetText("Blur");
		panelConfigTitle->SetSize(vec2(160.0f,20.0f));
		panelConfigTitle->SetPos(vec2((panelConfigBase->GetSize().x - panelConfigTitle->GetSize().x)*0.5f,panelConfigBase->GetSize().y - panelConfigTitle->GetSize().y));
	}
	panelConfigSizer = (GUI::Panels::Default*)CreateFloatSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigSizer);
		panelConfigSizer->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 1));
		auto data = (SizerFloatData*)panelConfigSizer->GetUserData();
		data->val = float32(paramRadius);
		data->minVal = 1.0f;
		data->maxVal = 100.0f;
	}
}
void										TexProject::Tools::Filter::Correction::Blur::Refresh()
{
	auto source = GetInput();

	if(panelConfigBase)
	{
		paramRadius = float32(((SizerFloatData*)panelConfigSizer->GetUserData())->val);
	}

	if(source)
	{
		texture->Create(source->GetSize());
		{
			for(int32 x = 0; x < int32(texture->GetSize().x); ++x)
			for(int32 y = 0; y < int32(texture->GetSize().y); ++y)
			{
				vec4 color = source->GetPixel(uvec2(x,y));
				float32 count = 1.0f;
				for(int32 tx = -int32(paramRadius); tx < int32(paramRadius); ++tx)
				for(int32 ty = -int32(paramRadius); ty < int32(paramRadius); ++ty)
				if(x != tx || y != ty)
				{
					float32 d = vec2(float32(tx),float32(ty)).length();
					if(d < paramRadius)
					{
						if(x + tx >= 0 && x + tx < int32(source->GetSize().x) && y + ty >= 0 && y + ty < int32(source->GetSize().y))
						{
							float32 t = 1.0f;// / float32(d);
							color += source->GetPixel(uvec2(x + tx,y + ty)) * t;
							count += t;
						}
						/*
						if(x + tx < int32(source->GetSize().x))
						{
							float32 t = 1.0f / float32(d);
							color += source->GetPixel(uvec2(x + tx,y)) * t;
							count += t;
						}
						if(x - tx >= 0)
						{
							float32 t = 1.0f / float32(d);
							color += source->GetPixel(uvec2(x - tx,y)) * t;
							count += t;
						}
						if(y + ty < int32(source->GetSize().y))
						{
							float32 t = 1.0f / float32(d);
							color += source->GetPixel(uvec2(x,y + ty)) * t;
							count += t;
						}
						if(y - ty >= 0)
						{
							float32 t = 1.0f / float32(d);
							color += source->GetPixel(uvec2(x,y - ty)) * t;
							count += t;
						}
						*/
					}
				}

				color /= count;
				texture->SetPixel(uvec2(x,y),color);
			}
		}
		panelFieldImage->SetImage(texture);
		((OutputData*)buttonFieldOutput->GetUserData())->data = texture;
		buttonFieldOutput->RefreshObservers();
	}
	else
	{
		panelFieldImage->SetImage(nullptr);
		((OutputData*)buttonFieldOutput->GetUserData())->data = nullptr;
		buttonFieldOutput->RefreshObservers();
	}
}
TexProject::Texture::D2*					TexProject::Tools::Filter::Correction::Blur::GetInput()
{
	auto t = buttonFieldInput->GetTarget();
	auto d = t ? (OutputData*)t->GetUserData() : nullptr;
	return	d ? (d->type == OutputData::Type::Texture2D) ? (Texture::D2*)d->data : nullptr : nullptr;
}
#pragma endregion
#pragma region Function
TexProject::Tools::Filter::Correction::Function::Function(ToolSet* toolSet_):
	Tool(toolSet_)
{
	panelFieldTitle->SetText("Function");
	buttonFieldInput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldInput->SetRecipient();
		buttonFieldInput->SetUserData(this);
		buttonFieldInput->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Filter::Correction::Function*)item->GetUserData())->Refresh();
			}
		);
		buttonFieldInput->DisableDragging();
		buttonFieldInput->SetSize(vec2(8.0f));
		buttonFieldInput->SetPos(vec2(4.0f,(panelFieldBase->GetSize().y - buttonFieldInput->GetSize().y)*0.5f));
		buttonFieldInput->direction = vec2(-100.0f,0.0f);
	}
	buttonFieldOutput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldOutput->SetUserData
		(
			new OutputData
			{
				OutputData::Type::Texture2D,
				nullptr
			},
			true
		);
		buttonFieldOutput->DisableDragging();
		buttonFieldOutput->SetSize(vec2(8.0f));
		buttonFieldOutput->SetPos(vec2(panelFieldBase->GetSize().x - buttonFieldOutput->GetSize().x - 4.0f,(panelFieldBase->GetSize().y - buttonFieldOutput->GetSize().y)*0.5f));
		buttonFieldOutput->direction = vec2(100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				((Tools::Filter::Correction::Function*)item->GetUserData())->Refresh();
			}
		);
	}
}
TexProject::Tools::Filter::Correction::Function::~Function()
{

}
void										TexProject::Tools::Filter::Correction::Function::FocusInit()
{
	panelConfigBase = (GUI::Panels::Default*)toolSet->panelConfig->AddPanel(GUI::PanelTypes::Default);
	{
		panelConfigBase->SetColor(vec4(vec3(0.16f),1));
		panelConfigBase->SetSize(vec2(toolSet->panelConfig->GetSize().x - 8.0f,400.0f));
		panelConfigBase->SetPos(vec2(4.0f,toolSet->panelConfig->GetSize().y - panelConfigBase->GetSize().y - 4.0f));
	}
	panelConfigTitle = (GUI::Panels::Text*)panelConfigBase->AddPanel(GUI::PanelTypes::Text);
	{
		panelConfigTitle->SetText("Function");
		panelConfigTitle->SetSize(vec2(160.0f,20.0f));
		panelConfigTitle->SetPos(vec2((panelConfigBase->GetSize().x - panelConfigTitle->GetSize().x)*0.5f,panelConfigBase->GetSize().y - panelConfigTitle->GetSize().y));
	}
	panelConfigAdd = (GUI::Panels::Default*)CreateFloatSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigAdd);
		panelConfigAdd->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 1));
		auto data = (SizerFloatData*)panelConfigAdd->GetUserData();
		data->val = float32(paramAdd);
		data->minVal = -1.0f;
		data->maxVal = 1.0f;
	}
	panelConfigMul = (GUI::Panels::Default*)CreateFloatSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigMul);
		panelConfigMul->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 2));
		auto data = (SizerFloatData*)panelConfigMul->GetUserData();
		data->val = float32(paramMul);
		data->minVal = -2.0f;
		data->maxVal = 2.0f;
	}
	panelConfigPow = (GUI::Panels::Default*)CreateFloatSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigPow);
		panelConfigPow->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 3));
		auto data = (SizerFloatData*)panelConfigPow->GetUserData();
		data->val = float32(paramPow);
		data->minVal = -1.0f;
		data->maxVal = 10.0f;
	}
}
void										TexProject::Tools::Filter::Correction::Function::Refresh()
{
	auto source = GetInput();

	if(panelConfigBase)
	{
		paramAdd = float32(((SizerFloatData*)panelConfigAdd->GetUserData())->val);
		paramMul = float32(((SizerFloatData*)panelConfigMul->GetUserData())->val);
		paramPow = float32(((SizerFloatData*)panelConfigPow->GetUserData())->val);
	}

	if(source)
	{
		texture->Create(source->GetSize());
		{
			for(int32 x = 0; x < int32(texture->GetSize().x); ++x)
			for(int32 y = 0; y < int32(texture->GetSize().y); ++y)
			{
				vec4 color = source->GetPixel(uvec2(x,y));
				color = paramAdd + paramMul * vec4
				(
					sign(color.x) * pow(abs(color.x),paramPow),
					sign(color.y) * pow(abs(color.y),paramPow),
					sign(color.z) * pow(abs(color.z),paramPow),
					sign(color.w) * pow(abs(color.w),paramPow)
				);
				texture->SetPixel(uvec2(x,y),color);
			}
		}
		panelFieldImage->SetImage(texture);
		((OutputData*)buttonFieldOutput->GetUserData())->data = texture;
		buttonFieldOutput->RefreshObservers();
	}
	else
	{
		panelFieldImage->SetImage(nullptr);
		((OutputData*)buttonFieldOutput->GetUserData())->data = nullptr;
		buttonFieldOutput->RefreshObservers();
	}
}
TexProject::Texture::D2*					TexProject::Tools::Filter::Correction::Function::GetInput()
{
	auto t = buttonFieldInput->GetTarget();
	auto d = t ? (OutputData*)t->GetUserData() : nullptr;
	return	d ? (d->type == OutputData::Type::Texture2D) ? (Texture::D2*)d->data : nullptr : nullptr;
}
#pragma endregion
#pragma region Mix
TexProject::Tools::Filter::Correction::Mix::Mix(ToolSet* toolSet_):
	Tool(toolSet_)
{
	panelFieldTitle->SetText("Mix");
	buttonFieldInputA = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldInputA->SetRecipient();
		buttonFieldInputA->SetUserData(this);
		buttonFieldInputA->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Filter::Correction::Mix*)item->GetUserData())->Refresh();
			}
		);
		buttonFieldInputA->DisableDragging();
		buttonFieldInputA->SetSize(vec2(8.0f));
		buttonFieldInputA->SetPos(vec2(4.0f,(panelFieldBase->GetSize().y - buttonFieldInputA->GetSize().y)*0.5f + 16.0f));
		buttonFieldInputA->direction = vec2(-100.0f,0.0f);
	}
	buttonFieldInputB = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldInputB->SetRecipient();
		buttonFieldInputB->SetUserData(this);
		buttonFieldInputB->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Filter::Correction::Mix*)item->GetUserData())->Refresh();
			}
		);
		buttonFieldInputB->DisableDragging();
		buttonFieldInputB->SetSize(vec2(8.0f));
		buttonFieldInputB->SetPos(vec2(4.0f,(panelFieldBase->GetSize().y - buttonFieldInputB->GetSize().y)*0.5f + 0.0f));
		buttonFieldInputB->direction = vec2(-100.0f,0.0f);
	}
	buttonFieldInputMix = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldInputMix->SetRecipient();
		buttonFieldInputMix->SetUserData(this);
		buttonFieldInputMix->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Filter::Correction::Mix*)item->GetUserData())->Refresh();
			}
		);
		buttonFieldInputMix->DisableDragging();
		buttonFieldInputMix->SetSize(vec2(8.0f));
		buttonFieldInputMix->SetPos(vec2(4.0f,(panelFieldBase->GetSize().y - buttonFieldInputMix->GetSize().y)*0.5f - 16.0f));
		buttonFieldInputMix->direction = vec2(-100.0f,0.0f);
	}

	buttonFieldOutput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldOutput->SetUserData
		(
			new OutputData
			{
				OutputData::Type::Texture2D,
				nullptr
			},
			true
		);
		buttonFieldOutput->DisableDragging();
		buttonFieldOutput->SetSize(vec2(8.0f));
		buttonFieldOutput->SetPos(vec2(panelFieldBase->GetSize().x - buttonFieldOutput->GetSize().x - 4.0f,(panelFieldBase->GetSize().y - buttonFieldOutput->GetSize().y)*0.5f));
		buttonFieldOutput->direction = vec2(100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				((Tools::Filter::Correction::Mix*)item->GetUserData())->Refresh();
			}
		);
	}
}
TexProject::Tools::Filter::Correction::Mix::~Mix()
{

}
void										TexProject::Tools::Filter::Correction::Mix::FocusInit()
{
	panelConfigBase = (GUI::Panels::Default*)toolSet->panelConfig->AddPanel(GUI::PanelTypes::Default);
	{
		panelConfigBase->SetColor(vec4(vec3(0.16f),1));
		panelConfigBase->SetSize(vec2(toolSet->panelConfig->GetSize().x - 8.0f,400.0f));
		panelConfigBase->SetPos(vec2(4.0f,toolSet->panelConfig->GetSize().y - panelConfigBase->GetSize().y - 4.0f));
	}
	panelConfigTitle = (GUI::Panels::Text*)panelConfigBase->AddPanel(GUI::PanelTypes::Text);
	{
		panelConfigTitle->SetText("Mix");
		panelConfigTitle->SetSize(vec2(160.0f,20.0f));
		panelConfigTitle->SetPos(vec2((panelConfigBase->GetSize().x - panelConfigTitle->GetSize().x)*0.5f,panelConfigBase->GetSize().y - panelConfigTitle->GetSize().y));
	}
}
void										TexProject::Tools::Filter::Correction::Mix::Refresh()
{
	auto sourceA = GetInputA();
	auto sourceB = GetInputB();
	auto sourceMix = GetInputMix();

	if(sourceA && sourceB && sourceMix && sourceA->GetSize() == sourceB->GetSize() && sourceB->GetSize() == sourceMix->GetSize())
	{
		texture->Create(sourceA->GetSize());
		{
			for(int32 x = 0; x < int32(texture->GetSize().x); ++x)
			for(int32 y = 0; y < int32(texture->GetSize().y); ++y)
			{
				vec4 colorA = sourceA->GetPixel(uvec2(x,y));
				vec4 colorB = sourceB->GetPixel(uvec2(x,y));
				vec4 colorMix = sourceMix->GetPixel(uvec2(x,y));
				vec4 color = bezier(colorA,colorB,colorMix);
				texture->SetPixel(uvec2(x,y),color);
			}
		}
		panelFieldImage->SetImage(texture);
		((OutputData*)buttonFieldOutput->GetUserData())->data = texture;
		buttonFieldOutput->RefreshObservers();
	}
	else
	{
		panelFieldImage->SetImage(nullptr);
		((OutputData*)buttonFieldOutput->GetUserData())->data = nullptr;
		buttonFieldOutput->RefreshObservers();
	}
}
TexProject::Texture::D2*					TexProject::Tools::Filter::Correction::Mix::GetInputA()
{
	auto t = buttonFieldInputA->GetTarget();
	auto d = t ? (OutputData*)t->GetUserData() : nullptr;
	return	d ? (d->type == OutputData::Type::Texture2D) ? (Texture::D2*)d->data : nullptr : nullptr;
}
TexProject::Texture::D2*					TexProject::Tools::Filter::Correction::Mix::GetInputB()
{
	auto t = buttonFieldInputB->GetTarget();
	auto d = t ? (OutputData*)t->GetUserData() : nullptr;
	return	d ? (d->type == OutputData::Type::Texture2D) ? (Texture::D2*)d->data : nullptr : nullptr;
}
TexProject::Texture::D2*					TexProject::Tools::Filter::Correction::Mix::GetInputMix()
{
	auto t = buttonFieldInputMix->GetTarget();
	auto d = t ? (OutputData*)t->GetUserData() : nullptr;
	return	d ? (d->type == OutputData::Type::Texture2D) ? (Texture::D2*)d->data : nullptr : nullptr;
}
#pragma endregion
#pragma endregion
#pragma region Physics
#pragma region HeightToNormal
TexProject::Tools::Filter::Physics::HeightToNormal::HeightToNormal(ToolSet* toolSet_):
Tool(toolSet_)
{
	panelFieldTitle->SetText("Height To Normal");
	buttonFieldInput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldInput->SetRecipient();
		buttonFieldInput->SetUserData(this);
		buttonFieldInput->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Filter::Physics::HeightToNormal*)item->GetUserData())->Refresh();
			}
		);
		buttonFieldInput->DisableDragging();
		buttonFieldInput->SetSize(vec2(8.0f));
		buttonFieldInput->SetPos(vec2(4.0f,(panelFieldBase->GetSize().y - buttonFieldInput->GetSize().y)*0.5f));
		buttonFieldInput->direction = vec2(-100.0f,0.0f);
	}
	buttonFieldOutput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldOutput->SetUserData
		(
			new OutputData
			{
				OutputData::Type::Texture2D,
				nullptr
			},
			true
		);
		buttonFieldOutput->DisableDragging();
		buttonFieldOutput->SetSize(vec2(8.0f));
		buttonFieldOutput->SetPos(vec2(panelFieldBase->GetSize().x - buttonFieldOutput->GetSize().x - 4.0f,(panelFieldBase->GetSize().y - buttonFieldOutput->GetSize().y)*0.5f));
		buttonFieldOutput->direction = vec2(100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
			(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
		{
			((Tools::Filter::Physics::HeightToNormal*)item->GetUserData())->Refresh();
		}
		);
	}
}
TexProject::Tools::Filter::Physics::HeightToNormal::~HeightToNormal()
{

}
void										TexProject::Tools::Filter::Physics::HeightToNormal::FocusInit()
{
	panelConfigBase = (GUI::Panels::Default*)toolSet->panelConfig->AddPanel(GUI::PanelTypes::Default);
	{
		panelConfigBase->SetColor(vec4(vec3(0.16f),1));
		panelConfigBase->SetSize(vec2(toolSet->panelConfig->GetSize().x - 8.0f,400.0f));
		panelConfigBase->SetPos(vec2(4.0f,toolSet->panelConfig->GetSize().y - panelConfigBase->GetSize().y - 4.0f));
	}
	panelConfigTitle = (GUI::Panels::Text*)panelConfigBase->AddPanel(GUI::PanelTypes::Text);
	{
		panelConfigTitle->SetText("Height To Normal");
		panelConfigTitle->SetSize(vec2(160.0f,20.0f));
		panelConfigTitle->SetPos(vec2((panelConfigBase->GetSize().x - panelConfigTitle->GetSize().x)*0.5f,panelConfigBase->GetSize().y - panelConfigTitle->GetSize().y));
	}
	panelConfigSizer = (GUI::Panels::Default*)CreateSizer(panelConfigBase->GetGUI());
	{
		panelConfigBase->AttachItem(panelConfigSizer);
		panelConfigSizer->SetPos(vec2(4.0f,panelConfigBase->GetSize().y - 20.0f - 32.0f * 1));
		auto data = (SizerData*)panelConfigSizer->GetUserData();
		data->val = int32(paramScaleFactor);
		data->minVal = 1;
		data->maxVal = 255;
	}
}
void										TexProject::Tools::Filter::Physics::HeightToNormal::Refresh()
{
	auto source = GetInput();

	if(panelConfigBase)
	{
		paramScaleFactor = float32(((SizerData*)panelConfigSizer->GetUserData())->val);
	}

	if(source)
	{
		texture->Create(source->GetSize());
		{
			for(uint32 i = 0; i < source->GetSize().x; ++i)
			for(uint32 j = 0; j < source->GetSize().y; ++j)
			{
				vec3 a;
				if(i != 0)
				{
					if(i != source->GetSize().x - 1)
						a.x = source->GetPixel(uvec2(i - 1,j)).x - source->GetPixel(uvec2(i + 1,j)).x;
					else
						a.x = source->GetPixel(uvec2(i - 1,j)).x - source->GetPixel(uvec2(i,j)).x;
				}
				else
					a.x = source->GetPixel(uvec2(i,j)).x - source->GetPixel(uvec2(i + 1,j)).x;

				if(j != 0)
				{
					if(j != source->GetSize().y - 1)
						a.y = source->GetPixel(uvec2(i,j - 1)).x - source->GetPixel(uvec2(i,j + 1)).x;
					else
						a.y = source->GetPixel(uvec2(i,j - 1)).x - source->GetPixel(uvec2(i,j)).x;
				}
				else
					a.y = source->GetPixel(uvec2(i,j)).x - source->GetPixel(uvec2(i,j + 1)).x;
				a.z = 2.0f / paramScaleFactor;
				a.normalize();
				a += vec3(1.0f);
				a *= vec3(0.5f);
				texture->SetPixel(uvec2(i,j),vec4(a,1.0f));
			}
		}
		panelFieldImage->SetImage(texture);
		((OutputData*)buttonFieldOutput->GetUserData())->data = texture;
		buttonFieldOutput->RefreshObservers();
	}
	else
	{
		panelFieldImage->SetImage(nullptr);
		((OutputData*)buttonFieldOutput->GetUserData())->data = nullptr;
		buttonFieldOutput->RefreshObservers();
	}
}
TexProject::Texture::D2*					TexProject::Tools::Filter::Physics::HeightToNormal::GetInput()
{
	auto t = buttonFieldInput->GetTarget();
	auto d = t ? (OutputData*)t->GetUserData() : nullptr;
	return	d ? (d->type == OutputData::Type::Texture2D) ? (Texture::D2*)d->data : nullptr : nullptr;
}
#pragma endregion
#pragma region NormalsToSlopeFactor
TexProject::Tools::Filter::Physics::NormalsToSlopeFactor::NormalsToSlopeFactor(ToolSet* toolSet_):
	Tool(toolSet_)
{
	panelFieldTitle->SetText("Slope Factor");
	buttonFieldInput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldInput->SetRecipient();
		buttonFieldInput->SetUserData(this);
		buttonFieldInput->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Filter::Physics::NormalsToSlopeFactor*)item->GetUserData())->Refresh();
			}
		);
		buttonFieldInput->DisableDragging();
		buttonFieldInput->SetSize(vec2(8.0f));
		buttonFieldInput->SetPos(vec2(4.0f,(panelFieldBase->GetSize().y - buttonFieldInput->GetSize().y)*0.5f));
		buttonFieldInput->direction = vec2(-100.0f,0.0f);
	}
	buttonFieldOutput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldOutput->SetUserData
		(
			new OutputData
			{
				OutputData::Type::Texture2D,
				nullptr
			},
			true
		);
		buttonFieldOutput->DisableDragging();
		buttonFieldOutput->SetSize(vec2(8.0f));
		buttonFieldOutput->SetPos(vec2(panelFieldBase->GetSize().x - buttonFieldOutput->GetSize().x - 4.0f,(panelFieldBase->GetSize().y - buttonFieldOutput->GetSize().y)*0.5f));
		buttonFieldOutput->direction = vec2(100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				((Tools::Filter::Physics::NormalsToSlopeFactor*)item->GetUserData())->Refresh();
			}
		);
	}
}
TexProject::Tools::Filter::Physics::NormalsToSlopeFactor::~NormalsToSlopeFactor()
{

}
void										TexProject::Tools::Filter::Physics::NormalsToSlopeFactor::Refresh()
{
	auto source = GetInput();

	if(source)
	{
		texture->Create(source->GetSize());
		{
			for(uint32 x = 0; x < source->GetSize().x; ++x)
			for(uint32 y = 0; y < source->GetSize().y; ++y)
			{
				vec3 normal = normalize(source->GetPixel(uvec2(x,y)).xyz() * 2.0f - 1.0f);
				float32 slope = dot(normal,vec3(0.0f,0.0f,1.0f));
				slope = 1.0f - pow(abs(acosDg(slope)/90.0f),2.0f);
				texture->SetPixel(uvec2(x,y),vec4(vec3(slope),1.0f));
			}
		}
		panelFieldImage->SetImage(texture);
		((OutputData*)buttonFieldOutput->GetUserData())->data = texture;
		buttonFieldOutput->RefreshObservers();
	}
	else
	{
		panelFieldImage->SetImage(nullptr);
		((OutputData*)buttonFieldOutput->GetUserData())->data = nullptr;
		buttonFieldOutput->RefreshObservers();
	}
}
TexProject::Texture::D2*					TexProject::Tools::Filter::Physics::NormalsToSlopeFactor::GetInput()
{
	auto t = buttonFieldInput->GetTarget();
	auto d = t ? (OutputData*)t->GetUserData() : nullptr;
	return	d ? (d->type == OutputData::Type::Texture2D) ? (Texture::D2*)d->data : nullptr : nullptr;
}
#pragma endregion
#pragma endregion
#pragma endregion
#pragma region Viewer
#pragma region Simple
void										TexProject::Tools::Viewer::Simple::FuncWindowInit(Window* window)
{
	auto tool = (Tools::Viewer::Simple*)window->GetUserData();

	tool->mesh->CreateBox(vec3(1.0f),vec3(1.0f),uvec3(1));

	tool->oglShader = new OpenGL::Shader(window);
	{
		tool->oglShader->Load(GetEXEPath() + "/Media/Shaders/GLSL/3D/Material/Basic/1.","vs","","","","ps");
		tool->oglShader->Use();
		tool->oglShader->SetInt("Texture",0);
	}

	tool->oglMesh = new OpenGL::Mesh(window);
	{
		tool->oglMesh->Create(tool->mesh,tool->oglShader);
	}

	tool->oglTexture = new OpenGL::Texture(window);
	{
		*tool->oglTexture = *tool->texture;
	}
}
void										TexProject::Tools::Viewer::Simple::FuncWindowFree(Window* window)
{
	auto tool = (Tools::Viewer::Simple*)window->GetUserData();

	if(tool->oglTexture) { delete tool->oglTexture; tool->oglTexture = nullptr; }
	if(tool->oglMesh) { delete tool->oglMesh; tool->oglMesh = nullptr; }
	if(tool->oglShader) { delete tool->oglShader; tool->oglShader = nullptr; }
}
void										TexProject::Tools::Viewer::Simple::FuncWindowLoop(Window* window)
{
	auto tool = (Tools::Viewer::Simple*)window->GetUserData();

	glViewport(0,0,window->GetSize().x,window->GetSize().y);

	glClearColor(0.16f,0.16f,0.16f,1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);

	tool->mMat.Rotate(vec3(0.0f,1.0f,0.0f));

	tool->vpMat.SetPos(mat3::rotateZXY(vec3(30.0f,0.0,0.0f)) * vec3(0.0,0.0f,-2.0f));
	tool->vpMat.SetAng(vec3(30.0f,0.0,0.0f));
	tool->vpMat.SetPerspective(90.0f,tool->windowRender->GetAspect(),0.1f,100.0f);

	if(tool->oglShader)
	{
		tool->oglShader->Use();
		{
			tool->oglShader->SetMat4("ModelMatrix",tool->mMat.GetMMat());
			tool->oglShader->SetMat4("ModelViewProjectionMatrix",tool->mMat.GetMMat() * tool->vpMat.GetVPMat());
		}

		tool->oglTexture->Use(0);

		tool->oglMesh->DrawIndex();
	}
}
TexProject::Tools::Viewer::Simple::Simple(ToolSet* toolSet_):
	Tool(toolSet_),
	vpMat(vec3(0.0f,0.0f,-2.0f),vec3(0.0f),Helper::PParams::Perspective(80.0f,1.0f,0.1f,1000.0f)),
	mMat(vec3(0.0f),vec3(0.0f),vec3(1.0f))
{
	panelFieldTitle->SetText("Viewer");
	buttonInput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonInput->SetRecipient();
		buttonInput->SetUserData(this);
		buttonInput->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Viewer::Simple*)item->GetUserData())->Refresh();
			}
		);
		buttonInput->DisableDragging();
		buttonInput->SetSize(vec2(8.0f));
		buttonInput->SetPos(vec2(4.0f,(panelFieldBase->GetSize().y - buttonInput->GetSize().y)*0.5f));
		buttonInput->direction = vec2(-100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				((Tools::Viewer::Simple*)item->GetUserData())->Refresh();
			}
		);
	}
	windowRender->SetUserData(this);
	{
		windowRender->EnableVSync();
		windowRender->SetFunc(Window::FuncType::Init,FuncWindowInit);
		windowRender->SetFunc(Window::FuncType::Free,FuncWindowFree);
		windowRender->SetFunc(Window::FuncType::Loop,FuncWindowLoop);
	}
}
TexProject::Tools::Viewer::Simple::~Simple()
{
	if(windowRender) delete windowRender;
}
void										TexProject::Tools::Viewer::Simple::Refresh()
{
	auto source = GetInput();

	if(source)
	{
		*texture = *source;
	}

	panelFieldImage->SetImage(nullptr);

	if(windowRender)
	{
		windowRender->Create();
		windowRender->SetSize(uvec2(512));
		windowRender->SetRenderContext(RenderContext::Type::OpenGL);

		auto tmpRC = new OpenGL::RenderContext(windowRender);
		{
			if(tmpRC->Use())
			{
				auto tmpGeometry = new Geometry::Mesh();
				{
					//tmpGeometry->CreateBox(vec3(1.0f),vec3(1.0f),uvec3(1));
					tmpGeometry->CreateSphere(0.5f,vec2(1.0f),uvec2(32));
				}
				auto tmpShader = new OpenGL::Shader(tmpRC);
				{
					tmpShader->Load(GetEXEPath() + "/Media/Shaders/GLSL/3D/Material/Flat/1.","vs","","","","ps");
					tmpShader->Use();
					tmpShader->SetInt("Texture",0);
				}
				auto tmpInTexture = (OpenGL::Texture*)nullptr;
				{
					if(auto input = GetInput())
					{
						tmpInTexture = new OpenGL::Texture(tmpRC);
						*tmpInTexture = *input;
					}
				}
				auto tmpOutTexture = new OpenGL::Texture(tmpRC);
				{
					tmpOutTexture->Create
					(
						OpenGL::Texture::Type::D2,
						OpenGL::Texture::IFormat::RGB8,
						OpenGL::Texture::Format::RGB,
						OpenGL::Texture::Component::UInt8,
						OpenGL::Texture::Wrap::Clamp,
						OpenGL::Texture::Filter::Off,
						uvec3(128),
						nullptr
					);
				}
				auto tmpDepthTexture = new OpenGL::Texture(tmpRC);
				{
					tmpDepthTexture->Create
					(
						OpenGL::Texture::Type::D2,
						OpenGL::Texture::IFormat::Depth16,
						OpenGL::Texture::Format::Depth,
						OpenGL::Texture::Component::UInt16,
						OpenGL::Texture::Wrap::Clamp,
						OpenGL::Texture::Filter::Off,
						uvec3(128),
						nullptr
					);
				}
				auto tmpFBuffer = new OpenGL::Buffer::Frame(tmpRC);
				{
					tmpFBuffer->Create
					(
						{
							tmpOutTexture
						},
						tmpDepthTexture,
						nullptr
					);
				}
				auto tmpMesh = new OpenGL::Mesh(tmpRC);
				{
					tmpMesh->Create(tmpGeometry,tmpShader);
				}
				tmpFBuffer->Use();
				{
					glClearColor(1.0f,0.5f,0.16f,1);
					glClearDepth(1.0f);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LESS);
					glDisable(GL_BLEND);
					glDisable(GL_CULL_FACE);

					if(tmpInTexture) tmpInTexture->Use(0);

					tmpShader->Use();
					{
						tmpShader->SetMat4("ModelViewProjectionMatrix",mat4::rotateYXZ(vec3(30.0f,-45.0f,0.0f)) * mat4::orthogonal(-1.0f,1.0f,-1.0f,1.0f,-10.0f,10.0f));
					}

					tmpMesh->DrawIndex();

					glFlush();

					tmpFBuffer->Unuse();
				}
				*texturePreview = *tmpOutTexture;
				delete tmpFBuffer;
				delete tmpOutTexture;
				delete tmpMesh;
				delete tmpInTexture;
				delete tmpShader;
				delete tmpGeometry;

				panelFieldImage->SetImage(texturePreview);
			}
			delete tmpRC;
		}
	}
}
TexProject::Texture::D2*					TexProject::Tools::Viewer::Simple::GetInput()
{
	auto t = buttonInput->GetTarget();
	auto d = t ? (OutputData*)t->GetUserData() : nullptr;
	return	d ? (d->type == OutputData::Type::Texture2D) ? (Texture::D2*)d->data : nullptr : nullptr;
}
#pragma endregion
#pragma region BumpMapping
void										TexProject::Tools::Viewer::BumpMapping::FuncWindowInit(Window* window)
{
	auto tool = (Tools::Viewer::BumpMapping*)window->GetUserData();

	tool->mesh->CreateBox(vec3(1.0f),vec3(1.0f),uvec3(1));
	//tool->mesh->CreateSphere(0.5f,vec2(1.0f),uvec2(64));

	tool->oglShader = new OpenGL::Shader(window);
	{
		tool->oglShader->Load(GetEXEPath() + "/Media/Shaders/GLSL/3D/Material/Bump Mapping/1.","vs","","","","ps");
		//tool->oglShader->Load("Media/Shaders/GLSL/3D/Material/Bump Mapping/1.","vs","","","","ps");
		tool->oglShader->Use();
		tool->oglShader->SetInt("TextureDiffuse",0);
		tool->oglShader->SetInt("TextureNormals",1);
	}

	tool->oglMesh = new OpenGL::Mesh(window);
	{
		tool->oglMesh->Create(tool->mesh,tool->oglShader);
	}

	tool->oglTextureDiffuse = new OpenGL::Texture(window);
	{
		*tool->oglTextureDiffuse = *tool->textureDiffuse;
	}
	tool->oglTextureNormals = new OpenGL::Texture(window);
	{
		*tool->oglTextureNormals = *tool->textureNormals;
	}
}
void										TexProject::Tools::Viewer::BumpMapping::FuncWindowFree(Window* window)
{
	auto tool = (Tools::Viewer::BumpMapping*)window->GetUserData();

	if(tool->oglTextureDiffuse) { delete tool->oglTextureDiffuse; tool->oglTextureDiffuse = nullptr; }
	if(tool->oglTextureNormals) { delete tool->oglTextureNormals; tool->oglTextureNormals = nullptr; }
	if(tool->oglMesh) { delete tool->oglMesh; tool->oglMesh = nullptr; }
	if(tool->oglShader) { delete tool->oglShader; tool->oglShader = nullptr; }
}
void										TexProject::Tools::Viewer::BumpMapping::FuncWindowLoop(Window* window)
{
	auto tool = (Tools::Viewer::BumpMapping*)window->GetUserData();

	glViewport(0,0,window->GetSize().x,window->GetSize().y);

	glClearColor(0.16f,0.16f,0.16f,1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);

	tool->mMat.Rotate(vec3(0.0f,1.0f,0.0f));

	tool->vpMat.SetPos(mat3::rotateZXY(vec3(30.0f,0.0,0.0f)) * vec3(0.0,0.0f,-2.0f));
	tool->vpMat.SetAng(vec3(30.0f,0.0,0.0f));
	tool->vpMat.SetPerspective(90.0f,tool->windowRender->GetAspect(),0.1f,100.0f);

	if(tool->oglShader)
	{
		tool->oglShader->Use();
		{
			tool->oglShader->SetVec3("lightDir",normalize(vec3(1.0f,-2.0f,1.0f)));
			tool->oglShader->SetMat3("RotateMatrix",tool->mMat.GetRMat());
			tool->oglShader->SetMat4("ModelMatrix",tool->mMat.GetMMat());
			tool->oglShader->SetMat4("ModelViewProjectionMatrix",tool->mMat.GetMMat() * tool->vpMat.GetVPMat());
		}

		tool->oglTextureDiffuse->Use(0);
		tool->oglTextureNormals->Use(1);

		tool->oglMesh->DrawIndex();
	}
}
TexProject::Tools::Viewer::BumpMapping::BumpMapping(ToolSet* toolSet_):
	Tool(toolSet_),
	vpMat(vec3(0.0f,0.0f,-2.0f),vec3(0.0f),Helper::PParams::Perspective(80.0f,1.0f,0.1f,1000.0f)),
	mMat(vec3(0.0f),vec3(0.0f),vec3(1.0f))
{
	panelFieldTitle->SetText("Viewer");
	buttonFieldInputDiffuse = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldInputDiffuse->SetRecipient();
		buttonFieldInputDiffuse->SetUserData(this);
		buttonFieldInputDiffuse->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Viewer::BumpMapping*)item->GetUserData())->Refresh();
			}
		);
		buttonFieldInputDiffuse->DisableDragging();
		buttonFieldInputDiffuse->SetSize(vec2(8.0f));
		buttonFieldInputDiffuse->SetPos(vec2(4.0f,(panelFieldBase->GetSize().y - buttonFieldInputDiffuse->GetSize().y)*0.5f + 8.0f));
		buttonFieldInputDiffuse->direction = vec2(-100.0f,0.0f);
	}
	buttonFieldInputNormals = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonFieldInputNormals->SetRecipient();
		buttonFieldInputNormals->SetUserData(this);
		buttonFieldInputNormals->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Viewer::BumpMapping*)item->GetUserData())->Refresh();
			}
		);
		buttonFieldInputNormals->DisableDragging();
		buttonFieldInputNormals->SetSize(vec2(8.0f));
		buttonFieldInputNormals->SetPos(vec2(4.0f,(panelFieldBase->GetSize().y - buttonFieldInputNormals->GetSize().y)*0.5f - 8.0f));
		buttonFieldInputNormals->direction = vec2(-100.0f,0.0f);
	}
	buttonFieldRefresh->SetUserData(this);
	{
		buttonFieldRefresh->SetAction
		(
			GUI::Item::ActionType::Click,
			[](GUI::Item* item)
			{
				((Tools::Viewer::BumpMapping*)item->GetUserData())->Refresh();
			}
		);
	}
	windowRender->SetUserData(this);
	{
		windowRender->EnableVSync();
		windowRender->SetFunc(Window::FuncType::Init,FuncWindowInit);
		windowRender->SetFunc(Window::FuncType::Free,FuncWindowFree);
		windowRender->SetFunc(Window::FuncType::Loop,FuncWindowLoop);
	}
}
TexProject::Tools::Viewer::BumpMapping::~BumpMapping()
{
	if(windowRender) delete windowRender;
}
void										TexProject::Tools::Viewer::BumpMapping::Refresh()
{
	if(auto sourceDiffuse = GetInputDiffuse())
	{
		*textureDiffuse = *sourceDiffuse;
	}
	if(auto sourceNormals = GetInputNormals())
	{
		*textureNormals = *sourceNormals;
	}

	panelFieldImage->SetImage(nullptr);

	if(windowRender)
	{
		windowRender->Create();
		windowRender->SetSize(uvec2(512));
		windowRender->SetRenderContext(RenderContext::Type::OpenGL);

		auto tmpRC = new OpenGL::RenderContext(windowRender);
		{
			if(tmpRC->Use())
			{
				auto tmpGeometry = new Geometry::Mesh();
				{
					//tmpGeometry->CreateBox(vec3(1.0f),vec3(1.0f),uvec3(1));
					tmpGeometry->CreateSphere(0.5f,vec2(1.0f),uvec2(32));
				}
				auto tmpShader = new OpenGL::Shader(tmpRC);
				{
					tmpShader->Load(GetEXEPath() + "/Media/Shaders/GLSL/3D/Material/Bump Mapping/1.","vs","","","","ps");
					//tmpShader->Load("Media/Shaders/GLSL/3D/Material/Bump Mapping/1.","vs","","","","ps");
					tmpShader->Use();
					tmpShader->SetInt("TextureDiffuse",0);
					tmpShader->SetInt("TextureNormals",1);
				}
				auto tmpInTextureDiffuse = (OpenGL::Texture*)nullptr;
				{
					if(auto input = GetInputDiffuse())
					{
						tmpInTextureDiffuse = new OpenGL::Texture(tmpRC);
						*tmpInTextureDiffuse = *input;
					}
				}
				auto tmpInTextureNormals = (OpenGL::Texture*)nullptr;
				{
					if(auto input = GetInputNormals())
					{
						tmpInTextureNormals = new OpenGL::Texture(tmpRC);
						*tmpInTextureNormals = *input;
					}
				}
				auto tmpOutTexture = new OpenGL::Texture(tmpRC);
				{
					tmpOutTexture->Create
					(
						OpenGL::Texture::Type::D2,
						OpenGL::Texture::IFormat::RGB8,
						OpenGL::Texture::Format::RGB,
						OpenGL::Texture::Component::UInt8,
						OpenGL::Texture::Wrap::Clamp,
						OpenGL::Texture::Filter::Off,
						uvec3(128),
						nullptr
					);
				}
				auto tmpDepthTexture = new OpenGL::Texture(tmpRC);
				{
					tmpDepthTexture->Create
					(
						OpenGL::Texture::Type::D2,
						OpenGL::Texture::IFormat::Depth16,
						OpenGL::Texture::Format::Depth,
						OpenGL::Texture::Component::UInt16,
						OpenGL::Texture::Wrap::Clamp,
						OpenGL::Texture::Filter::Off,
						uvec3(128),
						nullptr
					);
				}
				auto tmpFBuffer = new OpenGL::Buffer::Frame(tmpRC);
				{
					tmpFBuffer->Create
					(
						{
							tmpOutTexture
						},
						tmpDepthTexture,
						nullptr
					);
				}
				auto tmpMesh = new OpenGL::Mesh(tmpRC);
				{
					tmpMesh->Create(tmpGeometry,tmpShader);
				}
				tmpFBuffer->Use();
				{
					glClearColor(1.0f,0.5f,0.16f,1);
					glClearDepth(1.0f);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LESS);
					glDisable(GL_BLEND);
					glDisable(GL_CULL_FACE);

					if(tmpInTextureDiffuse) tmpInTextureDiffuse->Use(0);
					if(tmpInTextureNormals) tmpInTextureNormals->Use(1);

					tmpShader->Use();
					{
						tmpShader->SetVec3("lightDir",normalize(vec3(0.0f,-2.0f,-1.0f)));
						tmpShader->SetMat3("RotateMatrix",mat3::one());
						tmpShader->SetMat4("ModelMatrix",mat4::one());
						tmpShader->SetMat4("ModelViewProjectionMatrix",mat4::rotateYXZ(vec3(30.0f,-45.0f,0.0f)) * mat4::orthogonal(-1.0f,1.0f,-1.0f,1.0f,-10.0f,10.0f));
					}

					tmpMesh->DrawIndex();

					glFlush();

					tmpFBuffer->Unuse();
				}
				*texturePreview = *tmpOutTexture;
				delete tmpFBuffer;
				delete tmpOutTexture;
				delete tmpMesh;
				delete tmpInTextureDiffuse;
				delete tmpInTextureNormals;
				delete tmpShader;
				delete tmpGeometry;

				panelFieldImage->SetImage(texturePreview);
			}
			delete tmpRC;
		}
	}
}
TexProject::Texture::D2*					TexProject::Tools::Viewer::BumpMapping::GetInputDiffuse()
{
	auto t = buttonFieldInputDiffuse->GetTarget();
	auto d = t ? (OutputData*)t->GetUserData() : nullptr;
	return	d ? (d->type == OutputData::Type::Texture2D) ? (Texture::D2*)d->data : nullptr : nullptr;
}
TexProject::Texture::D2*					TexProject::Tools::Viewer::BumpMapping::GetInputNormals()
{
	auto t = buttonFieldInputNormals->GetTarget();
	auto d = t ? (OutputData*)t->GetUserData() : nullptr;
	return	d ? (d->type == OutputData::Type::Texture2D) ? (Texture::D2*)d->data : nullptr : nullptr;
}
#pragma endregion

#pragma endregion
#pragma endregion

































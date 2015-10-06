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
		panelConfig->SetSize(vec2(128.0f,float32(window->GetSize().y)));
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
			auto SummonButton = [this](GUI::Item::Action action)
			{
				static uint32 pos = 0;
				auto button = (GUI::Buttons::Default*)panelTools->AddButton(GUI::ButtonTypes::Default);
				{
					button->SetUserData(this);
					button->SetColor(vec4(0,1,0,1));
					button->SetSize(vec2(32.0f));
					button->SetPos(vec2(20.0f - button->GetSize().x*0.5f + 40.0f * pos,(panelTools->GetSize().y - button->GetSize().y)*0.5f));
					button->SetAction(GUI::Item::ActionType::Click,action);
				}
				++pos;
				return button;
			};

			SummonButton([](GUI::Item* item) { new Tools::Generator::Noise::Simple((ToolSet*)item->GetUserData()); });
			SummonButton([](GUI::Item* item) { new Tools::Generator::Noise::Worley((ToolSet*)item->GetUserData()); });
			SummonButton([](GUI::Item* item) { new Tools::Filter::Correction::Grayscale((ToolSet*)item->GetUserData()); });
			SummonButton([](GUI::Item* item) { new Tools::Filter::Correction::Blur((ToolSet*)item->GetUserData()); });
			SummonButton([](GUI::Item* item) { new Tools::Filter::Physics::HeightToNormal((ToolSet*)item->GetUserData()); });
			SummonButton([](GUI::Item* item) { new Tools::Viewer::Simple((ToolSet*)item->GetUserData()); });
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
	panelConfig->SetSize(vec2(128.0f,float32(window->GetSize().y)));
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
#pragma region Generator
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
void										TexProject::Tools::Generator::Noise::Simple::Refresh()
{
	texture->Create(uvec2(256));
	{
		for(uint32 x = 0; x < texture->GetSize().x; ++x)
		for(uint32 y = 0; y < texture->GetSize().y; ++y)
		{
			texture->SetPixel(uvec2(x,y),vec4(rnd(),rnd(),rnd(),1.0f));
		}
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
void										TexProject::Tools::Generator::Noise::Worley::Refresh()
{
	texture->Create(uvec2(128));
	{
		uint32 width = texture->GetSize().x;
		float32 wcoef = 1.0f / width;

		uint32 height = texture->GetSize().y;
		float32 hcoef = 1.0f / height;
		vec2* dotArr = new vec2[generationDotsNumber];

		for (uint32 i = 0; i < generationDotsNumber; ++i)
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


				for (int i = 0; i < int32(generationDotsNumber); ++i)
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
	buttonInput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonInput->SetRecipient();
		buttonInput->SetUserData(this);
		buttonInput->SetAction
		(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
			{
				((Tools::Filter::Correction::Blur*)item->GetUserData())->Refresh();
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
				((Tools::Filter::Correction::Blur*)item->GetUserData())->Refresh();
			}
		);
	}
}
TexProject::Tools::Filter::Correction::Blur::~Blur()
{

}
void										TexProject::Tools::Filter::Correction::Blur::Refresh()
{
	auto source = GetInput();

	if(source)
	{
		texture->Create(source->GetSize());
		{
			float32 radius = 5.0f;

			for(int32 x = 0; x < int32(texture->GetSize().x); ++x)
			for(int32 y = 0; y < int32(texture->GetSize().y); ++y)
			{
				vec4 color = source->GetPixel(uvec2(x,y));
				float32 count = 1.0f;
				for(int32 tx = 1; tx < int32(radius); ++tx)
				for(int32 ty = 1; ty < int32(radius); ++ty)
				{
					float32 d = vec2(float32(tx),float32(ty)).length();
					if(d < radius)
					{
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
					}
				}

				color /= count;
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
TexProject::Texture::D2*					TexProject::Tools::Filter::Correction::Blur::GetInput()
{
	auto t = buttonInput->GetTarget();
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
	buttonInput = (GUI::Buttons::Connector*)panelFieldBase->AddButton(GUI::ButtonTypes::Connector);
	{
		buttonInput->SetRecipient();
		buttonInput->SetUserData(this);
		buttonInput->SetAction
			(
			GUI::Item::ActionType::Refresh,
			[](GUI::Item* item)
		{
			((Tools::Filter::Physics::HeightToNormal*)item->GetUserData())->Refresh();
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
			((Tools::Filter::Physics::HeightToNormal*)item->GetUserData())->Refresh();
		}
		);
	}
}
TexProject::Tools::Filter::Physics::HeightToNormal::~HeightToNormal()
{

}
void										TexProject::Tools::Filter::Physics::HeightToNormal::Refresh()
{
	auto source = GetInput();

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
				a.z = 0.1f;
				a.normalize();
				a += vec3(1.0f);
				a *= vec3(0.5f);
				texture->SetPixel(uvec2(i,j),vec4(a,1.0f));
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
TexProject::Texture::D2*					TexProject::Tools::Filter::Physics::HeightToNormal::GetInput()
{
	auto t = buttonInput->GetTarget();
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
		tool->oglShader->Load("Media/Shaders/GLSL/3D/Material/Basic/1.","vs","","","","ps");
		tool->oglShader->Use();
		tool->oglShader->SetInt("TextureDiffuse",0);
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
					tmpShader->Load("Media/Shaders/GLSL/3D/material/Flat/1.","vs","","","","ps");
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
#pragma endregion
#pragma endregion

































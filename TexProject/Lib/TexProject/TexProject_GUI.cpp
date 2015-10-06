#include "TexProject_GUI.h"
using namespace TexProject;

#pragma region Test
#pragma endregion


#pragma region GUI
#pragma region GUI
#pragma region Basic
TexProject::GraphicUserInterface::GraphicUserInterface(RenderContext* renderContext_):
	ContextBind(renderContext_),
	mouse(this)
{
}
void										TexProject::GraphicUserInterface::Loop()
{
	mouse.Process();

	DraggingProcess();

	item.sort([](Item* a,Item* b) { return *a < *b; });

	auto i = item.begin();
	while(i != item.end())
	{
		try
		{
			(*i)->Loop();
		}
		catch(Item::LocalDestruction)
		{
			delete *i;
			i = item.erase(i);
			continue;
		}
		catch(Item::Destruction)
		{
			delete *i;
			i = item.erase(i);
			continue;
		}
		++i;
	}
}
#pragma endregion
#pragma region Items Processing
TexProject::GUI::Panel*						TexProject::GraphicUserInterface::AddPanel(PanelTypes type_)
{
	return nullptr;
}
TexProject::GUI::Button*					TexProject::GraphicUserInterface::AddButton(ButtonTypes type_)
{
	return nullptr;
}
#pragma endregion
#pragma region Platform-Dependent
#if __TEXPROJECT_WIN__
void										TexProject::GraphicUserInterface::_win_Paint()
{
}
#endif
#pragma endregion
#pragma endregion
#pragma region Item
#pragma region Basic
TexProject::GUI::Item::Item(GUI* gui_,Item* parent_):
	Helper::Prio(0),
	Helper::Pos2(vec2(0.0f)),
	Helper::Size2(vec2(100.0f)),
	Helper::Color4(vec4(1.0f)),
	gui(gui_),
	parent(parent_)
{
	for(uint32 i = 0; i < actionsCount; ++i) action[i] = nullptr;
}
TexProject::GUI::Item::~Item()
{
	CallAction(ActionType::Destruction);
	SetUserData(nullptr);

	if(gui->draggingPick == this) gui->draggingPick = nullptr;
	if(gui->draggingSelection == this) gui->draggingSelection = nullptr;
}
void										TexProject::GUI::Item::Loop()
{
	auto &mouse = gui->mouse;
	auto p = vec2(mouse.locpos) - GetPos();

	auto size_ = GetSize();
	auto t = size_*(scrollingSize/(size_+scrollingSize));

	if((properties & (uint32)PropertiesBit::ScrollX) == 0)
	{
		if(gui->draggingSelection == this)
		if(mouse.lstate && !mouse.olstate)
		{
			if(p.x >= 0.0f && p.x < size_.x && p.y < 0.0f)
			{
				properties |= (uint32)PropertiesBit::ScrollX;
			}
		}
	}
	if((properties & (uint32)PropertiesBit::ScrollX) > 0)
	{
		if(mouse.lstate)
		{
			scrollingValue.x = block(p.x-t.x*0.5f,0.0f,size_.x - t.x)/(size_.x-t.x);
		}
		else
		{
			properties &= ~(uint32)PropertiesBit::ScrollX;
		}
	}

	if((properties & (uint32)PropertiesBit::ScrollY) == 0)
	{
		if(gui->draggingSelection == this)
		if(mouse.lstate && !mouse.olstate)
		{
			if(p.y >= 0.0f && p.y < size_.y && p.x < 0.0f)
			{
				properties |= (uint32)PropertiesBit::ScrollY;
			}
		}
	}
	if((properties & (uint32)PropertiesBit::ScrollY) > 0)
	{
		if(mouse.lstate)
		{
			scrollingValue.y = block(p.y-t.y*0.5f,0.0f,size_.y - t.y)/(size_.y-t.y);
		}
		else
		{
			properties &= ~(uint32)PropertiesBit::ScrollY;
		}
	}

	if(gui->draggingSelection == this && IsEnabled())
	if(mouse.lstate && !mouse.olstate)
	{
		CallAction(ActionType::Click);
	}
}
TexProject::vec2							TexProject::GUI::Item::GetPos() const
{
	return	parent ?
			(
				parent->IsScrollable() ?
				parent->GetPos() - parent->GetScrollingSize()*parent->GetScrollingValue() + (GetLocalPos() + GetAnchor()) :
				parent->GetPos() + (GetLocalPos() + GetAnchor())
			) :
			GetLocalPos() + GetAnchor();
}
TexProject::GUI::Item*						TexProject::GUI::Item::GetBase()
{
	return parent ? parent->GetBase() : this;
}
#pragma endregion
#pragma region Dragging
TexProject::GUI::Item*						TexProject::GUI::Item::GetSelection()
{
	if(IsSelected()) return this;
	return nullptr;
}
bool										TexProject::GUI::Item::IsSelected() const
{
	auto p = vec2(gui->mouse.locpos) - GetPos();

	if(IsScrollable() || IsCollapsable() || IsClosable())
	{
		if(IsCollapsable() && IsCollapsed())
		{
			if(p.x >= -border.x && p.x <= size.x+border.x)
			if(p.y >= size.y && p.y <= size.y+border.y)
			{
				return true;
			}
		}
		else
		{
			if(p.x >= -border.x && p.x <= size.x+border.x)
			if(p.y >= -border.y && p.y <= size.y+border.y)
			{
				return true;
			}
		}
	}
	else
	{
		if(p.x >= 0.0f && p.x <= size.x)
		if(p.y >= 0.0f && p.y <= size.y)
		{
			return true;
		}
	}

	return false;
}
bool										TexProject::GUI::Item::CanDrag() const
{
	auto p = vec2(gui->mouse.locpos) - GetPos();

	if(IsCollapsable() && IsCollapsed())
	{
		if(p.x >= -border.x && p.x <= size.x+border.x)
		if(p.y >= size.y && p.y <= size.y+border.y)
		{
			return true;
		}
	}
	else
	{
		if(p.x >= 0.0f && p.x <= size.x)
		if(p.y >= 0.0f && p.y <= size.y)
		{
			return true;
		}
	}

	return false;
}
#pragma endregion
#pragma region Platform-Dependent
#if __TEXPROJECT_WIN__
void										TexProject::GUI::Item::_win_Paint()
{
}
#endif
#pragma endregion
#pragma endregion
#pragma region Panel
#pragma region Child
TexProject::GUI::Panel::Panel(GUI* gui_,Item* parent_):
	Item(gui_,parent_)
{
}
TexProject::GUI::Panel*						TexProject::GraphicUserInterface::Panel::AddPanel(PanelTypes type_)
{
	throw Exception();
}
TexProject::GUI::Button*					TexProject::GraphicUserInterface::Panel::AddButton(ButtonTypes type_)
{
	throw Exception();
}
#pragma endregion
#pragma region Basic
TexProject::GraphicUserInterface::Panel::~Panel()
{
	for(auto i : item)
	{
		delete i;
	}
}
void										TexProject::GraphicUserInterface::Panel::Loop()
{
	Item::Loop();

	auto &mouse = gui->mouse;
	auto p = vec2(mouse.locpos) - GetPos();

	auto size_ = GetSize();

	if(IsClosable())
	{
		if(gui->draggingSelection == this)
		if(p.x > size_.x && p.x <= size_.x+border.x)
		if(p.y > size_.y && p.y <= size_.y+border.y)
		if(mouse.lstate && !mouse.olstate)
		{
			throw Destruction();
		}
	}

	if(IsCollapsable())
	{
		auto p = vec2(gui->mouse.locpos) - GetPos();

		if(gui->draggingSelection == this)
		if(p.x >= -border.x && p.x < 0.0f)
		if(p.y > size_.y && p.x <= size_.y+border.y)
		if(gui->mouse.lstate && !gui->mouse.olstate)
		{
			if(IsCollapsed())
			{
				Restore();
			}
			else
			{
				Collapse();
			}
		}
	}

	item.sort([](Item* a,Item* b) { return *a < *b; });

	auto i = item.begin();
	while(i != item.end())
	{
		try
		{
			(*i)->Loop();
		}
		catch(Item::LocalDestruction)
		{
			delete *i;
			i = item.erase(i);
			continue;
		}
		++i;
	}
}
#pragma endregion
#pragma region Dragging
TexProject::GUI::Item*						TexProject::GUI::Panel::GetSelection()
{
	for(auto i: item) { if(auto t = i->GetSelection()) return t; }
	if(IsSelected()) return this;
	return nullptr;
}
#pragma endregion
#pragma region Platform-Dependent
#if __TEXPROJECT_WIN__
void										TexProject::GraphicUserInterface::Panel::_win_Paint()
{
	for(auto i: item)
	{
		i->_win_Paint();
	}
}
#endif
#pragma endregion
#pragma endregion
#pragma region Button
#pragma region Basic
TexProject::GUI::Button::Button(GUI* gui_,Item* parent_):
	Item(gui_,parent_)
{
}
#pragma endregion
#pragma endregion
#pragma region Panels
#pragma region Default
TexProject::GUI::Panels::Default::Default(GUI* gui_,Item* parent_):
	Panel(gui_,parent_)
{
}
void															TexProject::GUI::Panels::Default::Loop()
{
	Panel::Loop();
}
TexProject::GUI::Panels::Default::Type							TexProject::GUI::Panels::Default::GetType() const
{
	return Type::Default;
}
#pragma endregion
#pragma region Image
TexProject::GUI::Panels::Image::Image(GUI* gui_,Item* parent_):
	Panel(gui_,parent_)
{
}
TexProject::GUI::Panels::Image::Type							TexProject::GUI::Panels::Image::GetType() const
{
	return Type::Image;
}
#pragma endregion
#pragma region Text
TexProject::GUI::Panels::Text::Text(GUI* gui_,Item* parent_):
	Panel(gui_,parent_)
{
}
TexProject::GUI::Panels::Text::Type							TexProject::GUI::Panels::Text::GetType() const
{
	return Type::Text;
}
void														TexProject::GUI::Panels::Text::Loop()
{
	Panel::Loop();
}
#pragma endregion
#pragma endregion
#pragma region Buttons
#pragma region Default
TexProject::GUI::Buttons::Default::Default(GUI* gui_,Item* parent_):
	Button(gui_,parent_)
{
}
TexProject::GUI::Buttons::Default::Type							TexProject::GUI::Buttons::Default::GetType() const
{
	return Type::Default;
}
#pragma endregion
#pragma region Trigger
TexProject::GUI::Buttons::Trigger::Trigger(GUI* gui_,Item* parent_):
	Button(gui_,parent_)
{
}
TexProject::GUI::Buttons::Trigger::Type							TexProject::GUI::Buttons::Trigger::GetType() const
{
	return Type::Trigger;
}
void															TexProject::GUI::Buttons::Trigger::Loop()
{
	auto &mouse = gui->mouse;

	Button::Loop();

	if(gui->draggingSelection == this && IsEnabled())
	if(mouse.lstate && !mouse.olstate)
	{
		state = !state;
	}
}
#pragma endregion
#pragma region Switcher
TexProject::GUI::Buttons::Switcher::Switcher(GUI* gui_,Item* parent_):
	Button(gui_,parent_)
{
}
TexProject::GUI::Buttons::Switcher::Type						TexProject::GUI::Buttons::Switcher::GetType() const
{
	return Type::Switcher;
}
void															TexProject::GUI::Buttons::Switcher::Loop()
{
	auto &mouse = gui->mouse;

	if(gui->draggingSelection == this && IsEnabled())
	{
		if(mouse.lstate && !mouse.olstate)
		{
			auto p1 = GetPos().y;
			auto p2 = p1 + GetSize().y;
			auto m = (float32)mouse.locpos.y;

			for(uint32 i = 0; i < maxState; ++i)
			{
				if(m > bezier(p1,p2,float32(i)/float32(maxState)) && m < bezier(p1,p2,float32(i+1)/float32(maxState)))
				{
					state = i;
					break;
				}
			}
		}
	}

	Button::Loop();
}
#pragma endregion
#pragma region Slider
TexProject::GUI::Buttons::Slider::Slider(GUI* gui_,Item* parent_):
	Button(gui_,parent_)
{
	properties &= (uint32)PropertiesBit::Lock;
}
TexProject::GUI::Buttons::Slider::Type							TexProject::GUI::Buttons::Slider::GetType() const
{
	return Type::Slider;
}
void															TexProject::GUI::Buttons::Slider::Loop()
{
	auto &mouse = gui->mouse;

	Button::Loop();

	if(mouse.lstate)
	{
		if(!mouse.olstate)
		if(gui->draggingSelection == this && IsEnabled())
		{
			properties |= (uint32)PropertiesBit::Lock; //lock = true;
		}
	}
	else
	{
		properties &= ~(uint32)PropertiesBit::Lock; //lock = false;
	}

	//if(lock)
	if((properties & (uint32)PropertiesBit::Lock) > 0)
	{
		float32 tSize = size.x;// - 2.0f*border.x;
		value = block(float32(mouse.locpos.x - GetPos().x) / tSize,0.0f,1.0f);
	}
}
#pragma endregion
#pragma region Connector
TexProject::GUI::Buttons::Connector*							TexProject::GUI::Buttons::Connector::selected = nullptr;
TexProject::GUI::Buttons::Connector*							TexProject::GUI::Buttons::Connector::binder = nullptr;
TexProject::GUI::Buttons::Connector*							TexProject::GUI::Buttons::Connector::oBinder = nullptr;
TexProject::GUI::Buttons::Connector::Connector(GUI* gui_,Item* parent_):
	Button(gui_,parent_)
{
	properties &= ~(uint32)PropertiesBit::Recipient;
}
TexProject::GUI::Buttons::Connector::~Connector()
{
	if(binder == this) binder = nullptr;
	if(oBinder == this) oBinder = nullptr;
	if(target)
	{
		target->observers.remove(this);
	}
	for(auto i : observers)
	{
		i->target = nullptr;
	}
}
TexProject::GUI::Buttons::Connector::Type						TexProject::GUI::Buttons::Connector::GetType() const
{
	return Type::Connector;
}
void															TexProject::GUI::Buttons::Connector::Loop()
{
	auto &mouse = gui->mouse;

	Button::Loop();

	if(mouse.lstate)
	{
		if(!mouse.olstate)
		if(gui->draggingSelection == this)
		{
			binder = this;
		}
	}
	else
	{
		if(mouse.olstate)
		{
			if(binder == this)
			{
				if(IsRecipient())//recipient)
				if
				(
					!gui->draggingSelection ||
					!dynamic_cast<Buttons::Connector*>(gui->draggingSelection) ||
					((Buttons::Connector*)gui->draggingSelection)->IsRecipient()
				)
				{
					SetTarget(nullptr);
					binder = nullptr;
				}
			}
			else
			{
				if(binder && gui->draggingSelection == this)
				{
					//if(recipient && !binder->recipient)
					if(IsRecipient() && !binder->IsRecipient())
					{
						SetTarget(binder); binder = nullptr;
					}
					//if(!recipient && binder->recipient)
					if(!IsRecipient() && binder->IsRecipient())
					{
						binder->SetTarget(this); binder = nullptr;
					}
				}
			}
		}
	}
}
#pragma endregion
#pragma endregion
#pragma endregion

































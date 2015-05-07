#include "TexProject_Interface.h"
using namespace TexProject;


#include <TexProject/TexProject_Windows.h>
#include <TexProject/TexProject_Textures.h>


// Interface::Basic
void										TexProject::Interface::Basic::RefreshPicked()
{
	picked = nullptr;

	for(auto i: item)
	{
		if(i->IsSelect() && (!picked || i->GetPriority() > picked->GetPriority()))
		{
			picked = i;
		}
	}
}
void										TexProject::Interface::Basic::RefreshSelected()
{
	//selected = NULL;
	if(selected)
	{
		if(mouse.stateL)
		{
			if(selected->CanMove()) selected->AddPos(vec2(mouse.dPos));
		}
		else
		{
			selected = nullptr;
		}
	}
	else
	{
		if(picked && mouse.stateL && !mouse.stateOL)
		{
			if(!picked->IsAnyButtonSelect())
			{
				selected = picked;
				selected->ToTop();
			}
		}
	}
}


TexProject::Interface::Basic::Basic(PWindow window_):
window(window_)
{
}

void										TexProject::Interface::Basic::Create()
{
}
void										TexProject::Interface::Basic::Delete()
{
	for(auto i: item) Item::DeleteItem((Item*)i);
	item.clear();
}
void										TexProject::Interface::Basic::Loop()
{
	{
		mouse.oPos = mouse.pos;
		mouse.pos = MousePos();
		mouse.dPos = mouse.pos - mouse.oPos;

		mouse.stateOL = mouse.stateL;
		mouse.stateOM = mouse.stateM;
		mouse.stateOR = mouse.stateR;

		mouse.stateL = MouseLState();
		mouse.stateM = MouseMState();
		mouse.stateR = MouseRState();
	}

	RefreshPicked();
	RefreshSelected();

	if(!item.empty())
	{
		item.sort([](Item* i1,Item* i2){ return i1->GetPriority() < i2->GetPriority(); });
		top = *item.rbegin();
	}
	else
	{
		top = nullptr;
	}
	
	auto i = item.begin();
	while(i != item.end())
	{
		auto t = *i;
		try
		{
			t->Loop();
		}
		catch(Item::Exception_Destruction)
		{
			Item::DeleteItem(t);
			i = item.erase(i);
			continue;
		}
		++i;
	}
	//for(auto i: button) i->Loop();
}
Interface::GUIPanel*						TexProject::Interface::Basic::AddPanel(const PanelType& type_)
{
	throw TexProject::Exception("Forbidden [TexProject::Interface::Basic::AddPanel]");
}
Interface::GUIButton*						TexProject::Interface::Basic::AddButton(const ButtonType& type_)
{
	throw TexProject::Exception("Forbidden [TexProject::Interface::Basic::AddButton[");
}

#if __TEXPROJECT_WIN__
void										TexProject::Interface::Basic::_win_WMPaint(HDC hDC)
{
}
#endif


// Interface::Basic::Item
TexProject::Interface::Item::Item(GUI* interface_,Item* parent_):
	parent(parent_),
	Helper::Prio(0),
	Helper::Pos2((parent_) ? (vec2(0.0f)) : (vec2(interface_->GetWindow()->GetSize())*0.5f)),
	Helper::Size2(vec2(128.0f)),
	inter(interface_)
{
	//for(auto i: action) i = nullptr;
	for(auto i = 0; i < ActionTypes::count; ++i) action[i] = nullptr;
}
TexProject::Interface::Item::~Item()
{
	CallAction(ActionTypes::Free);

	ResetPointers();

	if(inter->GetPicked() == this) inter->ResetPicked();
	if(inter->GetSelected() == this) inter->ResetSelected();
	if(inter->GetTop() == this) inter->ResetTop();
}
void					TexProject::Interface::Item::Create()
{
}
void					TexProject::Interface::Item::Delete()
{
}
void					TexProject::Interface::Item::Loop()
{
	if(IsSelect() && GetBase() == inter->GetPicked())
	{
		if(inter->mouse.stateL && !inter->mouse.stateOL)
		{
			CallAction(ActionType::Click);
		}
	}
}

Interface::GUIItem*		TexProject::Interface::Item::GetBase()
{
	return parent ? parent->GetBase() : this;
}

vec2					TexProject::Interface::Item::GetPos()
{
	return parent ? (parent->GetPos() + Helper::Pos2::GetPos()) : (Helper::Pos2::GetPos());
}
vec2					TexProject::Interface::Item::GetLocalPos()
{
	return Helper::Pos2::GetPos();
}
int32					TexProject::Interface::Item::GetPriority()
{
	return parent ? (parent->GetPriority()) : (Helper::Prio::GetPriority());
}
int32					TexProject::Interface::Item::GetLocalPriority()
{
	return Helper::Prio::GetPriority();
}

bool					TexProject::Interface::Item::IsSelect()
{
	return false;
}
bool					TexProject::Interface::Item::IsAnyButtonSelect()
{
	return false;
}

#if __TEXPROJECT_WIN__
void					TexProject::Interface::Item::_win_WMPaint()
{
}
#endif


// Interface::Panel::Basic
TexProject::Interface::Panel::Basic::Basic(GUI* interface_,Item* parent_):
	Item(interface_,parent_)
{
}
void										TexProject::Interface::Panel::Basic::Create()
{
}
void										TexProject::Interface::Panel::Basic::Delete()
{
	for(auto i: panel) Item::DeleteItem(i);
	panel.clear();
	for(auto i: button) Item::DeleteItem(i);
	button.clear();
}
void										TexProject::Interface::Panel::Basic::Loop()
{
	Item::Loop();
	{
		auto i = panel.begin();
		while(i != panel.end())
		{
			auto t = *i;
			try
			{
				t->Loop();
			}
			catch(Item::Exception_LocalDestruction)
			{
				Item::DeleteItem(t);
				i = panel.erase(i);
				continue;
			}
			++i;
		}
	}
	{
		auto i = button.begin();
		while(i != button.end())
		{
			auto t = *i;
			try
			{
				t->Loop();
			}
			catch(Item::Exception_LocalDestruction)
			{
				Item::DeleteItem(t);
				i = button.erase(i);
				continue;
			}
			++i;
		}
	}
}
Interface::GUIPanel*						TexProject::Interface::Panel::Basic::AddPanel(const PanelType& type_)
{
	throw TexProject::Exception("Forbidden [TexProject::Interface::Basic::AddPanel]");
}
Interface::GUIButton*						TexProject::Interface::Panel::Basic::AddButton(const ButtonType& type_)
{
	throw TexProject::Exception("Forbidden [TexProject::Interface::Basic::AddButton[");
}

#if __TEXPROJECT_WIN__
void										TexProject::Interface::Panel::Basic::_win_WMPaint()
{
	for(auto i: button) i->_win_WMPaint();
	for(auto i: panel) i->_win_WMPaint();
}
#endif


// Interface::Basic::Panel::Default
TexProject::Interface::Panel::Default::Default(GUI* interface_,Item* parent_):
	Basic(interface_,parent_)
{
}


// Interface::Basic::Panel::Image
TexProject::Interface::Panel::Image::Image(GUI* interface_,Item* parent_):
	Basic(interface_,parent_)
{
}


// Interface::Button::Basic
TexProject::Interface::Button::Basic::Basic(GUI* interface_,Item* parent_):
	Item(interface_,parent_)
{
}


// Interface::Basic::Button::Default
TexProject::Interface::Button::Default::Default(GUI* interface_,Item* parent_):
	Basic(interface_,parent_)
{
}


// Interface::Basic::Button::Trigger
TexProject::Interface::Button::Trigger::Trigger(GUI* interface_,Item* parent_):
	Basic(interface_,parent_)
{
}
void					TexProject::Interface::Button::Trigger::Loop()
{
	Basic::Loop();
	if(IsSelect() && GetBase() == inter->GetPicked())
	{
		if(inter->mouse.stateL && !inter->mouse.stateOL)
		{
			state = !state;
		}
	}
}



// Interface::Default::Panel::Default
TexProject::Interface::Default::Panel::Default::Default(GUI* interface_,Item* parent_):
	Interface::Panel::Default(interface_,parent_)
{
}
bool										TexProject::Interface::Default::Panel::Default::IsSelect()
{
	//if(parent) return parent->IsSelect();

	auto m_ = MousePos();

	auto pos_ = GetPos();
	pos_.x += inter->GetWindow()->GetPos().x;
	pos_.y += inter->GetWindow()->GetPos().y;
	auto hsize_ = GetSize()*0.5f;

	if( (m_.x >= pos_.x - hsize_.x) && (m_.x <= pos_.x + hsize_.x) && (m_.y >= pos_.y - hsize_.y) && (m_.y <= pos_.y + hsize_.y) )
	{
		return true;
	}
	else
	{
		for(auto i: panel) if(i->IsSelect()) return true;
	}
	return false;
}
bool										TexProject::Interface::Default::Panel::Default::IsAnyButtonSelect()
{
	for(auto i: button) if(i->IsSelect()) return true;
	return false;
}
void										TexProject::Interface::Default::Panel::Default::_win_WMPaint()
{
	auto &hDC = ((Interface::Default*)(inter))->renderDeviceContextHandle;
	auto &rect = ((Interface::Default*)(inter))->renderRect;

	auto pos_ = GetPos();
	auto hsize_ = GetSize()*0.5f;

	if(!parent)
	{	// shadow
		rect.left = LONG(pos_.x - hsize_.x + 4.0f);
		rect.bottom = LONG(pos_.y + hsize_.y + 4.0f);
		rect.right = LONG(pos_.x + hsize_.x + 4.0f);
		rect.top = LONG(pos_.y - hsize_.y + 4.0f);

		FillRect(hDC,&rect,(HBRUSH)GetStockObject(BLACK_BRUSH));
	}

	rect.left = LONG(pos_.x - hsize_.x);
	rect.bottom = LONG(pos_.y + hsize_.y);
	rect.right = LONG(pos_.x + hsize_.x);
	rect.top = LONG(pos_.y - hsize_.y);

	SelectObject(hDC,(HPEN)GetStockObject(WHITE_PEN));

	if(inter->GetSelected() == this)
	{
		SelectObject(hDC,(HBRUSH)GetStockObject(WHITE_BRUSH));
		Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
		//FillRect(hDC,&rect,(HBRUSH)GetStockObject(WHITE_BRUSH));
	}
	else
	{
		if(inter->GetPicked() == this)	//IsSelect())
		{
			SelectObject(hDC,(HBRUSH)GetStockObject(LTGRAY_BRUSH));
			Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
			//FillRect(hDC,&rect,(HBRUSH)GetStockObject(LTGRAY_BRUSH));
		}
		else
		{
			SelectObject(hDC,(HBRUSH)GetStockObject(GRAY_BRUSH));
			Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
			//FillRect(hDC,&rect,(HBRUSH)GetStockObject(GRAY_BRUSH));
		}
	}

	Basic::_win_WMPaint();
}
Interface::GUIPanel*						TexProject::Interface::Default::Panel::Default::AddPanel(const PanelType& type_)
{
	switch(type_)
	{
		case PanelTypes::Default:
		{
			return Interface::Panel::Default::AddPanel<Interface::Default::Panel::Default>();
		}
		case PanelTypes::Image:
		{
			return Interface::Panel::Default::AddPanel<Interface::Default::Panel::Image>();
		}
		default:
		{
			return nullptr;
		}
	}
}
Interface::GUIButton*						TexProject::Interface::Default::Panel::Default::AddButton(const ButtonType& type_)
{
	switch(type_)
	{
		case ButtonTypes::Default:
		{
			return Interface::Panel::Default::AddButton<Interface::Default::Button::Default>();
		}
		/*case ButtonTypes::Trigger:
		{
			//return AddItem<Button::Trigger>();
			return nullptr;
		}
		case ButtonTypes::Slider:
		{
			//return AddItem<Button::Default>();
			return nullptr;
		}*/
		case ButtonTypes::Close:
		{
			auto t = Interface::Panel::Default::AddButton<Interface::Default::Button::Default>();
			t->SetAction
			(
				Item::ActionTypes::Click,
				[](Item* item) -> void
				{
					throw Item::Exception_Destruction();
				}
			);
			return t;
		}
		case ButtonTypes::Trigger:
		{
			return Interface::Panel::Default::AddButton<Interface::Default::Button::Trigger>();
		}
		default:
		{
			return nullptr;
		}
	}
}


// Interface::Default::Panel::Image
TexProject::Interface::Default::Panel::Image::Image(GUI* interface_,Item* parent_):
	Interface::Panel::Image(interface_,parent_)
{
}
bool										TexProject::Interface::Default::Panel::Image::IsSelect()
{
	//if(parent) return parent->IsSelect();

	auto m_ = MousePos();

	auto pos_ = GetPos();
	pos_.x += inter->GetWindow()->GetPos().x;
	pos_.y += inter->GetWindow()->GetPos().y;
	auto hsize_ = GetSize()*0.5f;

	if((m_.x >= pos_.x - hsize_.x) && (m_.x <= pos_.x + hsize_.x) && (m_.y >= pos_.y - hsize_.y) && (m_.y <= pos_.y + hsize_.y))
	{
		return true;
	}
	/*else
	{
		for(auto i: panel) if(i->IsSelect()) return true;
	}*/
	return false;
}
void										TexProject::Interface::Default::Panel::Image::_win_WMPaint()
{
	auto window = inter->GetWindow();
	auto &hDC = ((Interface::Default*)(inter))->renderDeviceContextHandle;
	auto &rect = ((Interface::Default*)(inter))->renderRect;

	auto pos_ = GetPos();
	auto hsize_ = GetSize()*0.5f;

	if(!parent)
	{	// shadow
		rect.left = LONG(pos_.x - hsize_.x + 4.0f);
		rect.bottom = LONG(pos_.y + hsize_.y + 4.0f);
		rect.right = LONG(pos_.x + hsize_.x + 4.0f);
		rect.top = LONG(pos_.y - hsize_.y + 4.0f);

		FillRect(hDC,&rect,(HBRUSH)GetStockObject(BLACK_BRUSH));
	}

	float32 border = 1.0f;

	rect.left = LONG(pos_.x - (hsize_.x+border));
	rect.bottom = LONG(pos_.y + (hsize_.y+border));
	rect.right = LONG(pos_.x + (hsize_.x+border));
	rect.top = LONG(pos_.y - (hsize_.y+border));

	SelectObject(hDC,(HBRUSH)GetStockObject(WHITE_PEN));
	SelectObject(hDC,(HBRUSH)GetStockObject(GRAY_BRUSH));
	Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);

	rect.left = LONG(pos_.x - hsize_.x);
	rect.bottom = LONG(pos_.y + hsize_.y);
	rect.right = LONG(pos_.x + hsize_.x);
	rect.top = LONG(pos_.y - hsize_.y);

	if(texture)
	{
		SetStretchBltMode(hDC,STRETCH_HALFTONE);
		StretchDIBits
		(
			hDC,
			rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
			0,0,texture->GetSize().x,texture->GetSize().y,
			texture->winTextureData,(BITMAPINFO*)&texture->winInfoHeader,
			DIB_RGB_COLORS,SRCCOPY
		);
	}

	Basic::_win_WMPaint();
}



// Interface::Default::Button::Default
TexProject::Interface::Default::Button::Default::Default(GUI* interface_,Item* parent_):
	Interface::Button::Default(interface_,parent_)
{
}
bool										TexProject::Interface::Default::Button::Default::IsSelect()
{
	auto m_ = MousePos();

	auto pos_ = GetPos();
	pos_.x += inter->GetWindow()->GetPos().x;
	pos_.y += inter->GetWindow()->GetPos().y;
	auto hsize_ = GetSize()*0.5f;

	return	(
		(m_.x >= pos_.x - hsize_.x) &&
		(m_.x <= pos_.x + hsize_.x) &&
		(m_.y >= pos_.y - hsize_.y) &&
		(m_.y <= pos_.y + hsize_.y)
		);
}
void										TexProject::Interface::Default::Button::Default::_win_WMPaint()
{
	auto &hDC = ((Interface::Default*)(inter))->renderDeviceContextHandle;
	auto &rect = ((Interface::Default*)(inter))->renderRect;
	auto &redBrush = ((Interface::Default*)(inter))->renderBrushRed;
	auto &greenBrush = ((Interface::Default*)(inter))->renderBrushGreen;
	auto &blueBrush = ((Interface::Default*)(inter))->renderBrushBlue;

	auto pos_ = GetPos();
	auto hsize_ = GetSize()*0.5f;

	/*if(!parent)
	{	// shadow
	rect.left = LONG(pos_.x - hsize_.x + 4.0f);
	rect.bottom = LONG(pos_.y + hsize_.y + 4.0f);
	rect.right = LONG(pos_.x + hsize_.x + 4.0f);
	rect.top = LONG(pos_.y - hsize_.y + 4.0f);

	FillRect(hDC,&rect,(HBRUSH)GetStockObject(BLACK_BRUSH));
	}*/

	rect.left = LONG(pos_.x - hsize_.x);
	rect.bottom = LONG(pos_.y + hsize_.y);
	rect.right = LONG(pos_.x + hsize_.x);
	rect.top = LONG(pos_.y - hsize_.y);

	SelectObject(hDC,(HPEN)GetStockObject(WHITE_PEN));

	if(IsSelect() && GetBase() == inter->GetPicked())
	{
		SelectObject(hDC,redBrush);
	}
	else
	{
		SelectObject(hDC,greenBrush);
	}
	Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
}


// Interface::Default::Button::Trigger
TexProject::Interface::Default::Button::Trigger::Trigger(GUI* interface_,Item* parent_):
	Interface::Button::Trigger(interface_,parent_)
{
}
/*void										TexProject::Interface::Default::Button::Trigger::Create()
{
}
void										TexProject::Interface::Default::Button::Trigger::Delete()
{
}
void										TexProject::Interface::Default::Button::Trigger::Loop()
{
	if(IsSelect() && GetBase() == inter->GetPicked())
	{
		if(inter->mouse.stateL && !inter->mouse.stateOL)
		{
			state = !state;
			//CallAction(ActionType::Click);
		}
	}
}*/
bool										TexProject::Interface::Default::Button::Trigger::IsSelect()
{
	auto m_ = MousePos();

	auto pos_ = GetPos();
	pos_.x += inter->GetWindow()->GetPos().x;
	pos_.y += inter->GetWindow()->GetPos().y;
	auto hsize_ = GetSize()*0.5f;

	return	(
				(m_.x >= pos_.x - hsize_.x) &&
				(m_.x <= pos_.x + hsize_.x) &&
				(m_.y >= pos_.y - hsize_.y) &&
				(m_.y <= pos_.y + hsize_.y)
			);
}
void										TexProject::Interface::Default::Button::Trigger::_win_WMPaint()
{
	auto &hDC = ((Interface::Default*)(inter))->renderDeviceContextHandle;
	auto &rect = ((Interface::Default*)(inter))->renderRect;
	auto &redBrush = ((Interface::Default*)(inter))->renderBrushRed;
	auto &greenBrush = ((Interface::Default*)(inter))->renderBrushGreen;
	auto &blueBrush = ((Interface::Default*)(inter))->renderBrushBlue;

	auto pos_ = GetPos();
	auto hsize_ = GetSize()*0.5f;

	rect.left = LONG(pos_.x - hsize_.x);
	rect.bottom = LONG(pos_.y + hsize_.y);
	rect.right = LONG(pos_.x + hsize_.x);
	rect.top = LONG(pos_.y - hsize_.y);

	SelectObject(hDC,(HPEN)GetStockObject(WHITE_PEN));

	if(IsSelect() && GetBase() == inter->GetPicked())
	{
		SelectObject(hDC,redBrush);
	}
	else
	{
		if(state) SelectObject(hDC,blueBrush);
		else SelectObject(hDC,greenBrush);
	}
	Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
}


// Interface::Default
TexProject::Interface::Default::Default(PWindow window_):
	Basic(window_)
{
}
void										TexProject::Interface::Default::Create()
{
	renderBrushRed = CreateSolidBrush(RGB(255,0,0));
	renderBrushGreen = CreateSolidBrush(RGB(0,255,0));
	renderBrushBlue = CreateSolidBrush(RGB(0,0,255));
}
void										TexProject::Interface::Default::Delete()
{
	DeleteObject(renderBrushRed); renderBrushRed = NULL;
	DeleteObject(renderBrushGreen); renderBrushGreen = NULL;
	DeleteObject(renderBrushBlue); renderBrushBlue = NULL;
	Basic::Delete();
}
void										TexProject::Interface::Default::Loop()
{
	Basic::Loop();
}
Interface::GUIPanel*						TexProject::Interface::Default::AddPanel(const PanelType& type_)
{
	switch(type_)
	{
		case PanelTypes::Default:
		{
			return AddItem<Panel::Default>();
		}
		case PanelTypes::Image:
		{
			return AddItem<Panel::Image>();
		}
		default:
		{
			return nullptr;
		}
	}
}
Interface::GUIButton*						TexProject::Interface::Default::AddButton(const ButtonType& type_)
{
	switch(type_)
	{
		case ButtonTypes::Default:
		{
			return AddItem<Button::Default>();
		}
		/*case ButtonTypes::Trigger:
		{
			//return AddItem<Button::Trigger>();
			return nullptr;
		}
		case ButtonTypes::Slider:
		{
			//return AddItem<Button::Default>();
			return nullptr;
		}*/
		case ButtonTypes::Close:
		{
			auto t = AddItem<Button::Default>();
			t->SetAction
			(
				Item::ActionTypes::Click,
				[](Item* item) -> void
				{
					throw Item::Exception_Destruction();
				}
			);
			return t;
		}
		default:
		{
			return nullptr;
		}
	}
}

#if __TEXPROJECT_WIN__
void										TexProject::Interface::Default::_win_WMPaint(HDC hDC)
{
	renderDeviceContextHandle = hDC;
	for(auto i: item) i->_win_WMPaint();
}
#endif











































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
		auto j = i->IsSelect();
		if(j && (!picked || j->GetPriority() > picked->GetPriority()))
		{
			picked = j;
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
			if(selected->CanMove()) selected->GetBase()->AddPos(vec2(mouse.dPos));
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

	{
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

	{	//Set Priority
		uint32 j = 0;
		for(auto i: item) { i->SetPriority(j); ++j; };
	}
	

	{	// do some preparation
		Button::Connector::oBinder = Button::Connector::binder;
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


	{	// do some finalization?
		Button::Connector::oBinder = nullptr;
	}
}
Interface::GUIPanel*						TexProject::Interface::Basic::AddPanel(const PanelType& type_)
{
	throw TexProject::Exception("Forbidden [TexProject::Interface::Basic::AddPanel]");
}
Interface::GUIButton*						TexProject::Interface::Basic::AddButton(const ButtonType& type_)
{
	throw TexProject::Exception("Forbidden [TexProject::Interface::Basic::AddButton]");
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
	Helper::Color4(vec4(1.0f)),
	inter(interface_)
{
	//for(auto i: action) i = nullptr;
	for(auto i = 0; i < ActionTypes::count; ++i) action[i] = nullptr;
}
TexProject::Interface::Item::~Item()
{
	CallAction(ActionTypes::Free);

	ResetPointers();

	if(userDataRemove && userData)
	{
		delete userData;
	}

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
	/*if(IsLocalSelect() && inter->GetPicked() && GetBase() == inter->GetPicked()->GetBase())
	{
		if(inter->mouse.stateL && !inter->mouse.stateOL)
		{
			CallAction(ActionType::Click);
		}
	}*/
	if(inter->mouse.stateL)
	{
		if(clamped)
		{
			if(clampLock > 0) --clampLock;
			else CallAction(ActionType::Clamp);
		}
		else
		{
			if(!inter->mouse.stateOL)
			{
				if(IsLocalSelect() && inter->GetPicked() && GetBase() == inter->GetPicked()->GetBase())
				{
					CallAction(ActionType::Click);
					clamped = true;
					clampLock = 30;
				}
			}
		}
	}
	else
	{
		clamped = false;
		clampLock = 0;
	}

}
bool					TexProject::Interface::Item::IsConnector()
{
	return false;
}

void					TexProject::Interface::Item::Refresh()
{
	CallAction(ActionTypes::Refresh);
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

Interface::GUIItem*		TexProject::Interface::Item::IsSelect()
{
	return parent ? parent->IsSelect() : (IsLocalSelect() ? this : nullptr);
}
bool					TexProject::Interface::Item::IsLocalSelect()
{
	auto m_ = MousePos();

	auto pos_ = GetPos();
	pos_.x += inter->GetWindow()->GetPos().x;
	pos_.y += inter->GetWindow()->GetPos().y;
	auto hsize_ = GetSize()*0.5f;

	if((m_.x >= pos_.x - hsize_.x) && (m_.x <= pos_.x + hsize_.x) && (m_.y >= pos_.y - hsize_.y) && (m_.y <= pos_.y + hsize_.y))
	{
		return true;
	}
	return false;
}
bool					TexProject::Interface::Item::IsAnyButtonSelect()
{
	return parent ? parent->IsAnyButtonSelect() : false;
}

bool					TexProject::Interface::Item::CanMove()
{
	return (properties & PropertyBits::Move) > 0 && (parent ? parent->CanMove() : true);
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
			catch(Exception_LocalDestruction)
			{
				Item::DeleteItem(t);
				i = panel.erase(i);
				continue;
			}
			catch(Exception_Destruction)
			{
				CallAction(ActionTypes::Destruction);
				throw Exception_Destruction();
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
			catch(Exception_LocalDestruction)
			{
				Item::DeleteItem(t);
				i = button.erase(i);
				continue;
			}
			catch(Exception_Destruction)
			{
				CallAction(ActionTypes::Destruction);
				throw Exception_Destruction();
			}
			++i;
		}
	}
}
Interface::GUIItem*							TexProject::Interface::Panel::Basic::IsSelect()
{
	if(parent) return parent->IsSelect();
	for(auto i: button) if(i->IsLocalSelect()) return i;
	if(IsLocalSelect()) return this;
	for(auto i: panel) if(i->IsLocalSelect()) return i;
	return nullptr;
}
bool										TexProject::Interface::Panel::Basic::IsAnyButtonSelect()
{
	for(auto i: button) if(i->IsLocalSelect()) return true;
	return false;
}
Interface::GUIPanel*						TexProject::Interface::Panel::Basic::AddPanel(const PanelType& type_)
{
	throw TexProject::Exception("Forbidden [TexProject::Interface::Basic::AddPanel]");
}
Interface::GUIButton*						TexProject::Interface::Panel::Basic::AddButton(const ButtonType& type_)
{
	throw TexProject::Exception("Forbidden [TexProject::Interface::Basic::AddButton[");
}
void										TexProject::Interface::Panel::Basic::Refresh()
{
	Item::Refresh();
	for(auto i: button) i->Refresh();
	for(auto i: panel) i->Refresh();
}

#if __TEXPROJECT_WIN__
void										TexProject::Interface::Panel::Basic::_win_WMPaint()
{
	for(auto i: button) i->_win_WMPaint();
	for(auto i: panel) i->_win_WMPaint();
}
#endif




// Interface::Panel::Default
TexProject::Interface::Panel::Default::Default(GUI* interface_,Item* parent_):
	Basic(interface_,parent_)
{
}


//
TexProject::Interface::Panel::Text::Text(GUI* interface_,Item* parent_):
	Basic(interface_,parent_)
{
}
void										TexProject::Interface::Panel::Text::SetText(const string& text_)
{
	text = text_;
}
TexProject::string							TexProject::Interface::Panel::Text::GetText() const
{
	return text;
}
void										TexProject::Interface::Panel::Text::SetAlignment(Alignment alignment_)
{
	alignment = alignment_;
}



// Interface::Panel::Image
TexProject::Interface::Panel::Image::Image(GUI* interface_,Item* parent_):
	Basic(interface_,parent_)
{
}
void										TexProject::Interface::Panel::Image::SetImage(Texture::D2* texture_)
{
}


// Interface::Button::Basic
TexProject::Interface::Button::Basic::Basic(GUI* interface_,Item* parent_):
	Item(interface_,parent_)
{
	color = vec4(0.0f,1.0f,0.0f,1.0f);
}


// Interface::Button::Default
TexProject::Interface::Button::Default::Default(GUI* interface_,Item* parent_):
	Basic(interface_,parent_)
{
}


// Interface::Button::Trigger
TexProject::Interface::Button::Trigger::Trigger(GUI* interface_,Item* parent_):
	Basic(interface_,parent_)
{
}
void					TexProject::Interface::Button::Trigger::Loop()
{
	Basic::Loop();
	if(IsLocalSelect() && inter->GetPicked() && GetBase() == inter->GetPicked()->GetBase())
	{
		if(inter->mouse.stateL && !inter->mouse.stateOL)
		{
			state = !state;
		}
	}
}


// Interface::Button::Slider
TexProject::Interface::Button::Slider::Slider(GUI* interface_,Item* parent_):
	Basic(interface_,parent_)
{
}
void					TexProject::Interface::Button::Slider::Loop()
{
	Basic::Loop();
	if(inter->mouse.stateL)
	{
		if(!inter->mouse.stateOL)
		if(IsLocalSelect() && inter->GetPicked() && GetBase() == inter->GetPicked()->GetBase())
		{
			selected = true;
		}
	}
	else
	{
		selected = false;
	}
	if(selected)
	{
		float32 tPos = GetPos().x + float32(inter->GetWindow()->GetPos().x);
		float32 tSize = size.x - 2.0f*border.x;
		slide = block((float32(inter->mouse.pos.x) - tPos + tSize*0.5f) / tSize,0.0f,1.0f);
	}
}


// Interface::Button::Connector
TexProject::Interface::GUIButtonConnector*	TexProject::Interface::Button::Connector::binder = nullptr;
TexProject::Interface::GUIButtonConnector*	TexProject::Interface::Button::Connector::oBinder = nullptr;

TexProject::Interface::Button::Connector::Connector(GUI* interface_,Item* parent_):
	Basic(interface_,parent_)
{
}
TexProject::Interface::Button::Connector::~Connector()
{
	if(binder == this) binder = nullptr;
	if(oBinder == this) oBinder = nullptr;
	UnsetTarget();
	FlushTargeting();
}
void					TexProject::Interface::Button::Connector::Loop()
{
	Basic::Loop();

	if(inter->mouse.stateL)
	{
		if(!binder)
		{
			if(IsLocalSelect() && inter->GetPicked() && GetBase() == inter->GetPicked()->GetBase())
			{
				if(!inter->mouse.stateOL)
				{
					binder = this;
				}
			}
		}
	}
	else
	{
		if(inter->mouse.stateOL)
		{
			if(binder == this)
			{
				if(recipient)
				if(!inter->GetPicked() || !inter->GetPicked()->IsConnector())
				{
					UnsetTarget();
					oBinder = nullptr;
				}
				binder = nullptr;
			}
			else
			{
				if(IsLocalSelect() && inter->GetPicked() && GetBase() == inter->GetPicked()->GetBase())
				{
					if(oBinder && oBinder->GetBase() != GetBase())
					{
						if(!(oBinder)->recipient && recipient)
						{
							SetTarget(oBinder);
						}
						if((oBinder)->recipient && !recipient)
						{
							oBinder->SetTarget(this);
						}
					}
				}
			}
		}
	}
}
bool					TexProject::Interface::Button::Connector::IsConnector()
{
	return true;
}
void					TexProject::Interface::Button::Connector::Refresh()
{
	Button::Basic::Refresh();
	if(target) target->Refresh();
}








// Interface::Default::Panel::Default
TexProject::Interface::Default::Panel::Default::Default(GUI* interface_,Item* parent_):
	Interface::Panel::Default(interface_,parent_)
{
}
void										TexProject::Interface::Default::Panel::Default::_win_WMPaint()
{
	auto &hDC = ((Interface::Default*)(inter))->renderDeviceContextHandle;
	auto &rect = ((Interface::Default*)(inter))->renderRect;

	auto pos_ = GetPos();
	auto hsize_ = GetSize()*0.5f;

	{
		rect.left = LONG(pos_.x - hsize_.x);
		rect.bottom = LONG(pos_.y + hsize_.y);
		rect.right = LONG(pos_.x + hsize_.x);
		rect.top = LONG(pos_.y - hsize_.y);

		SetDCBrushColor(hDC,RGB(color.x*255,color.y*255,color.z*255));

		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
	}

	/*
	//if(!parent)
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

	if(inter->GetSelected() && inter->GetSelected()->GetBase() == GetBase())
	{
		SelectObject(hDC,(HBRUSH)GetStockObject(WHITE_BRUSH));
		Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
	}
	else
	{
		if(inter->GetPicked() && inter->GetPicked()->GetBase() == GetBase())
		{
			SelectObject(hDC,(HBRUSH)GetStockObject(LTGRAY_BRUSH));
			Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
		}
		else
		{
			SelectObject(hDC,(HBRUSH)GetStockObject(GRAY_BRUSH));
			Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
		}
	}
	*/

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
		case PanelTypes::Text:
		{
			return  Interface::Panel::Default::AddPanel<Interface::Default::Panel::Text>();
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
		case ButtonTypes::Trigger:
		{
			auto t = Interface::Panel::Default::AddButton<Interface::Default::Button::Trigger>();
			t->SetSize(vec2(24.0f));
			return t;
		}
		case ButtonTypes::Slider:
		{
			auto t = Interface::Panel::Default::AddButton<Interface::Default::Button::Slider>();
			t->SetSize(vec2(128.0f,24.0f));
			return t;
		}
		case ButtonTypes::InputConnector:
		{
			auto i = Interface::Panel::Default::AddButton<Interface::Default::Button::Connector>();
			i->SetRecipient();
			return i;
		}
		case ButtonTypes::OutputConnector:
		{
			auto i = Interface::Panel::Default::AddButton<Interface::Default::Button::Connector>();
			i->UnsetRecipient();
			return i;
		}		
		case ButtonTypes::Close:
		{
			auto t = Interface::Panel::Default::AddButton<Interface::Default::Button::Default>();
			t->SetSize(vec2(24.0f));
			t->SetPos(vec2(GetSize().x*0.5f - 16.0f,-GetSize().y*0.5f + 16.0f));
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


// Interface::Default::Panel::Text
TexProject::Interface::Default::Panel::Text::Text(GUI* interface_,Item* parent_):
	Interface::Panel::Text(interface_,parent_)
{
}
void										TexProject::Interface::Default::Panel::Text::SetAlignment(Alignment alignment_)
{
	alignment = alignment_;
	switch(alignment)
	{
	case TexProject::Interface::Panel::Text::Alignment::Default: _win_alignment = _win_Alignment::Default; break;
	case TexProject::Interface::Panel::Text::Alignment::LeftTop: _win_alignment = _win_Alignment::LeftTop; break;
	case TexProject::Interface::Panel::Text::Alignment::LeftCenter: _win_alignment = _win_Alignment::LeftCenter; break;
	case TexProject::Interface::Panel::Text::Alignment::LeftBottom: _win_alignment = _win_Alignment::LeftBottom; break;
	case TexProject::Interface::Panel::Text::Alignment::CenterTop: _win_alignment = _win_Alignment::CenterTop; break;
	case TexProject::Interface::Panel::Text::Alignment::CenterCenter: _win_alignment = _win_Alignment::CenterCenter; break;
	case TexProject::Interface::Panel::Text::Alignment::CenterBottom: _win_alignment = _win_Alignment::CenterBottom; break;
	case TexProject::Interface::Panel::Text::Alignment::RightTop: _win_alignment = _win_Alignment::RightTop; break;
	case TexProject::Interface::Panel::Text::Alignment::RightCenter: _win_alignment = _win_Alignment::RightCenter; break;
	case TexProject::Interface::Panel::Text::Alignment::RightBottom: _win_alignment = _win_Alignment::RightBottom; break;
	default: _win_alignment = _win_Alignment::LeftTop; break;
	}
}
void										TexProject::Interface::Default::Panel::Text::_win_WMPaint()
{
	auto window = inter->GetWindow();
	auto &hDC = ((Interface::Default*)(inter))->renderDeviceContextHandle;
	auto &rect = ((Interface::Default*)(inter))->renderRect;

	auto pos_ = GetPos();
	auto hsize_ = GetSize()*0.5f;

	/*{
		float32 border = 1.0f;

		rect.left = LONG(pos_.x - (hsize_.x+border));
		rect.bottom = LONG(pos_.y + (hsize_.y+border));
		rect.right = LONG(pos_.x + (hsize_.x+border));
		rect.top = LONG(pos_.y - (hsize_.y+border));

		SetDCBrushColor(hDC,RGB(color.x*255,color.y*255,color.z*255));

		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
	}*/

	{
		rect.left = LONG(pos_.x - hsize_.x);
		rect.bottom = LONG(pos_.y + hsize_.y);
		rect.right = LONG(pos_.x + hsize_.x);
		rect.top = LONG(pos_.y - hsize_.y);

		SetTextColor(hDC,RGB(color.x*255,color.y*255,color.z*255));
		//SetTextAlign(hDC,TA_CENTER | TA_TOP);
		/*
		#define TA_NOUPDATECP                0
		#define TA_UPDATECP                  1

		#define TA_LEFT                      0
		#define TA_RIGHT                     2
		#define TA_CENTER                    6

		#define TA_TOP                       0
		#define TA_BOTTOM                    8
		#define TA_BASELINE                  24

		TA_RTLREADING
		*/

		//SetBkColor(hDC,RGB(0,255,0));
		SetBkMode(hDC,TRANSPARENT);	// OPAQUE, TRANSPARENT

		//text = "text\nlol";

		//UINT format = DT_LEFT | DT_TOP | DT_NOPREFIX;
		/*
		DT_TOP                      0x00000000
		DT_LEFT                     0x00000000
		DT_CENTER                   0x00000001
		DT_RIGHT                    0x00000002
		DT_VCENTER                  0x00000004
		DT_BOTTOM                   0x00000008
		DT_WORDBREAK                0x00000010
		DT_SINGLELINE               0x00000020
		DT_EXPANDTABS               0x00000040
		DT_TABSTOP                  0x00000080
		DT_NOCLIP                   0x00000100
		DT_EXTERNALLEADING          0x00000200
		DT_CALCRECT                 0x00000400
		DT_NOPREFIX                 0x00000800
		DT_INTERNAL                 0x00001000
		*/

		DrawText(hDC,text.c_str(),text.length(),&rect,(UINT)_win_alignment | DT_NOPREFIX);
		//TextOut(hDC,0,0,text.c_str(),text.length());
	}

	Basic::_win_WMPaint();
}


// Interface::Default::Panel::Image
TexProject::Interface::Default::Panel::Image::Image(GUI* interface_,Item* parent_):
	Interface::Panel::Image(interface_,parent_)
{
}
TexProject::Interface::Default::Panel::Image::~Image()
{
	if(image) { delete image; image = nullptr; }
}
void										TexProject::Interface::Default::Panel::Image::SetImage(Texture::D2* texture_)
{
	if(image) { delete image; image = nullptr; }
	if(texture_)
	{
		image = new Windows::Texture(inter->GetWindow());
		*image = *texture_;
	}
}
void										TexProject::Interface::Default::Panel::Image::_win_WMPaint()
{
	auto window = inter->GetWindow();
	auto &hDC = ((Interface::Default*)(inter))->renderDeviceContextHandle;
	auto &rect = ((Interface::Default*)(inter))->renderRect;

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

	{
		float32 border = 1.0f;

		rect.left = LONG(pos_.x - (hsize_.x+border));
		rect.bottom = LONG(pos_.y + (hsize_.y+border));
		rect.right = LONG(pos_.x + (hsize_.x+border));
		rect.top = LONG(pos_.y - (hsize_.y+border));

		SetDCBrushColor(hDC,RGB(color.x*255,color.y*255,color.z*255));

		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));

		/*SelectObject(hDC,(HBRUSH)GetStockObject(WHITE_PEN));
		SelectObject(hDC,(HBRUSH)GetStockObject(GRAY_BRUSH));
		Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);*/
	}

	if(image)
	{
		rect.left = LONG(pos_.x - hsize_.x);
		rect.bottom = LONG(pos_.y + hsize_.y);
		rect.right = LONG(pos_.x + hsize_.x);
		rect.top = LONG(pos_.y - hsize_.y);

		SetStretchBltMode(hDC,STRETCH_HALFTONE);
		StretchDIBits
		(
			hDC,
			rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
			0,0,image->GetSize().x,image->GetSize().y,
			image->textureData,(BITMAPINFO*)&image->infoHeader,
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

	{
		rect.left = LONG(pos_.x - hsize_.x);
		rect.bottom = LONG(pos_.y + hsize_.y);
		rect.right = LONG(pos_.x + hsize_.x);
		rect.top = LONG(pos_.y - hsize_.y);

		SetDCBrushColor(hDC,RGB(color.x*255,color.y*255,color.z*255));

		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
	}

	/*rect.left = LONG(pos_.x - hsize_.x);
	rect.bottom = LONG(pos_.y + hsize_.y);
	rect.right = LONG(pos_.x + hsize_.x);
	rect.top = LONG(pos_.y - hsize_.y);

	SelectObject(hDC,(HPEN)GetStockObject(WHITE_PEN));

	if(IsLocalSelect() && inter->GetPicked() && inter->GetPicked()->GetBase() == GetBase())
	{
		SelectObject(hDC,redBrush);
	}
	else
	{
		SelectObject(hDC,greenBrush);
	}
	Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);*/
}


// Interface::Default::Button::Trigger
TexProject::Interface::Default::Button::Trigger::Trigger(GUI* interface_,Item* parent_):
	Interface::Button::Trigger(interface_,parent_)
{
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

	{
		rect.left = LONG(pos_.x - hsize_.x);
		rect.bottom = LONG(pos_.y + hsize_.y);
		rect.right = LONG(pos_.x + hsize_.x);
		rect.top = LONG(pos_.y - hsize_.y);

		if(state) SetDCBrushColor(hDC,RGB(colorActive.x*255,colorActive.y*255,colorActive.z*255));
		else SetDCBrushColor(hDC,RGB(color.x*255,color.y*255,color.z*255));

		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
	}

	/*rect.left = LONG(pos_.x - hsize_.x);
	rect.bottom = LONG(pos_.y + hsize_.y);
	rect.right = LONG(pos_.x + hsize_.x);
	rect.top = LONG(pos_.y - hsize_.y);

	SelectObject(hDC,(HPEN)GetStockObject(WHITE_PEN));

	if(IsLocalSelect() && inter->GetPicked() && inter->GetPicked()->GetBase() == GetBase())
	{
		SelectObject(hDC,redBrush);
	}
	else
	{
		if(state) SelectObject(hDC,blueBrush);
		else SelectObject(hDC,greenBrush);
	}
	Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);*/
}


// Interface::Default::Button::Slider
TexProject::Interface::Default::Button::Slider::Slider(GUI* interface_,Item* parent_):
	Interface::Button::Slider(interface_,parent_)
{
}
void										TexProject::Interface::Default::Button::Slider::_win_WMPaint()
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

	{	// bordered
		rect.left = LONG(pos_.x - hsize_.x);
		rect.bottom = LONG(pos_.y + hsize_.y);
		rect.right = LONG(pos_.x + hsize_.x);
		rect.top = LONG(pos_.y - hsize_.y);

		/*SelectObject(hDC,(HPEN)GetStockObject(WHITE_PEN));
		SelectObject(hDC,(HBRUSH)GetStockObject(DKGRAY_BRUSH));

		Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);*/
		SetDCBrushColor(hDC,RGB(color.x*255,color.y*255,color.z*255));
		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
	}

	{	// field
		rect.left = LONG(pos_.x - hsize_.x + border.x);
		rect.bottom = LONG(pos_.y + hsize_.y - border.y);
		rect.right = LONG(pos_.x + hsize_.x - border.x);
		rect.top = LONG(pos_.y - hsize_.y + border.y);

		//FillRect(hDC,&rect,(HBRUSH)GetStockObject(GRAY_BRUSH));
		SetDCBrushColor(hDC,RGB(colorInner.x*255,colorInner.y*255,colorInner.z*255));
		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
	}

	{	// slide rail
		rect.left = LONG(pos_.x - hsize_.x + border.x);
		rect.bottom = LONG(pos_.y + 1.0f);
		rect.right = LONG(pos_.x + hsize_.x - border.x);
		rect.top = LONG(pos_.y - 1.0f);

		//FillRect(hDC,&rect,(HBRUSH)GetStockObject(WHITE_BRUSH));
		SetDCBrushColor(hDC,RGB(colorRail.x*255,colorRail.y*255,colorRail.z*255));
		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
	}

	{	// slider
		vec2 tPos = vec2(bezier(pos_.x-hsize_.x+border.x,pos_.x+hsize_.x-border.x,slide),pos_.y);
		rect.left = LONG(tPos.x - 2.0f);
		rect.bottom = LONG(tPos.y + hsize_.y - border.y);
		rect.right = LONG(tPos.x + 2.0f);
		rect.top = LONG(tPos.y - hsize_.y + border.y);

		/*SelectObject(hDC,(HPEN)GetStockObject(WHITE_PEN));
		if(IsLocalSelect() && inter->GetPicked() && inter->GetPicked()->GetBase() == GetBase()) SelectObject(hDC,redBrush);
		else SelectObject(hDC,greenBrush);

		Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);*/
		SetDCBrushColor(hDC,RGB(colorSlider.x*255,colorSlider.y*255,colorSlider.z*255));
		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
	}
}


// Interface::Default::Button::Connector
TexProject::Interface::Default::Button::Connector::Connector(GUI* interface_,Item* parent_):
	Interface::Button::Connector(interface_,parent_)
{
}
void										TexProject::Interface::Default::Button::Connector::_win_WMPaint()
{
	auto &hDC = ((Interface::Default*)(inter))->renderDeviceContextHandle;
	auto &rect = ((Interface::Default*)(inter))->renderRect;
	auto &redBrush = ((Interface::Default*)(inter))->renderBrushRed;
	auto &greenBrush = ((Interface::Default*)(inter))->renderBrushGreen;
	auto &blueBrush = ((Interface::Default*)(inter))->renderBrushBlue;
	auto blackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	auto whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);

	auto pos_ = GetPos();
	auto hsize_ = GetSize()*0.5f;

	if(!parent)
	{	// shadow
		rect.left = LONG(pos_.x - hsize_.x + 4.0f);
		rect.bottom = LONG(pos_.y + hsize_.y + 4.0f);
		rect.right = LONG(pos_.x + hsize_.x + 4.0f);
		rect.top = LONG(pos_.y - hsize_.y + 4.0f);

		FillRect(hDC,&rect,blackBrush);
	}

	{	// field
		rect.left = LONG(pos_.x - hsize_.x);
		rect.bottom = LONG(pos_.y + hsize_.y);
		rect.right = LONG(pos_.x + hsize_.x);
		rect.top = LONG(pos_.y - hsize_.y);

		SelectObject(hDC,(HPEN)GetStockObject(WHITE_PEN));

		if(IsLocalSelect() && inter->GetPicked() && inter->GetPicked()->GetBase() == GetBase()) SelectObject(hDC,whiteBrush);
		else if(recipient)
		{
			if(target) SelectObject(hDC,blueBrush);
			else SelectObject(hDC,redBrush);
		}
		else if(observers.size() > 0) SelectObject(hDC,greenBrush);
		else SelectObject(hDC,blackBrush);

		Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
	}

	{
		if(binder == this && inter->mouse.stateL)
		{
			vec2 t1 = GetPos();
			vec2 t3 = vec2(inter->mouse.pos - inter->GetWindow()->GetPos());
			vec2 t2 = t1 + connectDirection * block(dist(t1,t3)/100.0f,0.0f,1.0f);

			SelectObject(hDC,whiteBrush);
			bezier
			(
				t1,t2,t3,[&hDC](const vec2& a,const vec2& b)
				{
					MoveToEx(hDC,int32(a.x),int32(a.y),NULL); LineTo(hDC,int32(b.x),int32(b.y));
				}
			);
		}
	}

	if(target && target->GetPriority() < GetPriority() )
	{
		vec2 t1 = GetPos();
		vec2 t4 = target->GetPos();
		float32 t = block(dist(t1,t4)/100.0f,0.0f,1.0f);
		vec2 t2 = t1 + connectDirection*t;
		vec2 t3 = t4 + target->connectDirection*t;

		bezier
		(
			t1,t2,t3,t4,[&hDC](const vec2& a,const vec2& b)
			{
				MoveToEx(hDC,int32(a.x),int32(a.y),NULL); LineTo(hDC,int32(b.x),int32(b.y));
			}
		);
	}
	for(auto i: observers)
	{
		if(i && i->GetPriority() < GetPriority())
		{
			vec2 t1 = GetPos();
			vec2 t4 = i->GetPos();
			float32 t = block(dist(t1,t4)/100.0f,0.0f,1.0f);
			vec2 t2 = t1 + connectDirection*t;
			vec2 t3 = t4 + i->connectDirection*t;

			bezier
			(
				t1,t2,t3,t4,[&hDC](const vec2& a,const vec2& b)
				{
					MoveToEx(hDC,int32(a.x),int32(a.y),NULL); LineTo(hDC,int32(b.x),int32(b.y));
				}
			);
		}
	}

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
		case PanelTypes::Text:
		{
			return AddItem<Panel::Text>();
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
		case ButtonTypes::Trigger:
		{
			return AddItem<Button::Trigger>();
		}
		case ButtonTypes::Slider:
		{
			return AddItem<Button::Slider>();
		}
		case ButtonTypes::InputConnector:
		{
			auto i = AddItem<Button::Connector>();
			i->SetRecipient();
			return i;
		}
		case ButtonTypes::OutputConnector:
		{
			auto i = AddItem<Button::Connector>();
			i->UnsetRecipient();
			return i;
		}
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











































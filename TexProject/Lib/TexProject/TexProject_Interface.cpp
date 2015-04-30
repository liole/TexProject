#include "TexProject_Interface.h"
using namespace TexProject;


#include <TexProject/TexProject_Windows.h>


// Interface::Basic
void										TexProject::Interface::Basic::RefreshPicked()
{
	picked = nullptr;

	for(auto i: panel)
	{
		//if(el->Select() && (!picked || el->priority > picked->priority)) picked = el;
		if(i->IsSelect() && (!picked || i->GetPriority() > picked->GetPriority()))
		{
			picked = i;
		}
	}
	/*for(auto i: button)
	{
		//if(el->Select() && (!picked || el->priority > picked->priority)) picked = el;
		if(i->IsSelect() && (!picked))
		{
			picked = i;
		}
	}*/
}
void										TexProject::Interface::Basic::RefreshSelected()
{
	//selected = NULL;
	if(selected)
	{
		if(mouse.stateL)
		{
			//selected->SetPos(selected->GetPos() + MOUSE::_dPos);
			selected->AddPos(vec2(mouse.dPos));
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
			/*bool go = true;

			for(auto i = picked->buttons.begin(); i != picked->buttons.end(); ++i)
			{
				if((*i)->Select()) { go = false; break; }
			}

			if(go)
			{
				selected = picked;
				selected->ToTop();
			}*/
			selected = picked;
			ToTop(selected);
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
	for(auto i: button) Item::DeleteItem((Item*)i);
	button.clear();
	for(auto i: panel) Item::DeleteItem((Item*)i);
	panel.clear();
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

	if(!panel.empty())
	{
		panel.sort([](Item* i1,Item* i2){ return i1->GetPriority() < i2->GetPriority(); });
		top = *panel.rbegin();
	}
	else
	{
		top = nullptr;
	}
	
	//button.sort([](Item* i1,Item* i2){ return i1->GetPriority() > i2->GetPriority(); });

	for(auto i: panel) i->Loop();
	//for(auto i: button) i->Loop();
}

Interface::GUIPanelDefault*					TexProject::Interface::Basic::AddPanelDefault()
{
	return nullptr;
}
Interface::GUIButtonDefault*				TexProject::Interface::Basic::AddButtonDefault()
{
	return nullptr;
}
Interface::GUIButtonTrigger*				TexProject::Interface::Basic::AddButtonTrigger()
{
	return nullptr;
}
Interface::GUIButtonAction*					TexProject::Interface::Basic::AddButtonAction()
{
	return nullptr;
}
Interface::GUIButtonSlider*					TexProject::Interface::Basic::AddButtonSlider()
{
	return nullptr;
}

#if __TEXPROJECT_WIN__
void										TexProject::Interface::Basic::_win_WMPaint(HDC hDC)
{
}
#endif


// Interface::Basic::Item
TexProject::Interface::Item::Item(GUI* interface_):
	Helper::Prio(0),
	Helper::Pos2(vec2(interface_->GetWindow()->GetSize())*0.5f),
	Helper::Size2(vec2(128.0f)),
	inter(interface_)
{
}
TexProject::Interface::Item::~Item()
{
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
}

bool					TexProject::Interface::Item::IsSelect()
{
	return false;
}

#if __TEXPROJECT_WIN__
void					TexProject::Interface::Item::_win_WMPaint()
{
}
#endif


// Interface::Basic::Panel::Basic
TexProject::Interface::Panel::Basic::Basic(GUI* interface_):
	Item(interface_)
{
}
void					TexProject::Interface::Panel::Basic::Create()
{
}
void					TexProject::Interface::Panel::Basic::Delete()
{
}
void					TexProject::Interface::Panel::Basic::Loop()
{
}


// Interface::Basic::Panel::Default
TexProject::Interface::Panel::Default::Default(GUI* interface_):
	Basic(interface_)
{
}


// Interface::Basic::Button::Basic
TexProject::Interface::Button::Basic::Basic(GUI* interface_):
	Item(interface_)
{
}
void					TexProject::Interface::Button::Basic::Create()
{
}
void					TexProject::Interface::Button::Basic::Delete()
{
}
void					TexProject::Interface::Button::Basic::Loop()
{
}




// Interface::Default::Panel::Default
TexProject::Interface::Default::Panel::Default::Default(GUI* interface_):
	Interface::Panel::Default(interface_)
{
}
void										TexProject::Interface::Default::Panel::Default::Create()
{
}
void										TexProject::Interface::Default::Panel::Default::Delete()
{
}
void										TexProject::Interface::Default::Panel::Default::Loop()
{

}
bool										TexProject::Interface::Default::Panel::Default::IsSelect()
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
void										TexProject::Interface::Default::Panel::Default::_win_WMPaint()
{
	auto &hDC = ((Interface::Default*)(inter))->renderDeviceContextHandle;
	auto &rect = ((Interface::Default*)(inter))->renderRect;

	auto pos_ = GetPos();
	auto hsize_ = GetSize()*0.5f;

	rect.left = LONG(pos_.x - hsize_.x);
	rect.bottom = LONG(pos_.y + hsize_.y);
	rect.right = LONG(pos_.x + hsize_.x);
	rect.top = LONG(pos_.y - hsize_.y);

	if(inter->GetSelected() == this)
	{
		FillRect(hDC,&rect,(HBRUSH)GetStockObject(WHITE_BRUSH));
	}
	else
	{
		if(inter->GetPicked() == this)	//IsSelect())
		{
			FillRect(hDC,&rect,(HBRUSH)GetStockObject(LTGRAY_BRUSH));
		}
		else
		{
			FillRect(hDC,&rect,(HBRUSH)GetStockObject(GRAY_BRUSH));
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
}
void										TexProject::Interface::Default::Delete()
{
	Basic::Delete();
}
void										TexProject::Interface::Default::Loop()
{
	Basic::Loop();
}
Interface::GUIPanelDefault*					TexProject::Interface::Default::AddPanelDefault()
{
	return AddPanel<Panel::Default>();
}
Interface::GUIButtonDefault*				TexProject::Interface::Default::AddButtonDefault()
{
	return nullptr;
}
Interface::GUIButtonTrigger*				TexProject::Interface::Default::AddButtonTrigger()
{
	return nullptr;
}
Interface::GUIButtonAction*					TexProject::Interface::Default::AddButtonAction()
{
	return nullptr;
}
Interface::GUIButtonSlider*					TexProject::Interface::Default::AddButtonSlider()
{
	return nullptr;
}

#if __TEXPROJECT_WIN__
void										TexProject::Interface::Default::_win_WMPaint(HDC hDC)
{
	renderDeviceContextHandle = hDC;	//window->wndDeviceContextHandle;
	for(auto i: panel) i->_win_WMPaint();
	for(auto i: button) i->_win_WMPaint();
}
#endif











































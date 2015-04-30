#include "TexProject_Interface.h"
using namespace TexProject;


#include <TexProject/TexProject_Windows.h>


// Interface::Basic
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
	for(auto i: button) i->Loop();
	for(auto i: panel) i->Loop();
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


// Interface::Basic::Item
TexProject::Interface::Item::Item(GUI* interface_):
	inter(interface_)
{
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
	auto hDC = ((Window::Render*)(inter->GetWindow()))->wndDeviceContextHandle;

	Rectangle(hDC,100,200,200,100);
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
	deviceContextHandle = window->wndDeviceContextHandle;

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












































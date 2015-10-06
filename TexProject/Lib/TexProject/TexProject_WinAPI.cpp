#include "TexProject_WinAPI.h"
using namespace TexProject;

#pragma region Test
#pragma endregion

#if __TEXPROJECT_WIN__
#pragma region Render Context
TexProject::WinAPI::RenderContext::RenderContext(Window* window_):
	::RenderContext(window_)
{
	dbSize = window->GetSize();
	dbHDC = CreateCompatibleDC(window->_win_windowDeviceContextHandle);
	dbBitmap = CreateCompatibleBitmap(window->_win_windowDeviceContextHandle,int32(dbSize.x),int32(dbSize.y));
}
TexProject::WinAPI::RenderContext::~RenderContext()
{
	if(dbBitmap)
	{
		DeleteObject(dbBitmap);
		//_win_dbBitmap = NULL;
	}
	if(dbHDC)
	{
		DeleteDC(dbHDC);
		//_win_dbHDC = NULL;
	}
}
TexProject::RenderContext::Type									TexProject::WinAPI::RenderContext::GetType() const
{
	return Type::Default;
}
bool															TexProject::WinAPI::RenderContext::Use()
{
	if(window->IsInit())
	{

#if __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif

		return true;
	}
	return false;
}
void															TexProject::WinAPI::RenderContext::Unuse()
{
}
void															TexProject::WinAPI::RenderContext::Loop()
{
	UpdateWindow(window->_win_windowHandle);
	//SwapBuffers(wndDeviceContextHandle);
	InvalidateRect(window->_win_windowHandle,NULL,TRUE);
}
/*void															TexProject::WinAPI::RenderContext::_win_Paint()
{
	if(dbSize != window->GetSize())
	{
		dbSize = window->GetSize();
		if(dbBitmap)
		{
			DeleteObject(dbBitmap);
			dbBitmap = NULL;
		}
		dbBitmap = CreateCompatibleBitmap(window->_win_windowDeviceContextHandle,int32(dbSize.x),int32(dbSize.y));
		if(dbHDC)
		{
			DeleteDC(dbHDC);
			dbHDC = NULL;
		}
		dbHDC = CreateCompatibleDC(window->_win_windowDeviceContextHandle);
#if __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif
	}

	SetROP2(window->_win_windowDeviceContextHandle,R2_COPYPEN);

	auto hDC = BeginPaint(window->_win_windowHandle,&ps);

	auto hOldBitmap = (HBITMAP)SelectObject(dbHDC,dbBitmap);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = window->size.x;
	rect.bottom = window->size.y;

	SelectObject(dbHDC,WHITE_BRUSH);
	FillRect(dbHDC,&rect,(HBRUSH)GetStockObject(GRAY_BRUSH));
	
	//if(window->renderContext)
	//{
	//	//window->renderContext->_win_WMPaint(window->_win_dbHDC);
	//}

	BitBlt(hDC,0,0,dbSize.x,dbSize.y,dbHDC,0,0,SRCCOPY);

	SelectObject(dbHDC,hOldBitmap);

	ValidateRect(window->_win_windowHandle,NULL);

	EndPaint(window->_win_windowHandle,&ps);
}*/
#pragma endregion
#pragma region GUI
#pragma region Panels
#pragma region Default
TexProject::WinAPI::GUI::Panels::Default::Default(::GUI* gui_,Item* parent_):
	::GUI::Panels::Default(gui_,parent_)
{
}
TexProject::GUI::Panel*						TexProject::WinAPI::GraphicUserInterface::Panels::Default::AddPanel(PanelTypes type_)
{
	switch(type_)
	{
	case TexProject::GraphicUserInterface::PanelTypes::Default: return AddItem<Panels::Default>();
	case TexProject::GraphicUserInterface::PanelTypes::Image: return AddItem<Panels::Image>();
	case TexProject::GraphicUserInterface::PanelTypes::Text: return AddItem<Panels::Text>();
	default: throw Exception();
	}
}
TexProject::GUI::Button*					TexProject::WinAPI::GraphicUserInterface::Panels::Default::AddButton(ButtonTypes type_)
{
	switch(type_)
	{
	case TexProject::GraphicUserInterface::ButtonTypes::Default: return AddItem<Buttons::Default>();
	case TexProject::GraphicUserInterface::ButtonTypes::Trigger: return AddItem<Buttons::Trigger>();
	case TexProject::GraphicUserInterface::ButtonTypes::Switcher: return AddItem<Buttons::Switcher>();
	case TexProject::GraphicUserInterface::ButtonTypes::Slider: return AddItem<Buttons::Slider>();
	case TexProject::GraphicUserInterface::ButtonTypes::Connector: return AddItem<Buttons::Connector>();
	default: throw Exception();
	}
}
void										TexProject::WinAPI::GUI::Panels::Default::_win_Paint()
{
	if(IsVisible())
	{
		auto rc = (WinAPI::RenderContext*)gui->GetRenderContext();
		auto gui_ = (WinAPI::GraphicUserInterface*)gui;
		auto wnd = rc->GetWindow();
		auto &cs = gui->colorScheme;
		auto hDC = rc->dbHDC;

		

		static RECT rect;
		auto pos_ = GetPos();
		auto size_ = GetSize();

		if(IsScrollable() || IsCollapsable() || IsClosable())
		{
			if(!IsCollapsed())
			{
				wnd->_win_RectToWindow(rect,pos_-border,pos_+size_+border);
				SetDCBrushColor(hDC,_win_RGB(cs.colorBack));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
			}
		}
		if(!IsCollapsable() || !IsCollapsed())
		{
			if(IsCollapsable())
			{
				wnd->_win_RectToWindow(rect,vec2(pos_.x-border.x,pos_.y+size_.y),vec2(pos_.x,pos_.y+size_.y+border.x));
				SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
			}
			if(IsClosable())
			{
				wnd->_win_RectToWindow(rect,pos_+size_,pos_+size_+border);
				SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
			}
			if(IsScrollable())
			{
				auto t = (scrollingSize/(scrollingSize + size_))*size_;
				auto l = (size_ - t)*scrollingValue;

				wnd->_win_RectToWindow(rect,pos_+vec2(l.x,-border.y),pos_+vec2(l.x+t.x,0.0f));
				if((properties & (uint32)PropertiesBit::ScrollX) > 0) SetDCBrushColor(hDC,_win_RGB(cs.colorSelect));
				else SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));

				wnd->_win_RectToWindow(rect,pos_+vec2(-border.x,l.y),pos_+vec2(0.0f,l.y+t.y));
				if((properties & (uint32)PropertiesBit::ScrollY) > 0) SetDCBrushColor(hDC,_win_RGB(cs.colorSelect));
				else SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
			}

			wnd->_win_RectToWindow(rect,pos_,pos_+size_);
			SetDCBrushColor(hDC,_win_RGB(color));
			FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));

			if(IsClippable())
			{
				HRGN parentClippingReg = CreateRectRgn(0,0,0,0);
				if(GetClipRgn(hDC,parentClippingReg) != 1)
				{
					DeleteObject(parentClippingReg); parentClippingReg = NULL;
				}

				clippingRegion = CreateRectRgn(rect.left,rect.top,rect.right,rect.bottom);

				if(parentClippingReg) CombineRgn(clippingRegion,clippingRegion,parentClippingReg,RGN_AND);

				SelectClipRgn(hDC,clippingRegion);
				DeleteObject(clippingRegion); clippingRegion = NULL;

				Panel::_win_Paint();

				SelectClipRgn(hDC,parentClippingReg);
				if(parentClippingReg) DeleteObject(parentClippingReg);
			}
			else
			{
				Panel::_win_Paint();
			}

		}
		else
		{
			wnd->_win_RectToWindow(rect,pos_+vec2(-border.x,size.y),pos_+size_+border);
			SetDCBrushColor(hDC,_win_RGB(cs.colorBack));
			FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));

			wnd->_win_RectToWindow(rect,vec2(pos_.x-border.x,pos_.y+size_.y),vec2(pos_.x,pos_.y+size_.y+border.x));
			SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
			FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));

			if(IsClosable())
			{
				wnd->_win_RectToWindow(rect,pos_+size_,pos_+size_+border);
				SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
			}
		}
	}
}
#pragma endregion
#pragma region Image
TexProject::WinAPI::GUI::Panels::Image::Image(::GUI* gui_,Item* parent_):
	::GUI::Panels::Image(gui_,parent_)
{
}
TexProject::WinAPI::GUI::Panels::Image::~Image()
{
	if(image) delete image;
}
void										TexProject::WinAPI::GUI::Panels::Image::SetImage(::Texture::D2* image_)
{
	if(image) { delete image; image = nullptr; }

	if(image_)
	{
		image = new WinAPI::Texture(gui->GetRenderContext());
		*image = *image_;
	}
}
void										TexProject::WinAPI::GUI::Panels::Image::_win_Paint()
{
	if(IsVisible())
	{
		auto rc = (WinAPI::RenderContext*)gui->GetRenderContext();
		auto gui_ = (WinAPI::GraphicUserInterface*)gui;
		auto wnd = rc->GetWindow();
		auto &cs = gui->colorScheme;
		auto hDC = rc->dbHDC;

		static RECT rect;
		auto pos_ = GetPos();
		auto size_ = GetSize();

		wnd->_win_RectToWindow(rect,pos_,pos_+size_);
		SetDCBrushColor(hDC,_win_RGB(color));
		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));

		if(image)
		{
			SetStretchBltMode(hDC,STRETCH_HALFTONE);
			StretchDIBits
			(
				hDC,
				rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,
				0,0,image->GetSize().x,image->GetSize().y,
				image->textureData,(BITMAPINFO*)&image->infoHeader,
				DIB_RGB_COLORS,SRCCOPY
			);
		}
	}
}
#pragma endregion
#pragma region Text
TexProject::WinAPI::GUI::Panels::Text::Text(::GUI* gui_,Item* parent_):
	::GUI::Panels::Text(gui_,parent_)
{
}
void										TexProject::WinAPI::GUI::Panels::Text::_win_Paint()
{
	if(IsVisible())
	{
		auto rc = (WinAPI::RenderContext*)gui->GetRenderContext();
		auto gui_ = (WinAPI::GraphicUserInterface*)gui;
		auto wnd = rc->GetWindow();
		auto &cs = gui->colorScheme;
		auto hDC = rc->dbHDC;

		static RECT rect;
		auto pos_ = GetPos();
		auto size_ = GetSize();

		if(IsScrollable() || IsCollapsable() || IsClosable())	// малювання рамки
		{
			if(!IsCollapsed())
			{
				wnd->_win_RectToWindow(rect,pos_-border,pos_+size_+border);
				SetDCBrushColor(hDC,_win_RGB(cs.colorBack));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
			}
		}
		if(!IsCollapsable() || !IsCollapsed())	// малювання, якщо розгорнута
		{
			if(IsCollapsable())	// малювання кнопки згортання
			{
				wnd->_win_RectToWindow(rect,vec2(pos_.x-border.x,pos_.y+size_.y),vec2(pos_.x,pos_.y+size_.y+border.x));
				SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
			}
			if(IsClosable())	// малювання кнопки закриття
			{
				wnd->_win_RectToWindow(rect,pos_+size_,pos_+size_+border);
				SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
			}
			if(IsScrollable())	// малювання скролбарів
			{
				auto t = (scrollingSize/(scrollingSize + size_))*size_;
				auto l = (size_ - t)*scrollingValue;

				wnd->_win_RectToWindow(rect,pos_+vec2(l.x,-border.y),pos_+vec2(l.x+t.x,0.0f));
				if((properties & (uint32)Item::PropertiesBit::ScrollX) > 0) SetDCBrushColor(hDC,_win_RGB(cs.colorSelect));
				else SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));

				wnd->_win_RectToWindow(rect,pos_+vec2(-border.x,l.y),pos_+vec2(0.0f,l.y+t.y));
				if((properties & (uint32)Item::PropertiesBit::ScrollY) > 0) SetDCBrushColor(hDC,_win_RGB(cs.colorSelect));
				else SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
			}

			// малювання панелі
			/*wnd->_win_RectToWindow(rect,pos_,pos_+size_);
			SetDCBrushColor(hDC,_win_RGB(color));
			FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));*/

			{
				wnd->_win_RectToWindow(rect,pos_,pos_ + size_);

				SetTextColor(hDC,RGB(color.x * 255,color.y * 255,color.z * 255));

				//SetBkColor(hDC,RGB(0,255,0));
				SetBkMode(hDC,TRANSPARENT);	// OPAQUE, TRANSPARENT

				DrawText(hDC,text.c_str(),text.length(),&rect,DT_CENTER | DT_NOPREFIX);
			}

			// весь розмір = size_ + scrollingSize
			// лівий нижній кут квадрату = scrollingSize*scrollingValue

			/* твій код тут */

			Panel::_win_Paint();
		}
		else
		{
			wnd->_win_RectToWindow(rect,pos_+vec2(-border.x,size.y),pos_+size_+border);
			SetDCBrushColor(hDC,_win_RGB(cs.colorBack));
			FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));

			wnd->_win_RectToWindow(rect,vec2(pos_.x-border.x,pos_.y+size_.y),vec2(pos_.x,pos_.y+size_.y+border.x));
			SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
			FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));

			if(IsClosable())
			{
				wnd->_win_RectToWindow(rect,pos_+size_,pos_+size_+border);
				SetDCBrushColor(hDC,_win_RGB(cs.colorSlider));
				FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
			}
		}
	}
}
#pragma endregion
#pragma endregion
#pragma region Buttons
#pragma region Default
TexProject::WinAPI::GUI::Buttons::Default::Default(::GUI* gui_,Item* parent_):
	::GUI::Buttons::Default(gui_,parent_)
{
}
void										TexProject::WinAPI::GUI::Buttons::Default::_win_Paint()
{
	if(IsVisible())
	{
		auto rc = (WinAPI::RenderContext*)gui->GetRenderContext();
		auto gui_ = (WinAPI::GraphicUserInterface*)gui;
		auto wnd = rc->GetWindow();
		auto &cs = gui->colorScheme;
		auto hDC = rc->dbHDC;

		static RECT rect;
		auto pos_ = GetPos();
		auto size_ = GetSize();

		wnd->_win_RectToWindow(rect,pos_,pos_+size_);
		SetDCBrushColor(hDC,_win_RGB(color));
		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
	}
}
#pragma endregion
#pragma region Trigger
TexProject::WinAPI::GUI::Buttons::Trigger::Trigger(::GUI* gui_,Item* parent_):
	::GUI::Buttons::Trigger(gui_,parent_)
{
}
void										TexProject::WinAPI::GUI::Buttons::Trigger::_win_Paint()
{
	if(IsVisible())
	{
		auto rc = (WinAPI::RenderContext*)gui->GetRenderContext();
		auto gui_ = (WinAPI::GraphicUserInterface*)gui;
		auto wnd = rc->GetWindow();
		auto &cs = gui->colorScheme;
		auto hDC = rc->dbHDC;

		static RECT rect;
		auto pos_ = GetPos();
		auto size_ = GetSize();

		wnd->_win_RectToWindow(rect,pos_,pos_+size_);
		if(state) SetDCBrushColor(hDC,_win_RGB(vec4(1,0,0,1)));
		else SetDCBrushColor(hDC,_win_RGB(color));
		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
	}
}
#pragma endregion
#pragma region Switcher
TexProject::WinAPI::GUI::Buttons::Switcher::Switcher(::GUI* gui_,Item* parent_):
	::GUI::Buttons::Switcher(gui_,parent_)
{
}
void										TexProject::WinAPI::GUI::Buttons::Switcher::_win_Paint()
{
	if(IsVisible())
	{
		auto rc = (WinAPI::RenderContext*)gui->GetRenderContext();
		auto gui_ = (WinAPI::GraphicUserInterface*)gui;
		auto wnd = rc->GetWindow();
		auto &cs = gui->colorScheme;
		auto hDC = rc->dbHDC;

		static RECT rect;
		auto pos_ = GetPos();
		auto size_ = GetSize();

		auto t = pos_+size_;
		for(uint32 i = 0; i < maxState; ++i)
		{
			float32 di = float32(i)/float32(maxState);
			float32 ndi = float32(i+1)/float32(maxState);
			wnd->_win_RectToWindow(rect,vec2(pos_.x,bezier(pos_.y,t.y,di)) + 2.0f,vec2(t.x,bezier(pos_.y,t.y,ndi)) - 2.0f);
			if(i == state) SetDCBrushColor(hDC,_win_RGB(vec4(1,0,0,1)));
			else SetDCBrushColor(hDC,_win_RGB(color));
			FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
		}
	}
}
#pragma endregion
#pragma region Slider
TexProject::WinAPI::GUI::Buttons::Slider::Slider(::GUI* gui_,Item* parent_):
	::GUI::Buttons::Slider(gui_,parent_)
{
}
void										TexProject::WinAPI::GUI::Buttons::Slider::_win_Paint()
{
	if(IsVisible())
	{
		auto rc = (WinAPI::RenderContext*)gui->GetRenderContext();
		auto gui_ = (WinAPI::GraphicUserInterface*)gui;
		auto wnd = rc->GetWindow();
		auto &cs = gui->colorScheme;
		auto hDC = rc->dbHDC;

		static RECT rect;
		auto pos_ = GetPos();
		auto size_ = GetSize();

		wnd->_win_RectToWindow(rect,pos_,pos_+size_);
		SetDCBrushColor(hDC,_win_RGB(color));
		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));

		wnd->_win_RectToWindow(rect,vec2(bezier(pos_.x,pos_.x+size_.y-1.0f,value),pos_.y),vec2(bezier(pos_.x+1.0f,pos_.x+size_.y,value),pos_.y+size_.y));
		SetDCBrushColor(hDC,_win_RGB(vec4(1,0,0,1)));
		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));
	}
}
#pragma endregion
#pragma region Connector
TexProject::WinAPI::GUI::Buttons::Connector::Connector(::GUI* gui_,Item* parent_):
	::GUI::Buttons::Connector(gui_,parent_)
{
}
void										TexProject::WinAPI::GUI::Buttons::Connector::_win_Paint()
{
	if(IsVisible())
	{
		auto rc = (WinAPI::RenderContext*)gui->GetRenderContext();
		auto gui_ = (WinAPI::GraphicUserInterface*)gui;
		auto wnd = rc->GetWindow();
		auto &cs = gui->colorScheme;
		auto hDC = rc->dbHDC;

		static RECT rect;
		auto pos_ = GetPos();
		auto size_ = GetSize();

		wnd->_win_RectToWindow(rect,pos_,pos_+size_);
		if(IsRecipient())
		{
			if(target) SetDCBrushColor(hDC,_win_RGB(vec4(0,0,1,1)));
			else SetDCBrushColor(hDC,_win_RGB(vec4(1,0,0,1)));
		}
		else
		{
			if(observers.empty()) SetDCBrushColor(hDC,_win_RGB(vec4(0,0,0,1)));
			else SetDCBrushColor(hDC,_win_RGB(vec4(0,1,0,1)));
		}
		FillRect(hDC,&rect,(HBRUSH)GetStockObject(DC_BRUSH));

		HRGN clippingRegion = CreateRectRgn(0,0,0,0);
		if(GetClipRgn(hDC,clippingRegion) != 1)
		{
			DeleteObject(clippingRegion); clippingRegion = NULL;
		}

		SelectClipRgn(hDC,NULL);

		//SetDCBrushColor(hDC,RGB(255,125,0));
		//SelectObject(hDC,(HBRUSH)GetStockObject(DC_BRUSH));
		SetDCPenColor(hDC,RGB(255,125,0));
		SelectObject(hDC,(HPEN)GetStockObject(DC_PEN));
		{
			if(binder && gui_->mouse.lstate)
			{
				vec2 t1 = GetPos() + GetSize()*0.5f;
				vec2 t3 = vec2(gui_->mouse.pos - wnd->GetPos());
				vec2 t2 = t1 + direction * block(dist(t1,t3)/100.0f,0.0f,1.0f);

				bezier
				(
					t1,t2,t3,[&hDC,wnd](const vec2& a,const vec2& b)
					{
						auto p1 = vec2(a.x,wnd->GetSize().y - a.y);	//wnd->ToWindowSpace(a);
						auto p2 = vec2(b.x,wnd->GetSize().y - b.y);	//wnd->ToWindowSpace(b);
						MoveToEx(hDC,int32(p1.x),int32(p1.y),NULL);
						LineTo(hDC,int32(p2.x),int32(p2.y));
					}
				);
			}
		}
		if(target && !(*this < *target))
		{
			vec2 t1 = GetPos() + GetSize()*0.5f;
			vec2 t4 = target->GetPos() + target->GetSize()*0.5f;
			float32 t = block(dist(t1,t4)/100.0f,0.0f,1.0f);
			vec2 t2 = t1 + direction*t;
			vec2 t3 = t4 + target->direction*t;
			bezier
			(
				t1,t2,t3,t4,[&hDC,wnd](const vec2& a,const vec2& b)
				{
					auto p1 = vec2(a.x,wnd->GetSize().y - a.y);	//wnd->ToWindowSpace(a);
					auto p2 = vec2(b.x,wnd->GetSize().y - b.y);	//wnd->ToWindowSpace(b);
					MoveToEx(hDC,int32(p1.x),int32(p1.y),NULL);
					LineTo(hDC,int32(p2.x),int32(p2.y));
				}
			);
		}
		for(auto i: observers)
		{
			if(i && !(*this < *i))
			{
				vec2 t1 = GetPos() + GetSize()*0.5f;
				vec2 t4 = i->GetPos() + i->GetSize()*0.5f;
				float32 t = block(dist(t1,t4)/100.0f,0.0f,1.0f);
				vec2 t2 = t1 + direction*t;
				vec2 t3 = t4 + i->direction*t;

				bezier
				(
					t1,t2,t3,t4,[&hDC,wnd](const vec2& a,const vec2& b)
					{
						auto p1 = vec2(a.x,wnd->GetSize().y - a.y);	//wnd->ToWindowSpace(a);
						auto p2 = vec2(b.x,wnd->GetSize().y - b.y);	//wnd->ToWindowSpace(b);
						MoveToEx(hDC,int32(p1.x),int32(p1.y),NULL);
						LineTo(hDC,int32(p2.x),int32(p2.y));
					}
				);
			}
		}

		SelectClipRgn(hDC,clippingRegion);
		DeleteObject(clippingRegion);
	}
}
#pragma endregion
#pragma endregion
#pragma region GUI
#pragma region Basic
TexProject::WinAPI::GraphicUserInterface::GraphicUserInterface(::RenderContext* renderContext_):
	::GraphicUserInterface(renderContext_)
{
}
TexProject::GUI::Panel*						TexProject::WinAPI::GraphicUserInterface::AddPanel(PanelTypes type_)
{
	switch(type_)
	{
	case TexProject::GraphicUserInterface::PanelTypes::Default: return AddItem<Panels::Default>();
	case TexProject::GraphicUserInterface::PanelTypes::Image: return AddItem<Panels::Image>();
	case TexProject::GraphicUserInterface::PanelTypes::Text: return AddItem<Panels::Text>();
	default: throw Exception();
	}
}
TexProject::GUI::Button*					TexProject::WinAPI::GraphicUserInterface::AddButton(ButtonTypes type_)
{
	switch(type_)
	{
	case TexProject::GraphicUserInterface::ButtonTypes::Default: return AddItem<Buttons::Default>();
	case TexProject::GraphicUserInterface::ButtonTypes::Trigger: return AddItem<Buttons::Trigger>();
	case TexProject::GraphicUserInterface::ButtonTypes::Switcher: return AddItem<Buttons::Switcher>();
	case TexProject::GraphicUserInterface::ButtonTypes::Slider: return AddItem<Buttons::Slider>();
	case TexProject::GraphicUserInterface::ButtonTypes::Connector: return AddItem<Buttons::Connector>();
	default: throw Exception();
	}
}
#pragma endregion
#pragma endregion
#pragma endregion
#endif
#pragma region Platform-Dependent
#if __TEXPROJECT_WIN__
void										TexProject::WinAPI::GraphicUserInterface::_win_Paint()
{
	auto rc = (WinAPI::RenderContext*)renderContext;
	rc->_win_BeginPaint();

	for(auto i: item)
	{
		i->_win_Paint();
	}

	rc->_win_EndPaint();
}
#endif
#pragma endregion

































#pragma once
#pragma region TexProject Includes
#include <TexProject/TexProject_Header.h>

#include <TexProject/TexProject_Windows.h>
#include <TexProject/TexProject_Textures.h>
#include <TexProject/TexProject_GUI.h>
#pragma endregion
#pragma region Includes

#include <Windows.h>
#include <time.h>
#pragma endregion


#pragma region Test
#pragma endregion


#if __TEXPROJECT_WIN__
namespace TexProject
{
	namespace WinAPI		
	{
		inline COLORREF			_win_RGB(const vec4& color_);
		class ContextBind
		{
		protected:
			RenderContext*const									renderContext;
		public:
			inline												ContextBind(Window* window_);
			inline												ContextBind(::RenderContext* renderContext_);
			inline RenderContext*								GetRenderContext() const;
		};
		class RenderContext:
			public ::RenderContext
		{
#pragma region Basic
			friend Window;
			friend GraphicUserInterface;
		protected:
			uvec2							dbSize = uvec2(0);
			HDC								dbHDC = NULL;
			HBITMAP							dbBitmap = NULL;
			HDC								oldDC = NULL;
			HBITMAP							oldBitmap = NULL;
			PAINTSTRUCT						ps;
		protected:
			virtual bool					Use() override;
			virtual void					Unuse() override;
			virtual void					Loop() override;
		public:
											RenderContext(Window* window_);
			virtual							~RenderContext();
			virtual Type					GetType() const override;
#pragma endregion
#pragma region _win_Paint
		protected:
			inline void						_win_BeginPaint();
			inline void						_win_EndPaint();
#pragma endregion
		};
		class GraphicUserInterface:
			public ::GraphicUserInterface
		{
			friend Window;
#pragma region Items
		protected:
			friend Texture;
		protected:
			class Panels
			{
			public:
				class Default:
					public ::GUI::Panels::Default
				{
					friend ::GraphicUserInterface;
					friend GraphicUserInterface;
				protected:
					HRGN					clippingRegion = NULL;
				protected:
											Default(::GUI* gui_,Item* parent_ = nullptr);
					virtual					~Default() = default;
					virtual Panel*			AddPanel(PanelTypes type_) override;
					virtual Button*			AddButton(ButtonTypes type_) override;
					virtual void			_win_Paint() override;
				};
				class Image:
					public ::GUI::Panels::Image
				{
					friend ::GraphicUserInterface;
					friend GraphicUserInterface;
				protected:
					Texture*				image = nullptr;
				protected:
											Image(::GUI* gui_,Item* parent_ = nullptr);
					virtual					~Image();
					virtual void			SetImage(::Texture::D2* image_) override;
					virtual void			_win_Paint() override;
				};
				class Text:
					public ::GUI::Panels::Text
				{
					friend ::GraphicUserInterface;
					friend GraphicUserInterface;
				protected:
				protected:
											Text(::GUI* gui_,Item* parent_ = nullptr);
					virtual					~Text() = default;
					virtual void			_win_Paint() override;
				};
			protected:
				Panels();
			};
			class Buttons
			{
			public:
				class Default:
					public ::GUI::Buttons::Default
				{
					friend ::GraphicUserInterface;
					friend GraphicUserInterface;
				protected:
											Default(::GUI* gui_,Item* parent_ = nullptr);
					virtual					~Default() = default;
					virtual void			_win_Paint() override;
				};
				class Trigger:
					public ::GUI::Buttons::Trigger
				{
					friend ::GraphicUserInterface;
					friend GraphicUserInterface;
				protected:
											Trigger(::GUI* gui_,Item* parent_ = nullptr);
					virtual					~Trigger() = default;
					virtual void			_win_Paint() override;
				};
				class Switcher:
					public ::GUI::Buttons::Switcher
				{
					friend ::GraphicUserInterface;
					friend GraphicUserInterface;
				protected:
											Switcher(::GUI* gui_,Item* parent_ = nullptr);
					virtual					~Switcher() = default;
					virtual void			_win_Paint() override;
				};
				class Slider:
					public ::GUI::Buttons::Slider
				{
					friend ::GraphicUserInterface;
					friend GraphicUserInterface;
				protected:
											Slider(::GUI* gui_,Item* parent_ = nullptr);
					virtual					~Slider() = default;
					virtual void			_win_Paint() override;
				};
				class Connector:
					public ::GUI::Buttons::Connector
				{
					friend ::GraphicUserInterface;
					friend GraphicUserInterface;
				protected:
											Connector(::GUI* gui_,Item* parent_ = nullptr);
					virtual					~Connector() = default;
					virtual void			_win_Paint() override;
				};
			};
			friend Panels::Default;
			friend Panels::Image;
			friend Panels::Text;
			friend Buttons::Default;
			friend Buttons::Trigger;
			friend Buttons::Switcher;
			friend Buttons::Slider;
			friend Buttons::Connector;
#pragma endregion
#pragma region Basic
		protected:
												GraphicUserInterface(::RenderContext* renderContext_);
			virtual								~GraphicUserInterface() = default;
#pragma endregion
#pragma region Items Processing
			virtual Panel*						AddPanel(PanelTypes type_) override;
			virtual Button*						AddButton(ButtonTypes type_) override;
#pragma endregion
#pragma region Platform-Dependent
#if __TEXPROJECT_WIN__
			virtual void					_win_Paint() override;
#endif
#pragma endregion

		};
		class Texture:
			public ContextBind
		{
			friend GUI::Panels::Image;
		protected:

			uvec2												size = uvec2(0);
			uint32												bitCount = 32;
			uint32												bytesPerLine = 0;
			HBITMAP												bitmap = NULL;
			BITMAPINFOHEADER									infoHeader;
			BYTE*												textureData = nullptr;

		public:

			inline Texture(Window* window);
			inline Texture(::RenderContext* renderContext_);
			inline ~Texture();

			inline Texture&										operator = (const TexProject::Texture::D2& source);

			inline bool											Create(uvec2 size_,vec4* data_);
			inline void											Delete();

			inline uvec2										GetSize() const;
		};
	}
}


inline COLORREF								TexProject::WinAPI::_win_RGB(const vec4& color_)
{
	return RGB(color_.x*255,color_.y*255,color_.z*255);
}
#pragma region ContextBind
inline															TexProject::WinAPI::ContextBind::ContextBind(Window* window_):
	renderContext
	(
		window_->GetRenderContext()->GetType() == RenderContext::Type::Default ?
		(RenderContext*)window_->GetRenderContext() :
		throw Exception()
	)
{
}
inline															TexProject::WinAPI::ContextBind::ContextBind(::RenderContext* renderContext_):
	renderContext
	(
		renderContext_->GetType() == RenderContext::Type::Default ?
		(RenderContext*)renderContext_ :
		throw Exception()
	)
{
}
inline TexProject::WinAPI::RenderContext*						TexProject::WinAPI::ContextBind::GetRenderContext() const
{
	return renderContext;
}
#pragma endregion
#pragma region RenderContext
#pragma region _win_Paint
inline void						TexProject::WinAPI::RenderContext::_win_BeginPaint()
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

	oldDC = BeginPaint(window->_win_windowHandle,&ps);

	oldBitmap = (HBITMAP)SelectObject(dbHDC,dbBitmap);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = window->size.x;
	rect.bottom = window->size.y;

	SelectObject(dbHDC,WHITE_BRUSH);
	FillRect(dbHDC,&rect,(HBRUSH)GetStockObject(GRAY_BRUSH));
}
inline void						TexProject::WinAPI::RenderContext::_win_EndPaint()
{
	BitBlt(oldDC,0,0,dbSize.x,dbSize.y,dbHDC,0,0,SRCCOPY);

	SelectObject(dbHDC,oldBitmap);

	ValidateRect(window->_win_windowHandle,NULL);

	EndPaint(window->_win_windowHandle,&ps);
}
#pragma endregion
#pragma endregion
#pragma region Texture
inline										TexProject::WinAPI::Texture::Texture(Window* window):
	ContextBind(window)
{
}
inline										TexProject::WinAPI::Texture::Texture(::RenderContext* renderContext_):
	ContextBind(renderContext_)
{
}
inline										TexProject::WinAPI::Texture::~Texture()
{
	Delete();
}
inline TexProject::WinAPI::Texture&			TexProject::WinAPI::Texture::operator = (const TexProject::Texture::D2& source)
{
	auto data_ = source.GetData();
	Create(source.GetSize(),data_);
	delete[] data_;
	return *this;
}
inline bool									TexProject::WinAPI::Texture::Create(uvec2 size_,vec4* data_)
{
	Delete();
	{
		size = size_;
		bitCount = 32;
		bytesPerLine = ((size.x * bitCount + 31)/32) * 4;
	}
	{
		infoHeader.biSize = sizeof(BITMAPINFOHEADER);
		infoHeader.biWidth = size.x;
		infoHeader.biHeight = size.y;
		infoHeader.biPlanes = 1;
		infoHeader.biBitCount = 32;
		infoHeader.biCompression = BI_RGB;
		infoHeader.biSizeImage = 0; //for BI_RGB
		infoHeader.biXPelsPerMeter = 0;
		infoHeader.biYPelsPerMeter = 0;
		infoHeader.biClrUsed = 0;
		infoHeader.biClrImportant = 0;
	}
	{
		textureData = new BYTE[bytesPerLine*size.y];
		for(uint32 x = 0; x < size.x; ++x)
		for(uint32 y = 0; y < size.y; ++y)
		{
			uint32 id1 = (y*bytesPerLine + x*4);
			uint32 id2 = y*size_.x + x;
			textureData[id1+0] = BYTE(data_[id2].z*255.0f);
			textureData[id1+1] = BYTE(data_[id2].y*255.0f);
			textureData[id1+2] = BYTE(data_[id2].x*255.0f);
			textureData[id1+3] = BYTE(data_[id2].w*255.0f);
		}
	}

	//bitmap = CreateBitmap(size.x,size.y,1,bitCount,textureData);

	return true;//bitmap != NULL;
}
inline void									TexProject::WinAPI::Texture::Delete()
{
	if(textureData)
	{
		delete[] textureData;
		textureData = nullptr;
	}
	if(bitmap)
	{
		//delete bitmap
		bitmap = NULL;
	}
}
inline TexProject::uvec2					TexProject::WinAPI::Texture::GetSize() const
{
	return size;
}
#pragma endregion
#endif

















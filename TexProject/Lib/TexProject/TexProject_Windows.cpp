#include "TexProject_Windows.h"
using namespace TexProject;


#if __TEXPROJECT_WIN__
#include <TexProject/TexProject_WinAPI.h>
#endif
#if __TEXPROJECT_OPENGL__
#include <TexProject/TexProject_OpenGL.h>
#endif


#pragma region RenderContext
bool															TexProject::RenderContext::Use()
{
	return false;
}
void															TexProject::RenderContext::Unuse()
{
}
void															TexProject::RenderContext::Loop()
{
}
#pragma endregion
#pragma region Window
#pragma region Input
TexProject::Input							TexProject::Window::input;
#pragma endregion
#pragma region Platform-Dependent
#if __TEXPROJECT_WIN__
TexProject::Window::_win_StaticData								TexProject::Window::_win_staticData;
LRESULT CALLBACK												TexProject::Window::_win_StaticData::CallbackDefault(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	auto window = (Window*)GetWindowLongPtr(hWnd,GWLP_USERDATA);

	switch(msg)
	{
		case WM_PAINT:
		{			
			if(window)
			{
				//if(window->renderContext) window->renderContext->_win_Paint();
				if(window->gui) window->gui->_win_Paint();
			}
			else
			{
				ValidateRect(hWnd,NULL);
			}
			DefWindowProc(hWnd,msg,wParam,lParam); //return 0;
		}
		case WM_ERASEBKGND:
		{
			return 1; // Say we handled it.
		}
		case WM_CLOSE:
		{
			window->running = false;
			return 0;
		}
		case WM_QUIT:
		{
			window->running = false;
			return 0;
		}
		case WM_DESTROY:
		{
			window->running = false;
			return 0;
		}
		default:
		{
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
	}

	return 0;
}
#endif
#pragma endregion
#pragma region Create/Delete/Loop
void															TexProject::Window::Loop()
{
#if __TEXPROJECT_WIN__
	{
		static MSG msg;
		while(running && PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
#endif
	if(init)
	{
		if(running)
		{
#if __TEXPROJECT_WIN__
			{
				RECT rect;
				GetClientRect(_win_windowHandle,&rect);
				size.x = (uint32)rect.right;
				size.y = (uint32)rect.bottom;

				POINT p;
				p.x = 0;
				p.y = (LONG)size.y;
				ClientToScreen(_win_windowHandle,&p);
				pos = ivec2(FromDesktopSpace(vec2((float32)p.x,(float32)p.y)));
			}

			if(GetFocus() == _win_windowHandle)
			{
				active = true;
			}
			else
			{
				active = false;
			}
#endif

			if(gui)
			{
				gui->Loop();
			}

			if(renderContext && renderContext->Use())
			{
				if( vSync )
				{
					while( difftime((vSyncTimer = clock()),oVSyncTimer) < 1.0/60.0f );
					oVSyncTimer = vSyncTimer;
				}
				{
					CallFunc(FuncType::Loop);
					renderContext->Loop();
				}
				renderContext->Unuse();
			}
		}
		else
		{
			Delete();
		}
#if __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif
	}
}
#pragma endregion
#pragma region RenderContext
void															TexProject::Window::SetRenderContext(RenderContext::Type type_)
{
	if(gui)
	{
		delete gui;
		gui = nullptr;
	}
	if(renderContext)
	{
		if(renderContext->Use())
		{
			CallFunc(FuncType::Free);
			renderContext->Unuse();
		}
		delete renderContext; renderContext = nullptr;
	}

	switch(type_)
	{
	case TexProject::RenderContext::Type::Default:
	{
		renderContext = new RenderContexts::Default(this);
		gui = new GraphicUserInterfaces::Default(renderContext);
	}
	break;
#if __TEXPROJECT_OPENGL__
	case TexProject::RenderContext::Type::OpenGL:
	{
		renderContext = new OpenGL::RenderContext(this);
	}
	break;
#endif
#if __TEXPROJECT_DIRECT3D__
	case TexProject::RenderContext::Type::Direct3D:
	{
		throw Exception();
	}
	break;
#endif
	default:
	{
		throw Exception();
	}
	break;
	}

	if(init && renderContext && renderContext->Use())
	{
		CallFunc(FuncType::Init);
		renderContext->Unuse();
	}
}
#pragma endregion
#pragma endregion
































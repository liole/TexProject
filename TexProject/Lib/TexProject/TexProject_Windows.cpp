#include "TexProject_Windows.h"
using namespace TexProject;


// Window
void					TexProject::Window::Init()
{
	Window::Main::Init();
}
void					TexProject::Window::Free()
{
	Window::Main::Free();
}
void					TexProject::Window::Process()
{
	for(auto i = 0; i < Window::Basic::GetCount(); ++i)
	{
		auto window = Window::Basic::Get(i);
		window->Loop();
	}
}


// Window::Window::Default
string					TexProject::Window::Main::wndClassName = "[Window::Main] Class";
WNDCLASSEX				TexProject::Window::Main::wndClassEx;
LRESULT CALLBACK		TexProject::Window::Main::callbackDefault(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	auto window = (Main*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	switch(msg)
	{
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
			//PostQuitMessage(0);
			return 0;
		}
		default:
		{
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
	}

	return 0;
}

void					TexProject::Window::Main::Init()
{
	{
		wndClassEx.cbSize			= sizeof(wndClassEx);
		wndClassEx.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		/*
		CS_BYTEALIGNCLIENT
		CS_BYTEALIGNWINDOW
		CS_CLASSDC
		CS_DBLCLKS
		CS_DROPSHADOW
		CS_GLOBALCLASS
		CS_HREDRAW
		CS_NOCLOSE
		CS_OWNDC
		CS_PARENTDC
		CS_SAVEBITS
		CS_VREDRAW
		*/
		wndClassEx.lpfnWndProc		= callbackDefault;//WndProc_Default;
		wndClassEx.cbClsExtra		= 0;
		wndClassEx.cbWndExtra		= 0;
		wndClassEx.hInstance		= EntryPointData::hInstance;
		wndClassEx.hIcon			= LoadIcon(NULL,IDI_APPLICATION);
		wndClassEx.hCursor			= LoadCursor(NULL,IDC_ARROW);
		wndClassEx.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//NULL_BRUSH;//GetStockObject(NULL_BRUSH);//WHITE_BRUSH);
		wndClassEx.lpszMenuName		= NULL;
		wndClassEx.lpszClassName	= wndClassName.c_str();	//wndClassName.c_str(),
		wndClassEx.hIconSm			= LoadIcon(NULL,IDI_APPLICATION);
	}

	if(!RegisterClassEx(&wndClassEx))
	{
		Message("Failed To register window class.");
		return;
	}
}
void					TexProject::Window::Main::Free()
{
	UnregisterClass(wndClassName.c_str(), EntryPointData::hInstance);
}


void					TexProject::Window::Main::Create()
{
#ifdef __TEXPROJECT_DEBUG__
	if(!EntryPointData::init)
	{
		Error("Creating a window before entry point.");
	}
#endif

	Delete();

	{
		pos = ivec2(500, 200);
		size = uvec2(400, 300);
		title = "window";
	}

	{
		wndStyle	= WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;
		/*
		WS_BORDER
		WS_CAPTION
		WS_CHILD
		WS_CHILDWINDOW
		WS_CLIPCHILDREN
		WS_CLIPSIBLINGS
		WS_DISABLED
		WS_DLGFRAME
		WS_GROUP
		WS_HSCROLL
		WS_ICONIC
		WS_MAXIMIZE
		WS_MAXIMIZEBOX
		WS_MINIMIZE
		WS_MINIMIZEBOX
		WS_OVERLAPPED
		WS_OVERLAPPEDWINDOW		// (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
		WS_POPUP				// Без рамки
		WS_POPUPWINDOW			// (WS_POPUP | WS_BORDER | WS_SYSMENU)
		WS_SIZEBOX
		WS_SYSMENU
		WS_TABSTOP
		WS_THICKFRAME
		WS_TILED
		WS_TILEDWINDOW			// (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
		WS_VISIBLE
		WS_VSCROLL
		*/
		wndExStyle	= WS_EX_APPWINDOW | WS_EX_TOOLWINDOW;
		/*
		WS_EX_ACCEPTFILES
		WS_EX_APPWINDOW
		WS_EX_CLIENTEDGE
		WS_EX_COMPOSITED
		WS_EX_CONTEXTHELP			// WS_EX_CONTEXTHELP cannot be used with the WS_MAXIMIZEBOX or WS_MINIMIZEBOX styles.
		WS_EX_CONTROLPARENT
		WS_EX_DLGMODALFRAME
		WS_EX_LAYERED
		WS_EX_LAYOUTRTL
		WS_EX_LEFT
		WS_EX_LEFTSCROLLBAR
		WS_EX_LTRREADING
		WS_EX_MDICHILD
		WS_EX_NOACTIVATE
		WS_EX_NOINHERITLAYOUT
		WS_EX_NOPARENTNOTIFY
		WS_EX_NOREDIRECTIONBITMAP
		WS_EX_OVERLAPPEDWINDOW		// (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
		WS_EX_PALETTEWINDOW			// (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)
		WS_EX_RIGHT
		WS_EX_RIGHTSCROLLBAR
		WS_EX_RTLREADING
		WS_EX_STATICEDGE
		WS_EX_TOOLWINDOW
		WS_EX_TOPMOST
		WS_EX_TRANSPARENT
		WS_EX_WINDOWEDGE
		*/
	}

	{
		wndRect.left	= (long)(pos.x);
		wndRect.right	= (long)(pos.x + size.x);
		wndRect.top		= (long)(pos.y);
		wndRect.bottom	= (long)(pos.y + size.y);
	}
	
	AdjustWindowRectEx(&wndRect,wndStyle,FALSE,wndExStyle);

	wndHandle =	CreateWindowEx
	(
		wndExStyle,
		wndClassName.c_str(),
		title.c_str(),
		wndStyle,
		wndRect.left,
		wndRect.top,
		wndRect.right - wndRect.left,
		wndRect.bottom - wndRect.top,
		(HWND)NULL,
		(HMENU)NULL,
		wndClassEx.hInstance,
		NULL
	);

	if(!wndHandle)
	{
		Message("Can't create window.");
		return;
	}

	SetWindowLongPtr(wndHandle, GWLP_USERDATA, (LONG)this);
	/*
	GWL_EXSTYLE
	GWLP_HINSTANCE
	GWLP_ID
	GWL_STYLE
	GWLP_USERDATA
	GWLP_WNDPROC
	*/

	ShowWindow(wndHandle, SW_SHOW);
	SetFocus(wndHandle);

	init = true;
	running = true;

}
void					TexProject::Window::Main::Delete()
{
	if(init)
	{
		if(wndHandle)
		{
			DestroyWindow(wndHandle);
			wndHandle = 0;
		}

		init = false;
	}
}
void					TexProject::Window::Main::Loop()
{
	{
		static MSG msg;
		while(running && PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if(!running)
	{
		Delete();
	}
}































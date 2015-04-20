#include "TexProject_Windows.h"
using namespace TexProject;


// Window
void					TexProject::Window::Init()
{
	Window::Main::Init();
	Window::Input::Init();
}
void					TexProject::Window::Free()
{
	Window::Input::Free();
	Window::Main::Free();
}
void					TexProject::Window::Process()
{
	Window::Input::Loop();

	for(uint32 i = 0; i < Window::Basic::GetCount(); ++i)
	{
		auto window = Window::Basic::Get(i);
		window->Loop();
	}
}


// Window::Input
bool					Window::Input::Init()
{
	if( !Keyboard::Init() ) return false;
	return true;
}
void					Window::Input::Loop()
{
	Keyboard::Loop();
}
void					Window::Input::Free()
{
	Keyboard::Free();
}
void					Window::Input::Flush()
{
	Keyboard::Flush();
}


// Window::Input::Keyboard
Window::Input::Key		Window::Input::Keyboard::keys[KeyCodes::count];

bool					Window::Input::Keyboard::Init()
{
	return true;
}
void					Window::Input::Keyboard::Loop()
{
	{
		keys[Keys::ESC].state									= GetAsyncKeyState(VK_ESCAPE) != 0;
		keys[Keys::F1].state									= GetAsyncKeyState(VK_F1) != 0;
		keys[Keys::F2].state									= GetAsyncKeyState(VK_F2) != 0;
		keys[Keys::F3].state									= GetAsyncKeyState(VK_F3) != 0;
		keys[Keys::F4].state									= GetAsyncKeyState(VK_F4) != 0;
		keys[Keys::F5].state									= GetAsyncKeyState(VK_F5) != 0;
		keys[Keys::F6].state									= GetAsyncKeyState(VK_F6) != 0;
		keys[Keys::F7].state									= GetAsyncKeyState(VK_F7) != 0;
		keys[Keys::F8].state						= GetAsyncKeyState(VK_F8) != 0;
		keys[Keys::F9].state						= GetAsyncKeyState(VK_F9) != 0;
		keys[Keys::F10].state						= GetAsyncKeyState(VK_F10) != 0;
		keys[Keys::F11].state						= GetAsyncKeyState(VK_F11) != 0;
		keys[Keys::F12].state						= GetAsyncKeyState(VK_F2) != 0;
		keys[Keys::PrtScr].state					= GetAsyncKeyState(VK_SNAPSHOT) != 0;
		keys[Keys::SCROLL_LOCK].state				= GetAsyncKeyState(VK_SCROLL) != 0;
		keys[Keys::PAUSE].state					= GetAsyncKeyState(VK_PAUSE) != 0;

		keys[Keys::TILDE].state					= GetAsyncKeyState(VK_OEM_3) != 0;
		keys[Keys::DIGIT1].state					= GetAsyncKeyState('1') != 0;
		keys[Keys::DIGIT2].state					= GetAsyncKeyState('2') != 0;
		keys[Keys::DIGIT3].state					= GetAsyncKeyState('3') != 0;
		keys[Keys::DIGIT4].state					= GetAsyncKeyState('4') != 0;
		keys[Keys::DIGIT5].state					= GetAsyncKeyState('5') != 0;
		keys[Keys::DIGIT6].state					= GetAsyncKeyState('6') != 0;
		keys[Keys::DIGIT7].state					= GetAsyncKeyState('7') != 0;
		keys[Keys::DIGIT8].state					= GetAsyncKeyState('8') != 0;
		keys[Keys::DIGIT9].state					= GetAsyncKeyState('9') != 0;
		keys[Keys::DIGIT0].state					= GetAsyncKeyState('0') != 0;
		keys[Keys::MINUS].state					= GetAsyncKeyState(VK_OEM_MINUS) != 0;
		keys[Keys::PLUS].state					= GetAsyncKeyState(VK_OEM_PLUS) != 0;
		keys[Keys::BACKSPACE].state				= GetAsyncKeyState(VK_BACK) != 0;

		keys[Keys::TAB].state						= GetAsyncKeyState(VK_TAB) != 0;
		keys[Keys::Q].state						= GetAsyncKeyState('Q') != 0;
		keys[Keys::W].state						= GetAsyncKeyState('W') != 0;
		keys[Keys::E].state						= GetAsyncKeyState('E') != 0;
		keys[Keys::R].state						= GetAsyncKeyState('R') != 0;
		keys[Keys::T].state						= GetAsyncKeyState('T') != 0;
		keys[Keys::Y].state						= GetAsyncKeyState('Y') != 0;
		keys[Keys::U].state						= GetAsyncKeyState('U') != 0;
		keys[Keys::I].state						= GetAsyncKeyState('I') != 0;
		keys[Keys::O].state						= GetAsyncKeyState('O') != 0;
		keys[Keys::P].state						= GetAsyncKeyState('P') != 0;
		keys[Keys::L_CLIP].state					= GetAsyncKeyState(VK_OEM_4) != 0;
		keys[Keys::R_CLIP].state					= GetAsyncKeyState(VK_OEM_6) != 0;
		keys[Keys::ENTER].state					= GetAsyncKeyState(VK_RETURN) != 0;

		keys[Keys::CAPS_LOCK].state				= GetAsyncKeyState(VK_CAPITAL) != 0;
		keys[Keys::A].state						= GetAsyncKeyState('A') != 0;
		keys[Keys::S].state						= GetAsyncKeyState('S') != 0;
		keys[Keys::D].state						= GetAsyncKeyState('D') != 0;
		keys[Keys::F].state						= GetAsyncKeyState('F') != 0;
		keys[Keys::G].state						= GetAsyncKeyState('G') != 0;
		keys[Keys::H].state						= GetAsyncKeyState('H') != 0;
		keys[Keys::J].state						= GetAsyncKeyState('J') != 0;
		keys[Keys::K].state						= GetAsyncKeyState('K') != 0;
		keys[Keys::L].state						= GetAsyncKeyState('L') != 0;
		keys[Keys::COLON].state					= GetAsyncKeyState(VK_OEM_1) != 0;
		keys[Keys::QUOTE].state					= GetAsyncKeyState(VK_OEM_7) != 0;
		keys[Keys::DASH].state					= GetAsyncKeyState(VK_OEM_5) != 0;

		keys[Keys::BACKSLASH].state				= GetAsyncKeyState(VK_OEM_102) != 0;
		keys[Keys::Z].state						= GetAsyncKeyState('Z') != 0;
		keys[Keys::X].state						= GetAsyncKeyState('X') != 0;
		keys[Keys::C].state						= GetAsyncKeyState('C') != 0;
		keys[Keys::V].state						= GetAsyncKeyState('V') != 0;
		keys[Keys::B].state						= GetAsyncKeyState('B') != 0;
		keys[Keys::N].state						= GetAsyncKeyState('N') != 0;
		keys[Keys::M].state						= GetAsyncKeyState('M') != 0;
		keys[Keys::COMM].state					= GetAsyncKeyState(VK_OEM_COMMA) != 0;
		keys[Keys::DOT].state						= GetAsyncKeyState(VK_OEM_PERIOD) != 0;
		keys[Keys::SLASH].state					= GetAsyncKeyState(VK_OEM_2) != 0;

		keys[Keys::L_SHIFT].state					= GetAsyncKeyState(VK_LSHIFT) != 0;
		keys[Keys::R_SHIFT].state					= GetAsyncKeyState(VK_RSHIFT) != 0;
		keys[Keys::SHIFT].state					= keys[Keys::L_SHIFT].state || keys[Keys::R_SHIFT].state;
		keys[Keys::L_ALT].state					= GetAsyncKeyState(VK_LMENU) != 0;
		keys[Keys::R_ALT].state					= GetAsyncKeyState(VK_RMENU) != 0;
		keys[Keys::ALT].state						= keys[Keys::L_ALT].state || keys[Keys::R_ALT].state;
		keys[Keys::L_CTRL].state					= GetAsyncKeyState(VK_LCONTROL) != 0;
		keys[Keys::R_CTRL].state					= GetAsyncKeyState(VK_RCONTROL) != 0;
		keys[Keys::CTRL].state					= keys[Keys::L_CTRL].state || keys[Keys::R_CTRL].state;
		keys[Keys::L_WIN].state					= GetAsyncKeyState(VK_LWIN) != 0;
		keys[Keys::R_WIN].state					= GetAsyncKeyState(VK_RWIN) != 0;
		keys[Keys::WIN].state						= keys[Keys::L_WIN].state || keys[Keys::R_WIN].state;
		keys[Keys::SPACE].state					= GetAsyncKeyState(VK_SPACE) != 0;
		keys[Keys::MENU].state					= GetAsyncKeyState(VK_APPS) != 0;

		keys[Keys::INS].state						= GetAsyncKeyState(VK_INSERT) != 0;
		keys[Keys::DEL].state						= GetAsyncKeyState(VK_DELETE) != 0;
		keys[Keys::HOME].state					= GetAsyncKeyState(VK_HOME) != 0;
		keys[Keys::END].state						= GetAsyncKeyState(VK_END) != 0;
		keys[Keys::PAGE_UP].state					= GetAsyncKeyState(VK_PRIOR) != 0;
		keys[Keys::PAGE_DOWN].state				= GetAsyncKeyState(VK_NEXT) != 0;

		keys[Keys::UP].state						= GetAsyncKeyState(VK_UP) != 0;
		keys[Keys::DOWN].state					= GetAsyncKeyState(VK_DOWN) != 0;
		keys[Keys::RIGHT].state					= GetAsyncKeyState(VK_RIGHT) != 0;
		keys[Keys::LEFT].state					= GetAsyncKeyState(VK_LEFT) != 0;

		keys[Keys::NUM_LOCK].state				= GetAsyncKeyState(VK_NUMLOCK) != 0;
		keys[Keys::NUM_DIV].state					= GetAsyncKeyState(VK_DIVIDE) != 0;
		keys[Keys::NUM_MUL].state					= GetAsyncKeyState(VK_MULTIPLY) != 0;
		keys[Keys::NUM_SUB].state					= GetAsyncKeyState(VK_SUBTRACT) != 0;
		keys[Keys::NUM_ADD].state					= GetAsyncKeyState(VK_ADD) != 0;
		//NUM_ENTER.state		= GetAsyncKeyState(VK_UP);
		//NUM_DOT.state		= GetAsyncKeyState(VK_DELETE);
		keys[Keys::NUM_DIGIT1].state				= GetAsyncKeyState(VK_NUMPAD1) != 0;
		keys[Keys::NUM_DIGIT2].state				= GetAsyncKeyState(VK_NUMPAD2) != 0;
		keys[Keys::NUM_DIGIT3].state				= GetAsyncKeyState(VK_NUMPAD3) != 0;
		keys[Keys::NUM_DIGIT4].state				= GetAsyncKeyState(VK_NUMPAD4) != 0;
		keys[Keys::NUM_DIGIT5].state				= GetAsyncKeyState(VK_NUMPAD5) != 0;
		keys[Keys::NUM_DIGIT6].state				= GetAsyncKeyState(VK_NUMPAD6) != 0;
		keys[Keys::NUM_DIGIT7].state				= GetAsyncKeyState(VK_NUMPAD7) != 0;
		keys[Keys::NUM_DIGIT8].state				= GetAsyncKeyState(VK_NUMPAD8) != 0;
		keys[Keys::NUM_DIGIT9].state				= GetAsyncKeyState(VK_NUMPAD9) != 0;
		keys[Keys::NUM_DIGIT0].state				= GetAsyncKeyState(VK_NUMPAD0) != 0;
	}
	for(uint32 i = 0; i < Keys::count; ++i) keys[i].Loop();
}
void					Window::Input::Keyboard::Free()
{
}
void					Window::Input::Keyboard::Flush()
{
	for(uint32 i = 0; i < Keys::count; ++i) keys[i].Flush();
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































#include "TexProject_Windows.h"
using namespace TexProject;


// Window
void					TexProject::Window::Init()
{
	Window::RenderContext::Init();

	Window::Main::Init();
	Window::Render::Init();

	Window::Input::Init();
}
void					TexProject::Window::Free()
{
	Window::Input::Free();

	Window::Render::Free();
	Window::Main::Free();

	Window::RenderContext::Free();
}
bool					TexProject::Window::Process()
{
	Window::Input::Loop();

	bool res = false;

	for(uint32 i = 0; i < Window::Basic::GetCount(); ++i)
	{
		auto window = Window::Basic::Get(i);
		if(window->IsRunning()) res = true;
		Window::Basic::current = window;
		window->Loop();
	}
	Window::Basic::current = nullptr;

	return res;
}

bool					TexProject::Window::ErrorTest()
{
	auto error = GetLastError();
	if(error != NO_ERROR)
	{
		string text = "[Windows]\n";
		switch(error)
		{
			default:
			{
				text += "Unknown Error.";
				break;
			}
		}
		Message(text);
		return true;
	}
	return false;
}



// Window::Input
bool					TexProject::Window::Input::Init()
{
	if( !Keyboard::Init() ) return false;
	return true;
}
void					TexProject::Window::Input::Loop()
{
	Keyboard::Loop();
}
void					TexProject::Window::Input::Free()
{
	Keyboard::Free();
}
void					TexProject::Window::Input::Flush()
{
	Keyboard::Flush();
}


// Window::Input::Keyboard
Window::Input::Key		TexProject::Window::Input::Keyboard::keys[KeyCodes::count];

bool					TexProject::Window::Input::Keyboard::Init()
{
	return true;
}
void					TexProject::Window::Input::Keyboard::Loop()
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
void					TexProject::Window::Input::Keyboard::Free()
{
}
void					TexProject::Window::Input::Keyboard::Flush()
{
	for(uint32 i = 0; i < Keys::count; ++i) keys[i].Flush();
}


// Window::RenderContext
void					TexProject::Window::RenderContext::Init()
{
#ifdef __TEXPROJECT_WIN__
#ifdef __TEXPROJECT_DEBUG__
	if(!EntryPointData::init)
	{
		Error("Initing a RenderContext before entry point.");
	}
#endif
#endif

#ifdef __TEXPROJECT_WIN__
	Default::Init();
#endif

#ifdef __TEXPROJECT_OPENGL__
	OpenGL::Init();
#endif
}
void					TexProject::Window::RenderContext::Free()
{
#ifdef __TEXPROJECT_WIN__
	Default::Free();
#endif

#ifdef __TEXPROJECT_OPENGL__
	OpenGL::Free();
#endif
}


// Window::RenderContext::Basic
TexProject::Window::RenderContext::Basic::Basic(Window::Render* window_):
window(window_)
{
}
TexProject::Window::RenderContext::Basic::~Basic()
{
	Delete();
}

void					TexProject::Window::RenderContext::Basic::Create()
{
	Delete();
}
void					TexProject::Window::RenderContext::Basic::Delete()
{
}
void					TexProject::Window::RenderContext::Basic::Loop()
{
}
bool					TexProject::Window::RenderContext::Basic::Use()
{
	return false;
}


// Window::RenderContext::Default
#ifdef __TEXPROJECT_WIN__
void					TexProject::Window::RenderContext::Default::Init()
{
}
void					TexProject::Window::RenderContext::Default::Free()
{
}

TexProject::Window::RenderContext::Default::Default(Window::Render* window_):
	Basic(window_)
{
}
TexProject::Window::RenderContext::Default::~Default()
{
	Delete();
}
void					TexProject::Window::RenderContext::Default::Create()
{
	Delete();

	if(!inter)
	{
		//inter = Interface::Create<Interface::Default>(window);
		inter = Interface::Creator::CreateInterface<Interface::Default>(window);
	}

	init = true;
}
void					TexProject::Window::RenderContext::Default::Delete()
{
	if(init)
	{
		if(inter)
		{
			Interface::Creator::DeleteInterface(inter);
			inter = nullptr;
		}

		init = false;
	}
}
void					TexProject::Window::RenderContext::Default::Loop()
{
	if(inter)
	{
		inter->Loop();
	}
}
bool					TexProject::Window::RenderContext::Default::Use()
{
	if(init && window->IsInit())
	{
		SetROP2(window->wndDeviceContextHandle,R2_COPYPEN);
		/*
		R2_BLACK
		R2_NOTMERGEPEN
		R2_MASKNOTPEN
		R2_NOTCOPYPEN
		R2_MASKPENNOT
		R2_NOT
		R2_XORPEN
		R2_NOTMASKPEN
		R2_MASKPEN
		R2_NOTXORPEN
		R2_NOP
		R2_MERGENOTPEN
		R2_COPYPEN
		R2_MERGEPENNOT
		R2_MERGEPEN
		R2_WHITE
		R2_LAST
		*/

		//HPEN tPen = CreatePen();

		{
			/*auto newPen = (HPEN)GetStockObject(WHITE_PEN);
			auto oldPen = (HPEN)SelectObject(window->wndDeviceContextHandle,newPen);
			auto newBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
			auto ondBrush = (HBRUSH)SelectObject(window->wndDeviceContextHandle,newBrush);

			auto tBMP = (HBITMAP)LoadImage(NULL,"Media/Images/Test.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);			
			auto tBrush = CreatePatternBrush(tBMP);
			SelectObject(window->wndDeviceContextHandle,tBrush);*/
			{
				//SetDCPenColor(window->wndDeviceContextHandle,RGB(255,0,255));
				//SetDCBrushColor(window->wndDeviceContextHandle,RGB(0,255,255));
			}
			{
				/*MoveToEx(window->wndDeviceContextHandle,100,100,NULL);
				LineTo(window->wndDeviceContextHandle,200,200);*/
			}
			{
				//Rectangle(window->wndDeviceContextHandle,100,200,200,100);
				/*RECT tRect;
				tRect.bottom = 100;
				tRect.top = 200;
				tRect.left = 100;
				tRect.right = 400;
				FillRect(window->wndDeviceContextHandle,&tRect,tBrush);*/
			}
			{
				/*PAINTSTRUCT ps;
				auto hdc = BeginPaint(window->wndHandle,&ps);

				auto hdcMem = CreateCompatibleDC(hdc);

				BITMAP bitmap;

				SelectObject(hdcMem,tBMP);
				GetObject(tBMP,sizeof(bitmap),&bitmap);

				BitBlt(window->wndDeviceContextHandle,50,50,64,64,hdcMem,0,0,SRCCOPY);
				DeleteObject(hdcMem);

				EndPaint(window->wndHandle,&ps);*/
			}
			{
				/*RECT tRect;
				tRect.bottom = 100;
				tRect.top = 200;
				tRect.left = 100;
				tRect.right = 400;
				DrawText(window->wndDeviceContextHandle,"lol",-1,&tRect,DT_SINGLELINE | DT_CENTER | DT_VCENTER);*/
				/*
				DT_TOP
				DT_LEFT
				DT_CENTER
				DT_RIGHT
				DT_VCENTER
				DT_BOTTOM
				DT_WORDBREAK
				DT_SINGLELINE
				DT_EXPANDTABS
				DT_TABSTOP
				DT_NOCLIP
				DT_EXTERNALLEADING
				DT_CALCRECT
				DT_NOPREFIX
				DT_INTERNAL
				*/
			}
			/*SelectObject(window->wndDeviceContextHandle,oldPen);

			DeleteObject(tBrush);
			DeleteObject(tBMP);*/
		}

#ifdef __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif

		return true;
	}
	return false;
}
#endif


// Window::RenderContext::OpenGL
#ifdef __TEXPROJECT_OPENGL__
PFNWGLCREATECONTEXTATTRIBSARBPROC			TexProject::Window::RenderContext::OpenGL::wglCreateContextAttribsARB = NULL;

void					TexProject::Window::RenderContext::OpenGL::Init()
{
#ifdef __TEXPROJECT_WIN__
	{
		WNDCLASS tempWinClass;

		DWORD style =	WS_DISABLED;
		DWORD exStyle =	WS_EX_APPWINDOW;

		tempWinClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		tempWinClass.lpfnWndProc	= DefWindowProc;
		tempWinClass.cbClsExtra		= NULL;
		tempWinClass.cbWndExtra		= NULL;
		tempWinClass.hInstance		= EntryPointData::hInstance;
		tempWinClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);
		tempWinClass.hCursor		= LoadCursor(NULL,IDC_ARROW);
		tempWinClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
		tempWinClass.lpszMenuName	= NULL;
		tempWinClass.lpszClassName	= "Temp Window Class";

		if(!RegisterClass(&tempWinClass))
		{
			Message("Cannot register temp class.");
			return;
		}

		HWND tempWin = CreateWindow
			(
				"Temp Window Class",
				"Temp Window",
				WS_DISABLED,
				0,0,0,0,
				NULL,NULL,
				EntryPointData::hInstance,
				NULL
			);

		if(!tempWin)
		{
			Message("Cannot create window.");
			return;
		}

		{
			HDC tempDC = GetDC(tempWin);
			if(!tempDC)
			{
				Message("Cannot create Temp Device Context.");
				return;
			}

			PIXELFORMATDESCRIPTOR pfd;
			memset(&pfd,0,sizeof(pfd));
			pfd.nSize      = sizeof(pfd);
			pfd.nVersion   = 1;
			pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cStencilBits = 32;
			pfd.cDepthBits = 32;

			int PixelFormat = ChoosePixelFormat(tempDC,&pfd);
			if(!PixelFormat)
			{
				Message("Can't Chose A Pixel Format.\nChoosePixelFormat");
				return;
			}

			if(!SetPixelFormat(tempDC,PixelFormat,&pfd))
			{
				Message("Can't Set A Pixel Format.\nSetPixelFormat");
				return;
			}

			HGLRC tempRC = wglCreateContext(tempDC);
			if(!tempRC)
			{
				Message("Can't Create Temp GL Render Context.\nwglCreateContext");
				return;
			}

			if(!wglMakeCurrent(tempDC,tempRC))
			{
				Message("Can't Activate Temp GL Render Context.\nwglMakeCurrent");
				return;
			}

			wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));

			TexProject::OpenGL::Init();

			if(!wglMakeCurrent(NULL,NULL))
			{
				Message("Can't Release Render Context.\nwglMakeCurrent(NULL, NULL)");
				return;
			}

			if(!wglDeleteContext(tempRC))
			{
				Message("Can't Delete Temp GL Render Context.\nwglDeleteContext(Temp_hRC)");
				return;
			}

			//if(!wglCreateContextAttribsARB) Error("GL Context Creation Failed.\nwglCreateContextAttribsARB");
		}
		
		DestroyWindow(tempWin);
		UnregisterClass("Temp Window Class", EntryPointData::hInstance);
	}
#endif
}
void					TexProject::Window::RenderContext::OpenGL::Free()
{
}

TexProject::Window::RenderContext::OpenGL::OpenGL(Window::Render* window_):
	Basic(window_)
{
}
TexProject::Window::RenderContext::OpenGL::~OpenGL()
{
	Delete();
}
void					TexProject::Window::RenderContext::OpenGL::Create()
{
	Delete();

	static const int32 attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB,3,
		WGL_CONTEXT_MINOR_VERSION_ARB,3,
		WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB,WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, //WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0,0
	};

	wndRenderContextHandle = wglCreateContextAttribsARB(window->wndDeviceContextHandle,0,attribs);

	if(!wndRenderContextHandle)
	{
		Message("Can't create OpenGL render context.");
		return;
	}

	init = true;
}
void					TexProject::Window::RenderContext::OpenGL::Delete()
{
	if( init )
	{
		init = false;
	}
}
bool					TexProject::Window::RenderContext::OpenGL::Use()
{
	if(init && window->IsInit())
	{
		if(!wglMakeCurrent(window->wndDeviceContextHandle,wndRenderContextHandle))
		{
			Message("Fail to use OpenGL render context.");
			return false;
		}

#ifdef __TEXPROJECT_DEBUG__
	TexProject::OpenGL::ErrorTest();
#endif

		return true;
	}
	return false;
}
#endif


// Window::Basic
Window::Basic*			TexProject::Window::Basic::current = nullptr;

void					TexProject::Window::Basic::Delete()
{
	for(auto i: child) i->Delete();
	child.clear();
}


void					TexProject::Window::Basic::SetSize(const uvec2 size_)
{
	size = size_;
}
void					TexProject::Window::Basic::SetPos(const ivec2 pos_)
{
	pos = pos_;
}

void*					TexProject::Window::Basic::GetHandle()
{
	return nullptr;
}


// Window::Main
#ifdef __TEXPROJECT_WIN__
LRESULT CALLBACK		TexProject::Window::Main::callbackDefault(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
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
#endif

void					TexProject::Window::Main::Init()
{
#ifdef __TEXPROJECT_WIN__
	{
		wndClassName = "[Window::Main] Class";

		wndClassEx.cbSize			= sizeof(wndClassEx);
		wndClassEx.style			= CS_HREDRAW | CS_VREDRAW | CS_DROPSHADOW;
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

	{
		wndStyle	= WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_VISIBLE;
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
		wndExStyle	= WS_EX_APPWINDOW;
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
#endif
}
void					TexProject::Window::Main::Free()
{
#ifdef __TEXPROJECT_WIN__
	UnregisterClass(wndClassName.c_str(),EntryPointData::hInstance);
#endif
}


void					TexProject::Window::Main::Create(Basic* parent_)
{
#ifdef __TEXPROJECT_WIN__
#ifdef __TEXPROJECT_DEBUG__
	if(!EntryPointData::init)
	{
		Error("Creating a window before entry point.");
	}
#endif

	Delete();

	{
		parent = parent_;
		if(parent)
		{
			if(!parent->IsInit()) return;
			parent->AddChild(this);
		}
	}

	{
		size = uvec2(400, 300);
		pos = GetDesktopSize()/2 - size/2;
		title = "window";
	}

	{
		wndRect.left	= (LONG)(pos.x);
		wndRect.right	= (LONG)(pos.x + size.x);
		wndRect.top		= (LONG)(pos.y);
		wndRect.bottom	= (LONG)(pos.y + size.y);
	}
	AdjustWindowRectEx(&wndRect,wndStyle,FALSE,wndExStyle);

	wndHandle =	CreateWindowEx
	(
		wndExStyle,
		wndClassName.c_str(),
		title.c_str(),
		wndStyle | (parent ? WS_CHILD : 0),
		wndRect.left,
		wndRect.top,
		wndRect.right - wndRect.left,
		wndRect.bottom - wndRect.top,
		(HWND)(parent ? parent->GetHandle() : nullptr),	//nullptr,
		(HMENU)nullptr,
		wndClassEx.hInstance,
		nullptr
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
#endif

	init = true;
	running = true;

}
void					TexProject::Window::Main::Delete()
{
	Basic::Delete();

#ifdef __TEXPROJECT_WIN__
	if(wndHandle)
	{
		DestroyWindow(wndHandle);
		wndHandle = 0;
	}
#endif

	if(init)
	{
		init = false;
	}
}
void					TexProject::Window::Main::Loop()
{
#ifdef __TEXPROJECT_WIN__
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
		if(GetFocus() == wndHandle)
		{
			active = true;
		}
		else
		{
			active = false;
		}

		if(!running)
		{
			Delete();
		}

		UpdateWindow(wndHandle);

#ifdef __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif
	}
}

void					TexProject::Window::Main::SetSize(const uvec2 size_)
{
	if(size.x != size_.x || size.y != size_.y)
	{
		size = size_;
#ifdef __TEXPROJECT_WIN__
		if(wndHandle)
		{
			{
				wndRect.left	= (LONG)(pos.x);
				wndRect.right	= (LONG)(pos.x + size.x);
				wndRect.top		= (LONG)(pos.y);
				wndRect.bottom	= (LONG)(pos.y + size.y);
			}
			AdjustWindowRectEx(&wndRect,wndStyle,FALSE,wndExStyle);
			SetWindowPos
				(
				wndHandle,
				HWND_NOTOPMOST,
				wndRect.left,
				wndRect.bottom,
				wndRect.right-wndRect.left,
				wndRect.bottom-wndRect.top,
				SWP_NOMOVE
				);
			UpdateWindow(wndHandle);
		}
#endif
	}
}
void					TexProject::Window::Main::SetPos(const ivec2 pos_)
{
	if(pos.x != pos_.x || pos.y != pos_.y)
	{
		pos = pos_;
#ifdef __TEXPROJECT_WIN__
		if(wndHandle)
		{
			{
				wndRect.left	= (LONG)(pos.x);
				wndRect.right	= (LONG)(pos.x + size.x);
				wndRect.top		= (LONG)(pos.y);
				wndRect.bottom	= (LONG)(pos.y + size.y);
			}
			AdjustWindowRectEx(&wndRect,wndStyle,FALSE,wndExStyle);
			SetWindowPos
				(
				wndHandle,
				HWND_NOTOPMOST,
				wndRect.left,
				wndRect.bottom,
				wndRect.right-wndRect.left,
				wndRect.bottom-wndRect.top,
				SWP_NOSIZE
				);
			UpdateWindow(wndHandle);
		}
#endif
	}
}

void*					TexProject::Window::Main::GetHandle()
{
	return wndHandle;
}


// Window::Window::Render
#ifdef __TEXPROJECT_WIN__
PIXELFORMATDESCRIPTOR	TexProject::Window::Render::wndPixelFormatDescriptor;
LRESULT CALLBACK		TexProject::Window::Render::callbackDefault(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	auto window = (Render*)GetWindowLongPtr(hWnd,GWLP_USERDATA);

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
#endif

void					TexProject::Window::Render::Init()
{
#ifdef __TEXPROJECT_WIN__
	{
		wndClassName = "[Window::Render] Class";

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
		wndClassEx.hbrBackground	= (HBRUSH)GetStockObject(GRAY_BRUSH);
		wndClassEx.lpszMenuName		= NULL;
		wndClassEx.lpszClassName	= wndClassName.c_str();
		wndClassEx.hIconSm			= LoadIcon(NULL,IDI_APPLICATION);
	}

	if(!RegisterClassEx(&wndClassEx))
	{
		Message("Failed To register window class.");
		return;
	}

	{
		wndStyle	=  WS_CAPTION | WS_SYSMENU | WS_VISIBLE;	//WS_POPUP;
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
		wndExStyle	= WS_EX_APPWINDOW ;//| WS_EX_TOOLWINDOW;
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
		memset(&wndPixelFormatDescriptor,0,sizeof(wndPixelFormatDescriptor));
		wndPixelFormatDescriptor.nSize			= sizeof(wndPixelFormatDescriptor);
		wndPixelFormatDescriptor.nVersion		= 1;
		wndPixelFormatDescriptor.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		/*
		PFD_DOUBLEBUFFER
		PFD_STEREO
		PFD_DRAW_TO_WINDOW
		PFD_DRAW_TO_BITMAP
		PFD_SUPPORT_GDI
		PFD_SUPPORT_OPENGL
		PFD_GENERIC_FORMAT
		PFD_NEED_PALETTE
		PFD_NEED_SYSTEM_PALETTE
		PFD_SWAP_EXCHANGE
		PFD_SWAP_COPY
		PFD_SWAP_LAYER_BUFFERS
		PFD_GENERIC_ACCELERATED
		PFD_SUPPORT_DIRECTDRAW
		PFD_DIRECT3D_ACCELERATED
		PFD_SUPPORT_COMPOSITION
		*/
		wndPixelFormatDescriptor.iPixelType		= PFD_TYPE_RGBA;
		/*
		PFD_TYPE_RGBA
		PFD_TYPE_COLORINDEX
		*/
		wndPixelFormatDescriptor.cColorBits		= 32;
		wndPixelFormatDescriptor.cStencilBits	= 32;
		wndPixelFormatDescriptor.cDepthBits		= 32;
	}
#endif
}
void					TexProject::Window::Render::Free()
{
#ifdef __TEXPROJECT_WIN__
	UnregisterClass(wndClassName.c_str(),EntryPointData::hInstance);
#endif
}

TexProject::Window::Render::Render()	
{
#if __TEXPROJECT_WIN__
	vSyncTimer = clock();
	oVSyncTimer = vSyncTimer;
#endif

	ResetFuncs();
}
TexProject::Window::Render::~Render()
{
	Delete();
}

void					TexProject::Window::Render::Create(Basic* parent_)
{
#ifdef __TEXPROJECT_WIN__
#ifdef __TEXPROJECT_DEBUG__
	if(!EntryPointData::init)
	{
		Error("Creating a window before entry point.");
	}
#endif

	Delete();

	{
		parent = parent_;
		if(parent && !parent->IsInit()) return;
		if(parent)
		{
			if(!parent->IsInit()) return;
			parent->AddChild(this);
		}
	}

	{
		size = uvec2(256);
		pos = GetDesktopSize()/2 - size/2;
		title = "window";
	}

	{
		wndRect.left	= (LONG)(pos.x);
		wndRect.right	= (LONG)(pos.x + size.x);
		wndRect.top		= (LONG)(pos.y);
		wndRect.bottom	= (LONG)(pos.y + size.y);
	}

	AdjustWindowRectEx(&wndRect,wndStyle,FALSE,wndExStyle);

	wndHandle =	CreateWindowEx
		(
		wndExStyle,
		wndClassName.c_str(),
		title.c_str(),
		wndStyle | (parent ? WS_CHILD : 0),
		wndRect.left,
		wndRect.top,
		wndRect.right - wndRect.left,
		wndRect.bottom - wndRect.top,
		(HWND)(parent ? parent->GetHandle() : nullptr),	//nullptr,
		(HMENU)NULL,
		wndClassEx.hInstance,
		NULL
		);
	if(!wndHandle)
	{
		Message("Can't create window.");
		return;
	}

	{
		wndDeviceContextHandle = GetDC(wndHandle);		
	}
	if(!wndDeviceContextHandle)
	{
		Message("Cannot create device context.");
		return;
	}

	{
		auto pixelFormat = ChoosePixelFormat(wndDeviceContextHandle,&wndPixelFormatDescriptor);
		if(!pixelFormat)
		{
			Message("Can't chose pixel format.");
			return;
		}
		if(!SetPixelFormat(wndDeviceContextHandle,pixelFormat,&wndPixelFormatDescriptor))
		{
			Message("Can't set pixel format.");
			return;
		}
	}

	SetWindowLongPtr(wndHandle,GWLP_USERDATA,(LONG)this);
	/*
	GWL_EXSTYLE
	GWLP_HINSTANCE
	GWLP_ID
	GWL_STYLE
	GWLP_USERDATA
	GWLP_WNDPROC
	*/

	ShowWindow(wndHandle,SW_SHOW);
	SetFocus(wndHandle);
#endif

	init = true;
	running = true;

	if(renderContext)
	{
		renderContext->Create();
		if(renderContext->Use())
		{
			if(func[FuncTypes::Init]) func[FuncTypes::Init](this);
		}
	}

}
void					TexProject::Window::Render::Delete()
{
	if(renderContext)
	{
		if(init)
		{
			if(renderContext->Use())
			{
				if(func[FuncTypes::Free]) func[FuncTypes::Free](this);
			}
		}
	}

	Basic::Delete();

	if(renderContext)
	{
		renderContext->Delete();
	}

#ifdef __TEXPROJECT_WIN__

	if(wndHandle)
	{
		if(wndDeviceContextHandle)
		{
			if(!ReleaseDC(wndHandle,wndDeviceContextHandle))
			{
				Error("Can't Release hDC.");
			}
			wndDeviceContextHandle = 0;
		}

		DestroyWindow(wndHandle);
		wndHandle = 0;
	}

	if(init)
	{
		init = false;
	}

#endif
}
void					TexProject::Window::Render::Loop()
{
#ifdef __TEXPROJECT_WIN__
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
			if(GetFocus() == wndHandle)
			{
				active = true;
			}
			else
			{
				active = false;
			}

			if(renderContext)
			{
				if(renderContext->Use())
				{
					if( vSync )
					{
						while( difftime((vSyncTimer = clock()),oVSyncTimer) < 1.0/60.0f );
						oVSyncTimer = vSyncTimer;
					}
					else
					{
						if(func[FuncTypes::Loop]) func[FuncTypes::Loop](this);

						renderContext->Loop();

						SwapBuffers(wndDeviceContextHandle);
					}
				}
			}
		}
		else
		{
			Delete();
		}

#ifdef __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif
	}
}

void					TexProject::Window::Render::SetSize(const uvec2 size_)
{
	if(size.x != size_.x || size.y != size_.y)
	{
		size = size_;
#ifdef __TEXPROJECT_WIN__
		if(wndHandle)
		{
			{
				wndRect.left	= (LONG)(pos.x);
				wndRect.right	= (LONG)(pos.x + size.x);
				wndRect.top		= (LONG)(pos.y);
				wndRect.bottom	= (LONG)(pos.y + size.y);
			}
			AdjustWindowRectEx(&wndRect,wndStyle,FALSE,wndExStyle);
			SetWindowPos
				(
				wndHandle,
				HWND_NOTOPMOST,
				wndRect.left,
				wndRect.bottom,
				wndRect.right-wndRect.left,
				wndRect.bottom-wndRect.top,
				SWP_NOMOVE
				);
			UpdateWindow(wndHandle);
		}
#endif
	}
}
void					TexProject::Window::Render::SetPos(const ivec2 pos_)
{
	if(pos.x != pos_.x || pos.y != pos_.y)
	{
		pos = pos_;
#ifdef __TEXPROJECT_WIN__
		if(wndHandle)
		{
			{
				wndRect.left	= (LONG)(pos.x);
				wndRect.right	= (LONG)(pos.x + size.x);
				wndRect.top		= (LONG)(pos.y);
				wndRect.bottom	= (LONG)(pos.y + size.y);
			}
			AdjustWindowRectEx(&wndRect,wndStyle,FALSE,wndExStyle);
			SetWindowPos
				(
				wndHandle,
				HWND_NOTOPMOST,
				wndRect.left,
				wndRect.bottom,
				wndRect.right-wndRect.left,
				wndRect.bottom-wndRect.top,
				SWP_NOSIZE
				);
			UpdateWindow(wndHandle);
		}
#endif
	}
}

void					TexProject::Window::Render::SetRenderContext(const RenderContext::Type& type_)
{
	if(renderContext)
	{
		delete renderContext; renderContext = nullptr;
	}

	switch(type_)
	{
#ifdef __TEXPROJECT_WIN__
		case RenderContext::Types::Default:
		{
			renderContext = new RenderContext::Default(this);
			break;
		}
#endif
#ifdef __TEXPROJECT_OPENGL__
		case RenderContext::Types::OpenGL:
		{
			renderContext = new RenderContext::OpenGL(this);
			break;
		}
#endif
		default:
		{
			return;
		}
	}

	if( init && renderContext )
	{
		renderContext->Create();
		if(renderContext->Use())
		{
			if(func[FuncTypes::Init]) func[FuncTypes::Init](this);
		}
	}
}
void					TexProject::Window::Render::SetFunc(const FuncType& type_,Func func_)
{
	func[type_] = func_;
}
void					TexProject::Window::Render::ResetFuncs()
{
	for(uint32 i = 0; i < FuncTypes::count; ++i) func[i] = nullptr;
}




























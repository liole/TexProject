#include "TexProject_Windows.h"
using namespace TexProject;


#include <TexProject/TexProject_OpenGL.h>
#include <TexProject/TexProject_Textures.h>


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

	Window::Basic::FreeArray();
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
		do
		{
			string text = "[Windows]\n";
			{
				char *t = "\0";
				FormatMessage
				(
					FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
					NULL,
					error,
					LANG_NEUTRAL,
					(LPTSTR)&t,
					0,
					NULL
				);
				text += t;
				LocalFree(t);
			}
			Message(text);
			error = GetLastError();
		}
		while(error != NO_ERROR);
	}
	return true;

	return false;
}



// Window::Input
bool					TexProject::Window::Input::Init()
{
	if(!Mouse::Init()) return false;
	if(!Keyboard::Init()) return false;
	return true;
}
void					TexProject::Window::Input::Loop()
{
	Mouse::Loop();
	Keyboard::Loop();
}
void					TexProject::Window::Input::Free()
{
	Mouse::Free();
	Keyboard::Free();
}
void					TexProject::Window::Input::Flush()
{
	Mouse::Flush();
	Keyboard::Flush();
}


// Window::Input::Mouse
Window::Input::Key		TexProject::Window::Input::Mouse::lB,
						TexProject::Window::Input::Mouse::mB,
						TexProject::Window::Input::Mouse::rB;
ivec2					TexProject::Window::Input::Mouse::pos;

bool					TexProject::Window::Input::Mouse::Init()
{
	return true;
}
void					TexProject::Window::Input::Mouse::Loop()
{
	static POINT t;
	GetCursorPos(&t);
	//pos.x = t.x;
	//pos.y = t.y;	//.y = Window.size.y - t.y;

	pos.x = t.x;
	pos.y = GetDesktopSize().y - t.y;

	lB.state = GetAsyncKeyState(VK_LBUTTON) != NULL;
	mB.state = GetAsyncKeyState(VK_MBUTTON) != NULL;
	rB.state = GetAsyncKeyState(VK_RBUTTON) != NULL;

	lB.Loop();
	mB.Loop();
	rB.Loop();
}
void					TexProject::Window::Input::Mouse::Free()
{
}
void					TexProject::Window::Input::Mouse::Flush()
{
	pos = ivec2(0,0);
	lB.Flush();
	mB.Flush();
	rB.Flush();
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
#if __TEXPROJECT_WIN__
#if __TEXPROJECT_DEBUG__
	if(!EntryPointData::init)
	{
		Error("Initing a RenderContext before entry point.");
	}
#endif
#endif

#if __TEXPROJECT_WIN__
	Default::Init();
#endif

#if __TEXPROJECT_OPENGL__
	OpenGL::Init();
#endif

#if __TEXPROJECT_DIRECT3D__
	Direct3D::Init();
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

#if __TEXPROJECT_DIRECT3D__
	Direct3D::Free();
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
void					TexProject::Window::RenderContext::Basic::Unuse()
{
}


#if __TEXPROJECT_WIN__
void					TexProject::Window::RenderContext::Basic::_win_WMPaint(HDC hDC)
{
}
#endif



// Window::RenderContext::Default
#if __TEXPROJECT_WIN__

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
void*					TexProject::Window::RenderContext::Default::GetData() const
{
	return nullptr;
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
	UpdateWindow(window->wndHandle);
	//SwapBuffers(wndDeviceContextHandle);
	InvalidateRect(window->wndHandle,NULL,TRUE);
}
bool					TexProject::Window::RenderContext::Default::Use()
{
	if(init && window->IsInit())
	{
		SetROP2(window->wndDeviceContextHandle,R2_COPYPEN);

#if __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif

		return true;
	}
	return false;
}
void					TexProject::Window::RenderContext::Default::_win_WMPaint(HDC hDC)
{
	RECT rc;
	rc.left = 0;
	rc.right = window->GetSize().x;
	rc.top = 0;
	rc.bottom = window->GetSize().y;

	FillRect(hDC,&rc,(HBRUSH)GetStockObject(DKGRAY_BRUSH));

	inter->_win_WMPaint(hDC);
}

#endif


// Window::RenderContext::OpenGL
#if __TEXPROJECT_OPENGL__
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

#if __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif

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
	//textureCurrent(new TexProject::OpenGL::Texture*[GetTextureMaxSlots()])
{
}
TexProject::Window::RenderContext::OpenGL::~OpenGL()
{
}
TexProject::OpenGL::Texture*				TexProject::Window::RenderContext::OpenGL::GetCurrentTexture(uint32 level) const
{
#if __TEXPROJECT_DEBUG__
	if(int32(level) < GetTextureMaxSlots())
	{
		return textureCurrent[level];
	}
	else
	{
		throw Exception("");
	}
#else
	return textureCurrent[level];
#endif
}
void*					TexProject::Window::RenderContext::OpenGL::GetData() const
{
	return reinterpret_cast<void*>(const_cast<RenderContext::OpenGL * const>(this));
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

	Use();

	{
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,&textureMaxSlots);
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS,&bufferFrameMaxColorAttachment);
	}

	{
		textureCurrent = new TexProject::OpenGL::Texture*[GetTextureMaxSlots()];
		for(int32 i = 0; i < GetTextureMaxSlots(); ++i) textureCurrent[i] = nullptr;
	}

	Unuse();
}
void					TexProject::Window::RenderContext::OpenGL::Delete()
{
	if( init )
	{
		{
			textureMaxSlots = 0;
			bufferFrameMaxColorAttachment = 0;
		}
		if(textureCurrent)
		{
			delete[] textureCurrent;
			textureCurrent = nullptr;
		}
		init = false;
	}
}
void					TexProject::Window::RenderContext::OpenGL::Loop()
{
	SwapBuffers(window->wndDeviceContextHandle);
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

void					TexProject::Window::RenderContext::OpenGL::UnuseBufferArray()
{
	::OpenGL::glBindVertexArray(0);
	bufferArrayCurrent = nullptr;
}
void					TexProject::Window::RenderContext::OpenGL::UnuseBufferIndex()
{
	::OpenGL::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	bufferIndexCurrent = nullptr;
}
void					TexProject::Window::RenderContext::OpenGL::UnuseBufferData()
{
	::OpenGL::glBindBuffer(GL_ARRAY_BUFFER,0);
	bufferDataCurrent = nullptr;
}
void					TexProject::Window::RenderContext::OpenGL::UnuseBufferFrame()
{
	::OpenGL::glBindFramebuffer(GL_FRAMEBUFFER,0);
	bufferFrameCurrent = nullptr;
}
void					TexProject::Window::RenderContext::OpenGL::UnuseShader()
{
	::OpenGL::glUseProgram(0);
	shaderCurrent = nullptr;
}

#endif


// Window::RenderContext::Direct3D
#if __TEXPROJECT_DIRECT3D__

void					TexProject::Window::RenderContext::Direct3D::Init()
{
}
void					TexProject::Window::RenderContext::Direct3D::Free()
{
}
TexProject::Window::RenderContext::Direct3D::Direct3D(Window::Render* window_):
	Basic(window_)
{
}
TexProject::Window::RenderContext::Direct3D::~Direct3D()
{
}
void*					TexProject::Window::RenderContext::Direct3D::GetData() const
{
	//return reinterpret_cast<void*>(d3ddev);
	return reinterpret_cast<void*>(const_cast<RenderContext::Direct3D * const>(this));
}

LPDIRECT3DVERTEXBUFFER9 vb = NULL;
LPDIRECT3DINDEXBUFFER9	ib = NULL;
LPD3DXEFFECT			fx = NULL;
struct CUSTOMVERTEX
{
	FLOAT x,y,z,rhw;
	DWORD color;
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)


void					TexProject::Window::RenderContext::Direct3D::Create()
{
	Delete();

	//d3ddev = new IDirect3DDevice9();

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(!d3d) Error("Cant create direct device.");

	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferWidth = window->GetSize().x;
	d3dpp.BackBufferHeight = window->GetSize().y;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//D3DFMT_R8G8B8;	//D3DFMT_UNKNOWN
	d3dpp.EnableAutoDepthStencil = FALSE;
	d3dpp.hDeviceWindow = (HWND)window->GetHandle();	//hWnd;

	{
		auto result = d3d->CreateDevice
		(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			NULL,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// D3DCREATE_HARDWARE_VERTEXPROCESSING
			&d3dpp,
			&d3ddev
		);
		TexProject::Direct3D::ErrorTest(result);
	}

	if(!d3ddev) Error("");

	/*{
		auto result = d3ddev->CreateVertexBuffer
		(
			sizeof(CUSTOMVERTEX)*3,
			0,
			D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT,
			&vb,
			NULL
		);
		TexProject::Direct3D::ErrorTest(result);
	}

	{
		CUSTOMVERTEX vArr[] =
		{
			{256.0f,0.0f,0.5f,1.0f,0xffff0000,},
			{512.0f,512.0f,0.5f,1.0f,0xff00ff00,},
			{0.0f,512.0f,0.5f,1.0f,0xff00ffff,},
		};

		void* tArr = nullptr;
		TexProject::Direct3D::ErrorTest(vb->Lock(0,sizeof(CUSTOMVERTEX)*3,&tArr,0));
		memcpy(tArr,vArr,sizeof(vArr));
		TexProject::Direct3D::ErrorTest(vb->Unlock());
	}

	{
		uint32 iArr[] = { 0,1,2 };

		d3ddev->CreateIndexBuffer(sizeof(uint32)*3,0,D3DFMT_INDEX32,D3DPOOL_DEFAULT,&ib,NULL);
		void* tArr = nullptr;
		ib->Lock(0,sizeof(uint32)*3,&tArr,0);
		memcpy(tArr,iArr,sizeof(iArr));
		ib->Unlock();
	}

	{
		auto result = D3DXCreateEffectFromFile(d3ddev,"Media/Shaders/HLSL/1.fx",NULL,NULL,D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,NULL,&fx,NULL);
		TexProject::Direct3D::ErrorTest(result);
	}*/

	init = true;
}
void					TexProject::Window::RenderContext::Direct3D::Delete()
{
	if(init)
	{
		init = false;
	}
}
void					TexProject::Window::RenderContext::Direct3D::Loop()
{
	SwapBuffers(window->wndDeviceContextHandle);
}
bool					TexProject::Window::RenderContext::Direct3D::Use()
{
	if(init && d3ddev)
	{

		//d3ddev->CreateVertexShader()

		TexProject::Direct3D::ErrorTest(d3ddev->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.0f,0));
		TexProject::Direct3D::ErrorTest(d3ddev->BeginScene());

		/*uint32 passes = 0;
		fx->Begin(&passes, 0);
		for(uint32 uiPass = 0; uiPass < passes; ++uiPass)
		{
			fx->BeginPass(uiPass);

			{
				auto result = d3ddev->SetStreamSource(0,vb,0,sizeof(CUSTOMVERTEX));
				switch(result)
				{
					case D3DERR_DEVICELOST: Message("D3DERR_DEVICELOST"); break;
					case D3DERR_INVALIDCALL: Message("D3DERR_INVALIDCALL"); break;
					case D3DERR_NOTAVAILABLE: Message("D3DERR_NOTAVAILABLE"); break;
					case D3DERR_OUTOFVIDEOMEMORY: Message("D3DERR_OUTOFVIDEOMEMORY"); break;
				}
			}
			d3ddev->SetIndices(ib);
			d3ddev->SetFVF(D3DFVF_CUSTOMVERTEX);
			{
				//auto result = d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST,0,1);
				auto result = d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,3,0,1);
				switch(result)
				{
					case D3DERR_DEVICELOST: Message("D3DERR_DEVICELOST"); break;
					case D3DERR_INVALIDCALL: Message("D3DERR_INVALIDCALL"); break;
					case D3DERR_NOTAVAILABLE: Message("D3DERR_NOTAVAILABLE"); break;
					case D3DERR_OUTOFVIDEOMEMORY: Message("D3DERR_OUTOFVIDEOMEMORY"); break;
				}
			}

			fx->EndPass();
		}
		fx->End();*/

		/*d3ddev->EndScene();
		d3ddev->Present(NULL,NULL,NULL,NULL);*/
		return true;
	}
	return false;
}
void					TexProject::Window::RenderContext::Direct3D::Unuse()
{
	if(init && d3ddev)
	{
		d3ddev->EndScene();
		d3ddev->Present(NULL,NULL,NULL,NULL);
	}
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
#if __TEXPROJECT_WIN__
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


void					TexProject::Window::Main::Create(const string& title_)
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
		parent = nullptr;	//parent_;
		if(parent)
		{
			if(!parent->IsInit()) return;
			parent->AddChild(this);
		}
	}

	{
		size = uvec2(400, 300);
		pos = GetDesktopSize()/2 - size/2;
		title = title_;	//"window";
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
#if __TEXPROJECT_WIN__
PIXELFORMATDESCRIPTOR	TexProject::Window::Render::wndPixelFormatDescriptor;
LRESULT CALLBACK		TexProject::Window::Render::callbackDefault(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	auto window = (Window::Render*)GetWindowLongPtr(hWnd,GWLP_USERDATA);

	switch(msg)
	{
		case WM_PAINT:
		{			
			if(window)
			{
				if(window->renderContext)
				{
					PAINTSTRUCT ps;
					auto hDC = BeginPaint(hWnd,&ps);
					
					auto hOldBitmap = (HBITMAP)SelectObject(window->dbHDC,window->dbBitmap);

					window->renderContext->_win_WMPaint(window->dbHDC);

					BitBlt(hDC,0,0,window->GetSize().x,window->GetSize().y,window->dbHDC,0,0,SRCCOPY);

					SelectObject(window->dbHDC,hOldBitmap);

					ValidateRect(hWnd,NULL);

					EndPaint(hWnd,&ps);
				}
			}
			return 0;
		}
		case WM_ERASEBKGND:
		{
			return 1; // Say we handled it.
		}
		case WM_MOVE:
		{
			if(window)
			{
				RECT rect;
				GetClientRect(hWnd,&rect);
				POINT p;
				p.x = rect.left;
				p.y = rect.top;
				ClientToScreen(hWnd,&p);
				window->pos.x = p.x;
				window->pos.y = p.y;
			}
			return DefWindowProc(hWnd,msg,wParam,lParam);
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
#if __TEXPROJECT_WIN__
	{
		wndClassName = "[Window::Render] Class";

		wndClassEx.cbSize			= sizeof(wndClassEx);
		wndClassEx.style			= CS_OWNDC;	//CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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
		wndClassEx.lpfnWndProc		= callbackDefault;
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
#if __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif
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
		wndPixelFormatDescriptor.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_SUPPORT_DIRECTDRAW | PFD_SUPPORT_GDI | PFD_DOUBLEBUFFER;
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
#if __TEXPROJECT_WIN__
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

void					TexProject::Window::Render::Create(const string& title_)
{
#if __TEXPROJECT_WIN__
#if __TEXPROJECT_DEBUG__
	if(!EntryPointData::init)
	{
		Error("Creating a window before entry point.");
	}
#endif

	Delete();

	{
		parent = nullptr;	//parent_;
		if(parent && !parent->IsInit()) return;
		if(parent)
		{
			if(!parent->IsInit()) return;
			parent->AddChild(this);
		}
	}

	{
		size = uvec2(256);
		pos = (vec2(GetDesktopSize()) - vec2(size))*0.5f;
		title = title_;
	}

	{
		vec2 p;
		p = ToDesktopSpace(vec2(pos));
		wndRect.left	= (LONG)(p.x);
		wndRect.bottom	= (LONG)(p.y);
		p = ToDesktopSpace(vec2(pos + ivec2(size)));
		wndRect.right	= (LONG)(p.x);
		wndRect.top		= (LONG)(p.y);
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
		(HWND)(parent ? parent->GetHandle() : NULL),	//NULL,
		(HMENU)NULL,
		wndClassEx.hInstance,
		NULL
	);

	if(!wndHandle)
	{
#if __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif
		Message("Can't create window.");
		return;
	}

	UpdateWindow(wndHandle);

	{
		wndDeviceContextHandle = GetDC(wndHandle);		
	}
	if(!wndDeviceContextHandle)
	{
#if __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif
		Message("Cannot create device context.");
		return;
	}

	{
		auto pixelFormat = ChoosePixelFormat(wndDeviceContextHandle,&wndPixelFormatDescriptor);
		if(!pixelFormat)
		{
#if __TEXPROJECT_DEBUG__
			Window::ErrorTest();
#endif
			Message("Can't chose pixel format.");
			return;
		}
		if(!SetPixelFormat(wndDeviceContextHandle,pixelFormat,&wndPixelFormatDescriptor))
		{
#if __TEXPROJECT_DEBUG__
			Window::ErrorTest();
#endif
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


	{
		dbHDC = CreateCompatibleDC(wndDeviceContextHandle);
		dbBitmap = CreateCompatibleBitmap(wndDeviceContextHandle,size.x,size.y);
	}

#endif

#if __TEXPROJECT_DEBUG__
	Window::ErrorTest();
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
	Basic::Delete();

	if(renderContext)
	{
		if(init)
		{
			if(renderContext->Use())
			{
				if(func[FuncTypes::Free]) func[FuncTypes::Free](this);
			}
		}

		renderContext->Delete();
		delete renderContext;
		renderContext = nullptr;
	}

#if __TEXPROJECT_WIN__

	if(dbBitmap)
	{
		DeleteObject(dbBitmap);
		dbBitmap = NULL;
	}
	if(dbHDC)
	{
		DeleteDC(dbHDC);
		dbHDC = NULL;
	}

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
			{
				RECT rect;
				GetClientRect(wndHandle,&rect);
				size.x = (uint32)rect.right;
				size.y = (uint32)rect.bottom;

				POINT p;
				p.x = 0;
				p.y = (LONG)size.y;
				ClientToScreen(wndHandle,&p);
				pos = ivec2(FromDesktopSpace(vec2((float32)p.x,(float32)p.y)));
			}

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
					{
						if(func[FuncTypes::Loop]) func[FuncTypes::Loop](this);
						renderContext->Loop();
					}
					renderContext->Unuse();
				}
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

void					TexProject::Window::Render::SetSize(const uvec2 size_)
{
	if(size.x != size_.x || size.y != size_.y)
	{
		pos += (ivec2(size) - ivec2(size_))/2;
		size = size_;
#ifdef __TEXPROJECT_WIN__
		if(wndHandle)
		{
			{
				vec2 p;
				p = ToDesktopSpace(vec2(pos));
				wndRect.left	= (LONG)(p.x);
				wndRect.bottom	= (LONG)(p.y);
				p = ToDesktopSpace(vec2(pos + ivec2(size)));
				wndRect.right	= (LONG)(p.x);
				wndRect.top		= (LONG)(p.y);
			}
			AdjustWindowRectEx(&wndRect,wndStyle,FALSE,wndExStyle);
			SetWindowPos
			(
				wndHandle,
				HWND_NOTOPMOST,
				wndRect.left,
				wndRect.top,
				wndRect.right - wndRect.left,
				wndRect.bottom - wndRect.top,
				SWP_NOZORDER	//SWP_NOMOVE
			);
			UpdateWindow(wndHandle);
		}
		{
			if(dbHDC) DeleteDC(dbHDC);
			dbHDC = CreateCompatibleDC(wndDeviceContextHandle);
			if(dbBitmap) DeleteObject(dbBitmap);
			dbBitmap = CreateCompatibleBitmap(wndDeviceContextHandle,size.x,size.y);
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
				vec2 p;
				p = ToDesktopSpace(vec2(pos));
				wndRect.left	= (LONG)(p.x);
				wndRect.bottom	= (LONG)(p.y);
				p = ToDesktopSpace(vec2(pos + ivec2(size)));
				wndRect.right	= (LONG)(p.x);
				wndRect.top		= (LONG)(p.y);
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

void*					TexProject::Window::Render::GetHandle()
{
	return wndHandle;
}

void					TexProject::Window::Render::SetRenderContext(const RenderContext::Type& type_)
{
	if(renderContext)
	{
		renderContext->Delete();
		delete renderContext;
		renderContext = nullptr;
	}

	switch(type_)
	{
#ifdef __TEXPROJECT_WIN__
		case RenderContext::Type::Default:
		{
			renderContext = new RenderContext::Default(this);
			break;
		}
#endif
#ifdef __TEXPROJECT_OPENGL__
		case RenderContext::Type::OpenGL:
		{
			renderContext = new RenderContext::OpenGL(this);
			break;
		}
#endif
#ifdef __TEXPROJECT_DIRECT3D__
		case RenderContext::Type::Direct3D:
		{
			renderContext = new RenderContext::Direct3D(this);
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
			renderContext->Unuse();
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



























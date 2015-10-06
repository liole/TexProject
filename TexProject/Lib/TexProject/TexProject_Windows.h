#pragma once
#pragma region TexProject Includes
#include <TexProject/TexProject_Header.h>
using namespace TexProject;

#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Helpers.h>
#pragma endregion
#pragma region Includes
#include <time.h>
#pragma endregion


#pragma region Test
#pragma endregion


namespace TexProject
{
	class Input
	{
	public:
		class Key
		{
		public:
			bool						state = false;
			bool						press = false;

			inline						Key() = default;
			inline						~Key() = default;

			inline void					Loop();
			inline void					Flush();
			inline void					Press();
		};
		class Mouse
		{
		public:
			Key								lB,mB,rB;
			ivec2							pos = ivec2(0);

			inline bool						Init();
			inline void						Loop();
			inline void						Free();
			inline void						Flush();
		};
		class Keyboard
		{
		public:
			struct KeyCodes
			{
				static const uint32			count = 108;
				enum Enum
				{
					ESC						= 0,
					F1						= 1,
					F2						= 2,
					F3						= 4,
					F4						= 5,
					F5						= 6,
					F6						= 7,
					F7						= 8,
					F8						= 9,
					F9						= 10,
					F10						= 11,
					F11						= 12,
					F12						= 13,
					PrtScr					= 14,
					SCROLL_LOCK				= 15,
					PAUSE					= 16,
					TILDE					= 17,
					DIGIT1					= 18,
					DIGIT2					= 19,
					DIGIT3					= 20,
					DIGIT4					= 21,
					DIGIT5					= 22,
					DIGIT6					= 23,
					DIGIT7					= 24,
					DIGIT8					= 25,
					DIGIT9					= 26,
					DIGIT0					= 27,
					MINUS					= 28,
					PLUS					= 29,
					BACKSPACE				= 30,
					TAB						= 31,
					Q						= 32,
					W						= 33,
					E						= 34,
					R						= 35,
					T						= 36,
					Y						= 37,
					U						= 38,
					I						= 39,
					O						= 40,
					P						= 41,
					L_CLIP					= 42,		// {
					R_CLIP					= 43,		// }
					ENTER					= 44,
					CAPS_LOCK				= 45,
					A						= 46,
					S						= 47,
					D						= 48,
					F						= 49,
					G						= 50,
					H						= 51,
					J						= 52,
					K						= 53,
					L						= 54,
					COLON					= 55,		// ;
					QUOTE					= 56,		// '
					DASH					= 57,		// \0
					BACKSLASH				= 58,		// \0
					Z						= 59,
					X						= 60,
					C						= 61,
					V						= 62,
					B						= 63,
					N						= 64,
					M						= 65,
					COMM					= 66,		// ,
					DOT						= 67,		// .
					SLASH					= 68,		// /
					L_SHIFT					= 69,
					R_SHIFT					= 70,
					SHIFT					= 71,
					L_ALT					= 72,
					R_ALT					= 73,
					ALT						= 74,
					L_CTRL					= 75,
					R_CTRL					= 76,
					CTRL					= 77,
					L_WIN					= 78,
					R_WIN					= 79,
					WIN						= 80,
					SPACE					= 81,
					MENU					= 82,
					INS						= 83,
					DEL						= 84,
					HOME					= 85,
					END						= 86,
					PAGE_UP					= 87,
					PAGE_DOWN				= 88,
					UP						= 89,
					DOWN					= 90,
					RIGHT					= 91,
					LEFT					= 92,
					NUM_LOCK				= 93,
					NUM_DIV					= 94,
					NUM_MUL					= 95,
					NUM_SUB					= 96,
					NUM_ADD					= 97,
					NUM_DIGIT1				= 98,
					NUM_DIGIT2				= 99,
					NUM_DIGIT3				= 100,
					NUM_DIGIT4				= 101,
					NUM_DIGIT5				= 102,
					NUM_DIGIT6				= 103,
					NUM_DIGIT7				= 104,
					NUM_DIGIT8				= 105,
					NUM_DIGIT9				= 106,
					NUM_DIGIT0				= 107
				};
			};
			typedef KeyCodes::Enum			KeyCode;

			Key								keys[KeyCodes::count];

			inline bool						Init();
			inline void						Loop();
			inline void						Free();
			inline void						Flush();
		};

		Mouse								mouse;
		Keyboard							keyboard;

		inline bool							Init();
		inline void							Loop();
		inline void							Free();
		inline void							Flush();
	};
	typedef Input::Keyboard::KeyCode							Key;
#pragma region Input Functions
	inline uvec2		GetDesktopSize();
	inline bool			MouseLState();
	inline bool			MouseMState();
	inline bool			MouseRState();
	inline bool			MouseLPress();
	inline bool			MouseMPress();
	inline bool			MouseRPress();
	inline void			MousePressL();
	inline void			MousePressM();
	inline void			MousePressR();
	inline ivec2		MousePos();
	inline bool			KeyState(const Input::Keyboard::KeyCode& key);
	inline bool			KeyPress(const Input::Keyboard::KeyCode& key);
	inline void			PressKey(const Input::Keyboard::KeyCode& key);
#pragma endregion
	class ContextBind
	{
	protected:
		RenderContext*const					renderContext;
	public:
		inline								ContextBind(RenderContext* renderContext_);
		inline RenderContext*				GetRenderContext() const;
	};
	class WindowBind
	{
	protected:
		Window*const						window;
	public:
		inline								WindowBind(Window* window_);
		inline Window*						GetWindow() const;
	};
	class RenderContext:
		public WindowBind
	{
		friend Window;
	public:
		enum class Type
		{
#if __TEXPROJECT_OPENGL__
			OpenGL							= 1,
#endif
#if __TEXPROJECT_DIRECT3D__
			Direct3D						= 2,
#endif
			Default							= 0
		};
	protected:
		virtual bool						Use();
		virtual void						Unuse();
		virtual void						Loop();
	public:
		inline								RenderContext(Window* window_);
		virtual								~RenderContext() = default;
		virtual Type						GetType() const = 0;
	};
	class Window:
		public Helper::Structure::ClassList<Window>
	{
#pragma region Input
		friend bool			MouseLState();
		friend bool			MouseMState();
		friend bool			MouseRState();
		friend bool			MouseLPress();
		friend bool			MouseMPress();
		friend bool			MouseRPress();
		friend void			MousePressL();
		friend void			MousePressM();
		friend void			MousePressR();
		friend ivec2		MousePos();
		friend bool			KeyState(const Input::Keyboard::KeyCode& key);
		friend bool			KeyPress(const Input::Keyboard::KeyCode& key);
		friend void			PressKey(const Input::Keyboard::KeyCode& key);
	protected:
		static Input						input;
#pragma endregion
#pragma region Desktop
		inline uvec2						GetDesktopSize();
		inline vec2							ToDesktopSpace(vec2 input);
		inline vec2							FromDesktopSpace(vec2 input);
#pragma endregion
#pragma region Errors
	public:
		static inline bool					ErrorTest();
#pragma endregion
#pragma region Platform-Dependent
#if __TEXPROJECT_WIN__
		friend WinAPI::RenderContext;
	protected:
		class _win_StaticData
		{
			friend Window;
		protected:
			const string					wndClassName = "[TexProject Window Class]";
			WNDCLASSEX						wndClassEx;
			DWORD							wndStyle;
			DWORD							wndExStyle;
			RECT							wndRect;
			PIXELFORMATDESCRIPTOR			wndPixelFormatDescriptor;
			inline							_win_StaticData();
			inline							~_win_StaticData();
			static LRESULT CALLBACK			CallbackDefault(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
		};
		static _win_StaticData				_win_staticData;
	protected:
		HWND								_win_windowHandle = NULL;
		HDC									_win_windowDeviceContextHandle = NULL;
		clock_t								vSyncTimer = 0, oVSyncTimer = 0;
	public:
		inline void							_win_RectToWindow(RECT& rect_,const vec2& a,const vec2& b);
#endif
#if __TEXPROJECT_OPENGL__
		friend OpenGL::RenderContext;
#endif
#pragma endregion
#pragma region Create/Delete/Loop
	public:
		static inline bool					Process();
	public:
		inline								Window();
		inline								~Window();
		inline void							Create();
		inline void							Delete();
	protected:
		void								Loop();
#pragma endregion
#pragma region Func
	public:
		typedef void(*Func)(Window*);
		enum class FuncType: uint32
		{
			Init							= 0,
			Free							= 1,
			Loop							= 2
		};
	protected:
		static const uint32					funcCount = 3;
		Func								func[3];
		inline void							CallFunc(FuncType type_);
	public:
		inline void							SetFunc(FuncType type_,Func func_);
#pragma endregion
#pragma region Basic Parameters
	protected:
		string								title = "Window";
		ivec2								pos = ivec2(0);
		uvec2								size = uvec2(100);
		bool								init = false;
		bool								active = false;
		bool								running = false;
		bool								vSync = true;
		void*								userData = nullptr;
		bool								userDataClearing = false;
	public:
		inline void							SetTitle(const string& title_);
		inline string						GetTitle() const;
		inline void							SetPos(const ivec2& pos_);
		inline ivec2						GetPos() const;
		inline void							SetSize(const uvec2& size_);
		inline uvec2						GetSize() const;
		inline float32						GetAspect() const;
		inline bool							IsInit() const;
		inline bool							IsActive() const;
		inline bool							IsRunning() const;
		inline void							EnableVSync();
		inline void							DisaleVSync();
		inline bool							IsVSync() const;
		inline void							SetUserData(void* userData_,bool autoRemove_ = false);
		inline void*						GetUserData() const;
#pragma endregion
#pragma region RenderContext
	protected:
		RenderContext*						renderContext = nullptr;
	public:
		inline RenderContext*				GetRenderContext() const;
		void								SetRenderContext(RenderContext::Type type_);
#pragma endregion
#pragma region GUI
		protected:
			GUI*							gui = nullptr;
		public:
			inline GUI*						GetGUI() const;
#pragma endregion
	};
}
#pragma region Input
#pragma region Input
bool															TexProject::Input::Init()
{
	if(!mouse.Init()) return false;
	if(!keyboard.Init()) return false;
	return true;
}
void															TexProject::Input::Loop()
{
	mouse.Loop();
	keyboard.Loop();
}
void															TexProject::Input::Free()
{
	mouse.Free();
	keyboard.Free();
}
void															TexProject::Input::Flush()
{
	mouse.Flush();
	keyboard.Flush();
}
#pragma region Key
void															TexProject::Input::Key::Loop()
{
	if(!state) press = false;
}
void															TexProject::Input::Key::Flush()
{
	state = false;
	press = false;
}
void															TexProject::Input::Key::Press()
{
	press = true;
}
#pragma endregion
#pragma region Mouse
bool					TexProject::Input::Mouse::Init()
{
	return true;
}
void					TexProject::Input::Mouse::Loop()
{
	static POINT t;
	GetCursorPos(&t);

	pos.x = t.x;
	pos.y = int32(GetDesktopSize().y) - t.y;

	lB.state = GetAsyncKeyState(VK_LBUTTON) != NULL;
	mB.state = GetAsyncKeyState(VK_MBUTTON) != NULL;
	rB.state = GetAsyncKeyState(VK_RBUTTON) != NULL;

	//GetDoubleClickTime();

	lB.Loop();
	mB.Loop();
	rB.Loop();
}
void					TexProject::Input::Mouse::Free()
{
}
void					TexProject::Input::Mouse::Flush()
{
	pos = ivec2(0,0);
	lB.Flush();
	mB.Flush();
	rB.Flush();
}
#pragma endregion
#pragma region Keyboard
bool					TexProject::Input::Keyboard::Init()
{
	return true;
}
void					TexProject::Input::Keyboard::Loop()
{
	{
		keys[KeyCode::ESC].state								= GetAsyncKeyState(VK_ESCAPE) != 0;
		keys[KeyCode::F1].state									= GetAsyncKeyState(VK_F1) != 0;
		keys[KeyCode::F2].state									= GetAsyncKeyState(VK_F2) != 0;
		keys[KeyCode::F3].state									= GetAsyncKeyState(VK_F3) != 0;
		keys[KeyCode::F4].state									= GetAsyncKeyState(VK_F4) != 0;
		keys[KeyCode::F5].state									= GetAsyncKeyState(VK_F5) != 0;
		keys[KeyCode::F6].state									= GetAsyncKeyState(VK_F6) != 0;
		keys[KeyCode::F7].state									= GetAsyncKeyState(VK_F7) != 0;
		keys[KeyCode::F8].state									= GetAsyncKeyState(VK_F8) != 0;
		keys[KeyCode::F9].state									= GetAsyncKeyState(VK_F9) != 0;
		keys[KeyCode::F10].state								= GetAsyncKeyState(VK_F10) != 0;
		keys[KeyCode::F11].state								= GetAsyncKeyState(VK_F11) != 0;
		keys[KeyCode::F12].state								= GetAsyncKeyState(VK_F2) != 0;
		keys[KeyCode::PrtScr].state								= GetAsyncKeyState(VK_SNAPSHOT) != 0;
		keys[KeyCode::SCROLL_LOCK].state						= GetAsyncKeyState(VK_SCROLL) != 0;
		keys[KeyCode::PAUSE].state								= GetAsyncKeyState(VK_PAUSE) != 0;

		keys[KeyCode::TILDE].state								= GetAsyncKeyState(VK_OEM_3) != 0;
		keys[KeyCode::DIGIT1].state								= GetAsyncKeyState('1') != 0;
		keys[KeyCode::DIGIT2].state								= GetAsyncKeyState('2') != 0;
		keys[KeyCode::DIGIT3].state								= GetAsyncKeyState('3') != 0;
		keys[KeyCode::DIGIT4].state								= GetAsyncKeyState('4') != 0;
		keys[KeyCode::DIGIT5].state								= GetAsyncKeyState('5') != 0;
		keys[KeyCode::DIGIT6].state								= GetAsyncKeyState('6') != 0;
		keys[KeyCode::DIGIT7].state								= GetAsyncKeyState('7') != 0;
		keys[KeyCode::DIGIT8].state								= GetAsyncKeyState('8') != 0;
		keys[KeyCode::DIGIT9].state								= GetAsyncKeyState('9') != 0;
		keys[KeyCode::DIGIT0].state								= GetAsyncKeyState('0') != 0;
		keys[KeyCode::MINUS].state								= GetAsyncKeyState(VK_OEM_MINUS) != 0;
		keys[KeyCode::PLUS].state								= GetAsyncKeyState(VK_OEM_PLUS) != 0;
		keys[KeyCode::BACKSPACE].state							= GetAsyncKeyState(VK_BACK) != 0;

		keys[KeyCode::TAB].state								= GetAsyncKeyState(VK_TAB) != 0;
		keys[KeyCode::Q].state									= GetAsyncKeyState('Q') != 0;
		keys[KeyCode::W].state									= GetAsyncKeyState('W') != 0;
		keys[KeyCode::E].state									= GetAsyncKeyState('E') != 0;
		keys[KeyCode::R].state									= GetAsyncKeyState('R') != 0;
		keys[KeyCode::T].state									= GetAsyncKeyState('T') != 0;
		keys[KeyCode::Y].state									= GetAsyncKeyState('Y') != 0;
		keys[KeyCode::U].state									= GetAsyncKeyState('U') != 0;
		keys[KeyCode::I].state									= GetAsyncKeyState('I') != 0;
		keys[KeyCode::O].state									= GetAsyncKeyState('O') != 0;
		keys[KeyCode::P].state									= GetAsyncKeyState('P') != 0;
		keys[KeyCode::L_CLIP].state								= GetAsyncKeyState(VK_OEM_4) != 0;
		keys[KeyCode::R_CLIP].state								= GetAsyncKeyState(VK_OEM_6) != 0;
		keys[KeyCode::ENTER].state								= GetAsyncKeyState(VK_RETURN) != 0;

		keys[KeyCode::CAPS_LOCK].state							= GetAsyncKeyState(VK_CAPITAL) != 0;
		keys[KeyCode::A].state									= GetAsyncKeyState('A') != 0;
		keys[KeyCode::S].state									= GetAsyncKeyState('S') != 0;
		keys[KeyCode::D].state									= GetAsyncKeyState('D') != 0;
		keys[KeyCode::F].state									= GetAsyncKeyState('F') != 0;
		keys[KeyCode::G].state									= GetAsyncKeyState('G') != 0;
		keys[KeyCode::H].state									= GetAsyncKeyState('H') != 0;
		keys[KeyCode::J].state									= GetAsyncKeyState('J') != 0;
		keys[KeyCode::K].state									= GetAsyncKeyState('K') != 0;
		keys[KeyCode::L].state									= GetAsyncKeyState('L') != 0;
		keys[KeyCode::COLON].state								= GetAsyncKeyState(VK_OEM_1) != 0;
		keys[KeyCode::QUOTE].state								= GetAsyncKeyState(VK_OEM_7) != 0;
		keys[KeyCode::DASH].state								= GetAsyncKeyState(VK_OEM_5) != 0;

		keys[KeyCode::BACKSLASH].state							= GetAsyncKeyState(VK_OEM_102) != 0;
		keys[KeyCode::Z].state									= GetAsyncKeyState('Z') != 0;
		keys[KeyCode::X].state									= GetAsyncKeyState('X') != 0;
		keys[KeyCode::C].state									= GetAsyncKeyState('C') != 0;
		keys[KeyCode::V].state									= GetAsyncKeyState('V') != 0;
		keys[KeyCode::B].state									= GetAsyncKeyState('B') != 0;
		keys[KeyCode::N].state									= GetAsyncKeyState('N') != 0;
		keys[KeyCode::M].state									= GetAsyncKeyState('M') != 0;
		keys[KeyCode::COMM].state								= GetAsyncKeyState(VK_OEM_COMMA) != 0;
		keys[KeyCode::DOT].state								= GetAsyncKeyState(VK_OEM_PERIOD) != 0;
		keys[KeyCode::SLASH].state								= GetAsyncKeyState(VK_OEM_2) != 0;

		keys[KeyCode::L_SHIFT].state							= GetAsyncKeyState(VK_LSHIFT) != 0;
		keys[KeyCode::R_SHIFT].state							= GetAsyncKeyState(VK_RSHIFT) != 0;
		keys[KeyCode::SHIFT].state								= keys[KeyCode::L_SHIFT].state || keys[KeyCode::R_SHIFT].state;
		keys[KeyCode::L_ALT].state								= GetAsyncKeyState(VK_LMENU) != 0;
		keys[KeyCode::R_ALT].state								= GetAsyncKeyState(VK_RMENU) != 0;
		keys[KeyCode::ALT].state								= keys[KeyCode::L_ALT].state || keys[KeyCode::R_ALT].state;
		keys[KeyCode::L_CTRL].state								= GetAsyncKeyState(VK_LCONTROL) != 0;
		keys[KeyCode::R_CTRL].state								= GetAsyncKeyState(VK_RCONTROL) != 0;
		keys[KeyCode::CTRL].state								= keys[KeyCode::L_CTRL].state || keys[KeyCode::R_CTRL].state;
		keys[KeyCode::L_WIN].state								= GetAsyncKeyState(VK_LWIN) != 0;
		keys[KeyCode::R_WIN].state								= GetAsyncKeyState(VK_RWIN) != 0;
		keys[KeyCode::WIN].state								= keys[KeyCode::L_WIN].state || keys[KeyCode::R_WIN].state;
		keys[KeyCode::SPACE].state								= GetAsyncKeyState(VK_SPACE) != 0;
		keys[KeyCode::MENU].state								= GetAsyncKeyState(VK_APPS) != 0;

		keys[KeyCode::INS].state								= GetAsyncKeyState(VK_INSERT) != 0;
		keys[KeyCode::DEL].state								= GetAsyncKeyState(VK_DELETE) != 0;
		keys[KeyCode::HOME].state								= GetAsyncKeyState(VK_HOME) != 0;
		keys[KeyCode::END].state								= GetAsyncKeyState(VK_END) != 0;
		keys[KeyCode::PAGE_UP].state							= GetAsyncKeyState(VK_PRIOR) != 0;
		keys[KeyCode::PAGE_DOWN].state							= GetAsyncKeyState(VK_NEXT) != 0;

		keys[KeyCode::UP].state									= GetAsyncKeyState(VK_UP) != 0;
		keys[KeyCode::DOWN].state								= GetAsyncKeyState(VK_DOWN) != 0;
		keys[KeyCode::RIGHT].state								= GetAsyncKeyState(VK_RIGHT) != 0;
		keys[KeyCode::LEFT].state								= GetAsyncKeyState(VK_LEFT) != 0;

		keys[KeyCode::NUM_LOCK].state							= GetAsyncKeyState(VK_NUMLOCK) != 0;
		keys[KeyCode::NUM_DIV].state							= GetAsyncKeyState(VK_DIVIDE) != 0;
		keys[KeyCode::NUM_MUL].state							= GetAsyncKeyState(VK_MULTIPLY) != 0;
		keys[KeyCode::NUM_SUB].state							= GetAsyncKeyState(VK_SUBTRACT) != 0;
		keys[KeyCode::NUM_ADD].state							= GetAsyncKeyState(VK_ADD) != 0;

		keys[KeyCode::NUM_DIGIT1].state							= GetAsyncKeyState(VK_NUMPAD1) != 0;
		keys[KeyCode::NUM_DIGIT2].state							= GetAsyncKeyState(VK_NUMPAD2) != 0;
		keys[KeyCode::NUM_DIGIT3].state							= GetAsyncKeyState(VK_NUMPAD3) != 0;
		keys[KeyCode::NUM_DIGIT4].state							= GetAsyncKeyState(VK_NUMPAD4) != 0;
		keys[KeyCode::NUM_DIGIT5].state							= GetAsyncKeyState(VK_NUMPAD5) != 0;
		keys[KeyCode::NUM_DIGIT6].state							= GetAsyncKeyState(VK_NUMPAD6) != 0;
		keys[KeyCode::NUM_DIGIT7].state							= GetAsyncKeyState(VK_NUMPAD7) != 0;
		keys[KeyCode::NUM_DIGIT8].state							= GetAsyncKeyState(VK_NUMPAD8) != 0;
		keys[KeyCode::NUM_DIGIT9].state							= GetAsyncKeyState(VK_NUMPAD9) != 0;
		keys[KeyCode::NUM_DIGIT0].state							= GetAsyncKeyState(VK_NUMPAD0) != 0;
	}
	for(uint32 i = 0; i < KeyCodes::count; ++i) keys[i].Loop();
}
void					TexProject::Input::Keyboard::Free()
{
}
void					TexProject::Input::Keyboard::Flush()
{
	for(uint32 i = 0; i < KeyCodes::count; ++i) keys[i].Flush();
}
#pragma endregion
#pragma endregion
#pragma endregion
#pragma region RenderContext
inline TexProject::RenderContext::RenderContext(Window* window_):
	WindowBind(window_)
{
}
#pragma endregion
#pragma region Window
#pragma region Desktop
inline TexProject::uvec2										TexProject::Window::GetDesktopSize()
{
#if __TEXPROJECT_WIN__
	return uvec2
	(
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN)
	);
#endif
}
inline TexProject::vec2											TexProject::Window::ToDesktopSpace(vec2 input)
{
#if __TEXPROJECT_WIN__
	return vec2(input.x,GetDesktopSize().y - input.y);
#endif
}
inline TexProject::vec2											TexProject::Window::FromDesktopSpace(vec2 input)
{
#if __TEXPROJECT_WIN__
	return vec2(input.x,GetDesktopSize().y - input.y);
#endif
}
#pragma endregion
#pragma region Errors
inline bool									TexProject::Window::ErrorTest()
{
#if __TEXPROJECT_WIN__
	auto error = GetLastError();
	if(error != NO_ERROR)
	{
		do
		{
			string text = "[WinAPI]\n";
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
#endif
}
#pragma endregion
#pragma region Platform-Dependent
#if __TEXPROJECT_WIN__
inline															TexProject::Window::_win_StaticData::_win_StaticData()
{
	{
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
		wndClassEx.lpfnWndProc		= CallbackDefault;
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
		//wndStyle	=  WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_BORDER;	//WS_POPUP;
		wndStyle	=  WS_BORDER | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_OVERLAPPED | WS_SIZEBOX | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE;
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
		wndExStyle	= WS_EX_APPWINDOW;//| WS_EX_TOOLWINDOW;
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

#if __TEXPROJECT_DEBUG__
	Window::ErrorTest();
#endif
}
inline															TexProject::Window::_win_StaticData::~_win_StaticData()
{
	UnregisterClass(wndClassName.c_str(),EntryPointData::hInstance);

#if __TEXPROJECT_DEBUG__
	Window::ErrorTest();
#endif
}
inline void														TexProject::Window::_win_RectToWindow(RECT& rect_,const vec2& a,const vec2& b)
{
	rect_.left = (LONG)(a.x);
	rect_.right = (LONG)(b.x);
	rect_.top = (LONG)(size.y - b.y);
	rect_.bottom = (LONG)(size.y - a.y);
}
#endif
#pragma endregion
#pragma region Create/Delete/Loop
inline bool														TexProject::Window::Process()
{
	input.Loop();

	bool res = false;
	for(auto i: list)
	{
		i->Loop();
		if(i->IsRunning()) res = true;
	}

	return res;
}
inline															TexProject::Window::Window()
{
	for(uint32 i = 0; i < funcCount; ++i) func[i] = nullptr;
}
inline															TexProject::Window::~Window()
{
	Delete();

	SetUserData(nullptr);
}
inline void														TexProject::Window::Create()
{
	Delete();

#if __TEXPROJECT_WIN__

	{
		size = uvec2(800,600);
		pos = (vec2(GetDesktopSize()) - vec2(size))*0.5f;
		title = "test";//title_;
	}

	{
		vec2 p;
		p = ToDesktopSpace(vec2(pos));
		_win_staticData.wndRect.left	= (LONG)(p.x);
		_win_staticData.wndRect.bottom	= (LONG)(p.y);
		p = ToDesktopSpace(vec2(pos + ivec2(size)));
		_win_staticData.wndRect.right	= (LONG)(p.x);
		_win_staticData.wndRect.top		= (LONG)(p.y);
	}

	AdjustWindowRectEx(&_win_staticData.wndRect,_win_staticData.wndStyle,FALSE,_win_staticData.wndExStyle);

	_win_windowHandle =	CreateWindowEx
	(
		_win_staticData.wndExStyle,
		_win_staticData.wndClassName.c_str(),
		title.c_str(),
		_win_staticData.wndStyle,
		_win_staticData.wndRect.left,
		_win_staticData.wndRect.top,
		_win_staticData.wndRect.right - _win_staticData.wndRect.left,
		_win_staticData.wndRect.bottom - _win_staticData.wndRect.top,
		NULL,
		(HMENU)NULL,
		_win_staticData.wndClassEx.hInstance,
		NULL
	);

	GetClientRect(_win_windowHandle,&_win_staticData.wndRect);
	{
		size.x = _win_staticData.wndRect.right - _win_staticData.wndRect.left;
		size.y = _win_staticData.wndRect.bottom - _win_staticData.wndRect.top;

		static POINT p;
		p.x = 0;
		p.y = (LONG)size.y;
		ClientToScreen(_win_windowHandle,&p);
		pos = ivec2(FromDesktopSpace(vec2((float32)p.x,(float32)p.y)));
	}

	if(!_win_windowHandle)
	{
		Message("Can't create window.");
		return;
	}
#if __TEXPROJECT_DEBUG__
	Window::ErrorTest();
#endif

	UpdateWindow(_win_windowHandle);

	{
		_win_windowDeviceContextHandle = GetDC(_win_windowHandle);
	}
	if(!_win_windowDeviceContextHandle)
	{
#if __TEXPROJECT_DEBUG__
		Window::ErrorTest();
#endif
		Message("Cannot create device context.");
		return;
	}

	{
		auto pixelFormat = ChoosePixelFormat(_win_windowDeviceContextHandle,&_win_staticData.wndPixelFormatDescriptor);
		if(!pixelFormat)
		{
#if __TEXPROJECT_DEBUG__
			Window::ErrorTest();
#endif
			Message("Can't chose pixel format.");
			return;
		}
		if(!SetPixelFormat(_win_windowDeviceContextHandle,pixelFormat,&_win_staticData.wndPixelFormatDescriptor))
		{
#if __TEXPROJECT_DEBUG__
			Window::ErrorTest();
#endif
			Message("Can't set pixel format.");
			return;
		}
	}

	SetWindowLongPtr(_win_windowHandle,GWLP_USERDATA,(LONG)this);
	/*
	GWL_EXSTYLE
	GWLP_HINSTANCE
	GWLP_ID
	GWL_STYLE
	GWLP_USERDATA
	GWLP_WNDPROC
	*/

#if __TEXPROJECT_DEBUG__
	Window::ErrorTest();
#endif

#endif

	init = true;
	running = true;

	if(renderContext && renderContext->Use())
	{
		CallFunc(FuncType::Init);
		renderContext->Unuse();
	}
}
inline void														TexProject::Window::Delete()
{
	if(init)
	{
		if(renderContext && renderContext->Use())
		{
			CallFunc(FuncType::Free);
			renderContext->Unuse();
		}

#if __TEXPROJECT_WIN__
	if(_win_windowHandle)
	{
		if(_win_windowDeviceContextHandle)
		{
			if(!ReleaseDC(_win_windowHandle,_win_windowDeviceContextHandle))
			{
				Error("Can't Release hDC.");
			}
			_win_windowDeviceContextHandle = 0;
		}

		DestroyWindow(_win_windowHandle);
		_win_windowHandle = NULL;
	}
#endif

		init = false;
	}
}
#pragma endregion
#pragma region Func
inline void														TexProject::Window::CallFunc(FuncType type_)
{
	if(func[(uint32)type_]) func[(uint32)type_](this);
}
inline void														TexProject::Window::SetFunc(FuncType type_,Func func_)
{
	func[(uint32)type_] = func_;
}
#pragma endregion
#pragma region Basic Parameters
inline void														TexProject::Window::SetTitle(const string& title_)
{
	title = title_;
}
inline TexProject::string										TexProject::Window::GetTitle() const
{
	return std::move(title);
}
inline void														TexProject::Window::SetPos(const ivec2& pos_)
{
	if(pos.x != pos_.x || pos.y != pos_.y)
	{
		pos = pos_;
#ifdef __TEXPROJECT_WIN__
		if(_win_windowHandle)
		{
			{
				vec2 p;
				p = ToDesktopSpace(vec2(pos));
				_win_staticData.wndRect.left	= (LONG)(p.x);
				_win_staticData.wndRect.bottom	= (LONG)(p.y);
				p = ToDesktopSpace(vec2(pos + ivec2(size)));
				_win_staticData.wndRect.right	= (LONG)(p.x);
				_win_staticData.wndRect.top		= (LONG)(p.y);
			}
			AdjustWindowRectEx(&_win_staticData.wndRect,_win_staticData.wndStyle,FALSE,_win_staticData.wndExStyle);
			SetWindowPos
			(
				_win_windowHandle,
				HWND_NOTOPMOST,
				_win_staticData.wndRect.left,
				_win_staticData.wndRect.top,
				_win_staticData.wndRect.right-_win_staticData.wndRect.left,
				_win_staticData.wndRect.bottom-_win_staticData.wndRect.top,
				SWP_NOZORDER	//SWP_NOSIZE
			);
			UpdateWindow(_win_windowHandle);
		}
#endif
	}
}
inline TexProject::ivec2										TexProject::Window::GetPos() const
{
	return pos;
}
inline void														TexProject::Window::SetSize(const uvec2& size_)
{
	if(size.x != size_.x || size.y != size_.y)
	{
		pos += (ivec2(size) - ivec2(size_))/2;
		size = size_;
#ifdef __TEXPROJECT_WIN__
		if(_win_windowHandle)
		{
			{
				vec2 p;
				p = ToDesktopSpace(vec2(pos));
				_win_staticData.wndRect.left	= (LONG)(p.x);
				_win_staticData.wndRect.bottom	= (LONG)(p.y);
				p = ToDesktopSpace(vec2(pos + ivec2(size)));
				_win_staticData.wndRect.right	= (LONG)(p.x);
				_win_staticData.wndRect.top		= (LONG)(p.y);
			}
			AdjustWindowRectEx(&_win_staticData.wndRect,_win_staticData.wndStyle,FALSE,_win_staticData.wndExStyle);
			SetWindowPos
			(
				_win_windowHandle,
				HWND_NOTOPMOST,
				_win_staticData.wndRect.left,
				_win_staticData.wndRect.top,
				_win_staticData.wndRect.right-_win_staticData.wndRect.left,
				_win_staticData.wndRect.bottom-_win_staticData.wndRect.top,
				SWP_NOZORDER	//SWP_NOMOVE
			);
			UpdateWindow(_win_windowHandle);
		}
#endif
	}
}
inline TexProject::uvec2										TexProject::Window::GetSize() const
{
	return size;
}
inline TexProject::float32										TexProject::Window::GetAspect() const
{
	return float32(size.x)/float32(size.y);
}
inline bool														TexProject::Window::IsInit() const
{
	return init;
}
inline bool														TexProject::Window::IsActive() const
{
	return active;
}
inline bool														TexProject::Window::IsRunning() const
{
	return running;
}
inline void														TexProject::Window::EnableVSync()
{
	vSync = true;
}
inline void														TexProject::Window::DisaleVSync()
{
	vSync = false;
}
inline bool														TexProject::Window::IsVSync() const
{
	return vSync;
}
inline void														TexProject::Window::SetUserData(void* data_,bool clearing_)
{
	if(userData)
	{
		if(userDataClearing) delete userData;
		userData = nullptr;
	}

	userData = data_;

	userDataClearing = clearing_;
}
inline void*													TexProject::Window::GetUserData() const
{
	return userData;
}

#pragma endregion
#pragma region RenderContext
inline TexProject::RenderContext*								TexProject::Window::GetRenderContext() const
{
	return renderContext;
}
#pragma endregion
#pragma region GUI
inline TexProject::GUI*						TexProject::Window::GetGUI() const
{
	return gui;
}
#pragma endregion
#pragma endregion
#pragma region ContextBind
inline TexProject::ContextBind::ContextBind(RenderContext* renderContext_):
	renderContext(renderContext_)
{
}
inline TexProject::RenderContext*			TexProject::ContextBind::GetRenderContext() const
{
	return renderContext;
}
#pragma endregion
#pragma region WindowBind
inline TexProject::WindowBind::WindowBind(Window* window_):
	window(window_)
{
}
inline TexProject::Window*					TexProject::WindowBind::GetWindow() const
{
	return window;
}
#pragma endregion
#pragma region Input Functions
inline TexProject::uvec2										TexProject::GetDesktopSize()
{
#if __TEXPROJECT_WIN__
	return uvec2
	(
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN)
	);
#endif
}
inline bool														TexProject::MouseLState()
{
	return Window::input.mouse.lB.state;
}
inline bool														TexProject::MouseMState()
{
	return Window::input.mouse.mB.state;
}
inline bool														TexProject::MouseRState()
{
	return Window::input.mouse.rB.state;
}
inline bool														TexProject::MouseLPress()
{
	return Window::input.mouse.lB.press;
}
inline bool														TexProject::MouseMPress()
{
	return Window::input.mouse.mB.press;
}
inline bool														TexProject::MouseRPress()
{
	return Window::input.mouse.rB.press;
}
inline void														TexProject::MousePressL()
{
	Window::input.mouse.lB.press = true;
}
inline void														TexProject::MousePressM()
{
	Window::input.mouse.mB.press = true;
}
inline void														TexProject::MousePressR()
{
	Window::input.mouse.rB.press = true;
}
inline TexProject::ivec2										TexProject::MousePos()
{
	return Window::input.mouse.pos;
}
inline bool														TexProject::KeyState(const Input::Keyboard::KeyCode& key)
{
	return Window::input.keyboard.keys[key].state;
}
inline bool														TexProject::KeyPress(const Input::Keyboard::KeyCode& key)
{
	return Window::input.keyboard.keys[key].press;
}
inline void														TexProject::PressKey(const Input::Keyboard::KeyCode& key)
{
	Window::input.keyboard.keys[key].press = true;
}
#pragma endregion



















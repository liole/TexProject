/*
*/
#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_OpenGL.h>
#include <TexProject/TexProject_Helpers.h>
#include <TexProject/TexProject_Interface.h>


#include <time.h>
#include <list>


#ifdef __TEXPROJECT_WIN__

#include <Windows.h>

#else
#ifdef __TEXPROJECT_LIN__
// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
// MacOS variant
#endif
#endif
#endif


namespace TexProject
{

	namespace Window
	{
		/*���������, �� ������� �� ���*/
		namespace Input
		{
			/*������ ��������� ������*/
			struct Key
			{
				bool						state;
				bool						press;

				inline						Key();

				inline void					Loop();
				inline void					Flush();
				inline void					Press();
			};

			/*��������� ���������*/
			namespace Keyboard
			{
				struct KeyCodes
				{
					static const uint32		count = 108;
					enum Enum
					{
						ESC				= 0,
						F1				= 1,
						F2				= 2,
						F3				= 4,
						F4				= 5,
						F5				= 6,
						F6				= 7,
						F7				= 8,
						F8				= 9,
						F9				= 10,
						F10				= 11,
						F11				= 12,
						F12				= 13,
						PrtScr			= 14,
						SCROLL_LOCK		= 15,
						PAUSE			= 16,
						TILDE			= 17,
						DIGIT1			= 18,
						DIGIT2			= 19,
						DIGIT3			= 20,
						DIGIT4			= 21,
						DIGIT5			= 22,
						DIGIT6			= 23,
						DIGIT7			= 24,
						DIGIT8			= 25,
						DIGIT9			= 26,
						DIGIT0			= 27,
						MINUS			= 28,
						PLUS			= 29,
						BACKSPACE		= 30,
						TAB				= 31,
						Q				= 32,
						W				= 33,
						E				= 34,
						R				= 35,
						T				= 36,
						Y				= 37,
						U				= 38,
						I				= 39,
						O				= 40,
						P				= 41,
						L_CLIP			= 42,		// {
						R_CLIP			= 43,		// }
						ENTER			= 44,
						CAPS_LOCK		= 45,
						A				= 46,
						S				= 47,
						D				= 48,
						F				= 49,
						G				= 50,
						H				= 51,
						J				= 52,
						K				= 53,
						L				= 54,
						COLON			= 55,		// ;
						QUOTE			= 56,		// '
						DASH			= 57,		// \0
						BACKSLASH		= 58,		// \0
						Z				= 59,
						X				= 60,
						C				= 61,
						V				= 62,
						B				= 63,
						N				= 64,
						M				= 65,
						COMM			= 66,		// ,
						DOT				= 67,		// .
						SLASH			= 68,		// /
						L_SHIFT			= 69,
						R_SHIFT			= 70,
						SHIFT			= 71,
						L_ALT			= 72,
						R_ALT			= 73,
						ALT				= 74,
						L_CTRL			= 75,
						R_CTRL			= 76,
						CTRL			= 77,
						L_WIN			= 78,
						R_WIN			= 79,
						WIN				= 80,
						SPACE			= 81,
						MENU			= 82,
						INS				= 83,
						DEL				= 84,
						HOME			= 85,
						END				= 86,
						PAGE_UP			= 87,
						PAGE_DOWN		= 88,
						UP				= 89,
						DOWN			= 90,
						RIGHT			= 91,
						LEFT			= 92,
						NUM_LOCK		= 93,
						NUM_DIV			= 94,
						NUM_MUL			= 95,
						NUM_SUB			= 96,
						NUM_ADD			= 97,
						NUM_DIGIT1		= 98,
						NUM_DIGIT2		= 99,
						NUM_DIGIT3		= 100,
						NUM_DIGIT4		= 101,
						NUM_DIGIT5		= 102,
						NUM_DIGIT6		= 103,
						NUM_DIGIT7		= 104,
						NUM_DIGIT8		= 105,
						NUM_DIGIT9		= 106,
						NUM_DIGIT0		= 107
					};
				};
				typedef KeyCodes::Enum		KeyCode;

				extern Key					keys[KeyCodes::count];

				bool						Init();
				void						Loop();
				void						Free();
				void						Flush();
			};

			bool							Init();
			void							Loop();
			void							Free();
			void							Flush();
		}

		/*��������� ������*/
		namespace RenderContext
		{
			struct Types
			{
				enum Enum
				{
					Default,
					OpenGL
				};
			};
			typedef Types::Enum				Type;

			/*������� �������� ������*/
			struct Basic
			{
			protected:

				Window::Render*	const		window;
				bool						init = false;
				Interface::GUI*				inter = nullptr;

			public:
											Basic(Window::Render* window_);
											Basic(const Basic& source) = delete;
											Basic(Basic&& source) = delete;
				virtual						~Basic();

				Basic&						operator = (const Basic& source) = delete;
				Basic&						operator = (Basic&& source) = delete;

				virtual void				Create();
				virtual void				Delete();
				virtual void				Loop();
				virtual bool				Use();

				inline Interface::GUIPanelDefault*				AddPanelDefault();
				inline Interface::GUIButtonDefault*				AddButtonDefault();
				inline Interface::GUIButtonTrigger*				AddButtonTrigger();
				inline Interface::GUIButtonAction*				AddButtonAction();
				inline Interface::GUIButtonSlider*				AddButtonSlider();
				inline void										RemovePanel(Interface::GUIPanel* source);
				inline void										RemoveButton(Interface::GUIButton* source);
			};

			/*�������� Windows*/
#ifdef __TEXPROJECT_WIN__
			struct Default:
				public Basic
			{
			protected:

				HPEN						winPenRect = NULL;

			public:

				static void					Init();
				static void					Free();

											Default(Window::Render* window_);
											Default(const Default&) = delete;
											Default(Default&& source) = delete;
				virtual						~Default();

				Default&					operator = (const Default&) = delete;
				Default&					operator = (Default&&) = delete;

				virtual void				Create() override;
				virtual void				Delete() override;
				virtual void				Loop() override;
				virtual bool				Use() override;
			};
#endif
			/*�������� OpenGL*/
#ifdef __TEXPROJECT_OPENGL__
			struct OpenGL:
				public Basic
			{
			protected:

				static PFNWGLCREATECONTEXTATTRIBSARBPROC		wglCreateContextAttribsARB;

#ifdef __TEXPROJECT_WIN__

				HGLRC											wndRenderContextHandle;

#else
#ifdef __TEXPROJECT_LIN__
				// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
				// MacOS variant
#endif
#endif
#endif

			public:

				static void					Init();
				static void					Free();

											OpenGL(Window::Render* window_);
											OpenGL(const OpenGL&) = delete;
											OpenGL(OpenGL&& source) = delete;
				virtual						~OpenGL();

				OpenGL&						operator = (const OpenGL&) = delete;
				OpenGL&						operator = (OpenGL&&) = delete;

				virtual void				Create() override;
				virtual void				Delete() override;
				virtual bool				Use() override;
			};
#endif

			void							Init();
			void							Free();
		};

		template <typename T>
		struct WindowStructures
		{
#ifdef __TEXPROJECT_WIN__
		protected:

			static string					wndClassName;
			static WNDCLASSEX				wndClassEx;
			static DWORD					wndStyle;
			static DWORD					wndExStyle;
			static RECT						wndRect;
			static LRESULT CALLBACK			callbackDefault(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);


			HWND							wndHandle = 0;

		public:

			static void						Init();
			static void						Free();

											WindowStructures() = default;
											WindowStructures(const WindowStructures& source) = delete;
											WindowStructures(WindowStructures&& source) = delete;
			virtual							~WindowStructures() = default;

			Main&							operator = (const WindowStructures& source) = delete;
			Main&							operator = (WindowStructures&& source) = delete;
#else
#ifdef __TEXPROJECT_LIN__
			// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
			// MacOS variant
#endif
#endif
#endif
		};

		/*������� ���� ��� ��� ����*/
		struct Basic:
			public Helper::Structure::IndirectClassArray<Basic,true,true>
		{
			friend bool Window::Process();
		protected:

			static Basic*					current;

			Basic*							parent		= nullptr;
			std::list<Basic*>				child;
			bool							init		= false;
			bool							running		= false;
			bool							active		= false;
			ivec2							pos			= ivec2(0);
			uvec2							size		= uvec2(100);
			string							title		= "window";

		public:

			static inline Basic*			GetCurrent();


											Basic() = default;
											Basic(const Basic& source) = delete;
											Basic(Basic&& source) = delete;
											~Basic() = default;

			Basic&							operator = (const Basic& source) = delete;
			Basic&							operator = (Basic&& source) = delete;


			virtual void					Create(Basic* parent_ = nullptr) = 0;
			virtual void					Delete();
			virtual void					Loop() = 0;

			inline void						AddChild(Basic* child_);

			virtual void					SetSize(const uvec2 size_);
			virtual void					SetPos(const ivec2 pos_);

			virtual void*					GetHandle();

			inline bool						IsInit() const;
			inline bool						IsRunning() const;

			inline uvec2					GetSize() const;
		};
		/*���� ���������� ����*/
		struct Main:
			public Basic,
			public WindowStructures<Main>
		{
		protected:

#ifdef __TEXPROJECT_WIN__
			static LRESULT CALLBACK		callbackDefault(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
#endif

		public:

			static void						Init();
			static void						Free();

											Main() = default;
											Main(const Main& source) = delete;
											Main(Main&& source) = delete;
			virtual							~Main() = default;

			Main&							operator = (const Main& source) = delete;
			Main&							operator = (Main&& source) = delete;

			virtual void					Create(Basic* parent_ = nullptr) override;
			virtual void					Delete() override;
			virtual void					Loop() override;

			virtual void 					SetSize(const uvec2 size_) override;
			virtual void					SetPos(const ivec2 pos_) override;

			virtual void*					GetHandle();
		};
		/*³��� � ��������� ������*/
		struct Render:
			public Basic,
			public WindowStructures<Render>
		{
		public:

			struct FuncTypes
			{
				static const uint32			count = 3;
				enum Enum
				{
					Init					= 0,
					Free					= 1,
					Loop					= 2
				};
											FuncTypes() = delete;
			};
			typedef FuncTypes::Enum			FuncType;
			typedef void(*Func)(Render*);

			friend RenderContext::Basic;
#ifdef __TEXPROJECT_WIN__
			friend RenderContext::Default;
			friend Interface::Default;
#endif
#ifdef __TEXPROJECT_OPENGL__
			friend RenderContext::OpenGL;
#endif

			template <typename T>
			T*								AddPanel();

		protected:

#ifdef __TEXPROJECT_WIN__

			static PIXELFORMATDESCRIPTOR	wndPixelFormatDescriptor;
			static LRESULT CALLBACK			callbackDefault(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);

			HDC								wndDeviceContextHandle = NULL;
			clock_t							vSyncTimer,
											oVSyncTimer;

#endif

			RenderContext::Basic*			renderContext = nullptr;

		public:

			static void						Init();
			static void						Free();


			bool							vSync = false;
			Func							func[FuncTypes::count];


											Render();
											Render(const Render& source) = delete;
											Render(Render&& source) = delete;
			virtual							~Render() override;

			Render&							operator = (const Render& source) = delete;
			Render&							operator = (Render&& source) = delete;

			virtual void					Create(Basic* parent_ = nullptr) override;
			virtual void					Delete() override;
			virtual void					Loop() override;

			virtual void 					SetSize(const uvec2 size_) override;
			virtual void					SetPos(const ivec2 pos_) override;

			virtual void					SetRenderContext(const RenderContext::Type& type_);
			virtual void					SetFunc(const FuncType& type_, Func func_);
			virtual void					ResetFuncs();

			inline Interface::GUIPanelDefault*					AddPanelDefault();
			inline Interface::GUIButtonDefault*					AddButtonDefault();
			inline Interface::GUIButtonTrigger*					AddButtonTrigger();
			inline Interface::GUIButtonAction*					AddButtonAction();
			inline Interface::GUIButtonSlider*					AddButtonSlider();
			inline void											RemovePanel(Interface::GUIPanel* source);
			inline void											RemoveButton(Interface::GUIButton* source);
		};

		void								Init();
		void								Free();

		/*������� �������� �� ����, ��� � ����� ������ ������������ �������� Window::Process()*/
		inline Basic*						GetCurrent();
		inline uvec2						GetDesktopSize();

		/*������� ������� Windows*/
		bool								ErrorTest();
	}

	//Keyboard Input
	typedef Window::Input::Keyboard::KeyCodes					Keys;

	/*������� true, ���� ������ ���������*/
	inline bool								KeyState(const Window::Input::Keyboard::KeyCode& key);
	/*������� true, ���� "���������" ������ ���������*/
	inline bool								KeyPress(const Window::Input::Keyboard::KeyCode& key);
	/*������� "���������" ������. ����������� "���������" ������ ���������� ����� ���� ����������� ������� ������.*/
	inline void								PressKey(const Window::Input::Keyboard::KeyCode& key);

}


// TexProject
bool										TexProject::KeyState(const Window::Input::Keyboard::KeyCode& key)
{
	return Window::Input::Keyboard::keys[key].state;
}
bool										TexProject::KeyPress(const Window::Input::Keyboard::KeyCode& key)
{
	return Window::Input::Keyboard::keys[key].press;
}
void										TexProject::PressKey(const Window::Input::Keyboard::KeyCode& key)
{
	Window::Input::Keyboard::keys[key].press = true;
}


// Window
inline TexProject::uvec2					TexProject::Window::GetDesktopSize()
{
	return uvec2(
					GetSystemMetrics(SM_CXSCREEN),
					GetSystemMetrics(SM_CYSCREEN)
				);
}
inline TexProject::Window::Basic*			TexProject::Window::GetCurrent()
{
	return Basic::GetCurrent();
}


// Window::Input::Key
TexProject::Window::Input::Key::Key():
	press(false), state(false)
{
}
void										TexProject::Window::Input::Key::Loop()
{
	if(!state) press = false;
}
void										TexProject::Window::Input::Key::Flush()
{
	state = false;
	press = false;
}
void										TexProject::Window::Input::Key::Press()
{
	press = true;
}


// WindowStructures
#ifdef __TEXPROJECT_WIN__

template <typename T>
TexProject::string							TexProject::Window::WindowStructures<T>::wndClassName;
template <typename T>
WNDCLASSEX									TexProject::Window::WindowStructures<T>::wndClassEx;
template <typename T>
DWORD										TexProject::Window::WindowStructures<T>::wndStyle = 0;
template <typename T>
DWORD										TexProject::Window::WindowStructures<T>::wndExStyle = 0;
template <typename T>
RECT										TexProject::Window::WindowStructures<T>::wndRect;

#else
#ifdef __TEXPROJECT_LIN__
// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
// MacOS variant
#endif
#endif
#endif


// RenderContext
TexProject::Interface::GUIPanelDefault*							TexProject::Window::RenderContext::Basic::AddPanelDefault()
{
	return inter->AddPanelDefault();
}
TexProject::Interface::GUIButtonDefault*						TexProject::Window::RenderContext::Basic::AddButtonDefault()
{
	return inter->AddButtonDefault();
}
TexProject::Interface::GUIButtonTrigger*						TexProject::Window::RenderContext::Basic::AddButtonTrigger()
{
	return inter->AddButtonTrigger();
}
TexProject::Interface::GUIButtonAction*							TexProject::Window::RenderContext::Basic::AddButtonAction()
{
	return inter->AddButtonAction();
}
TexProject::Interface::GUIButtonSlider*							TexProject::Window::RenderContext::Basic::AddButtonSlider()
{
	return inter->AddButtonSlider();
}
void															TexProject::Window::RenderContext::Basic::RemovePanel(Interface::GUIPanel* source)
{
	inter->RemovePanel(source);
}
void															TexProject::Window::RenderContext::Basic::RemoveButton(Interface::GUIButton* source)
{
	inter->RemoveButton(source);
}


// Window::Basic
TexProject::Window::Basic*					TexProject::Window::Basic::GetCurrent()
{
	return current;
}

void										TexProject::Window::Basic::AddChild(Basic* child_)
{
	child.push_back(child_);
}

bool										TexProject::Window::Basic::IsInit() const
{
	return init;
}
bool										TexProject::Window::Basic::IsRunning() const
{
	return running;
}
TexProject::uvec2							TexProject::Window::Basic::GetSize() const
{
	return size;
}


// Window::Render
TexProject::Interface::GUIPanelDefault*		TexProject::Window::Render::AddPanelDefault()
{
	return renderContext->AddPanelDefault();
}
TexProject::Interface::GUIButtonDefault*	TexProject::Window::Render::AddButtonDefault()
{
	return renderContext->AddButtonDefault();
}
TexProject::Interface::GUIButtonTrigger*	TexProject::Window::Render::AddButtonTrigger()
{
	return renderContext->AddButtonTrigger();
}
TexProject::Interface::GUIButtonAction*		TexProject::Window::Render::AddButtonAction()
{
	return renderContext->AddButtonAction();
}
TexProject::Interface::GUIButtonSlider*		TexProject::Window::Render::AddButtonSlider()
{
	return renderContext->AddButtonSlider();
}
void										TexProject::Window::Render::RemovePanel(Interface::GUIPanel* source)
{
	renderContext->RemovePanel(source);
}
void										TexProject::Window::Render::RemoveButton(Interface::GUIButton* source)
{
	renderContext->RemoveButton(source);
}





















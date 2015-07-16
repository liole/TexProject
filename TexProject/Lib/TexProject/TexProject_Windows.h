#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_OpenGL.h>
#include <TexProject/TexProject_Direct3D.h>
#include <TexProject/TexProject_Helpers.h>
#include <TexProject/TexProject_Interface.h>


#include <time.h>
#include <list>


#if __TEXPROJECT_WIN__

#include <Windows.h>

#else
#if __TEXPROJECT_LIN__
// Linux variant
#else
#if __TEXPROJECT_MAC__
// MacOS variant
#endif
#endif
#endif


namespace TexProject
{

	namespace Window
	{
		/*Неймспейс, що відповідає за ввід*/
		namespace Input
		{
			/*Базова структура клавіші*/
			struct Key
			{
				bool						state = false;
				bool						press = false;

				inline						Key() = default;
				inline						~Key() = default;

				inline void					Loop();
				inline void					Flush();
				inline void					Press();
			};

			/*Неймспейс Миші*/
			namespace Mouse
			{
				extern Key						lB,mB,rB;
				extern ivec2					pos;

				bool							Init();
				void							Loop();
				void							Free();
				void							Flush();
			};

			/*Неймспейс клавіатури*/
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

		/*Контексти виводу*/
		namespace RenderContext
		{
			enum struct Type: uint32
			{
				Default,
				OpenGL,
				Direct3D
			};

			/*Базовий контекст виводу*/
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

				virtual Type				GetType() const { throw Exception(); }
				virtual void*				GetData() const { throw Exception(); }

				virtual void				Create();
				virtual void				Delete();
				virtual void				Loop();
				virtual bool				Use();
				virtual void				Unuse();

				inline Interface::Basic*	GetInterface()
				{
					return inter;
				}

				inline Interface::GUIPanel*						AddPanel(const Interface::PanelType& type_);
				inline Interface::GUIButton*					AddButton(const Interface::ButtonType& type_);
				inline void										RemoveItem(Interface::GUIItem* source);

				/*Методи, специфічні для ОС Windows*/
#if __TEXPROJECT_WIN__
				/*
				Цю функцію вікно буде викликати при обробці повідомлення WM_PAINT
				*/
				virtual void									_win_WMPaint(HDC hDC);
#endif
			};

#if __TEXPROJECT_WIN__
			/*Контекст Windows*/
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

				virtual Type				GetType() const override { return Type::Default; }
				virtual void*				GetData() const override;

				virtual void				Create() override;
				virtual void				Delete() override;
				virtual void				Loop() override;
				virtual bool				Use() override;

				virtual void									_win_WMPaint(HDC hDC) override;
			};
#endif

#ifdef __TEXPROJECT_OPENGL__
			/*Контекст OpenGL*/
			struct OpenGL:
				public Basic
			{
				friend TexProject::OpenGL::Buffer::Data;
				friend TexProject::OpenGL::Buffer::Index;
				friend TexProject::OpenGL::Buffer::Array;
				friend TexProject::OpenGL::Buffer::Frame;
				friend TexProject::OpenGL::Shader;
				friend TexProject::OpenGL::Texture;
			protected:

				static PFNWGLCREATECONTEXTATTRIBSARBPROC		wglCreateContextAttribsARB;


				TexProject::OpenGL::Buffer::Array*				bufferArrayCurrent = nullptr;
				TexProject::OpenGL::Buffer::Data*				bufferDataCurrent = nullptr;
				TexProject::OpenGL::Buffer::Index*				bufferIndexCurrent = nullptr;
				TexProject::OpenGL::Buffer::Frame*				bufferFrameCurrent = nullptr;

				TexProject::OpenGL::Shader*						shaderCurrent = nullptr;

				uint32											textureActiveSlot = 0;
				TexProject::OpenGL::Texture**					textureCurrent = nullptr;

				int32											textureMaxSlots = 0;
				int32											bufferFrameMaxColorAttachment = 0;

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

				virtual Type				GetType() const override { return Type::OpenGL; }
				virtual void*				GetData() const override;

				virtual void				Create() override;
				virtual void				Delete() override;
				virtual void				Loop() override;
				virtual bool				Use() override;

				inline TexProject::OpenGL::Buffer::Array*		GetCurrentBufferArray() const
				{
					return bufferArrayCurrent;
				}
				inline TexProject::OpenGL::Buffer::Index*		GetCurrentBufferIndex() const
				{
					return bufferIndexCurrent;
				}
				inline TexProject::OpenGL::Buffer::Data*		GetCurrentBufferDara() const
				{
					return bufferDataCurrent;
				}
				inline TexProject::OpenGL::Buffer::Frame*		GetCurrentBufferFrame() const
				{
					return bufferFrameCurrent;
				}
				inline TexProject::OpenGL::Shader*				GetCurrentShader() const
				{
					return shaderCurrent;
				}
				inline uint32									GetTextureActiveSlot() const
				{
					return textureActiveSlot;
				}
				TexProject::OpenGL::Texture*					GetCurrentTexture(uint32 level = 0) const;
				inline int32									GetTextureMaxSlots() const
				{
					return textureMaxSlots;
				}
				inline int32									GetBufferFrameMaxColorAttachment() const
				{
					return bufferFrameMaxColorAttachment;
				}
				void											UnuseBufferArray();
				void											UnuseBufferIndex();
				void											UnuseBufferData();
				void											UnuseBufferFrame();
				void											UnuseShader();

			};
#endif

#ifdef __TEXPROJECT_DIRECT3D__
			/*Контекст Direct3D*/
			struct Direct3D:
				public Basic
			{
			protected:

				LPDIRECT3D9					d3d = nullptr;
				LPDIRECT3DDEVICE9			d3ddev = nullptr;
				D3DPRESENT_PARAMETERS		d3dpp;

			public:

				static void					Init();
				static void					Free();

											Direct3D(Window::Render* window_);
											Direct3D(const Direct3D&) = delete;
											Direct3D(Direct3D&& source) = delete;
				virtual						~Direct3D();

				Direct3D&					operator = (const OpenGL&) = delete;
				Direct3D&					operator = (OpenGL&&) = delete;

				virtual Type				GetType() const override { return Type::Direct3D; }
				virtual void*				GetData() const override;

				virtual void				Create() override;
				virtual void				Delete() override;
				virtual void				Loop() override;
				virtual bool				Use() override;
				virtual void				Unuse() override;

				inline LPDIRECT3DDEVICE9	GetDevice() const
				{
					return d3ddev;
				}
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

		/*Базовий клас для усіх вікон*/
		struct Basic:
			public Helper::Structure::IndirectClassArray<Basic,true,true>
			//public Helper::Structure::ListClassArray<Basic,true,true>
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

			void*							userData = nullptr;

		public:

			static inline Basic*			GetCurrent();


											Basic() = default;
											Basic(const Basic& source) = delete;
											Basic(Basic&& source) = delete;
											~Basic() = default;

			Basic&							operator = (const Basic& source) = delete;
			Basic&							operator = (Basic&& source) = delete;


			inline float32					GetAspect() const
			{
				return float32(size.x)/float32(size.y);
			}

			inline void						SetUserData(void* data_)
			{
				userData = data_;
			}
			inline void*					GetUserData()
			{
				return userData;
			}

			virtual void					Create(const string& title_ = "") = 0;
			virtual void					Delete();
			virtual void					Loop() = 0;

			inline void						AddChild(Basic* child_);

			virtual void					SetSize(const uvec2 size_);
			virtual void					SetPos(const ivec2 pos_);

			virtual void*					GetHandle();

			inline bool						IsInit() const;
			inline bool						IsRunning() const;

			inline uvec2					GetSize() const;
			inline ivec2					GetPos() const;
		};
		/*Клас звичайного вікна*/
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

			virtual void					Create(const string& title_ = "") override;
			virtual void					Delete() override;
			virtual void					Loop() override;

			virtual void 					SetSize(const uvec2 size_) override;
			virtual void					SetPos(const ivec2 pos_) override;

			virtual void*					GetHandle() override;
		};
		/*Вікно з підтримкою виводу*/
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
#if __TEXPROJECT_WIN__
			friend RenderContext::Default;
			friend Interface::Default;
#endif
#if __TEXPROJECT_OPENGL__
			friend RenderContext::OpenGL;
#endif
#if __TEXPROJECT_DIRECT3D__
			friend RenderContext::Direct3D;
#endif

			virtual void*					GetHandle() override;
			inline vec2						ToWindowSpace(vec2 input)
			{
				return vec2(input.x, size.y - input.y);
			}

			template <typename T>
			T*								AddPanel();

		protected:

#if __TEXPROJECT_WIN__

			static PIXELFORMATDESCRIPTOR	wndPixelFormatDescriptor;
			static LRESULT CALLBACK			callbackDefault(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);

			HDC								wndDeviceContextHandle = NULL;
			clock_t							vSyncTimer,
											oVSyncTimer;

			// Double Buffering Stuff
			HDC								dbHDC = NULL;
			HBITMAP							dbBitmap = NULL;

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

			inline Interface::Basic*		GetInterface() { return renderContext->GetInterface(); }
			inline RenderContext::Basic*	GetRenderContext() { return renderContext; }

			virtual void					Create(const string& title_ = "") override;
			virtual void					Delete() override;
			virtual void					Loop() override;

			virtual void 					SetSize(const uvec2 size_) override;
			virtual void					SetPos(const ivec2 pos_) override;

			virtual void					SetRenderContext(const RenderContext::Type& type_);
			virtual void					SetFunc(const FuncType& type_, Func func_);
			virtual void					ResetFuncs();

			inline Interface::GUIPanel*		AddPanel(const Interface::PanelType& type_);
			inline Interface::GUIButton*	AddButton(const Interface::ButtonType& type_);
			inline void						RemoveItem(Interface::GUIItem* source);
		};

		void								Init();
		void								Free();

		/*Повертає вказівник на вікно, яке в даний момент обробляється функцією Window::Process()*/
		inline Basic*						GetCurrent();
		inline uvec2						GetDesktopSize();
		inline vec2							ToDesktopSpace(vec2 input)
		{
			return vec2(input.x,GetDesktopSize().y - input.y);
		}
		inline vec2							FromDesktopSpace(vec2 input)
		{
			return vec2(input.x,GetDesktopSize().y - input.y);
		}

		/*Обробка помилок Windows*/
		bool								ErrorTest();
	}


	// Mouse Input
	inline bool								MouseLState();
	inline bool								MouseMState();
	inline bool								MouseRState();
	inline bool								MouseLPress();
	inline bool								MouseMPress();
	inline bool								MouseRPress();
	inline void								MousePressL();
	inline void								MousePressM();
	inline void								MousePressR();
	inline ivec2							MousePos();


	//Keyboard Input
	typedef Window::Input::Keyboard::KeyCodes					Keys;

	/*Повертає true, якщо клавіша натиснута*/
	inline bool								KeyState(const Window::Input::Keyboard::KeyCode& key);
	/*Повертає true, якщо "віртуальна" клавіша натиснута*/
	inline bool								KeyPress(const Window::Input::Keyboard::KeyCode& key);
	/*Натискає "віртуальну" клавішу. Розтискання "віртуальної" клавіші відбудеться тільки після розтискання фізичної клавіші.*/
	inline void								PressKey(const Window::Input::Keyboard::KeyCode& key);

}


// TexProject
bool										TexProject::MouseLState()
{
	return Window::Input::Mouse::lB.state;
}
bool										TexProject::MouseMState()
{
	return Window::Input::Mouse::mB.state;
}
bool										TexProject::MouseRState()
{
	return Window::Input::Mouse::rB.state;
}
bool										TexProject::MouseLPress()
{
	return Window::Input::Mouse::lB.press;
}
bool										TexProject::MouseMPress()
{
	return Window::Input::Mouse::mB.press;
}
bool										TexProject::MouseRPress()
{
	return Window::Input::Mouse::rB.press;
}
void										TexProject::MousePressL()
{
	Window::Input::Mouse::lB.press = true;
}
void										TexProject::MousePressM()
{
	Window::Input::Mouse::mB.press = true;
}
void										TexProject::MousePressR()
{
	Window::Input::Mouse::rB.press = true;
}
TexProject::ivec2							TexProject::MousePos()
{
	return Window::Input::Mouse::pos;
}

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
TexProject::Interface::GUIPanel*								TexProject::Window::RenderContext::Basic::AddPanel(const Interface::PanelType& type_)
{
	return inter->AddPanel(type_);
}
TexProject::Interface::GUIButton*								TexProject::Window::RenderContext::Basic::AddButton(const Interface::ButtonType& type_)
{
	return inter->AddButton(type_);
}
void															TexProject::Window::RenderContext::Basic::RemoveItem(Interface::GUIItem* source)
{
	inter->RemoveItem(source);
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
TexProject::ivec2							TexProject::Window::Basic::GetPos() const
{
	return pos;
}


// Window::Render
TexProject::Interface::GUIPanel*			TexProject::Window::Render::AddPanel(const Interface::PanelType& type_)
{
	return renderContext->AddPanel(type_);
}
TexProject::Interface::GUIButton*			TexProject::Window::Render::AddButton(const Interface::ButtonType& type_)
{
	return renderContext->AddButton(type_);
}
void										TexProject::Window::Render::RemoveItem(Interface::GUIItem* source)
{
	renderContext->RemoveItem(source);
}




















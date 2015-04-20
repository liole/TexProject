/*
*/
#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Helpers.h>


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
		/*Неймспейс, що відповідає за ввід*/
		namespace Input
		{
			/*Базова структура клавіші*/
			struct Key
			{
				bool						state;
				bool						press;

				inline						Key();

				inline void					Loop();
				inline void					Flush();
				inline void					Press();
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

		/*Базовий клас для усіх вікон*/
		struct Basic:
			public Helper::Structure::IndirectClassArray<Basic,true,true>
		{
		protected:

			bool							init		= false;
			bool							running		= false;
			ivec2							pos			= ivec2(0);
			uvec2							size		= uvec2(100);
			string							title		= "window";

		public:

											Basic() = default;
											Basic(const Basic& source) = delete;
											Basic(Basic&& source) = delete;
											~Basic() = default;

			Basic&							operator = (const Basic& source) = delete;
			Basic&							operator = (Basic&& source) = delete;


			virtual void					Create() = 0;
			virtual void					Delete() = 0;
			virtual void					Loop() = 0;

			inline bool						IsInit() const;
			inline bool						IsRunning() const;
		};
		/*Клас звичайного вікна*/
		struct Main: public Basic
		{
#ifdef __TEXPROJECT_WIN__

		protected:

			static string					wndClassName;
			static WNDCLASSEX				wndClassEx;
			static LRESULT CALLBACK			callbackDefault(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);


			HWND							wndHandle = 0;
			DWORD							wndStyle = 0;
			DWORD							wndExStyle = 0;
			RECT							wndRect;

		public:

			static void						Init();
			static void						Free();

											Main() = default;
											Main(const Main& source) = delete;
											Main(Main&& source) = delete;
											~Main() = default;

			Main&							operator = (const Main& source) = delete;
			Main&							operator = (Main&& source) = delete;

			virtual void					Create();
			virtual void					Delete();
			virtual void					Loop();

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

		void			Init();
		void			Free();
	}

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
bool	TexProject::KeyState(const Window::Input::Keyboard::KeyCode& key)
{
	return Window::Input::Keyboard::keys[key].state;
}
bool	TexProject::KeyPress(const Window::Input::Keyboard::KeyCode& key)
{
	return Window::Input::Keyboard::keys[key].press;
}
void	TexProject::PressKey(const Window::Input::Keyboard::KeyCode& key)
{
	Window::Input::Keyboard::keys[key].press = true;
}


// Window::Input::Key
TexProject::Window::Input::Key::Key():
	press(false), state(false)
{
}
void					TexProject::Window::Input::Key::Loop()
{
	if(!state) press = false;
}
void					TexProject::Window::Input::Key::Flush()
{
	state = false;
	press = false;
}
void					TexProject::Window::Input::Key::Press()
{
	press = true;
}


// Window::Basic
inline bool									TexProject::Window::Basic::IsInit() const
{
	return init;
}
inline bool									TexProject::Window::Basic::IsRunning() const
{
	return running;
}




















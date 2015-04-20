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
		/*Базовий клас для усіх вікон*/
		struct Basic:
			public Helper::Structure::IndirectClassArray<Basic,true,true>
		{
		protected:

			bool						init		= false;
			bool						running		= false;
			ivec2						pos			= ivec2(0);
			uvec2						size		= uvec2(100);
			string						title		= "window";

		public:

										Basic() = default;
										Basic(const Basic& source) = delete;
										Basic(Basic&& source) = delete;
										~Basic() = default;

			Basic&						operator = (const Basic& source) = delete;
			Basic&						operator = (Basic&& source) = delete;


			virtual void				Create() = 0;
			virtual void				Delete() = 0;
			virtual void				Loop() = 0;

			inline bool					IsInit() const;
			inline bool					IsRunning() const;
		};
		/*Клас звичайного вікна*/
		struct Main: public Basic
		{
#ifdef __TEXPROJECT_WIN__

		protected:

			static string				wndClassName;
			static WNDCLASSEX			wndClassEx;
			static LRESULT CALLBACK		callbackDefault(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);

		public:

			static void					Init();
			static void					Free();


			HWND						wndHandle = 0;
			DWORD						wndStyle = 0;
			DWORD						wndExStyle = 0;
			RECT						wndRect;


										Main() = default;
										Main(const Main& source) = delete;
										Main(Main&& source) = delete;
										~Main() = default;

			Main&						operator = (const Main& source) = delete;
			Main&						operator = (Main&& source) = delete;

			virtual void				Create();
			virtual void				Delete();
			virtual void				Loop();

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




















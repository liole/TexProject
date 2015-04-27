#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Helpers.h>
#include <TexProject/TexProject_OpenGL.h>
#include <TexProject/TexProject_Shaders.h>
#include <TexProject/TexProject_Textures.h>


#include<list>


namespace TexProject
{
	namespace Interface
	{
		struct Basic
		{
		protected:
			Window::Basic*				window = nullptr;
			Basic*						parent;
			std::list<Basic*>			child;

		public:
										Basic(Window::Basic* window_);
			virtual						~Basic();

			virtual void				Create();
			virtual void				Delete();
			virtual void				Loop();
		};
	}
}





















#pragma once
#include <TexProject/TexProject_Header.h>


#ifdef __TEXPROJECT_DIRECT3D__


#include <TexProject/TexProject_Main.h>


#include <Direct3D/include/d3d9.h>
#include <Direct3D/include/d3dx9.h>

#pragma comment(lib, "Direct3D/lib/x86/d3d9.lib")
#pragma comment(lib, "Direct3D/lib/x86/d3dx9.lib")


namespace TexProject
{
	namespace Direct3D
	{
		void test();
	}
}


#endif


















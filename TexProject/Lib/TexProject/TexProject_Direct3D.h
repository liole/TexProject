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
		inline bool ErrorTest(HRESULT result)
		{
			switch(result)
			{
				case D3DERR_DEVICELOST: Message("D3DERR_DEVICELOST"); return true; break;
				case D3DERR_INVALIDCALL: Message("D3DERR_INVALIDCALL"); return true; break;
				case D3DERR_NOTAVAILABLE: Message("D3DERR_NOTAVAILABLE"); return true; break;
				case D3DERR_OUTOFVIDEOMEMORY: Message("D3DERR_OUTOFVIDEOMEMORY"); return true; break;
			}
			return false;
		}
	}
}


#endif


















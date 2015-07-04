#include <TexProject/TexProject_Header.h>


#include <HalfFloat/half.hpp>


#include <DevIL/include/il/il.h>
#include <DevIL/include/il/ilu.h>
#include <DevIL/include/il/ilut.h>
#pragma comment (lib, "DevIL/lib/DevIL.lib")
#pragma comment (lib, "DevIL/lib/ILU.lib")
#pragma comment (lib, "DevIL/lib/ILUT.lib")


#include <OpenGL/include/gl/GL.h>
#pragma comment(lib, "OpenGL/lib/OpenGL32.lib")


#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "x86/d3d9.lib")
#pragma comment(lib, "x86/d3dx9.lib")


#include <Windows.h>


INT WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,INT)
{

	auto pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(pD3D == NULL) MessageBox(NULL,"fail","fail",MB_OK);

	MessageBox(NULL,"ok","ok",MB_OK);

	return 0;
}
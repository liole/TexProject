#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>

#if __TEXPROJECT_DEVIL__

#include <DevIL/include/il/il.h>
#include <DevIL/include/il/ilu.h>
#include <DevIL/include/il/ilut.h>
#pragma comment (lib, "DevIL/lib/DevIL.lib")
#pragma comment (lib, "DevIL/lib/ILU.lib")
#pragma comment (lib, "DevIL/lib/ILUT.lib")

#endif



namespace TexProject
{
#if __TEXPROJECT_DEVIL__
	namespace DevIL
	{
		extern bool							isInit;

		bool								Init();
		bool								ErrorTest();
	}
#endif
}





















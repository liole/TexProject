#include "TexProject_Main.h"
using namespace TexProject;


#ifdef __TEXPROJECT_WIN__

int WINAPI			WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	Main();

	return 0;
}

#else
#ifdef __TEXPROJECT_LIN__
// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
// MacOS variant
#endif
#endif
#endif


void				TexProject::Message(const string& text)
{
#ifdef __TEXPROJECT_WIN__

	MessageBox(0, text.c_str(), "[TexProject] Message", MB_OK);

#else
#ifdef __TEXPROJECT_LIN__
	// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
	// MacOS variant
#endif
#endif
#endif
}
void				TexProject::Error(const string& text)
{
#ifdef __TEXPROJECT_WIN__

	MessageBox(0, text.c_str(), "[TexProject] Error", MB_OK);
	terminate();

#else
#ifdef __TEXPROJECT_LIN__
	// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
	// MacOS variant
#endif
#endif
#endif
}
bool				TexProject::Question(const string& text)
{
#ifdef __TEXPROJECT_WIN__

	return MessageBox(0,text.c_str(),"[TexProject] Question", MB_YESNO) == IDYES;

#else
#ifdef __TEXPROJECT_LIN__
	// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
	// MacOS variant
#endif
#endif
#endif
}
































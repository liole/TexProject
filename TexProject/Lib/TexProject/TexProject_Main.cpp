#include "TexProject_Main.h"
using namespace TexProject;


#if __TEXPROJECT_WIN__
#include <cstdlib>
#include <ctime>
#endif


#if __TEXPROJECT_WIN__


// EntryPointData
bool					TexProject::EntryPointData::init = false;
HINSTANCE				TexProject::EntryPointData::hInstance = 0;
HINSTANCE				TexProject::EntryPointData::hPrevInstance = 0;
LPSTR					TexProject::EntryPointData::lpCmdLine = "";
int						TexProject::EntryPointData::nShowCmd = 0;


int WINAPI				WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{

	{	// �������� ���� ����� �����
		EntryPointData::init = true;
		EntryPointData::hInstance = hInstance;
		EntryPointData::hPrevInstance = hPrevInstance;
		EntryPointData::lpCmdLine = lpCmdLine;
		EntryPointData::nShowCmd = nShowCmd;
	}

	srand(static_cast <unsigned> (time(0)));
	//try
	{
		Main();
	}
	/*catch(Exception exc)
	{
		Message(exc.Get());
	}*/

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


void					TexProject::Message(const string& text)
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
void					TexProject::Error(const string& text)
{
#ifdef __TEXPROJECT_WIN__

	throw Exception(text);

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
bool					TexProject::Question(const string& text)
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
































#pragma once
#include <TexProject/TexProject_Header.h>


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
	struct EntryPointData
	{
#ifdef __TEXPROJECT_WIN__
	public:

		static bool							init;
		static HINSTANCE					hInstance;
		static HINSTANCE					hPrevInstance;
		static LPSTR						lpCmdLine;
		static int							nShowCmd;

		EntryPointData() = delete;

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

	void				Main();

	void				Message(const string& text);
	void				Error(const string& text);
	bool				Question(const string& text);

	inline string		GetEXEPath()
	{
		HMODULE hModule = GetModuleHandleW(NULL);
		char path[MAX_PATH];
		GetModuleFileName(hModule,path,MAX_PATH);
		string::size_type pos = string(path).find_last_of("\\/");
		return string(path).substr(0,pos);
	}

	struct Exception
	{
	protected:
		string								text = "";
	public:
		inline								Exception() = default;
		inline								Exception(const string& text_);
		inline								Exception(const Exception& source) = default;
		inline								~Exception() = default;
		inline string						Get() const;
	};
}


// Exception
inline								TexProject::Exception::Exception(const string& text_):
	text(text_)
{
}
inline TexProject::string			TexProject::Exception::Get() const
{
	return text;
}


















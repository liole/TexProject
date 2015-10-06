#include "TexProject_OpenGL.h"
using namespace TexProject;


#if __TEXPROJECT_OPENGL__
#pragma region Func
// Texture func
bool										TexProject::OpenGL::initFuncTexture = false;
PFNGLACTIVETEXTUREPROC						TexProject::OpenGL::glActiveTexture = nullptr;
PFNGLGETTEXPARAMETERIIVPROC					TexProject::OpenGL::glGetTexParameterIiv = nullptr;
PFNGLGENERATEMIPMAPPROC						TexProject::OpenGL::glGenerateMipmap = nullptr;
PFNGLTEXIMAGE3DPROC							TexProject::OpenGL::glTexImage3D = nullptr;
// Shader func
bool										TexProject::OpenGL::initFuncShader = false;
PFNGLCREATEPROGRAMPROC						TexProject::OpenGL::glCreateProgram = nullptr;
PFNGLDELETEPROGRAMPROC						TexProject::OpenGL::glDeleteProgram = nullptr;
PFNGLLINKPROGRAMPROC						TexProject::OpenGL::glLinkProgram = nullptr;
PFNGLVALIDATEPROGRAMPROC					TexProject::OpenGL::glValidateProgram = nullptr;
PFNGLUSEPROGRAMPROC							TexProject::OpenGL::glUseProgram = nullptr;
PFNGLGETPROGRAMIVPROC						TexProject::OpenGL::glGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC					TexProject::OpenGL::glGetProgramInfoLog = nullptr;
PFNGLCREATESHADERPROC						TexProject::OpenGL::glCreateShader = nullptr;
PFNGLDELETESHADERPROC						TexProject::OpenGL::glDeleteShader = nullptr;
PFNGLSHADERSOURCEPROC						TexProject::OpenGL::glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC						TexProject::OpenGL::glCompileShader = nullptr;
PFNGLATTACHSHADERPROC						TexProject::OpenGL::glAttachShader = nullptr;
PFNGLDETACHSHADERPROC						TexProject::OpenGL::glDetachShader = nullptr;
PFNGLGETSHADERIVPROC						TexProject::OpenGL::glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC					TexProject::OpenGL::glGetShaderInfoLog = nullptr;
PFNGLGETUNIFORMLOCATIONPROC					TexProject::OpenGL::glGetUniformLocation = nullptr;
PFNGLUNIFORM1IPROC							TexProject::OpenGL::glUniform1i = nullptr;
PFNGLUNIFORM1FPROC							TexProject::OpenGL::glUniform1f = nullptr;
PFNGLUNIFORM2FPROC							TexProject::OpenGL::glUniform2f = nullptr;
PFNGLUNIFORM3FPROC							TexProject::OpenGL::glUniform3f = nullptr;
PFNGLUNIFORM4FPROC							TexProject::OpenGL::glUniform4f = nullptr;
PFNGLUNIFORMMATRIX3FVPROC					TexProject::OpenGL::glUniformMatrix3fv = nullptr;
PFNGLUNIFORMMATRIX4FVPROC					TexProject::OpenGL::glUniformMatrix4fv = nullptr;
PFNGLGETUNIFORMBLOCKINDEXPROC				TexProject::OpenGL::glGetUniformBlockIndex = nullptr;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC			TexProject::OpenGL::glGetActiveUniformBlockiv = nullptr;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC			TexProject::OpenGL::glGetActiveUniformBlockName = nullptr;
PFNGLUNIFORMBLOCKBINDINGPROC				TexProject::OpenGL::glUniformBlockBinding = nullptr;
PFNGLBINDATTRIBLOCATIONPROC					TexProject::OpenGL::glBindAttribLocation;
PFNGLGETACTIVEATTRIBPROC					TexProject::OpenGL::glGetActiveAttrib;
PFNGLGETACTIVEUNIFORMPROC					TexProject::OpenGL::glGetActiveUniform;
PFNGLGETATTRIBLOCATIONPROC					TexProject::OpenGL::glGetAttribLocation;
PFNGLVERTEXATTRIBPOINTERPROC				TexProject::OpenGL::glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC			TexProject::OpenGL::glEnableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC			TexProject::OpenGL::glDisableVertexAttribArray;
// Buffer Func
bool										TexProject::OpenGL::initFuncBuffer = false;
PFNGLGENVERTEXARRAYSPROC					TexProject::OpenGL::glGenVertexArrays = nullptr;
PFNGLDELETEVERTEXARRAYSPROC					TexProject::OpenGL::glDeleteVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC					TexProject::OpenGL::glBindVertexArray = nullptr;
PFNGLBINDBUFFERPROC							TexProject::OpenGL::glBindBuffer = nullptr;
PFNGLDELETEBUFFERSPROC						TexProject::OpenGL::glDeleteBuffers = nullptr;
PFNGLGENBUFFERSPROC							TexProject::OpenGL::glGenBuffers = nullptr;
PFNGLISBUFFERPROC							TexProject::OpenGL::glIsBuffer = nullptr;
PFNGLBUFFERDATAPROC							TexProject::OpenGL::glBufferData = nullptr;
PFNGLBUFFERSUBDATAPROC						TexProject::OpenGL::glBufferSubData = nullptr;
PFNGLGETBUFFERSUBDATAPROC					TexProject::OpenGL::glGetBufferSubData = nullptr;
PFNGLMAPBUFFERPROC							TexProject::OpenGL::glMapBuffer = nullptr;
PFNGLUNMAPBUFFERPROC						TexProject::OpenGL::glUnmapBuffer = nullptr;
PFNGLGETBUFFERPARAMETERIVPROC				TexProject::OpenGL::glGetBufferParameteriv = nullptr;
PFNGLGETBUFFERPOINTERVPROC					TexProject::OpenGL::glGetBufferPointerv = nullptr;
// Framebuffer func
bool										TexProject::OpenGL::initFuncFramebuffer = nullptr;
PFNGLBINDFRAMEBUFFERPROC					TexProject::OpenGL::glBindFramebuffer = nullptr;
PFNGLDELETEFRAMEBUFFERSPROC					TexProject::OpenGL::glDeleteFramebuffers = nullptr;
PFNGLGENFRAMEBUFFERSPROC					TexProject::OpenGL::glGenFramebuffers = nullptr;
PFNGLCHECKFRAMEBUFFERSTATUSPROC				TexProject::OpenGL::glCheckFramebufferStatus = nullptr;
PFNGLFRAMEBUFFERTEXTUREPROC					TexProject::OpenGL::glFramebufferTexture = nullptr;
PFNGLFRAMEBUFFERTEXTURE2DPROC				TexProject::OpenGL::glFramebufferTexture2D = nullptr;
PFNGLDRAWBUFFERSPROC						TexProject::OpenGL::glDrawBuffers = nullptr;
#pragma endregion
#pragma region Initer
TexProject::OpenGL::Initer										TexProject::OpenGL::initer;
PFNWGLCREATECONTEXTATTRIBSARBPROC								TexProject::OpenGL::wglCreateContextAttribsARB = NULL;
TexProject::OpenGL::Initer::Initer()
{
#if __TEXPROJECT_WIN__
	WNDCLASS tempWinClass;

	DWORD style =	WS_DISABLED;

	tempWinClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	tempWinClass.lpfnWndProc	= DefWindowProc;
	tempWinClass.cbClsExtra		= NULL;
	tempWinClass.cbWndExtra		= NULL;
	tempWinClass.hInstance		= EntryPointData::hInstance;
	tempWinClass.hIcon			= LoadIcon(NULL,IDI_APPLICATION);
	tempWinClass.hCursor		= LoadCursor(NULL,IDC_ARROW);
	tempWinClass.hbrBackground	= (HBRUSH)GetStockObject(GRAY_BRUSH);
	tempWinClass.lpszMenuName	= NULL;
	tempWinClass.lpszClassName	= "Temp Window Class";

	if(!RegisterClass(&tempWinClass)) throw Exception("Cannot register temp class.");

	HWND tempWin = CreateWindow
	(
		"Temp Window Class",
		"Temp Window",
		style,
		0,0,0,0,
		NULL,NULL,
		EntryPointData::hInstance,
		NULL
	);

	if(!tempWin) throw Exception("Cannot create window.");

	HDC tempDC = GetDC(tempWin);
	if(!tempDC) throw Exception("Cannot create Temp Device Context.");

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd,0,sizeof(pfd));
	pfd.nSize			= sizeof(pfd);
	pfd.nVersion		= 1;
	pfd.dwFlags			= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType		= PFD_TYPE_RGBA;
	pfd.cColorBits		= 32;
	pfd.cStencilBits	= 32;
	pfd.cDepthBits		= 32;

	int PixelFormat = ChoosePixelFormat(tempDC,&pfd);
	if(!PixelFormat) throw Exception("Can't Chose A Pixel Format.\nChoosePixelFormat");

	if(!SetPixelFormat(tempDC,PixelFormat,&pfd)) throw Exception("Can't Set A Pixel Format.\nSetPixelFormat");

	HGLRC tempRC = wglCreateContext(tempDC);
	if(!tempRC) throw Exception("Can't Create Temp GL Render Context.\nwglCreateContext");

	if(!wglMakeCurrent(tempDC,tempRC)) throw Exception("Can't Activate Temp GL Render Context.\nwglMakeCurrent");

	wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
#endif

	// GL_VERSION_2_0
	// Texture Func
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLACTIVETEXTUREPROC,glActiveTexture);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETTEXPARAMETERIIVPROC,glGetTexParameterIiv);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGENERATEMIPMAPPROC,glGenerateMipmap);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLTEXIMAGE3DPROC,glTexImage3D);
	initFuncTexture =
	(
		glActiveTexture != nullptr &&
		glGetTexParameterIiv != nullptr &&
		glGenerateMipmap != nullptr &&
		glTexImage3D != nullptr
	);
	// Shader Func
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLCREATEPROGRAMPROC,glCreateProgram);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLDELETEPROGRAMPROC,glDeleteProgram);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLLINKPROGRAMPROC,glLinkProgram);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLVALIDATEPROGRAMPROC,glValidateProgram);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLUSEPROGRAMPROC,glUseProgram);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETPROGRAMIVPROC,glGetProgramiv);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETPROGRAMINFOLOGPROC,glGetProgramInfoLog);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLCREATESHADERPROC,glCreateShader);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLDELETESHADERPROC,glDeleteShader);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLSHADERSOURCEPROC,glShaderSource);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLCOMPILESHADERPROC,glCompileShader);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLATTACHSHADERPROC,glAttachShader);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLDETACHSHADERPROC,glDetachShader);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETSHADERIVPROC,glGetShaderiv);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETSHADERINFOLOGPROC,glGetShaderInfoLog);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETUNIFORMLOCATIONPROC,glGetUniformLocation);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLUNIFORM1IPROC,glUniform1i);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLUNIFORM1FPROC,glUniform1f);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLUNIFORM2FPROC,glUniform2f);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLUNIFORM3FPROC,glUniform3f);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLUNIFORM4FPROC,glUniform4f);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLUNIFORMMATRIX3FVPROC,glUniformMatrix3fv);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLUNIFORMMATRIX4FVPROC,glUniformMatrix4fv);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETUNIFORMBLOCKINDEXPROC,glGetUniformBlockIndex);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETACTIVEUNIFORMBLOCKIVPROC,glGetActiveUniformBlockiv);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC,glGetActiveUniformBlockName);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLUNIFORMBLOCKBINDINGPROC,glUniformBlockBinding);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLBINDATTRIBLOCATIONPROC,glBindAttribLocation);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETACTIVEATTRIBPROC,glGetActiveAttrib);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETACTIVEUNIFORMPROC,glGetActiveUniform);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETATTRIBLOCATIONPROC,glGetAttribLocation);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLVERTEXATTRIBPOINTERPROC,glVertexAttribPointer);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLENABLEVERTEXATTRIBARRAYPROC,glEnableVertexAttribArray);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLDISABLEVERTEXATTRIBARRAYPROC,glDisableVertexAttribArray);
	initFuncShader =
	(
		glCreateProgram != nullptr &&
		glDeleteProgram != nullptr &&
		glLinkProgram != nullptr &&
		glValidateProgram != nullptr &&
		glUseProgram != nullptr &&
		glGetProgramiv != nullptr &&
		glGetProgramInfoLog != nullptr &&
		glCreateShader != nullptr &&
		glDeleteShader != nullptr &&
		glShaderSource != nullptr &&
		glCompileShader != nullptr &&
		glAttachShader != nullptr &&
		glDetachShader != nullptr &&
		glGetShaderiv != nullptr &&
		glGetShaderInfoLog != nullptr &&
		glGetUniformLocation != nullptr &&
		glUniform1i != nullptr &&
		glUniform1f != nullptr &&
		glUniform2f != nullptr &&
		glUniform3f != nullptr &&
		glUniform4f != nullptr &&
		glUniformMatrix3fv != nullptr &&
		glUniformMatrix4fv != nullptr &&
		glGetUniformBlockIndex != nullptr &&
		glGetActiveUniformBlockiv != nullptr &&
		glGetActiveUniformBlockName != nullptr &&
		glUniformBlockBinding != nullptr
	);

	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGENVERTEXARRAYSPROC,glGenVertexArrays);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLDELETEVERTEXARRAYSPROC,glDeleteVertexArrays);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLBINDVERTEXARRAYPROC,glBindVertexArray);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLBINDBUFFERPROC,glBindBuffer);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLDELETEBUFFERSPROC,glDeleteBuffers);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGENBUFFERSPROC,glGenBuffers);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLISBUFFERPROC,glIsBuffer);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLBUFFERDATAPROC,glBufferData);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLBUFFERSUBDATAPROC,glBufferSubData);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETBUFFERSUBDATAPROC,glGetBufferSubData);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLMAPBUFFERPROC,glMapBuffer);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLUNMAPBUFFERPROC,glUnmapBuffer);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETBUFFERPARAMETERIVPROC,glGetBufferParameteriv);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETBUFFERPOINTERVPROC,glGetBufferPointerv);
	initFuncBuffer =
	(
		glGenVertexArrays != nullptr &&
		glDeleteVertexArrays != nullptr &&
		glBindVertexArray != nullptr &&
		glBindBuffer != nullptr &&
		glDeleteBuffers != nullptr &&
		glGenBuffers != nullptr &&
		glIsBuffer != nullptr &&
		glBufferData != nullptr &&
		glBufferSubData != nullptr &&
		glGetBufferSubData != nullptr &&
		glMapBuffer != nullptr &&
		glUnmapBuffer != nullptr &&
		glGetBufferParameteriv != nullptr &&
		glGetBufferPointerv != nullptr
	);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLBINDFRAMEBUFFERPROC,glBindFramebuffer);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLDELETEFRAMEBUFFERSPROC,glDeleteFramebuffers);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGENFRAMEBUFFERSPROC,glGenFramebuffers);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLCHECKFRAMEBUFFERSTATUSPROC,glCheckFramebufferStatus);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLFRAMEBUFFERTEXTUREPROC,glFramebufferTexture);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLFRAMEBUFFERTEXTURE2DPROC,glFramebufferTexture2D);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLDRAWBUFFERSPROC,glDrawBuffers);
	initFuncFramebuffer =
	(
		glBindFramebuffer != nullptr &&
		glDeleteFramebuffers != nullptr &&
		glGenFramebuffers != nullptr &&
		glCheckFramebufferStatus != nullptr &&
		glFramebufferTexture != nullptr &&
		glFramebufferTexture2D != nullptr &&
		glDrawBuffers != nullptr
	);


	auto initFunc =	initFuncShader &&
					initFuncTexture &&
					initFuncBuffer &&
					initFuncFramebuffer;

	if(!initFunc) throw Exception();

#if __TEXPROJECT_WIN__
	if(!wglMakeCurrent(NULL,NULL)) throw Exception("Can't Release Render Context.\nwglMakeCurrent(NULL, NULL)");

	if(!wglDeleteContext(tempRC)) throw Exception("Can't Delete Temp GL Render Context.\nwglDeleteContext(Temp_hRC)");

	DestroyWindow(tempWin);
	UnregisterClass("Temp Window Class",EntryPointData::hInstance);
#endif
}
#pragma endregion
#pragma region RenderContext
TexProject::OpenGL::RenderContext::RenderContext(Window* window_):
	TexProject::RenderContext(window_)
{
	const int32 attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB,3,
		WGL_CONTEXT_MINOR_VERSION_ARB,3,
		WGL_CONTEXT_FLAGS_ARB,WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB,WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, //WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0,0
	};

	_wnd_RenderContextHandle = wglCreateContextAttribsARB(window->_win_windowDeviceContextHandle,0,attribs);

	if(!_wnd_RenderContextHandle) throw Exception("Can't create OpenGL render context.");

	Use();

	{
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,&textureMaxSlots);
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS,&bufferFrameMaxColorAttachment);
	}

	{
		currentTexture = new TexProject::OpenGL::Texture*[GetTextureMaxSlots()];
		for(int32 i = 0; i < GetTextureMaxSlots(); ++i) currentTexture[i] = nullptr;
	}

#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif

	Unuse();	
}
TexProject::OpenGL::RenderContext::~RenderContext()
{
}
TexProject::RenderContext::Type									TexProject::OpenGL::RenderContext::GetType() const
{
	return Type::OpenGL;
}
bool															TexProject::OpenGL::RenderContext::Use()
{
	if(!wglMakeCurrent(window->_win_windowDeviceContextHandle,_wnd_RenderContextHandle))
	{
		Message("Fail to use OpenGL render context.");
		return false;
	}

#ifdef __TEXPROJECT_DEBUG__
	//TexProject::OpenGL::ErrorTest();
#endif

	return true;
}
void															TexProject::OpenGL::RenderContext::Unuse()
{
	SetCurrentBufferAttribute(nullptr);
	SetCurrentBufferData(nullptr);
	SetCurrentBufferIndex(nullptr);
	SetCurrentBufferFrame(nullptr);
	SetCurrentShader(nullptr);
	for(int32 i = 0; i < GetTextureMaxSlots(); ++i) SetCurrentTexture(i,nullptr);
}
void															TexProject::OpenGL::RenderContext::Loop()
{
	SwapBuffers(window->_win_windowDeviceContextHandle);
}
#pragma endregion
#pragma region Texture
const TexProject::OpenGL::Texture::Filter	TexProject::OpenGL::Texture::Filter::Off(Minification::Off,Magnification::Off);
const TexProject::OpenGL::Texture::Filter	TexProject::OpenGL::Texture::Filter::Linear(Minification::Linear,Magnification::Linear);
const TexProject::OpenGL::Texture::Filter	TexProject::OpenGL::Texture::Filter::Mipmap(Minification::Mipmap,Magnification::Linear);
#pragma endregion
bool										TexProject::OpenGL::ErrorTest()
{
	GLenum error;
	bool result = false;
	while((error = glGetError()) != GL_NO_ERROR)
	{
		string code = "[OpenGL]\n";

		switch(error)
		{
			case GL_INVALID_OPERATION:
			{
				code += "INVALID_OPERATION";
				break;
			}
			case GL_INVALID_ENUM:
			{
				code += "INVALID_ENUM";
				break;
			}
			case GL_INVALID_VALUE:
			{
				code += "INVALID_VALUE";
				break;
			}
			case GL_OUT_OF_MEMORY:
			{
				code += "OUT_OF_MEMORY";
				break;
			}
			case GL_INVALID_FRAMEBUFFER_OPERATION:
			{
				code += "INVALID_FRAMEBUFFER_OPERATION";
				break;
			}
		}
		Message(code);

		result = true;
	}
	return result;
}
#endif


#pragma region Func
#pragma endregion



























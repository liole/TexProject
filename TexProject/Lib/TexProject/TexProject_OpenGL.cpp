#include "TexProject_OpenGL.h"
using namespace TexProject;


#ifdef __TEXPROJECT_OPENGL__


// Texture func
bool										TexProject::OpenGL::initFuncTexture = false;
PFNGLACTIVETEXTUREPROC						TexProject::OpenGL::glActiveTexture = nullptr;
PFNGLGETTEXPARAMETERIIVPROC					TexProject::OpenGL::glGetTexParameterIiv = nullptr;
PFNGLGENERATEMIPMAPPROC						TexProject::OpenGL::glGenerateMipmap = nullptr;
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


bool										TexProject::OpenGL::isInit = false;
bool										TexProject::OpenGL::initFunc = false;

bool										TexProject::OpenGL::Init()
{
	if(isInit) return true;

	// GL_VERSION_2_0
	// Texture Func
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLACTIVETEXTUREPROC,glActiveTexture);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGETTEXPARAMETERIIVPROC,glGetTexParameterIiv);
	_TEXPROJECT_OPENGL_GET_PROC(PFNGLGENERATEMIPMAPPROC,glGenerateMipmap);
	initFuncTexture =
		(
			glActiveTexture != nullptr &&
			glGetTexParameterIiv != nullptr &&
			glGenerateMipmap != nullptr
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

	initFunc = initFuncShader;

	//glGetString​(GL_VERSION​);
	isInit = true;

	return true;
}
bool										TexProject::OpenGL::ErrorTest()
{
	//if(BVE::exit) return false;
	GLenum error;
	bool result = false;
	while((error = glGetError()) != GL_NO_ERROR)
	{
		string code;

		switch(error)
		{
		case GL_INVALID_OPERATION:
			code = "INVALID_OPERATION";
			break;
		case GL_INVALID_ENUM:
			code = "INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			code = "INVALID_VALUE";
			break;
		case GL_OUT_OF_MEMORY:
			code = "OUT_OF_MEMORY";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			code = "INVALID_FRAMEBUFFER_OPERATION";
			break;
		}
		Message(code);

		result = true;
	}
	return result;
}


#endif






























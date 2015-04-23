#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>


#ifdef __TEXPROJECT_OPENGL__


#include <Windows.h>
#include <OpenGL/include/gl/GL.h>
#include <OpenGL/include/gl/glext.h>
#include <OpenGL/include/gl/wglext.h>

#pragma comment (lib, "Lib/OpenGL/lib/OpenGL32.lib")


#define _TEXPROJECT_OPENGL_GET_PROC(p,n) n = (p)wglGetProcAddress(#n); //return (n == nullptr) ? false : true;


namespace TexProject
{
	namespace OpenGL
	{
		/*
		// INIT OPENGL EXT
		// Data
		extern PFNGLPOINTPARAMETERFPROC							glPointParameterf;
		extern PFNGLPOINTPARAMETERFVPROC						glPointParameterfv;
		extern PFNGLPOINTPARAMETERIPROC							glPointParameteri;
		extern PFNGLPOINTPARAMETERIVPROC						glPointParameteriv;
		// Texture
		extern PFNGLTEXIMAGE3DPROC								glTexImage3D;
		extern PFNGLTEXSUBIMAGE3DPROC							glTexSubImage3D;
		extern PFNGLCOPYTEXSUBIMAGE3DPROC						glCopyTexSubImage3D;
		extern PFNGLACTIVETEXTUREPROC							glActiveTexture;
		extern PFNGLGETTEXPARAMETERIIVPROC						glGetTexParameterIiv;
		extern PFNGLGENERATEMIPMAPPROC							glGenerateMipmap;
		//extern glTexStorage2D	// ned gl 4.1
		extern PFNGLGENSAMPLERSPROC								glGenSamplers;
		extern PFNGLDELETESAMPLERSPROC							glDeleteSamplers;
		extern PFNGLISSAMPLERPROC								glIsSampler;
		extern PFNGLBINDSAMPLERPROC								glBindSampler;
		extern PFNGLSAMPLERPARAMETERIPROC						glSamplerParameteri;
		extern PFNGLSAMPLERPARAMETERIVPROC						glSamplerParameteriv;
		extern PFNGLSAMPLERPARAMETERFPROC						glSamplerParameterf;
		extern PFNGLSAMPLERPARAMETERFVPROC						glSamplerParameterfv;
		extern PFNGLSAMPLERPARAMETERIIVPROC						glSamplerParameterIiv;
		extern PFNGLSAMPLERPARAMETERIUIVPROC					glSamplerParameterIuiv;
		extern PFNGLGETSAMPLERPARAMETERIVPROC					glGetSamplerParameteriv;
		extern PFNGLGETSAMPLERPARAMETERIIVPROC					glGetSamplerParameterIiv;
		extern PFNGLGETSAMPLERPARAMETERFVPROC					glGetSamplerParameterfv;
		extern PFNGLGETSAMPLERPARAMETERIUIVPROC					glGetSamplerParameterIuiv;
		// VAO
		extern PFNGLGENVERTEXARRAYSPROC							glGenVertexArrays;
		extern PFNGLDELETEVERTEXARRAYSPROC						glDeleteVertexArrays;
		extern PFNGLBINDVERTEXARRAYPROC							glBindVertexArray;
		// Buffers
		extern PFNGLBINDBUFFERPROC								glBindBuffer;
		extern PFNGLDELETEBUFFERSPROC							glDeleteBuffers;
		extern PFNGLGENBUFFERSPROC								glGenBuffers;
		extern PFNGLISBUFFERPROC								glIsBuffer;
		extern PFNGLBUFFERDATAPROC								glBufferData;
		extern PFNGLBUFFERSUBDATAPROC							glBufferSubData;
		extern PFNGLGETBUFFERSUBDATAPROC						glGetBufferSubData;
		extern PFNGLMAPBUFFERPROC								glMapBuffer;
		extern PFNGLUNMAPBUFFERPROC								glUnmapBuffer;
		extern PFNGLGETBUFFERPARAMETERIVPROC					glGetBufferParameteriv;
		extern PFNGLGETBUFFERPOINTERVPROC						glGetBufferPointerv;
		// Blending
		extern PFNGLBLENDCOLORPROC								glBlendColor;
		extern PFNGLBLENDEQUATIONPROC							glBlendEquation;
		extern PFNGLBLENDFUNCSEPARATEPROC						glBlendFuncSeparate;
		extern PFNGLBLENDEQUATIONSEPARATEPROC					glBlendEquationSeparate;
		// Drawing
		extern PFNGLCLAMPCOLORPROC								glClampColor;
		extern PFNGLDRAWELEMENTSBASEVERTEXPROC					glDrawElementsBaseVertex;
		extern PFNGLDRAWRANGEELEMENTSPROC						glDrawRangeElements;
		extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC				glDrawRangeElementsBaseVertex;
		extern PFNGLDRAWARRAYSINDIRECTPROC						glDrawArraysIndirect;
		extern PFNGLDRAWELEMENTSINDIRECTPROC					glDrawElementsIndirect;
		extern PFNGLMULTIDRAWARRAYSPROC							glMultiDrawArrays;
		extern PFNGLMULTIDRAWELEMENTSPROC						glMultiDrawElements;
		//extern PFNGLMULTIDRAWARRAYSINDIRECTPROC				glMultiDrawArraysIndirect;
		//extern PFNGLMULTIDRAWELEMENTSINDIRECTPROC				glMultiDrawElementsIndirect;
		extern PFNGLDRAWARRAYSINSTANCEDPROC						glDrawArraysInstanced;
		extern PFNGLDRAWELEMENTSINSTANCEDPROC					glDrawElementsInstanced;
		extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC			glDrawElementsInstancedBaseVertex;
		extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC				glMultiDrawElementsBaseVertex;
		extern PFNGLTEXBUFFERPROC								glTexBuffer;
		extern PFNGLPRIMITIVERESTARTINDEXPROC					glPrimitiveRestartIndex;
		// Shaders
		extern PFNGLCREATEPROGRAMPROC							glCreateProgram;
		extern PFNGLDELETEPROGRAMPROC							glDeleteProgram;
		extern PFNGLLINKPROGRAMPROC								glLinkProgram;
		extern PFNGLVALIDATEPROGRAMPROC							glValidateProgram;
		extern PFNGLUSEPROGRAMPROC								glUseProgram;
		extern PFNGLGETPROGRAMIVPROC							glGetProgramiv;
		extern PFNGLGETPROGRAMINFOLOGPROC						glGetProgramInfoLog;
		extern PFNGLCREATESHADERPROC							glCreateShader;
		extern PFNGLDELETESHADERPROC							glDeleteShader;
		extern PFNGLSHADERSOURCEPROC							glShaderSource;
		extern PFNGLCOMPILESHADERPROC							glCompileShader;
		extern PFNGLATTACHSHADERPROC							glAttachShader;
		extern PFNGLDETACHSHADERPROC							glDetachShader;
		extern PFNGLGETSHADERIVPROC								glGetShaderiv;
		extern PFNGLGETSHADERINFOLOGPROC						glGetShaderInfoLog;
		extern PFNGLPATCHPARAMETERIPROC							glPatchParameteri;
		// Shaders attributes
		extern PFNGLBINDATTRIBLOCATIONPROC						glBindAttribLocation;
		extern PFNGLGETACTIVEATTRIBPROC							glGetActiveAttrib;
		extern PFNGLGETACTIVEUNIFORMPROC						glGetActiveUniform;
		extern PFNGLGETATTRIBLOCATIONPROC						glGetAttribLocation;
		extern PFNGLVERTEXATTRIBPOINTERPROC						glVertexAttribPointer;
		extern PFNGLENABLEVERTEXATTRIBARRAYPROC					glEnableVertexAttribArray;
		extern PFNGLDISABLEVERTEXATTRIBARRAYPROC				glDisableVertexAttribArray;
		// Shaders uniforms
		extern PFNGLGETUNIFORMLOCATIONPROC						glGetUniformLocation;
		extern PFNGLUNIFORM1IPROC								glUniform1i;
		extern PFNGLUNIFORM1FPROC								glUniform1f;
		extern PFNGLUNIFORM2FPROC								glUniform2f;
		extern PFNGLUNIFORM3FPROC								glUniform3f;
		extern PFNGLUNIFORM4FPROC								glUniform4f;
		extern PFNGLUNIFORMMATRIX3FVPROC						glUniformMatrix3fv;
		extern PFNGLUNIFORMMATRIX4FVPROC						glUniformMatrix4fv;
		extern PFNGLGETUNIFORMBLOCKINDEXPROC					glGetUniformBlockIndex;
		extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC					glGetActiveUniformBlockiv;
		extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC				glGetActiveUniformBlockName;
		extern PFNGLUNIFORMBLOCKBINDINGPROC						glUniformBlockBinding;
		// Query
		extern PFNGLGENQUERIESPROC								glGenQueries;
		extern PFNGLDELETEQUERIESPROC							glDeleteQueries;
		extern PFNGLISQUERYPROC									glIsQuery;
		extern PFNGLBEGINQUERYPROC								glBeginQuery;
		extern PFNGLENDQUERYPROC								glEndQuery;
		extern PFNGLGETQUERYIVPROC								glGetQueryiv;
		extern PFNGLGETQUERYOBJECTIVPROC						glGetQueryObjectiv;
		extern PFNGLGETQUERYOBJECTUIVPROC						glGetQueryObjectuiv;
		// Transform Feedback
		extern PFNGLBEGINTRANSFORMFEEDBACKPROC					glBeginTransformFeedback;
		extern PFNGLENDTRANSFORMFEEDBACKPROC					glEndTransformFeedback;
		extern PFNGLBINDBUFFERRANGEPROC							glBindBufferRange;
		extern PFNGLBINDBUFFERBASEPROC							glBindBufferBase;
		extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC				glTransformFeedbackVaryings;
		// FBO
		extern PFNGLBINDFRAMEBUFFERPROC							glBindFramebuffer;
		extern PFNGLDELETEFRAMEBUFFERSPROC						glDeleteFramebuffers;
		extern PFNGLGENFRAMEBUFFERSPROC							glGenFramebuffers;
		extern PFNGLCHECKFRAMEBUFFERSTATUSPROC					glCheckFramebufferStatus;
		extern PFNGLFRAMEBUFFERTEXTUREPROC						glFramebufferTexture;
		extern PFNGLFRAMEBUFFERTEXTURE2DPROC					glFramebufferTexture2D;
		extern PFNGLDRAWBUFFERSPROC								glDrawBuffers;
		*/
		
		/*OpenGL func declaration*/
		// TextureFunc
		extern bool												initFuncTexture;
		extern PFNGLACTIVETEXTUREPROC							glActiveTexture;
		extern PFNGLGETTEXPARAMETERIIVPROC						glGetTexParameterIiv;
		extern PFNGLGENERATEMIPMAPPROC							glGenerateMipmap;
		// Shader func
		extern bool												initFuncShader;
		extern PFNGLCREATEPROGRAMPROC							glCreateProgram;
		extern PFNGLDELETEPROGRAMPROC							glDeleteProgram;
		extern PFNGLLINKPROGRAMPROC								glLinkProgram;
		extern PFNGLVALIDATEPROGRAMPROC							glValidateProgram;
		extern PFNGLUSEPROGRAMPROC								glUseProgram;
		extern PFNGLGETPROGRAMIVPROC							glGetProgramiv;
		extern PFNGLGETPROGRAMINFOLOGPROC						glGetProgramInfoLog;
		extern PFNGLCREATESHADERPROC							glCreateShader;
		extern PFNGLDELETESHADERPROC							glDeleteShader;
		extern PFNGLSHADERSOURCEPROC							glShaderSource;
		extern PFNGLCOMPILESHADERPROC							glCompileShader;
		extern PFNGLATTACHSHADERPROC							glAttachShader;
		extern PFNGLDETACHSHADERPROC							glDetachShader;
		extern PFNGLGETSHADERIVPROC								glGetShaderiv;
		extern PFNGLGETSHADERINFOLOGPROC						glGetShaderInfoLog;
		extern PFNGLGETUNIFORMLOCATIONPROC						glGetUniformLocation;
		extern PFNGLUNIFORM1IPROC								glUniform1i;
		extern PFNGLUNIFORM1FPROC								glUniform1f;
		extern PFNGLUNIFORM2FPROC								glUniform2f;
		extern PFNGLUNIFORM3FPROC								glUniform3f;
		extern PFNGLUNIFORM4FPROC								glUniform4f;
		extern PFNGLUNIFORMMATRIX3FVPROC						glUniformMatrix3fv;
		extern PFNGLUNIFORMMATRIX4FVPROC						glUniformMatrix4fv;
		extern PFNGLGETUNIFORMBLOCKINDEXPROC					glGetUniformBlockIndex;
		extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC					glGetActiveUniformBlockiv;
		extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC				glGetActiveUniformBlockName;
		extern PFNGLUNIFORMBLOCKBINDINGPROC						glUniformBlockBinding;


		extern bool							isInit;
		extern bool							initFunc;

		bool								Init();
		bool								ErrorTest();
	}
}


#endif



















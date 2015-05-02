#include "TexProject_DevIL.h"
using namespace TexProject;


#if __TEXPROJECT_DEVIL__

bool					TexProject::DevIL::isInit = false;

bool					TexProject::DevIL::Init()
{
	if(!isInit)
	{
		if(ilGetInteger(IL_VERSION_NUM) < IL_VERSION) return false;
		if(iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION) return false;
		if(ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION) return false;

		ilInit();
		iluInit();
		ilutInit();

		ilEnable(IL_FILE_OVERWRITE);
		ilSetInteger(IL_KEEP_DXTC_DATA,IL_TRUE);
		ilutRenderer(ILUT_OPENGL);
		ilutEnable(ILUT_GL_AUTODETECT_TEXTURE_TARGET);
		ilutEnable(ILUT_OPENGL_CONV);
		ilutEnable(ILUT_GL_USE_S3TC);

		DevIL::ErrorTest();

		isInit = true;
	}

	return true;
}
bool					TexProject::DevIL::ErrorTest()
{
	ILenum error;
	bool result = false;

	while((error = ilGetError()) != IL_NO_ERROR)
	{
		string code;

		switch(error)
		{
		case IL_INVALID_ENUM:// || ILU_INVALID_ENUM || ILUT_INVALID_ENUM:
			code = "IL_INVALID_ENUM";
			break;
		case IL_OUT_OF_MEMORY://, ILU_OUT_OF_MEMORY, ILUT_OUT_OF_MEMORY:
			code = "IL_OUT_OF_MEMORY";
			break;
		case IL_FORMAT_NOT_SUPPORTED:
			code = "IL_FORMAT_NOT_SUPPORTED";
			break;
		case IL_INVALID_VALUE://, ILU_INVALID_VALUE, ILUT_INVALID_VALUE:
			code = "IL_INVALID_VALUE";
			break;
		case IL_ILLEGAL_OPERATION://, ILU_ILLEGAL_OPERATION, ILUT_ILLEGAL_OPERATION:
			code = "IL_ILLEGAL_OPERATION";
			break;
		case IL_ILLEGAL_FILE_VALUE:
			code = "IL_ILLEGAL_FILE_VALUE";
			break;
		case IL_INVALID_FILE_HEADER:
			code = "IL_INVALID_FILE_HEADER";
			break;
		case IL_INVALID_PARAM://, ILU_INVALID_PARAM, ILUT_INVALID_PARAM:
			code = "IL_INVALID_PARAM";
			break;
		case IL_COULD_NOT_OPEN_FILE: //, ILUT_COULD_NOT_OPEN_FILE:
			code = "IL_COULD_NOT_OPEN_FILE";
			break;
		case IL_INVALID_EXTENSION:
			code = "IL_INVALID_EXTENSION";
			break;
		case IL_FILE_ALREADY_EXISTS:
			code = "IL_FILE_ALREADY_EXISTS";
			break;
		case IL_OUT_FORMAT_SAME:
			code = "IL_OUT_FORMAT_SAME";
			break;
		case IL_STACK_OVERFLOW://, ILUT_STACK_OVERFLOW:
			code = "IL_STACK_OVERFLOW";
			break;
		case IL_STACK_UNDERFLOW://, ILUT_STACK_UNDERFLOW:
			code = "IL_STACK_UNDERFLOW";
			break;
		case IL_INVALID_CONVERSION:
			code = "IL_INVALID_CONVERSION";
			break;
		case IL_LIB_JPEG_ERROR:
			code = "IL_LIB_JPEG_ERROR";
			break;
		case IL_LIB_PNG_ERROR:
			code = "IL_LIB_PNG_ERROR";
			break;
		case IL_UNKNOWN_ERROR:
			code = "IL_UNKNOWN_ERROR";
			break;
		case ILUT_NOT_SUPPORTED:
			code = "ILUT_NOT_SUPPORTED";
			break;
		}
		Message(code);

		result = true;
	}
	return result;
}

#endif
































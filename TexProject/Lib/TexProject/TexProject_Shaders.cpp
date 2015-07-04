#include "TexProject_Shaders.h"
using namespace TexProject;


#ifdef __TEXPROJECT_OPENGL__


bool					TexProject::OpenGL::Shader::LinkProgram(GLuint PRG)
{
	//if(!OpenGL::initFuncShader) throw Exception("OpenGL not supported.");

#ifdef __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif

	glLinkProgram(PRG);

#ifdef __TEXPROJECT_DEBUG__
	{
		OpenGL::ErrorTest();

		GLint result;
		glGetProgramiv(PRG,GL_LINK_STATUS,&result);
		if(result != GL_TRUE)
		{
			if(Question("Error In Shader Program.\nShow Error Code?"))
			{
				GLint errorCodeLength;
				glGetProgramiv(PRG,GL_INFO_LOG_LENGTH,&errorCodeLength);
				char *buffer = (char*)malloc(errorCodeLength+1);
				int len = errorCodeLength;
				glGetProgramInfoLog(PRG,errorCodeLength,&len,buffer);
				buffer[errorCodeLength] = '\0';
				string code = string(buffer);
				while(code.length() > 0)
				{
					if(code.length() < 500)
					{
						Message("[glLinkProgram] Error:\n" + code);
						code = "";
					}
					else
					{
						uint32 pos = code.find('\n',500);
						Message("[glLinkProgram] Error:\n" + code.substr(0,pos));
						code = code.substr(pos,code.length());
					}
				}
				free(buffer);
			}
			return false;
		}

		OpenGL::ErrorTest();
	}
#endif

	return true;
}
bool					TexProject::OpenGL::Shader::CompileShader(GLuint SHD)
{
#ifdef __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif

	glCompileShader(SHD);

#ifdef __TEXPROJECT_DEBUG__
	{
		OpenGL::ErrorTest();

		GLint result;
		glGetShaderiv(SHD,GL_COMPILE_STATUS,&result);
		if(result != GL_TRUE)
		{
			if(Question("Error In Shader Component.\nShow Error Code?"))
			{
				GLint errorCodeLength;
				glGetShaderiv(SHD,GL_INFO_LOG_LENGTH,&errorCodeLength);
				char *buffer = (char*)malloc(errorCodeLength+1);
				int len;
				glGetShaderInfoLog(SHD,errorCodeLength,&len,buffer);
				buffer[errorCodeLength] = '\0';
				Message("[glCompileShader] Error:\n"+string(buffer));
				free(buffer);
			}
			return false;
		}

		OpenGL::ErrorTest();
	}
#endif	

	return true;
}
bool					TexProject::OpenGL::Shader::LoadFile(const string& fileName,bool binary,uint8 **buffer,uint32 *size)
{
	FILE		*input;
	uint32		fileSize,readed;

	const char mode[] ={'r',binary ? 'b' : 't','\0'};

	//if( (input = fopen(fileName.c_str(),mode)) == NULL )
	if(fopen_s(&input,fileName.c_str(),mode))
	{
		return false;
	}

	fseek(input,0,SEEK_END);
	fileSize = (uint32)ftell(input);
	rewind(input);

	if(fileSize == 0)
	{
		fclose(input);
		return false;
	}

	*buffer = new uint8[fileSize];

	readed = fread(*buffer,1,fileSize,input);

	fclose(input);

	if(readed != fileSize)
	{
		delete[] *buffer;
		return false;
	}

	*size = fileSize;

	return true;
}


bool					TexProject::OpenGL::Shader::Load(const string& vsPath,const string& tcPath,const string& tePath,const string& gsPath,const string& psPath)
{
	Delete();

#ifdef __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif

	Create();

	uint8		*shaderSource;
	uint32		sourceLength;

	//Load Vertex Shader
	if(vsPath.length() > 0)
	{
		if(!LoadFile(vsPath,true,&shaderSource,&sourceLength)) { Message("Can't Load Vertex Shader.\npath: ''"+vsPath+"''"); return false; }
		glShaderSource(vs,1,(const GLchar**)&shaderSource,(const GLint*)&sourceLength);
		if(!CompileShader(vs)) return false;
		delete[] shaderSource;
	}

	//Load Tesselation Control Shader
	if(tcPath.length() > 0)
	{
		if(!LoadFile(tcPath,true,&shaderSource,&sourceLength)) { Message("Can't Load Tesselation Control Shader.\npath: ''"+tcPath+"''"); return false; }
		glShaderSource(tc,1,(const GLchar**)&shaderSource,(const GLint*)&sourceLength);
		if(!CompileShader(tc)) return false;
		delete[] shaderSource;
	}

	//Load Tesselation Evaluated Shader
	if(tePath.length() > 0)
	{
		if(!LoadFile(tePath,true,&shaderSource,&sourceLength)) { Message("Can't Load Tesselation Evaluated Shader.\npath: ''"+tePath+"''"); return false; }
		glShaderSource(te,1,(const GLchar**)&shaderSource,(const GLint*)&sourceLength);
		if(!CompileShader(te)) return false;
		delete[] shaderSource;
	}

	//Load Geometry Shader
	if(gsPath.length() > 0)
	{
		if(!LoadFile(gsPath,true,&shaderSource,&sourceLength)) { Message("Can't Load Geometry Shader.\npath: ''"+gsPath+"''"); return false; }
		glShaderSource(gs,1,(const GLchar**)&shaderSource,(const GLint*)&sourceLength);
		if(!CompileShader(gs)) return false;
		delete[] shaderSource;
	}

	//Load Pixel Shader
	if(psPath.length() > 0)
	{
		if(!LoadFile(psPath,true,&shaderSource,&sourceLength)) { Message("Can't Load Pixel Shader.\npath: ''"+psPath+"''"); return false; }
		glShaderSource(ps,1,(const GLchar**)&shaderSource,(const GLint*)&sourceLength);
		if(!CompileShader(ps)) return false;
		delete[] shaderSource;
	}

	if(vsPath.length() > 0) glAttachShader(prog,vs);
	if(tcPath.length() > 0) glAttachShader(prog,tc);
	if(tePath.length() > 0) glAttachShader(prog,te);
	if(gsPath.length() > 0) glAttachShader(prog,gs);
	if(psPath.length() > 0) glAttachShader(prog,ps);

#ifdef __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif

	return LinkProgram(prog);
}


#endif






























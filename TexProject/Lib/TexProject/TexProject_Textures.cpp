#include "TexProject_Textures.h"
using namespace TexProject;
using namespace TexProject::OpenGL;


void					TexProject::Texture::Init()
{
#ifdef __TEXPROJECT_OPENGL__
	if(OpenGL::initFuncShader)
	{
		for(uint32 i = 0; i < glMaxTextureSlots; ++i) glCurrent[i] = nullptr;
	}
#endif
}
void					TexProject::Texture::InitDraw()
{
	string path = "Media/Shaders/1";
	if(!glDrawShader.Load(path+".vs","","",path+".gs",path+".ps"))
	{
		Message("Can't load shader.");
	}
	glDrawShader.SetInt("Texture",0);
}
void					TexProject::Texture::FreeDraw()
{
	glDrawShader.Delete();
}


TexProject::Texture::~Texture()
{
	Delete();
}

void					TexProject::Texture::Delete()
{
	if(init)
	{

#ifdef __TEXPROJECT_OPENGL__
	if(OpenGL::initFuncShader)
	{
		if(glTexture)
		{
			for(uint32 i = 0; i < glMaxTextureSlots; ++i) if(glCurrent[i] == this) glUseNull(i,glType);

			glDeleteTextures(1,&glTexture);
			glTexture = 0;
		}
	}
#endif

		Resize(uvec3(0));

		init = false;
	}
}

vec4&					TexProject::Texture::Get(uint32 x,uint32 y)
{
	if( x < size.x && y < size.y && size.z > 0 )
	{
		return data[x][y][0];
	}
	else
	{
		throw Exception("Out of texture data array.");
	}
}
void					TexProject::Texture::Resize(uvec3 size_)
{
	if( size.x > 0 || size.y > 0 || size.z > 0 )
	{
		for(uint32 x = 0; x < size.x; ++x)
		{
			for(uint32 y = 0; y < size.y; ++y)
			{
				delete[] data[x][y];
			}
			delete[] data[x];
		}
		delete[] data;
		data = nullptr;
	}
	
	size = size_;

	if(size.x > 0 || size.y > 0 || size.z > 0)
	{
		data = new vec4**[size.x];
		for(uint32 x = 0; x < size.x; ++x)
		{
			data[x] = new vec4*[size.y];
			for(uint32 y = 0; y < size.y; ++y)
			{
				data[x][y] = new vec4[size.z];
				for(uint32 z = 0; z < size.z; ++z)
				{
					data[x][y][z].x = 0.0f;
					data[x][y][z].y = 0.0f;
					data[x][y][z].z = 0.0f;
					data[x][y][z].w = 1.0f;
				}
			}
		}
	}
}
void					TexProject::Texture::Build()
{
	auto t = new float32[size.x*size.y*size.z*4];

	for(uint32 x = 0; x < size.x; ++x)
	for(uint32 y = 0; y < size.y; ++y)
	for(uint32 z = 0; z < size.z; ++z)
	{
		auto id = 4*(size.x*(z*size.y + y) + x);
		t[id+0] = data[x][y][z].x;
		t[id+1] = data[x][y][z].y;
		t[id+2] = data[x][y][z].z;
		t[id+3] = data[x][y][z].w;
	}

	{
#ifdef __TEXPROJECT_OPENGL__
		if( init && OpenGL::initFuncShader)
		{
			if(glTexture)
			{
				for(uint32 i = 0; i < glMaxTextureSlots; ++i) if(glCurrent[i] == this) glUseNull(i,glType);

				glDeleteTextures(1,&glTexture);
				glTexture = 0;
			}
		}

		{
			glIFormat = GLIFormats::RGBA32F;
			glFormat = GLFormats::RGBA;
			glComponent = GLComponents::Float;
			glFilter = GLFilters::Linear;
			glWrap = GLWraps::Repeat;
			glType = GLTypes::tex2D;
		}

		{
			glGenTextures(1,&glTexture);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(glType,glTexture);
		}

		switch(glFilter)
		{
			case GLFilters::Off:
			{
				glTexParameteri(glType,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
				glTexParameteri(glType,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				break;
			}
			case GLFilters::Linear:
			{
				glTexParameteri(glType,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexParameteri(glType,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				break;
			}
			case GLFilters::Mipmap:
			{
				glTexParameteri(glType,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(glType,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				break;
			}
		}

		switch(glWrap)
		{
			case GLWraps::Clamp:
			{
				glTexParameteri(glType,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
				glTexParameteri(glType,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
				glTexParameteri(glType,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
				break;
			}
			case GLWraps::Border:
			{
				glTexParameteri(glType,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
				glTexParameteri(glType,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
				glTexParameteri(glType,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_BORDER);
				break;
			}
			case GLWraps::Repeat:
			{
				glTexParameteri(glType,GL_TEXTURE_WRAP_S,GL_REPEAT);
				glTexParameteri(glType,GL_TEXTURE_WRAP_T,GL_REPEAT);
				glTexParameteri(glType,GL_TEXTURE_WRAP_R,GL_REPEAT);
				break;
			}
			case GLWraps::Mirror:
			{
				glTexParameteri(glType,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
				glTexParameteri(glType,GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
				glTexParameteri(glType,GL_TEXTURE_WRAP_R,GL_MIRRORED_REPEAT);
				break;
			}
		}

		{
			static GLfloat color[4];
			color[0] = 0.0f;	//borderColor.x;
			color[1] = 0.0f;	//borderColor.y;
			color[2] = 0.0f;	//borderColor.z;
			color[3] = 0.0f;	//borderColor.w;
			glTexParameterfv(glType,GL_TEXTURE_BORDER_COLOR,color);
		}

		glTexImage2D(GL_TEXTURE_2D,0,glIFormat,size.x,size.y,0,glFormat,glComponent,t);

		if(glFilter == GLFilters::Mipmap)
		{
			//glGenerateMipmap(type);
		}

		glBindTexture(glType,0);

		OpenGL::ErrorTest();
#endif

		init = true;
	}

	delete t;
}
void					TexProject::Texture::Draw()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); glBlendFunc(GL_ONE,GL_ONE);

	glViewport(0,0,Window::GetCurrent()->GetSize().x,Window::GetCurrent()->GetSize().y);

	glDrawShader.Use();
	glUse(0);

	glDrawArrays(GL_POINTS,0,1);

	OpenGL::Shader::UseNull();
}


#ifdef __TEXPROJECT_OPENGL__

Texture*				TexProject::Texture::glCurrent[glMaxTextureSlots];
OpenGL::Shader			TexProject::Texture::glDrawShader;


void					TexProject::Texture::glUseNull(uint32 slot_,const GLType& type_)
{
	if(!OpenGL::initFuncShader) throw Exception("OpenGL not supported.");
}


bool					TexProject::Texture::glCreate
						(
							const uvec3& size_,
							const GLIFormat& iFormat_,
							const GLFormat& format_,
							const GLComponent& component_,
							const GLFilter filter_,
							const GLWrap& wrap_,
							const GLType& type_,
							GenFunc genFunc
						)
{
	if(!OpenGL::initFuncShader) throw Exception("OpenGL not supported.");

	Delete();

	{
		Resize(size_);	//size = size_;
		glIFormat = iFormat_;
		glFormat = format_;
		glComponent = component_;
		glFilter = filter_;
		glWrap = wrap_;
		glType = type_;
	}

	{
		glGenTextures(1,&glTexture);
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(glType,glTexture);
	}

	switch( glFilter )
	{
		case GLFilters::Off:
		{
			glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(glType,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			break;
		}
		case GLFilters::Linear:
		{
			glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(glType,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			break;
		}
		case GLFilters::Mipmap:
		{
			glTexParameteri(glType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(glType,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			break;
		}
	}

	switch( glWrap )
	{
		case GLWraps::Clamp:
		{
			glTexParameteri(glType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(glType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(glType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			break;
		}
		case GLWraps::Border:
		{
			glTexParameteri(glType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(glType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(glType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
			break;
		}
		case GLWraps::Repeat:
		{
			glTexParameteri(glType, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(glType, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(glType, GL_TEXTURE_WRAP_R, GL_REPEAT);
			break;
		}
		case GLWraps::Mirror:
		{
			glTexParameteri(glType, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(glType, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			glTexParameteri(glType, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
			break;
		}
	}

	{
		static GLfloat color[4];
		color[0] = 0.0f;	//borderColor.x;
		color[1] = 0.0f;	//borderColor.y;
		color[2] = 0.0f;	//borderColor.z;
		color[3] = 0.0f;	//borderColor.w;
		glTexParameterfv(glType, GL_TEXTURE_BORDER_COLOR, color);
	}

	switch(glType)
	{
		case GLTypes::tex2D:
		{
			if(genFunc)
			{
				auto arr = genFunc(this);
				glTexImage2D(GL_TEXTURE_2D, 0, glIFormat, size.x, size.y, 0, glFormat, glComponent, arr);
				if(arr) delete[] arr;
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, glIFormat, size.x, size.y, 0, glFormat, glComponent, nullptr);
			}
			break;
		}
	}
	if( glFilter == GLFilters::Mipmap )
	{
		//glGenerateMipmap(type);
	}

	glBindTexture(glType,0);

	OpenGL::ErrorTest();

	init = true;

	return true;
}



#endif






























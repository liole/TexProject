#include "TexProject_Textures.h"
using namespace TexProject;
using namespace TexProject::OpenGL;


#include <TexProject/TexProject_Windows.h>


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

bool					TexProject::Texture::Load(const string& filename)
{
#if __TEXPROJECT_DEVIL__
	return _devIL_Load2D(filename);
#endif

#if __TEXPROJECT_DEBUG__
	Message("[Texture]\nCan't Load Image '"+filename+"'");
#endif
	return false;
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

void					TexProject::Texture::Resize(uvec3 size_)
{
	if( size.x > 0 || size.y > 0 || size.z > 0 )
	{
		/*for(uint32 x = 0; x < size.x; ++x)
		{
			for(uint32 y = 0; y < size.y; ++y)
			{
				delete[] data[x][y];
			}
			delete[] data[x];
		}*/
		delete[] data;
		data = nullptr;
	}
	
	size = size_;

	if(size.x > 0 || size.y > 0 || size.z > 0)
	{
		data = new vec4[size.x*size.y*size.z];
		for(uint32 x = 0; x < size.x; ++x)
		for(uint32 y = 0; y < size.y; ++y)
		for(uint32 z = 0; z < size.z; ++z)
		{
			data[size.x*(0*size.y + y) + x] = vec4(0.0f,0.0f,0.0f,1.0f);
		}
		/*data = new vec4**[size.x];
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
		}*/
	}
}
void					TexProject::Texture::Build(Window::Render* window)
{
	if(window) window->Build(this);
}
void					TexProject::Texture::Draw()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0,0,Window::GetCurrent()->GetSize().x,Window::GetCurrent()->GetSize().y);

	glDrawShader.Use();
	glUse(0);

	glDrawArrays(GL_POINTS,0,1);

	OpenGL::Shader::UseNull();
}


#if __TEXPROJECT_DEVIL__

bool					TexProject::Texture::_devIL_Load2D(const string& filename)
{
	Delete();

	ILuint	id;

	ilGenImages(1,&id);
	ilBindImage(id);

	if(ilLoadImage(filename.c_str()) != IL_TRUE)
	{
		Message("[DevIL]\nCan't Load Image '"+filename+"'");
		ilDeleteImages(1,&id);
		return false;
	}
	DevIL::ErrorTest();

	ivec3 inILSize;
	inILSize.x		= ilGetInteger(IL_IMAGE_WIDTH);
	inILSize.y		= ilGetInteger(IL_IMAGE_HEIGHT);
	inILSize.z		= ilGetInteger(IL_IMAGE_DEPTH);

	Resize(uvec3(inILSize.x,inILSize.y,inILSize.z));

	auto ilOriginMode	= ilGetInteger(IL_ORIGIN_MODE);	// top-to-down or down-to-top
	/*
	IL_ORIGIN_LOWER_LEFT
	IL_ORIGIN_UPPER_LEFT
	*/

	auto inILType	= ilGetInteger(IL_IMAGE_TYPE);
	auto inILFormat	= ilGetInteger(IL_IMAGE_FORMAT);
	auto inILBytes	= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	auto inILBits	= ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
	auto inILData	= ilGetData();


	{
		ivec4	off(-1,-1,-1,-1);

		switch(inILFormat)
		{
			/*
			IL_COLOUR_INDEX
			IL_COLOR_INDEX
			IL_ALPHA
			IL_RGB
			IL_RGBA
			IL_BGR
			IL_BGRA
			IL_LUMINANCE
			IL_LUMINANCE_ALPHA
			*/
			case IL_ALPHA:				{ off = ivec4(-1,-1,-1,0); break; }	// not shure
			case IL_RGB:				{ off = ivec4(0,1,2,-1); break; }
			case IL_BGR:				{ off = ivec4(2,1,0,-1); break; }
			case IL_RGBA:				{ off = ivec4(0,1,2,3); break; }
			case IL_BGRA:				{ off = ivec4(2,1,0,3); break; }	// not shure
			case IL_LUMINANCE:			{ off = ivec4(0,0,0,-1); break; }	// not shure
			case IL_LUMINANCE_ALPHA:	{ off = ivec4(0,0,0,-1); break; }	// not shure
			default:
			{
				throw Exception("[DevIL] Image loading\nUnknown of forbidden format.");
			}
		}

		for(uint32 x = 0; x < size.x; ++x)
		for(uint32 y = 0; y < size.y; ++y)
		for(uint32 z = 0; z < size.z; ++z)
		{
			vec4 color(0.0f,0.0f,0.0f,1.0f);
			auto data =	inILData;
			data +=	(ilOriginMode==IL_ORIGIN_LOWER_LEFT)
					? ((z*size.y + y)*size.x + x)*inILBytes
					: ((z*size.y + (size.y-1-y))*size.x + x)*inILBytes;

			switch(inILType)
			{
				/*
				IL_BYTE           0x1400
				IL_UNSIGNED_BYTE  0x1401
				IL_SHORT          0x1402
				IL_UNSIGNED_SHORT 0x1403
				IL_INT            0x1404
				IL_UNSIGNED_INT   0x1405
				IL_FLOAT          0x1406
				IL_DOUBLE         0x140A
				IL_HALF           0x140B
				*/
				case IL_BYTE:
				{
					if(off.x>=0) color.x =  float32(float64(*((int8*)data+off.x) - INT8_MIN) / INT8_MAX);
					if(off.y>=0) color.y =  float32(float64(*((int8*)data+off.y) - INT8_MIN) / INT8_MAX);
					if(off.z>=0) color.z =  float32(float64(*((int8*)data+off.z) - INT8_MIN) / INT8_MAX);
					if(off.w>=0) color.w =  float32(float64(*((int8*)data+off.w) - INT8_MIN) / INT8_MAX);
					break;
				}
				case IL_UNSIGNED_BYTE:
				{
					if(off.x>=0) color.x =  float32(float64(*((uint8*)data+off.x)) / UINT8_MAX);
					if(off.y>=0) color.y =  float32(float64(*((uint8*)data+off.y)) / UINT8_MAX);
					if(off.z>=0) color.z =  float32(float64(*((uint8*)data+off.z)) / UINT8_MAX);
					if(off.w>=0) color.w =  float32(float64(*((uint8*)data+off.w)) / UINT8_MAX);
					break;
				}
				case IL_SHORT:
				{
					if(off.x>=0) color.x =  float32(float64(*((int16*)data+off.x) - INT16_MIN) / INT16_MAX);
					if(off.y>=0) color.y =  float32(float64(*((int16*)data+off.y) - INT16_MIN) / INT16_MAX);
					if(off.z>=0) color.z =  float32(float64(*((int16*)data+off.z) - INT16_MIN) / INT16_MAX);
					if(off.w>=0) color.w =  float32(float64(*((int16*)data+off.w) - INT16_MIN) / INT16_MAX);
					break;
				}
				case IL_UNSIGNED_SHORT:
				{
					if(off.x>=0) color.x =  float32(float64(*((uint16*)data+off.x)) / UINT16_MAX);
					if(off.y>=0) color.y =  float32(float64(*((uint16*)data+off.y)) / UINT16_MAX);
					if(off.z>=0) color.z =  float32(float64(*((uint16*)data+off.z)) / UINT16_MAX);
					if(off.w>=0) color.w =  float32(float64(*((uint16*)data+off.w)) / UINT16_MAX);
					break;
				}
				case IL_INT:
				{
					if(off.x>=0) color.x =  float32(float64(*((int32*)data+off.x) - INT32_MIN) / INT32_MAX);
					if(off.y>=0) color.y =  float32(float64(*((int32*)data+off.y) - INT32_MIN) / INT32_MAX);
					if(off.z>=0) color.z =  float32(float64(*((int32*)data+off.z) - INT32_MIN) / INT32_MAX);
					if(off.w>=0) color.w =  float32(float64(*((int32*)data+off.w) - INT32_MIN) / INT32_MAX);
					break;
				}
				case IL_UNSIGNED_INT:
				{
					if(off.x>=0) color.x =  float32(float64(*((uint32*)data+off.x)) / UINT32_MAX);
					if(off.y>=0) color.y =  float32(float64(*((uint32*)data+off.y)) / UINT32_MAX);
					if(off.z>=0) color.z =  float32(float64(*((uint32*)data+off.z)) / UINT32_MAX);
					if(off.w>=0) color.w =  float32(float64(*((uint32*)data+off.w)) / UINT32_MAX);
					break;
				}
				case IL_HALF:
				{
					if(off.x>=0) color.x =  float32(*((float16*)data+off.x));
					if(off.y>=0) color.y =  float32(*((float16*)data+off.y));
					if(off.z>=0) color.z =  float32(*((float16*)data+off.z));
					if(off.w>=0) color.w =  float32(*((float16*)data+off.w));
					break;
				}
				case IL_FLOAT:
				{
					if(off.x>=0) color.x =  float32(*((float32*)data+off.x));
					if(off.y>=0) color.y =  float32(*((float32*)data+off.y));
					if(off.z>=0) color.z =  float32(*((float32*)data+off.z));
					if(off.w>=0) color.w =  float32(*((float32*)data+off.w));
					break;
				}
				case IL_DOUBLE:
				{
					if(off.x>=0) color.x =  float32(*((float64*)data+off.x));
					if(off.y>=0) color.y =  float32(*((float64*)data+off.y));
					if(off.z>=0) color.z =  float32(*((float64*)data+off.z));
					if(off.w>=0) color.w =  float32(*((float64*)data+off.w));
					break;
				}
				default:
				{
					throw Exception("[DevIL] Image loading\nUnknown of forbidden type.");
				}
			}
			Get(x,y,z) = color;
		}
	}

	ilDeleteImages(1,&id);

	//Build();

	return true;
}

#endif

#if __TEXPROJECT_WIN__

bool					TexProject::Texture::winCreate()
{
	{
		winBitCount = 32;

		winBytesPerLine = ((size.x * winBitCount + 31)/32) * 4;

		/*{
			img.bFile.bfType = 0x4d42;
			img.bFile.bfSize = sizeof(BITMAPFILEHEADER)+ sizeof(BITMAPINFOHEADER)+ img.bytesPerLine*img.height;
			img.bFile.bfReserved1 = 0;
			img.bFile.bfReserved2 = 0;
			img.bFile.bfOffBits = sizeof(BITMAPFILEHEADER)+ sizeof(BITMAPINFOHEADER);
		}*/
		{
			winInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
			winInfoHeader.biWidth = size.x;
			winInfoHeader.biHeight = size.y;
			winInfoHeader.biPlanes = 1;
			winInfoHeader.biBitCount = 32;
			winInfoHeader.biCompression = BI_RGB;
			winInfoHeader.biSizeImage = 0; //for BI_RGB
			winInfoHeader.biXPelsPerMeter = 0;
			winInfoHeader.biYPelsPerMeter = 0;
			winInfoHeader.biClrUsed = 0;
			winInfoHeader.biClrImportant = 0;
		}
		{
			winTextureData = new BYTE[winBytesPerLine*size.y];
			for(uint32 x = 0; x < size.x; ++x)
			for(uint32 y = 0; y < size.y; ++y)
			{
				uint32 id = (y*winBytesPerLine + x*4);
				winTextureData[id+0] = BYTE(Get(x,y).x*255.0f);
				winTextureData[id+1] = BYTE(Get(x,y).y*255.0f);
				winTextureData[id+2] = BYTE(Get(x,y).z*255.0f);
				winTextureData[id+3] = BYTE(Get(x,y).w*255.0f);
			}
		}

		winBitmapHandle = CreateBitmap(size.x,size.y,1,32,winTextureData);

	}

	return true;
}
void					TexProject::Texture::winBuild()
{
	winCreate();
}

#endif


#ifdef __TEXPROJECT_OPENGL__

Texture*				TexProject::Texture::glCurrent[glMaxTextureSlots];
OpenGL::Shader			TexProject::Texture::glDrawShader;


void					TexProject::Texture::glUseNull(uint32 slot_,const GLType& type_)
{
	if(!OpenGL::initFuncShader) throw Exception("OpenGL not supported.");
}
void					TexProject::Texture::glBuild()
{
	auto t = new float32[size.x*size.y*size.z*4];

	for(uint32 x = 0; x < size.x; ++x)
	for(uint32 y = 0; y < size.y; ++y)
	for(uint32 z = 0; z < size.z; ++z)
	{
		auto id = (size.x*(z*size.y + y) + x);
		t[4*id+0] = data[id].x;
		t[4*id+1] = data[id].y;
		t[4*id+2] = data[id].z;
		t[4*id+3] = data[id].w;
	}

	{
		if(init && OpenGL::initFuncShader)
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
			glWrap = GLWraps::Clamp;
			if(size.z > 1) glType = GLTypes::tex3D;
			else glType = GLTypes::tex2D;
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

		init = true;
	}

	delete t;
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




// Generator::Noise
TexProject::Texture*			TexProject::Generator::Noise::SimpleMono(const uvec3& size)
{
	auto tex = new Texture;
	tex->Resize(size);

	for(uint32 x = 0; x < tex->GetSize().x; ++x)
	for(uint32 y = 0; y < tex->GetSize().y; ++y)
	for(uint32 z = 0; z < tex->GetSize().z; ++z)
	{
		tex->SetPixel(uvec3(x,y,z),vec4(vec3(rnd()),1.0f));
	}

	return tex;
}
TexProject::Texture*			TexProject::Generator::Noise::Perlin(const uvec3& size)
{
	auto noiseTex = Noise::SimpleMono(size);
	auto tex = new Texture; tex->Resize(size);

	const uint32 iterations = 8;

	for(uint32 i = 1; i < iterations; ++i)
	{
		float32 v = pow(float32(i)/iterations*(3.0f/5.0f), 1.5f);
		vec3 t = (1.0f / pow(2.0f,float32(i))) / vec3(size);
		for(uint32 x = 0; x < tex->GetSize().x; ++x)
		for(uint32 y = 0; y < tex->GetSize().y; ++y)
		for(uint32 z = 0; z < tex->GetSize().z; ++z)
		{
			tex->SetPixel
			(
				uvec3(x,y,z), 
				block
				(
					tex->GetPixel(uvec3(x,y,z)) +
					block(noiseTex->GetPixelCosine(vec3(float32(x),float32(y),float32(z))*t)*v,vec4(0.0f),vec4(1.0f)),
					vec4(0.0f),
					vec4(1.0f)
				)
			);
		}
	}

	return tex;
}

// Generator::Filter
TexProject::Texture*			TexProject::Filter::Noise::Perlin(Texture* in)
{
	auto noiseTex = in;
	auto tex = new Texture; tex->Resize(noiseTex->GetSize());

	const uint32 iterations = 8;

	for(uint32 i = 1; i < iterations; ++i)
	{
		float32 v = pow(float32(i)/iterations*(3.0f/5.0f), 1.5f);
		vec3 t = (1.0f / pow(2.0f,float32(i))) / vec3(noiseTex->GetSize());
		for(uint32 x = 0; x < tex->GetSize().x; ++x)
		for(uint32 y = 0; y < tex->GetSize().y; ++y)
		for(uint32 z = 0; z < tex->GetSize().z; ++z)
		{
			tex->SetPixel
			(
				uvec3(x,y,z), 
				block
				(
					tex->GetPixel(uvec3(x,y,z)) +
					block(noiseTex->GetPixelCosine(vec3(float32(x),float32(y),float32(z))*t)*v,vec4(0.0f),vec4(1.0f)),
					vec4(0.0f),
					vec4(1.0f)
				)
			);
		}
	}

	return tex;
}




























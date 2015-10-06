#include "TexProject_Textures.h"
using namespace TexProject;

#include <TexProject/TexProject_Windows.h>

#if __TEXPROJECT_OPENGL__
#include <TexProject/TexProject_OpenGL.h>
using namespace TexProject::OpenGL;
#endif



bool										TexProject::Texture::D2::Load(const string& filename)
{
#if __TEXPROJECT_DEVIL__
	return _DevIL_Load(filename);
#endif
	throw TexProject::Exception();
}
#if __TEXPROJECT_DEVIL__
bool										TexProject::Texture::D2::_DevIL_Load(const string& filename)
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

	//Resize(uvec3(inILSize.x,inILSize.y,inILSize.z));
	Create(uvec2(inILSize.x,inILSize.y));

	auto ilOriginMode	= ilGetInteger(IL_ORIGIN_MODE);	// top-to-down or down-to-top
	/*
	IL_ORIGIN_LOWER_LEFT
	IL_ORIGIN_UPPER_LEFT
	*/

	auto inILIFormat	= ilGetInteger(IL_IMAGE_BPP);
	auto inILType		= ilGetInteger(IL_IMAGE_TYPE);
	auto inILFormat		= ilGetInteger(IL_IMAGE_FORMAT);
	auto inILBytes		= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	auto inILBits		= ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
	auto inILData		= ilGetData();


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
				throw TexProject::Exception("[DevIL] Image loading\nUnknown of forbidden format.");
			}
		}

		for(uint32 x = 0; x < size.x; ++x)
		for(uint32 y = 0; y < size.y; ++y)
		{
			vec4 color(0.0f,0.0f,0.0f,1.0f);
			auto ilData =	inILData;
			ilData +=	(ilOriginMode==IL_ORIGIN_LOWER_LEFT)
				? (y*size.x + x)*inILBytes
				: ((size.y-1-y)*size.x + x)*inILBytes;

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
					if(off.x>=0) color.x =  float32(float64(*((int8*)ilData+off.x) - INT8_MIN) / INT8_MAX);
					if(off.y>=0) color.y =  float32(float64(*((int8*)ilData+off.y) - INT8_MIN) / INT8_MAX);
					if(off.z>=0) color.z =  float32(float64(*((int8*)ilData+off.z) - INT8_MIN) / INT8_MAX);
					if(off.w>=0) color.w =  float32(float64(*((int8*)ilData+off.w) - INT8_MIN) / INT8_MAX);
					break;
				}
				case IL_UNSIGNED_BYTE:
				{
					if(off.x>=0) color.x =  float32(float64(*((uint8*)ilData+off.x)) / UINT8_MAX);
					if(off.y>=0) color.y =  float32(float64(*((uint8*)ilData+off.y)) / UINT8_MAX);
					if(off.z>=0) color.z =  float32(float64(*((uint8*)ilData+off.z)) / UINT8_MAX);
					if(off.w>=0) color.w =  float32(float64(*((uint8*)ilData+off.w)) / UINT8_MAX);
					break;
				}
				case IL_SHORT:
				{
					if(off.x>=0) color.x =  float32(float64(*((int16*)ilData+off.x) - INT16_MIN) / INT16_MAX);
					if(off.y>=0) color.y =  float32(float64(*((int16*)ilData+off.y) - INT16_MIN) / INT16_MAX);
					if(off.z>=0) color.z =  float32(float64(*((int16*)ilData+off.z) - INT16_MIN) / INT16_MAX);
					if(off.w>=0) color.w =  float32(float64(*((int16*)ilData+off.w) - INT16_MIN) / INT16_MAX);
					break;
				}
				case IL_UNSIGNED_SHORT:
				{
					if(off.x>=0) color.x =  float32(float64(*((uint16*)ilData+off.x)) / UINT16_MAX);
					if(off.y>=0) color.y =  float32(float64(*((uint16*)ilData+off.y)) / UINT16_MAX);
					if(off.z>=0) color.z =  float32(float64(*((uint16*)ilData+off.z)) / UINT16_MAX);
					if(off.w>=0) color.w =  float32(float64(*((uint16*)ilData+off.w)) / UINT16_MAX);
					break;
				}
				case IL_INT:
				{
					if(off.x>=0) color.x =  float32(float64(*((int32*)ilData+off.x) - INT32_MIN) / INT32_MAX);
					if(off.y>=0) color.y =  float32(float64(*((int32*)ilData+off.y) - INT32_MIN) / INT32_MAX);
					if(off.z>=0) color.z =  float32(float64(*((int32*)ilData+off.z) - INT32_MIN) / INT32_MAX);
					if(off.w>=0) color.w =  float32(float64(*((int32*)ilData+off.w) - INT32_MIN) / INT32_MAX);
					break;
				}
				case IL_UNSIGNED_INT:
				{
					if(off.x>=0) color.x =  float32(float64(*((uint32*)ilData+off.x)) / UINT32_MAX);
					if(off.y>=0) color.y =  float32(float64(*((uint32*)ilData+off.y)) / UINT32_MAX);
					if(off.z>=0) color.z =  float32(float64(*((uint32*)ilData+off.z)) / UINT32_MAX);
					if(off.w>=0) color.w =  float32(float64(*((uint32*)ilData+off.w)) / UINT32_MAX);
					break;
				}
				case IL_HALF:
				{
					if(off.x>=0) color.x =  float32(*((float16*)ilData+off.x));
					if(off.y>=0) color.y =  float32(*((float16*)ilData+off.y));
					if(off.z>=0) color.z =  float32(*((float16*)ilData+off.z));
					if(off.w>=0) color.w =  float32(*((float16*)ilData+off.w));
					break;
				}
				case IL_FLOAT:
				{
					if(off.x>=0) color.x =  float32(*((float32*)ilData+off.x));
					if(off.y>=0) color.y =  float32(*((float32*)ilData+off.y));
					if(off.z>=0) color.z =  float32(*((float32*)ilData+off.z));
					if(off.w>=0) color.w =  float32(*((float32*)ilData+off.w));
					break;
				}
				case IL_DOUBLE:
				{
					if(off.x>=0) color.x =  float32(*((float64*)ilData+off.x));
					if(off.y>=0) color.y =  float32(*((float64*)ilData+off.y));
					if(off.z>=0) color.z =  float32(*((float64*)ilData+off.z));
					if(off.w>=0) color.w =  float32(*((float64*)ilData+off.w));
					break;
				}
				default:
				{
					throw TexProject::Exception("[DevIL] Image loading\nUnknown of forbidden type.");
				}
			}
			data[y*size.x + x] = color;
		}
	}

	ilDeleteImages(1,&id);

	return true;
}
#endif
#if __TEXPROJECT_OPENGL__

TexProject::Texture::D2&					TexProject::Texture::D2::operator = (OpenGL::Texture& source)
{
	if(source.GetType() == OpenGL::Texture::Type::D2)
	{
		Create(source.GetSize().xy());
		auto t = source.GetDataRGBA32F();
		for(uint32 i = 0; i < size.x*size.y; ++i)
		{
			data[i] = t[i];
		}
		delete[] t;
	}
	return *this;
}
#endif


bool					TexProject::Texture::Cube::Load(const string& filename)
{
#if __TEXPROJECT_DEVIL__
	return _DevIL_Load(filename);
#endif
	throw TexProject::Exception();
}
#if __TEXPROJECT_DEVIL__
bool					TexProject::Texture::Cube::_DevIL_Load(const string& filename)
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

	Create(inILSize.x);

	auto ilOriginMode	= ilGetInteger(IL_ORIGIN_MODE);	// top-to-down or down-to-top
	/*
	IL_ORIGIN_LOWER_LEFT
	IL_ORIGIN_UPPER_LEFT
	*/

	auto inILIFormat	= ilGetInteger(IL_IMAGE_BPP);
	auto inILType		= ilGetInteger(IL_IMAGE_TYPE);
	auto inILFormat		= ilGetInteger(IL_IMAGE_FORMAT);
	auto inILBytes		= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	auto inILBits		= ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
	//auto inILData		= ilGetData();


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
				throw TexProject::Exception("[DevIL] Image loading\nUnknown of forbidden format.");
			}
		}

		for(uint32 i = 0; i < 6; ++i)
		for(uint32 x = 0; x < size; ++x)
		for(uint32 y = 0; y < size; ++y)
		{
			vec4 color(0.0f,0.0f,0.0f,1.0f);

			ilBindImage(id);
			ilActiveFace(i);
			auto ilData = ilGetData();//inILData;

			ilData +=	(ilOriginMode==IL_ORIGIN_UPPER_LEFT)
				? (y*size + x)*inILBytes
				: ((size-1-y)*size + x)*inILBytes;

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
					if(off.x>=0) color.x =  float32(float64(*((int8*)ilData+off.x) - INT8_MIN) / INT8_MAX);
					if(off.y>=0) color.y =  float32(float64(*((int8*)ilData+off.y) - INT8_MIN) / INT8_MAX);
					if(off.z>=0) color.z =  float32(float64(*((int8*)ilData+off.z) - INT8_MIN) / INT8_MAX);
					if(off.w>=0) color.w =  float32(float64(*((int8*)ilData+off.w) - INT8_MIN) / INT8_MAX);
					break;
				}
				case IL_UNSIGNED_BYTE:
				{
					if(off.x>=0) color.x =  float32(float64(*((uint8*)ilData+off.x)) / UINT8_MAX);
					if(off.y>=0) color.y =  float32(float64(*((uint8*)ilData+off.y)) / UINT8_MAX);
					if(off.z>=0) color.z =  float32(float64(*((uint8*)ilData+off.z)) / UINT8_MAX);
					if(off.w>=0) color.w =  float32(float64(*((uint8*)ilData+off.w)) / UINT8_MAX);
					break;
				}
				case IL_SHORT:
				{
					if(off.x>=0) color.x =  float32(float64(*((int16*)ilData+off.x) - INT16_MIN) / INT16_MAX);
					if(off.y>=0) color.y =  float32(float64(*((int16*)ilData+off.y) - INT16_MIN) / INT16_MAX);
					if(off.z>=0) color.z =  float32(float64(*((int16*)ilData+off.z) - INT16_MIN) / INT16_MAX);
					if(off.w>=0) color.w =  float32(float64(*((int16*)ilData+off.w) - INT16_MIN) / INT16_MAX);
					break;
				}
				case IL_UNSIGNED_SHORT:
				{
					if(off.x>=0) color.x =  float32(float64(*((uint16*)ilData+off.x)) / UINT16_MAX);
					if(off.y>=0) color.y =  float32(float64(*((uint16*)ilData+off.y)) / UINT16_MAX);
					if(off.z>=0) color.z =  float32(float64(*((uint16*)ilData+off.z)) / UINT16_MAX);
					if(off.w>=0) color.w =  float32(float64(*((uint16*)ilData+off.w)) / UINT16_MAX);
					break;
				}
				case IL_INT:
				{
					if(off.x>=0) color.x =  float32(float64(*((int32*)ilData+off.x) - INT32_MIN) / INT32_MAX);
					if(off.y>=0) color.y =  float32(float64(*((int32*)ilData+off.y) - INT32_MIN) / INT32_MAX);
					if(off.z>=0) color.z =  float32(float64(*((int32*)ilData+off.z) - INT32_MIN) / INT32_MAX);
					if(off.w>=0) color.w =  float32(float64(*((int32*)ilData+off.w) - INT32_MIN) / INT32_MAX);
					break;
				}
				case IL_UNSIGNED_INT:
				{
					if(off.x>=0) color.x =  float32(float64(*((uint32*)ilData+off.x)) / UINT32_MAX);
					if(off.y>=0) color.y =  float32(float64(*((uint32*)ilData+off.y)) / UINT32_MAX);
					if(off.z>=0) color.z =  float32(float64(*((uint32*)ilData+off.z)) / UINT32_MAX);
					if(off.w>=0) color.w =  float32(float64(*((uint32*)ilData+off.w)) / UINT32_MAX);
					break;
				}
				case IL_HALF:
				{
					if(off.x>=0) color.x =  float32(*((float16*)ilData+off.x));
					if(off.y>=0) color.y =  float32(*((float16*)ilData+off.y));
					if(off.z>=0) color.z =  float32(*((float16*)ilData+off.z));
					if(off.w>=0) color.w =  float32(*((float16*)ilData+off.w));
					break;
				}
				case IL_FLOAT:
				{
					if(off.x>=0) color.x =  float32(*((float32*)ilData+off.x));
					if(off.y>=0) color.y =  float32(*((float32*)ilData+off.y));
					if(off.z>=0) color.z =  float32(*((float32*)ilData+off.z));
					if(off.w>=0) color.w =  float32(*((float32*)ilData+off.w));
					break;
				}
				case IL_DOUBLE:
				{
					if(off.x>=0) color.x =  float32(*((float64*)ilData+off.x));
					if(off.y>=0) color.y =  float32(*((float64*)ilData+off.y));
					if(off.z>=0) color.z =  float32(*((float64*)ilData+off.z));
					if(off.w>=0) color.w =  float32(*((float64*)ilData+off.w));
					break;
				}
				default:
				{
					throw TexProject::Exception("[DevIL] Image loading\nUnknown of forbidden type.");
				}
			}
			data[i][y*size + x] = color;
		}
	}

	ilDeleteImages(1,&id);

	return true;
}
#endif





























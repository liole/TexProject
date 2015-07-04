#include "TexProject_Textures.h"
using namespace TexProject;
using namespace TexProject::OpenGL;


#include <TexProject/TexProject_Windows.h>




bool					TexProject::Texture::D2::Load(const string& filename)
{
#if __TEXPROJECT_DEVIL__
	return _DevIL_Load2D(filename);
#endif
	throw TexProject::Exception();
}


#if __TEXPROJECT_DEVIL__

bool					TexProject::Texture::D2::_DevIL_Load2D(const string& filename)
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
			//Get(x,y,z) = color;
		}
	}

	ilDeleteImages(1,&id);

	return true;
}

#endif


#if __TEXPROJECT_OPENGL__


const TexProject::OpenGL::Texture::Filter	TexProject::OpenGL::Texture::Filter::Off(Minification::Off,Magnification::Off);
const TexProject::OpenGL::Texture::Filter	TexProject::OpenGL::Texture::Filter::Linear(Minification::Linear,Magnification::Linear);
const TexProject::OpenGL::Texture::Filter	TexProject::OpenGL::Texture::Filter::Mipmap(Minification::Mipmap,Magnification::Linear);


#endif

/*
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
TexProject::Texture*			TexProject::Filter::Noise::Perlin(Texture* in,uint32 iterations)
{
	auto noiseTex = in;
	auto tex = new Texture; tex->Resize(noiseTex->GetSize());

	float32 v = 6.0f/10.0f;
	for(uint32 i = 1; i < iterations; ++i)
	{
		//v *= v;
		v = (1.0f - v) * v;

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
*/



























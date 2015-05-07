#pragma once
#include <TexProject/TexProject_Header.h>

#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>


#if __TEXPROJECT_DEVIL__
#include <TexProject/TexProject_DevIL.h>
#endif

#if __TEXPROJECT_OPENGL__
#include <TexProject/TexProject_OpenGL.h>
#include <TexProject/TexProject_Shaders.h>
#endif


namespace TexProject
{
	struct Texture
	{
		friend Window::Render;
		friend Window::RenderContext::Default;
		friend Window::RenderContext::OpenGL;
		friend Interface::Default::Panel::Image;

		typedef void*(*GenFunc)(Texture*);


		static void							Init();
		static void							InitDraw();
		static void							FreeDraw();

#if __TEXPROJECT_OPENGL__

		struct GLTypes
		{
			enum Enum
			{
				tex1D								= GL_TEXTURE_1D,
				tex1DArray							= GL_TEXTURE_1D_ARRAY,
				tex2D								= GL_TEXTURE_2D,
				tex2DArr							= GL_TEXTURE_2D_ARRAY,
				tex3D								= GL_TEXTURE_3D,
				texCube								= GL_TEXTURE_CUBE_MAP,
				texCubeArr							= GL_TEXTURE_CUBE_MAP_ARRAY
			};
		};
		struct GLInternalFormats
		{
			enum Enum
			{
				R8								= GL_R8,
				R16								= GL_R16,
				R16F							= GL_R16F,
				R32F							= GL_R32F,
				RG8								= GL_RG8,
				RG16							= GL_RG16,
				RG16F							= GL_RG16F,
				RG32F							= GL_RG32F,
				RGB8							= GL_RGB8,
				RGB16							= GL_RGB16,
				RGB16F							= GL_RGB16F,
				RGB32F							= GL_RGB32F,
				RGBA8							= GL_RGBA8,
				RGBA16							= GL_RGBA16,
				RGBA16F							= GL_RGBA16F,
				RGBA32F							= GL_RGBA32F,

				/*Depth16							= GL_DEPTH_COMPONENT16,
				Depth24							= GL_DEPTH_COMPONENT24,
				Depth32							= GL_DEPTH_COMPONENT32,
				Depth32F						= GL_DEPTH_COMPONENT32F*/
			};
		};
		struct GLFormats
		{
			enum Enum
			{
				R								= GL_RED,
				G								= GL_GREEN,
				B								= GL_BLUE,
				A								= GL_ALPHA,
				L								= GL_LUMINANCE,
				RG								= GL_RG,
				RGB								= GL_RGB,
				BGR								= GL_BGR,
				RGBA							= GL_RGBA,
				BGRA							= GL_BGRA,

				Depth							= GL_DEPTH_COMPONENT
			};
		};
		struct GLComponents
		{
			enum Enum
			{
				UByte							= GL_UNSIGNED_BYTE,
				UShort							= GL_UNSIGNED_SHORT,
				UInt							= GL_UNSIGNED_INT,
				Byte							= GL_BYTE,
				Short							= GL_SHORT,
				Int								= GL_INT,
				Half							= GL_HALF_FLOAT,
				Float							= GL_FLOAT
			};
		};
		struct GLWraps
		{
			enum Enum
			{
				Clamp,
				Repeat,
				Border,
				Mirror
			};
		};
		struct GLFilters
		{
			enum Enum
			{
				Off,
				Linear,
				Mipmap,
			};
		};

		typedef GLTypes::Enum				GLType;
		typedef GLInternalFormats			GLIFormats;
		typedef GLInternalFormats::Enum		GLInternalFormat,GLIFormat;
		typedef GLFormats::Enum				GLFormat;
		typedef GLComponents::Enum			GLComponent;
		typedef GLWraps::Enum				GLWrap;
		typedef GLFilters::Enum				GLFilter;

#endif

	protected:

		bool			init = false;
		vec4*			data = nullptr;
		uvec3			size = uvec3(0);

	public:

		void								Delete();

											Texture() = default;
											~Texture();

		bool								Load(const string& filename);
		inline vec4&						Get(uint32 x,uint32 y);
		inline vec4&						Get(uint32 x,uint32 y,uint32 z);
		inline uvec3						GetSize() const;
		void								Resize(uvec3 size_);
		void								Build(Window::Render* window);
		void								Draw();

#if __TEXPROJECT_DEVIL__
		bool								_devIL_Load2D(const string& filename);
#endif
#if __TEXPROJECT_WIN__

	protected:

		uint32								winBitCount = 32;
		uint32								winBytesPerLine = 0;
		//BITMAPFILEHEADER					winFileHeader;
		HBITMAP								winBitmapHandle = NULL;
		BITMAPINFOHEADER					winInfoHeader;
		BYTE*								winTextureData = nullptr;

	public:

		bool								winCreate();
		void								winBuild();

#endif
#if __TEXPROJECT_OPENGL__

	protected:

		static const uint32					glMaxTextureSlots = 32;
		static Texture*						glCurrent[glMaxTextureSlots];
		static OpenGL::Shader				glDrawShader;

		GLFilter							glFilter = GLFilters::Off;
		GLWrap								glWrap = GLWraps::Clamp;
		GLType								glType = GLTypes::tex2D;
		GLIFormat							glIFormat = GLIFormats::RGB8;
		GLFormat							glFormat = GLFormats::RGB;
		GLComponent							glComponent = GLComponents::UByte;
		GLuint								glTexture = 0;

	public:
		static void							glUseNull(uint32 slot_ = 0, const GLType& type_ = GLTypes::tex2D);


		bool								glCreate(
														const uvec3& size_,
														const GLIFormat& iFormat_,
														const GLFormat& format_,
														const GLComponent& component_,
														const GLFilter filter_,
														const GLWrap& wrap_,
														const GLType& type_ = GLTypes::tex2D,
														GenFunc genFunc = nullptr
													);
		void								glBuild();

		inline void							glUse(uint32 slot_ = 0);
#endif

	};
}


void										TexProject::Texture::glUse(uint32 slot_)
{
#ifdef __TEXPROJECT_OPENGL__
	if( slot_ < glMaxTextureSlots && init && glTexture )
	{
		glCurrent[slot_] = this;
		OpenGL::glActiveTexture(GL_TEXTURE0+slot_); glBindTexture(glType,glTexture);
	}
	else
	{
		Message("Error while seting a texture");
	}
#else
	glCurrent[slot_] = this;
	OpenGL::glActiveTexture(GL_TEXTURE0+slot_); glBindTexture(glType,glTexture);
#endif
}


inline TexProject::vec4&					TexProject::Texture::Get(uint32 x,uint32 y)
{
#if __TEXPROJECT_DEBUG__
	if(x < size.x && y < size.y && size.z > 0)
	{
		return data[size.x*(0*size.y + y) + x];
	}
	else
	{
		throw Exception("Out of texture data array.");
	}
#else
	return data[size.x*(0*size.y + y) + x];
#endif
}
inline TexProject::vec4&					TexProject::Texture::Get(uint32 x,uint32 y,uint32 z)
{
#if __TEXPROJECT_DEBUG__
	if(x < size.x && y < size.y && z < size.z)
	{
		return data[size.x*(z*size.y + y) + x];
	}
	else
	{
		throw Exception("Out of texture data array.");
	}
#else
	return data[size.x*(z*size.y + y) + x];
#endif
}
inline TexProject::uvec3					TexProject::Texture::GetSize() const
{
	return size;
}




















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
	namespace Texture
	{
		namespace Exception
		{
			class InvalidTextureCoord: public Exception {};
		}

		enum struct Type
		{
			D1,
			D2,
			D3,
			Cube
		};

		struct D1
		{
		protected:

			vec4*	data = nullptr;
			uint32	size = 0;

		public:

			inline D1() = default;
			inline D1(const D1& source);
			inline ~D1();

			inline void						Create(uint32 size_);
			inline void						Delete();
			//bool							Load(const string& filename);
			inline void						Fill(const vec4& color_);

			inline uint32					GetSize() const;

			// Direct storage access
			inline void						SetPixel(uint32 pos_,const vec4& color_);
			inline vec4						GetPixel(uint32 pos_);
			inline vec4*					GetData() const;
			inline void*					GetDataRGBA32F() const;

			// Logic acess with interpolation
			inline vec4						GetPixelNearestClamp(float32 pos_) const;
			inline vec4						GetPixelLinearClamp(float32 pos_) const;

#if __TEXPROJECT_OPENGL__
			inline D1&						operator = (OpenGL::Texture& source);
#endif
		};
		struct D2
		{
		protected:

			vec4* data = nullptr;
			uvec2 size = uvec2(0);

		public:

			inline D2() = default;
			inline D2(const D2& source);
			inline ~D2();

			inline void						Create(const uvec2& size_);
			inline void						Delete();
			bool							Load(const string& filename);
			inline void						Fill(const vec4& color_);

			inline uvec2					GetSize() const;

			// Direct storage access
			inline void						SetPixel(const uvec2& pos_,const vec4& color_);
			inline vec4						GetPixel(const uvec2& pos_);
			inline vec4*					GetData() const;
			inline void*					GetDataRGBA32F() const;

			// Logic acess with interpolation
			inline vec4						GetPixelNearestClamp(const vec2& pos_) const;
			inline vec4						GetPixelLinearClamp(const vec2& pos_) const;

#if __TEXPROJECT_DEVIL__
			bool							_DevIL_Load(const string& filename);
#endif
#if __TEXPROJECT_OPENGL__
			inline D2&						operator = (OpenGL::Texture& source);
#endif
		};
		struct D3
		{
		protected:

			vec4*	data = nullptr;
			uvec3	size = 0;

		public:

			inline D3() = default;
			inline D3(const D3& source);
			inline ~D3();

			inline void						Create(const uvec3& size_);
			inline void						Delete();
			//bool							Load(const string& filename);
			inline void						Fill(const vec4& color_);

			inline uvec3					GetSize() const;

			// Direct storage access
			inline void						SetPixel(const uvec3& pos_,const vec4& color_);
			inline vec4						GetPixel(const uvec3& pos_);
			inline vec4*					GetData() const;
			inline void*					GetDataRGBA32F() const;

			// Logic acess with interpolation
			inline vec4						GetPixelNearestClamp(const vec3& pos_) const;
			inline vec4						GetPixelLinearClamp(const vec3& pos_) const;

#if __TEXPROJECT_OPENGL__
			inline D3&						operator = (OpenGL::Texture& source);
#endif
		};
		struct Cube
		{
		public:

			enum class Face: uint32
			{
				Right						= 0,
				Left						= 1,
				Top							= 2,
				Bottom						= 3,
				Front						= 4,
				Back						= 5
			};

		protected:
			vec4*							data[6];
			uint32							size = 0;

		public:
			inline							Cube();
			inline							~Cube();

			inline void						Create(uint32 size_);
			bool							Load(const string& filename);
			inline void						Fill(const vec4& color_);
			inline void						Fill(Face face_,const vec4& color_);
			inline void						Delete();

			inline uint32					GetSize() const;

			// Direct storage access
			inline void						SetPixel(Face face_,const uvec2& pos_,const vec4& color_);
			inline vec4						GetPixel(Face face_,const uvec2& pos_);
			inline void*					GetDataRGBA32F() const;
			inline void*					GetDataRGBA32F(Face face_) const;

#if __TEXPROJECT_DEVIL__
			bool							_DevIL_Load(const string& filename);
#endif
		};
	}


#if __TEXPROJECT_WIN__
	namespace Windows
	{
		struct Texture
		{
			friend Interface::Default::Panel::Image;
		protected:

			uvec2												size = uvec2(0);
			Window::RenderContext::Default* const				renderContext;
			uint32												bitCount = 32;
			uint32												bytesPerLine = 0;
			HBITMAP												bitmap = NULL;
			BITMAPINFOHEADER									infoHeader;
			BYTE*												textureData = nullptr;

		public:

			Texture(Window::Render* window);
			~Texture();

			inline Texture&						operator = (const TexProject::Texture::D2& source);

			inline bool							Create(uvec2 size_,vec4* data_);
			inline void							Delete();

			inline uvec2					GetSize() const;

			inline Window::RenderContext::Default*				GetRenderContext() const;

		};
	}
#endif


#if __TEXPROJECT_OPENGL__
	namespace OpenGL
	{
		struct Texture
		{
		public:

			enum class Type: GLenum
			{
				D1								= GL_TEXTURE_1D,
				D1Array							= GL_TEXTURE_1D_ARRAY,
				D2								= GL_TEXTURE_2D,
				D2Array							= GL_TEXTURE_2D_ARRAY,
				D3								= GL_TEXTURE_3D,
				Cube							= GL_TEXTURE_CUBE_MAP,
				CubeArray						= GL_TEXTURE_CUBE_MAP_ARRAY
			};
			enum class InternalFormat: GLint
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

				Depth16							= GL_DEPTH_COMPONENT16,
				Depth24							= GL_DEPTH_COMPONENT24,
				Depth32							= GL_DEPTH_COMPONENT32,
				Depth32F						= GL_DEPTH_COMPONENT32F
			};
			enum class Format: GLenum
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
			enum class Component: GLenum
			{
				UByte							= GL_UNSIGNED_BYTE,
				UInt8							= GL_UNSIGNED_BYTE,
				UShort							= GL_UNSIGNED_SHORT,
				UInt16							= GL_UNSIGNED_SHORT,
				UInt							= GL_UNSIGNED_INT,
				UInt32							= GL_UNSIGNED_INT,
				Byte							= GL_BYTE,
				Int8							= GL_BYTE,
				Short							= GL_SHORT,
				Int16							= GL_SHORT,
				Int								= GL_INT,
				Int32							= GL_INT,
				Half							= GL_HALF_FLOAT,
				Float16							= GL_HALF_FLOAT,
				Float							= GL_FLOAT,
				Float32							= GL_FLOAT
			};
			enum class Wrap: GLint
			{
				Clamp							= GL_CLAMP_TO_EDGE,
				Repeat							= GL_REPEAT,
				Border							= GL_CLAMP_TO_BORDER,
				Mirror							= GL_MIRRORED_REPEAT
			};
			struct Filter
			{
			public:

				enum class Minification: GLint
				{
					Off						= GL_NEAREST,
					Linear					= GL_LINEAR,
					MipmapNearestNearest	= GL_NEAREST_MIPMAP_NEAREST,
					MipmapLinearNearest		= GL_LINEAR_MIPMAP_NEAREST,
					MipmapNearestLinear		= GL_NEAREST_MIPMAP_LINEAR,
					MipmapLinearLinear		= GL_LINEAR_MIPMAP_LINEAR,
					Mipmap					= MipmapLinearLinear
				};
				enum class Magnification: GLint
				{
					Off						= GL_NEAREST,
					Linear					= GL_LINEAR
				};

				typedef Minification		Min;
				typedef Magnification		Mag;

				Minification				min = Minification::Mipmap;
				Magnification				mag = Magnification::Linear;

				inline Filter() = default;
				inline Filter(const Filter&) = default;
				inline Filter(const Minification& min_,const Magnification& mag_):
					min(min_),mag(mag_)
				{
				}

				static const Filter			Off;
				static const Filter			Linear;
				static const Filter			Mipmap;
			};

			typedef InternalFormat			IFormat;

			/*static inline int32			GetSlotCount()
			{
				static GLint result;
				glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,&result);
				return (int32)result;
			}*/

		protected:

			Window::RenderContext::OpenGL* const			renderContext;

			Type							type = Type::D2;
			InternalFormat					internalFormat = InternalFormat::RGBA32F;
			Format							format = Format::BGRA;
			Component						component = Component::Float32;
			Wrap							wrap = Wrap::Repeat;
			Filter							filter = Filter::Mipmap;

			uvec3							size = uvec3(0);
			GLuint							texture = 0;
			vec4							border = vec4(0.0f);

		public:

			inline Texture(Window::Render* window);
			inline Texture(Window::RenderContext::Basic* renderContext_);
			inline ~Texture();

			inline Texture&					operator = (const TexProject::Texture::D1& source);
			inline Texture&					operator = (const TexProject::Texture::D2& source);
			inline Texture&					operator = (const TexProject::Texture::D3& source);
			inline Texture&					operator = (const TexProject::Texture::Cube& source);

			inline Type						GetType() const
			{
				return type;
			}
			inline InternalFormat			GetInternalFormat() const
			{
				return internalFormat;
			}
			inline Format					GetFormat() const
			{
				return format;
			}
			inline Component				GetComponent() const
			{
				return component;
			}
			inline Wrap						GetWrap() const
			{
				return wrap;
			}
			inline Filter					GetFilter() const
			{
				return filter;
			}
			inline uvec3					GetSize() const
			{
				return size;
			}

			inline void						Create(Type type_,InternalFormat internalFormat_,Format format_,Component component_,Wrap wrap_,Filter filter_,uvec3 size_,void* data_);
			inline void						Delete();
			inline void						Use(uint32 level = 0);
			inline void						Unuse(uint32 level);
			inline void						Unuse();
			inline GLuint					GetTexture() const
			{
				return texture;
			}
			inline vec4*					GetDataRGBA32F();
			inline Window::RenderContext::OpenGL*			GetRenderContext() const;

		};
	}
#endif


	/*Неймспейс генераторів*/
	namespace Generator
	{
		/*Неймспейс шумів*/
		namespace Noise
		{
			/*Монохромний шум*/
			/*
			Texture*						SimpleMono(const uvec3& size);
			Texture*						Perlin(const uvec3& size);
			*/
		}
	}
	/*Неймспейс фільтрів*/
	namespace Filter
	{
		/*Неймспейс шумів-фільтрів*/
		namespace Noise
		{
			/*
			Texture*						Perlin(Texture* in,uint32 iterations);
			*/
		}
	}
}


inline TexProject::Texture::D1::D1(const D1& source):
	size(source.size),
	data(new vec4[source.size])
{
	for(uint32 i = 0; i < size; ++i) data[i] = source.data[i];
}
inline TexProject::Texture::D1::~D1()
{
	Delete();
}
inline void									TexProject::Texture::D1::Create(uint32 size_)
{
	Delete();

	size = size_;

	data = new vec4[size];
}
inline void									TexProject::Texture::D1::Delete()
{
	if(size > 0)
	{
		if(data) delete[] data;
		size = 0;
	}
}
inline void									TexProject::Texture::D1::Fill(const vec4& color_)
{
	for(uint32 i = 0; i < size; ++i) data[i] = color_;
}
inline TexProject::uint32					TexProject::Texture::D1::GetSize() const
{
	return size;
}
inline void									TexProject::Texture::D1::SetPixel(uint32 pos_,const vec4& color_)
{
#if __TEXPROJECT_DEBUG__
	if(pos_ >= size) throw Exception::InvalidTextureCoord();
#endif
	data[pos_] = color_;
}
inline TexProject::vec4						TexProject::Texture::D1::GetPixel(uint32 pos_)
{
#if __TEXPROJECT_DEBUG__
	if(pos_ >= size) throw Exception::InvalidTextureCoord();
#endif
	return data[pos_];
}
inline TexProject::vec4*					TexProject::Texture::D1::GetData() const
{
	auto data_ = new vec4[size];
	for(uint32 i = 0; i < size; ++i)
	{
		data_[i] = data[i];
	}
	return data_;
}
inline void*								TexProject::Texture::D1::GetDataRGBA32F() const
{
	auto data_ = new float32[size*4];
	for(uint32 i = 0; i < size; ++i)
	{
		data_[i*4+0] = data[i].x;
		data_[i*4+1] = data[i].y;
		data_[i*4+2] = data[i].z;
		data_[i*4+3] = data[i].w;
	}
	return data_;
}
inline TexProject::vec4						TexProject::Texture::D1::GetPixelNearestClamp(float32 pos_) const
{
	static uint32 t;

	t = uint32(block(pos_,0.0f,1.0f)*float32(size));

	return data[t];
}
inline TexProject::vec4						TexProject::Texture::D1::GetPixelLinearClamp(float32 pos_) const
{
	static float32 t;
	static uint32 nearPos,farPos;

	t = block(pos_,0.0f,1.0f)*float32(size-1);

	nearPos = uint32(std::floor(t));
	farPos = uint32(std::ceil(t));

	t -= float32(nearPos);

	return bezier(data[nearPos],data[farPos],t);
}

#if __TEXPROJECT_OPENGL__

inline TexProject::Texture::D1&				TexProject::Texture::D1::operator = (OpenGL::Texture& source)
{
	if(source.GetType() == OpenGL::Texture::Type::D1)
	{
		Create(source.GetSize().x);
		auto t = source.GetDataRGBA32F();
		for(uint32 i = 0; i < size; ++i)
		{
			data[i] = t[i];
		}
		delete[] t;
	}
	return *this;
}

#endif




inline TexProject::Texture::D2::D2(const D2& source):
	size(source.size),
	data(new vec4[source.size.x*source.size.y])
{
	for(uint32 i = 0; i < size.x*size.y; ++i) data[i] = source.data[i];
}
inline TexProject::Texture::D2::~D2()
{
	Delete();
}
inline void									TexProject::Texture::D2::Create(const uvec2& size_)
{
	Delete();

	size = size_;

	data = new vec4[size.x*size.y];
}
inline void									TexProject::Texture::D2::Delete()
{
	if(size.x > 0 && size.y > 0)
	{
		if(data) delete[] data;
		size = uvec2(0);
	}
}
inline void									TexProject::Texture::D2::Fill(const vec4& color_)
{
	for(uint32 i = 0; i < size.x*size.y; ++i) data[i] = color_;
}
inline TexProject::uvec2					TexProject::Texture::D2::GetSize() const
{
	return size;
}
inline void									TexProject::Texture::D2::SetPixel(const uvec2& pos_,const vec4& color_)
{
#if __TEXPROJECT_DEBUG__
	if(pos_.x >= size.x || pos_.y >= size.y) throw Exception::InvalidTextureCoord();
#endif
	data[pos_.y*size.x + pos_.x] = color_;
}
inline TexProject::vec4						TexProject::Texture::D2::GetPixel(const uvec2& pos_)
{
#if __TEXPROJECT_DEBUG__
	if(pos_.x >= size.x || pos_.y >= size.y) throw Exception::InvalidTextureCoord();
#endif
	return data[pos_.y*size.x + pos_.x];
}
inline TexProject::vec4*					TexProject::Texture::D2::GetData() const
{
	auto data_ = new vec4[size.x*size.y];
	for(uint32 i = 0; i < size.x*size.y; ++i)
	{
		data_[i] = data[i];
	}
	return data_;
}
inline void*								TexProject::Texture::D2::GetDataRGBA32F() const
{
	auto data_ = new float32[size.x*size.y*4];
	for(uint32 i = 0; i < size.x*size.y; ++i)
	{
		data_[i*4+0] = data[i].x;
		data_[i*4+1] = data[i].y;
		data_[i*4+2] = data[i].z;
		data_[i*4+3] = data[i].w;
	}
	return data_;
}
inline TexProject::vec4						TexProject::Texture::D2::GetPixelNearestClamp(const vec2& pos_) const
{
	static uvec2 t;

	t = block(pos_,vec2(0.0f),vec2(1.0f))*vec2(size);

	return data[t.y*size.x + t.x];
}
inline TexProject::vec4						TexProject::Texture::D2::GetPixelLinearClamp(const vec2& pos_) const
{
	static vec2 t;
	static uvec2 nearPos,farPos;

	t = block(pos_,vec2(0.0f),vec2(1.0f))*vec2(size-1);

	nearPos = uvec2(uint32(std::floor(t.x)),uint32(std::floor(t.y)));
	farPos = uvec2(uint32(std::ceil(t.x)),uint32(std::ceil(t.y)));

	t -= vec2(nearPos);

	return bezier
	(
		bezier(data[nearPos.y*size.x + nearPos.x],data[nearPos.y*size.x + farPos.x],t.x),
		bezier(data[farPos.y*size.x + nearPos.x],data[farPos.y*size.x + farPos.x],t.x),
		t.y
	);
}

#if __TEXPROJECT_OPENGL__

inline TexProject::Texture::D2&				TexProject::Texture::D2::operator = (OpenGL::Texture& source)
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




inline TexProject::Texture::D3::D3(const D3& source):
	size(source.size),
	data(new vec4[source.size.x*source.size.y*source.size.z])
{
	for(uint32 i = 0; i < source.size.x*source.size.y*source.size.z; ++i) data[i] = source.data[i];
}
inline TexProject::Texture::D3::~D3()
{
	Delete();
}
inline void									TexProject::Texture::D3::Create(const uvec3& size_)
{
	Delete();

	size = size_;

	data = new vec4[size.x*size.y*size.z];
}
inline void									TexProject::Texture::D3::Delete()
{
	if(size.x*size.y*size.z > 0)
	{
		if(data) delete[] data;
		size = 0;
	}
}
inline void									TexProject::Texture::D3::Fill(const vec4& color_)
{
	for(uint32 i = 0; i < size.x*size.y*size.z; ++i) data[i] = color_;
}
inline TexProject::uvec3					TexProject::Texture::D3::GetSize() const
{
	return size;
}
inline void									TexProject::Texture::D3::SetPixel(const uvec3& pos_,const vec4& color_)
{
#if __TEXPROJECT_DEBUG__
	if(pos_.x >= size.x || pos_.y >= size.y || pos_.z >= size.z) throw Exception::InvalidTextureCoord();
#endif
	data[(pos_.z*size.y + pos_.y)*size.x + pos_.x] = color_;
}
inline TexProject::vec4						TexProject::Texture::D3::GetPixel(const uvec3& pos_)
{
#if __TEXPROJECT_DEBUG__
	if(pos_.x >= size.x || pos_.y >= size.y || pos_.z >= size.z) throw Exception::InvalidTextureCoord();
#endif
	return data[(pos_.z*size.y + pos_.y)*size.x + pos_.x];
}
inline TexProject::vec4*					TexProject::Texture::D3::GetData() const
{
	auto data_ = new vec4[size.x*size.y*size.z];
	for(uint32 i = 0; i < size.x*size.y*size.z; ++i)
	{
		data_[i] = data[i];
	}
	return data_;
}
inline void*								TexProject::Texture::D3::GetDataRGBA32F() const
{
	auto data_ = new float32[size.x*size.y*size.z*4];
	for(uint32 i = 0; i < size.x*size.y*size.z; ++i)
	{
		data_[i*4+0] = data[i].x;
		data_[i*4+1] = data[i].y;
		data_[i*4+2] = data[i].z;
		data_[i*4+3] = data[i].w;
	}
	return data_;
}
inline TexProject::vec4						TexProject::Texture::D3::GetPixelNearestClamp(const vec3& pos_) const
{
	static uvec3 t;

	t = uvec3(block(pos_,vec3(0.0f),vec3(1.0f))*vec3(size));

	return data[(t.z*size.y + t.y)*size.x + t.x];
}
inline TexProject::vec4						TexProject::Texture::D3::GetPixelLinearClamp(const vec3& pos_) const
{
	static vec3 t;
	static uvec3 nearPos,farPos;

	t = block(pos_,vec3(0.0f),vec3(1.0f))*vec3(size-1);

	nearPos = uvec3(uint32(std::floor(t.x)),uint32(std::floor(t.y)),uint32(std::floor(t.z)));
	farPos = uvec3(uint32(std::ceil(t.x)),uint32(std::ceil(t.y)),uint32(std::ceil(t.z)));

	t -= vec3(nearPos);

	return bezier
	(
		bezier
		(
			//bezier(data[nearPos.y*size.x + nearPos.x],data[nearPos.y*size.x + farPos.x],t.x),
			//bezier(data[farPos.y*size.x + nearPos.x],data[farPos.y*size.x + farPos.x],t.x),
			bezier(data[(nearPos.z*size.y + nearPos.y)*size.x + nearPos.x],data[(nearPos.z*size.y + nearPos.y)*size.x + farPos.x],t.x),
			bezier(data[(nearPos.z*size.y + farPos.y)*size.x+ nearPos.x],data[(nearPos.z*size.y + farPos.y)*size.x + farPos.x],t.x),
			t.y
		),
		bezier
		(
			bezier(data[(farPos.z*size.y + nearPos.y)*size.x + nearPos.x],data[(farPos.z*size.y + nearPos.y)*size.x + farPos.x],t.x),
			bezier(data[(farPos.z*size.y + farPos.y)*size.x + nearPos.x],data[(farPos.z*size.y + farPos.y)*size.x + farPos.x],t.x),
			t.y
		),
		t.z
	);
}


#if __TEXPROJECT_OPENGL__

inline TexProject::Texture::D3&				TexProject::Texture::D3::operator = (OpenGL::Texture& source)
{
	if(source.GetType() == OpenGL::Texture::Type::D3)
	{
		Create(source.GetSize());
		auto t = source.GetDataRGBA32F();
		for(uint32 i = 0; i < size.x*size.y*size.z; ++i)
		{
			data[i] = t[i];
		}
		delete[] t;
	}
	return *this;
}

#endif




inline										TexProject::Texture::Cube::Cube()
{
	for(uint32 i = 0; i < 6; ++i) data[i] = nullptr;
}
inline										TexProject::Texture::Cube::~Cube()
{
	Delete();
}
inline void									TexProject::Texture::Cube::Create(uint32 size_)
{
	Delete();

	size = size_;

	for(uint32 i = 0; i < 6; ++i)
	{
		data[i] = new vec4[size*size];
	}
}
inline void									TexProject::Texture::Cube::Fill(const vec4& color_)
{
	for(uint32 i = 0; i < 6; ++i)
	{
		for(uint32 j = 0; j < size*size; ++j)
		{
			data[i][j] = color_;
		}
	}
}
inline void									TexProject::Texture::Cube::Fill(Face face_,const vec4& color_)
{
	for(uint32 j = 0; j < size*size; ++j)
	{
		data[(uint32)face_][j] = color_;
	}
}
inline void									TexProject::Texture::Cube::Delete()
{
	for(uint32 i = 0; i < 6; ++i)
	{
		if(data[i]) { delete[] data[i]; data[i] = nullptr; }
	}

	size = 0;
}
inline TexProject::uint32					TexProject::Texture::Cube::GetSize() const
{
	return size;
}
inline void									TexProject::Texture::Cube::SetPixel(Face face_,const uvec2& pos_,const vec4& color_)
{
#if __TEXPROJECT_DEBUG__
	if(pos_.x >= size || pos_.y >= size) throw Exception::InvalidTextureCoord();
#endif
	data[(uint32)face_][pos_.y*size + pos_.x] = color_;
}
inline TexProject::vec4						TexProject::Texture::Cube::GetPixel(Face face_,const uvec2& pos_)
{
#if __TEXPROJECT_DEBUG__
	if(pos_.x >= size || pos_.y >= size) throw Exception::InvalidTextureCoord();
#endif
	return data[(uint32)face_][pos_.y*size + pos_.x];
}
inline void*								TexProject::Texture::Cube::GetDataRGBA32F() const
{
	return new void*[6]
	{
		GetDataRGBA32F(Face::Right),
		GetDataRGBA32F(Face::Left),
		GetDataRGBA32F(Face::Top),
		GetDataRGBA32F(Face::Bottom),
		GetDataRGBA32F(Face::Front),
		GetDataRGBA32F(Face::Back)
	};
}
inline void*								TexProject::Texture::Cube::GetDataRGBA32F(Face face_) const
{
	auto data_ = new float32[size*size*4];
	for(uint32 i = 0; i < size*size; ++i)
	{
		data_[i*4+0] = data[(uint32)face_][i].x;
		data_[i*4+1] = data[(uint32)face_][i].y;
		data_[i*4+2] = data[(uint32)face_][i].z;
		data_[i*4+3] = data[(uint32)face_][i].w;
	}
	return data_;
}



#if __TEXPROJECT_WIN__

inline										TexProject::Windows::Texture::Texture(Window::Render* window):
	renderContext
	(	nullptr
		/*window->GetRenderContext()->GetType() == Window::RenderContext::Type::Default ?
		(Window::RenderContext::Default*)window->GetRenderContext()->GetData() :
		throw Exception()*/
	)
{
}
inline										TexProject::Windows::Texture::~Texture()
{
	Delete();
}
inline TexProject::Windows::Texture&		TexProject::Windows::Texture::operator = (const TexProject::Texture::D2& source)
{
	auto data_ = source.GetData();
	Create(source.GetSize(),data_);
	delete[] data_;
	return *this;
}
inline bool									TexProject::Windows::Texture::Create(uvec2 size_,vec4* data_)
{
	Delete();
	{
		size = size_;
		bitCount = 32;
		bytesPerLine = ((size.x * bitCount + 31)/32) * 4;
	}
	{
		infoHeader.biSize = sizeof(BITMAPINFOHEADER);
		infoHeader.biWidth = size.x;
		infoHeader.biHeight = size.y;
		infoHeader.biPlanes = 1;
		infoHeader.biBitCount = 32;
		infoHeader.biCompression = BI_RGB;
		infoHeader.biSizeImage = 0; //for BI_RGB
		infoHeader.biXPelsPerMeter = 0;
		infoHeader.biYPelsPerMeter = 0;
		infoHeader.biClrUsed = 0;
		infoHeader.biClrImportant = 0;
	}
	{
		textureData = new BYTE[bytesPerLine*size.y];
		for(uint32 x = 0; x < size.x; ++x)
		for(uint32 y = 0; y < size.y; ++y)
		{
			uint32 id1 = (y*bytesPerLine + x*4);
			uint32 id2 = y*size_.x + x;
			textureData[id1+0] = BYTE(data_[id2].z*255.0f);
			textureData[id1+1] = BYTE(data_[id2].y*255.0f);
			textureData[id1+2] = BYTE(data_[id2].x*255.0f);
			textureData[id1+3] = BYTE(data_[id2].w*255.0f);
		}
	}

	//bitmap = CreateBitmap(size.x,size.y,1,bitCount,textureData);

	return true;//bitmap != NULL;
}
inline void									TexProject::Windows::Texture::Delete()
{
	if(textureData)
	{
		delete[] textureData;
		textureData = nullptr;
	}
	if(bitmap)
	{
		//delete bitmap
		bitmap = NULL;
	}
}
inline TexProject::uvec2					TexProject::Windows::Texture::GetSize() const
{
	return size;
}
inline TexProject::Window::RenderContext::Default*				TexProject::Windows::Texture::GetRenderContext() const
{
	return renderContext;
}

#endif




#if __TEXPROJECT_OPENGL__

inline										TexProject::OpenGL::Texture::Texture(Window::Render* window):
	renderContext
	(
		window->GetRenderContext()->GetType() == Window::RenderContext::Type::OpenGL ?
		(Window::RenderContext::OpenGL*)window->GetRenderContext()->GetData() :
		throw Exception()
	)
{
}
inline										TexProject::OpenGL::Texture::Texture(Window::RenderContext::Basic* renderContext_):
	renderContext
	(
		renderContext_->GetType() == Window::RenderContext::Type::OpenGL ?
		(Window::RenderContext::OpenGL*)renderContext_->GetData() :
		throw Exception()
	)
{
}
inline										TexProject::OpenGL::Texture::~Texture()
{
	Delete();
}
inline TexProject::OpenGL::Texture&			TexProject::OpenGL::Texture::operator = (const TexProject::Texture::D1& source)
{
	{
		auto data_ = source.GetDataRGBA32F();
		Create
		(
			Type::D1,
			IFormat::RGBA32F,
			Format::RGBA,
			Component::Float32,
			Wrap::Repeat,
			Filter::Mipmap,
			uvec3(source.GetSize(),0,0),
			data_
		);
		delete[] data_;
	}
	return *this;
}
inline TexProject::OpenGL::Texture&			TexProject::OpenGL::Texture::operator = (const TexProject::Texture::D2& source)
{
	{
		auto data_ = source.GetDataRGBA32F();
		Create
		(
			Type::D2,
			IFormat::RGBA32F,
			Format::RGBA,
			Component::Float32,
			Wrap::Repeat,
			Filter::Mipmap,
			uvec3(source.GetSize(),0),
			data_
		);
		delete[] data_;
	}
	return *this;
}
inline TexProject::OpenGL::Texture&			TexProject::OpenGL::Texture::operator = (const TexProject::Texture::D3& source)
{
	{
		auto data_ = source.GetDataRGBA32F();
		Create
		(
			Type::D3,
			IFormat::RGBA32F,
			Format::RGBA,
			Component::Float32,
			Wrap::Repeat,
			Filter::Mipmap,
			source.GetSize(),
			data_
		);
		delete[] data_;
	}
	return *this;
}
inline TexProject::OpenGL::Texture&			TexProject::OpenGL::Texture::operator = (const TexProject::Texture::Cube& source)
{
	{
		auto data_ = source.GetDataRGBA32F();
		Create
		(
			Type::Cube,
			IFormat::RGBA32F,
			Format::RGBA,
			Component::Float32,
			Wrap::Clamp,
			Filter::Mipmap,
			uvec3(source.GetSize(),0,0),
			data_
		);
		delete[] data_;
	}
	return *this;
}
inline void									TexProject::OpenGL::Texture::Create(Type type_,InternalFormat internalFormat_,Format format_,Component component_,Wrap wrap_,Filter filter_,uvec3 size_,void* data_)
{
	Delete();
	{
		glActiveTexture(GL_TEXTURE0); renderContext->textureActiveSlot = 0;
	}
	{
		type = type_;
		glGenTextures(1,&texture);
		glBindTexture((GLenum)type,texture); renderContext->textureCurrent[0] = this;
	}
	{
		filter = filter_;
		glTexParameteri((GLenum)type,GL_TEXTURE_MIN_FILTER,(GLint)filter.min);
		glTexParameteri((GLenum)type,GL_TEXTURE_MAG_FILTER,(GLint)filter.mag);
	}
	{
		wrap = wrap_;
		border = vec4(0.0f);
		glTexParameteri((GLenum)type,GL_TEXTURE_WRAP_S,(GLint)wrap);
		glTexParameteri((GLenum)type,GL_TEXTURE_WRAP_T,(GLint)wrap);
		glTexParameteri((GLenum)type,GL_TEXTURE_WRAP_R,(GLint)wrap);
		static GLfloat borderColor_[4];
		borderColor_[0] = border.x;
		borderColor_[1] = border.y;
		borderColor_[2] = border.z;
		borderColor_[3] = border.w;
		glTexParameterfv((GLenum)type,GL_TEXTURE_BORDER_COLOR,borderColor_);
	}
	{
		internalFormat = internalFormat_;
		format = format_;
		component = component_;
		size = size_;
	}
	switch(type)
	{
		case Type::D1:
		{
			glTexImage1D((GLenum)type,0,(GLint)internalFormat,size.x,0,(GLenum)format,(GLenum)component,data_);
		}
		break;
		//case Type::D1Array: break;
		case Type::D2:
		{
			glTexImage2D((GLenum)type,0,(GLint)internalFormat,size.x,size.y,0,(GLenum)format,(GLenum)component,data_);
		}
		break;
		//case Type::D2Array: break;
		case Type::D3:
		{
			glTexImage3D((GLenum)type,0,(GLint)internalFormat,size.x,size.y,size.z,0,(GLenum)format,(GLenum)component,data_);
		}
		break;
		case Type::Cube:
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,(GLint)internalFormat,size.x,size.x,0,(GLenum)format,(GLenum)component,data_ ? ((void**)data_)[0] : NULL);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,(GLint)internalFormat,size.x,size.x,0,(GLenum)format,(GLenum)component,data_ ? ((void**)data_)[1] : NULL);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,(GLint)internalFormat,size.x,size.x,0,(GLenum)format,(GLenum)component,data_ ? ((void**)data_)[2] : NULL);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,(GLint)internalFormat,size.x,size.x,0,(GLenum)format,(GLenum)component,data_ ? ((void**)data_)[3] : NULL);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,(GLint)internalFormat,size.x,size.x,0,(GLenum)format,(GLenum)component,data_ ? ((void**)data_)[4] : NULL);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,(GLint)internalFormat,size.x,size.x,0,(GLenum)format,(GLenum)component,data_ ? ((void**)data_)[5] : NULL);
		}
		break;
		//case Type::CubeArray: break;
		default: throw Exception(); break;
	}
	{
		if(filter.min != Filter::Min::Off && filter.min != Filter::Min::Linear) glGenerateMipmap((GLenum)type);
	}

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Texture::Delete()
{
	Unuse();
	if(texture)
	{
		glDeleteTextures(1,&texture); //texture = 0;
	}

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Texture::Use(uint32 level)
{
#if __TEXPROJECT_DEBUG__
	if(texture)
	{
		if(int32(level) < renderContext->GetTextureMaxSlots())//GetSlotCount())
		{
			if(renderContext->textureActiveSlot != level)
			{
				renderContext->textureActiveSlot = level;
				glActiveTexture(GL_TEXTURE0 + level);
			}

			renderContext->textureCurrent[level] = this;
			glBindTexture((GLenum)type,texture);
		}
		else
		{
			throw Exception("");
		}
	}
	else
	{
		throw Exception();
	}
#else
	if(renderContext->textureActiveSlot != level)
	{
		renderContext->textureActiveSlot = level;
		glActiveTexture(GL_TEXTURE0 + level);
	}

	renderContext->textureCurrent[level] = this;
	glBindTexture((GLenum)type,texture);
#endif
}
inline void									TexProject::OpenGL::Texture::Unuse(uint32 level)
{
#if __TEXPROJECT_DEBUG__
	if(int32(level) < renderContext->GetTextureMaxSlots())
	{
		if(renderContext->textureCurrent[level] == this)
		{
			if(texture)
			{
				if(renderContext->textureActiveSlot != level)
				{
					renderContext->textureActiveSlot = level;
					glActiveTexture(GL_TEXTURE0 + level);
				}
				glBindTexture((GLenum)type,0);
			}
			renderContext->textureCurrent[level] = nullptr;
		}
	}
	else
	{
		throw Exception("");
	}
#else
	if(texture && renderContext->textureCurrent[level] == this)
	{
		if(renderContext->textureActiveSlot != level)
		{
			renderContext->textureActiveSlot = level;
			glActiveTexture(GL_TEXTURE0 + level);
		}

		glBindTexture((GLenum)type,0);
	}
	renderContext->textureCurrent[level] = nullptr;
#endif
}
inline void									TexProject::OpenGL::Texture::Unuse()
{
	for(int32 i = 0; i < renderContext->GetTextureMaxSlots(); ++i) Unuse(i);
}
inline TexProject::vec4*					TexProject::OpenGL::Texture::GetDataRGBA32F()
{
	switch(type)
	{
	case TexProject::OpenGL::Texture::Type::D1: break;
	case TexProject::OpenGL::Texture::Type::D1Array: break;
	case TexProject::OpenGL::Texture::Type::D2:
	{
		auto res = new vec4[size.x*size.y];

		uint32	pixelSize = 0;		// size in bytes
		uint32	pixelLength = 0;	// component count

		switch(component)
		{
		case TexProject::OpenGL::Texture::Component::UInt8: pixelSize = 1; break;
		case TexProject::OpenGL::Texture::Component::UInt16: pixelSize = 2; break;
		case TexProject::OpenGL::Texture::Component::UInt32: pixelSize = 4; break;
		case TexProject::OpenGL::Texture::Component::Int8: pixelSize = 1; break;
		case TexProject::OpenGL::Texture::Component::Int16: pixelSize = 2; break;
		case TexProject::OpenGL::Texture::Component::Int32: pixelSize = 4; break;
		case TexProject::OpenGL::Texture::Component::Float16: pixelSize = 2; break;
		case TexProject::OpenGL::Texture::Component::Float32: pixelSize = 4; break;
		default: break;
		}

		switch(format)
		{
		case TexProject::OpenGL::Texture::Format::R: pixelLength = 1; break;
		case TexProject::OpenGL::Texture::Format::G: pixelLength = 1; break;
		case TexProject::OpenGL::Texture::Format::B: pixelLength = 1; break;
		case TexProject::OpenGL::Texture::Format::A: pixelLength = 1; break;
		case TexProject::OpenGL::Texture::Format::L: pixelLength = 1; break;
		case TexProject::OpenGL::Texture::Format::RG: pixelLength = 2; break;
		case TexProject::OpenGL::Texture::Format::RGB: pixelLength = 3; break;
		case TexProject::OpenGL::Texture::Format::BGR: pixelLength = 3; break;
		case TexProject::OpenGL::Texture::Format::RGBA: pixelLength = 4; break;
		case TexProject::OpenGL::Texture::Format::BGRA: pixelLength = 4; break;
		case TexProject::OpenGL::Texture::Format::Depth: pixelLength = 1; break;
		default: break;
		}
		
		auto storage_ = malloc(size.x*size.y*pixelSize*pixelLength);

		Use(0);
		glGetTexImage((GLenum)type,0,(GLenum)format,(GLenum)component,storage_);
		Unuse(0);

		{
			ivec4	off(-1,-1,-1,-1);

			switch(format)
			{
				case Format::R:				{ off = ivec4(0,-1,-1,-1); break; }
				case Format::G:				{ off = ivec4(-1,0,-1,-1); break; }
				case Format::B:				{ off = ivec4(-1,-1,0,-1); break; }
				case Format::A:				{ off = ivec4(-1,-1,-1,0); break; }
				case Format::L:				{ off = ivec4(0,0,0,-1); break; }
				case Format::RG:			{ off = ivec4(0,1,-1,-1); break; }
				case Format::RGB:			{ off = ivec4(0,1,2,-1); break; }
				case Format::BGR:			{ off = ivec4(2,1,0,-1); break; }
				case Format::RGBA:			{ off = ivec4(0,1,2,3); break; }
				case Format::BGRA:			{ off = ivec4(2,1,0,3); break; }
				default:					throw TexProject::Exception();
			}

			for(uint32 x = 0; x < size.x; ++x)
			for(uint32 y = 0; y < size.y; ++y)
			{
				void* data_ = (int8*)storage_ + (y*size.x+x)*pixelSize*pixelLength;
				vec4 color(0.0f);
				switch(component)
				{
					case Component::Int8:
					{
						if(off.x>=0) color.x =  float32(float64(*((int8*)data_+off.x) - INT8_MIN) / INT8_MAX);
						if(off.y>=0) color.y =  float32(float64(*((int8*)data_+off.y) - INT8_MIN) / INT8_MAX);
						if(off.z>=0) color.z =  float32(float64(*((int8*)data_+off.z) - INT8_MIN) / INT8_MAX);
						if(off.w>=0) color.w =  float32(float64(*((int8*)data_+off.w) - INT8_MIN) / INT8_MAX);
						break;
					}
					case Component::UInt8:
					{
						if(off.x>=0) color.x =  float32(float64(*((uint8*)data_+off.x)) / UINT8_MAX);
						if(off.y>=0) color.y =  float32(float64(*((uint8*)data_+off.y)) / UINT8_MAX);
						if(off.z>=0) color.z =  float32(float64(*((uint8*)data_+off.z)) / UINT8_MAX);
						if(off.w>=0) color.w =  float32(float64(*((uint8*)data_+off.w)) / UINT8_MAX);
						break;
					}
					case Component::Int16:
					{
						if(off.x>=0) color.x =  float32(float64(*((int16*)data_+off.x) - INT16_MIN) / INT16_MAX);
						if(off.y>=0) color.y =  float32(float64(*((int16*)data_+off.y) - INT16_MIN) / INT16_MAX);
						if(off.z>=0) color.z =  float32(float64(*((int16*)data_+off.z) - INT16_MIN) / INT16_MAX);
						if(off.w>=0) color.w =  float32(float64(*((int16*)data_+off.w) - INT16_MIN) / INT16_MAX);
						break;
					}
					case Component::UInt16:
					{
						if(off.x>=0) color.x =  float32(float64(*((uint16*)data_+off.x)) / UINT16_MAX);
						if(off.y>=0) color.y =  float32(float64(*((uint16*)data_+off.y)) / UINT16_MAX);
						if(off.z>=0) color.z =  float32(float64(*((uint16*)data_+off.z)) / UINT16_MAX);
						if(off.w>=0) color.w =  float32(float64(*((uint16*)data_+off.w)) / UINT16_MAX);
						break;
					}
					case Component::Int32:
					{
						if(off.x>=0) color.x =  float32(float64(*((int32*)data_+off.x) - INT32_MIN) / INT32_MAX);
						if(off.y>=0) color.y =  float32(float64(*((int32*)data_+off.y) - INT32_MIN) / INT32_MAX);
						if(off.z>=0) color.z =  float32(float64(*((int32*)data_+off.z) - INT32_MIN) / INT32_MAX);
						if(off.w>=0) color.w =  float32(float64(*((int32*)data_+off.w) - INT32_MIN) / INT32_MAX);
						break;
					}
					case Component::UInt32:
					{
						if(off.x>=0) color.x =  float32(float64(*((uint32*)data_+off.x)) / UINT32_MAX);
						if(off.y>=0) color.y =  float32(float64(*((uint32*)data_+off.y)) / UINT32_MAX);
						if(off.z>=0) color.z =  float32(float64(*((uint32*)data_+off.z)) / UINT32_MAX);
						if(off.w>=0) color.w =  float32(float64(*((uint32*)data_+off.w)) / UINT32_MAX);
						break;
					}
					case Component::Float16:
					{
						if(off.x>=0) color.x =  float32(*((float16*)data_+off.x));
						if(off.y>=0) color.y =  float32(*((float16*)data_+off.y));
						if(off.z>=0) color.z =  float32(*((float16*)data_+off.z));
						if(off.w>=0) color.w =  float32(*((float16*)data_+off.w));
						break;
					}
					case Component::Float32:
					{
						if(off.x>=0) color.x =  float32(*((float32*)data_+off.x));
						if(off.y>=0) color.y =  float32(*((float32*)data_+off.y));
						if(off.z>=0) color.z =  float32(*((float32*)data_+off.z));
						if(off.w>=0) color.w =  float32(*((float32*)data_+off.w));
						break;
					}
					default:
					{
						throw TexProject::Exception();
					}
				}
				res[y*size.x + x] = color;
			}

			free(storage_);
		}

		return res;
	}
	break;
	case TexProject::OpenGL::Texture::Type::D2Array: break;
	case TexProject::OpenGL::Texture::Type::D3: break;
	case TexProject::OpenGL::Texture::Type::Cube: break;
	case TexProject::OpenGL::Texture::Type::CubeArray: break;
	default: break;
	}
	return nullptr;
}
inline TexProject::Window::RenderContext::OpenGL*				TexProject::OpenGL::Texture::GetRenderContext() const
{
	return renderContext;
}

#endif



















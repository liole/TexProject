#pragma once
#pragma region Include
#include <TexProject/TexProject_Header.h>

#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>


#if __TEXPROJECT_DEVIL__
#include <TexProject/TexProject_DevIL.h>
#endif

#pragma endregion

#pragma region Test
#pragma endregion

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

#if __TEXPROJECT_OPENGL1__
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
			D2&								operator = (OpenGL::Texture& source);
#endif
		};
		struct D3
		{
		protected:

			vec4*	data = nullptr;
			uvec3	size = uvec3(0);

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

#if __TEXPROJECT_OPENGL1__
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

#if __TEXPROJECT_OPENGL1__
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


#if __TEXPROJECT_DIRECT3D__
	namespace Direct3D
	{
		struct Texture:
			public ContextBind
		{
			friend Shader;
		public:
			enum struct Format
			{
				BGR8						= D3DFMT_R8G8B8,
				BGRA8						= D3DFMT_A8R8G8B8,
				RGBA32F						= D3DFMT_A32B32G32R32F
			};

		//protected:

			uvec2							size = uvec2(0);
			uint32							componentSize = 0;
			Format							format = Format::BGRA8;
			LPDIRECT3DTEXTURE9				texture = NULL;

		public:

			inline							Texture(Window::Render* window);
			inline							Texture(Window::RenderContext::Basic* renderContext_);
			inline							~Texture();

			inline Texture&					operator = (const TexProject::Texture::D2& source);

			inline void						Create(const uvec2& size_,Format format_,void* data_);
			inline void						Delete();

			inline void						Use(uint32 slot_ = 0);
		};
	}
#endif

}

#pragma region D1
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
#if __TEXPROJECT_OPENGL1__

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
#pragma endregion
#pragma region D2
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
#pragma endregion
#pragma region D3
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
#if __TEXPROJECT_OPENGL1__

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
#pragma endregion
#pragma region Cube
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
#pragma endregion
















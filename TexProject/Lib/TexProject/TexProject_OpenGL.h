#pragma once
#pragma region Include
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Geometry.h>
#include <TexProject/TexProject_Windows.h>
#include <TexProject/TexProject_Textures.h>


#include <OpenGL/include/gl/GL.h>
#include <OpenGL/include/gl/glext.h>
#include <OpenGL/include/gl/wglext.h>

#pragma comment (lib, "Lib/OpenGL/lib/OpenGL32.lib")
#pragma endregion

#if __TEXPROJECT_OPENGL__
#define _TEXPROJECT_OPENGL_GET_PROC(p,n) n = (p)wglGetProcAddress(#n); //return (n == nullptr) ? false : true;


namespace TexProject
{
	namespace OpenGL
	{
#pragma region Func
		// TextureFunc
		extern bool												initFuncTexture;
		extern PFNGLACTIVETEXTUREPROC							glActiveTexture;
		extern PFNGLGETTEXPARAMETERIIVPROC						glGetTexParameterIiv;
		extern PFNGLGENERATEMIPMAPPROC							glGenerateMipmap;
		extern PFNGLTEXIMAGE3DPROC								glTexImage3D;
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
		extern PFNGLBINDATTRIBLOCATIONPROC						glBindAttribLocation;
		extern PFNGLGETACTIVEATTRIBPROC							glGetActiveAttrib;
		extern PFNGLGETACTIVEUNIFORMPROC						glGetActiveUniform;
		extern PFNGLGETATTRIBLOCATIONPROC						glGetAttribLocation;
		extern PFNGLVERTEXATTRIBPOINTERPROC						glVertexAttribPointer;
		extern PFNGLENABLEVERTEXATTRIBARRAYPROC					glEnableVertexAttribArray;
		extern PFNGLDISABLEVERTEXATTRIBARRAYPROC				glDisableVertexAttribArray;
		// Buffer Func
		extern bool												initFuncBuffer;
		extern PFNGLGENVERTEXARRAYSPROC							glGenVertexArrays;
		extern PFNGLDELETEVERTEXARRAYSPROC						glDeleteVertexArrays;
		extern PFNGLBINDVERTEXARRAYPROC							glBindVertexArray;
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
		// Framebuffer Func
		extern bool												initFuncFramebuffer;
		extern PFNGLBINDFRAMEBUFFERPROC							glBindFramebuffer;
		extern PFNGLDELETEFRAMEBUFFERSPROC						glDeleteFramebuffers;
		extern PFNGLGENFRAMEBUFFERSPROC							glGenFramebuffers;
		extern PFNGLCHECKFRAMEBUFFERSTATUSPROC					glCheckFramebufferStatus;
		extern PFNGLFRAMEBUFFERTEXTUREPROC						glFramebufferTexture;
		extern PFNGLFRAMEBUFFERTEXTURE2DPROC					glFramebufferTexture2D;
		extern PFNGLDRAWBUFFERSPROC								glDrawBuffers;
#pragma endregion
		class Initer
		{
		public:
			Initer();
		};
		extern Initer											initer;
		extern PFNWGLCREATECONTEXTATTRIBSARBPROC				wglCreateContextAttribsARB;
		class RenderContext:
			public TexProject::RenderContext
		{
#pragma region Platform-dependent
#if __TEXPROJECT_WIN__
		protected:
			HGLRC											_wnd_RenderContextHandle;
#endif
#pragma endregion
#pragma region Basic
		public:
			RenderContext(Window* window_);
			virtual											~RenderContext();
			virtual Type									GetType() const override;
			virtual bool									Use() override;
			virtual void									Unuse() override;
			virtual void									Loop() override;
#pragma endregion
#pragma region Current Objects
			friend Buffer::Attribute;
			friend Buffer::Data;
			friend Buffer::Index;
			friend Buffer::Frame;
			friend Shader;
			friend Texture;
		protected:
			Buffer::Attribute*								currentBufferAttribute	= nullptr;
			Buffer::Data*									currentBufferData		= nullptr;
			Buffer::Index*									currentBufferIndex		= nullptr;
			Buffer::Frame*									currentBufferFrame		= nullptr;
			Shader*											currentShader			= nullptr;
			Texture**										currentTexture			= nullptr;
			int32											textureMaxSlots			= 0;
			uint32											textureSlot				= 0;
			int32											bufferFrameMaxColorAttachment = 0;

			inline void										SetCurrentBufferAttribute(Buffer::Attribute* buffer_);
			inline void										SetCurrentBufferData(Buffer::Data* buffer_);
			inline void										SetCurrentBufferIndex(Buffer::Index* buffer_);
			inline void										SetCurrentBufferFrame(Buffer::Frame* buffer_);
			inline void										SetCurrentShader(Shader* shader_);
			inline bool										SetCurrentTexture(int32 slot,Texture* texture);
			inline void										SetTextureSlot(uint32 slot);
		public:
			inline Buffer::Attribute*						GetCurrentBufferAttribute() const;
			inline Buffer::Data*							GetCurrentBufferData() const;
			inline Buffer::Index*							GetCurrentBufferIndex() const;
			inline Buffer::Frame*							GetCurrentBufferFrame() const;
			inline Shader*									GetCurrentShader() const;
			inline int32									GetTextureMaxSlots() const;
			inline uint32									GetTextureSlot() const;
			inline int32									GetBufferFrameMaxColorAttachment() const;
#pragma endregion
		};
		class ContextBind
		{
		protected:
			RenderContext*const				renderContext;
		public:
			inline							ContextBind(Window* window_);
			inline							ContextBind(::RenderContext* renderContext_);
			inline RenderContext*			GetRenderContext() const;
		};
		namespace Buffer
		{
			enum class Type
			{
				Static						= GL_STATIC_DRAW,
				Dynamic						= GL_DYNAMIC_DRAW,
				Stream						= GL_STREAM_DRAW
			};
			class TypeBind
			{
			protected:
				Type						type = Type::Static;
			public:
				inline Type					GetType() const;
			};
			class Attribute:
				public ContextBind
			{
			public:
				enum struct DataType
				{
					Int8					= GL_BYTE,
					UInt8					= GL_UNSIGNED_BYTE,
					Int16					= GL_SHORT,
					UInt16					= GL_UNSIGNED_SHORT,
					Int32					= GL_INT,
					UInt32					= GL_UNSIGNED_INT,
					Float16					= GL_HALF_FLOAT,
					Float32					= GL_FLOAT,
					Float64					= GL_DOUBLE
				};
				enum struct IndexType
				{
					Int8					= GL_BYTE,
					UInt8					= GL_UNSIGNED_BYTE,
					Int16					= GL_SHORT,
					UInt16					= GL_UNSIGNED_SHORT,
					Int32					= GL_INT,
					UInt32					= GL_UNSIGNED_INT
				};
				struct Param
				{
					string					name;
					DataType				componentType;
					uint32					componentCount;
					bool					normalization;
					uint32					stride;
					uint32					offset;
					inline					Param
					(
						const string&			name_,
						DataType				componentType_,
						uint32					componentCount_,
						bool					normalization_,
						uint32					stride_,
						uint32					offset_
					);
				};
			protected:
				GLuint						buffer = 0;
				Shader*						shader = nullptr;
				Buffer::Data*				dBuffer = nullptr;
				Buffer::Index*				iBuffer = nullptr;
				IndexType					indexType = IndexType::UInt32;
			public:
				inline						Attribute(Window* window_);
				inline						Attribute(::RenderContext* renderContext_);
				inline void					Create(std::list<Param> params,IndexType indexType_ = IndexType::UInt32);
				inline void					Delete();
				inline void					Use();
				inline void					Unuse();
				inline IndexType			GetIndexType() const;
			};
			class Data:
				public ContextBind,
				public TypeBind
			{
			protected:
				GLuint						buffer = 0;
				uint32						vertexCount = 0;
				uint32						vertexSize = 0;
			public:
				inline						Data(Window* window_);
				inline						Data(::RenderContext* renderContext_);
				inline						~Data();
				inline void					Create(uint32 vertexCount_,uint32 vertexSize_,void* data_ = nullptr,Type type_ = Type::Static);
				inline void					Delete();
				inline void					Use();
				inline void					Unuse();
				inline void*				Map();
				inline void					Unmap();
				inline uint32				GetVertexCount() const;
				inline uint32				GetVertexSize() const;
			};
			class Index:
				public ContextBind,
				public TypeBind
			{
			protected:
				GLuint						buffer = 0;
				uint32						indexCount = 0;
				uint32						indexSize = 0;
			public:
				inline						Index(Window* window_);
				inline						Index(::RenderContext* renderContext_);
				inline						~Index();
				inline void					Create(uint32 indexCount_,uint32 indexSize_,void* data_ = nullptr,Type type_ = Type::Static);
				inline void					Delete();
				inline void					Use();
				inline void					Unuse();
				inline void*				Map();
				inline void					Unmap();
				inline uint32				GetIndexCount() const;
				inline uint32				GetIndexSize() const;
			};
			class Frame:
				public ContextBind
			{
			protected:
				GLuint						buffer = 0;
				uvec2						size = uvec2(0);
				uint32						count = 0;
				GLenum*						buffers = nullptr;
				Texture**const				color;
				Texture*					depth = nullptr;
				Texture*					stencil = nullptr;
				uint32*const				own;
				inline uint32				GetOwnbitCount() const;
				inline uint32				GetColorIndex(uint32 i) const;
				inline uint32				GetColorBit(uint32 i) const;
				inline uint32				GetDepthIndex() const;
				inline uint32				GetDepthBit() const;
				inline uint32				GetStencilIndex() const;
				inline uint32				GetStencilBit() const;
			public:
				inline						Frame(Window* window_);
				inline						Frame(::RenderContext* renderContext_);
				inline						~Frame();
				inline void					Create(std::list<Texture*> color_,Texture* depth_,Texture* stencil_);
				inline void					Delete();
				inline void					Use();
				inline void					Unuse();
			};
		}
		class Shader:
			public ContextBind
		{
		protected:
			GLuint							prog = 0,vs = 0,tc = 0,te = 0,gs = 0,fs = 0;
		protected:
			static inline bool				LinkProgram(GLuint PRG);
			static inline bool				CompileShader(GLuint SHD);
			static inline bool				LoadFile(const string& fileName,bool binary,uint8 **buffer,uint32 *size);
		public:
			inline							Shader(Window* window);
			inline							Shader(::RenderContext* renderContext_);
			inline							~Shader();
			inline void						Create();
			inline bool						Load(const string& vs_);
			inline bool						Load(const string& vs_,const string& fs_);
			inline bool						Load(const string& vs_,const string& gs_,const string& fs_);
			inline bool						Load(const string& vs_,const string& tc_,const string& te_,const string& gs_,const string& fs_);
			inline bool						Load(const string& base_,const string& vs_,const string& tc_,const string& te_,const string& gs_,const string& fs_);
			inline void						Delete();
			inline void						Use();
			inline void						Unuse();
			inline GLint					PrepareAttribute(const string& name_);
			inline GLint					PrepareUniform(const string& uniformName);
			inline void						SetInt(GLint slot_,int32 val_);
			inline void						SetFloat(GLint slot_,float32 val_);
			inline void						SetVec2(GLint slot_,const vec2& val_);
			inline void						SetVec3(GLint slot_,const vec3& val_);
			inline void						SetVec4(GLint slot_,const vec4& val_);
			inline void						SetMat3(GLint slot_,const mat3& val_);
			inline void						SetMat4(GLint slot_,const mat4& val_);
			inline void						SetInt(const string& slot_,int32 val_);
			inline void						SetFloat(const string& slot_,float32 val_);
			inline void						SetVec2(const string& slot_,const vec2& val_);
			inline void						SetVec3(const string& slot_,const vec3& val_);
			inline void						SetVec4(const string& slot_,const vec4& val_);
			inline void						SetMat3(const string& slot_,const mat3& val_);
			inline void						SetMat4(const string& slot_,const mat4& val_);
		};
		class Texture:
			public ContextBind
		{
			friend Buffer::Frame;
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
				Depth32F						= GL_DEPTH_COMPONENT32F,

				Depth24Stencil8					= GL_DEPTH24_STENCIL8,
				Depth32FStencil8				= GL_DEPTH32F_STENCIL8
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
				Depth							= GL_DEPTH_COMPONENT,
				DepthStencil					= GL_DEPTH_STENCIL
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
				Float32							= GL_FLOAT,

				Uint24_8						= GL_UNSIGNED_INT_24_8
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

			struct Params
			{
				Type						type;
				InternalFormat				internalFormat;
				Format						format;
				Component					component;
				Wrap						wrap;
				Filter						filter;
			};

			typedef InternalFormat			IFormat;

		protected:
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

			inline Texture(Window* window);
			inline Texture(::RenderContext* renderContext_);
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
		};
		class Mesh:
			public ContextBind
		{
		public:
			enum class DrawMode: GLenum
			{
				Points						= GL_POINTS,
				Lines						= GL_LINES,
				LineStrip					= GL_LINE_STRIP,
				Triangles					= GL_TRIANGLES,
				TriangleStrip				= GL_TRIANGLE_STRIP,
				TriangleFan					= GL_TRIANGLE_FAN
			};
		protected:
			enum class Own
			{
				Attribute					= 0x01,
				Data						= 0x02,
				Index						= 0x04,
				Shader						= 0x08,
				All							= Attribute | Data | Index | Shader,
				None						= ~Attribute | ~Data | ~Index | ~Shader,
				Default						= None
			};
		public://protected:
			uint32							own = (uint32)Own::Default;
			DrawMode						drawMode = DrawMode::Triangles;
			Buffer::Attribute*				aBuffer = nullptr;
			Buffer::Data*					dBuffer = nullptr;
			Buffer::Index*					iBuffer = nullptr;
			Shader*							shader = nullptr;
		public:
			inline							Mesh(Window* window);
			inline							Mesh(::RenderContext* renderContext_);
			inline							~Mesh();
			inline void						Create(Geometry::Mesh* mesh_,Shader* shader_);
			inline void						Delete();
			inline void						Use();
			inline void						DrawIndex();
		};
		bool													ErrorTest();
	}
}
#endif


#pragma region OpenGL
#pragma region RenderContext
inline TexProject::OpenGL::Buffer::Attribute*					TexProject::OpenGL::RenderContext::GetCurrentBufferAttribute() const
{
	return currentBufferAttribute;
}
inline TexProject::OpenGL::Buffer::Data*						TexProject::OpenGL::RenderContext::GetCurrentBufferData() const
{
	return currentBufferData;
}
inline TexProject::OpenGL::Buffer::Index*						TexProject::OpenGL::RenderContext::GetCurrentBufferIndex() const
{
	return currentBufferIndex;
}
inline TexProject::OpenGL::Buffer::Frame*						TexProject::OpenGL::RenderContext::GetCurrentBufferFrame() const
{
	return currentBufferFrame;
}
inline TexProject::OpenGL::Shader*								TexProject::OpenGL::RenderContext::GetCurrentShader() const
{
	return currentShader;
}
inline TexProject::int32										TexProject::OpenGL::RenderContext::GetTextureMaxSlots() const
{
	return textureMaxSlots;
}
inline TexProject::uint32										TexProject::OpenGL::RenderContext::GetTextureSlot() const
{
	return textureSlot;
}
inline TexProject::int32										TexProject::OpenGL::RenderContext::GetBufferFrameMaxColorAttachment() const
{
	return bufferFrameMaxColorAttachment;
}
inline void														TexProject::OpenGL::RenderContext::SetCurrentBufferAttribute(Buffer::Attribute* buffer_)
{
	if(currentBufferAttribute && !buffer_)
	{
		glBindVertexArray(0);
	}
	currentBufferAttribute = buffer_;

	if(currentBufferData)
	{
		auto t = currentBufferData;
		currentBufferData = nullptr;
		t->Use();
	}

	if(currentBufferIndex)
	{
		auto t = currentBufferIndex;
		currentBufferIndex = nullptr;
		t->Use();
	}
}
inline void														TexProject::OpenGL::RenderContext::SetCurrentBufferData(Buffer::Data* buffer_)
{
	if(currentBufferData && !buffer_)
	{
		glBindBuffer(GL_ARRAY_BUFFER,0);
	}
	currentBufferData = buffer_;
}
inline void														TexProject::OpenGL::RenderContext::SetCurrentBufferIndex(Buffer::Index* buffer_)
{
	if(currentBufferIndex && !buffer_)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	}
	currentBufferIndex = buffer_;
}
inline void														TexProject::OpenGL::RenderContext::SetCurrentBufferFrame(Buffer::Frame* buffer_)
{
	if (currentBufferFrame && !buffer_)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	currentBufferFrame = buffer_;
}
inline void														TexProject::OpenGL::RenderContext::SetCurrentShader(Shader* shader_)
{
	if(currentShader && !shader_)
	{
		glUseProgram(0);
	}
	currentShader = shader_;
}
inline bool														TexProject::OpenGL::RenderContext::SetCurrentTexture(int32 slot,Texture* texture_)
{
	SetTextureSlot(uint32(slot));
	if(currentTexture && slot >= 0 && slot < textureMaxSlots)
	{
		if(currentTexture[slot] != texture_)
		{
			if(!texture_)
			{
				glBindTexture(GL_TEXTURE_1D,0);
				glBindTexture(GL_TEXTURE_2D,0);
				glBindTexture(GL_TEXTURE_3D,0);
				glBindTexture(GL_TEXTURE_CUBE_MAP,0);
			}
			currentTexture[slot] = texture_;
			return true;
		}
	}
	else throw Exception("Failed to set current texture");
	return false;
}
inline void														TexProject::OpenGL::RenderContext::SetTextureSlot(uint32 slot)
{
	if(slot < uint32(textureMaxSlots))
	{
		if(textureSlot != slot)
		{
			textureSlot = slot;
			glActiveTexture(GL_TEXTURE0 + slot);
		}
	}
	else throw Exception("Failed to set texture slot");
}
#pragma endregion
#pragma region ContextBind
inline															TexProject::OpenGL::ContextBind::ContextBind(Window* window_):
	renderContext
	(
		window_->GetRenderContext()->GetType() == RenderContext::Type::OpenGL ?
		(OpenGL::RenderContext*)window_->GetRenderContext() :
		throw Exception()
	)
{
}
inline															TexProject::OpenGL::ContextBind::ContextBind(::RenderContext* renderContext_):
	renderContext
	(
		renderContext_->GetType() == RenderContext::Type::OpenGL ?
		(RenderContext*)renderContext_ :
		throw Exception()
	)
{
}
inline TexProject::OpenGL::RenderContext*						TexProject::OpenGL::ContextBind::GetRenderContext() const
{
	return renderContext;
}
#pragma endregion
#pragma region Buffer
#pragma region TypeBind
inline TexProject::OpenGL::Buffer::Type							TexProject::OpenGL::Buffer::TypeBind::GetType() const
{
	return type;
}
#pragma endregion
#pragma region Attribute
#pragma region Param
inline															TexProject::OpenGL::Buffer::Attribute::Param::Param
(
	const string&			name_,
	DataType				componentType_,
	uint32					componentCount_,
	bool					normalization_,
	uint32					stride_,
	uint32					offset_
):
	name(name_),
	componentType(componentType_),
	componentCount(componentCount_),
	normalization(normalization_),
	stride(stride_),
	offset(offset_)
{
}
#pragma endregion
inline															TexProject::OpenGL::Buffer::Attribute::Attribute(Window* window_):
	ContextBind(window_)
{
}
inline															TexProject::OpenGL::Buffer::Attribute::Attribute(::RenderContext* renderContext_):
	ContextBind(renderContext_)
{
}
inline void														TexProject::OpenGL::Buffer::Attribute::Create(std::list<Param> params,IndexType indexType_)
{
	glGenVertexArrays(1,&buffer);
	glBindVertexArray(buffer); renderContext->SetCurrentBufferAttribute(this);

#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif

	if(auto dBuffer_ = renderContext->GetCurrentBufferData()) dBuffer = dBuffer_;
	else throw Exception("No data buffer.");

	if(auto iBuffer_ = renderContext->GetCurrentBufferIndex())
	{
		iBuffer = iBuffer_;
		indexType = indexType_;
	}

	if(auto shader_ = renderContext->GetCurrentShader()) shader = shader_;
	else throw Exception("No shader.");

	shader->Use();

	auto att = new GLuint[params.size()];

	uint32 i = 0;
	for(auto param: params)
	{
		att[i] = shader->PrepareAttribute(param.name);
		if(att[i] != -1)
		{
			glVertexAttribPointer(att[i],param.componentCount,(GLenum)param.componentType,param.normalization,param.stride,(const void*)param.offset);
			glEnableVertexAttribArray(att[i]);
		}
		++i;
	}

	delete[] att;

#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Attribute::Delete()
{
	Unuse();
	glDeleteVertexArrays(1,&buffer);
#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
	buffer = 0;
	dBuffer = nullptr;
	iBuffer = nullptr;
	shader = nullptr;
}
inline void														TexProject::OpenGL::Buffer::Attribute::Use()
{
	if(buffer)
	{
		if(renderContext->GetCurrentBufferAttribute() != this)
		{
			glBindVertexArray(buffer);
#if __TEXPROJECT_DEBUG__
			ErrorTest();
#endif
			renderContext->SetCurrentBufferAttribute(this);
		}
	} else throw Exception("Try to use uninitialized attribute buffer");
}
inline void														TexProject::OpenGL::Buffer::Attribute::Unuse()
{
	if(renderContext->GetCurrentBufferAttribute() == this)
	{
		if(buffer)
		{
			renderContext->SetCurrentBufferAttribute(nullptr);
		}
		else throw Exception("Uninitialized attribute buffer previously be used and now try to unuse");
	}
}
inline TexProject::OpenGL::Buffer::Attribute::IndexType			TexProject::OpenGL::Buffer::Attribute::GetIndexType() const
{
	return indexType;
}
#pragma endregion
#pragma region Data
inline															TexProject::OpenGL::Buffer::Data::Data(Window* window_):
	ContextBind(window_)
{
}
inline															TexProject::OpenGL::Buffer::Data::Data(::RenderContext* renderContext_):
	ContextBind(renderContext_)
{
}
inline															TexProject::OpenGL::Buffer::Data::~Data()
{
	Delete();
}
inline void														TexProject::OpenGL::Buffer::Data::Create(uint32 vertexCount_,uint32 vertexSize_,void* data_,Type type_)
{
	Delete();

	vertexCount = vertexCount_;
	vertexSize = vertexSize_;
	type = type_;

	glGenBuffers(1,&buffer);
	glBindBuffer(GL_ARRAY_BUFFER,buffer); renderContext->SetCurrentBufferData(this);
	glBufferData(GL_ARRAY_BUFFER,vertexCount*vertexSize,data_,(GLenum)type);

#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Data::Delete()
{
	if(buffer)
	{
		Unuse();
		glDeleteBuffers(1,&buffer);
#if __TEXPROJECT_DEBUG__
		ErrorTest();
#endif
		buffer = 0;
		vertexCount = 0;
		vertexSize = 0;
	}
}
inline void														TexProject::OpenGL::Buffer::Data::Use()
{
	if(buffer)
	{
		if(renderContext->GetCurrentBufferData() != this)
		{
			glBindBuffer(GL_ARRAY_BUFFER,buffer);
#if __TEXPROJECT_DEBUG__
			ErrorTest();
#endif
			renderContext->SetCurrentBufferData(this);
		}
	}
	else
	{
		throw Exception("Try to use uninitialized data buffer");
	}
}
inline void														TexProject::OpenGL::Buffer::Data::Unuse()
{
	if(renderContext->GetCurrentBufferData() == this)
	{
		if(buffer)
		{
			renderContext->SetCurrentBufferData(nullptr);
		}
		else
		{
			throw Exception("Uninitialized data buffer previously be used and now try to unuse");
		}
	}
}
inline void*													TexProject::OpenGL::Buffer::Data::Map()
{
#if __TEXPROJECT_DEBUG__
	if(renderContext->currentBufferData != this) throw Exception("Try to map unused data buffer.");
	if(!buffer) throw Exception("Try to map uninitialized data buffer.");

	auto t = glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);

	ErrorTest();

	return t;
#else
	return glMapBuffer(GL_ARRAY_BUFFER,GL_READ_WRITE);
#endif
}
inline void														TexProject::OpenGL::Buffer::Data::Unmap()
{
#if __TEXPROJECT_DEBUG__
	if(renderContext->currentBufferData != this) throw Exception("Try to unmap unused data buffer.");
	if(!buffer) throw Exception("Try to unmap uninitialized data buffer.");
#endif
	glUnmapBuffer(GL_ARRAY_BUFFER);
#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Data::GetVertexCount() const
{
	return vertexCount;
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Data::GetVertexSize() const
{
	return vertexSize;
}
#pragma endregion
#pragma region Index
inline															TexProject::OpenGL::Buffer::Index::Index(Window* window_):
	ContextBind(window_)
{
}
inline															TexProject::OpenGL::Buffer::Index::Index(::RenderContext* renderContext_):
	ContextBind(renderContext_)
{
}
inline															TexProject::OpenGL::Buffer::Index::~Index()
{
	Delete();
}
inline void														TexProject::OpenGL::Buffer::Index::Create(uint32 indexCount_,uint32 indexSize_,void* data_,Type type_)
{
	Delete();

	indexCount = indexCount_;
	indexSize = indexSize_;
	type = type_;

	glGenBuffers(1,&buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer); renderContext->SetCurrentBufferIndex(this);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,indexCount*indexSize,data_,(GLenum)type);

#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Index::Delete()
{
	Unuse();
	glDeleteBuffers(1,&buffer);
#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
	buffer = 0;
	indexCount = 0;
	indexSize = 0;
}
inline void														TexProject::OpenGL::Buffer::Index::Use()
{
	if(buffer)
	{
		if(renderContext->GetCurrentBufferIndex() != this)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer);
#if __TEXPROJECT_DEBUG__
			ErrorTest();
#endif
			renderContext->SetCurrentBufferIndex(this);
		}
	}
	else
	{
		throw Exception("Try to use uninitialized index buffer");
	}
}
inline void														TexProject::OpenGL::Buffer::Index::Unuse()
{
	if(renderContext->GetCurrentBufferIndex() == this)
	{
		if(buffer)
		{
			renderContext->SetCurrentBufferIndex(nullptr);
		}
		else
		{
			throw Exception("Uninitialized index buffer previously be used and now try to unuse");
		}
	}
}
inline void*													TexProject::OpenGL::Buffer::Index::Map()
{
#if __TEXPROJECT_DEBUG__
	if(renderContext->currentBufferIndex != this) throw Exception("Try to map unused index buffer.");
	if(!buffer) throw Exception("Try to map uninitialized index buffer.");

	auto t = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_READ_WRITE);

	ErrorTest();

	return t;
#else
	return glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_READ_WRITE);
#endif
}
inline void														TexProject::OpenGL::Buffer::Index::Unmap()
{
#if __TEXPROJECT_DEBUG__
	if(renderContext->currentBufferIndex != this) throw Exception("Try to unmap unused index buffer.");
	if(!buffer) throw Exception("Try to unmap uninitialized index buffer.");
#endif
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
#ifdef __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Index::GetIndexCount() const
{
	return indexCount;
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Index::GetIndexSize() const
{
	return indexSize;
}
#pragma endregion
#pragma region Frame
inline TexProject::uint32										TexProject::OpenGL::Buffer::Frame::GetOwnbitCount() const
{
	return (renderContext->GetBufferFrameMaxColorAttachment() + 2 + 31) / 32;
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Frame::GetColorIndex(uint32 i) const
{
	return (i + 2) / GetOwnbitCount();
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Frame::GetColorBit(uint32 i) const
{
	return (i + 2) % (GetOwnbitCount() * 32);
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Frame::GetDepthIndex() const
{
	return 0;
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Frame::GetDepthBit() const
{
	return 0;
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Frame::GetStencilIndex() const
{
	return 0;
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Frame::GetStencilBit() const
{
	return 1;
}
inline															TexProject::OpenGL::Buffer::Frame::Frame(Window* window_):
	ContextBind(window_),
	color(new Texture*[renderContext->GetBufferFrameMaxColorAttachment()]),
	own(new uint32[GetOwnbitCount()])
{
	for(int32 i = 0; i < renderContext->GetBufferFrameMaxColorAttachment(); ++i) color[i] = nullptr;
}
inline															TexProject::OpenGL::Buffer::Frame::Frame(::RenderContext* renderContext_):
	ContextBind(renderContext_),
	color(new Texture*[renderContext->GetBufferFrameMaxColorAttachment()]),
	own(new uint32[GetOwnbitCount()])
{
	for(int32 i = 0; i < renderContext->GetBufferFrameMaxColorAttachment(); ++i) color[i] = nullptr;
	for(uint32 i = 0; i < GetOwnbitCount(); ++i)
	{
		own[i] = 0;
	}
}
inline															TexProject::OpenGL::Buffer::Frame::~Frame()
{
	Delete();
}
inline void														TexProject::OpenGL::Buffer::Frame::Create(std::list<Texture*> color_, Texture* depth_, Texture* stencil_)
{
	Delete();

	if ((int32)color_.size() > renderContext->GetBufferFrameMaxColorAttachment())
	{
		throw Exception("Too many color textures while creating frame buffer");
	}

	glGenFramebuffers(1, &buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer); renderContext->SetCurrentBufferFrame(this);

	size = (*color_.begin())->GetSize().xy();
	count = color_.size();
	buffers = new GLenum[count];

	uint32 i = 0;
	for (auto tex: color_)
	{
		color[i] = tex;
		own[GetColorIndex(i)] &= ~((uint32)1 << GetColorBit(i));
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, tex->texture, 0);
		buffers[i] = GL_COLOR_ATTACHMENT0 + i;
		++i;
	}

	if (depth_)
	{
		depth = depth_;
		own[GetDepthIndex()] &= ~((uint32)1 << GetDepthBit());
		if(depth_->format == Texture::Format::DepthStencil)
		{
			glFramebufferTexture(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,depth_->texture,0);
		}
		else
		{
			glFramebufferTexture(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,depth_->texture,0);
		}
	}

	if (stencil_ && (!depth_ || depth_->format != Texture::Format::DepthStencil))
	{
		stencil = stencil_;
		own[GetStencilIndex()] &= ~((uint32)1 << GetStencilBit());
		glFramebufferTexture(GL_FRAMEBUFFER,GL_STENCIL_ATTACHMENT,stencil_->texture,0);
	}
}
inline void														TexProject::OpenGL::Buffer::Frame::Delete()
{
	Unuse();

	if(buffer)
	{
		glDeleteFramebuffers(1,&buffer);
		buffer = 0;
	}

	if(depth)
	{
		if((own[GetDepthIndex()] & ((uint32)1 << GetDepthBit())) > 0)
		{
			delete depth;
			own[GetDepthIndex()] &= ~((uint32)1 << GetDepthBit());
		}
		depth = nullptr;
	}
	if(stencil)
	{
		if((own[GetStencilIndex()] & ((uint32)1 << GetStencilBit())) > 0)
		{
			delete stencil;
			own[GetStencilIndex()] &= ~((uint32)1 << GetStencilBit());
		}
		stencil = nullptr;
	}

	for(int32 i = 0; i < renderContext->GetBufferFrameMaxColorAttachment(); ++i)
	{
		if(color[i])
		{
			if((own[GetColorIndex(i)] & ((uint32)1 << GetColorBit(i))) > 0)
			{
				delete color[i];
				own[GetColorIndex(i)] &= ~((uint32)1 << GetColorBit(i));
			}
			color[i] = nullptr;
		}
	}

	if(buffers) { delete[] buffers; buffers = nullptr; }
	count = 0;

#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
	for(uint32 i = 0; i < GetOwnbitCount(); ++i)
	{
		own[i] = 0;
	}
}
inline void														TexProject::OpenGL::Buffer::Frame::Use()
{
	if (buffer)
	{
		if (renderContext->GetCurrentBufferFrame() != this)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, buffer);
			glDrawBuffers(count,buffers);
#if __TEXPROJECT_DEBUG__
			ErrorTest();
#endif
			renderContext->SetCurrentBufferFrame(this);
		}
		glViewport(0,0,size.x,size.y);
	}
	else
	{
		throw Exception("Try to use uninitialized frame buffer");
	}

}
inline void														TexProject::OpenGL::Buffer::Frame::Unuse()
{
	if (renderContext->GetCurrentBufferFrame() == this)
	{
		if (buffer)
		{
			renderContext->SetCurrentBufferFrame(nullptr);
		}
		else
		{
			throw Exception("Uninitialized frame buffer previously be used and now try to unuse");
		}
	}
}
#pragma endregion
#pragma endregion
#pragma region Shader
inline TexProject::OpenGL::Shader::Shader(Window* window):
	ContextBind(window)
{
}
inline TexProject::OpenGL::Shader::Shader(::RenderContext* renderContext_):
	ContextBind(renderContext_)
{
}
inline TexProject::OpenGL::Shader::~Shader()
{
	Delete();
}
inline void									TexProject::OpenGL::Shader::Create()
{
	Delete();

	prog	= glCreateProgram();
	vs		= glCreateShader(GL_VERTEX_SHADER);
	fs		= glCreateShader(GL_FRAGMENT_SHADER);

	gs		= glCreateShader(GL_GEOMETRY_SHADER);

	tc		= glCreateShader(GL_TESS_CONTROL_SHADER);
	te		= glCreateShader(GL_TESS_EVALUATION_SHADER);

#ifdef __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline bool									TexProject::OpenGL::Shader::Load(const string& vs_)
{
	return Load(vs_,"","","","");
}
inline bool									TexProject::OpenGL::Shader::Load(const string& vs_,const string& fs_)
{
	return Load(vs_,"","","",fs_);
}
inline bool									TexProject::OpenGL::Shader::Load(const string& vs_,const string& gs_,const string& fs_)
{
	return Load(vs_,"","",gs_,fs_);
}
inline bool									TexProject::OpenGL::Shader::Load(const string& vs_,const string& tc_,const string& te_,const string& gs_,const string& fs_)
{
	Delete();

#ifdef __TEXPROJECT_DEBUG__
	//OpenGL::ErrorTest();
#endif

	Create();

	uint8		*shaderSource;
	uint32		sourceLength;

	//Load Vertex Shader
	if(vs_.length() > 0)
	{
		if(!LoadFile(vs_,true,&shaderSource,&sourceLength)) { Message("Can't Load Vertex Shader.\npath: ''"+vs_+"''"); return false; }
		glShaderSource(vs,1,(const GLchar**)&shaderSource,(const GLint*)&sourceLength);
		if(!CompileShader(vs)) return false;
		delete[] shaderSource;
	}

	//Load Tesselation Control Shader
	if(tc_.length() > 0)
	{
		if(!LoadFile(tc_,true,&shaderSource,&sourceLength)) { Message("Can't Load Tesselation Control Shader.\npath: ''"+tc_+"''"); return false; }
		glShaderSource(tc,1,(const GLchar**)&shaderSource,(const GLint*)&sourceLength);
		if(!CompileShader(tc)) return false;
		delete[] shaderSource;
	}

	//Load Tesselation Evaluated Shader
	if(te_.length() > 0)
	{
		if(!LoadFile(te_,true,&shaderSource,&sourceLength)) { Message("Can't Load Tesselation Evaluated Shader.\npath: ''"+te_+"''"); return false; }
		glShaderSource(te,1,(const GLchar**)&shaderSource,(const GLint*)&sourceLength);
		if(!CompileShader(te)) return false;
		delete[] shaderSource;
	}

	//Load Geometry Shader
	if(gs_.length() > 0)
	{
		if(!LoadFile(gs_,true,&shaderSource,&sourceLength)) { Message("Can't Load Geometry Shader.\npath: ''"+gs_+"''"); return false; }
		glShaderSource(gs,1,(const GLchar**)&shaderSource,(const GLint*)&sourceLength);
		if(!CompileShader(gs)) return false;
		delete[] shaderSource;
	}

	//Load Pixel Shader
	if(fs_.length() > 0)
	{
		if(!LoadFile(fs_,true,&shaderSource,&sourceLength)) { Message("Can't Load Pixel Shader.\npath: ''"+fs_+"''"); return false; }
		glShaderSource(fs,1,(const GLchar**)&shaderSource,(const GLint*)&sourceLength);
		if(!CompileShader(fs)) return false;
		delete[] shaderSource;
	}

	if(vs_.length() > 0) glAttachShader(prog,vs);
	if(tc_.length() > 0) glAttachShader(prog,tc);
	if(te_.length() > 0) glAttachShader(prog,te);
	if(gs_.length() > 0) glAttachShader(prog,gs);
	if(fs_.length() > 0) glAttachShader(prog,fs);

#ifdef __TEXPROJECT_DEBUG__
	//OpenGL::ErrorTest();
#endif

	return LinkProgram(prog);
}
inline bool									TexProject::OpenGL::Shader::Load(const string& base_,const string& vs_,const string& tc_,const string& te_,const string& gs_,const string& fs_)
{
	return Load
	(
		vs_.length() > 0 ? base_+vs_ : "",
		tc_.length() > 0 ? base_+tc_ : "",
		te_.length() > 0 ? base_+te_ : "",
		gs_.length() > 0 ? base_+gs_ : "",
		fs_.length() > 0 ? base_+fs_ : ""
	);
}
inline void									TexProject::OpenGL::Shader::Delete()
{
	Unuse();

	if(prog) { glDeleteProgram(prog); prog = 0; }
	if(vs) { glDeleteShader(vs); vs = 0; }
	if(tc) { glDeleteShader(tc); tc = 0; }
	if(te) { glDeleteShader(te); te = 0; }
	if(gs) { glDeleteShader(gs); gs = 0; }
	if(fs) { glDeleteShader(fs); fs = 0; }

#ifdef __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::Use()
{
	if(renderContext->currentShader != this)
	{
		renderContext->SetCurrentShader(this);
	}
	if(prog) glUseProgram(prog);
	else throw Exception("Use uninitialized buffer.");
#ifdef __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::Unuse()
{
	if(renderContext->currentShader == this)
	{
		renderContext->SetCurrentShader(nullptr);
	}
}
inline bool									TexProject::OpenGL::Shader::LinkProgram(GLuint PRG)
{
#ifdef __TEXPROJECT_DEBUG__
	ErrorTest();
#endif

	glLinkProgram(PRG);

#ifdef __TEXPROJECT_DEBUG__
	{
		ErrorTest();

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

		ErrorTest();
	}
#endif

	return true;
}
inline bool									TexProject::OpenGL::Shader::CompileShader(GLuint SHD)
{
#ifdef __TEXPROJECT_DEBUG__
	ErrorTest();
#endif

	glCompileShader(SHD);

#ifdef __TEXPROJECT_DEBUG__
	{
		ErrorTest();

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

		ErrorTest();
	}
#endif	

	return true;
}
inline bool									TexProject::OpenGL::Shader::LoadFile(const string& fileName,bool binary,uint8 **buffer,uint32 *size)
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
inline GLint								TexProject::OpenGL::Shader::PrepareAttribute(const string& name_)
{
#if __TEXPROJECT_DEBUG__
	if(renderContext->GetCurrentShader() != this) throw Exception("Shader is not in use.");
	if(!prog) throw Exception("Uninit shader.");
#endif
	return glGetAttribLocation(prog,name_.c_str());
}
inline GLint								TexProject::OpenGL::Shader::PrepareUniform(const string& uniformName)
{
#ifdef __TEXPROJECT_DEBUG__
	ErrorTest();

	if(prog && renderContext->GetCurrentShader() == this) return glGetUniformLocation(prog,uniformName.c_str());
	throw Exception("Failed To Get Uniform.");
#else
	return glGetUniformLocation(prog,uniformName.c_str());
#endif
}
inline void									TexProject::OpenGL::Shader::SetInt(GLint slot_,int32 val_)
{
	glUniform1i(slot_, val_);
#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetFloat(GLint slot_,float32 val_)
{
	glUniform1f(slot_, val_);
#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetVec2(GLint slot_,const vec2& val_)
{
	glUniform2f(slot_, val_.x, val_.y);
#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetVec3(GLint slot_,const vec3& val_)
{
	glUniform3f(slot_,val_.x,val_.y,val_.z);
#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetVec4(GLint slot_,const vec4& val_)
{
	glUniform4f(slot_, val_.x, val_.y, val_.z, val_.w);
#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetMat3(GLint slot_,const mat3& val_)
{
	glUniformMatrix3fv(slot_,1,GL_TRUE,val_.val);
#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetMat4(GLint slot_,const mat4& val_)
{
	glUniformMatrix4fv(slot_,1,GL_TRUE,val_.val);
#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetInt(const string& slot_,int32 val_)
{
	Use();
	auto uni = PrepareUniform(slot_);
	if(uni != -1) SetInt(uni,val_);
}
inline void									TexProject::OpenGL::Shader::SetFloat(const string& slot_,float32 val_)
{
	Use();
	auto uni = PrepareUniform(slot_);
	if(uni != -1) SetFloat(uni,val_);
}
inline void									TexProject::OpenGL::Shader::SetVec2(const string& slot_,const vec2& val_)
{
	Use();
	SetVec2(PrepareUniform(slot_),val_);
}
inline void									TexProject::OpenGL::Shader::SetVec3(const string& slot_,const vec3& val_)
{
	Use();
	SetVec3(PrepareUniform(slot_),val_);
}
inline void									TexProject::OpenGL::Shader::SetVec4(const string& slot_,const vec4& val_)
{
	Use();
	SetVec4(PrepareUniform(slot_),val_);
}
inline void									TexProject::OpenGL::Shader::SetMat3(const string& slot_,const mat3& val_)
{
	Use();
	SetMat3(PrepareUniform(slot_),val_);
}
inline void									TexProject::OpenGL::Shader::SetMat4(const string& slot_,const mat4& val_)
{
	Use();
	SetMat4(PrepareUniform(slot_),val_);
}
#pragma endregion
#pragma region Texture
inline										TexProject::OpenGL::Texture::Texture(Window* window):
	ContextBind(window)
{
}
inline										TexProject::OpenGL::Texture::Texture(::RenderContext* renderContext_):
	ContextBind(renderContext_)
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
		type = type_;
		glGenTextures(1,&texture);
		renderContext->SetCurrentTexture(0,this);
		glBindTexture((GLenum)type,texture);
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
	ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Texture::Delete()
{
	Unuse();

#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif

	if(texture)
	{
		glDeleteTextures(1,&texture); texture = 0;
	}

#if __TEXPROJECT_DEBUG__
	ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Texture::Use(uint32 level)
{
	if(texture)
	{
		if(renderContext->SetCurrentTexture((int32)level,this))
		{
			glBindTexture((GLenum)type,texture);
		}
	}
	else throw Exception();
}
inline void									TexProject::OpenGL::Texture::Unuse(uint32 level)
{
	if(texture)
	{
		renderContext->SetCurrentTexture((int32)level,nullptr);
	}
}
inline void									TexProject::OpenGL::Texture::Unuse()
{
	if(texture)
	{
		for(int32 i = 0; i < renderContext->GetTextureMaxSlots(); ++i) Unuse(i);
	}
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

#pragma endregion
#pragma region Mesh
inline										TexProject::OpenGL::Mesh::Mesh(Window* window):
	ContextBind(window)
{
}
inline										TexProject::OpenGL::Mesh::Mesh(::RenderContext* renderContext_):
	ContextBind(renderContext_)
{
}
inline										TexProject::OpenGL::Mesh::~Mesh()
{
	Delete();
}
inline void									TexProject::OpenGL::Mesh::Create(Geometry::Mesh* mesh_,Shader* shader_)
{
	Delete();

	own |= (uint32)Own::Attribute;
	own |= (uint32)Own::Data;
	own |= (uint32)Own::Index;
	own &= ~(uint32)Own::Shader;

	shader = shader_;
	aBuffer = new Buffer::Attribute(shader->GetRenderContext());
	dBuffer = new Buffer::Data(shader->GetRenderContext());
	iBuffer = new Buffer::Index(shader->GetRenderContext());

	auto vArr = mesh_->GetVertexArray();
	auto iArr = mesh_->GetIndexArray();

	dBuffer->Create(mesh_->GetVertexCount(),mesh_->GetVertexSize(),vArr);

	iBuffer->Create(mesh_->GetIndexCount(),mesh_->GetIndexSize(),iArr);

	Buffer::Attribute::IndexType iType;
	switch(iBuffer->GetIndexSize())
	{
	case 1: iType = Buffer::Attribute::IndexType::UInt8; break;
	case 2: iType = Buffer::Attribute::IndexType::UInt16; break;
	case 4: iType = Buffer::Attribute::IndexType::UInt32; break;
	default: throw Exception("Unknown index size");
	}

	shader->Use();
	aBuffer->Create
	(
		{
			Buffer::Attribute::Param("vPos",Buffer::Attribute::DataType::Float32,3,false,dBuffer->GetVertexSize(),0),
			Buffer::Attribute::Param("vTan",Buffer::Attribute::DataType::Float32,3,false,dBuffer->GetVertexSize(),12),
			Buffer::Attribute::Param("vBin",Buffer::Attribute::DataType::Float32,3,false,dBuffer->GetVertexSize(),24),
			Buffer::Attribute::Param("vNor",Buffer::Attribute::DataType::Float32,3,false,dBuffer->GetVertexSize(),36),
			Buffer::Attribute::Param("vTex",Buffer::Attribute::DataType::Float32,2,false,dBuffer->GetVertexSize(),48)
		},
		iType
	);

	delete[] vArr;
	delete[] iArr;
}
inline void									TexProject::OpenGL::Mesh::Delete()
{
	if(aBuffer)
	{
		if((own & (uint32)Own::Attribute) > 0)
		{
			delete aBuffer;
			own &= ~(uint32)Own::Attribute;
		}
		aBuffer = nullptr;
	}
	if(dBuffer)
	{
		if((own & (uint32)Own::Data) > 0)
		{
			delete dBuffer;
			own &= ~(uint32)Own::Data;
		}
		dBuffer = nullptr;
	}
	if(iBuffer)
	{
		if((own & (uint32)Own::Index) > 0)
		{
			delete iBuffer;
			own &= ~(uint32)Own::Index;
		}
		iBuffer = nullptr;
	}
	if(shader)
	{
		if((own & (uint32)Own::Shader) > 0)
		{
			delete shader;
			own &= ~(uint32)Own::Shader;
		}
		shader = nullptr;
	}
}
inline void									TexProject::OpenGL::Mesh::Use()
{
	aBuffer->Use();
	if(dBuffer) dBuffer->Use();
	if(iBuffer) iBuffer->Use();
}
inline void									TexProject::OpenGL::Mesh::DrawIndex()
{
	if(shader)
	{
		shader->Use();

		aBuffer->Use();
		dBuffer->Use();
		iBuffer->Use();

		glDrawElements((GLenum)drawMode,iBuffer->GetIndexCount(),(GLenum)aBuffer->GetIndexType(),0);
	}
}
#pragma endregion
#pragma endregion


#pragma region Test
#pragma endregion
















#pragma once
#include <TexProject/TexProject_Header.h>

#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Geometry.h>
#include <TexProject/TexProject_OpenGL.h>
#include <TexProject/TexProject_Direct3D.h>
#include <TexProject/TexProject_Shaders.h>


namespace TexProject
{
#if __TEXPROJECT_OPENGL__
	namespace OpenGL
	{
		struct ContextBind
		{
		protected:
			Window::RenderContext::OpenGL* const				renderContext;

		public:
			inline												ContextBind(Window::Render* window);
			inline												ContextBind(Window::RenderContext::Basic* renderContext_);

			inline Window::RenderContext::OpenGL*				GetRenderContext() const;
		};
		namespace Buffer
		{
			enum struct Type: GLenum
			{
				Static	= GL_STATIC_DRAW,
				Dynamic	= GL_DYNAMIC_DRAW,
				Stream	= GL_STREAM_DRAW
			};

			namespace Attribute
			{
				enum struct DataType
				{
					Int8	= GL_BYTE,
					Int16	= GL_SHORT,
					Int32	= GL_INT,
					UInt8	= GL_UNSIGNED_BYTE,
					UInt16	= GL_UNSIGNED_SHORT,
					UInt32	= GL_UNSIGNED_INT,
					Float16	= GL_HALF_FLOAT,
					Float32 = GL_FLOAT,
					Float64 = GL_DOUBLE
				};
				struct Params
				{
					GLint					location;
					uint32					paramCount;
					DataType				dataType;
					bool					normalization;
					uint32					stride;
					uint32					offset;
					inline Params(GLint location_,uint32 paramCount_,DataType dataType_,bool normalization_,uint32 stride_,uint32 offset_)
					{
						location = location_;
						paramCount = paramCount_;
						dataType = dataType_;
						normalization = normalization_;
						stride = stride_;
						offset = offset_;
					}
				};
			};

			struct Data:
				public ContextBind
			{
			protected:
				Type											type = Type::Static;
				GLuint											buffer = 0;
				uint32											vCount = 0,
																vSize = 0;
			public:
				inline						Data(Window::Render* window);
				inline						Data(Window::RenderContext::Basic* renderContext_);
				inline						Data(const Data&) = delete;
				inline						~Data();

				inline void					Create(uint32 vCount_,uint32 vSize_,void* vData_,const Type& type_);
				inline void					Delete();
				inline void					Use();
				inline void					Unuse();
				inline uint32				GetVertexCount() const;
				inline uint32				GetVertexSize() const;
			};
			struct Index:
				public ContextBind
			{
			protected:
				Type											type = Type::Static;
				GLuint											buffer = 0;
				uint32											iCount = 0,
																iSize = 0;
			public:
				inline						Index(Window::Render* window);
				inline						Index(Window::RenderContext::Basic* renderContext_);
				inline						Index(const Index&) = delete;
				inline						~Index();

				inline void					Create(uint32 iCount_,uint32 iSize_,void* iData_,const Type& type_);
				inline void					Delete();
				inline void					Use();
				inline void					Unuse();
				inline uint32				GetIndexCount() const;
				inline uint32				GetIndexSize() const;
			};
			struct Array:
				public ContextBind
			{
			protected:
				GLuint											buffer = 0;

			public:
				inline						Array(Window::Render* window);
				inline						Array(Window::RenderContext::Basic* renderContext_);
				inline						~Array();

				//inline void					Create(Data* dBuffer_,Index* iBuffer_,Shader* shader_,std::list<Attribute::Params> params);
				inline void					Create(std::list<Attribute::Params> params);
				inline void					Delete();
				inline void					Use();
				inline void					Unuse();
			};
			struct Frame:
				public ContextBind
			{
			protected:
				uvec2						size = uvec2(0);
				GLuint						buffer = 0;

				bool*const					ownColor;
				bool						ownDepth = false;
				bool						ownStencil = false;
				Texture**const				color;				// Color Attachment
				Texture*					depth = nullptr;	// Depth Attachment
				Texture*					stencil = nullptr;	// Stencil Attachment

			public:
				inline						Frame(Window::Render* window);
				inline						Frame(Window::RenderContext::Basic* renderContext_);
				inline						~Frame();

				void						Create(Texture* texture_);
				void						Delete();
				inline void					Use();
				inline void					Unuse();
			};
		}

		struct Model
		{
		protected:

			enum struct bit: uint8
			{
				ownData		= 1<<0,
				ownIndex	= 1<<1,
				ownArray	= 1<<2,
				ownShader	= 1<<3,
				ownNone		= 0,
				ownAll		= ownData | ownIndex | ownArray | ownShader
			};

			uint8											ownBit = (uint8)bit::ownNone;

			Window::RenderContext::OpenGL* const			renderContext;

			Buffer::Data*									dBuffer = nullptr;
			Buffer::Index*									iBuffer = nullptr;
			Buffer::Array*									aBuffer = nullptr;
			Shader*											shader = nullptr;

		public:

			inline							Model(Window::Render* window):
				renderContext
				(
					window->GetRenderContext()->GetType() == Window::RenderContext::Type::OpenGL ?
					(Window::RenderContext::OpenGL*)window->GetRenderContext()->GetData() :
					throw Exception()
				)
			{
			}
			inline							Model(const Model&) = delete;
			inline							~Model()
			{
				Delete();
			}

			inline void						Create(const Geometry::Mesh* mesh_,Shader* shader_)
			{
				Delete();

				dBuffer = new Buffer::Data(renderContext);
				iBuffer = new Buffer::Index(renderContext);
				aBuffer = new Buffer::Array(renderContext);
				shader = shader_;

				ownBit = (uint8)bit::ownData | (uint8)bit::ownIndex | (uint8)bit::ownArray;

				auto vArr = mesh_->GetVertexArray();
				auto iArr = mesh_->GetIndexArray();

				shader_->Use();
				auto attPos = shader_->PrepareAttribute("vPos");
				auto attTex = shader_->PrepareAttribute("vTex");
				auto attTan = shader_->PrepareAttribute("vTan");
				auto attBin = shader_->PrepareAttribute("vBin");
				auto attNor = shader_->PrepareAttribute("vNor");

				dBuffer->Create(mesh_->GetVertexCount(),mesh_->GetVertexSize(),vArr,OpenGL::Buffer::Type::Static);
				dBuffer->Use();
				iBuffer->Create(mesh_->GetIndexCount(),mesh_->GetIndexSize(),iArr,OpenGL::Buffer::Type::Static);
				iBuffer->Use();

				aBuffer->Create
				(
					{
						OpenGL::Buffer::Attribute::Params(attPos,3,OpenGL::Buffer::Attribute::DataType::Float32,false,mesh_->GetVertexSize(),sizeof(float32)*0),
						OpenGL::Buffer::Attribute::Params(attTex,2,OpenGL::Buffer::Attribute::DataType::Float32,false,mesh_->GetVertexSize(),sizeof(float32)*3),
						OpenGL::Buffer::Attribute::Params(attTan,3,OpenGL::Buffer::Attribute::DataType::Float32,true,mesh_->GetVertexSize(),sizeof(float32)*5),
						OpenGL::Buffer::Attribute::Params(attBin,3,OpenGL::Buffer::Attribute::DataType::Float32,true,mesh_->GetVertexSize(),sizeof(float32)*8),
						OpenGL::Buffer::Attribute::Params(attNor,3,OpenGL::Buffer::Attribute::DataType::Float32,true,mesh_->GetVertexSize(),sizeof(float32)*11)
					}
				);

				delete[] vArr;
				delete[] iArr;
			}
			inline void						Delete()
			{
				if(aBuffer)
				{
					if(ownBit & (uint8)bit::ownArray)
					{
						delete aBuffer;
						ownBit &= ~(uint8)bit::ownArray;
					}
					aBuffer = nullptr;
				}
				if(dBuffer)
				{
					if(ownBit & (uint8)bit::ownData)
					{
						delete dBuffer;
						ownBit &= ~(uint8)bit::ownData;
					}
					dBuffer = nullptr;
				}
				if(iBuffer)
				{
					if(ownBit & (uint8)bit::ownIndex)
					{
						delete iBuffer;
						ownBit &= ~(uint8)bit::ownIndex;
					}
					iBuffer = nullptr;
				}
				if(shader)
				{
					if(ownBit & (uint8)bit::ownShader)
					{
						delete shader;
						ownBit &= ~(uint8)bit::ownShader;
					}
					shader = nullptr;
				}
			}
			inline void						Draw()
			{
				aBuffer->Use();
				dBuffer->Use();
				iBuffer->Use();
				shader->Use();

				glDrawElements(GL_TRIANGLES,iBuffer->GetIndexCount(),GL_UNSIGNED_INT,0);
			}
		};
	}
#endif
#if __TEXPROJECT_DIRECT3D__
	namespace Direct3D
	{
		namespace Buffer
		{
			struct Data
			{
			public:

				enum class Format: DWORD
				{
					XYZ						= D3DFVF_XYZ,
					XYZW					= D3DFVF_XYZW,
					XYZRHW					= D3DFVF_XYZRHW
				};

			protected:
				Window::RenderContext::Direct3D* const				renderContext;				
				LPDIRECT3DVERTEXBUFFER9								buffer = NULL;
				uint32												vCount = 0;
				uint32												vSize = 0;
				Format												format = Format::XYZ;				

			public:

				inline						Data(Window::Render* window);
				inline						~Data();

				inline void					Create(uint32 vCount_,uint32 vSize_,Format format_,void* data_);
				inline void					Delete();
				inline void					Use();
				inline void					Unuse();
				inline Window::RenderContext::Direct3D*			GetRenderContext() const;
			};
			struct Index
			{
			public:

				enum class Format
				{
					UInt16					= D3DFMT_INDEX16,
					UInt32					= D3DFMT_INDEX32
				};

			protected:
				Window::RenderContext::Direct3D* const				renderContext;
				LPDIRECT3DINDEXBUFFER9								buffer = NULL;
				uint32												iCount = 0;
				uint32												iSize = 0;
				Format												format = Format::UInt32;

			public:

				inline						Index(Window::Render* window);
				inline						~Index();

				inline void					Create(uint32 iCount_,uint32 iSize_,Format format_,void* data_);
				inline void					Delete();
				inline void					Use();
				inline void					Unuse();
				inline Window::RenderContext::Direct3D*			GetRenderContext() const;
			};
		}
	}
#endif
}


#if __TEXPROJECT_OPENGL__

// TexProject::OpenGL::ContextBind
inline TexProject::OpenGL::ContextBind::ContextBind(Window::Render* window):
	renderContext
	(
		window->GetRenderContext()->GetType() == Window::RenderContext::Type::OpenGL ?
		(Window::RenderContext::OpenGL*)window->GetRenderContext()->GetData() :
		throw Exception()
	)
{
}
inline TexProject::OpenGL::ContextBind::ContextBind(Window::RenderContext::Basic* renderContext_):
	renderContext
	(
		renderContext_->GetType() == Window::RenderContext::Type::OpenGL ?
		(Window::RenderContext::OpenGL*)renderContext_->GetData() :
		throw Exception()
	)
{
}
inline TexProject::Window::RenderContext::OpenGL*				TexProject::OpenGL::ContextBind::GetRenderContext() const
{
	return renderContext;
}


// Buffer::Data
inline															TexProject::OpenGL::Buffer::Data::Data(Window::Render* window):
	ContextBind(window)
{
}
inline															TexProject::OpenGL::Buffer::Data::Data(Window::RenderContext::Basic* renderContext_):
	ContextBind(renderContext_)
{
}
inline															TexProject::OpenGL::Buffer::Data::~Data()
{
	Delete();
}
inline void														TexProject::OpenGL::Buffer::Data::Create(uint32 vCount_,uint32 vSize_,void* vData_,const Type& type_)
{
	Delete();

	vCount = vCount_;
	vSize = vSize_;
	type = type_;

	OpenGL::glGenBuffers(1,&buffer);
	OpenGL::glBindBuffer(GL_ARRAY_BUFFER,buffer); renderContext->bufferDataCurrent = this;
	OpenGL::glBufferData(GL_ARRAY_BUFFER,vSize*vCount,vData_,(GLenum)type);

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Data::Delete()
{
	Unuse();
	OpenGL::glDeleteBuffers(1,&buffer);

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Data::Use()
{
	renderContext->bufferDataCurrent = this;
	OpenGL::glBindBuffer(GL_ARRAY_BUFFER,buffer);

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Data::Unuse()
{
	if(renderContext->bufferDataCurrent == this)
	{
		renderContext->bufferDataCurrent = nullptr;
		OpenGL::glBindBuffer(GL_ARRAY_BUFFER,0);
	}

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Data::GetVertexCount() const
{
	return vCount;
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Data::GetVertexSize() const
{
	return vSize;
}


// Buffer::Index
inline															TexProject::OpenGL::Buffer::Index::Index(Window::Render* window):
	ContextBind(window)
{
}
inline															TexProject::OpenGL::Buffer::Index::Index(Window::RenderContext::Basic* renderContext_):
	ContextBind(renderContext_)
{
}
inline															TexProject::OpenGL::Buffer::Index::~Index()
{
	Delete();
}
inline void														TexProject::OpenGL::Buffer::Index::Create(uint32 iCount_,uint32 iSize_,void* iData_,const Type& type_)
{
	Delete();

	iCount = iCount_;
	iSize = iSize_;
	type = type_;

	OpenGL::glGenBuffers(1,&buffer);
	OpenGL::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer); renderContext->bufferIndexCurrent = this;
	OpenGL::glBufferData(GL_ELEMENT_ARRAY_BUFFER,iSize*iCount,iData_,(GLenum)type);

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Index::Delete()
{
	Unuse();
	OpenGL::glDeleteBuffers(1,&buffer);

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Index::Use()
{
	renderContext->bufferIndexCurrent = this;
	OpenGL::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer);

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Index::Unuse()
{
	if(renderContext->bufferIndexCurrent == this)
	{
		renderContext->bufferIndexCurrent = nullptr;
		OpenGL::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	}

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Index::GetIndexCount() const
{
	return iCount;
}
inline TexProject::uint32										TexProject::OpenGL::Buffer::Index::GetIndexSize() const
{
	return iSize;
}


// Buffer::Array
inline															TexProject::OpenGL::Buffer::Array::Array(Window::Render* window):
	ContextBind(window)
{
}
inline															TexProject::OpenGL::Buffer::Array::Array(Window::RenderContext::Basic* renderContext_):
	ContextBind(renderContext_)
{
}
inline															TexProject::OpenGL::Buffer::Array::~Array()
{
	Delete();
}
inline void														TexProject::OpenGL::Buffer::Array::Create(std::list<Attribute::Params> params)
{
	Delete();

	OpenGL::glGenVertexArrays(1,&buffer);
	OpenGL::glBindVertexArray(buffer); renderContext->bufferArrayCurrent = this;

	if(!renderContext->GetCurrentBufferDara()) throw Exception();
	
	if(!renderContext->GetCurrentShader()) throw Exception();

	for(auto i: params)
	{
		if(i.location != -1)
		{
			OpenGL::glVertexAttribPointer(i.location,i.paramCount,(GLenum)i.dataType,i.normalization,i.stride,(const GLvoid*)i.offset);
			OpenGL::glEnableVertexAttribArray(i.location);
		}
	}

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Array::Delete()
{
	Unuse();
	OpenGL::glDeleteVertexArrays(1,&buffer);

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Array::Use()
{
	renderContext->bufferArrayCurrent = this;
	OpenGL::glBindVertexArray(buffer);

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Array::Unuse()
{
	if(renderContext->bufferArrayCurrent == this)
	{
		renderContext->bufferArrayCurrent = nullptr;
		OpenGL::glBindVertexArray(0);
	}

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}


// Buffer::Frame
inline															TexProject::OpenGL::Buffer::Frame::Frame(Window::Render* window):
	ContextBind(window),
	ownColor(new bool[renderContext->GetBufferFrameMaxColorAttachment()]),
	color(new Texture*[renderContext->GetBufferFrameMaxColorAttachment()])
{
	for(int32 i = 0; i < renderContext->GetBufferFrameMaxColorAttachment(); ++i)
	{
		ownColor[i] = false;
		color[i] = nullptr;
	}
}
inline															TexProject::OpenGL::Buffer::Frame::Frame(Window::RenderContext::Basic* renderContext_):
	ContextBind(renderContext_),
	ownColor(new bool[renderContext->GetBufferFrameMaxColorAttachment()]),
	color(new Texture*[renderContext->GetBufferFrameMaxColorAttachment()])
{
	for(int32 i = 0; i < renderContext->GetBufferFrameMaxColorAttachment(); ++i)
	{
		ownColor[i] = false;
		color[i] = nullptr;
	}
}
inline															TexProject::OpenGL::Buffer::Frame::~Frame()
{
	Delete();

	delete[] color;
	delete[] ownColor;
}
inline void														TexProject::OpenGL::Buffer::Frame::Use()
{
	renderContext->bufferFrameCurrent = this;
	glBindFramebuffer(GL_FRAMEBUFFER,buffer);

	glViewport(0,0,size.x,size.y);

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void														TexProject::OpenGL::Buffer::Frame::Unuse()
{
	if(renderContext->bufferFrameCurrent == this)
	{
		renderContext->bufferFrameCurrent = nullptr;
		glBindFramebuffer(GL_FRAMEBUFFER,0);
	}

#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}

#endif


#if __TEXPROJECT_DIRECT3D__

// Buffer::Data
inline					TexProject::Direct3D::Buffer::Data::Data(Window::Render* window):
	renderContext
	(
		window->GetRenderContext()->GetType() == Window::RenderContext::Type::Direct3D ?
		(Window::RenderContext::Direct3D*)window->GetRenderContext()->GetData() :
		throw Exception()
	)
{
}
inline					TexProject::Direct3D::Buffer::Data::~Data()
{
	Delete();
}
inline void				TexProject::Direct3D::Buffer::Data::Create(uint32 vCount_,uint32 vSize_,Format format_,void* data_)
{
	Delete();

	vCount = vCount_;
	vSize = vSize_;
	format = format_;

	Direct3D::ErrorTest
	(
		renderContext->GetDevice()->CreateVertexBuffer
		(
			vSize*vCount,	//sizeof(CUSTOMVERTEX)*3,
			0,
			(DWORD)format,
			D3DPOOL_DEFAULT,
			&buffer,
			NULL
		)
	);

	if(data_)
	{
		static void* tData;
		Direct3D::ErrorTest(buffer->Lock(0,vSize*vCount,&tData,0));
		memcpy(tData,data_,vSize*vCount);
		Direct3D::ErrorTest(buffer->Unlock());
	}
}
inline void				TexProject::Direct3D::Buffer::Data::Delete()
{
	Unuse();

	//buffer->Release();
	//renderContext->GetDevice()->de
}
inline void				TexProject::Direct3D::Buffer::Data::Use()
{
	Direct3D::ErrorTest(renderContext->GetDevice()->SetStreamSource(0,buffer,0,vSize));
	renderContext->GetDevice()->SetFVF((DWORD)format);
}
inline void				TexProject::Direct3D::Buffer::Data::Unuse()
{
}
inline TexProject::Window::RenderContext::Direct3D*				TexProject::Direct3D::Buffer::Data::GetRenderContext() const
{
	return renderContext;
}


inline					TexProject::Direct3D::Buffer::Index::Index(Window::Render* window):
	renderContext
	(
		window->GetRenderContext()->GetType() == Window::RenderContext::Type::Direct3D ?
		(Window::RenderContext::Direct3D*)window->GetRenderContext()->GetData() :
		throw Exception()
	)
{
}
inline					TexProject::Direct3D::Buffer::Index::~Index()
{
	Delete();
}
inline void				TexProject::Direct3D::Buffer::Index::Create(uint32 iCount_,uint32 iSize_,Format format_,void* data_)
{
	Delete();

	iCount = iCount_;
	iSize = iSize_;
	format = format_;

	Direct3D::ErrorTest
	(
		renderContext->GetDevice()->CreateIndexBuffer
		(
			iSize*iCount,
			0,
			(D3DFORMAT)format,
			D3DPOOL_DEFAULT,
			&buffer,
			NULL
		)
	);

	if(data_)
	{
		static void* tData;
		Direct3D::ErrorTest(buffer->Lock(0,iSize*iCount,&tData,0));
		memcpy(tData,data_,iSize*iCount);
		Direct3D::ErrorTest(buffer->Unlock());
	}
}
inline void				TexProject::Direct3D::Buffer::Index::Delete()
{
	Unuse();

	//buffer->Release();
}
inline void				TexProject::Direct3D::Buffer::Index::Use()
{
	renderContext->GetDevice()->SetIndices(buffer);
}
inline void				TexProject::Direct3D::Buffer::Index::Unuse()
{
}

inline TexProject::Window::RenderContext::Direct3D*				TexProject::Direct3D::Buffer::Index::GetRenderContext() const
{
	return renderContext;
}


#endif











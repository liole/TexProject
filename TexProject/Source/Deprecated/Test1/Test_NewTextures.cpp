#include <TexProject/TexProject.h>
using namespace TexProject;


namespace NewTexture
{
	/*namespace Texture
	{
		namespace Exception
		{
			class InvalidTextureCoord: public Exception {};
		}

		class D2
		{
		protected:

			vec4* data = nullptr;
			uvec2 size = uvec2(0);

		public:

			D2() = default;
			~D2() = default;

			void		Create(const uvec2& size_)
			{
				Delete();

				size = size_;

				data = new vec4[size.x*size.y];
			}
			void		Delete()
			{
				if(size.x > 0 && size.y > 0)
				{
					if(data) delete[] data;
					size = uvec2(0);
				}
			}
			void		Fill(const vec4& color_)
			{
				for(uint32 i = 0; i < size.x*size.y; ++i) data[i] = color_;
			}

			uvec2		GetSize() const
			{
				return size;
			}

			// Direct storage access
			void		SetPixel(const uvec2 pos_, const vec4& color_)
			{
				if(pos_.x < size.x && pos_.y < size.y)
				{
					data[pos_.y*size.x + pos_.x] = color_;
				}
				else
				{
					throw Exception::InvalidTextureCoord();
				}
			}
			vec4		GetPixel(const uvec2 pos_)
			{
				if(pos_.x < size.x && pos_.y < size.y)
				{
					return data[pos_.y*size.x + pos_.x];
				}
				else
				{
					throw Exception::InvalidTextureCoord();
				}
			}
			float32*	GetData()
			{
				float32* data_ = new float32[size.x*size.y*4];
				for(uint32 i = 0; i < size.x*size.y; ++i)
				{
					data_[i*4+0] = data[i].x;
					data_[i*4+1] = data[i].y;
					data_[i*4+2] = data[i].z;
					data_[i*4+3] = data[i].w;
				}
				return data_;
			}
		};		
	}*/
}


/*OpenGL::Buffer::Data*	dBuffer = nullptr;
OpenGL::Buffer::Index*	iBuffer = nullptr;
OpenGL::Buffer::Array*	aBuffer = nullptr;
OpenGL::Shader*			shader = nullptr;

NewTexture::Texture::D2	tex;
OpenGL::Texture*		glTex;*/


void tInit(Window::Render* window)
{
	/*tex.Create(uvec2(64));
	tex.Fill(vec4(1.0f,0.5f,0.0f,1.0f));

	glTex = new OpenGL::Texture(window);
	{
		auto data = tex.GetData();
		glTex->Create
		(
			OpenGL::Texture::Type::D2,
			OpenGL::Texture::IFormat::RGBA32F,
			OpenGL::Texture::Format::RGBA,
			OpenGL::Texture::Component::Float32,
			OpenGL::Texture::Wrap::Clamp,
			OpenGL::Texture::Filter::Linear,
			uvec3(tex.GetSize(),0),
			data
		);
		delete[] data;
	}

	float32 vArr[] =
	{
		-1.0f,-1.0f,0.0f,
		1.0f,-1.0f,0.0f,
		0.0f,1.0f,0.0f
	};
	dBuffer = new OpenGL::Buffer::Data(window);
	dBuffer->Create(3,sizeof(float32)*3,vArr,OpenGL::Buffer::Type::Static);
	dBuffer->Use();

	shader = new OpenGL::Shader(window);
	shader->Load("Media/Shaders/GLSL/Simple Texture/1.vs","","","","Media/Shaders/GLSL/Simple Texture/1.ps");
	shader->Use();
	shader->SetInt("Texture",0);
	auto locPos = shader->PrepareAttribute("vPos");

	aBuffer = new OpenGL::Buffer::Array(window);
	aBuffer->Create
	(
		{
			OpenGL::Buffer::Attribute::Params(locPos,3,OpenGL::Buffer::Attribute::DataType::Float32,false,sizeof(float32)*3,0)
		}
	);*/

	auto tex = new Texture::D2;
	tex->Load("Media/Images/Example.jpg");
	//tex->Create(uvec2(64));
	//tex->Fill(vec4(0.0f,1.0f,1.0f,1.0f));

	auto t = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);
	t->SetImage(tex);
}
void tFree(Window::Render* window)
{
}
void tLoop(Window::Render* window)
{
	/*glClearColor(0.16f,0.16f,0.16f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glTex->Use(0);

	aBuffer->Use();
	dBuffer->Use();
	shader->Use();

	glDrawArrays(GL_TRIANGLES,0,3);*/
}


void TexProject::Main()
{
	Window::Render tWindow;

	tWindow.SetFunc(Window::Render::FuncTypes::Init,tInit);
	tWindow.SetFunc(Window::Render::FuncTypes::Free,tFree);
	tWindow.SetFunc(Window::Render::FuncTypes::Loop,tLoop);
	tWindow.Create();
	tWindow.SetSize(uvec2(800,600));
	//tWindow.SetRenderContext(Window::RenderContext::Type::OpenGL);
	tWindow.SetRenderContext(Window::RenderContext::Type::Default);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	tWindow.Delete();
}













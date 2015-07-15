#include <TexProject/TexProject.h>
using namespace TexProject;


Window::RenderContext::OpenGL*	glRC = nullptr;
OpenGL::Shader*					glShader = nullptr;
OpenGL::Texture*				glSourceTexture = nullptr;
OpenGL::Texture*				glResultTexture = nullptr;
OpenGL::Buffer::Frame*			glBufferFrame = nullptr;

Texture::D2						sourceTexture;
Texture::D2						resultTexture;

void fInit(Window::Render* window)
{
	sourceTexture.Load("Media/Images/Stone_HeightMap.png");
	//sourceTexture.Load("Media/Images/Floor1_M.png");

	{
		glRC = new Window::RenderContext::OpenGL(window);
		glRC->Create();

		if(glRC->Use())
		{
			glShader = new OpenGL::Shader(glRC);
			glShader->Load("Media/Shaders/GLSL/Screen Quad/Normals Generator/1.vs","","","Media/Shaders/GLSL/Screen Quad/Normals Generator/1.gs","Media/Shaders/GLSL/Screen Quad/Normals Generator/1.ps");
			glShader->SetInt("Texture",0);
			glShader->SetVec2("dt",1.0f/vec2(sourceTexture.GetSize()));

			glSourceTexture = new OpenGL::Texture(glRC);
			*glSourceTexture = sourceTexture;

			glResultTexture = new OpenGL::Texture(glRC);
			//glResultTexture->Create(OpenGL::Texture::Type::D2,OpenGL::Texture::IFormat::RGBA32F,OpenGL::Texture::Format::RGBA,OpenGL::Texture::Component::Float32,OpenGL::Texture::Wrap::Clamp,OpenGL::Texture::Filter::Off,uvec3(uvec2(1024),0),nullptr);
			glResultTexture->Create(OpenGL::Texture::Type::D2,OpenGL::Texture::IFormat::RGB8,OpenGL::Texture::Format::RGB,OpenGL::Texture::Component::UInt8,OpenGL::Texture::Wrap::Clamp,OpenGL::Texture::Filter::Off,glSourceTexture->GetSize(),nullptr);

			glBufferFrame = new OpenGL::Buffer::Frame(glRC);
			glBufferFrame->Create(glResultTexture);

			glSourceTexture->Use(0);
			glBufferFrame->Use();
			glShader->Use();
			glDrawArrays(GL_POINTS,0,1);
			glShader->Unuse();
			glBufferFrame->Unuse();
			glSourceTexture->Unuse(0);

			resultTexture = *glResultTexture;

			delete glBufferFrame;
			delete glSourceTexture;
			delete glResultTexture;
			delete glShader;

			glRC->Unuse();
		}
		
		delete glRC;
	}

	auto t = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);
	t->SetSize(vec2(512.0f));
	t->SetImage(&resultTexture);
}
void fFree(Window::Render* window)
{
}
void fLoop(Window::Render* window)
{
}


void TexProject::Main()
{
	Window::Render wnd;

	wnd.SetFunc(Window::Render::FuncTypes::Init,fInit);
	wnd.SetFunc(Window::Render::FuncTypes::Free,fFree);
	wnd.SetFunc(Window::Render::FuncTypes::Loop,fLoop);
	wnd.Create("window");
	wnd.SetSize(uvec2(800,600));
	wnd.SetRenderContext(Window::RenderContext::Type::Default);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	wnd.Delete();
}













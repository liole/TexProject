#include <TexProject/TexProject.h>
using namespace TexProject;


OpenGL::Shader*		glShader1D		= nullptr;
OpenGL::Shader*		glShader2D		= nullptr;
OpenGL::Shader*		glShader3D		= nullptr;
OpenGL::Shader*		glShaderCube	= nullptr;
OpenGL::Texture*	glTex1D			= nullptr;
OpenGL::Texture*	glTex2D			= nullptr;
OpenGL::Texture*	glTex3D			= nullptr;
OpenGL::Texture*	glTexCube		= nullptr;


void fInit(Window::Render* window)
{
	glShader1D = new OpenGL::Shader(window);
	{
		glShader1D->Load
		(
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer 1D/1.vs",
			"",
			"",
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer 1D/1.gs",
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer 1D/1.ps"
		);
		glShader1D->SetInt("Texture",0);
	}

	glShader2D = new OpenGL::Shader(window);
	{
		glShader2D->Load
		(
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer 2D/1.vs",
			"",
			"",
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer 2D/1.gs",
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer 2D/1.ps"
		);
		glShader2D->SetInt("Texture",0);
	}

	glShader3D = new OpenGL::Shader(window);
	{
		glShader3D->Load
		(
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer 3D/1.vs",
			"",
			"",
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer 3D/1.gs",
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer 3D/1.ps"
		);
		glShader3D->SetInt("Texture",0);
	}

	glShaderCube = new OpenGL::Shader(window);
	{
		glShaderCube->Load
		(
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer Cube/1.vs",
			"",
			"",
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer Cube/1.gs",
			"Media/Shaders/GLSL/Screen Quad/Test/Drawer Cube/1.ps"
		);
		glShaderCube->SetInt("Texture",0);
	}


	auto tex1D		= new Texture::D1;
	{
		tex1D->Create(64);
		for(uint32 x = 0; x < tex1D->GetSize(); ++x)
		{
			auto d = float32(x)/float32(tex1D->GetSize()-1);
			tex1D->SetPixel(x,vec4(d,0.0f,1.0f,1.0f));
		}
		glTex1D		= new OpenGL::Texture(window);
		*glTex1D = *tex1D;
	}
	delete tex1D;

	auto tex2D		= new Texture::D2;
	{
		tex2D->Create(uvec2(64));
		for(uint32 x = 0; x < tex2D->GetSize().x; ++x)
		for(uint32 y = 0; y < tex2D->GetSize().y; ++y)
		{
			auto d = vec2(x,y)/vec2(tex2D->GetSize()-1);
			tex2D->SetPixel(uvec2(x,y),vec4(d,0.5f,1.0f));
		}
		glTex2D		= new OpenGL::Texture(window);
		*glTex2D = *tex2D;
	}
	delete tex2D;

	auto tex3D		= new Texture::D3;
	{
		tex3D->Create(uvec3(64));
		for(uint32 x = 0; x < tex3D->GetSize().x; ++x)
		for(uint32 y = 0; y < tex3D->GetSize().y; ++y)
		for(uint32 z = 0; z < tex3D->GetSize().z; ++z)
		{
			auto d = vec3(x,y,z)/vec3(tex3D->GetSize()-1);
			tex3D->SetPixel(uvec3(x,y,z),vec4(d,1.0f));
		}
		glTex3D		= new OpenGL::Texture(window);
		*glTex3D = *tex3D;
	}
	delete tex3D;

	auto texCube		= new Texture::Cube;
	{
		texCube->Create(64);
		for(uint32 f = 0; f < 6; ++f)
		for(uint32 x = 0; x < texCube->GetSize(); ++x)
		for(uint32 y = 0; y < texCube->GetSize(); ++y)
		{
			auto d = vec2(x,y)/vec2(texCube->GetSize()-1);
			auto face = (Texture::Cube::Face)f;
			switch(face)
			{
			case TexProject::Texture::Cube::Face::Right:	texCube->SetPixel(face,uvec2(x,y),vec4(d,0.0f,1.0f));		break;
			case TexProject::Texture::Cube::Face::Left:		texCube->SetPixel(face,uvec2(x,y),vec4(d.x,0.0f,d.y,1.0f));	break;
			case TexProject::Texture::Cube::Face::Top:		texCube->SetPixel(face,uvec2(x,y),vec4(0.0f,d,1.0f));		break;
			case TexProject::Texture::Cube::Face::Bottom:	texCube->SetPixel(face,uvec2(x,y),vec4(d,1.0f,1.0f));		break;
			case TexProject::Texture::Cube::Face::Front:	texCube->SetPixel(face,uvec2(x,y),vec4(d.x,1.0f,d.y,1.0f));	break;
			case TexProject::Texture::Cube::Face::Back:		texCube->SetPixel(face,uvec2(x,y),vec4(1.0f,d,1.0f));		break;
			default: texCube->SetPixel(face,uvec2(x,y),vec4(0.0f)); break;
			}
		}
		glTexCube		= new OpenGL::Texture(window);
		*glTexCube = *texCube;
	}
	delete texCube;

}
void fFree(Window::Render* window)
{
	if(glTex1D)		{ delete glTex1D;	glTex1D		= nullptr; }
	if(glTex2D)		{ delete glTex2D;	glTex2D		= nullptr; }
	if(glTex3D)		{ delete glTex3D;	glTex3D		= nullptr; }
	if(glTexCube)	{ delete glTexCube;	glTexCube	= nullptr; }
}
void fLoop(Window::Render* window)
{
	static float32 stage = 0.0f;
	if(KeyState(Keys::A)) stage -= 0.01f;
	if(KeyState(Keys::D)) stage += 0.01f;

	static int32 face = 0;
	if(KeyState(Keys::Q)) face = 0;
	if(KeyState(Keys::W)) face = 1;
	if(KeyState(Keys::E)) face = 2;
	if(KeyState(Keys::R)) face = 3;
	if(KeyState(Keys::T)) face = 4;
	if(KeyState(Keys::Y)) face = 5;


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	if(KeyState(Keys::DIGIT1))
	{
		glTex1D->Use(0);
		glShader1D->Use();
		glDrawArrays(GL_POINTS,0,1);
	}
	if(KeyState(Keys::DIGIT2))
	{
		glTex2D->Use(0);
		glShader2D->Use();
		glDrawArrays(GL_POINTS,0,1);
	}
	if(KeyState(Keys::DIGIT3))
	{
		glTex3D->Use(0);
		glShader3D->Use();
		glShader3D->SetFloat("stage",stage);
		glDrawArrays(GL_POINTS,0,1);
	}
	if(KeyState(Keys::DIGIT4))
	{
		glTexCube->Use(0);
		glShaderCube->Use();
		glShaderCube->SetInt("face",face);
		glDrawArrays(GL_POINTS,0,1);
	}

}


void TexProject::Main()
{
	Window::Render wnd;
	Window::Render wnd1;

	wnd.SetFunc(Window::Render::FuncTypes::Init,fInit);
	wnd.SetFunc(Window::Render::FuncTypes::Free,fFree);
	wnd.SetFunc(Window::Render::FuncTypes::Loop,fLoop);
	wnd.Create("window");
	wnd.SetSize(uvec2(800,600));
	wnd.SetRenderContext(Window::RenderContext::Type::OpenGL);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	wnd.Delete();
}













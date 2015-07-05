#include <TexProject/TexProject.h>
using namespace TexProject;


/*OpenGL::Buffer::Array*	aBuffer;
OpenGL::Buffer::Data*	dBuffer;
OpenGL::Shader*			shader;


void tInit1(Window::Render* window)
{
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
	shader->Load("Media/Shaders/GLSL/Simple/1.vs","","","","Media/Shaders/GLSL/Simple/1.ps");
	shader->Use();
	auto locPos = shader->PrepareAttribute("vPos");

	aBuffer = new OpenGL::Buffer::Array(window);
	aBuffer->Create
	(
		{
			OpenGL::Buffer::Attribute::Params(locPos,3,OpenGL::Buffer::Attribute::DataType::Float32,false,sizeof(float32)*3,0)
		}
	);
}
void tFree1(Window::Render* window)
{
}
void tLoop1(Window::Render* window)
{
	aBuffer->Use();
	dBuffer->Use();
	shader->Use();

	glDrawArrays(GL_TRIANGLES,0,3);
}*/


Direct3D::Buffer::Data*		dBufferDX = nullptr;
Direct3D::Buffer::Index*	iBufferDX = nullptr;
Direct3D::Shader*			shaderDX = nullptr;


void tInit2(Window::Render* window)
{
	float32 vArr[] =
	{
		0.0f,512.0f,0.0f,1.0f,
		512.0f,512.0f,0.0f,1.0f,
		256.0f,0.0f,0.0f,1.0f
	};
	uint32 iArr[] =
	{
		0, 1, 2
	};

	dBufferDX = new Direct3D::Buffer::Data(window);
	dBufferDX->Create(3,sizeof(float32)*4,Direct3D::Buffer::Data::Format::XYZRHW,vArr);

	iBufferDX = new Direct3D::Buffer::Index(window);
	iBufferDX->Create(3,sizeof(uint32),Direct3D::Buffer::Index::Format::UInt32,iArr);

	shaderDX = new Direct3D::Shader(window);
	shaderDX->Load("Media/Shaders/HLSL/1.fx");
}
void tFree2(Window::Render* window)
{
}
void tLoop2(Window::Render* window)
{
	shaderDX->Use();

	dBufferDX->Use();
	iBufferDX->Use();

	auto d3ddev = ((Window::RenderContext::Direct3D*)window->GetRenderContext())->GetDevice();
	//d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,3,0,1);

	shaderDX->Unuse();
}


void TexProject::Main()
{
	Window::Render wnd1;
	Window::Render wnd2;

	/*wnd1.SetFunc(Window::Render::FuncTypes::Init,tInit1);
	wnd1.SetFunc(Window::Render::FuncTypes::Free,tFree1);
	wnd1.SetFunc(Window::Render::FuncTypes::Loop,tLoop1);
	wnd1.Create("OpenGL");
	wnd1.SetSize(uvec2(512,512));
	wnd1.SetRenderContext(Window::RenderContext::Type::OpenGL);*/

	wnd2.SetFunc(Window::Render::FuncTypes::Init,tInit2);
	wnd2.SetFunc(Window::Render::FuncTypes::Free,tFree2);
	wnd2.SetFunc(Window::Render::FuncTypes::Loop,tLoop2);
	wnd2.Create("Direct3D");
	wnd2.SetSize(uvec2(512,512));
	wnd2.SetRenderContext(Window::RenderContext::Type::Direct3D);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	wnd1.Delete();
	wnd2.Delete();
}













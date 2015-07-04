#include <TexProject/TexProject.h>
using namespace TexProject;


OpenGL::Texture*		tTexDif = nullptr;
OpenGL::Texture*		tTexNor = nullptr;
OpenGL::Texture*		tTexMat = nullptr;
OpenGL::Model*			tModel = nullptr;
OpenGL::Shader*			tShader = nullptr;
GLint					tUni1,tUni2,tUni3;
Helper::MMat			tMMat;
Helper::VMat			tVMat;

void tInit1(Window::Render* window)
{
	tVMat.SetPos(vec3(0.0f,0.0f,-20.0f));
	tVMat.SetAng(vec3(0.0f,0.0,0.0f));
	tVMat.SetPerspective(Helper::Transform::D3::Projection::Params::Perspective(60.0f,float32(window->GetSize().x)/float32(window->GetSize().y),0.1f,1000.0f));

	tMMat.SetPos(vec3(0.0f));
	tMMat.SetAng(vec3(0.0f));
	tMMat.SetScale(vec3(1.0f));

	auto mesh = new Geometry::Mesh;
	mesh->CreateBox(vec3(10.0f),vec3(1.0f),uvec3(1));
	//mesh->CreateCylinder(5.0f,10.0f,vec2(1.0f),vec2(1.0f),uvec2(32,4),0);

	tShader = new OpenGL::Shader(window);
	tShader->Load("Media/Shaders/GLSL/3D/Material/Basic/V1/1.vs","","","","Media/Shaders/GLSL/3D/Material/Basic/V1/1.ps");
	tShader->Use();
	tShader->SetInt("TextureDiffuse",0);
	tShader->SetInt("TextureNormal",1);
	tShader->SetInt("TextureMaterial",2);
	tUni1 = tShader->PrepareUniform("RotateMatrix");
	tUni2 = tShader->PrepareUniform("ModelMatrix");
	tUni3 = tShader->PrepareUniform("ModelViewProjectionMatrix");

	tModel = new OpenGL::Model(window);
	tModel->Create(mesh,tShader);

	delete mesh;

	auto tex = new Texture::D2;
	tex->Load("Media/Images/Brick1_D.png");
	tTexDif = new OpenGL::Texture(window); *tTexDif = *tex;
	tex->Load("Media/Images/Brick1_N.png");
	tTexNor = new OpenGL::Texture(window); *tTexNor = *tex;
	tex->Load("Media/Images/Brick1_M.png");
	tTexMat = new OpenGL::Texture(window); *tTexMat = *tex;
	delete tex;
}
void tFree1(Window::Render* window)
{
}
void tLoop1(Window::Render* window)
{
	{
		tMMat.Rotate(vec3(0.0f,1.0f,0.0f));
	}
	{
		float32 speed = 0.1f;
		vec3 move(0.0f);
		if(KeyState(Keys::W)) move.z += speed;
		if(KeyState(Keys::S)) move.z -= speed;
		if(KeyState(Keys::D)) move.x += speed;
		if(KeyState(Keys::A)) move.x -= speed;
		if(KeyState(Keys::SPACE)) move.y += speed;
		if(KeyState(Keys::L_CTRL)) move.y -= speed;
		tVMat.Move(move);
	}
	{
		float32 speed = 1.0f;
		vec3 rotate(0.0f);
		if(KeyState(Keys::E)) rotate.z += speed;
		if(KeyState(Keys::Q)) rotate.z -= speed;
		if(KeyState(Keys::UP)) rotate.x += speed;
		if(KeyState(Keys::DOWN)) rotate.x -= speed;
		if(KeyState(Keys::RIGHT)) rotate.y += speed;
		if(KeyState(Keys::LEFT)) rotate.y -= speed;
		tVMat.Rotate(rotate);
	}

	glClearColor(0.16f,0.16f,0.16f,1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);

	tTexDif->Use(0);
	tTexNor->Use(1);
	tTexMat->Use(2);
	tShader->Use();
	tShader->SetVec3("lightPos",vec3(0.0f,10.0f,-20.0f) - tVMat.GetPos());
	tShader->SetMat3(tUni1,tMMat.GetRMat());
	tShader->SetMat4(tUni2,tMMat.GetMMat() * mat4::move(-tVMat.GetPos()));
	tShader->SetMat4(tUni3,tMMat.GetMMat() * tVMat.GetVPMat());

	tModel->Draw();
}




void tInit2(Window::Render* window)
{
	auto tex = new Texture::D2;
	tex->Load("Media/Images/Example.jpg");

	tex->SetPixel(uvec2(0,0),vec4(1,0,0,1));

	auto a = window->AddPanel(Interface::PanelTypes::Default);
	a->LockMove();
	a->SetPos(vec2(100.0f));

	auto t = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);
	t->SetImage(tex);
}
void tFree2(Window::Render* window)
{
}
void tLoop2(Window::Render* window)
{
}




OpenGL::Buffer::Array*	aBuffer;
OpenGL::Buffer::Data*	dBuffer;
OpenGL::Shader*			shader;

void tInit3(Window::Render* window)
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
void tFree3(Window::Render* window)
{
}
void tLoop3(Window::Render* window)
{
	aBuffer->Use();
	dBuffer->Use();
	shader->Use();

	glDrawArrays(GL_TRIANGLES,0,3);
}




void tInit4(Window::Render* window)
{
}
void tFree4(Window::Render* window)
{
}
void tLoop4(Window::Render* window)
{
}




void TexProject::Main()
{
	Window::Render wnd1;
	Window::Render wnd2;
	Window::Render wnd3;
	Window::Render wnd4;

	wnd1.SetFunc(Window::Render::FuncTypes::Init,tInit1);
	wnd1.SetFunc(Window::Render::FuncTypes::Free,tFree1);
	wnd1.SetFunc(Window::Render::FuncTypes::Loop,tLoop1);
	wnd1.Create("Render");
	wnd1.SetSize(uvec2(512));
	wnd1.SetRenderContext(Window::RenderContext::Type::OpenGL);

	wnd2.SetFunc(Window::Render::FuncTypes::Init,tInit2);
	wnd2.SetFunc(Window::Render::FuncTypes::Free,tFree2);
	wnd2.SetFunc(Window::Render::FuncTypes::Loop,tLoop2);
	wnd2.Create("Default Context");
	wnd2.SetSize(uvec2(800,600));
	wnd2.SetRenderContext(Window::RenderContext::Type::Default);

	wnd3.SetFunc(Window::Render::FuncTypes::Init,tInit3);
	wnd3.SetFunc(Window::Render::FuncTypes::Free,tFree3);
	wnd3.SetFunc(Window::Render::FuncTypes::Loop,tLoop3);
	wnd3.Create("OpenGL Context");
	wnd3.SetSize(uvec2(512));
	wnd3.SetRenderContext(Window::RenderContext::Type::OpenGL);

	wnd4.Create("Direct3D Context");
	wnd4.SetSize(uvec2(512));
	wnd4.SetRenderContext(Window::RenderContext::Type::Direct3D);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	wnd1.Delete();
	wnd2.Delete();
	wnd3.Delete();
	wnd4.Delete();
}













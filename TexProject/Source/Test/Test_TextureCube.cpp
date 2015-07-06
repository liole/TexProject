#include <TexProject/TexProject.h>
using namespace TexProject;


OpenGL::Texture*		tTexDif = nullptr;
OpenGL::Texture*		tTexNor = nullptr;
OpenGL::Texture*		tTexMat = nullptr;
OpenGL::Texture*		tTexEnv = nullptr;
OpenGL::Model*			tModel = nullptr;
OpenGL::Shader*			tShader = nullptr;
GLint					tUni1,tUni2,tUni3;
Helper::MMat			tMMat;
Helper::VMat			tVMat;


void fInit(Window::Render* window)
{
	tVMat.SetPos(vec3(0.0f,0.0f,-20.0f));
	tVMat.SetAng(vec3(0.0f,0.0,0.0f));
	tVMat.SetPerspective(Helper::Transform::D3::Projection::Params::Perspective(60.0f,float32(window->GetSize().x)/float32(window->GetSize().y),0.1f,1000.0f));

	tMMat.SetPos(vec3(0.0f));
	tMMat.SetAng(vec3(0.0f));
	tMMat.SetScale(vec3(1.0f));

	auto mesh = new Geometry::Mesh;
	//mesh->CreateBox(vec3(10.0f),vec3(1.0f),uvec3(1));
	mesh->CreateCylinder(5.0f,10.0f,vec2(6.0f,2.0f),vec2(2.0f),uvec2(32,4),4);

	tShader = new OpenGL::Shader(window);
	tShader->Load("Media/Shaders/GLSL/3D/Material/Basic/V1/1.vs","","","","Media/Shaders/GLSL/3D/Material/Basic/V1/1.ps");
	tShader->Use();
	tShader->SetInt("TextureDiffuse",0);
	tShader->SetInt("TextureNormal",1);
	tShader->SetInt("TextureMaterial",2);
	tShader->SetInt("TextureEnvironment",3);
	tUni1 = tShader->PrepareUniform("RotateMatrix");
	tUni2 = tShader->PrepareUniform("ModelMatrix");
	tUni3 = tShader->PrepareUniform("ModelViewProjectionMatrix");

	tModel = new OpenGL::Model(window);
	tModel->Create(mesh,tShader);

	delete mesh;

	{
		auto tex = new Texture::D2;
		tex->Load("Media/Images/Brick1_D.png");
		tTexDif = new OpenGL::Texture(window); *tTexDif = *tex;
		tex->Load("Media/Images/Brick1_N.png");
		tTexNor = new OpenGL::Texture(window); *tTexNor = *tex;
		tex->Load("Media/Images/Brick1_M.png");
		tTexMat = new OpenGL::Texture(window); *tTexMat = *tex;
		delete tex;
	}

	{
		auto tex = new Texture::Cube;
		/*tex->Create(128);
		tex->Fill(Texture::Cube::Face::Right,vec4(1,0,0,1));
		tex->Fill(Texture::Cube::Face::Left,vec4(0,1,1,1));
		tex->Fill(Texture::Cube::Face::Top,vec4(0,1,0,1));
		tex->Fill(Texture::Cube::Face::Bottom,vec4(1,0,1,1));
		tex->Fill(Texture::Cube::Face::Front,vec4(0,0,1,1));
		tex->Fill(Texture::Cube::Face::Back,vec4(1,1,0,1));*/
		tex->Load("Media/Images/Cubemap2.DDS");
		tTexEnv = new OpenGL::Texture(window);
		*tTexEnv = *tex;
	}
}
void fFree(Window::Render* window)
{
}
void fLoop(Window::Render* window)
{
	{
		tMMat.Rotate(vec3(0.0f,0.25f,0.0f));
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
	glEnable(GL_CULL_FACE);	//glDisable(GL_CULL_FACE);

	if(MouseLState()) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	tTexDif->Use(0);
	tTexNor->Use(1);
	tTexMat->Use(2);
	tTexEnv->Use(3);
	tShader->Use();
	tShader->SetVec3("lightPos",vec3(0.0f,10.0f,-20.0f) - tVMat.GetPos());
	tShader->SetMat3(tUni1,tMMat.GetRMat());
	tShader->SetMat4(tUni2,tMMat.GetMMat() * mat4::move(-tVMat.GetPos()));
	tShader->SetMat4(tUni3,tMMat.GetMMat() * tVMat.GetVPMat());

	tModel->Draw();
}


void TexProject::Main()
{
	Window::Render wnd;

	wnd.SetFunc(Window::Render::FuncTypes::Init,fInit);
	wnd.SetFunc(Window::Render::FuncTypes::Free,fFree);
	wnd.SetFunc(Window::Render::FuncTypes::Loop,fLoop);
	wnd.Create("window");
	wnd.SetSize(uvec2(1024,600));
	wnd.SetRenderContext(Window::RenderContext::Type::OpenGL);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	wnd.Delete();
}













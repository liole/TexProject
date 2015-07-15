#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_OpenGL.h>
#include <TexProject/TexProject_Direct3D.h>
#include <TexProject/TexProject_Windows.h>


#ifdef __TEXPROJECT_OPENGL__
#endif


namespace TexProject
{
#if __TEXPROJECT_OPENGL__
	namespace OpenGL
	{
		struct Shader
		{
		protected:

			static bool						LinkProgram(GLuint prog);
			static bool						CompileShader(GLuint shader);
			static bool						LoadFile(const string& fileName,bool binary,uint8 **buffer,uint32 *size);


			Window::RenderContext::OpenGL* const			renderContext;
			GLuint											prog = 0,
															vs = 0,
															tc = 0,
															te = 0,
															gs = 0,
															ps = 0;

		public:


			inline							Shader(Window::Render* window);
			inline							Shader(Window::RenderContext::Basic* renderContext_);
			inline							Shader(const Shader&) = delete;
			inline							Shader(Shader&&) = delete;
			inline							~Shader();

			inline Shader&					operator = (const Shader&) = delete;
			inline Shader&					operator = (Shader&&) = delete;

			inline void						Create();
			inline void						Delete();
			inline void						Use();
			inline void						Unuse();

			bool							Load(const string& vsPath,const string& tcPath,const string& tePath,const string& gsPath,const string& psPath);

			inline GLint					PrepareAttribute(const string& attributeName);

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
	}
#endif
#if __TEXPROJECT_OPENGL__
	namespace Direct3D
	{
		struct Shader
		{
		protected:
			Window::RenderContext::Direct3D* const				renderContext;
			LPD3DXEFFECT										effect = NULL;

		public:

			inline							Shader(Window::Render* window);
			inline							~Shader();

			//inline void						Create();
			inline void						Delete();
			inline bool						Load(const string& filename);
			inline void						Use();
			inline void						Unuse();
			inline Window::RenderContext::Direct3D*			GetRenderContext() const;
		};
	}
#endif
}


#if __TEXPROJECT_OPENGL__

inline										TexProject::OpenGL::Shader::Shader(Window::Render* window):
	renderContext
	(
		window->GetRenderContext()->GetType() == Window::RenderContext::Type::OpenGL ?
		(Window::RenderContext::OpenGL*)window->GetRenderContext()->GetData() :
		throw Exception()
	)
{
}
inline										TexProject::OpenGL::Shader::Shader(Window::RenderContext::Basic* renderContext_):
	renderContext
	(
		renderContext_->GetType() == Window::RenderContext::Type::OpenGL ?
		(Window::RenderContext::OpenGL*)renderContext_->GetData() :
		throw Exception()
	)
{
}
inline										TexProject::OpenGL::Shader::~Shader()
{
	Delete();
}
inline void									TexProject::OpenGL::Shader::Create()
{
	Delete();

	prog	= glCreateProgram();
	vs		= glCreateShader(GL_VERTEX_SHADER);
	ps		= glCreateShader(GL_FRAGMENT_SHADER);

	gs		= glCreateShader(GL_GEOMETRY_SHADER);

	tc		= glCreateShader(GL_TESS_CONTROL_SHADER);
	te		= glCreateShader(GL_TESS_EVALUATION_SHADER);

#ifdef __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::Delete()
{
	Unuse();

	if(prog) { glDeleteProgram(prog); prog = 0; }
	if(vs) { glDeleteShader(vs); vs = 0; }
	if(ps) { glDeleteShader(ps); ps = 0; }
	if(gs) { glDeleteShader(gs); gs = 0; }
	if(tc) { glDeleteShader(tc); tc = 0; }
	if(te) { glDeleteShader(te); te = 0; }

#ifdef __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::Use()
{
	if(prog)
	{
		renderContext->shaderCurrent = this;
		glUseProgram(prog);
	}
	else
	{
		throw Exception("Try To Use Uninit Shader.");
	}

#ifdef __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::Unuse()
{
	if(renderContext->shaderCurrent == this)
	{
		renderContext->shaderCurrent = nullptr;
		glUseProgram(0);
	}

#ifdef __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline GLint								TexProject::OpenGL::Shader::PrepareAttribute(const string& attributeName)
{
#ifdef __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();

	if(prog && renderContext->shaderCurrent == this)
	{
		return glGetAttribLocation(prog,attributeName.c_str());
	}
	else
	{
		Message("Failed To Get Attribute.");
		return -1;
	}
#else
	return glGetAttribLocation(prog,attributeName.c_str());
#endif
}
inline GLint								TexProject::OpenGL::Shader::PrepareUniform(const string& uniformName)
{
#ifdef __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();

	if(prog && renderContext->shaderCurrent == this)
	{
		return glGetUniformLocation(prog,uniformName.c_str());
	}
	else
	{
		Message("Failed To Get Uniform.");
		return -1;
	}
#else
	return glGetUniformLocation(prog,uniformName.c_str());
#endif
}
inline void									TexProject::OpenGL::Shader::SetInt(GLint slot_,int32 val_)
{
	glUniform1i(slot_, val_);
#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetFloat(GLint slot_,float32 val_)
{
	glUniform1f(slot_, val_);
#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetVec2(GLint slot_,const vec2& val_)
{
	glUniform2f(slot_, val_.x, val_.y);
#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetVec3(GLint slot_,const vec3& val_)
{
	glUniform3f(slot_,val_.x,val_.y,val_.z);
#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetVec4(GLint slot_,const vec4& val_)
{
	glUniform4f(slot_, val_.x, val_.y, val_.z, val_.w);
#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetMat3(GLint slot_,const mat3& val_)
{
	glUniformMatrix3fv(slot_,1,GL_TRUE,val_.val);
#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
#endif
}
inline void									TexProject::OpenGL::Shader::SetMat4(GLint slot_,const mat4& val_)
{
	glUniformMatrix4fv(slot_,1,GL_TRUE,val_.val);
#if __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();
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

#endif


#if __TEXPROJECT_DIRECT3D__

inline					TexProject::Direct3D::Shader::Shader(Window::Render* window):
	renderContext
	(
		window->GetRenderContext()->GetType() == Window::RenderContext::Type::Direct3D ?
		(Window::RenderContext::Direct3D*)window->GetRenderContext()->GetData() :
		throw Exception()
	)
{
}
inline					TexProject::Direct3D::Shader::~Shader()
{
	Delete();
}
/*inline void				TexProject::Direct3D::Shader::Create()
{
	Delete();

}*/
inline void				TexProject::Direct3D::Shader::Delete()
{
}
inline bool				TexProject::Direct3D::Shader::Load(const string& filename)
{
	Delete();

	if(Direct3D::ErrorTest
	(
		D3DXCreateEffectFromFile
		(
			renderContext->GetDevice(),
			filename.c_str(),
			NULL,
			NULL,
			D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,
			NULL,
			&effect,
			NULL
		)
	)) return false;

	return true;
}
inline void									TexProject::Direct3D::Shader::Use()
{
	uint32 passes = 0;
	Direct3D::ErrorTest(effect->Begin(&passes,0));
	Direct3D::ErrorTest(effect->BeginPass(0));
}
inline void									TexProject::Direct3D::Shader::Unuse()
{
	effect->EndPass();
	effect->End();
}
inline TexProject::Window::RenderContext::Direct3D*				TexProject::Direct3D::Shader::GetRenderContext() const
{
	return renderContext;
}

#endif

















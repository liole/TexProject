#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_OpenGL.h>
#include <TexProject/TexProject_Windows.h>


#ifdef __TEXPROJECT_OPENGL__
#endif


namespace TexProject
{
#ifdef __TEXPROJECT_OPENGL__
	namespace OpenGL
	{
		struct Shader
		{
		protected:

			static Shader*					current;

			static bool						LinkProgram(GLuint prog);
			static bool						CompileShader(GLuint shader);
			static bool						LoadFile(const string& fileName,bool binary,uint8 **buffer,uint32 *size);


			bool							init = false;
			GLuint							prog_ = 0,
											vs_ = 0,
											tc_ = 0,
											te_ = 0,
											gs_ = 0,
											ps_ = 0;

		public:

			static void						UseNull();


											Shader() = default;
											Shader(const Shader&) = delete;
											Shader(Shader&&) = delete;

			Shader&							operator = (const Shader&) = delete;
			Shader&							operator = (Shader&&) = delete;

			void							Create();
			void							Delete();
			void							Use();

			bool							Load(const string& vsPath,const string& tcPath,const string& tePath,const string& gsPath,const string& psPath);

			inline GLint						PrepareUniform(const string& uniformName);
			inline void							SetInt(GLint slot_,int32 val_);
			inline void							SetFloat(GLint slot_,float32 val_);
			inline void							SetVec2(GLint slot_,const vec2& val_);
			inline void							SetVec3(GLint slot_,const vec3& val_);
			inline void							SetVec4(GLint slot_,const vec4& val_);
			inline void							SetMat3(GLint slot_,const mat3& val_);
			inline void							SetMat4(GLint slot_,const mat4& val_);
			inline void							SetInt(const string& slot_,int32 val_);
			inline void							SetFloat(const string& slot_,float32 val_);
			inline void							SetVec2(const string& slot_,const vec2& val_);
			inline void							SetVec3(const string& slot_,const vec3& val_);
			inline void							SetVec4(const string& slot_,const vec4& val_);
			inline void							SetMat3(const string& slot_,const mat3& val_);
			inline void							SetMat4(const string& slot_,const mat4& val_);

		};
	}
#endif
}


#ifdef __TEXPROJECT_OPENGL__

inline GLint								TexProject::OpenGL::Shader::PrepareUniform(const string& uniformName)
{
#ifdef __TEXPROJECT_DEBUG__
	OpenGL::ErrorTest();

	if(init && current == this)
	{
		return glGetUniformLocation(prog_,uniformName.c_str());
	}
	else
	{
		Message("Failed To Get Uniform.");
		return -1;
	}
#else
	return glGetUniformLocation(prog_,uniformName.c_str());
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
	SetInt(PrepareUniform(slot_),val_);
}
inline void									TexProject::OpenGL::Shader::SetFloat(const string& slot_,float32 val_)
{
	Use();
	SetFloat(PrepareUniform(slot_),val_);
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


















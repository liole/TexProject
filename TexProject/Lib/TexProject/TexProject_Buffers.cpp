#include "TexProject_Buffers.h"
using namespace TexProject;

#include <TexProject/TexProject_Textures.h>



#if __TEXPROJECT_OPENGL__

void										TexProject::OpenGL::Buffer::Frame::Create(Texture* texture_)
{
	auto prev = renderContext->GetCurrentBufferFrame();

	Delete();

	if(texture_ && texture_->GetType() == Texture::Type::D2)
	{
		color[0] = texture_; ownColor[0] = false;
		size = texture_->GetSize().xy();

		glGenFramebuffers(1,&buffer);
		glBindFramebuffer(GL_FRAMEBUFFER,buffer); renderContext->bufferFrameCurrent = this;

		glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,texture_->GetTexture(),0);
		//GL_DEPTH_ATTACHMENT
		//GL_STENCIL_ATTACHMENT
	}

	if(prev) prev->Use(); else renderContext->UnuseBufferFrame();
}
void										TexProject::OpenGL::Buffer::Frame::Delete()
{
	if(buffer)
	{
		Unuse();

		for(int32 i = 0; i < renderContext->GetBufferFrameMaxColorAttachment(); ++i)
		{
			if(color[i])
			{
				if(ownColor[i]) { delete color[i]; ownColor[i] = false; }
				color[i] = nullptr;
			}
		}

		if(depth)
		{
			if(ownDepth) { delete depth; ownDepth = false; }
			depth = nullptr;
		}

		if(stencil)
		{
			if(ownDepth) { delete stencil; ownStencil = false; }
			stencil = nullptr;
		}

		glDeleteFramebuffers(1,&buffer); buffer = 0;
	}
}


#endif





























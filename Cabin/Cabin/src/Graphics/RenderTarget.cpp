#include "Graphics/RenderTarget.h"
#include "Core/Debug.h"
#include <glad.h>

RenderTarget::RenderTarget() {}
RenderTarget::RenderTarget(int _width, int _height, RenderTargetType targetType, ColourChannels _textureChannels)
{
	Init(_width, _height, targetType, _textureChannels);
}
RenderTarget::~RenderTarget()
{
	_UnloadRenderTarget();
}
void RenderTarget::Unload()
{
	_UnloadRenderTarget();
	width = 0;
	height = 0;
	textureChannels = ColourChannels::RGB;
	type = RenderTargetType::Texture;
}

bool RenderTarget::Init(int _width, int _height, RenderTargetType targetType, ColourChannels _textureChannels)
{
	_UnloadRenderTarget();

	width = _width;
	height = _height;
	textureChannels = _textureChannels;
	type = targetType;

	int drawBufferCount = 0;
	unsigned int drawBuffers[2] = { 0 };

	// create framebuffer, contains main render texture and optional depthbuffer
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// the main render texture
	if (type & RenderTargetType::Texture)
	{
		unsigned int format = 0;
		if (textureChannels == ColourChannels::Grey) format = GL_RED;
		else if (textureChannels == ColourChannels::GreyAlpha) format = GL_RG;
		else if (textureChannels == ColourChannels::RGB) format = GL_RGB;
		else if (textureChannels == ColourChannels::RGBA) format = GL_RGBA;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, width, 0, format, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
		drawBuffers[drawBufferCount++] = GL_COLOR_ATTACHMENT0;
	}

	unsigned int internalFormat = 0;
	unsigned int attachmentType = 0;
	if (type & RenderTargetType::Depth && type & RenderTargetType::Stencil)
	{
		internalFormat = GL_DEPTH24_STENCIL8;
		attachmentType = GL_DEPTH_STENCIL_ATTACHMENT;
	}
	else if (type & RenderTargetType::Depth)
	{
		internalFormat = GL_DEPTH;
		attachmentType = GL_DEPTH_ATTACHMENT;
	}
	else if (type & RenderTargetType::Stencil)
	{
		internalFormat = GL_STENCIL;
		attachmentType = GL_STENCIL_ATTACHMENT;
	}
	if (internalFormat)
	{
		glGenRenderbuffers(1, &depthStencil);
		glBindRenderbuffer(GL_RENDERBUFFER, depthStencil);
		glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, depthStencil);
		glFramebufferTexture(GL_FRAMEBUFFER, attachmentType, depthStencil, 0);
		drawBuffers[drawBufferCount++] = attachmentType;
	}

	glDrawBuffers(drawBufferCount, drawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		ASSERT_MSG(false, "RenderTarget failed to generate framebuffer.");
		_UnloadRenderTarget();
		Unbind();
		return false;
	}

	Unbind();
	return true;
}

void RenderTarget::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, width, height);
}

void RenderTarget::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int RenderTarget::GetFramebufferId() const { return texture; }
unsigned int RenderTarget::GetTextureId() const { return texture; }
unsigned int RenderTarget::GetDepthStencilId() const { return depthStencil; }

int RenderTarget::GetWidth() const { return width; }
int RenderTarget::GetHeight() const { return height; }
ColourChannels RenderTarget::GetTextureChannels() const { return textureChannels; }
RenderTargetType RenderTarget::GetTargetType() const { return type; }

void RenderTarget::_UnloadRenderTarget()
{
	Unbind();

	if (framebuffer)
	{
		glDeleteFramebuffers(1, &framebuffer);
		framebuffer = 0;
	}
	if (texture)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}
	if (depthStencil)
	{
		glDeleteRenderbuffers(1, &depthStencil);
		depthStencil = 0;
	}
}

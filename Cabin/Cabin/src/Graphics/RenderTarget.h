#pragma once
#include "Graphics/ColourChannels.h"

enum RenderTargetType : char
{
	Texture = 0x01,
	Depth = 0x02,
	Stencil = 0x04,
};

class RenderTarget
{
public:
	RenderTarget();
	RenderTarget(const RenderTarget& that) = delete;
	RenderTarget(int _width, int _height, RenderTargetType targetType = RenderTargetType::Texture, ColourChannels _textureChannels = ColourChannels::RGB);
	~RenderTarget();
	void operator=(const RenderTarget& that) = delete;

	void Unload();

	bool Init(int _width, int _height, RenderTargetType targetType = RenderTargetType::Texture, ColourChannels _textureChannels = ColourChannels::RGB);
	void Bind() const;

	static void Unbind();
	unsigned int GetFramebufferId() const;
	unsigned int GetTextureId() const;
	unsigned int GetDepthStencilId() const;

	int GetWidth() const;
	int GetHeight() const;
	ColourChannels GetTextureChannels() const;
	RenderTargetType GetTargetType() const;

private:
	void _UnloadRenderTarget();

	unsigned int framebuffer = 0;
	unsigned int texture = 0;
	unsigned int depthStencil = 0;

	int width = 0;
	int height = 0;
	ColourChannels textureChannels = ColourChannels::RGB;
	RenderTargetType type = RenderTargetType::Texture;
};

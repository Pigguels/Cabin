#pragma once
#include "Data/RefManager.h"
#include "Graphics/Texture.h"

class TextureManager : public Internal::RefManager<Texture>
{
public:
	static TextureManager& GetInstance();

	/*
	Summary:
	Load an image from disk with the given filepath, and store it with the given handle.
	[Note: If a Texture exists with the given handle already, that Texture is returned]
	*/
	Ref LoadAs(const String& filepath, const String& handle);
	/*
	Summary:
	Load an image from disk with the given filepath, and store it with its handle being the given filepath.
	[Note: If a Texture exists with the given handle already, that Texture is returned]
	*/
	Ref Load(const String& filepath);

	/*
	Summary:
	Returns the Texture at the given handle.
	[Note: Returns the null Texture if there is no Texture with the given handle]
	*/
	Ref Get(const String& handle) const override;

private:
	TextureManager();
	~TextureManager();

	Ref nullTexture;
};
using TextureRef = TextureManager::Ref;

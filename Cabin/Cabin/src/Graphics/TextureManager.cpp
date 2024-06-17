#include "Graphics/TextureManager.h"

TextureManager::TextureManager() : Internal::RefManager<Texture>()
{
	nullTexture = _CreateRef("NULL_TEXTURE");
	//nullTexture->LoadImageFromDisk("null_texture.png");
}
TextureManager::~TextureManager() { nullTexture.DecRef(); }

TextureManager& TextureManager::GetInstance()
{
	static TextureManager* instance = new TextureManager();
	return *instance;
}

TextureRef TextureManager::Get(const String& handle) const
{
	Ref* ref = refs.TryGet(handle);
	return ref ? *ref : nullTexture;
}

TextureRef TextureManager::LoadAs(const String& filepath, const String& handle)
{
	TextureRef ref;
	if (!refs.TryGet(handle, ref))
	{
		ref = _CreateRef(handle);
		ref.Ref()->LoadImageFromDisk(filepath.c_str(), FilterType::Nearest); // maybe separate the image loading into its own file?
	}
	return ref;
}
TextureRef TextureManager::Load(const String& filepath)
{
	return LoadAs(filepath, filepath);
}

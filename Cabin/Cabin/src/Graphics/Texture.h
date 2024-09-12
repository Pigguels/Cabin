#pragma once
#include "Graphics/ColourChannels.h"

struct Colour;

enum class FilterType : int
{
	Nearest,
	Linear,
};

/*
Summary:
A base texture handler object.
Holds all texture data and handles uploading it to the gpu.
Easy access to bind and unbind loaded textures.
When using Textures directly, when to load and unload is up to the user.
*/
class Texture
{
public:
	Texture();
	Texture(const Texture& that) = delete;
	~Texture();

	void operator=(const Texture& that) = delete;

	bool Upload();
	bool Unload();

	void Bind(int textureIndex) const;
	void Unbind(int textureIndex) const;

	void ClearTexture();
	// this will handle the memory of the data that is passed in, be aware, also no data has to be passed in if the texture memory is going to be handled gpu side
	void CreateTexture(unsigned char* _imageData, int _width, int _height, ColourChannels _colourChannels, FilterType _filterType = FilterType::Nearest, bool _mipmaps = false);
	bool LoadImageFromDisk(const char* filePath, FilterType _filterType = FilterType::Nearest, bool _mipmaps = false);

	unsigned int GetPixel(int x, int y) const;
	void SetPixel(int x, int y, unsigned int colour);

	unsigned int GetTextureId() const;
	bool IsLoaded() const;
	int GetWidth() const;
	int GetHeight() const;
	ColourChannels GetColourType() const;
	FilterType GetFilterType() const;
	unsigned char* GetImageData() const;

private:
	void _ClearData();

	unsigned int texture = 0;
	int width = 0;
	int height = 0;
	ColourChannels colourChannels = ColourChannels::None;
	FilterType filterType = FilterType::Nearest;
	bool mipmaps = false;
	unsigned char* data = nullptr;
};

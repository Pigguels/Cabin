#include "Graphics/Texture.h"
#include "Graphics/Colour.h"
#include "Core/Debug.h"

//#define GLFW_INCLUDE_NONE
//#include <glfw3.h>
#include <glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
{
	width = 0;
	height = 0;
	colourChannels = ColourChannels::None;
	filterType = FilterType::Linear;
	mipmaps = false;
	data = nullptr;
}
Texture::~Texture()
{
	Unload();
	_ClearData();
}


bool Texture::Upload()
{
	/* Early out if the image is not loaded */
	if (!data)
	{
		DEBUG_MSG_WARNING("Texture failed to upload as it has no image data.");
		return false;
	}
	
	if (!texture) glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (colourChannels == ColourChannels::Grey) glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
	else if (colourChannels == ColourChannels::GreyAlpha) glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, data);
	else if (colourChannels == ColourChannels::RGB) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else if (colourChannels == ColourChannels::RGBA) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	if (mipmaps) glGenerateMipmap(GL_TEXTURE_2D);
	
	if (filterType == FilterType::Nearest)
	{
		if (mipmaps) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		else glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else if (filterType == FilterType::Linear)
	{
		if (mipmaps) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		else glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}
bool Texture::Unload()
{
	if (texture != 0)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
		return true;
	}
	return false;
}

void Texture::Bind(int textureIndex) const
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, texture);
}
void Texture::Unbind(int textureIndex) const
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D + textureIndex, 0);
}

void Texture::ClearTexture()
{
	if (texture != 0) Unload();

	width = 0;
	height = 0;
	colourChannels = ColourChannels::None;
	filterType = FilterType::Linear;
	mipmaps = false;

	_ClearData();
}

void Texture::CreateTexture(unsigned char* _imageData, int _width, int _height, ColourChannels _colourChannels, FilterType _filterType, bool _mipmaps)
{
	ClearTexture();
	width = _width;
	height = _height;
	colourChannels = _colourChannels;
	filterType = _filterType;
	mipmaps = _mipmaps;
	data = _imageData; // may want to mem copy, or just make sure the user is aware this is held

	Upload();
}

bool Texture::LoadImageFromDisk(const char* filePath, FilterType _filterType, bool _mipmaps)
{
	ClearTexture();

	filterType = _filterType;
	mipmaps = _mipmaps;

	data = stbi_load(filePath, &width, &height, &(int&)colourChannels, 0);

	if (!data)
	{
		DEBUG_MSG_WARNING("Failed to load image: " << filePath);
		ClearTexture();
		return false;
	}

	return Upload();
}

unsigned int Texture::GetPixel(int x, int y) const
{
	ASSERT_MSG((x > -1 && x < width && y > -1 && y < height), "Texture GetPixel coordinates out of range.");
	return (unsigned int&)data[(width * y + x) * (int)colourChannels] & (0xFFFFFFFF >> (32 - 8 * (int)colourChannels));
}
void Texture::SetPixel(int x, int y, unsigned int colour)
{
	ASSERT_MSG((x > -1 && x < width && y > -1 && y < height), "Texture SetPixel coordinates out of range.");

	// need to take another look at this since i really dont trust it to not write over neighboring pixels

	unsigned int mask = (0xFFFFFFFF >> (32 - 8 * (int)colourChannels));
	(unsigned int&)data[(width * y + x) * (int)colourChannels] = (colour & mask) | ((unsigned int&)data[(width * y + x) * (int)colourChannels] & ~mask);
}

GLuint Texture::GetTextureId() const { return texture; }
bool Texture::IsLoaded() const { return (texture != 0); }
int Texture::GetWidth() const { return width; }
int Texture::GetHeight() const { return height; }
ColourChannels Texture::GetColourType() const { return colourChannels; }
FilterType Texture::GetFilterType() const { return filterType; }
unsigned char* Texture::GetImageData() const { return data; }

void Texture::_ClearData()
{
	if (data)
	{
		free(data);
		data = nullptr;
	}
}

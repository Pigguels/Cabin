#include "Graphics/Colour.h"

Colour::Colour()
{
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
}
Colour::Colour(unsigned int colour)
{
	r = GetRed(colour) * ByteToFloat;
	g = GetGreen(colour) * ByteToFloat;
	b = GetBlue(colour) * ByteToFloat;
	a = GetAlpha(colour) * ByteToFloat;
}
Colour::Colour(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

bool Colour::operator==(const Colour& that)
{
	return (r == that.r && g == that.g && b == that.b && a == that.a);
}
bool Colour::operator!=(const Colour& that)
{
	return !(*this == that);
}

unsigned int Colour::ToNumber() const
{
	return (((int)(r * FloatToByte)) | ((int)(g * FloatToByte) << 8) | ((int)(b * FloatToByte) << 16) | ((int)(a * FloatToByte) << 24));
}

unsigned char Colour::GetRed(unsigned int colour) { return (colour & BitMaskRed); }
unsigned char Colour::GetGreen(unsigned int colour) { return (colour & BitMaskGreen) >> 8; }
unsigned char Colour::GetBlue(unsigned int colour) { return (colour & BitMaskBlue) >> 16; }
unsigned char Colour::GetAlpha(unsigned int colour) { return (colour & BitMaskAlpha) >> 24; }

const float Colour::ByteToFloat = 0.00392157f;
const float Colour::FloatToByte = 255.0f;

const unsigned int Colour::BitMaskRed = 0x000000FF;
const unsigned int Colour::BitMaskGreen = 0x0000FF00;
const unsigned int Colour::BitMaskBlue = 0x00FF0000;
const unsigned int Colour::BitMaskAlpha = 0xFF000000;

const Colour Colour::transparent = {0.0f, 0.0f, 0.0f, 0.0f};
const Colour Colour::red = {1.0f, 0.0f, 0.0f, 1.0f};
const Colour Colour::green = {0.0f, 1.0f, 0.0f, 1.0f};
const Colour Colour::blue = {0.0f, 0.0f, 1.0f, 1.0f};
const Colour Colour::white = {1.0f, 1.0f, 1.0f, 1.0f};
const Colour Colour::lightGrey = {0.75f, 0.75f, 0.75f, 1.0f};
const Colour Colour::grey = {0.5f, 0.5f, 0.5f, 1.0f};
const Colour Colour::darkGrey = {0.25f, 0.25f, 0.25f, 1.0f};
const Colour Colour::black = {0.0f, 0.0f, 0.0f, 1.0f};
const Colour Colour::magenta = {1.0f, 0.0f, 1.0f, 1.0f};

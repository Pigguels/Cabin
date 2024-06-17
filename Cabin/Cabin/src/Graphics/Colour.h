#pragma once

struct Colour
{
public:
	Colour();
	Colour(unsigned int colour);
	Colour(float r, float g, float b, float a);

	bool operator==(const Colour& that);
	bool operator!=(const Colour& that);

	/*
	Summary:
	Returns this Colour converted to a number colour
	*/
	unsigned int ToNumber() const;

	/*
	Summary:
	Returns the red value of a number colour
	*/
	static unsigned char GetRed(unsigned int colour);
	/*
	Summary:
	Returns the green value of a number colour
	*/
	static unsigned char GetGreen(unsigned int colour);
	/*
	Summary:
	Returns the blue value of a number colour
	*/
	static unsigned char GetBlue(unsigned int colour);
	/*
	Summary:
	Returns the alpha value of a number colour
	*/
	static unsigned char GetAlpha(unsigned int colour);

	/* Converts a 0-255 range to a 0-1 range */
	static const float ByteToFloat;
	/* Converts a 0-1 range to a 0-255 range */
	static const float FloatToByte;

	/* Bit mask for getting only the red value from a byte */
	static const unsigned int BitMaskRed;
	/* Bit mask for getting only the green value from a byte */
	static const unsigned int BitMaskGreen;
	/* Bit mask for getting only the blue value from a byte */
	static const unsigned int BitMaskBlue;
	/* Bit mask for getting only the alpha value from a byte */
	static const unsigned int BitMaskAlpha;

	static const Colour transparent;
	static const Colour red;
	static const Colour green;
	static const Colour blue;
	static const Colour white;
	static const Colour lightGrey;
	static const Colour grey;
	static const Colour darkGrey;
	static const Colour black;
	static const Colour magenta;

	float r;
	float g;
	float b;
	float a;
};

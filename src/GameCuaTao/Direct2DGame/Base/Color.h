#pragma once

#include <string>

struct Color
{
public:
	Color(int r, int g, int b);
	Color(int r, int g, int b, int alpha);

	unsigned long Get();

	int A();
	int R();
	int G();
	int B();

	std::string ToString();

	static Color Transparent();
	static Color White();
	static Color Black();
	static Color LavenderBlue();

	Color operator*(float scale);

	static Color FromHex(std::string hexColor);

private:
	unsigned long packedValue;
};
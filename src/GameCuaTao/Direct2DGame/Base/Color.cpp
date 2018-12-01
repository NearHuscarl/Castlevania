#include <sstream>
#include "../Direct3D9.h"
#include "Color.h"

Color::Color(int r, int g, int b) : Color{ r, g, b, 255 }
{
}

Color::Color(int r, int g, int b, int alpha)
{
	packedValue = D3DCOLOR_RGBA(r, g, b, alpha);
}

unsigned long Color::Get()
{
	return packedValue;
}

int Color::A()
{
	return (packedValue & 0xFF000000) >> 24;
}

int Color::R()
{
	return (packedValue & 0x00FF0000) >> 16;
}

int Color::G()
{
	return (packedValue & 0x0000FF00) >> 8;
}

int Color::B()
{
	return (packedValue & 0x000000FF);
}

std::string Color::ToString()
{
	auto strStream = std::stringstream{};

	strStream
		<< "{R: "
		<< R()
		<< " G:"
		<< G()
		<< " B:"
		<< B()
		<< " A:"
		<< A()
		<< "}";

	return strStream.str();
}

Color Color::Transparent()
{
	static auto transparent = Color{ 255, 255, 255, 0 };
	return transparent;
}

Color Color::Black()
{
	static auto black = Color{ 0, 0, 0 };
	return black;
}

Color Color::Blue()
{
	static auto blue = Color{ 0, 0, 255 };
	return blue;
}

Color Color::Green()
{
	static auto green = Color{ 0, 128, 0 };
	return green;
}

Color Color::LavenderBlue()
{
	static auto lavenderBlue = Color{ 200, 200, 255 };
	return lavenderBlue;
}

Color Color::Magenta()
{
	static auto magenta = Color{ 255, 0, 255 };
	return magenta;
}

Color Color::Red()
{
	static auto red = Color{ 255, 0, 0 };
	return red;
}

Color Color::White()
{
	static auto white = Color{ 255, 255, 255 };
	return white;
}

Color Color::operator*(float scale)
{
	return Color{
		(int)(R() * scale),
		(int)(G() * scale),
		(int)(B() * scale),
		(int)(A() * scale) };
}

Color Color::FromHex(std::string hexColor)
{
	if (hexColor.empty())
		return Color{ 0, 0, 0 };

	if (hexColor[0] == '#')
		hexColor.erase(0, 1);

	auto r = std::stoi(hexColor.substr(0, 2), nullptr, 16);
	auto g = std::stoi(hexColor.substr(2, 2), nullptr, 16);
	auto b = std::stoi(hexColor.substr(4, 2), nullptr, 16);
	auto a = 255;

	if (hexColor.length() == 8)
		a = std::stoi(hexColor.substr(6, 2), nullptr, 16);

	return Color{ r, g, b, a };
}
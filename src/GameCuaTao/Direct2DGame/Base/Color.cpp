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

Color Color::DimGray()
{
	static auto dimGray = Color{ 105, 105, 105 };
	return dimGray;
}

Color Color::Gold()
{
	static auto gold = Color{ 255, 215, 0 };
	return gold;
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

Color Color::Orange()
{
	static auto orange = Color{ 255, 165, 0 };
	return orange;
}

Color Color::Orchid()
{
	static auto orchid = Color{ 218, 112, 214 };
	return orchid;
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

Color Color::YellowGreen()
{
	static auto yellowGreen = Color{ 154, 205, 50 };
	return yellowGreen;
}

Color Color::operator*(float scale)
{
	return Color{
		(int)(R() * scale),
		(int)(G() * scale),
		(int)(B() * scale),
		(int)(A() * scale) };
}

bool Color::operator==(Color other)
{
	return this->packedValue == other.packedValue;
}

bool Color::operator!=(Color other)
{
	return !(*this == other);
}

Color Color::FromRgb(std::string rgb)
{
	if (rgb.empty())
		return Color{ 0, 0, 0 };

	if (rgb[0] == '#')
		rgb.erase(0, 1);

	auto r = std::stoi(rgb.substr(0, 2), nullptr, 16);
	auto g = std::stoi(rgb.substr(2, 2), nullptr, 16);
	auto b = std::stoi(rgb.substr(4, 2), nullptr, 16);
	auto a = 255;

	if (rgb.length() == 8)
		a = std::stoi(rgb.substr(6, 2), nullptr, 16);

	return Color{ r, g, b, a };
}

Color Color::FromArgb(std::string argb)
{
	if (argb.empty())
		return Color{ 0, 0, 0 };

	if (argb[0] == '#')
		argb.erase(0, 1);

	auto a = std::stoi(argb.substr(0, 2), nullptr, 16);
	auto r = std::stoi(argb.substr(2, 2), nullptr, 16);
	auto g = std::stoi(argb.substr(4, 2), nullptr, 16);
	auto b = std::stoi(argb.substr(6, 2), nullptr, 16);

	return Color{ r, g, b, a };
}
#pragma once

#include <d3dx9.h>
#include <string>
#include <sstream>

struct Color
{
public:
	Color(int r, int g, int b)
	{
		packedValue = D3DCOLOR_XRGB(r, g, b);
	}

	Color(int r, int g, int b, int alpha)
	{
		packedValue = D3DCOLOR_RGBA(r, g, b, alpha);
	}

	unsigned long Get()
	{
		return packedValue;
	}

	int A()
	{
		return (packedValue & 0xFF000000) >> 24;
	}

	int R()
	{
		return (packedValue & 0x00FF0000) >> 16;
	}

	int G()
	{
		return (packedValue & 0x0000FF00) >> 8;
	}

	int B()
	{
		return (packedValue & 0x000000FF);
	}

	std::string ToString()
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

private:
	unsigned long packedValue;
};
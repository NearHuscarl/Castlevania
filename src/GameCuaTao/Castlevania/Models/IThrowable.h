#pragma once

#include "Direct2DGame/Base/Rect.h"

namespace Castlevania
{
	class IThrowable
	{
	public:
		virtual void Throw(Rect moveArea) = 0;
		virtual ~IThrowable() {};
	};
}
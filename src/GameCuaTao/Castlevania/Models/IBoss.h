#pragma once

#include "Direct2DGame/Base/Rect.h"

namespace Castlevania
{
	class IBoss
	{
	public:
		virtual void SetActive() = 0;
		virtual Rect GetMoveArea() = 0;
		virtual void SetMoveArea(Rect moveArea) = 0;

		virtual ~IBoss() {};
	};
}
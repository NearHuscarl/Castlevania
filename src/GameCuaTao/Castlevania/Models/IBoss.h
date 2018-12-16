#pragma once

namespace Castlevania
{
	class IBoss
	{
	public:
		virtual void SetActive() = 0;
		virtual ~IBoss() {};
	};
}
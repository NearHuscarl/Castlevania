#pragma once

namespace Castlevania
{
	class IReceiver
	{
	public:
		virtual void Receive(int message) = 0;
	};
}
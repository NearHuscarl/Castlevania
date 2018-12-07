#pragma once

namespace Castlevania
{
	class IAttackable
	{
	public:
		virtual int GetAttack() = 0;
		virtual void SetAttack(int attack) = 0;
	};
}
#include "Facing.h"

using namespace Castlevania;

Facing Castlevania::Opposite(Facing facing)
{
	if (facing == Facing::Left)
		return Facing::Right;
	else
		return Facing::Left;
}

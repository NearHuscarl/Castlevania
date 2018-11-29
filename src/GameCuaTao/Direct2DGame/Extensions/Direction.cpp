#include "Direction.h"

Direction Opposite(Direction input)
{
	{
		switch (input)
		{
			case Direction::Left:
				return Direction::Right;

			case Direction::Top:
				return Direction::Bottom;

			case Direction::Right:
				return Direction::Left;

			case Direction::Bottom:
				return Direction::Top;

			default:
				return Direction::None;
		}
	}
}

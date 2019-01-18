#include "Direct2DGame/MathHelper.h"
#include "Direct2DGame/Utilities/CppExtensions.h"
#include "Health.h"

using namespace Castlevania;

constexpr auto UPDATE_TIME = 150;

Health::Health() : Health{ 0 }
{
}

Health::Health(int value)
{
	currentHealth = value;
	maxHealth = value;
	addedHealth = 0;
}

int Health::Value() const
{
	return currentHealth;
}

bool Health::IsEmpty()
{
	return currentHealth == 0;
}

void Health::Add(int value)
{
	healthStack.push(value);
}

void Health::Set(int value)
{
	currentHealth = value;
}

void Health::Update()
{
	if (updateTimer.IsRunning() && updateTimer.ElapsedMilliseconds() >= UPDATE_TIME)
	{
		if (addedHealth > 0)
		{
			addedHealth--;
			currentHealth = MathHelper::Min(++currentHealth, maxHealth);
			updateTimer.Restart();
		}
		else if (addedHealth < 0)
		{
			addedHealth++;
			currentHealth = MathHelper::Max(--currentHealth, 0);
			updateTimer.Restart();
		}
		else // (addedHealth == 0)
			updateTimer.Reset();
	}
	else if (!healthStack.empty())
	{
		addedHealth = Pop(healthStack);
		updateTimer.Start();
	}
}

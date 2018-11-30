#include "Subject.h"

using namespace Castlevania;

void Subject::AddObserver(IObserver &observer)
{
	observers.push_back(&observer);
}

void Subject::RemoveObserver(IObserver &observer)
{
	auto it = std::find(observers.begin(), observers.end(), &observer);

	if (it != observers.end())
	{
		observers.erase(it);
	}
}

void Subject::Notify(int event)
{
	for (auto &observer : observers)
	{
		observer->OnNotify(*this, event);
	}
}

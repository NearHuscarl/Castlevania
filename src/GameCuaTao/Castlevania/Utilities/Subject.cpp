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

Subject Subject::Empty()
{
	static auto emptySubject = Subject{};
	return emptySubject;
}

void Subject::Notify(int event)
{
	for (auto &observer : observers)
	{
		observer->OnNotify(*this, event);
	}
}

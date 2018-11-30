#pragma once

#include <vector>
#include "IObserver.h"

namespace Castlevania
{
	class Subject
	{
	public:
		void AddObserver(IObserver &observer);
		void RemoveObserver(IObserver &observer);

	protected:
		void Notify(int event);

	private:
		std::vector<IObserver*> observers;
	};
}
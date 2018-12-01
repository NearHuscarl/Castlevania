#include "UpdateData.h"

using namespace Castlevania;

UpdateData UpdateData::Empty()
{
	static auto emptyData = UpdateData{};
	return emptyData;
}

#include "Core/Types.h"

namespace Internal
{
	u32 next_id()
	{
		static u32 next(0);
		return ++next;
	}
}
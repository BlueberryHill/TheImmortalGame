#pragma once

#include "ThreadSafeCounter.h"

namespace EntityUtility
{
	template <typename T>
	int32 CreateNextUniqueID() {
		static FThreadSafeCounter ID{ 0 };
		return ID.Increment();
	}

}

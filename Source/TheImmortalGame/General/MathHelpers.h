#include "Platform.h"

namespace Maths
{
	bool IsEven(int32 n) { return (n % 2) == 0; }
	bool IsOdd(int32 n) { return !IsEven(n); }
};
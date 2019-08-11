#pragma once

#include <type_traits>

namespace TIG
{
	//template <typename EnumClass>
	//constexpr typename std::underlying_type_t<EnumClass> enum_to_value(EnumClass Enum)
	//{
	//	return static_cast<typename std::underlying_type_t<EnumClass>(Enum);
	//}

	template<typename E>
	constexpr auto enum_to_value(E e) -> typename std::underlying_type<E>::type
	{
		return static_cast<typename std::underlying_type<E>::type>(e);
	}
}
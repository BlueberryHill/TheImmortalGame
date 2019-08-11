#pragma once

#include "Containers/Map.h"

namespace TIG
{
	template <typename T1, typename T2>
	class BiMap
	{
	public:
		void AddPair(const T1& A, const T2& B);
		const T2& Get(const T1& A) const;
		const T1& Get(const T2& B) const;

	private:
		TMap<T1, T2> ABMap;
		TMap<T2, T1> BAMap;
	};
}
#pragma once

template<typename T1, typename T2>
struct Pair {
	T1 first;
	T2 second;

	Pair() = default;
	Pair(const T1& a, const T2& b) : first(a), second(b) {};

	bool operator==(const Pair& o) const {
		return first == o.first && second == o.second;
	}

	bool operator!=(const Pair& o) const {
		return !(*this == o);
	}
};

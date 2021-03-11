#pragma once
#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

namespace Violet {
	template <typename T>
	constexpr T min(T lhs, T rhs) { return lhs < rhs ? lhs : rhs; }
	template <typename T>
	constexpr T max(T lhs, T rhs) { return lhs > rhs ? lhs : rhs; }
	template <typename T>
	constexpr T clamp(T x, T ub, T lb) { return min(ub, max(x, lb)); }
};
#endif
#ifndef _TI83RC_UTIL_H
#define _TI83RC_UTIL_H

template <typename T>
inline T max(const T& a, const T& b) {
	return a > b ? a : b;
}
template <typename T>
inline T min(const T& a, const T& b) {
	return a < b ? a : b;
}

#endif

#pragma once

#include <stdint.h>

#if defined(_MSC_VER)
#include <intrin.h>

static inline unsigned int ctz32(uint32_t x) {
  unsigned long index;
  _BitScanForward(&index, x);
  return (unsigned int)index;
}

static inline unsigned int popcount32(uint32_t x) { return __popcnt(x); }

#else

static inline unsigned int ctz32(uint32_t x) { return __builtin_ctz(x); }

static inline unsigned int popcount32(uint32_t x) {
  return __builtin_popcount(x);
}

#endif

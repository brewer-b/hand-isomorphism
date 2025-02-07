#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HandIsomorphism HandIsomorphism;

typedef enum {
  RECALL_PERFECT = 0,
  RECALL_IMPERFECT = 1,
  RECALL_FLOP = 2,
  RECALL_PUBLIC_BOARD = 3
} Recall;

HandIsomorphism *hand_isomorphism_create(uint8_t numHoleCards, Recall recall);
void hand_isomorphism_destroy(HandIsomorphism *handle);

uint64_t hand_isomorphism_size(const HandIsomorphism *handle, int round);
uint64_t hand_isomorphism_index(const HandIsomorphism *handle, int round,
                                const uint8_t *cards);
bool hand_isomorphism_unindex(const HandIsomorphism *handle, int round,
                              uint64_t index, uint8_t *output);

#ifdef __cplusplus
}
#endif

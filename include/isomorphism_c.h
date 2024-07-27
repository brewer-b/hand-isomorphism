#ifndef HAND_ISOMORPHISM_C_H
#define HAND_ISOMORPHISM_C_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HandIsomorphism HandIsomorphism;

HandIsomorphism* HandIsomorphism_create(const uint8_t** cards_per_round, size_t* sizes, size_t num_rounds);
void HandIsomorphism_destroy(HandIsomorphism* hi);

uint64_t HandIsomorphism_size(HandIsomorphism* hi, int round);
uint64_t HandIsomorphism_index(HandIsomorphism* hi, int round, const uint8_t* cards);
bool HandIsomorphism_unindex(HandIsomorphism* hi, int round, uint64_t index, uint8_t* output);

#ifdef __cplusplus
}
#endif

#endif // HAND_ISOMORPHISM_C_H
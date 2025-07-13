#pragma once

#include <stdint.h>

typedef struct HandIsomorphism HandIsomorphism;

void iso_init(void);

const HandIsomorphism *iso_get_imperfect_indexer(void);

uint64_t iso_size(const HandIsomorphism *indexer, uint64_t round);

uint64_t iso_index(const HandIsomorphism *indexer, uint64_t round, const uint8_t *cards);

void iso_unindex(const HandIsomorphism *indexer, uint64_t round, uint64_t index, uint8_t *output);
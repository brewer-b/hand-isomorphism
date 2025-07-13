#include "hand-isomorphism/hand-isomorphism.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "hand_index.h"

typedef struct HandIsomorphism
{
    hand_indexer_t indexers[MAX_ROUNDS];
    uint32_t rounds[MAX_ROUNDS];
} HandIsomorphism;

HandIsomorphism *imperfect_indexer;

void iso_init(void)
{
    static bool init = false;
    if (init)
        return;
    hand_index_ctor();
    imperfect_indexer = calloc(1, sizeof(*imperfect_indexer));
    if (!imperfect_indexer)
    {
        fprintf(stderr, "Failed to allocated imperfect indexer\n");
        exit(EXIT_FAILURE);
    }
    hand_indexer_init(1, (uint8_t[]){2}, &imperfect_indexer->indexers[0]);
    imperfect_indexer->rounds[0] = 1;
    hand_indexer_init(2, (uint8_t[]){2, 3}, &imperfect_indexer->indexers[1]);
    imperfect_indexer->rounds[1] = 2;
    hand_indexer_init(2, (uint8_t[]){2, 4}, &imperfect_indexer->indexers[2]);
    imperfect_indexer->rounds[2] = 2;
    hand_indexer_init(2, (uint8_t[]){2, 5}, &imperfect_indexer->indexers[3]);
    imperfect_indexer->rounds[3] = 2;
}

const HandIsomorphism *iso_get_imperfect_indexer(void)
{
    return imperfect_indexer;
}

uint64_t iso_size(const HandIsomorphism *indexer, uint64_t round)
{
    assert(indexer);
    return hand_indexer_size(&indexer->indexers[round], indexer->rounds[round] - 1);
}

uint64_t iso_index(const HandIsomorphism *indexer, uint64_t round, const uint8_t *cards)
{
    assert(indexer);
    return hand_index_last(&indexer->indexers[round], cards);
}

void iso_unindex(const HandIsomorphism *indexer, uint64_t round, uint64_t index, uint8_t *output)
{
    bool result = hand_unindex(&indexer->indexers[round], indexer->rounds[round] - 1, index, output);
    assert(result);
}
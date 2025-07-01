#include "hand_isomorphism/hand_isomorphism.h"

extern "C"
{
#include "hand_index.h"
}

#include <cassert>

HandIsomorphism::HandIsomorphism(std::vector<std::vector<uint8_t>> cards_per_round) : cards_per_round_(cards_per_round)
{
    hand_index_ctor();
    size_t num_rounds = cards_per_round.size();
    indexers.resize(num_rounds);
    for (size_t i = 0; i < num_rounds; i++)
    {
        indexers[i] = malloc(sizeof(hand_indexer_t));
        bool result = hand_indexer_init(cards_per_round[i].size(), cards_per_round[i].data(), (hand_indexer_t *)indexers[i]);
        assert(result);
    }
}

HandIsomorphism::~HandIsomorphism()
{
    for (size_t i = 0; i < indexers.size(); i++)
    {
        hand_indexer_free((hand_indexer_t *)indexers[i]);
        free(indexers[i]);
        indexers[i] = NULL;
    }
}

uint64_t HandIsomorphism::size(uint64_t round) const
{
    return hand_indexer_size((hand_indexer_t *)indexers[round], cards_per_round_[round].size() - 1);
}

uint64_t HandIsomorphism::index(uint64_t round, const uint8_t *cards) const
{
    return hand_index_last((hand_indexer_t *)indexers[round], cards);
}

void HandIsomorphism::unindex(uint64_t round, uint64_t idx, uint8_t *output) const
{
    bool result = hand_unindex((hand_indexer_t *)indexers[round], cards_per_round_[round].size() - 1, idx, output);
    assert(result);
}

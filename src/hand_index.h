/**
 * hand_index.h
 *
 * @author Kevin Waugh (waugh@cs.cmu.edu)
 * @date April 13, 2013
 * 
 * map poker hands to an index shared by all isomorphic hands, and
 * map an index to a canonical poker hand
 */

#ifndef _HAND_INDEX_H_
#define _HAND_INDEX_H_

#include <cstdint>
#include <functional>

#define MAX_ROUNDS           8

typedef uint64_t hand_index_t;
typedef struct hand_indexer_s hand_indexer_t;
typedef struct hand_indexer_state_s hand_indexer_state_t;

#define PRIhand_index        PRIu64

#define MAX_GROUP_INDEX        0x100000 
#define MAX_CARDS_PER_ROUND    15
#define ROUND_SHIFT            4
#define ROUND_MASK             0xf
#define SUITS     4
#define RANKS    13
#define CARDS    52

class HandIndexer {
public:
    HandIndexer();
    ~HandIndexer();
    bool hand_indexer_init(uint_fast32_t rounds, const uint8_t cards_per_round[], hand_indexer_t * indexer);
    void hand_indexer_free(hand_indexer_t * indexer);
    hand_index_t hand_indexer_size(const hand_indexer_t * indexer, uint_fast32_t round);
    hand_index_t hand_index_all(const hand_indexer_t * indexer, const uint8_t cards[], hand_index_t indices[]);
    hand_index_t hand_index_last(const hand_indexer_t * indexer, const uint8_t cards[]);
    hand_index_t hand_index_next_round(const hand_indexer_t * indexer, const uint8_t cards[], hand_indexer_state_t * state);
    bool hand_unindex(const hand_indexer_t * indexer, uint_fast32_t round, hand_index_t index, uint8_t cards[]);

private:
    uint8_t (*nth_unset)[RANKS];
    bool (*equal)[SUITS];
    uint_fast32_t (*nCr_ranks)[RANKS + 1];
    uint_fast32_t *rank_set_to_index;
    uint_fast32_t (*index_to_rank_set)[1 << RANKS];
    uint_fast32_t (*suit_permutations)[SUITS];
    hand_index_t (*nCr_groups)[SUITS + 1];

    void hand_index_ctor();
    void hand_index_dtor();

    void enumerate_configurations_r(uint_fast32_t rounds, const uint8_t cards_per_round[], uint_fast32_t round, uint_fast32_t remaining, uint_fast32_t suit, uint_fast32_t equal, uint_fast32_t used[], uint_fast32_t configuration[], std::function<void(uint_fast32_t, uint_fast32_t*, void*)> observe, void * data);
    void enumerate_configurations(uint_fast32_t rounds, const uint8_t *cards_per_round, std::function<void(uint_fast32_t, uint_fast32_t*, void*)> observe, void* data);
    void count_configurations(uint_fast32_t round, uint_fast32_t configuration[], void * data);
    void tabulate_configurations(uint_fast32_t round, uint_fast32_t configuration[], void * data);

    void enumerate_permutations_r(uint_fast32_t rounds, const uint8_t cards_per_round[], uint_fast32_t round, uint_fast32_t remaining, uint_fast32_t suit, uint_fast32_t used[], uint_fast32_t count[], std::function<void(uint_fast32_t, uint_fast32_t*, void*)> observe, void * data);
    void enumerate_permutations(uint_fast32_t rounds, const uint8_t cards_per_round[], std::function<void(uint_fast32_t, uint_fast32_t*, void*)> observe, void * data);
    void count_permutations(uint_fast32_t round, uint_fast32_t count[], void * data);
    void tabulate_permutations(uint_fast32_t round, uint_fast32_t count[], void * data);

    void hand_indexer_state_init(const hand_indexer_t * indexer, hand_indexer_state_t * state);
};

#include "hand_index-impl.h"


#endif /* _HAND_INDEX_H_ */

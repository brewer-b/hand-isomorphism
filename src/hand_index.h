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

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include "deck.h"

#define MAX_ROUNDS           8

typedef uint64_t hand_index_t;
typedef struct hand_indexer_s hand_indexer_t;
typedef struct hand_indexer_state_s hand_indexer_state_t;

#define PRIhand_index        PRIu64

typedef struct indexer_helper_t {
    uint8_t (*nth_unset)[RANKS];
    bool (*equal)[SUITS];
    uint32_t (*nCr_ranks)[RANKS+1];
    uint32_t *rank_set_to_index;
    uint32_t (*index_to_rank_set)[1<<RANKS];
    hand_index_t (*nCr_groups)[SUITS+1];
    uint32_t (*suit_permutations)[SUITS]; 
} indexer_helper_t;

/**
 * Initializes and allocates memory for hand indexing lookup tables.
 * @return A structure with initialized lookup tables for hand indexing.
 */
indexer_helper_t* indexer_helper_ctor();

/**
 * Frees all memory allocated by the indexer_helper_ctor function.
 * @param poker_data Pointer to the structure to be destroyed.
 */
void indexer_helper_dtor(indexer_helper_t* poker_data);

/**
 * Initialize a hand indexer.  This generates a number of lookup tables and is relatively
 * expensive compared to indexing a hand.
 *
 * @param rounds number of rounds
 * @param cards_per_round number of cards in each round
 * @param indexer 
 */
bool hand_indexer_init(const indexer_helper_t* poker_data, uint32_t rounds, const uint8_t cards_per_round[], hand_indexer_t * indexer);

/**
 * Free a hand indexer.
 *
 * @param indexer
 */
void hand_indexer_free(hand_indexer_t * indexer);

/**
 * @param indexer
 * @param round 
 * @returns size of index for hands on round
 */
hand_index_t hand_indexer_size(const hand_indexer_t * indexer, uint32_t round);

/**
 * Initialize a hand index state.  This is used for incrementally indexing a hand as
 * new rounds are dealt and determining if a hand is canonical.
 *
 * @param indexer
 * @param state
 */
void hand_indexer_state_init(const hand_indexer_t * indexer, hand_indexer_state_t * state);

/**
 * Index a hand on every round.  This is not more expensive than just indexing the last round.
 *
 * @param indexer
 * @param cards
 * @param indices
 * @returns hand's index on the last round
 */
hand_index_t hand_index_all(const indexer_helper_t* poker_data, const hand_indexer_t * indexer, const uint8_t cards[], uint64_t indices[]);

/**
 * Index a hand on the last round.
 *
 * @param indexer
 * @param cards
 * @returns hand's index on the last round
 */
hand_index_t hand_index_last(const indexer_helper_t* poker_data, const hand_indexer_t * indexer, const uint8_t cards[]);

/**
 * Incrementally index the next round.
 * 
 * @param indexer
 * @param cards the cards for the next round only!
 * @param state
 * @returns the hand's index at the latest round
 */
hand_index_t hand_index_next_round(const indexer_helper_t* poker_data, const hand_indexer_t * indexer, const uint8_t cards[], hand_indexer_state_t * state);

/**
 * Recover the canonical hand from a particular index.
 *
 * @param indexer
 * @param round
 * @param index
 * @param cards
 * @returns true if successful
 */
bool hand_unindex(const indexer_helper_t* poker_data, const hand_indexer_t * indexer, uint32_t round, uint64_t index, uint8_t cards[]);

#include "hand_index-impl.h"


#endif /* _HAND_INDEX_H_ */

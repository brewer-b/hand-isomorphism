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

#include "deck.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_ROUNDS 8

typedef uint64_t hand_index_t;
typedef struct hand_indexer_s hand_indexer_t;
typedef struct hand_indexer_state_s hand_indexer_state_t;

#define PRIhand_index PRIu64

void hand_index_ctor();

/**
 * Initialize a hand indexer.  This generates a number of lookup tables and
 * is relatively expensive compared to indexing a hand.
 *
 * @param rounds number of rounds
 * @param cards_per_round number of cards in each round
 * @param indexer
 */
bool hand_indexer_init(uint32_t rounds, const uint8_t cards_per_round[],
                       hand_indexer_t *indexer);

/**
 * Free a hand indexer.
 *
 * @param indexer
 */
void hand_indexer_free(hand_indexer_t *indexer);

/**
 * @param indexer
 * @param round
 * @returns size of index for hands on round
 */
hand_index_t hand_indexer_size(const hand_indexer_t *indexer, uint32_t round);

/**
 * Initialize a hand index state.  This is used for incrementally indexing a
 * hand as new rounds are dealt and determining if a hand is canonical.
 *
 * @param indexer
 * @param state
 */
void hand_indexer_state_init(const hand_indexer_t *indexer,
                             hand_indexer_state_t *state);

/**
 * Index a hand on every round.  This is not more expensive than just indexing
 * the last round.
 *
 * @param indexer
 * @param cards
 * @param indices
 * @returns hand's index on the last round
 */
hand_index_t hand_index_all(const hand_indexer_t *indexer,
                            const uint8_t cards[], hand_index_t indices[]);

/**
 * Index a hand on the last round.
 *
 * @param indexer
 * @param cards
 * @returns hand's index on the last round
 */
hand_index_t hand_index_last(const hand_indexer_t *indexer,
                             const uint8_t cards[]);

/**
 * Incrementally index the next round.
 *
 * @param indexer
 * @param cards the cards for the next round only!
 * @param state
 * @returns the hand's index at the latest round
 */
hand_index_t hand_index_next_round(const hand_indexer_t *indexer,
                                   const uint8_t cards[],
                                   hand_indexer_state_t *state);

/**
 * Recover the canonical hand from a particular index.
 *
 * @param indexer
 * @param round
 * @param index
 * @param cards
 * @returns true if successful
 */
bool hand_unindex(const hand_indexer_t *indexer, uint32_t round,
                  hand_index_t index, uint8_t cards[]);

struct hand_indexer_s {
  uint8_t cards_per_round[MAX_ROUNDS], round_start[MAX_ROUNDS];
  uint32_t rounds, configurations[MAX_ROUNDS], permutations[MAX_ROUNDS];
  hand_index_t round_size[MAX_ROUNDS];

  uint32_t *permutation_to_configuration[MAX_ROUNDS],
      *permutation_to_pi[MAX_ROUNDS], *configuration_to_equal[MAX_ROUNDS];
  uint32_t (*configuration[MAX_ROUNDS])[NUM_SUITS];
  uint32_t (*configuration_to_suit_size[MAX_ROUNDS])[NUM_SUITS];
  hand_index_t *configuration_to_offset[MAX_ROUNDS];
};

struct hand_indexer_state_s {
  uint32_t suit_index[NUM_SUITS];
  uint32_t suit_multiplier[NUM_SUITS];
  uint32_t round, permutation_index, permutation_multiplier;
  uint32_t used_ranks[NUM_SUITS];
};

#endif /* _HAND_INDEX_H_ */

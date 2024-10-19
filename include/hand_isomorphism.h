#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

// Opaque type declarations
typedef struct indexer_helper_t indexer_helper_t;
typedef struct hand_indexer_t hand_indexer_t;
typedef struct hand_indexer_state_t hand_indexer_state_t;

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
 * Initializes a hand indexer with lookup tables for the specified rounds and cards.
 * @param rounds Number of rounds.
 * @param cards_per_round Number of cards in each round.
 * @param indexer Pointer to the indexer.
 * @return true if successful, false otherwise.
 */
hand_indexer_t* hand_indexer_init(const indexer_helper_t* poker_data, uint32_t rounds, const uint8_t cards_per_round[]);

/**
 * Frees a hand indexer and its associated memory.
 * @param indexer Pointer to the indexer.
 */
void hand_indexer_free(hand_indexer_t* indexer);

/**
 * Returns the size of the index for hands in the specified round.
 * @param indexer Pointer to the indexer.
 * @param round The round number.
 * @return Size of the hand index for the specified round.
 */
uint64_t hand_indexer_size(const hand_indexer_t * indexer, uint32_t round);

/**
 * Indexes a hand on all rounds and returns the hand's index on the last round.
 * @param poker_data Pointer to the helper data.
 * @param indexer Pointer to the indexer.
 * @param cards Array of cards.
 * @param indices Array to store the indices for each round.
 * @return Hand's index on the last round.
 */
uint64_t hand_index_all(const indexer_helper_t* poker_data, const hand_indexer_t * indexer, const uint8_t cards[], uint64_t indices[]);

/**
 * Index a hand on the last round.
 *
 * @param indexer
 * @param cards
 * @returns hand's index on the last round
 */
uint64_t hand_index_last(const indexer_helper_t* poker_data, const hand_indexer_t * indexer, const uint8_t cards[]);


/**
 * Recovers the canonical hand from a given index.
 * @param poker_data Pointer to the helper data.
 * @param indexer Pointer to the indexer.
 * @param round The round number.
 * @param index The hand index.
 * @param cards Array to store the recovered cards.
 * @return true if successful, false otherwise.
 */
bool hand_unindex(const indexer_helper_t* poker_data, const hand_indexer_t * indexer, uint32_t round, uint64_t index, uint8_t cards[]);

#ifdef __cplusplus
}
#endif
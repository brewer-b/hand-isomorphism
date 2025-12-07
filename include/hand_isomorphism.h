/**
 * hand_isomorphism.h
 *
 * C++ wrapper around Kevin Waugh's hand isomorphism library providing
 * hand indexing for poker abstraction with various recall types.
 *
 * Recall types define how hands are grouped across betting rounds:
 * - Imperfect recall: Groups isomorphic hands at each street independently
 *   Structure: [[2],[2,3],[2,4],[2,5]]
 * - Perfect recall: Maintains full hand history across all streets
 *   Structure: [[2],[2,3],[2,3,1],[2,3,1,1]]
 * - Flop recall: Perfect recall through turn, groups turn+river at river
 *   Structure: [[2],[2,3],[2,3,1],[2,3,2]]
 * - Other abstractions: (future) Custom grouping strategies
 *
 * Street definitions:
 * - Street 0: 2 hole cards (preflop)
 * - Street 1: 2 hole cards + 3 flop cards
 * - Street 2: 2 hole cards + 3 flop + 1 turn card
 * - Street 3: 2 hole cards + 3 flop + 1 turn + 1 river card
 */

#pragma once

#include <cstdint>

extern "C" {

    // ========== Imperfect Recall ==========

    /**
     * Get the number of unique hand indices for a given street (imperfect recall).
     *
     * Imperfect recall indexes each street independently without considering
     * the hand history from previous streets.
     *
     * @param street The betting round (0=preflop, 1=flop, 2=turn, 3=river)
     * @return The total number of isomorphic hand classes at this street
     */
    uint64_t num_imperfect_recall_hands(int street);

    /**
     * Map a poker hand to its isomorphic index for a given street (imperfect recall).
     *
     * Cards are represented as uint8_t values where suit isomorphisms are
     * automatically detected. Multiple hands that differ only by suit
     * permutations will map to the same index.
     *
     * @param street The betting round (0=preflop, 1=flop, 2=turn, 3=river)
     * @param cards Array of cards representing the hand (format depends on street)
     * @return The isomorphic index for this hand class
     */
    uint64_t imperfect_recall_index(int street, const uint8_t *cards);

    /**
     * Recover the canonical representative hand from an index (imperfect recall).
     *
     * Given an index, returns the canonical (lexicographically first) hand
     * that maps to this index. This is the inverse of imperfect_recall_index.
     *
     * @param output Array to store the canonical hand cards
     * @param street The betting round (0=preflop, 1=flop, 2=turn, 3=river)
     * @param index The isomorphic index to convert back to cards
     */
    void imperfect_recall_unindex(uint8_t *output, int street, uint64_t index);

    // ========== Perfect Recall ==========

    /**
     * Get the number of unique hand indices for a given street (perfect recall).
     *
     * Perfect recall maintains the full hand history, so the index at street N
     * considers all cards dealt from street 0 through street N.
     *
     * @param street The betting round (0=preflop, 1=flop, 2=turn, 3=river)
     * @return The total number of isomorphic hand classes at this street
     */
    uint64_t num_perfect_recall_hands(int street);

    /**
     * Map a poker hand to its isomorphic index for a given street (perfect recall).
     *
     * Perfect recall considers the full hand history including the order in which
     * cards were dealt across all streets.
     *
     * @param street The betting round (0=preflop, 1=flop, 2=turn, 3=river)
     * @param cards Array of cards in deal order (all cards from street 0 to street N)
     * @return The isomorphic index for this hand class
     */
    uint64_t perfect_recall_index(int street, const uint8_t *cards);

    /**
     * Recover the canonical representative hand from an index (perfect recall).
     *
     * Given an index, returns the canonical hand that maps to this index,
     * maintaining the full hand history. This is the inverse of perfect_recall_index.
     *
     * @param output Array to store the canonical hand cards
     * @param street The betting round (0=preflop, 1=flop, 2=turn, 3=river)
     * @param index The isomorphic index to convert back to cards
     */
    void perfect_recall_unindex(uint8_t *output, int street, uint64_t index);

    // ========== Flop Recall ==========

    /**
     * Get the number of unique hand indices for a given street (flop recall).
     *
     * Flop recall maintains perfect recall through the turn, but groups turn and
     * river cards together at the river street (not distinguishing their order).
     *
     * @param street The betting round (0=preflop, 1=flop, 2=turn, 3=river)
     * @return The total number of isomorphic hand classes at this street
     */
    uint64_t num_flop_recall_hands(int street);

    /**
     * Map a poker hand to its isomorphic index for a given street (flop recall).
     *
     * Flop recall maintains history through the turn, but on the river street,
     * turn and river cards are treated as an unordered pair.
     *
     * @param street The betting round (0=preflop, 1=flop, 2=turn, 3=river)
     * @param cards Array of cards (order matters through turn, river combines turn+river)
     * @return The isomorphic index for this hand class
     */
    uint64_t flop_recall_index(int street, const uint8_t *cards);

    /**
     * Recover the canonical representative hand from an index (flop recall).
     *
     * Given an index, returns the canonical hand that maps to this index.
     * This is the inverse of flop_recall_index.
     *
     * @param output Array to store the canonical hand cards
     * @param street The betting round (0=preflop, 1=flop, 2=turn, 3=river)
     * @param index The isomorphic index to convert back to cards
     */
    void flop_recall_unindex(uint8_t *output, int street, uint64_t index);

}
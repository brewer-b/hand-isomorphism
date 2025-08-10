#pragma once

#include <cstdint>
#include <memory>
#include <vector>

/**
 * @class HandIsomorphism
 * @brief Provides a C++ interface for indexing and un-indexing poker hands.
 *
 * This class uses the Pimpl idiom to wrap a C library and provides
 * a clean, exception-safe, and object-oriented API for working with
 * isomorphic poker hand combinations. This class is non-copyable.
 */
class HandIsomorphism {
public:
  /**
   * @brief Constructs a HandIsomorphism object and initializes the indexers.
   *
   * @param cardsPerRounds A vector of vectors, where each inner vector
   * contains the number of cards in that round (e.g., [2, 3, 1, 1] for
   * a Texas Hold'em game).
   * @throws std::runtime_error if the underlying C library fails to initialize.
   */
  HandIsomorphism(const std::vector<std::vector<uint8_t>> &cardsPerRounds);
  ~HandIsomorphism();
  HandIsomorphism(const HandIsomorphism &other);
  HandIsomorphism &operator=(const HandIsomorphism &other);
  HandIsomorphism(HandIsomorphism &&other);
  HandIsomorphism &operator=(HandIsomorphism &&other);

  /**
   * @brief Gets the total number of unique hand isomorphisms for a given round.
   *
   * @param round The zero-based index of the round (e.g., 0 for preflop, 1 for
   * flop).
   * @return The number of unique hand combinations as a 64-bit integer.
   */
  uint64_t size(size_t round) const;

  /**
   * @brief Calculates the unique index for a given poker hand.
   *
   * The cards should be an array of `uint8_t` values (e.g., 0-51 for a standard
   * deck).
   *
   * @param round The zero-based index of the round.
   * @param cards A pointer to a C-style array of cards. The size of this array
   * should match the total number of cards for the given round.
   * @return A 64-bit integer representing the hand's unique index.
   */
  uint64_t index(size_t round, const uint8_t *cards) const;

  /**
   * @brief Reconstructs a poker hand from a given index.
   *
   * @param round The zero-based index of the round.
   * @param index The unique index of the hand to reconstruct.
   * @param output A pointer to a C-style array where the reconstructed cards
   * will be written. The array must be large enough to hold all cards
   * for the specified round.
   * @return `true` if the hand was successfully un-indexed, `false` otherwise.
   */
  bool unindex(size_t round, uint64_t index, uint8_t *output) const;

private:
  class Impl;
  std::unique_ptr<Impl> m_impl;
};
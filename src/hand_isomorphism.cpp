#include "hand_isomorphism.hpp"
#include <mutex>
#include <stdexcept>

using _Bool = bool;
extern "C" {
#include "hand_index.h"
}

using HandIndexerDeleter = decltype(&hand_indexer_free);

namespace {

std::once_flag hand_index_ctor_flag;

auto makeIndexer(const std::vector<uint8_t> &cardsPerRound) {
  std::unique_ptr<hand_indexer_t, HandIndexerDeleter> indexer{
      new hand_indexer_t, hand_indexer_free};
  bool success = hand_indexer_init(cardsPerRound.size(), cardsPerRound.data(),
                                   indexer.get());
  if (!success) {
    throw std::runtime_error("Failed to initialize hand_indexer_t.");
  }
  return indexer;
}

} // namespace

class HandIsomorphismImpl {
public:
  HandIsomorphismImpl(const std::vector<std::vector<uint8_t>> &cardsPerRounds);

  uint64_t size(size_t round) const {
    return hand_indexer_size(m_indexers[round].get(),
                             m_cardsPerRounds[round].size() - 1);
  }

  uint64_t index(size_t round, const uint8_t *cards) const {
    return hand_index_last(m_indexers[round].get(), cards);
  }

  bool unindex(size_t round, uint64_t index, uint8_t *output) const {
    return hand_unindex(m_indexers[round].get(),
                        m_cardsPerRounds[round].size() - 1, index, output);
  }

private:
  std::vector<std::vector<uint8_t>> m_cardsPerRounds;
  std::vector<std::unique_ptr<hand_indexer_t, HandIndexerDeleter>> m_indexers;
};

HandIsomorphism::HandIsomorphism(
    const std::vector<std::vector<uint8_t>> &cardsPerRounds) {
  std::call_once(hand_index_ctor_flag, []() { hand_index_ctor(); });
  m_pimpl = std::make_unique<HandIsomorphismImpl>(cardsPerRounds);
}

HandIsomorphism::~HandIsomorphism() = default;

HandIsomorphismImpl::HandIsomorphismImpl(
    const std::vector<std::vector<uint8_t>> &cardsPerRounds)
    : m_cardsPerRounds{cardsPerRounds} {
  m_indexers.reserve(cardsPerRounds.size());
  for (const auto &cardsPerRound : cardsPerRounds) {
    m_indexers.push_back(makeIndexer(cardsPerRound));
  }
}

uint64_t HandIsomorphism::size(size_t round) const {
  return m_pimpl->size(round);
}

uint64_t HandIsomorphism::index(size_t round, const uint8_t *cards) const {
  return m_pimpl->index(round, cards);
}

bool HandIsomorphism::unindex(size_t round, uint64_t index,
                              uint8_t *output) const {
  return m_pimpl->unindex(round, index, output);
}

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

class HandIsomorphism::Impl {
public:
  Impl(const std::vector<std::vector<uint8_t>> &cardsPerRounds);
  ~Impl();
  Impl(const Impl &other);
  Impl &operator=(const Impl &other);
  Impl(Impl &&other) noexcept;
  Impl &operator=(Impl &&other) noexcept;

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

HandIsomorphism::Impl::Impl(
    const std::vector<std::vector<uint8_t>> &cardsPerRounds)
    : m_cardsPerRounds{cardsPerRounds} {
  m_indexers.reserve(cardsPerRounds.size());
  for (const auto &cardsPerRound : cardsPerRounds) {
    m_indexers.push_back(makeIndexer(cardsPerRound));
  }
}

HandIsomorphism::Impl::~Impl() {}

HandIsomorphism::Impl::Impl(const Impl &other)
    : m_cardsPerRounds{other.m_cardsPerRounds} {
  m_indexers.reserve(other.m_indexers.size());
  for (const auto &cardsPerRound : other.m_cardsPerRounds) {
    m_indexers.push_back(makeIndexer(cardsPerRound));
  }
}

HandIsomorphism::Impl &HandIsomorphism::Impl::operator=(const Impl &other) {
  auto temp{other};
  std::swap(m_cardsPerRounds, temp.m_cardsPerRounds);
  std::swap(m_indexers, temp.m_indexers);
  return *this;
}

HandIsomorphism::Impl::Impl(Impl &&other) noexcept
    : m_cardsPerRounds{std::move(other.m_cardsPerRounds)},
      m_indexers{std::move(other.m_indexers)} {}

HandIsomorphism::Impl &HandIsomorphism::Impl::operator=(Impl &&other) noexcept {
  if (this != &other) {
    m_cardsPerRounds = std::move(other.m_cardsPerRounds);
    m_indexers = std::move(other.m_indexers);
  }
  return *this;
}

HandIsomorphism::HandIsomorphism(
    const std::vector<std::vector<uint8_t>> &cardsPerRounds) {
  std::call_once(hand_index_ctor_flag, []() { hand_index_ctor(); });
  m_impl = std::make_unique<Impl>(cardsPerRounds);
}

HandIsomorphism::~HandIsomorphism() {}

HandIsomorphism::HandIsomorphism(const HandIsomorphism &other)
    : m_impl{std::make_unique<Impl>(*other.m_impl)} {}

HandIsomorphism &HandIsomorphism::operator=(const HandIsomorphism &other) {
  auto temp{other};
  std::swap(m_impl, temp.m_impl);
  return *this;
}

HandIsomorphism::HandIsomorphism(HandIsomorphism &&other)
    : m_impl{std::move(other.m_impl)} {}

HandIsomorphism &HandIsomorphism::operator=(HandIsomorphism &&other) {
  if (this != &other) {
    m_impl = std::move(other.m_impl);
  }
  return *this;
}

uint64_t HandIsomorphism::size(size_t round) const {
  return m_impl->size(round);
}

uint64_t HandIsomorphism::index(size_t round, const uint8_t *cards) const {
  return m_impl->index(round, cards);
}

bool HandIsomorphism::unindex(size_t round, uint64_t index,
                              uint8_t *output) const {
  return m_impl->unindex(round, index, output);
}

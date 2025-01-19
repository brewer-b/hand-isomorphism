#include "hand_isomorphism.h"

extern "C" {
#include "hand_index.h"
}

HandIsomorphism::HandIsomorphism(uint8_t numHoleCards, Recall recall) {
  static bool initialized = []() {
    hand_index_ctor();
    return true;
  }();

  switch (recall) {
  case Recall::Perfect:
    cardsPerRound_ = {{numHoleCards},
                      {numHoleCards, 3},
                      {numHoleCards, 3, 1},
                      {numHoleCards, 3, 1, 1}};
    break;
  case Recall::Imperfect:
    cardsPerRound_ = {{numHoleCards},
                      {numHoleCards, 3},
                      {numHoleCards, 4},
                      {numHoleCards, 5}};
    break;
  case Recall::Flop:
    cardsPerRound_ = {{numHoleCards},
                      {numHoleCards, 3},
                      {numHoleCards, 3, 1},
                      {numHoleCards, 3, 2}};
    break;
  case Recall::PublicBoard:
    cardsPerRound_ = {{3}, {3}, {4}, {5}};
    break;
  }
  for (size_t i = 0; i < cardsPerRound_.size(); i++) {
    HandIndexerPtr indexer(new hand_indexer_t, hand_indexer_free);
    hand_indexer_init(cardsPerRound_[i].size(), cardsPerRound_[i].data(),
                      indexer.get());
    handIndexers_.push_back(std::move(indexer));
  }
}

uint64_t HandIsomorphism::size(int round) const {
  return hand_indexer_size(handIndexers_[round].get(),
                           cardsPerRound_[round].size() - 1);
}

uint64_t HandIsomorphism::index(int round, const uint8_t *cards) const {
  return hand_index_last(handIndexers_[round].get(), cards);
}

bool HandIsomorphism::unindex(int round, uint64_t index,
                              uint8_t *output) const {
  return hand_unindex(handIndexers_[round].get(),
                      cardsPerRound_[round].size() - 1, index, output);
}

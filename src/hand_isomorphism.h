#pragma once

#include <memory>
#include <vector>

struct hand_indexer_s;

class HandIsomorphism {
public:
  enum class Recall { Perfect, Imperfect, Flop, PublicBoard };
  HandIsomorphism(Recall recall);
  uint64_t size(int round) const;
  uint64_t index(int round, const uint8_t *cards) const;
  bool unindex(int round, uint64_t index, uint8_t *output) const;

private:
  using HandIndexerPtr =
      std::unique_ptr<hand_indexer_s, void (*)(hand_indexer_s *)>;

  std::vector<HandIndexerPtr> handIndexers_;
  std::vector<std::vector<uint8_t>> cardsPerRound_;
};
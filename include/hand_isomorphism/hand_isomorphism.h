#pragma once

#include <vector>

class HandIsomorphism
{
public:
    HandIsomorphism(std::vector<std::vector<uint8_t>> cards_per_round);
    ~HandIsomorphism();
    void *get_indexer(uint64_t round) const;
    uint64_t size(uint64_t round) const;
    uint64_t index(uint64_t round, const uint8_t *cards) const;
    void unindex(uint64_t round, uint64_t idx, uint8_t *output) const;

private:
    std::vector<std::vector<uint8_t>> cards_per_round_;
    std::vector<void *> indexers;
};
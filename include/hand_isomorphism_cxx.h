#pragma once

#include <mutex>
#include <stdexcept>
#include <vector>
#include "hand_isomorphism.h"

class IndexerHelperSingleton {
public:
    static IndexerHelperSingleton& getInstance() {
        std::call_once(initInstanceFlag_, &IndexerHelperSingleton::initSingleton);
        return *instance_;
    }

    indexer_helper_t* getHelper() const {
        return helper_;
    }

private:
    static IndexerHelperSingleton* instance_;
    static std::once_flag initInstanceFlag_;

    indexer_helper_t* helper_;

    IndexerHelperSingleton() {
        helper_ = indexer_helper_ctor();
        if (!helper_) {
            throw std::runtime_error("Failed to create indexer_helper_t.");
        }
    }

    ~IndexerHelperSingleton() {
        if (helper_) {
            indexer_helper_dtor(helper_);
        }
    }

    static void initSingleton() {
        instance_ = new IndexerHelperSingleton();
    }

    IndexerHelperSingleton(const IndexerHelperSingleton&) = delete;
    IndexerHelperSingleton& operator=(const IndexerHelperSingleton&) = delete;
};

class HandIndexers {
public:
    HandIndexers(const std::vector<std::vector<uint8_t>>& rounds_cards_per_round):rounds_cards_per_round(rounds_cards_per_round) {
        helper = IndexerHelperSingleton::getInstance().getHelper();
        
        for (const auto& cards_per_round : rounds_cards_per_round) {
            if (cards_per_round.empty()) {
                throw std::invalid_argument("Each round must have at least one card.");
            }

            hand_indexer_t* indexer = hand_indexer_init(helper, cards_per_round.size(), cards_per_round.data());
            if (!indexer) {
                throw std::runtime_error("Failed to initialize hand indexer.");
            }

            indexers_.push_back(indexer);
        }
    }

    ~HandIndexers() {
        for (auto indexer : indexers_) {
            if (indexer) {
                hand_indexer_free(indexer);
            }
        }
    }

    uint64_t roundSize(uint32_t round) const {
        return hand_indexer_size(indexers_[round], rounds_cards_per_round[round].size() - 1);
    }

    uint64_t indexHand(uint32_t round, const std::vector<uint8_t>& cards) const {
        return hand_index_last(helper, indexers_[round], cards.data());
    }

    bool unindexHand(uint32_t round, uint64_t index, uint8_t* cards) const {
        return hand_unindex(helper, indexers_[round], rounds_cards_per_round[round].size() - 1, index, cards);
    }

private:
    std::vector<hand_indexer_t*> indexers_;  // Vector of hand indexer objects
    indexer_helper_t* helper;
    const std::vector<std::vector<uint8_t>> rounds_cards_per_round;
    // Disable copy constructor and assignment to prevent resource management issues
    HandIndexers(const HandIndexers&) = delete;
    HandIndexers& operator=(const HandIndexers&) = delete;
};
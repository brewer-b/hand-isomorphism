#pragma once

#include "../src/hand_index.h"
#include <vector>

//imperfect recall is HandIsomorphism({2},{2,3},{2,4},{2,5});
//flop recall is HandIsomorphism({2},{2,3},{2,3,1},{2,3,2});
//perfect recall is HandIsomorphism({2},{2,3},{2,3,1},{2,3,1,1});
class HandIsomorphism {
public:
    HandIsomorphism(std::vector<std::vector<uint8_t>> cardsPerRound):cardsPerRound(cardsPerRound){
        indexers.resize(cardsPerRound.size());
        for (size_t i = 0; i < indexers.size(); i++){
            indexInfo.hand_indexer_init(cardsPerRound[i].size(), cardsPerRound[i].data(), &indexers[i]);
        }
    }
    ~HandIsomorphism(){
        for (size_t i = 0; i < indexers.size(); i++){
            indexInfo.hand_indexer_free(&indexers[i]);
        }
    }
    uint64_t size(int round) {
        return indexInfo.hand_indexer_size(&indexers[round], cardsPerRound[round].size() - 1);
    }
    uint64_t index(int round, uint8_t const* cards) {
        return indexInfo.hand_index_last(&indexers[round], cards);
    }
    bool unindex(int round, uint64_t index, uint8_t* output){
        return indexInfo.hand_unindex(&indexers[round], cardsPerRound[round].size() - 1, index, output);
    }
private:
    HandIndexer indexInfo;
    std::vector<std::vector<uint8_t>> cardsPerRound;
    std::vector<hand_indexer_t> indexers;
};
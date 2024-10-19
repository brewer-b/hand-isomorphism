
#include <iostream>
#include "hand_isomorphism_cxx.h"

int main(){
    std::vector<std::vector<uint8_t>> rounds_cards_per_round = { {2}, {2, 3}, {2, 4}, {2, 5} };
    HandIndexers indexers(rounds_cards_per_round);

    for (size_t i = 0; i < 4; i++){
        std::cout << indexers.roundSize(i) << std::endl;
    }
    
    std::vector<uint8_t> cards(7);
    for (uint32_t round = 0; round < 4; round++)
    {
        for (size_t i = 0; i < indexers.roundSize(round); i++){
            bool result = indexers.unindexHand(round,i,cards.data());
            //std::cout << (int)cards[0] << "  " << (int)cards[1] << std::endl;
            uint64_t reverse = indexers.indexHand(round, cards);
            if (i != reverse){
                std::cerr << "failed" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    return 0;
}
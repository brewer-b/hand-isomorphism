#include "../include/isomorphism_c.h"
#include "../include/isomorphism.h"
#include <vector>

extern "C" {

struct HandIsomorphismWrapper {
    HandIsomorphismWrapper(std::vector<std::vector<uint8_t>> cardsPerRound)
        : impl(cardsPerRound) {}
    HandIsomorphism impl;
};

HandIsomorphism* HandIsomorphism_create(const uint8_t** cards_per_round, size_t* sizes, size_t num_rounds) {
    std::vector<std::vector<uint8_t>> cards_per_round_vec;
    for (size_t i = 0; i < num_rounds; ++i) {
        cards_per_round_vec.push_back(std::vector<uint8_t>(cards_per_round[i], cards_per_round[i] + sizes[i]));
    }
    return reinterpret_cast<HandIsomorphism*>(new HandIsomorphismWrapper(cards_per_round_vec));
}

void HandIsomorphism_destroy(HandIsomorphism* hi) {
    delete reinterpret_cast<HandIsomorphismWrapper*>(hi);
}

uint64_t HandIsomorphism_size(HandIsomorphism* hi, int round) {
    return reinterpret_cast<HandIsomorphismWrapper*>(hi)->impl.size(round);
}

uint64_t HandIsomorphism_index(HandIsomorphism* hi, int round, const uint8_t* cards) {
    return reinterpret_cast<HandIsomorphismWrapper*>(hi)->impl.index(round, cards);
}

bool HandIsomorphism_unindex(HandIsomorphism* hi, int round, uint64_t index, uint8_t* output) {
    return reinterpret_cast<HandIsomorphismWrapper*>(hi)->impl.unindex(round, index, output);
}

}
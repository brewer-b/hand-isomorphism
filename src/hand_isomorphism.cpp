#include "hand_isomorphism.h"

#include <vector>

extern "C"{
#include "hand_index.h"
}

struct HandIndexers{
    HandIndexers(const std::vector<std::vector<uint8_t>>& cards_per_street):
        cards_per_street(cards_per_street){
        indexers.resize(cards_per_street.size());
        for (size_t i = 0; i < cards_per_street.size(); i++)
        {
            hand_indexer_init(cards_per_street[i].size(), cards_per_street[i].data(), &indexers[i]);
        }
    }
    ~HandIndexers(){
        for (size_t i = 0; i < indexers.size(); i++)
        {
            hand_indexer_free(&indexers[i]);
        }
    }
    const std::vector<std::vector<uint8_t>> cards_per_street;
    std::vector<hand_indexer_t> indexers;
};

class HandIndexerBuilder{
public:
    static HandIndexerBuilder& get_instance() {
        static HandIndexerBuilder instance;
        return instance;
    }

    HandIndexers build(const std::vector<std::vector<uint8_t>>& cards_per_street){
        return HandIndexers(cards_per_street);
    }

    HandIndexerBuilder(const HandIndexerBuilder&) = delete;
    HandIndexerBuilder& operator=(const HandIndexerBuilder&) = delete;
    HandIndexerBuilder(HandIndexerBuilder&&) = delete;
    HandIndexerBuilder& operator=(HandIndexerBuilder&&) = delete;

private:
    HandIndexerBuilder() {
        hand_index_ctor();
    }
};

class ImperfectRecall{
public:
    static ImperfectRecall& get_instance() {
        static ImperfectRecall instance;
        return instance;
    }

    ImperfectRecall(const ImperfectRecall&) = delete;
    ImperfectRecall& operator=(const ImperfectRecall&) = delete;
    ImperfectRecall(ImperfectRecall&&) = delete;
    ImperfectRecall& operator=(ImperfectRecall&&) = delete;

    HandIndexers indexers;
private:
    ImperfectRecall()
        : indexers(HandIndexerBuilder::get_instance().build({{2},{2,3},{2,4},{2,5}})) {
    }
};

class PerfectRecall{
public:
    static PerfectRecall& get_instance() {
        static PerfectRecall instance;
        return instance;
    }

    PerfectRecall(const PerfectRecall&) = delete;
    PerfectRecall& operator=(const PerfectRecall&) = delete;
    PerfectRecall(PerfectRecall&&) = delete;
    PerfectRecall& operator=(PerfectRecall&&) = delete;

    HandIndexers indexers;
private:
    PerfectRecall()
        : indexers(HandIndexerBuilder::get_instance().build({{2},{2,3},{2,3,1},{2,3,1,1}})) {
    }
};

class FlopRecall{
public:
    static FlopRecall& get_instance() {
        static FlopRecall instance;
        return instance;
    }

    FlopRecall(const FlopRecall&) = delete;
    FlopRecall& operator=(const FlopRecall&) = delete;
    FlopRecall(FlopRecall&&) = delete;
    FlopRecall& operator=(FlopRecall&&) = delete;

    HandIndexers indexers;
private:
    FlopRecall()
        : indexers(HandIndexerBuilder::get_instance().build({{2},{2,3},{2,3,1},{2,3,2}})) {
    }
};

class BoardImperfectRecall{
public:
    static BoardImperfectRecall& get_instance() {
        static BoardImperfectRecall instance;
        return instance;
    }

    BoardImperfectRecall(const BoardImperfectRecall&) = delete;
    BoardImperfectRecall& operator=(const BoardImperfectRecall&) = delete;
    BoardImperfectRecall(BoardImperfectRecall&&) = delete;
    BoardImperfectRecall& operator=(BoardImperfectRecall&&) = delete;

    HandIndexers indexers;
private:
    BoardImperfectRecall()
        : indexers(HandIndexerBuilder::get_instance().build({{1},{3},{4},{5}})) {
    }
};

extern "C" {

    uint64_t num_imperfect_recall_hands(int street){
        const auto &indexers = ImperfectRecall::get_instance().indexers;
        return hand_indexer_size(&indexers.indexers[street], indexers.cards_per_street[street].size() - 1);
    }

    uint64_t imperfect_recall_index(int street, const uint8_t *cards){
        const auto &indexers = ImperfectRecall::get_instance().indexers;
        return hand_index_last(&indexers.indexers[street], cards);
    }

    void imperfect_recall_unindex(uint8_t *output, int street, uint64_t index){
        const auto &indexers = ImperfectRecall::get_instance().indexers;
        hand_unindex(&indexers.indexers[street], indexers.cards_per_street[street].size() - 1, index, output);
    }

    uint64_t num_perfect_recall_hands(int street){
        const auto &indexers = PerfectRecall::get_instance().indexers;
        return hand_indexer_size(&indexers.indexers[street], indexers.cards_per_street[street].size() - 1);
    }

    uint64_t perfect_recall_index(int street, const uint8_t *cards){
        const auto &indexers = PerfectRecall::get_instance().indexers;
        return hand_index_last(&indexers.indexers[street], cards);
    }

    void perfect_recall_unindex(uint8_t *output, int street, uint64_t index){
        const auto &indexers = PerfectRecall::get_instance().indexers;
        hand_unindex(&indexers.indexers[street], indexers.cards_per_street[street].size() - 1, index, output);
    }

    uint64_t num_flop_recall_hands(int street){
        const auto &indexers = FlopRecall::get_instance().indexers;
        return hand_indexer_size(&indexers.indexers[street], indexers.cards_per_street[street].size() - 1);
    }

    uint64_t flop_recall_index(int street, const uint8_t *cards){
        const auto &indexers = FlopRecall::get_instance().indexers;
        return hand_index_last(&indexers.indexers[street], cards);
    }

    void flop_recall_unindex(uint8_t *output, int street, uint64_t index){
        const auto &indexers = FlopRecall::get_instance().indexers;
        hand_unindex(&indexers.indexers[street], indexers.cards_per_street[street].size() - 1, index, output);
    }

    uint64_t num_board_imperfect_recall_boards(int street){
        const auto &indexers = BoardImperfectRecall::get_instance().indexers;
        return hand_indexer_size(&indexers.indexers[street], indexers.cards_per_street[street].size() - 1);
    }

    uint64_t board_imperfect_recall_index(int street, const uint8_t *cards){
        const auto &indexers = BoardImperfectRecall::get_instance().indexers;
        return hand_index_last(&indexers.indexers[street], cards);
    }

    void board_imperfect_recall_unindex(uint8_t *output, int street, uint64_t index){
        const auto &indexers = BoardImperfectRecall::get_instance().indexers;
        hand_unindex(&indexers.indexers[street], indexers.cards_per_street[street].size() - 1, index, output);
    }

}
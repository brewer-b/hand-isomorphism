#include "hand_isomorphism_c.h"
#include "hand_isomorphism.h"

#include <stdexcept>

#ifdef __cplusplus
extern "C" {
#endif

HandIsomorphism *hand_isomorphism_create(uint8_t numHoleCards, Recall recall) {
  switch (recall) {
  case RECALL_PERFECT:
    return new HandIsomorphism(numHoleCards, HandIsomorphism::Recall::Perfect);
  case RECALL_IMPERFECT:
    return new HandIsomorphism(numHoleCards,
                               HandIsomorphism::Recall::Imperfect);
  case RECALL_FLOP:
    return new HandIsomorphism(numHoleCards, HandIsomorphism::Recall::Flop);
  case RECALL_PUBLIC_BOARD:
    return new HandIsomorphism(numHoleCards,
                               HandIsomorphism::Recall::PublicBoard);
  }
}

void hand_isomorphism_destroy(HandIsomorphism *handle) {
  if (handle) {
    delete handle;
  }
}

uint64_t hand_isomorphism_size(const HandIsomorphism *handle, int round) {
  if (!handle)
    return 0;
  return handle->size(round);
}

uint64_t hand_isomorphism_index(const HandIsomorphism *handle, int round,
                                const uint8_t *cards) {
  if (!handle || !cards)
    return 0;
  return handle->index(round, cards);
}

bool hand_isomorphism_unindex(const HandIsomorphism *handle, int round,
                              uint64_t index, uint8_t *output) {
  if (!handle || !output)
    return 0;
  return handle->unindex(round, index, output);
}

#ifdef __cplusplus
}
#endif
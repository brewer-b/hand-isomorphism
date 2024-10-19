#include "hand_isomorphism_cxx.h"

IndexerHelperSingleton* IndexerHelperSingleton::instance_ = nullptr;
std::once_flag IndexerHelperSingleton::initInstanceFlag_;
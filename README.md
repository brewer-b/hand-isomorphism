Poker Hand Isomorphisms
=======================

This repository contains a C++ wrapper around Kevin Waugh's poker hand isomorphism
library. The original C library efficiently maps poker hands to and from a tight
set of indices. Poker hands are isomorphic with respect to permutations of the
suits and ordering within a betting round. That is, AsKs, KdAd and KhAh all map
to the same index preflop.

## Original Work

author: Kevin Waugh (waugh@cs.cmu.edu)
date: April 7, 2013

Please see:

K. Waugh, 2013. A Fast and Optimal Hand Isomorphism Algorithm.  In the Second
Computer Poker and Imperfect Information Symposium at AAAI

for more details, and src/hand_index.h for the original C API's description.

## This Wrapper

This C++ wrapper provides:
- Cross-platform compatibility (GCC, Clang, MSVC)
- Singleton pattern for efficient initialization
- Imperfect recall hand indexing for poker abstraction

The C library has been modified to support Windows/MSVC compilation while
maintaining compatibility with Unix-like systems.

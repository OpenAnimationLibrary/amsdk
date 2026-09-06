# Completion hardening

The receiver now retains its ordinary state until every nested dialog callback
returns, including destruction during destination confirmation. It stops before
SDK mutation if that receiver was closed. Native face verification checks cyclic
corner order as well as corner identity, rejecting crossed permutations.
Production-parser self-tests exercise those lifetime paths and all 24 quad
corner permutations. These are not a substitute for A:M shutdown/undo tests.

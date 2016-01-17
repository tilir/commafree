//===--------- cf_eastman.h -- Eastman algorithm header -------------------===//
//
// This file is distributed under the GNU GPL v3 License. 
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares function do_eastman, which examines sequences of
// numbers like:
//
// 3 0 1 2 0 1 2 3 0 3 1 2 4 3 3 0 3 1 3 2 0 
//
// to be shifted to prepare comma free word, from its equivalence class
// it outputs shift, in this case 12
//
// algorithm of Willard L. Eastman, IEEE Trans. IT-11 (1965), 263--267:
// Given a sequence of nonnegative integers x_0, x_1 ... x_{n-1} of
// odd length n, where x is not equal to any of its cyclic shifts
// we output a cyclic shift sigma(x) such that the set of all such shifts
// forms a commafree code of block length~$n$ (over an infinite alphabet).
//
// The simplest nontrivial example occurs when n=3. If x=abc, where
// a, b, and c aren't all equal, then exactly one of the cyclic shifts
// abc, bca, cab will satisfy y_0 > y_1 <= y_2, and we choose that one. 
// It's easy to check that the triples chosen in this way are commafree.
//
// Similar constructions are possible when n=5 or n=7. But the case
// n=9 already gets a bit dicey, and when n is really large it's not
// at all clear that commafreeness is possible. Eastman's paper resolved
// a conjecture made by Golomb, Gordon, and Welch in their pioneering paper 
// about comma-free codes (1958).
//
// (Of course, it's not at all clear that we would want to actually use a 
// commafree code when n is large; but that's another story, and beside the 
// point. The point is that Eastman discovered a really interesting algorithm.)
//
// also see: 
// http://www-cs-faculty.stanford.edu/~uno/programs/commafree-eastman.w 
//===----------------------------------------------------------------------===//

#ifndef CF_EASTMAN_GUARD_
#define CF_EASTMAN_GUARD_

#include <vector>

// We think of x as written cyclically, with x[n+j] = x[j] for all j >= 0.
// The basic idea in the algorithm below is to also think of x as partitioned
// into t <= n subwords by boundary markers b[j] where 
// 0 < b[0] < b[1] < ... < b[t-1] < n; 
// then subword y[j] is x[b[j]], x[b[j]+1], ..., x[b[j+1]-1],
// for 0 < j < t, where b[t] = b[0]. 
//
// If t=1, there's just one subword, and it's a cyclic shift of x. 
// The number t of subwords during each phase will be odd.
// 
// Eastman's algorithm essentially begins with b[j] = j for 0 < j < n, so that
// x is partitioned into n subwords of length 1. It successively removes
// boundary points until only one subword is left; that subword is the answer.
//
// Input/output:
// x is sequence like 3 0 1 2 0 1 2 3 0 3 1 2 4 3 3 0 3 1 3 2 0
//   it is modified inside routine
// output is required shift, like 12
int do_eastman (std::vector<int> &x);

#endif

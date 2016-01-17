//===------ cf_eastman.cpp -- Eastman algorithm implementation ----------===//
//
// This file is distributed under the GNU GPL v3 License. 
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains an implementation of algorithm, that examines sequence of
// numbers like:
//
// 3 0 1 2 0 1 2 3 0 3 1 2 4 3 3 0 3 1 3 2 0 
//
// to be shifted to prepare comma free word, from its equivalence class
// it outputs shift, in this case 12
//
// see cf_eastman.h for detailed description of approach
// this file rewritten in C++ from commafree-eastman.w programm:
// http://www-cs-faculty.stanford.edu/~uno/programs/commafree-eastman.w 
//
//===----------------------------------------------------------------------===//

#include <algorithm>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cassert>

#include "cf_eastman.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;

// true if subword b[i-1]..b[i] greater then b[i]..b[i+1] from xs 
// longer word counts greater
// equal length words counts lexicographically greater
static bool 
prev_greater (const vector<int> &xs, const vector<size_t> &b, size_t i) 
{
  assert (i > 0);
  assert (i < b.size() - 1);

  int j;
  int fst_start = b[i - 1];
  int fst_len = b[i] - b[i - 1];
  int snd_start = b[i];
  int snd_len = b[i + 1] - b[i];

  if (fst_len != snd_len)
    return fst_len > snd_len;

  for (j = 0; j < fst_len; j++) 
    {
      int fst_next = xs[fst_start + j];
      int snd_next = xs[snd_start + j];

      if (fst_next != snd_next)
        return fst_next > snd_next;
    }

  return false; /* y[i-1] == y[i] */
}

/* copy vector to itslef, tripling its size */
template <typename T> static void
triple_vector (vector<T> &m)
{
  auto size = m.size ();
  m.reserve (size * 3);
  std::back_insert_iterator< vector<T> > back_it (m);
  std::copy (m.begin(), m.begin() + size, back_it);
  std::copy (m.begin(), m.begin() + size, back_it);
}

/* look in header for detailed comment */
int 
do_eastman (vector<int> &xs)
{
  size_t new_cnt, phase = 1, boundaries_cnt;
  size_t n = xs.size();
  vector<size_t> b(n * 3);  

#ifdef DBGOUT
  for (auto x : xs)
    cout << x << " ";
#endif

  triple_vector(xs);
  std::iota (std::begin(b), std::end(b), 0);

  /* only one boundary point should survive */
  for (boundaries_cnt = n; boundaries_cnt > 1; boundaries_cnt = new_cnt)
    {
      size_t i, k;
      std::deque<int> retain_points;

      /* check for trivially cyclic input (say 0 0 0 is trivially cyclic) */
      for (i = 1; i <= boundaries_cnt; i++)
        {
          if (prev_greater (xs, b, i)) 
            break;
        }

      if (i > boundaries_cnt) 
        throw std::runtime_error("Input is cyclic");

      /* advance to the first basin */
      while (prev_greater (xs, b, i+1))
        i += 1;

      /* main loop of Eastman's algorithm */
      while (i <= boundaries_cnt) 
        {
          size_t q, j;

          /* climb the range */
          q = i + 1;
          while (!prev_greater (xs, b, q + 1))
            q += 1;

          /* advance to the next basin */
          j = q + 1;
          while (prev_greater (xs, b, j + 1))
            j += 1;

          if ((j - i) % 2)
            {
              /* Choose a boundary point to retain */
              if ((q - i) % 2) 
                q += 1;

              if (q < boundaries_cnt)
                retain_points.push_back(b[q]);
              else
                retain_points.push_front(b[q - boundaries_cnt]);
            }
        
          i = j;
        }

      new_cnt = retain_points.size();

#ifdef DBGOUT
      cout << ":";
      for (k = 0; k < new_cnt; k++)
        cout << retain_points[k] << " ";
#endif

      /* populate b with new retain points */
      for (k = 0; k < new_cnt; k++)
          b[k] = retain_points[k];

      /* repopulate b three times */ 
      while (b[k - new_cnt] < n + n) 
        {
          b[k] = b[k - new_cnt] + n;
          k += 1;
        }

      /* resize b to save some memory */
      if (b.size() > new_cnt * 3)
        b.erase(b.begin() + new_cnt * 3, b.end());

      phase += 1;
    }

#ifdef DBGOUT
  cout << endl;
#endif

  return b[0];
}


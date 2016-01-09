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

#include "cf_eastman.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;

/* compare subword b[i-1]..b[i] with b[i]..b[i+1] from xs */
static bool 
compare_less (const vector<int> &xs, const vector<int> &b, int i) 
{
  int j;
  int fst_start = b[i - 1];
  int fst_len = b[i] - b[i - 1];
  int snd_start = b[i];
  int snd_len = b[i + 1] - b[i];

  if (fst_len != snd_len)
    return fst_len > snd_len;

  for (j = 0; j < fst_len; j++) 
    {
      int fst_next = xs[b[i - 1] + j];
      int snd_next = xs[b[i] + j];

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
  int new_cnt, phase = 1, boundaries_cnt;
  int n = xs.size();
  vector<int> b(n * 3);  

  triple_vector(xs);
  std::iota (std::begin(b), std::end(b), 0);

  /* only one boundary point should survive */
  for (boundaries_cnt = n; boundaries_cnt > 1; boundaries_cnt = new_cnt)
    {
      int i, k;
      std::deque<int> odd_basins;

      /* check for trivially cyclic input (say 0 0 0 is trivially cyclic) */
      for (i = 1; i <= boundaries_cnt; i++)
        {
          if (compare_less (xs, b, i)) 
            break;
        }

      if (i > boundaries_cnt) 
        throw std::runtime_error("Input is cyclic");

      /* advance to the first basin */
      while (compare_less (xs, b, i+1))
        i += 1;

      /* main loop of Eastman's algorithm */
      while (i <= boundaries_cnt) 
        {
          int q, j;

          /* climb the range */
          q = i + 1;
          while (!compare_less (xs, b, q + 1))
            q += 1;

          /* advance to the next basin */
          j = q + 1;
          while (compare_less (xs, b, j + 1))
            j += 1;

          if ((j - i) % 2)
            {
              /* Choose a boundary point to retain */
              if ((q - i) % 2) 
                q += 1;

              if (q >= boundaries_cnt)
                odd_basins.push_front(b[q - boundaries_cnt]);
              else
                odd_basins.push_back(b[q]);             
            }
        
          i = j;
        }

      new_cnt = odd_basins.size();

#ifdef DBGOUT
      cout << "Phase " << phase << " leaves:";
      for (k = 0; k < new_cnt; k++)
        cout << " " << odd_basins[k];
      cout << endl;
#endif

      /* populate b with new basin points */
      for (k = 0; k < new_cnt; k++)
          b[k] = odd_basins[k];

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

  return b[0];
}


//===------- tuples.hpp -- simple n-tuple holder ------------------------===//
//
// This file is distributed under the GNU GPL v3 License. 
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains definition and implementation of Tuples class
// which generates all n-tuples for given configuration array
//
//===----------------------------------------------------------------------===//


#ifndef TUPLES_GUARD_
#define TUPLES_GUARD_

#include <vector>
#include <cassert>
#include <algorithm>

#include "cf_dict.hpp"

using std::vector;
using std::search;

/* simple n-tuple holder */
class Tuples
{
  int m_n;
  vector<int> m_a;
  vector<int> m_max;
public:
  Tuples (vector<int> maxnums) : m_n(maxnums.size()), m_a(m_n), m_max(maxnums) {}

  /* nxt is pure output parameter it will be discarded on entry */
  bool get_next (vector<int> &nxt)
    {
      int j;

      nxt = m_a;
      j = m_n - 1;

      while ((j > -1) && (m_a[j] == m_max[j]))
        {
          m_a[j] = 0;
          j = j - 1;
        }

      if (j == -1)
        return false;

      m_a[j] += 1;
      return true;
    }

  /* put all comma-free representatives from all tuples in given config to out */  
  int get_all_cf_reprs (vector< vector<int> > &out)
    {
      vector<int> nxt;
      bool ok;
      Cfdict d(m_n);

      out.clear();

      do {
        ok = get_next(nxt);
        d.add_tuple(nxt);
      } while (ok);

      d.get_dict(out);
      return out.size();
    }
};

#endif

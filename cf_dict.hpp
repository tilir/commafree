//===------- cfdict.hpp -- comma-free dictionary ------------------------===//
//
// This file is distributed under the GNU GPL v3 License. 
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains definition and implementation of Cfdict class
// which holds comma-free dictionary and methods to check and cross check 
// every input word
//
//===----------------------------------------------------------------------===//

#ifndef CF_GUARD_
#define CF_GUARD_

#include <vector>
#include <cassert>
#include <algorithm>
#include <stdexcept>

using std::vector;
using std::search;

class Cfdict
{
  size_t m_n;
  vector< vector<int> > m_dict;
public:
  Cfdict (size_t n) : m_n(n) {}

  /* return 0 on success, otherwise number of conflicting tuple + 1 returned */
  /* -1 means that candidate is cyclic itself */
  /* strict == true implies long check that code at all is really comma-free */
  int add_tuple (std::vector<int> nxt, bool strict = false)
    {
      int confl;
      m_lasterr.clear();

      if (nxt.size() != m_n)
        throw std::runtime_error("Incorrect size of candidate");

      size_t dsize = m_dict.size(), idx;

      for (idx = 0; idx != dsize; ++idx)
        {
          auto &x = m_dict[idx];
          if (search(x.begin(), x.end(), nxt.begin(), nxt.end()) != x.end())
            {
              m_lasterr = x;
              return (idx + 1);
            }
        }

      /* keeping nxtnxt to simplify cyclic_perm check to search */
      vector<int> nxt2(nxt);
      nxt2.insert(nxt2.end(), nxt.begin(), nxt.end());

      /* it should not be cyclic itself */
      if (search(nxt2.begin() + 1, nxt2.end() - 1, nxt.begin(), nxt.end()) != nxt2.end() - 1)
        return -1;
 
      if (strict)
        {
          confl = verify_dict (nxt);
          if (confl != 0) return confl;
        }        

      m_dict.push_back(nxt2);
      return 0;
    }

  void get_dict(vector< vector<int> > &out)
    {
      out = m_dict;

      /* now shrinking before return */
      for (auto& x : out)
        x.erase(x.begin() + x.size()/2, x.end());
    }

  /* not part of model, pure error reporting */
  std::vector<int> m_lasterr;

private:

  int cross_check (const vector<int> &fst, 
                   const vector<int> &snd, 
                   const vector<int> &nxt)
    {  
      vector<int> tmp(fst);
      tmp.insert(tmp.end(), snd.begin(), snd.end());
      if (search(tmp.begin(), tmp.end(), nxt.begin(), nxt.end()) != tmp.end())
        {
          vector<int> err(tmp.begin() + m_n, tmp.end() - m_n);
          m_lasterr = err;
          return -1;
        }
      return 0;
    }

  /* returns 0 or (conflicting pattern+1) */
  int verify_dict (std::vector<int> &nxt)
    {      
      size_t dsize = m_dict.size(), idx, jdx;

      if (dsize < 2)
        return 0;

      for (idx = 0; idx < dsize - 1; ++idx)
        for (jdx = idx + 1; jdx < dsize; ++jdx)
          {
            int ch = cross_check (m_dict[idx], m_dict[jdx], nxt);
            if (ch != 0) return (idx + 1);
            ch = cross_check (m_dict[jdx], m_dict[idx], nxt);
            if (ch != 0) return (idx + 1);
          }

      return 0;
    }
};

#endif

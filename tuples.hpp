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
  int bufsize;
  vector<int> buffer;
  vector<int> maxvals;
public:
  /* config is k-vector, config[k] is maximum value for k-th element */
  Tuples (vector<int> config) : bufsize(config.size()), 
    buffer(bufsize), maxvals(config) {}

  /* nxt is pure output parameter it will be discarded on entry */
  bool get_next (vector<int> &nxt)
    {
      int j;

      nxt = buffer;
      j = bufsize - 1;

      while ((j > -1) && (buffer[j] == maxvals[j]))
        {
          buffer[j] = 0;
          j = j - 1;
        }

      if (j == -1)
        return false;

      buffer[j] += 1;
      return true;
    }
};

/* [0 - n)-alphabet, k-position prime strings generator 
   based on 7.2.1.1-F */
class PrimeGen
{
  int suffix_len, string_len, max_letter;
  std::vector<int> buffer;

public:
  PrimeGen(int n, int k) : suffix_len(1), string_len(k), 
                           max_letter(n - 1), buffer(k+1) 
    { 
      assert (k > 1);
      assert (n > 1);
      buffer[0] = -1; 
    }

  bool get_next (std::vector<int>& out)
    {
      /* See Knuth-7.2.1.1-F for details */
      for (;;)
        {
          int ext;

          if (suffix_len == string_len)
            {
              assert (out.size() == static_cast<size_t>(string_len));
              std::copy(buffer.begin() + 1, buffer.end(), out.begin());
              suffix_len = 0; 
              return true;
            }

          /* find proper suffix lenght */
          suffix_len = string_len;
          while (buffer[suffix_len] == max_letter)
            suffix_len -= 1;          

          /* here a[0] .. a[j] is pre-prime 
             beacuse any proper suffix is pre-prime */
          if (suffix_len == 0)
            return false;

          /* increment pre-prime to make prime */
          buffer[suffix_len] += 1;

          /* k-extension of string */
          for (ext = suffix_len + 1; ext <= string_len; ext++)
            buffer[ext] = buffer[ext - suffix_len];
        }
    }
};

#endif

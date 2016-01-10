//===-- cf_all_path.cpp -- generator of all paths inside equiv. classes ---===//
//
// This file is distributed under the GNU GPL v3 License. 
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains an executable programm which generates all paths in 
// n-lets of digits like:
//
// All possibilities:
// 0 0 1    0 1 0    1 0 0    
// 0 1 1    1 1 0    1 0 1    
// All routes:
// 0 0  : ok
// 0 1  : ok
// 0 2  : ok
// 1 0  : ok
// 1 1  : ok
// 1 2  : ok
// 2 0  : ok
// 2 1  : ok
// 2 2  : ok
// 2 2  : ok
//
// in this simpole case all routes will be comma-free but in slightly harder 
// cases (try ./cf_all_path 2 3) percent of comma-free routes will be lower:
// about 427/6562
//
//===----------------------------------------------------------------------===//

#include <vector>
#include <algorithm>
#include <iostream>

#include "tuples.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;

static size_t
gcd (size_t a, size_t b)
{
  int r = a % b;

  while (r != 0)
    {
      a = b;
      b = r;
      r = a % b;
    }

  return b;
}

/* Juggling Algorithm for array rotation */
static void
make_cperm (vector<int> &c, int lshift)
{
  size_t n = c.size(), i;

  if (lshift == 0)
    return;

  for (i = 0; i < gcd (n, lshift); ++i)
    {
      int temp = c[i];
      size_t j = i;
      while (1)
        {
          size_t k = j + lshift;
          if (k >= n)
            k -= n;
          if (k == i)
            break;
          c[j] = c[k];
          j = k;
        }
      c[j] = temp;
    }
}

static void
display_all_possibilities (const vector< vector<int> > &out)
{
  cout << "All possibilities:" << endl;
  for (const auto &x: out)
    {
      vector<int> perm = x;
      size_t nperms = x.size(), i;
      for (i = 0; i != nperms; ++i)
        {
          for (auto &e: perm)
            cout << e << " ";
          cout << "   ";
          make_cperm (perm, 1);
        }
      cout << endl;
    }
}

static void
display_all_routes (const vector< vector<int> > &out, int k)
{
  vector<int> config(out.size(), k - 1);
  Tuples t(config);

  bool ok = true, ok2 = true;
  int nall = 0, nok = 0;
  vector<int> nxt;
  cout << "All routes:" << endl;

  do {
    if (!ok) 
      ok2 = false;

    if (ok2)
      ok = t.get_next(nxt);

    Cfdict d (k);
    bool xfail = false;
    size_t j, nxsz = nxt.size();
    for (j = 0; j != nxsz; ++j)
      {
        vector<int> perm = out[j];
        make_cperm(perm, nxt[j]);

        cout << nxt[j] << " ";
        if (0 != d.add_tuple (perm, true))
          xfail = true;
      }
    nall += 1; 
    if (!xfail)
      {
        cout << " : ok";
        nok += 1;
      }
    else
      cout << " : fail";

    cout << endl;
  } while (ok2);

  cout << nok << " from " << nall << " accepted" << endl;
}

void process_command_line (int argc, char **argv, int &n, int &k);

int 
main (int argc, char **argv)
{
  int n, k;

  process_command_line (argc, argv, n, k);

  vector<int> config(k, n);
  vector< vector<int> > out;

  Tuples t(config);
  t.get_all_cf_reprs (out);
  display_all_possibilities (out);
  display_all_routes (out, k);

  return 0;
}

void
process_command_line (int argc, char **argv, int &n, int &k)
{
  if (argc < 3)
    {
      cerr << "usage: \"" << argv[0] << " n k\" where n "
              "is alphabet delimiter [0 .. n] and k is position count" << endl;
      throw std::runtime_error("incorrect command line");
    }

  n = atoi (argv[1]);
  k = atoi (argv[2]);

  if ((n <= 0) || (k <= 0))
    {
      cerr << "Both n and k shall be > 0" << endl;
      throw std::runtime_error("incorrect command line");
    }
}


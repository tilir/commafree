//===-- cf_gen.cpp -- generator of digit series for comma-freeness -------===//
//
// This file is distributed under the GNU GPL v3 License. 
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains an executable programm which generates n-lets of
// digits like:
//
// 0 0 1
// 0 1 1
// 0 0 2
// ... etc ...
//
// this subset is minimal subset of cyclic shifts equivalence class 
// representatives (not necessary all of them are comma-free code)
//
// programm outputs lexicographically minimal representatives from every class
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <cstdlib>
#include "tuples.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::atoi;

void process_command_line (int argc, char **argv, int &n, int &k);

int
main (int argc, char **argv)
{
  int n, k;

  process_command_line (argc, argv, n, k);

  vector<int> res(k);

  PrimeGen pg(n, k);

  while (0 == pg.get_next(res))
    {
      for (auto a : res)
        cout << a << " ";
      cout << std::endl;
    }
  
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

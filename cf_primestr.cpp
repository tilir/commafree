//===-- cf_primestr.cpp -- generator of digit series for comma-freeness -------===//
//
// This file is distributed under the GNU GPL v3 License. 
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains an executable programm which generates k-lets of
// digits like:
//
// 0 0 0 0 1 
// 0 0 0 1 1 
// 0 0 1 0 1 
// 0 0 1 1 1 
// ... etc ...
//
// this subset is minimal subset of cyclic shifts equivalence class 
// representatives (not necessary all of them are comma-free code)
//
// now this is limited for 0/1 strings
//
// programm outputs lexicographically minimal representatives from every class
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <vector>

#include "tuples.hpp"

void process_command_line (int argc, char **argv, int &k);

int 
main (int argc, char **argv)
{
  int k;

  process_command_line (argc, argv, k);

  std::vector<int> res(k);

  PrimeGen pg(k);

  while (0 == pg.get_next(res))
    {
      for (auto a : res)
        std::cout << a << " ";
      std::cout << std::endl;
    } 

  return 0;
}

void
process_command_line (int argc, char **argv, int &k)
{
  if (argc < 2)
    {
      std::cerr << "usage: \"" << argv[0] << " n\" where k "
                   "is position count" << std::endl;
      throw std::runtime_error("incorrect command line");
    }

  k = atoi (argv[1]);

  if (k <= 1)
    {
      std::cerr << "k shall be > 1" << std::endl;
      throw std::runtime_error("incorrect command line");
    }
}


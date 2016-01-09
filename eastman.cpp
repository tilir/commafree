//===-------- eastman.cpp -- Eastman algorithm runner ---------------------===//
//
// This file is distributed under the GNU GPL v3 License. 
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains an executable programm which examines sequences of
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
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "cf_eastman.h"

using std::cout;
using std::cerr;
using std::endl;

void process_command_line (int argc, char **argv, std::vector<int> &xs);

int 
main (int argc, char **argv)
{
  std::vector<int> xs;  

  process_command_line (argc, argv, xs);

  int result = do_eastman (xs);

  cout << "required shift: " << result << endl;

  return 0;
}

void 
process_command_line (int argc, char **argv, std::vector<int> &xs)
{
  int n, idx;

  if (argc < 4)
    {
      cerr << "Usage " << argv[0] << " x1 x2 ... xn" << endl;
      throw std::runtime_error("incorrect command line");
    }

  n = argc - 1;

  if ((n % 2) == 0)
    {
      cerr << "Number of items n should be odd, not " << n << endl;
      throw std::runtime_error("incorrect command line");
    }

  bool corr = true;

  for (idx = 1; idx != argc; ++idx)
    {
      int x;
      std::istringstream ss(argv[idx]);
      if (!(ss >> x) || (x < 0))
        {
          cerr << "Argument #" << idx 
               << " should be a nonnegative integer, not " << argv[idx] 
               << endl;
          corr = false;
        }

      xs.push_back(x);
    }

  if (!corr)
    throw std::runtime_error("incorrect command line");
}



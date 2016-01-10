//===-- cf_check.cpp -- checker of digit series for comma-freeness -------===//
//
// This file is distributed under the GNU GPL v3 License. 
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains an executable programm which examines triples of
// digits like:
//
// 1 2 0
// 2 1 1
// 2 0 2
//
// to be comma free. In this case, last sequence will be rejected
// because 1 2 0 2 1 1 contains 2 0 2 in the midst
// i. e. suffix "2 0" is both head of "2 0 2" and tail of "1 2 0"
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "cf_dict.hpp"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::vector;

void process_command_line (int argc, char **argv, int &n);

int
main (int argc, char **argv)
{
  int n;

  process_command_line (argc, argv, n);

  std::vector<int> nxt(n);
  Cfdict d(n);

  cout << "Comma-free checker. Input space-separated numbers of size " << n << endl;

  while (cin)
    {
      std::string numbers_str;
      getline(cin, numbers_str, '\n');

      if (!cin)
        break;

      int number, idx = 0;
      for ( std::istringstream numbers_iss (numbers_str);
            numbers_iss >> number; ) 
        {
          if (idx < n)
            nxt[idx] = number;

          ++idx;
        }

      if (idx != n)
        {
          cout << "You should enter " << n << " space-separated numbers" << endl;
          continue;
        }
      
      int res = d.add_tuple(nxt, true);

      if (0 == res)
        continue;

      if (-1 == res)
        {
          cout << "Input is cyclic" << endl;
          continue;
        }

      cout << "error: ";
      for (const auto& x: d.m_lasterr)
        cout << x;
      cout << endl;
    }
}

void 
process_command_line (int argc, char **argv, int &n)
{
  if (argc < 2)
    {
      cerr << "usage: \"" << argv[0] << " n\" where n "
              "is word block count" << endl;
      throw std::runtime_error("incorrect command line");
    }

  n = atoi (argv[1]);

  if (n <= 0)
    {
      cerr << "Both n and k shall be > 0" << endl;
      throw std::runtime_error("incorrect command line");     
    }
}



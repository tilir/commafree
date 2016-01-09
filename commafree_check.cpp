//===-- commafree_check.cpp -- checker of words for comma-freeness -------===//
//
// This file is distributed under the GNU GPL v3 License. 
// See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains an executable programm which examines sequences of
// letters like:
//
// dead
// beaf
// aced
// face
//
// to be comma free. In this case, last sequence will be rejected
// because beafaced contains face in the midst
// i. e. suffix "ace" is both head of "aced" and tail of "face"
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
  int idx, n, total = 0, accepted = 0;

  process_command_line (argc, argv, n);

  std::vector<int> nxt(n);
  Cfdict d(n);

  cout << "Comma-free checker. Input comma-free words of size " << n << endl;

  while (cin)
    {
      std::string char_str;
      getline(cin, char_str, '\n');

      if (!cin)
        break;

      char c;
      int idx = 0;
      for ( std::istringstream char_iss (char_str);
            char_iss >> c; ) 
        {
          if (idx < n)
            nxt[idx] = c;

          ++idx;
        }

      if (idx != n)
        {
          cout << "You should enter word of size " << n << endl;
          continue;
        }
      
      total += 1;

      int res = d.add_tuple(nxt, true);

      if (0 == res)
        {
          accepted += 1;
          continue;
        }

      if (-1 == res)
        {
          cout << "  rejecting: input is cyclic" << endl;
          continue;
        }

      cout << "  rejecting: ";
      for (const auto& x: d.m_lasterr)
        cout << (char)x;
      cout << endl;
    }
  
  cout << "Accepted " << accepted << " of " << total << " words." << endl;

  return 0;
}

void 
process_command_line (int argc, char **argv, int &n)
{
  if (argc < 2)
    {
      cerr << "usage: \"" << argv[0] << " n\" where n "
              "is word size" << endl;
      throw std::runtime_error("incorrect command line");
    }

  n = atoi (argv[1]);

  if (n <= 0)
    {
      cerr << "word size n shall be > 0" << endl;
      throw std::runtime_error("incorrect command line");     
    }
}



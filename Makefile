CXX ?= g++
CXXFLAGS ?= --std=c++11 -g3 -O0 -DDBGOUT -Wall -Wextra

all : cf_gen cf_check commafree_check eastman eastman_new cf_all_paths

cf_gen : cf_gen.cpp tuples.hpp cf_dict.hpp
	$(CXX) $(CXXFLAGS) cf_gen.cpp -o $@

cf_check : cf_check.cpp cf_dict.hpp
	$(CXX) $(CXXFLAGS) cf_check.cpp -o $@

commafree_check : commafree_check.cpp cf_dict.hpp
	$(CXX) $(CXXFLAGS) commafree_check.cpp -o $@

eastman : cf_eastman.cpp eastman.cpp cf_eastman.h
	$(CXX) $(CXXFLAGS) cf_eastman.cpp eastman.cpp -o $@

eastman_new : cf_eastman_new.cpp eastman.cpp cf_eastman.h
	$(CXX) $(CXXFLAGS) cf_eastman_new.cpp eastman.cpp -o $@

cf_all_paths : cf_all_paths.cpp tuples.hpp cf_dict.hpp
	$(CXX) $(CXXFLAGS) cf_all_paths.cpp -o $@

clean:
	rm -rf cf_gen cf_check commafree_check eastman eastman_new cf_all_paths a.out

CXXFLAGS += --std=c++11 -g3 -O0 -DDBGOUT

all : cf_gen cf_check commafree_check eastman

cf_gen : cf_gen.cpp tuples.hpp cf_dict.hpp

cf_check : cf_check.cpp cf_dict.hpp

commafree_check : commafree_check.cpp cf_dict.hpp

eastman : cf_eastman.cpp eastman.cpp cf_eastman.h

clean:
	rm -rf cf_gen cf_check commafree_check eastman a.out

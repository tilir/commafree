CXXFLAGS += --std=c++11 -g3 -O0 -DDBGOUT -Wall -Wextra

all : cf_gen cf_check commafree_check eastman new_eastman cf_all_paths cf_primestr

cf_gen : cf_gen.cpp tuples.hpp cf_dict.hpp

cf_check : cf_check.cpp cf_dict.hpp

commafree_check : commafree_check.cpp cf_dict.hpp

eastman : cf_eastman.cpp eastman.cpp cf_eastman.h

new_eastman : cf_eastman_new.cpp eastman.cpp cf_eastman.h

cf_all_paths : cf_all_paths.cpp tuples.hpp cf_dict.hpp

cf_primestr : cf_primestr.cpp tuples.hpp

clean:
	rm -rf cf_gen cf_check commafree_check eastman new_eastman cf_all_paths cf_primestr a.out

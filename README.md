# commafree
Comma free algorithms and software

author: Konstantin Vladimirov

email: konstantin.vladimirov@gmail.com

official web page: https://github.com/tilir/commafree

cf_gen -- generator of prime strings

cf_check -- checker of cf-dictionary (numbers)

commafree_check -- checker of cf-dictionary (letters)

eastman -- eastmans algorithm, basin-range implementation

new_eastman -- eastmans algorithm, dip implementation

cf_all_paths -- all paths generator from give stdin

useful pipes:

./cf_gen 3 3 | ./cf_all_paths 3

./cf_gen 2 7 | xargs -n 7 ./eastman

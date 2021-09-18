# Comparation
+ Case A: exploit common mechanism Using a map struct to find the access index
+ Case B: use 24bits information embedding in key value to find the access index, but has the risk of conflict needing second-search

# Compiling without any optimization to see output
+ g++ -O0 -g -W -Wall  main.c
+ g++ -O0 -g -W -Wall -DUSE_MAP -o b.out  main.c

# Result
==> Map Access increases the time cost, but the price is relatively small. you should consider the memory requirement of the map struct for all items
==> If the 24bits information embedding in key value can always find the pos,you should use it plusing a smaller map struct only for conflicting keys

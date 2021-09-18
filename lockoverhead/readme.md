# Design
simulate runtime behavior using basic read operation and write operation as the classic Turing machine

# Compiling without any optimization to see output
+ gcc -O0 -g -W -Wall  main.c
+ gcc -O0 -g -W -Wall -DUSE_LOCK -o b.out  main.c

# Result
--> Although a moudule is thread-safe, if it is  used only by one thread, the lock overhead is small !!!

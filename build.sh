#!/bin/bash
micorepath=$1
cd $micorepath
/opt/rocm/hip/bin/hipcc -fPIC -c $micorepath/source/*.c
gcc -shared -o $micorepath/lib/libmicore.so $micorepath/*.o
rm -f *.o
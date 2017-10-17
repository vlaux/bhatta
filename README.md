# bhatta

### how to compile & run

```
g++ -std=c++11 -o bhatta bhatta.cpp
# parallel 
g++ -std=c++11 -fopenmp -o bhatta bhatta.cpp

./bhatta <instance_name>

# example
./bhatta dataset/TestMay03.txt
```

### available parameters:

use like `-D<PARAM>` (eg. `-DPARALLEL`)

`DEBUG`: outputs debug information

`PARALLEL`: runs program in parallel using OpenMP (do not forget to also use `-fopenmp`)

`RESULTSFILE`: writes cores used (if parallel) and elapsed time to file (`<filename>.res`)
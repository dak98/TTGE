# Trace Theory Gaussian Elimination (TTGE)
Above repository contains a parallel implementation of the Gaussian elimination algorithm using Trace Theory mathematical formalizm.

# Trace Theory
The first step is to identify and define atomic operations of the algorithm which will serve as the backbone of our model:
* ![equation](http://latex.codecogs.com/gif.latex?A_{i,j}) - find a multiplier to substract i-th row from the j-th
* ![equation](http://latex.codecogs.com/gif.latex?B_{i,j,k}) - multiply k-th element of the i-th row by ![equation](http://latex.codecogs.com/gif.latex?A_{i,j})
* ![equation](http://latex.codecogs.com/gif.latex?C_{i,j,k}) - substract ![equation](http://latex.codecogs.com/gif.latex?B_{i,j,k}) from the k-th element of the j-th row

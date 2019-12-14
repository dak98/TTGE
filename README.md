# Trace Theory Gaussian Elimination (TTGE)
Above repository contains a parallel implementation of the Gaussian elimination algorithm using Trace Theory mathematical formalizm.

# Trace Theory
## Atomic operations
The first step is to identify and define atomic operations of the algorithm which will serve as the backbone of our model:
* ![equation](http://latex.codecogs.com/gif.latex?A_{i,j}) - find a multiplier to substract i-th row from the j-th
* ![equation](http://latex.codecogs.com/gif.latex?B_{i,j,k}) - multiply k-th element of the i-th row by ![equation](http://latex.codecogs.com/gif.latex?A_{i,j})
* ![equation](http://latex.codecogs.com/gif.latex?C_{i,j,k}) - substract ![equation](http://latex.codecogs.com/gif.latex?B_{i,j,k}) from the k-th element of the j-th row

## Trace Theory Alphabet
To implement Gaussian elimination for a ![equation](http://latex.codecogs.com/gif.latex?N\times%20N) matrix, we will use appropriate atomic operations. They create an alphabet:

![equation](http://latex.codecogs.com/gif.latex?\Sigma%3D%20\\{A_{i,j},%20B_{i,j,k},%20C_{i,j,k}%20\\}%20\quad%20\underset{1%20\leq%20i%20%3C%20N}{\forall}%20\\;%20\underset{i%20%3C%20j%20\leq%20N}{\forall}%20\\;%20\underset{i%20\leq%20k%20\leq%20N+1}{\forall})

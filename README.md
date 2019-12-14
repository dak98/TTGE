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

## Predecessors Set
To help us with further writing down equations we will now define a set of predecessors:

![equation](http://latex.codecogs.com/gif.latex?\Lambda%3D\Lambda_1\cup\Lambda_2\cup\Lambda_3),

where:
* ![equation](http://latex.codecogs.com/gif.latex?\Lambda_1%3D\\{%20(A_{i,j},%20B_{i,j,k}),%20(B_{i,j,k},%20C_{i,j,k})%20\\}%20\quad%20\underset{1%20\leq%20i%20%3C%20N}{\forall}%20\\;%20\underset{i%20%3C%20j%20\leq%20N}{\forall}%20\\;%20\underset{i%20\leq%20k%20\leq%20N+1}{\forall}),
* ![equation](http://latex.codecogs.com/gif.latex?\Lambda_2%3D\\{%20(C_{i-1,i,i},%20A_{i,j}),%20(C_{i-1,j,i},%20A_{i,j})%20\\}%20\quad%20\underset{2%20\leq%20i%20%3C%20N}{\forall}%20\\;%20\underset{i%20%3C%20j%20\leq%20N}{\forall}),
* ![equation](http://latex.codecogs.com/gif.latex?\Lambda_3%3D\\{%20(C_{i-1,i,k},%20B_{i,j,k}),%20(C_{i-1,j,k},%20C_{i,j,k})%20\\}%20\quad%20\underset{2%20\leq%20i%20%3C%20N}{\forall}%20\\;%20\underset{i%20%3C%20j%20\leq%20N}{\forall}%20\\;%20\underset{i%20%3C%20k%20\leq%20N+1}{\forall}).

## Dependency relation
The key element of Trace Theory is the relation *happens before*. In our case it will make use of of the predecessors set defined before:

![equation](http://latex.codecogs.com/gif.latex?D%3Dsym\\{\Lambda^+\\}\cup%20I_\Sigma),

where ![equation](http://latex.codecogs.com/gif.latex?sym\\{\cdot\\}) is an operation adding symetry to given relation and ![equation](http://latex.codecogs.com/gif.latex?I_\Sigma%3D\\{(a,a)%20\\;%20|%20\\;%20a%20\in%20\Sigma%20\\}).

### Independency relation
Although not used in further equations, it may sometimes be necessary to also derive the independency relation:

![equation](http://latex.codecogs.com/gif.latex?I%3D\Sigma^2%20-%20D),

where ![equation](http://latex.codecogs.com/gif.latex?D) is the previously defined dependency relation.

## Gaussian elimination as a trace
Using previously stated atomic operations, we will now describe the algorithm of Gaussian elimination for a ![equation](http://latex.codecogs.com/gif.latex?N\times%20N) matrix:

![equation](http://latex.codecogs.com/gif.latex?t%3Dt_1\circ%20t_2%20\circ%20\dots%20\circ%20t_{N-1}),

where ![equation](http://latex.codecogs.com/gif.latex?t_i%3D\langle%20A_{i,j},%20B_{i,j,k},%20C_{i,j,k}%20\rangle%20\quad%20\underset{i%20%3C%20j%20\leq%20N}{\forall}%20\\;%20\underset{i%20\leq%20k%20\leq%20N+1}{\forall}) and ![equation](http://latex.codecogs.com/gif.latex?\langle%20\\,%20\circ%20\\,%20\rangle) is the concatenation operation.

## Foata's normal form
The final step is to devide the trace into Foata's classes. Elements contained in the same class could be executed simultaneously and must all conclude before the next class could begin. Finally we get:

![equation](http://latex.codecogs.com/gif.latex?FNF%3DFNF_1%20\\;%20FNF_2%20\\;%20\dots%20\\;%20FNF_{N-1}),

where ![equation](http://latex.codecogs.com/gif.latex?FNF_i%3D[A_{i,j}]%20\\;%20[B_{i,j,k}]%20\\;%20[C_{i,j,k}]%20\\;%20\underset{i%20%3C%20j%20\leq%20N}{\forall}%20\\;%20\underset{i%20\leq%20k%20\leq%20N+1}{\forall}).

# Implementation
The main algorithm and the atomic operations described above are implemented in the `main.cpp` file. The `parallel_call.hpp` file contains template parallel `for` loops used to simultaneously execute elements of a single Foata's class.

# Usage
The project was verified to work under Debian 10 with gcc 8.3.0. To compile it use the command:
```
g++ main.cpp -std=c++17 -pthread -o tt
```
and to run it type:
```
./tt
```
## Input data
The supplied matrix must be of the form:
```
N (number of rows)
N lines of N numbers representing the matrix
...
N numbers for the vector from the right side of the equation
```
e.g.
```
4
4 5 2.3 1
-3 5 6.3 10
1.2 4.7 -9.8 1
2.4 2.8 -0.3 2
5 3.4 -7.8 4
```
gives a result
```
4
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
2.16191 -1.24868 0.588533 1.24214
```

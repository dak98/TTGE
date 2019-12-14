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


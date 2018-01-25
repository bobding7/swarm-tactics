# Traveling Salesperson Problem (TSP)
C++ implemetation of TSP by Christofides’ algorithm with Rebecca Sagalyn

Usage
-----------
```
make
```

```
./tsp example_input
```
where inputfile is a text file in the format:
```
0    x-coord    y-coord
1    x-coord    y-coord 
.
.
.
n-1  x-coord    y-coord

```
and _x-coord_ and _y-coord_ need to be integers, and _n_ is the number of cities

#### Program Output
A new file with n +1 lines where n is the number of cities. The first line is the length of the tour found. The next n lines contain the city identifiers in the order they are visited by the tour. Each city is listed exactly once in this list. 


Implementation
-----------
### 1. Christofides' Algorithm
Assumption: A complete graph _G_ = ( _V_,_E_,_w_ ) with edge weights that satisfy the triangle inequality _w_(_x,y_) + _w_(_y,z_) ≤ _w_(_x,z_).

1. Find a minimum spanning tree T of G
2. Let O be the set of vertices with an _odd_ degree in T
3. Find a minimum cost perfect matching M for these vertices
4. Add M to T to obtain multigraph H
5. Find a Eulerian tour of H
6. Convert the Eulerian tour into Hamiltonian path by skipping visited nodes (using shortcuts)

### 2. Two-Opt
Improve the path quality.

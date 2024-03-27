#pragma once

#include <iostream>
#include <limits>
#include <stack>
#include <stdexcept>
#include <vector>

constexpr int infinity = std::numeric_limits<int>::max();

struct State {
    int a; // Amount in jug A
    int b; // Amount in jug B

    // Where to go on each of the six actions
    int fillA;
    int fillB;
    int emptyA;
    int emptyB;
    int AtoB;
    int BtoA;

    // variables for dijkstra's method
    int previous;
    int distance;
    bool visited;

    // state constructor, default values are infinity unless specified
    State(int a=infinity, int b=infinity, 
          int fillA=infinity, int fillB=infinity, 
          int emptyA=infinity, int emptyB=infinity,
          int AtoB=infinity, int BtoA=infinity)
        : a(a), b(b),
          fillA(fillA), fillB(fillB),
          emptyA(emptyA), emptyB(emptyB),
          AtoB(AtoB), BtoA(BtoA),
          previous(infinity),
          distance(infinity), 
          visited(false) 
    {}
};

class Jug {
    private:
        int Ca;
        int Cb;
        int N;
        int cfA;
        int cfB;
        int ceA;
        int ceB;
        int cpAB;
        int cpBA;
        // graph is a vector of states
        std::vector<State> graph;
        const bool invalidInputs() const;
        const int stateNumber(int, int, int, int) const;
        void createGraph();

    public:
        Jug(int,int,int,int,int,int,int,int,int);
        // ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        const int solve(std::string&);

};
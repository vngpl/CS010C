#include "Jug.h"

Jug::Jug(int capacityA, int capacityB, int targetNum, int costFillA, int costFillB, int costEmptyA, int costEmptyB, int costPourAB, int costPourBA) 
        : Ca(capacityA), Cb(capacityB), N(targetNum), cfA(costFillA), cfB(costFillB), ceA(costEmptyA), ceB(costEmptyB), cpAB(costPourAB), cpBA(costPourBA) 
{}

// Jug::~Jug() {}

const int Jug::solve(std::string& solution) {
    // if inputs do not match program criteria, no solution (return -1)
	if (invalidInputs()) {
        solution = "";
		return -1;
	}

    // populate the vector with possible states
    createGraph();

    // initialize first state's distance to 0 and previous to infinty
    graph[0].distance = 0;
    // first state has no previous
    graph[0].previous = infinity;

    while (true) {
        int minDistance = infinity;
        int current = infinity;

        // Find the unvisited node with the shortest distance
        for (int i = 0; i < static_cast<int>(graph.size()); ++i) {
            if (graph[i].distance < minDistance && !graph[i].visited) {
                minDistance = graph[i].distance;
                current = i;
            }
        }

        // If no unvisited node with finite distance is found, solution does not exist
        if (minDistance == infinity) {
            return 0;
        }
        
        graph[current].visited = true;

        // Evaluate each possible action and update distances
        for (int i = 0; i < 6; ++i) {
            // each action results in new state and has a cost
            int actionState;
            int actionCost;

            // evaluates current state (can be 0 - 5), assigns new state and cost
            switch (i) {
                case 0: // fill A
                    actionState = graph[current].fillA;
                    actionCost = cfA;
                    break;
                case 1: // fill B
                    actionState = graph[current].fillB;
                    actionCost = cfB;
                    break;
                case 2: // empty A
                    actionState = graph[current].emptyA;
                    actionCost = ceA;
                    break;
                case 3: // empty B
                    actionState = graph[current].emptyB;
                    actionCost = ceB;
                    break;
                case 4: // transfer A to B
                    actionState = graph[current].AtoB;
                    actionCost = cpAB;
                    break;
                case 5: // transfer B to A
                    actionState = graph[current].BtoA;
                    actionCost = cpBA;
                    break;
            }

            // distance from current state is the current minimum distance + cost of moving to new state
            int actionDistance = minDistance + actionCost;
            // if new distance is less than current distance, update distance and assign previous state
            if (actionDistance < graph[actionState].distance) {
                graph[actionState].distance = actionDistance;
                graph[actionState].previous = current;
            }
        }

        // iterates until state containing solution is visited
        if (graph[N].visited) {
            break;
        }
    }

    // stack for storing steps
    std::stack<std::string> reverseStringOrder;
    int currentState = N;
    int previousState = 0;
    // backward traversal of states from end state to starting state
    while (currentState != 0) {
        previousState = graph[currentState].previous;
        // checks what the previous state was to add the step to the stack
        if (graph[previousState].fillA == currentState) {
            reverseStringOrder.push("fill A\n");
        } 
        else if (graph[previousState].fillB == currentState) {
            reverseStringOrder.push("fill B\n");
        } 
        else if (graph[previousState].emptyA == currentState) {
            reverseStringOrder.push("empty A\n");
        } 
        else if (graph[previousState].emptyB == currentState) {
            reverseStringOrder.push("empty B\n");
        } 
        else if (graph[previousState].AtoB == currentState) {
            reverseStringOrder.push("pour A B\n");
        } 
        else if (graph[previousState].BtoA == currentState) {
            reverseStringOrder.push("pour B A\n");
        }
        currentState = previousState;
    }

    // string stream containing steps
    std::ostringstream solnSteps;
    // iterates through stack to get reverse of backward traversal (sequential order)
    while (!reverseStringOrder.empty()) {
        // add top element to stream
        solnSteps << reverseStringOrder.top();
        // remove element and continue until stack is empty
        reverseStringOrder.pop();
    }

    // add 'success' step with solution's distance from initial state 
    solnSteps << "success " << graph[N].distance;

    // transfer string stream to 'solution' string
    solution = solnSteps.str();

    // reaches when solution is found and returns 1
    return 1;
}

// checks the following: 
    // costs and capacities are non-negative
    // capacity of 'b' is greater than or equal to capacity of 'a'
    // target volume is less than or equal to capacity of 'b'
    // capacities are under 1000
const bool Jug::invalidInputs() const {
	return (cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0 || Ca < 0 || Cb <= Ca || N >= Cb || Cb >= 1000);
}

const int Jug::stateNumber(int a, int b, int Ca, int Cb) const {
    // volume of 'a' or 'b' can not be greater than the capacity of the jug
	if (a > Ca or b > Cb) {
        throw std::runtime_error("domain error");
    }

    // returns state (index) of the new state in the vector
    return a * (Cb + 1) + b;
}

void Jug::createGraph() {
    // calculates new state based on action, volume, and capacity of 'a' and 'b'
    for(int a = 0; a <= Ca; ++a) {
        for(int b = 0; b <= Cb; ++b) {
            // Compute action fill A.  A will have Ca gallons. B unchanged
            // Compute action fill B.  A unchanged, B will have Cb gallons
            int fillA = stateNumber(Ca,b, Ca,Cb);
            int fillB = stateNumber(a,Cb, Ca,Cb);

            // For the empties... just set the appropriate amount to zero
            int emptyA = stateNumber(0,b, Ca,Cb);
            int emptyB = stateNumber(a,0, Ca,Cb);

            // For the transfers, we can only pour in as much as we have
            // in the "from" jug OR as much room as we have in the "to" jug
            int transferFromA = std::min(a, Cb - b);
            int AtoB = stateNumber(a - transferFromA,b + transferFromA, Ca,Cb);
            int transferFromB = std::min(b, Ca - a);
            int BtoA = stateNumber(a + transferFromB,b - transferFromB, Ca,Cb);

            // Note: We can use emplace_back here (look it up!)
            graph.emplace_back(State(a,b, fillA,fillB, emptyA,emptyB, AtoB,BtoA));
        }
    }
}
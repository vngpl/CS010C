#include <iostream>
#include <string>
#include "Jug.h"

using namespace std;

int main() {
    {
        string solution;
        // construct problem with parameters
        Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);
        // call solve on problem, if incorrect solution (!= 1), print error
        if (head.solve(solution) != 1) {
            cout << "Error 3" << endl;
        }
        cout << solution << endl << endl;
    }

    {
        string solution;
        Jug head(3, 5, 4, 1, 1, 1, 1, 1, 2);         
        if(head.solve(solution) != 1) {
            cout << "Error 3" << endl;
        }
        cout << solution << endl;
    }
    
    return 0;
}
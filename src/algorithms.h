// algorithm time benchmarking
#include "dancing_links.h"
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

// brute force sudoku solver
void brute_force_solve(int **&m);

// dancing links sudoku solver
/* vector<int**> dlx_solve(int**& m); */
void dlx_solve(int **&m);

bool compare_result(vector<int **> &a, vector<int **> &b);

// algorithm time benchmarking
#include "dancing_links.h"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// brute force sudoku solver
vector<int**> brute_force_solve(int**& m);

// dancing links sudoku solver
vector<int**> dlx_solve(int**& m);

bool compare_result(vector<int**>& a, vector<int**>& b);

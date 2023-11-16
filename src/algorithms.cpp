#include "algorithms.h"

using namespace std;

// brute force sudoku solver
vector<int**> brute_force_solve(int**& m) {
    vector<int**> solutions;
    auto start = chrono::high_resolution_clock::now();

    // todo!()

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "brute force: " << duration.count() << " microseconds" << endl;

    return solutions;
}

// dancing links sudoku solver
vector<int**> dlx_solve(int**& m) {
    vector<int**> solutions;
    auto start = chrono::high_resolution_clock::now();

    // todo!()

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "dancing links: " << duration.count() << " microseconds" << endl;

    return solutions;
}


bool compare_result(vector<int**>& a, vector<int**>& b) {
    if (a.size() != b.size()) {
        return false; // different number of solutions
    }

    for (int i = 0; i < a.size(); ++i) {
        // todo!()
    }

    return true;
}

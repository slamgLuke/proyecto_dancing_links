// algorithm time benchmarking
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
typedef vector<vector<int>> Matrix;

// brute force sudoku solver
vector<Matrix> brute_force(Matrix& m) {
    vector<Matrix> solutions;
    auto start = chrono::high_resolution_clock::now();

    // todo!()

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "brute force: " << duration.count() << " microseconds" << endl;

    return solutions;
}

// dancing links sudoku solver
vector<Matrix> dancing_links(Matrix& m) {
    vector<Matrix> solutions;
    auto start = chrono::high_resolution_clock::now();

    // todo!()

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "dancing links: " << duration.count() << " microseconds" << endl;

    return solutions;
}


bool compare(vector<Matrix>& a, vector<Matrix>& b) {
    if (a.size() != b.size()) {
        return false; // different number of solutions
    }

    for (int i = 0; i < a.size(); ++i) {
        // todo!()
    }

    return true;
}

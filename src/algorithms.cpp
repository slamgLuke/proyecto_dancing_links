#include "algorithms.h"

using namespace std;

int main() {
  int **m = new int *[9];
  for (int i = 0; i < 9; i++) {
    m[i] = new int[9];
    for (int j = 0; j < 9; j++)
      m[i][j] = 0;
  }
  m[0][6] = 2;
  cout << "initial matrix: " << endl;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++)
      cout << m[i][j] << " ";
    cout << endl;
  }
  dlx_solve(m);
}

// brute force sudoku solver
vector<int **> brute_force_solve(int **&m) {
  vector<int **> solutions;
  auto start = chrono::high_resolution_clock::now();

  // todo!()

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "brute force: " << duration.count() << " microseconds" << endl;

  return solutions;
}

// dancing links sudoku solver
/* vector<vector<int>> dlx_solve(vector<vector<int>> &m) { */
void dlx_solve(int **&m) {
  /* vector<int **> solutions; */
  DancingLinks *DL = new DancingLinks();
  auto start = chrono::high_resolution_clock::now();
  cout << "start" << endl;

  // todo!()
  DL->initDlx();
  cout << "init done" << endl;
  DL->coverExisted(m);
  cout << "covered existed" << endl;
  DL->solve(0);
  for (DancingNode *s : DL->solution) {
    int n = s->getN();
    int r = s->getRow();
    int c = s->getCol();
    m[r][c] = n;
  }

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "dancing links: " << duration.count() << " microseconds" << endl;

  /* return solutions; */
}

bool compare_result(vector<int **> &a, vector<int **> &b) {
  if (a.size() != b.size()) {
    return false; // different number of solutions
  }

  for (int i = 0; i < a.size(); ++i) {
    // todo!()
  }

  return true;
}

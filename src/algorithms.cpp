#include "algorithms.h"

using namespace std;

int main() {
  int **m = new int *[9];
  for (int i = 0; i < 9; i++) {
    m[i] = new int[9];
    for (int j = 0; j < 9; j++)
      m[i][j] = 0;
  }
  m[0][0] = 5;
  m[0][1] = 3;
  m[0][4] = 7;

  m[1][0] = 6;
  m[1][3] = 1;
  m[1][4] = 9;
  m[1][5] = 5;

  m[2][1] = 9;
  m[2][2] = 8;
  m[2][7] = 6;

  m[3][0] = 8;
  m[3][4] = 6;
  m[3][8] = 3;

  m[4][0] = 4;
  m[4][3] = 8;
  m[4][5] = 3;
  m[4][8] = 1;

  m[5][0] = 7;
  m[5][4] = 2;
  m[5][8] = 6;

  m[6][1] = 6;
  m[6][6] = 2;
  m[6][7] = 8;

  m[7][3] = 4;
  m[7][4] = 1;
  m[7][5] = 9;
  m[7][8] = 5;

  m[8][4] = 8;
  m[8][7] = 7;
  m[8][8] = 9;
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

  cout << "\nSOLUTION\n" << endl;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++)
      cout << m[i][j] << " ";
    cout << endl;
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

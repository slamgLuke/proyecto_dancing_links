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

  /* m[1][1] = 5; */

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

  // test
  /* for (int i = 0; i < 9; i++) { */
  /*   for (int j = 0; j < 9; j++) */
  /*     m[i][j] = 0; */
  /* } */
  /* m[0][0] = 1; */
  /* m[8][8] = 1; */

  int **m2 = new int *[9];
  for (int i = 0; i < 9; ++i) {
    m2[i] = new int[9];
    for (int j = 0; j < 9; ++j) {
      m2[i][j] = m[i][j];
    }
  }

  cout << "initial matrix: " << endl;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++)
      cout << m[i][j] << " ";
    cout << endl;
  }

  dlx_solve(m);
  cout << "---------" << endl;
  brute_force_solve(m2);
}

// Backtracking / Solucion ingenua
bool isValid(int **&m, int row, int col, int k) {
  for (int i = 0; i < 9; i++) {
    if (m[i][col] == k)
      return false;
    if (m[row][i] == k)
      return false;
    if (m[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == k)
      return false;
  }
  return true;
}

bool solveIngenuo(int **&board) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == 0) {
        for (int k = 1; k <= 9; k++) {
          if (isValid(board, i, j, k)) {
            board[i][j] = k;
            if (solveIngenuo(board) == true) {
              return true;
            }
            board[i][j] = 0;
          }
        }
        return false;
      }
    }
  }
  return true;
}

// brute force sudoku solver
void brute_force_solve(int **&m) {
  auto start = chrono::high_resolution_clock::now();

  // todo!()
  solveIngenuo(m);
  cout << "\nSOLUTION\n" << endl;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++)
      cout << m[i][j] << " ";
    cout << endl;
  }

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "brute force: " << duration.count() << " microseconds" << endl;
}

// dancing links sudoku solver
// las funciones son metodos de la clase "DancingLinks"
void dlx_solve(int **&m) {
  DancingLinks *DL = new DancingLinks();
  DL->initDlx();
  cout << "init done" << endl;
  DL->coverExisted(m);
  cout << "covered existed" << endl;
  auto start = chrono::high_resolution_clock::now();
  cout << "start" << endl;

  // todo!()
  /* DL->initDlx(); */
  /* cout << "init done" << endl; */
  /* DL->coverExisted(m); */
  /* cout << "covered existed" << endl; */
  DL->solve(0);
  cout << "SOLVED" << endl;
  /* cout << "solution size: " << DL->solution.size() << endl; */
  /* for (DancingNode *s : DL->solution) { */
  /* for (int i = 0; i < DL->solution.size(); i++) { */
  /*   cout << "i: " << i << endl; */
  /*   DancingNode *s = DL->solution[i]; */
  /*   cout << "rowID: " << s->rowID << endl; */
  /*   int n = s->getN(); */
  /*   cout << "got n" << endl; */
  /*   int r = s->getRow(); */
  /*   cout << "got r" << endl; */
  /*   int c = s->getCol(); */
  /*   cout << "got c" << endl; */
  /*   cout << "r: " << r << ", c: " << c << endl; */
  /*   m[r][c] = n; */
  /* } */

  cout << "\nSOLUTION\n" << endl;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++)
      /* cout << m[i][j] << " "; */
      cout << DL->matrix[i][j] << " ";
    cout << endl;
  }

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "dancing links: " << duration.count() << " microseconds" << endl;
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

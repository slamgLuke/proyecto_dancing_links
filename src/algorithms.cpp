#include "algorithms.h"

using namespace std;

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
    for (int j = 0; j < 9; j++) {
      /* cout << m[i][j] << " "; */
      cout << DL->matrix[i][j] << " ";
      m[i][j] = DL->matrix[i][j];
    }
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

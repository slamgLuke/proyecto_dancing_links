#include "dancing_links.h"

/* DancingLinks::DancingLinks() { n_cols = 0; } */

/* DancingLinks::DancingLinks(int cols) { */
DancingLinks::DancingLinks() {
  sentinel = new ColumnNode();
  heads = new ColumnNode[nCols];

  for (int i = 0; i < nCols; i++) {
    heads[i] = ColumnNode(i);
  }

  // cierre circular de las cabeceras con la sentinala
  sentinel->right = &heads[0];
  sentinel->left = &heads[nCols - 1];
  heads[0].left = sentinel;
  heads[nCols - 1].right = sentinel;

  // inicializacion de conexiones horizontales en cabeceras
  for (int i = 0, j = nCols - 1; i < nCols - 1; i++, j--) {
    heads[i].right = &heads[i + 1];
    heads[j].left = &heads[j - 1];
  }
}

void DancingLinks::cover(ColumnNode *col) {
  col->right->left = col->left;
  col->left->right = col->right;

  if (col->size > 0) {
    for (DancingNode *dn = col->down; dn != col; dn = dn->down) {
      cout << "check" << endl;
      cout << "1for rowID: " << dn->column->rowID << endl;
      for (DancingNode *dnr = dn->right; dnr != dn; dnr = dnr->right) {
        cout << "SUBcheck" << endl;
        cout << "2for rowID: " << dnr->rowID << endl;

        if (dnr->down != nullptr) {
          cout << "down exists" << endl;

          // TODO (FIX)
          if (dnr->down->up != nullptr) {
            cout << "up exists" << endl;
          } else {
            cout << "up is nullptr" << endl;
          }
        } else {
          cout << "down is nullptr" << endl;
        }

        dnr->down->up = dnr->up;
        dnr->up->down = dnr->down;
        dnr->column->size--;
      }
    }
  }
}

void DancingLinks::uncover(ColumnNode *col) {
  col->left->right = col;
  col->right->left = col;

  if (col->size > 0) {
    for (DancingNode *dn = col->up; dn != col; dn = dn->up) {
      for (DancingNode *dnl = dn->left; dnl != dn; dnl = dnl->left) {
        dnl->down->up = dnl;
        dnl->up->down = dnl;
        dnl->column->size++;
      }
    }
    col->right->left = col;
    col->left->right = col;
  }
}

void DancingLinks::coverExisted(int **&m) {
  int ns = 81;
  for (int i = 0; i < 9; i++) {
    cout << "i: " << i << endl;
    for (int j = 0; j < 9; j++) {
      cout << "j: " << j << endl;
      if (m[i][j] != 0) {
        int n = m[i][j] - 1;
        cout << "n: " << n << endl;
        /* int rid = n * 81 + i * 9 + j; */

        ColumnNode *nodeRow = &heads[27 * n + i];
        ColumnNode *nodeCol = &heads[27 * n + 9 + j];
        ColumnNode *nodeGrid = &heads[27 * n + 18 + (i / 3 * 3 + j / 3)];
        ColumnNode *nodeCord = &heads[81 * 3 + i * 9 + j];
        cout << "declarated" << endl;
        cover(nodeRow);
        cout << "cover1" << endl;
        cover(nodeCol);
        cout << "cover2" << endl;
        cover(nodeGrid);
        cout << "cover3" << endl;
        cover(nodeCord);
        cout << "cover4" << endl;
        --ns;
      }
    }
  }
  solution.resize(ns);
}

ColumnNode *DancingLinks::getMinColumn() {
  int minsz = static_cast<ColumnNode *>(sentinel->right)->size;
  ColumnNode *temp = static_cast<ColumnNode *>(sentinel->right);
  for (ColumnNode *i = static_cast<ColumnNode *>(sentinel->right);
       i != sentinel; i = static_cast<ColumnNode *>(i->right)) {
    if (i->size < minsz) {
      minsz = i->size;
      temp = i;
    }
  }
  return temp;
}

void DancingLinks::initDlx() {
  // bucle para inicializar las filas y nodos en la matriz
  for (int r = 0; r < nRows; r++) {
    int n = r / 81;       // numero en el grid
    int i = (r % 81) / 9; // fila en el grid
    int j = (r % 81) % 9; // columna en el grid

    // header nodes por cada restriccion de sudoku:
    //
    // fila     -> cada numero debe aparecer solo 1 vez por fila
    // 27 * n   -> Agrupa cada conjunto de 9 filas
    // + i      -> Desplazamiento segun la fila dentro del subgrid
    ColumnNode *nodeRow = &heads[27 * n + i];
    //
    // columna  -> cada numero debe aparecer solo 1 vez por columna
    // 27 * n   -> Agrupa cada conjunto de 9 filas
    // + 9 + j  -> Desplazamiento segun la columna dentro del subgrid
    ColumnNode *nodeCol = &heads[27 * n + 9 + j];
    //
    // subgrid  -> cada numero debe aparecer solo 1 vez por subgrid
    // 27 * n   -> Agrupa cada conjunto de 9 filas
    // + 18 + (i / 3 * 3 + j / 3)  -> Desplazamiento segun el subgrid actual
    ColumnNode *nodeGrid = &heads[27 * n + 18 + (i / 3 * 3 + j / 3)];
    //
    // coordenada  -> cada numero debe aparecer solo 1 vez por combinacion unica
    // 81 * 3      -> Agrupa cada combinacion unica
    // + i * 9 + j -> Desplazamiento segun la fila y columna
    ColumnNode *nodeCord = &heads[81 * 3 + i * 9 + j];

    // nuevo nodo para la fila actual
    DancingNode *nodeR =
        new DancingNode(nullptr, nullptr, nodeRow->up, nodeRow, nodeRow, r);
    nodeRow->up->down = nodeR;
    nodeRow->up = nodeR;
    //
    // nuevo nodo para la columna actual
    DancingNode *nodeC =
        new DancingNode(nodeR, nullptr, nodeCol->up, nodeCol, nodeCol, r);
    nodeCol->up->down = nodeC;
    nodeCol->up = nodeC;
    //
    // nuevo nodo para la subGrid actual
    DancingNode *nodeG =
        new DancingNode(nodeC, nullptr, nodeGrid->up, nodeGrid, nodeGrid, r);
    nodeGrid->up->down = nodeG;
    nodeGrid->up = nodeG;
    //
    // nuevo nodo para la coordenada actual
    DancingNode *nodeCd =
        new DancingNode(nodeG, nodeR, nodeCord->up, nodeCord, nodeCord, r);
    nodeCord->up->down = nodeCd;
    nodeCord->up = nodeCd;
    //
    // conexiones entre nodos
    nodeR->left = nodeCd;
    nodeR->right = nodeC;
    nodeC->right = nodeG;
    nodeG->right = nodeCd;
    //
    // incremento de tamaño a headers
    nodeRow->size++;
    nodeCol->size++;
    nodeGrid->size++;
    nodeCord->size++;
  }
}

int DancingLinks::solve(int k) {
  if (sentinel->right == sentinel)
    return 1;
  ColumnNode *col = getMinColumn();
  if (col->size == 0)
    return 0;
  cover(col);
  //
  for (DancingNode *i = col->down; i != col; i = i->down) {
    solution[k] = i;
    for (DancingNode *j = i->right; j != i; j = j->right)
      cover(j->column);
    if (solve(k + 1))
      return 1;
    for (DancingNode *j = i->left; j != i; j = j->left)
      cover(j->column);
  }
  //
  uncover(col);
  return 0;
}

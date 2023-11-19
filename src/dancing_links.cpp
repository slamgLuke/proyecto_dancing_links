#include "dancing_links.h"

/* DancingLinks::DancingLinks() { n_cols = 0; } */

/* DancingLinks::DancingLinks(int cols) { */
DancingLinks::DancingLinks() {
  sentinel = new DancingNode();
  heads = new DancingNode[nCols];

  /* for (int i = 0; i < nCols; i++) { */
  /*   heads[i] = DancingNode(i); */
  /* } */

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

void DancingLinks::cover(DancingNode *col) {
  col->right->left = col->left;
  col->left->right = col->right;

  if (col->size > 0) {
    for (DancingNode *dn = col->down; dn != col; dn = dn->down) {
      for (DancingNode *dnr = dn->right; dnr != dn; dnr = dnr->right) {
        dnr->down->up = dnr->up;
        dnr->up->down = dnr->down;
        dnr->column->size--;
      }
    }
  }
}

void DancingLinks::uncover(DancingNode *col) {
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
    for (int j = 0; j < 9; j++) {
      if (m[i][j] != 0) {
        int n = m[i][j] - 1;

        DancingNode *nodeRow = &heads[27 * n + i];
        DancingNode *nodeCol = &heads[27 * n + 9 + j];
        DancingNode *nodeGrid = &heads[27 * n + 18 + (i / 3 * 3 + j / 3)];
        DancingNode *nodeCord = &heads[81 * 3 + i * 9 + j];
        cover(nodeRow);
        cover(nodeCol);
        cover(nodeGrid);
        cover(nodeCord);
        --ns;
      }
    }
  }
  solution.resize(ns);
}

DancingNode *DancingLinks::getMinColumn() {
  int minsz = sentinel->right->size;
  DancingNode *temp = sentinel->right;
  for (DancingNode *i = sentinel->right; i != sentinel; i = i->right) {
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
    DancingNode *nodeRow = &heads[27 * n + i];
    //
    // columna  -> cada numero debe aparecer solo 1 vez por columna
    // 27 * n   -> Agrupa cada conjunto de 9 filas
    // + 9 + j  -> Desplazamiento segun la columna dentro del subgrid
    DancingNode *nodeCol = &heads[27 * n + 9 + j];
    //
    // subgrid  -> cada numero debe aparecer solo 1 vez por subgrid
    // 27 * n   -> Agrupa cada conjunto de 9 filas
    // + 18 + (i / 3 * 3 + j / 3)  -> Desplazamiento segun el subgrid actual
    DancingNode *nodeGrid = &heads[27 * n + 18 + (i / 3 * 3 + j / 3)];
    //
    // coordenada  -> cada numero debe aparecer solo 1 vez por combinacion unica
    // 81 * 3      -> Agrupa cada combinacion unica
    // + i * 9 + j -> Desplazamiento segun la fila y columna
    DancingNode *nodeCord = &heads[81 * 3 + i * 9 + j];

    // nuevo nodo para la fila actual
    DancingNode *nodeR =
        new DancingNode(nullptr, nullptr, nodeRow->up, nodeRow, nodeRow, 0, r);
    nodeRow->up->down = nodeR;
    nodeRow->up = nodeR;
    //
    // nuevo nodo para la columna actual
    DancingNode *nodeC =
        new DancingNode(nodeR, nullptr, nodeCol->up, nodeCol, nodeCol, 0, r);
    nodeCol->up->down = nodeC;
    nodeCol->up = nodeC;
    //
    // nuevo nodo para la subGrid actual
    DancingNode *nodeG =
        new DancingNode(nodeC, nullptr, nodeGrid->up, nodeGrid, nodeGrid, 0, r);
    nodeGrid->up->down = nodeG;
    nodeGrid->up = nodeG;
    //
    // nuevo nodo para la coordenada actual
    DancingNode *nodeCd =
        new DancingNode(nodeG, nodeR, nodeCord->up, nodeCord, nodeCord, 0, r);
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
  DancingNode *col = getMinColumn();
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

#include "dancing_node.h"

using namespace std;

class DancingLinks {
private:
  ColumnNode *head;
  int n_cols;

public:
  DancingLinks();
  DancingLinks(int cols);

  void cover(ColumnNode *col);
  void uncover(ColumnNode *col);
};

DancingLinks::DancingLinks() {
  n_cols = 0;
  head = nullptr;
}

DancingLinks::DancingLinks(int cols) {
  n_cols = cols;
  head = new ColumnNode(0);
  ColumnNode *temp = head;
  for (int i = 1; i < cols; i++) {
    ColumnNode *new_node = new ColumnNode(i);
    temp->right = new_node;
    new_node->left = temp;
    temp = new_node;
  }
}

void DancingLinks::cover(ColumnNode *col) {
  col->left->right = col->right;
  col->right->left = col->left;

  if (col->size > 0) {
    //
    for (DancingNode *dn = col->down; dn != col; dn = dn->down) {
      for (DancingNode *dnr = dn->right; dnr != dn; dnr = dnr->right) {
        dnr->down->up = dnr->up;
        dnr->up->down = dnr->down;
        col->size--;
      }
    }
  }
}

void DancingLinks::uncover(ColumnNode *col) {
  col->left->right = col;
  col->right->left = col;

  if (col->size > 0) {
    //
    for (DancingNode *dn = col->up; dn != col; dn = dn->up) {
      for (DancingNode *dnl = dn->left; dnl != dn; dnl = dnl->left) {
        dnl->down->up = dnl;
        dnl->up->down = dnl;
        col->size++;
      }
    }
    col->right->left = col;
    col->left->right = col;
  }
}

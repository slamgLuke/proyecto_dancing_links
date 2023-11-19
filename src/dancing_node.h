#include <iostream>

using namespace std;

struct ColumnNode;

struct DancingNode {
  DancingNode *left;
  DancingNode *right;
  DancingNode *up;
  DancingNode *down;
  ColumnNode *column;
  int rowID;

  DancingNode() { left = right = up = down = this; }
  DancingNode(DancingNode *l, DancingNode *r, DancingNode *u, DancingNode *d,
              ColumnNode *c, int rid)
      : left(l), right(r), up(u), down(d), column(c), rowID(rid) {}

  int getRow() { return (rowID % 81) / 9; }
  int getCol() { return (rowID % 81) % 9; }
  int getN() { return rowID / 81 + 1; }
};

struct ColumnNode : public DancingNode {
  int size{};
  int index;

  ColumnNode() : DancingNode(), index(-1) { rowID = -1; }
  ColumnNode(int n) : DancingNode(), index(n) { rowID = -1; }
};

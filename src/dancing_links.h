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


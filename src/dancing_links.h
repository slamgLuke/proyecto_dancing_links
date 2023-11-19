#include "dancing_node.h"
#include <vector>
#define nCols 9 * 9 * 4
#define nRows 9 * 9 * 9

using namespace std;

class DancingLinks {
private:
  ColumnNode *sentinel;
  ColumnNode *heads;
  /* int n_cols; */

public:
  DancingLinks();
  /* DancingLinks(int cols); */

  vector<DancingNode *> solution;
  void cover(ColumnNode *col);
  void uncover(ColumnNode *col);
  void coverExisted(int **&m);
  ColumnNode *getMinColumn();
  void initDlx();
  int solve(int k);
};

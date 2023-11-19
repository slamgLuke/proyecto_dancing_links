#include "dancing_node.h"
#include <vector>
#define nCols 9 * 9 * 4
#define nRows 9 * 9 * 9

using namespace std;

class DancingLinks {
private:
  DancingNode *sentinel;
  DancingNode *heads;

public:
  DancingLinks();

  vector<DancingNode *> solution;
  void cover(DancingNode *col);
  void uncover(DancingNode *col);
  void coverExisted(int **&m);
  DancingNode *getMinColumn();
  void initDlx();
  int solve(int k);
};

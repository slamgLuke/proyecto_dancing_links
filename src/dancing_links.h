#include "dancing_node.h"

using namespace std;

class DancingLinks {
   private:
    ColumnNode* root;
    int n_cols;

   public:
    DancingLinks(int cols, int rows);

    void cover(ColumnNode* col);
    void uncover(ColumnNode* col);
};

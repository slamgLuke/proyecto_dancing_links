#include <iostream>

using namespace std;

struct DancingNode {
    DancingNode* left;
    DancingNode* right;
    DancingNode* up;
    DancingNode* down;

    DancingNode() { left = right = up = down = nullptr; }
};

struct ColumnNode : public DancingNode {
    int size;
    string name;

    ColumnNode(string n) : DancingNode() {
        size = 0;
        name = n;
    }
};

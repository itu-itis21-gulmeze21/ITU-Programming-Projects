#include <vector>
#include "BT.h"

#ifndef SET
#define SET

class Set{
    public:
        vector<int> get_intersection(BT*, BT*);
        vector<int> get_union(BT*, BT*);
        void traverse(Node*,unordered_map<int,int>&);
};

#endif 
//
// Created by jesse wang on 2/23/17.
//

#ifndef CODE1_INC_ME_H
#define CODE1_INC_ME_H

#include <vector>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <climits>
#include <cstring>

using namespace std;

struct ListNode {
    int val;
    ListNode* next = nullptr;
    ListNode(int v) : val(v) {}
};

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode(int v) : val(v) {}
};

struct Interval {
    int start, end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

#endif //CODE1_INC_ME_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// 定義二元樹的節點結構
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 插入節點到二元搜尋樹
TreeNode* insertBST(TreeNode* root, int val) {
    if (root == nullptr) return new TreeNode(val);
    if (val < root->val) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

// 中序遍歷二元搜尋樹
void inorderTraversal(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}

// 打印二元搜尋樹
void printBST(TreeNode* root, int space = 0, int height = 10) {
    if (root == nullptr) return;
    space += height;
    printBST(root->right, space);
    cout << endl;
    for (int i = height; i < space; i++) cout << ' ';
    cout << root->val << "\n";
    printBST(root->left, space);
}

// 建立最大堆
void buildMaxHeap(vector<int>& heap) {
    make_heap(heap.begin(), heap.end());
}

// 打印最大堆
void printHeap(const vector<int>& heap) {
    int n = heap.size();
    for (int i = 0; i < n; ++i) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

// 打印最大堆的樹狀圖
void printHeapTree(const vector<int>& heap, int i = 0, int space = 0, int height = 10) {
    if (i >= heap.size()) return;
    space += height;
    if (2 * i + 2 < heap.size()) printHeapTree(heap, 2 * i + 2, space);
    cout << endl;
    for (int j = height; j < space; j++) cout << ' ';
    cout << heap[i] << "\n";
    if (2 * i + 1 < heap.size()) printHeapTree(heap, 2 * i + 1, space);
}

int main() {
    vector<int> values;
    int val;
    cout << "請輸入整數值（輸入非數字結束輸入）：" << endl;
    while (cin >> val) {
        values.push_back(val);
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // 建立二元搜尋樹
    TreeNode* bstRoot = nullptr;
    for (int v : values) {
        bstRoot = insertBST(bstRoot, v);
    }

    // 中序遍歷並打印二元搜尋樹
    vector<int> bstInorder;
    inorderTraversal(bstRoot, bstInorder);
    cout << "二元搜尋樹的中序遍歷結果：" << endl;
    for (int v : bstInorder) {
        cout << v << " ";
    }
    cout << endl;

    cout << "二元搜尋樹的樹狀圖：" << endl;
    printBST(bstRoot);

    // 建立最大堆
    vector<int> maxHeap = values;
    buildMaxHeap(maxHeap);

    // 打印最大堆
    cout << "最大堆的陣列表示：" << endl;
    printHeap(maxHeap);

    cout << "最大堆的樹狀圖：" << endl;
    printHeapTree(maxHeap);

    return 0;
}

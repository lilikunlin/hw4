#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
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

// 計算樹的高度
int getHeight(TreeNode* root) {
    if (root == nullptr) return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

// 中序遍歷二元搜尋樹
void inorderTraversal(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return;
    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}

// 打印二元搜尋樹
void printBST(TreeNode* root) {
    if (root == nullptr) return;
    int height = getHeight(root);
    int maxNodes = (1 << height) - 1; // 2^height - 1
    queue<TreeNode*> q;
    q.push(root);
    for (int level = 0; level < height; ++level) {
        int levelNodes = 1 << level; // 2^level
        int space = (maxNodes / levelNodes) - 1;
        for (int i = 0; i < levelNodes; ++i) {
            if (i > 0) cout << setw(space) << " ";
            TreeNode* node = q.front();
            q.pop();
            if (node) {
                cout << setw(2) << node->val;
                q.push(node->left);
                q.push(node->right);
            }
            else {
                cout << setw(2) << " ";
                q.push(nullptr);
                q.push(nullptr);
            }
        }
        cout << endl;
        if (level < height - 1) {
            for (int i = 0; i < levelNodes; ++i) {
                if (i > 0) cout << setw(space) << " ";
                cout << setw(2) << "/";
                cout << setw(2) << "\\";
            }
            cout << endl;
        }
    }
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
void printHeapTree(const vector<int>& heap) {
    int n = heap.size();
    int height = 0;
    while ((1 << height) - 1 < n) height++;
    int maxNodes = (1 << height) - 1; // 2^height - 1
    int i = 0;
    for (int level = 0; level < height; ++level) {
        int levelNodes = 1 << level; // 2^level
        int space = (maxNodes / levelNodes) - 1;
        for (int j = 0; j < levelNodes && i < n; ++j) {
            if (j > 0) cout << setw(space) << " ";
            cout << setw(2) << heap[i++];
        }
        cout << endl;
        if (level < height - 1) {
            for (int j = 0; j < levelNodes; ++j) {
                if (j > 0) cout << setw(space) << " ";
                cout << setw(2) << "/";
                cout << setw(2) << "\\";
            }
            cout << endl;
        }
    }
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

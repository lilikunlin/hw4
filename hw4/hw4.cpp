#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cmath>
using namespace std;

// 定義 BST 節點結構
struct BSTNode {
    int val;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// 定義 Max-Heap 的類別
class MaxHeap {
public:
    vector<int> heap;
    void insert(int val) {
        heap.push_back(val);
        int i = heap.size() - 1;
        while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
            swap(heap[(i - 1) / 2], heap[i]);
            i = (i - 1) / 2;
        }
    }
    void printArray() {
        for (int i : heap) {
            cout << i << " ";
        }
        cout << endl;
    }
};

// 插入節點到 BST
BSTNode* insertBST(BSTNode* root, int val) {
    if (!root) return new BSTNode(val);
    if (val < root->val)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);
    return root;
}

// 中序遍歷 BST 並存入陣列
void inorderTraversal(BSTNode* root, vector<int>& result) {
    if (!root) return;
    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}

// 打印樹狀圖 (針對完全二元樹結構)
void printTree(const vector<int>& arr) {
    if (arr.empty()) return;

    int n = arr.size();
    int levels = log2(n) + 1; // 計算樹的總層數

    for (int level = 0, idx = 0; level < levels; ++level) {
        int nodesInLevel = pow(2, level); // 該層的節點數
        int indent = pow(2, levels - level) - 1; // 首行縮排數
        int space = pow(2, levels - level + 1) - 1; // 節點之間的間隔

        cout << string(indent, ' '); // 首行縮排
        for (int j = 0; j < nodesInLevel && idx < n; ++j, ++idx) {
            cout << setw(2) << arr[idx];
            if (j < nodesInLevel - 1) // 節點間距
                cout << string(space, ' ');
        }
        cout << endl; // 換行
    }
}

int main() {
    vector<int> input;
    int num;

    // 輸入數值
    cout << "請輸入整數（以 -1 結束輸入）：";
    while (cin >> num && num != -1) {
        input.push_back(num);
    }

    // 建立 BST
    BSTNode* bstRoot = nullptr;
    for (int val : input) {
        bstRoot = insertBST(bstRoot, val);
    }

    // 中序遍歷 BST
    vector<int> bstInorder;
    inorderTraversal(bstRoot, bstInorder);

    // 建立 Max-Heap
    MaxHeap maxHeap;
    for (int val : input) {
        maxHeap.insert(val);
    }

    // 輸出 BST 結果
    cout << "\nBinary Search Tree (中序遍歷): ";
    for (int val : bstInorder) {
        cout << val << " ";
    }
    cout << "\nBST 的樹狀圖表示：" << endl;
    printTree(bstInorder);

    // 輸出 Max-Heap 結果
    cout << "\nMax-Heap (陣列): ";
    maxHeap.printArray();
    cout << "Max-Heap 的樹狀圖表示：" << endl;
    printTree(maxHeap.heap);

    return 0;
}

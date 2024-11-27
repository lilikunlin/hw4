#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
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

// 打印樹狀圖 (BST 和 Max-Heap 共用)
void printTree(vector<int>& arr, int index, int indent = 0) {
    if (index >= arr.size()) return;
    printTree(arr, 2 * index + 2, indent + 4);
    cout << setw(indent) << arr[index] << endl;
    printTree(arr, 2 * index + 1, indent + 4);
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
    printTree(bstInorder, 0);

    // 輸出 Max-Heap 結果
    cout << "\nMax-Heap (陣列): ";
    maxHeap.printArray();
    cout << "Max-Heap 的樹狀圖表示：" << endl;
    printTree(maxHeap.heap, 0);

    return 0;
}

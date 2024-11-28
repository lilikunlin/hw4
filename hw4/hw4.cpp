#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

// 定義二元樹的節點結構
struct TreeNode {
    int val; // 節點的值
    TreeNode* left; // 左子節點
    TreeNode* right; // 右子節點
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} // 節點的構造函數
};

// 插入節點到二元搜尋樹
TreeNode* insertBST(TreeNode* root, int val) {
    if (root == nullptr) return new TreeNode(val); // 如果根節點為空，創建新節點
    if (val < root->val) root->left = insertBST(root->left, val); // 如果插入值小於根節點值，遞迴插入到左子樹
    else root->right = insertBST(root->right, val); // 否則，遞迴插入到右子樹
    return root; // 返回根節點
}

// 計算樹的高度
int getHeight(TreeNode* root) {
    if (root == nullptr) return 0; // 如果根節點為空，高度為0
    return max(getHeight(root->left), getHeight(root->right)) + 1; // 遞迴計算左子樹和右子樹的高度，取最大值加1
}

// 中序遍歷二元搜尋樹
void inorderTraversal(TreeNode* root, vector<int>& result) {
    if (root == nullptr) return; // 如果根節點為空，返回
    inorderTraversal(root->left, result); // 遞迴遍歷左子樹
    result.push_back(root->val); // 訪問根節點
    inorderTraversal(root->right, result); // 遞迴遍歷右子樹
}

// 打印二元搜尋樹
void printBST(TreeNode* root) {
    if (root == nullptr) return; // 如果根節點為空，返回
    int height = getHeight(root); // 獲取樹的高度
    int maxNodes = (1 << height) - 1; // 計算最大節點數量 2^height - 1
    queue<TreeNode*> q; // 使用隊列進行層次遍歷
    q.push(root); // 將根節點加入隊列
    for (int level = 0; level < height; ++level) { // 遍歷每一層
        int levelNodes = 1 << level; // 計算當前層的節點數量 2^level
        int space = (maxNodes / levelNodes) - 1; // 計算節點之間的間距
        for (int i = 0; i < levelNodes; ++i) { // 遍歷當前層的每個節點
            if (i > 0) cout << setw(space) << " "; // 打印節點之間的間距
            TreeNode* node = q.front(); // 獲取隊列中的節點
            q.pop(); // 移除隊列中的節點
            if (node) { // 如果節點不為空
                cout << setw(2) << node->val; // 打印節點的值
                q.push(node->left); // 將左子節點加入隊列
                q.push(node->right); // 將右子節點加入隊列
            }
            else { // 如果節點為空
                cout << setw(2) << " "; // 打印空格
                q.push(nullptr); // 將空節點加入隊列
                q.push(nullptr); // 將空節點加入隊列
            }
        }
        cout << endl; // 換行
        if (level < height - 1) { // 如果不是最後一層
            for (int i = 0; i < levelNodes; ++i) { // 遍歷當前層的每個節點
                if (i > 0) cout << setw(space) << " "; // 打印節點之間的間距
                cout << setw(2) << "/"; // 打印左斜線
                cout << setw(2) << "\\"; // 打印右斜線
            }
            cout << endl; // 換行
        }
    }
}

// 建立最大堆
void buildMaxHeap(vector<int>& heap) {
    make_heap(heap.begin(), heap.end()); // 使用標準庫函數建立最大堆
}

// 打印最大堆
void printHeap(const vector<int>& heap) {
    int n = heap.size(); // 獲取堆的大小
    for (int i = 0; i < n; ++i) { // 遍歷堆中的每個元素
        cout << heap[i] << " "; // 打印元素
    }
    cout << endl; // 換行
}

// 打印最大堆的樹狀圖
void printHeapTree(const vector<int>& heap) {
    int n = heap.size(); // 獲取堆的大小
    int height = 0; // 初始化高度
    while ((1 << height) - 1 < n) height++; // 計算堆的高度
    int maxNodes = (1 << height) - 1; // 計算最大節點數量 2^height - 1
    int i = 0; // 初始化索引
    for (int level = 0; level < height; ++level) { // 遍歷每一層
        int levelNodes = 1 << level; // 計算當前層的節點數量 2^level
        int space = (maxNodes / levelNodes) - 1; // 計算節點之間的間距
        for (int j = 0; j < levelNodes && i < n; ++j) { // 遍歷當前層的每個節點
            if (j > 0) cout << setw(space) << " "; // 打印節點之間的間距
            cout << setw(2) << heap[i++]; // 打印節點的值
        }
        cout << endl; // 換行
        if (level < height - 1) { // 如果不是最後一層
            for (int j = 0; j < levelNodes; ++j) { // 遍歷當前層的每個節點
                if (j > 0) cout << setw(space) << " "; // 打印節點之間的間距
                cout << setw(2) << "/"; // 打印左斜線
                cout << setw(2) << "\\"; // 打印右斜線
            }
            cout << endl; // 換行
        }
    }
}

int main() {
    vector<int> values; // 存儲輸入的整數值
    int val; // 單個整數值
    cout << "請輸入整數值（輸入非數字結束輸入）：" << endl;
    while (cin >> val) { // 讀取整數值，直到輸入非數字為止
        values.push_back(val); // 將整數值加入向量
    }
    cin.clear(); // 清除錯誤標誌
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略輸入緩衝區中的剩餘字符

    // 建立二元搜尋樹
    TreeNode* bstRoot = nullptr; // 初始化二元搜尋樹的根節點
    for (int v : values) { // 遍歷輸入的整數值
        bstRoot = insertBST(bstRoot, v); // 將整數值插入二元搜尋樹
    }

    // 中序遍歷並打印二元搜尋樹
    vector<int> bstInorder; // 存儲中序遍歷結果
    inorderTraversal(bstRoot, bstInorder); // 中序遍歷二元搜尋樹
    cout << "二元搜尋樹的中序遍歷結果：" << endl;
    for (int v : bstInorder) { // 遍歷中序遍歷結果
        cout << v << " "; // 打印節點值
    }
    cout << endl; // 換行

    cout << "二元搜尋樹的樹狀圖：" << endl;
    printBST(bstRoot); // 打印二元搜尋樹的樹狀圖

    // 建立最大堆
    vector<int> maxHeap = values; // 初始化最大堆
    buildMaxHeap(maxHeap); // 建立最大堆

    // 打印最大堆
    cout << "最大堆的陣列表示：" << endl;
    printHeap(maxHeap); // 打印最大堆的陣列表示

    cout << "最大堆的樹狀圖：" << endl;
    printHeapTree(maxHeap); // 打印最大堆的樹狀圖

    return 0; // 返回0，表示程式正常結束
}

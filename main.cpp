#include <iostream>
#include <vector>
using namespace std;
class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}
    void insert(int value) {
        if (root == nullptr) {
            root = new TreeNode(value);
        } else {
            insertRecursive(root, value);
        }
    }

    int height() {
        return heightRecursive(root);
    }

private:
    TreeNode* root;

    void insertRecursive(TreeNode* node, int value) {
        if (value < node->value) {
            if (node->left == nullptr) {
                node->left = new TreeNode(value);
            } else {
                insertRecursive(node->left, value);
            }
        } else if (value > node->value) {
            if (node->right == nullptr) {
                node->right = new TreeNode(value);
            } else {
                insertRecursive(node->right, value);
            }
        }
    }

    int heightRecursive(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        } else {
            int leftHeight = heightRecursive(node->left);
            int rightHeight = heightRecursive(node->right);
            return max(leftHeight, rightHeight) + 1;
        }
    }
};

int main() {
    vector<int> inputSequence;
    int value;
    cin >> value;
    while ( value != 0) {
        inputSequence.push_back(value);
        cin >> value;
    }

    BinarySearchTree bst;
    for (int val : inputSequence) {
        bst.insert(val);
    }

    // Вывод высоты дерева
    cout << bst.height() << endl;

    return 0;
}
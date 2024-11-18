#include <iostream>
#include <vector>
#include <cmath> // Для std::abs
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

    // Метод вставки значения в дерево
    void insert(int value) {
        if (root == nullptr) {
            root = new TreeNode(value);
        } else {
            insertRecursive(root, value);
        }
    }

    // Метод нахождения второго по величине элемента
    int findPreMax() {
        if (!root) {
            throw runtime_error("NO");
        }

        TreeNode* node = root;
        TreeNode* preMax = nullptr;

        // Находим максимальный элемент
        while (node->right) {
            preMax = node; // Запоминаем текущий узел как предшественника
            node = node->right;
        }

        // Если у максимального узла есть левое поддерево
        if (node->left) {
            node = node->left;
            while (node->right) {
                node = node->right;
            }
            return node->value;
        }

        // Если левого поддерева нет, возвращаем предшественника
        if (preMax) {
            return preMax->value;
        }

        throw runtime_error("NO");
    }

    // Метод проверки, сбалансировано ли дерево
    bool isBalanced() {
        return checkBalance(root) != -1;
    }

    // Метод нахождения высоты дерева
    int height() {
        return heightRecursive(root);
    }

private:
    TreeNode* root;

    // Рекурсивный метод вставки
    void insertRecursive(TreeNode* node, int value) {
        if (value < node->value) {
            if (!node->left) {
                node->left = new TreeNode(value);
            } else {
                insertRecursive(node->left, value);
            }
        } else if (value > node->value) {
            if (!node->right) {
                node->right = new TreeNode(value);
            } else {
                insertRecursive(node->right, value);
            }
        }
    }

    // Рекурсивная проверка сбалансированности
    int checkBalance(TreeNode* node) {
        if (!node) {
            return 0; // Высота пустого дерева равна 0
        }

        int leftHeight = checkBalance(node->left);
        if (leftHeight == -1) return -1; // Если левое поддерево несбалансировано

        int rightHeight = checkBalance(node->right);
        if (rightHeight == -1) return -1; // Если правое поддерево несбалансировано

        // Проверяем разницу высот
        if (abs(leftHeight - rightHeight) > 1) {
            return -1; // Текущее дерево несбалансировано
        }

        return max(leftHeight, rightHeight) + 1; // Возвращаем высоту текущего узла
    }

    // Рекурсивное вычисление высоты дерева
    int heightRecursive(TreeNode* node) {
        if (!node) {
            return 0;
        }
        int leftHeight = heightRecursive(node->left);
        int rightHeight = heightRecursive(node->right);
        return max(leftHeight, rightHeight) + 1;
    }
};

int main() {
    vector<int> inputSequence;
    int value;

    cin >> value;
    while (value != 0) {
        inputSequence.push_back(value);
        cin >> value;
    }

    BinarySearchTree bst;
    for (int val : inputSequence) {
        bst.insert(val);
    }


    cout << (bst.isBalanced() ? "YES" : "NO") << endl;

    return 0;
}

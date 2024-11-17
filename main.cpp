#include <iostream>
#include <string>
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

    // Вставка элемента
    string insert(int value) {
        if (!root) {
            root = new TreeNode(value);
            return "DONE";
        }
        return insertRecursive(root, value);
    }

    // Удаление элемента
    string deleteValue(int value) {
        if (!root) return "CANNOT";
        if (search(value) == "NO") return "CANNOT";
        root = deleteRecursive(root, value);
        return "DONE";
    }

    // Поиск элемента
    string search(int value) const {
        return searchRecursive(root, value) ? "YES" : "NO";
    }

    // Вывод дерева
    void printTree() const {
        printTreeRecursive(root, 0);
    }

private:
    TreeNode* root;

    string insertRecursive(TreeNode* node, int value) {
        if (value == node->value) return "ALREADY";
        if (value < node->value) {
            if (!node->left) {
                node->left = new TreeNode(value);
                return "DONE";
            }
            return insertRecursive(node->left, value);
        } else {
            if (!node->right) {
                node->right = new TreeNode(value);
                return "DONE";
            }
            return insertRecursive(node->right, value);
        }
    }

    TreeNode* deleteRecursive(TreeNode* node, int value) {
        if (!node) return nullptr;

        if (value < node->value) {
            node->left = deleteRecursive(node->left, value);
        } else if (value > node->value) {
            node->right = deleteRecursive(node->right, value);
        } else {
            // Найден узел для удаления
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // Узел имеет два поддерева
            TreeNode* maxNode = findMax(node->left);
            node->value = maxNode->value;
            node->left = deleteRecursive(node->left, maxNode->value);
        }
        return node;
    }

    TreeNode* findMax(TreeNode* node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    bool searchRecursive(TreeNode* node, int value) const {
        if (!node) return false;
        if (value == node->value) return true;
        if (value < node->value) return searchRecursive(node->left, value);
        return searchRecursive(node->right, value);
    }

    void printTreeRecursive(TreeNode* node, int level) const {
        if (!node) return;
        printTreeRecursive(node->left, level + 1);
        for (int i = 0; i < level; ++i) cout << ".";
        cout << node->value << endl;
        printTreeRecursive(node->right, level + 1);
    }
};

int main() {
    BinarySearchTree bst;
    string command;
    while (cin >> command) {
        if (command == "ADD") {
            int value;
            cin >> value;
            cout << bst.insert(value) << endl;
        } else if (command == "DELETE") {
            int value;
            cin >> value;
            cout << bst.deleteValue(value) << endl;
        } else if (command == "SEARCH") {
            int value;
            cin >> value;
            cout << bst.search(value) << endl;
        } else if (command == "PRINTTREE") {
            bst.printTree();
        }
    }
    return 0;
}

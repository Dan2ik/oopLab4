#include <iostream>
#include <string>
using namespace std;

// Узел бинарного дерева
class TreeNode {
public:
    int value; // Значение узла
    TreeNode* left; // Левый потомок
    TreeNode* right; // Правый потомок

    // Конструктор узла
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Класс бинарного дерева поиска
class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    // Метод вставки элемента
    string insert(int value) {
        if (!root) { // Если дерево пустое, создаем корень
            root = new TreeNode(value);
            return "DONE";
        }
        return insertRecursive(root, value); // Рекурсивная вставка
    }

    // Метод удаления элемента
    string deleteValue(int value) {
        if (!root) return "CANNOT"; // Если дерево пустое
        if (search(value) == "NO") return "CANNOT"; // Если элемента нет в дереве
        root = deleteRecursive(root, value); // Рекурсивное удаление
        return "DONE";
    }

    // Метод поиска элемента
    string search(int value) const {
        return searchRecursive(root, value) ? "YES" : "NO";
    }

    // Метод вывода дерева
    void printTree() const {
        printTreeRecursive(root, 0);
    }

private:
    TreeNode* root; // Корень дерева

    // Рекурсивный метод вставки
    string insertRecursive(TreeNode* node, int value) {
        if (value == node->value) return "ALREADY"; // Элемент уже существует
        if (value < node->value) { // Идем в левое поддерево
            if (!node->left) { // Если левого потомка нет
                node->left = new TreeNode(value);
                return "DONE";
            }
            return insertRecursive(node->left, value);
        } else { // Идем в правое поддерево
            if (!node->right) { // Если правого потомка нет
                node->right = new TreeNode(value);
                return "DONE";
            }
            return insertRecursive(node->right, value);
        }
    }

    // Рекурсивный метод удаления
    TreeNode* deleteRecursive(TreeNode* node, int value) {
        if (!node) return nullptr;

        if (value < node->value) {
            // левая часть
            node->left = deleteRecursive(node->left, value);
        } else if (value > node->value) {
            // правая часть
            node->right = deleteRecursive(node->right, value);
        } else {
            // Найден узел для удаления
            if (!node->left) {
                // Если нет левого потомка
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                // Если нет правого потомка
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // Если у узла два потомка, заменяем его значение на максимальное значение из левого поддерева
            TreeNode* maxNode = findMax(node->left);
            node->value = maxNode->value;
            node->left = deleteRecursive(node->left, maxNode->value); // Удаляем замененный узел
        }
        return node;
    }

    TreeNode* findMax(TreeNode* node) {
        while (node->right) { // просто берем крайний правый элемент
            node = node->right;
        }
        return node;
    }

    // Рекурсивный метод поиска элемента
    bool searchRecursive(TreeNode* node, int value) const {
        if (!node) return false; // Элемент не найден
        if (value == node->value) return true; // Элемент найден
        if (value < node->value) return searchRecursive(node->left, value); // Идем в левое поддерево
        return searchRecursive(node->right, value); // Идем в правое поддерево
    }

    // Рекурсивный метод для вывода дерева
    void printTreeRecursive(TreeNode* node, int level) const {
        if (!node) return;
        printTreeRecursive(node->left, level + 1); // Сначала левое поддерево
        for (int i = 0; i < level; ++i) cout << "."; // Вывод отступов
        cout << node->value << endl; // Вывод значения узла
        printTreeRecursive(node->right, level + 1); // Затем правое поддерево
    }
};

int main() {
    BinarySearchTree bst; // Создаем дерево
    string command; // Строка для хранения команды
    while (cin >> command) { // Читаем команды
        if (command == "ADD") {
            int value;
            cin >> value;
            cout << bst.insert(value) << endl; // Вставка элемента
        } else if (command == "DELETE") {
            int value;
            cin >> value;
            cout << bst.deleteValue(value) << endl; // Удаление элемента
        } else if (command == "SEARCH") {
            int value;
            cin >> value;
            cout << bst.search(value) << endl; // Поиск элемента
        } else if (command == "PRINTTREE") {
            bst.printTree(); // Вывод дерева
        }
    }
    return 0;
}

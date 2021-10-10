#include <iostream>
#include <queue>

struct node {
    int data;
    node* left;
    node* right;
};

class BST {
private:
    node* root;

    void insert(node* newNode, node*& tmp) {
        if (tmp == nullptr) {
            tmp = newNode;
            return;
        }
        if (newNode->data >= tmp->data)
            return insert(newNode, tmp->right);
        else
            return insert(newNode, tmp->left);
    }

    int height(node* tmp) {
        if (tmp == nullptr)
            return -1;
        return 1 + std::max(height(tmp->left), height(tmp->right));
    }

    void traverseInOrder(node* tmp) {
        if (tmp == nullptr)
            return;
        traverseInOrder(tmp->left);
        std::cout << tmp->data << std::endl;
        traverseInOrder(tmp->right);
    }

    void remove(int value, node* target, node* parent) {
        if (value > target->data)
            remove(value, target->right, target);
        else if (value < target->data)
            remove(value, target->left, target);
        else {
            if (target == root)
                root = removeRoute(target);
            else if (target->data > parent->data)
                parent->right = removeRoute(target);
            else
                parent->left = removeRoute(target);
        }
    }

    node* removeRoute(node* target) {
        if (target->right == nullptr && target->left == nullptr)
            return removeLeaf(target);
        else if (target->right != nullptr && target->left != nullptr)
            return removeTwoChildren(target);
        else
            return removeOneChild(target);
    }

    node* removeLeaf(node* target) {
        delete target;
        return nullptr;
    }

    node* removeOneChild(node* target) {
        node* tmp;
        if (target->right == nullptr) tmp = target->left;
        else tmp = target->right;
        delete target;
        return tmp;
    }

    node* removeTwoChildren(node* target) {
        node* tmp = target->left;
        while (tmp->right != nullptr)
            tmp = tmp->right;
        int data = tmp->data;
        remove(tmp->data);
        target->data = data;
        return target;
    }

public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        clear();
    }

    BST(const BST& another) {
        root = nullptr;
        std::queue<node*> q;
        if (another.root != nullptr)
            q.push(another.root);
        while (!q.empty()) {
            node* current = q.front();
            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
            q.pop();
            insert(current->data);
        }
    }

    BST& operator=(const BST& another) {
        if (this == &another)
            return *this;
        if (root != nullptr)
            clear();
        std::queue<node*> q;
        if (another.root != nullptr)
            q.push(another.root);
        while (!q.empty()) {
            node* current = q.front();
            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
            q.pop();
            insert(current->data);
        }
    }

    void insert(int value) {
        node* newNode = new node{ value , nullptr, nullptr };
        return insert(newNode, root);
    }

    void remove(int value) {
        remove(value, root, root);
    }

    int min() {
        node* tmp = root;
        while (tmp->left != nullptr)
            tmp = tmp->left;
        return tmp->data;
    }

    int max() {
        node* tmp = root;
        while (tmp->right != nullptr)
            tmp = tmp->right;
        return tmp->data;
    }

    int height() {
        return height(root);
    }

    void traverseLevelOrder() {
        std::queue<node*> q;
        if (root != nullptr)
            q.push(root);
        while (!q.empty()) {
            node* current = q.front();
            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
            std::cout << current->data << std::endl;
            q.pop();
        }
    }

    void traverseInOrder() {
        traverseInOrder(root);
    }

    bool contains(int value) {
        node* tmp = root;
        while (tmp != nullptr) {
            if (tmp->data == value)
                return true;
            else if (tmp->data > value)
                tmp = tmp->left;
            else
                tmp = tmp->right;
        }
        return false;
    }

    void clear() {
        std::queue<node*> q;
        if (root != nullptr)
            q.push(root);
        while (!q.empty()) {
            node* current = q.front();
            if (current->left != nullptr)
                q.push(current->left);
            if (current->right != nullptr)
                q.push(current->right);
            q.pop();
            delete current;
            root = nullptr;
        }
    }

};
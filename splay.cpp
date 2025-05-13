#include <iostream>
#include <fstream>
using namespace std;
ifstream f("abce.in");
ofstream g("abce.out");

struct Node {
    int key;
    Node *left, *right;
};

Node* newNode (int key) {
    Node* node = new Node();
    node->key = key;
    node->left = node->right = nullptr;
    return node;
}

Node* rightRotate (Node *x) {
    if (x == nullptr || x->left == nullptr)
        return x;
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* leftRotate (Node* x) {
    if (x == nullptr || x->right == nullptr)
        return x;
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* splay(Node* root, int key) {
    if (root == nullptr || root->key == key)
        return root;
    if (key < root->key) {
        if (root->left == nullptr)
            return root;
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (key > root->left->key) {
            root->left->right = splay (root->left->right, key);
            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }
        if (root->left != nullptr)
            root = rightRotate(root);
        return root;
    }
    else{
        if (root->right == nullptr)
            return root;

        if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        else if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr)
                root->right = rightRotate(root->right);
        }
        if (root->right != nullptr)
            root = leftRotate(root);
        return root;
    }
}

Node* insert (Node* root, int key) {
    if (root == nullptr)
        return newNode(key);
    root = splay(root, key);

    if (root->key == key)
        return root;
    Node* node = newNode(key);
    if (key < root->key) {
        node->right = root;
        node->left = root->left;
        root->left = nullptr;
    }
    else {
        node->left = root;
        node->right = root->right;
        root->right = nullptr;
    }
    return node;
}

Node* search(Node* root, int key) {
    return splay(root, key);
}

Node* getMax(Node* root) {
    if (root == nullptr || root->right == nullptr)
        return root;
    while (root->right != nullptr)
        root = root->right;
    return root;
}

Node* delNode (Node* root, int key) {
    if (root == nullptr)
        return nullptr;
    root = splay(root, key);
    if (root->key != key)
        return root;
    Node* temp;
    if (root->left != nullptr) {
        temp = splay (root->left, getMax(root->left)->key);
        temp->right = root->right;
    }
    else temp = root->right;
    delete root;
    return temp;
}

void preOrder (Node* root, int val) {
    if (root != nullptr) {
        cout << root->key << ", " << val << "  ";
        preOrder (root->left, val+1);
        preOrder (root->right, val+1);
    }
}

int smallest_greater_than (Node* root, int key) {

    if (root->key < key) {
        Node* temp = root->right;
        while (temp->left != nullptr)
            temp = temp->left;
        return temp->key;
    }
    else {
        return root->key;
    }
}

int greatest_smaller_than (Node* root, int key) {

    if (root->key > key) {
        Node* temp = root->left;
        while (temp->right != nullptr)
            temp = temp->right;
        return temp->key;
    }
    else {
        return root->key;
    }
}

void afis_interval (Node* root, int x, int y) { // inorder
    if (root == nullptr)
        return;
    if (root->key > x)
        afis_interval (root->left, x, y);
    if (root->key >= x && root->key <= y)
        g << root->key << ' ';
    if (root->key < y)
        afis_interval (root->right, x, y);
}



int main() {

    Node* root = nullptr;
    int n, op, x, y;
    f >> n;
    for (int i=0; i<n; ++i) {
        f >> op >> x;
        if (op == 1)
            root = insert (root, x);
        if (op == 2)
            root = delNode (root, x);
        if (op == 3) {
            root = search (root, x);
            if (root != nullptr && root->key == x)
                g << 1 << '\n';
            else g << 0 << '\n';
        }
        if (op == 4) {
            root = splay (root, x);
            g << greatest_smaller_than (root, x) << '\n';
        }
        if (op == 5) {
            root = splay (root, x);
            g << smallest_greater_than (root, x) << '\n';
        }
        if (op == 6) {
            f >> y;
            afis_interval (root, x, y);
            g << '\n';
        }

    }
    return 0;
}

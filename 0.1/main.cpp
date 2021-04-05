#include "gtest/gtest.h"
#include <fstream>
#include <string>

class BinaryTree {
private:
    struct Node {
    public:
        Node(long key) : key(key), right(nullptr), left(nullptr) {}

        long key;
        Node* right;
        Node* left;
    };

    Node* node;

    void PreOrderTraversal(std::ostream& fout, Node* pNode);

public:
    BinaryTree() : node(nullptr) {}
    ~BinaryTree();

    void Insert(const long& value);
    void Clear(Node* pNode);
    void AddValues(const std::string& fileName);
    void PreOrderTraversal();
};

BinaryTree::~BinaryTree() {
    Clear(node);
}

void BinaryTree::Insert(const long& value) {
    if(node == nullptr) {
        node = new Node(value);
    } else {
        Node* pNode = node;
        Node* parent;
        do {
            if(pNode->key == value)
                return;
            parent = pNode;
            pNode = pNode->key < value ? pNode->right : pNode->left;
        } while(pNode != nullptr);

        if(parent->key < value) {
            parent->right = new Node(value);
        } else {
            parent->left = new Node(value);
        }
    }
}

void BinaryTree::Clear(BinaryTree::Node *pNode) {
    if(pNode != nullptr) {
        Clear(pNode->left);
        Clear(pNode->right);
        delete pNode;
    }
}

void BinaryTree::AddValues(const std::string& fileName) {
    std::ifstream fin(fileName);
    std::string value;
    while(std::getline(fin, value)) {
        Insert(std::stol(value));
    }
    fin.close();
}

void BinaryTree::PreOrderTraversal(std::ostream& fout, BinaryTree::Node *pNode) {
    if(pNode != nullptr) {
        fout << pNode->key << '\n';
        PreOrderTraversal(fout, pNode->left);
        PreOrderTraversal(fout, pNode->right);
    }
}

void BinaryTree::PreOrderTraversal() {
    std::ofstream fout("output.txt");
    PreOrderTraversal(fout, node);
    fout.flush();
    fout.close();
}

int main() {
    BinaryTree tree;
    tree.AddValues("input.txt");
    tree.PreOrderTraversal();
    return 0;
}
#pragma comment(linker, "/STACK:16777216")

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
    Node *FindMin(Node *pNode);

public:
    BinaryTree() : node(nullptr) {}
    ~BinaryTree();

    void Insert(const long& value);
    void Remove(const long& value);
    void Clear(Node* pNode);
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

// правое удаление (в правом поддереве удаляемого элемента ищем мин)
void BinaryTree::Remove(const long& value) {
    Node* pNode = node;
    Node* parent = nullptr;

    if(pNode->key == value) {
        if (pNode->right == nullptr && pNode->left != nullptr ||
            pNode->right != nullptr && pNode->left == nullptr) { // left or right child exists
            node = pNode->right != nullptr ? pNode->right : pNode->left;
        } else if(pNode->right == nullptr && pNode->right == nullptr) {
            node = nullptr;
        } else { // left && right child exists
            Node* pMin = FindMin(pNode);
            pMin->right = pNode->right;
            pMin->left = pNode->left;
            node = pMin;
        }
        delete pNode;
        return;
    }

    while(pNode != nullptr) {
        if(pNode->key == value) {
            if(pNode->right == nullptr) {
                if(parent->left == pNode)
                    parent->left = pNode->left;
                else
                    parent->right = pNode->left;
            } else if (pNode->left == nullptr) {
                if(parent->left == pNode)
                    parent->left = pNode->right;
                else
                    parent->right = pNode->right;
            } else {
                Node* pMin = FindMin(pNode);
                pMin->right = pNode->right;
                pMin->left = pNode->left;
                if (parent->right == pNode)
                    parent->right = pMin;
                else
                    parent->left = pMin;
            }
            delete pNode;
            return;
        }
         parent = pNode;
         pNode = pNode->key < value ? pNode->right : pNode->left;
    }
}

BinaryTree::Node *BinaryTree::FindMin(BinaryTree::Node *pNode) {
    Node* pMin = pNode->right;
    Node* parent = pNode;
    while(pMin->left != nullptr) {
        parent = pMin;
        pMin = pMin->left;
    }
    if(parent->left == pMin)
        parent->left = pMin->right;
    else
        parent->right = pMin->right;
    return pMin;
}

int main() {
    BinaryTree tree;
    std::ifstream fin("input.txt");
    std::string value;

    std::getline(fin, value);
    long valueToDelete = std::stol(value);
    std::getline(fin, value);

    while(std::getline(fin, value)) {
        tree.Insert(std::stol(value));
    }
    fin.close();

    tree.Remove(valueToDelete);
    tree.PreOrderTraversal();
    return 0;
}
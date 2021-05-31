#pragma comment(linker, "/STACK:167772160")

#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>

class Node {
public:
    Node(long key) : key(key), right(nullptr), left(nullptr), mark(0) {}

    long key;
    Node* right;
    Node* left;

    long getMark() const {
        return mark;
    }

    void setMark(const long& value) {
        Node::mark = value;
    }
private:
    long mark;
};

class BinaryTree {
private:
    Node* node;

    void PreOrderTraversal(FILE* file, Node* pNode);
    Node *FindMin(Node *pNode);
    long GetMinLengthOfHalfway();
    void GetMinLengthOfHalfway(Node* pNode, long &minLength);
    std::vector<std::deque<Node *>> GetHalfwaysWithMinLengthAndWeight(long minLength);
    std::vector<std::deque<Node *>> GetHalfwaysWithMinLengthAndWeight(Node* pNode, long minLength, std::vector<std::deque<Node *>> &halfways, long& halfwayWeight);
    void RemoveCentreValue(std::vector<std::deque<Node *>> halfways, long minLength);
    void RemoveCentreValueFromHalfwayWithMinRoot(long length);
    void RemoveCentreValueFromHalfwayWithMinRoot(Node *pNode, long& rootKey, long minLength, std::deque<Node*>& deque);

public:
    BinaryTree() : node(nullptr) {}
    ~BinaryTree();

    void Insert(const long& value);
    void Remove(const long& value);
    void Clear(Node* pNode);
    void AddValues(const std::string& fileName);
    void PreOrderTraversal();
    bool RemoveMinCentreValueFromMinHalfway();
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

void BinaryTree::Clear(Node *pNode) {
    if(pNode != nullptr) {
        Clear(pNode->left);
        Clear(pNode->right);
        delete pNode;
    }
}

void BinaryTree::AddValues(const std::string& fileName) {
    freopen(fileName.c_str(), "r", stdin);
    long value;
    while(fscanf(stdin, "%ld", &value) != EOF) {
        Insert(value);
    }
}

void BinaryTree::PreOrderTraversal(FILE* file, Node *pNode) {
    if(pNode != nullptr) {
        fprintf(file, "%ld", pNode->key);
        fprintf(file, "%c", '\n');
        PreOrderTraversal(file, pNode->left);
        PreOrderTraversal(file, pNode->right);
    }
}

void BinaryTree::PreOrderTraversal() {
    freopen("out.txt", "w", stdout);
    PreOrderTraversal(stdout, node);
}

Node *BinaryTree::FindMin(Node *pNode) {
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

long BinaryTree::GetMinLengthOfHalfway() {
    long minLength = 0;
    GetMinLengthOfHalfway(node, minLength);
    return minLength;
}

void BinaryTree::GetMinLengthOfHalfway(Node *pNode, long& minLength) {
    if(pNode != nullptr) {
        GetMinLengthOfHalfway(pNode->left, minLength);
        GetMinLengthOfHalfway(pNode->right, minLength);
        if (pNode->right == nullptr && pNode->left != nullptr ||
            pNode->right != nullptr && pNode->left == nullptr) { // left or right child exists
            long mark = pNode->right != nullptr ? pNode->right->getMark() + 1 : pNode->left->getMark() + 1;
            pNode->setMark(mark);
        } else if(pNode->right == nullptr && pNode->right == nullptr) {
            pNode->setMark(0); // a leaf
        } else { // left && right child exists
            long mark = std::min(pNode->left->getMark(), pNode->right->getMark()) + 1;
            pNode->setMark(mark);
            long length = pNode->right->getMark() + pNode->left->getMark() + 2;
            if(minLength > length || minLength == 0) {
                minLength = length;
            }
        }
    }
}

std::vector<std::deque<Node *>> BinaryTree::GetHalfwaysWithMinLengthAndWeight(long minLength) {
    std::vector<std::deque<Node*>> halfwaysWithMinWeight;
    long halfwayWeight = LONG_MAX;
    return GetHalfwaysWithMinLengthAndWeight(node, minLength, halfwaysWithMinWeight, halfwayWeight);
}

std::vector<std::deque<Node *>>
BinaryTree::GetHalfwaysWithMinLengthAndWeight(Node* pNode, long minLength, std::vector<std::deque<Node *>> &halfways, long& halfwayWeight) {
    if(pNode != nullptr) {
        GetHalfwaysWithMinLengthAndWeight(pNode->left, minLength, halfways, halfwayWeight);
        GetHalfwaysWithMinLengthAndWeight(pNode->right, minLength, halfways, halfwayWeight);
        std::deque<Node*> deque;
        if (pNode->right != nullptr && pNode->left != nullptr) {
            if (pNode->right->getMark() + pNode->left->getMark() + 2 == minLength) {

                deque.push_front(pNode);
                Node *tempNode = pNode->left;
                deque.push_front(tempNode);
                long currHalfwayWeight = pNode->key + tempNode->key;

                while (tempNode->left != nullptr || tempNode->right != nullptr) {
                    currHalfwayWeight += tempNode->key;
                    if(tempNode->left != nullptr && tempNode->right != nullptr) {
                        tempNode = tempNode->left->getMark() < tempNode->right->getMark() ? tempNode->left
                                                                                          : tempNode->right;
                    } else if(tempNode->left == nullptr) {
                        tempNode = tempNode->right;
                    } else {
                        tempNode = tempNode->left;
                    }
                    deque.push_front(tempNode);
                }

                tempNode = pNode->right;
                deque.push_back(tempNode);
                currHalfwayWeight += tempNode->key;

                while (tempNode->left != nullptr || tempNode->right != nullptr) {
                    currHalfwayWeight += tempNode->key;
                    if(tempNode->left != nullptr && tempNode->right != nullptr) {
                        tempNode = tempNode->left->getMark() < tempNode->right->getMark() ? tempNode->left
                                                                                          : tempNode->right;
                    } else if(tempNode->left == nullptr) {
                        tempNode = tempNode->right;
                    } else {
                        tempNode = tempNode->left;
                    }
                    deque.push_back(tempNode);
                }
                if (!halfways.empty()) {
                    if (halfwayWeight == currHalfwayWeight) {
                        halfways.emplace_back(deque);
                        halfwayWeight = currHalfwayWeight;
                    } else if (halfwayWeight > currHalfwayWeight) {
                        halfways.clear();
                        halfways.emplace_back(deque);
                        halfwayWeight = currHalfwayWeight;
                    }
                } else {
                    halfways.emplace_back(deque);
                    halfwayWeight = currHalfwayWeight;
                }
            }
        }
    }
    return halfways;
}

void BinaryTree::RemoveCentreValue(std::vector<std::deque<Node*>> halfways, long minLength) {
    long index = minLength / 2;
    if (halfways.size() == 1) {
        Remove(halfways[0].at(index)->key);
    } else if(halfways.size() > 1) {
        RemoveCentreValueFromHalfwayWithMinRoot(minLength);
    }
}

bool BinaryTree::RemoveMinCentreValueFromMinHalfway() {
    long minLength = GetMinLengthOfHalfway();
    if(minLength % 2 == 0) {
        std::vector<std::deque<Node *>> halfways = GetHalfwaysWithMinLengthAndWeight(minLength);
        RemoveCentreValue(halfways, minLength);
        return true;
    }
    return false;
}

void BinaryTree::RemoveCentreValueFromHalfwayWithMinRoot(long minLength) {
    long rootKey = LONG_MAX;
    std::deque<Node*> deque;
    RemoveCentreValueFromHalfwayWithMinRoot(node, rootKey, minLength, deque);
    Remove(deque.at(minLength / 2)->key);
}

void BinaryTree::RemoveCentreValueFromHalfwayWithMinRoot(Node *pNode, long& rootKey, long minLength, std::deque<Node*>& deque) {
    if(pNode != nullptr) {
        RemoveCentreValueFromHalfwayWithMinRoot(pNode->left, rootKey, minLength, deque);
        RemoveCentreValueFromHalfwayWithMinRoot(pNode->right, rootKey, minLength, deque);
        if (pNode->right != nullptr && pNode->left != nullptr) {
            if (pNode->right->getMark() + pNode->left->getMark() + 2 == minLength) {
                if(pNode->key < rootKey) {
                    rootKey = pNode->key;
                    deque.clear();
                    deque.push_front(pNode);
                    Node *tempNode = pNode->left;
                    deque.push_front(tempNode);

                    while (tempNode->left != nullptr || tempNode->right != nullptr) {
                        if(tempNode->left != nullptr && tempNode->right != nullptr) {
                            tempNode = tempNode->left->getMark() < tempNode->right->getMark() ? tempNode->left
                                                                                              : tempNode->right;
                        } else if(tempNode->left == nullptr) {
                            tempNode = tempNode->right;
                        } else {
                            tempNode = tempNode->left;
                        }
                        deque.push_front(tempNode);
                    }

                    tempNode = pNode->right;
                    deque.push_back(tempNode);

                    while (tempNode->left != nullptr || tempNode->right != nullptr) {
                        if(tempNode->left != nullptr && tempNode->right != nullptr) {
                            tempNode = tempNode->left->getMark() < tempNode->right->getMark() ? tempNode->left
                                                                                              : tempNode->right;
                        } else if(tempNode->left == nullptr) {
                            tempNode = tempNode->right;
                        } else {
                            tempNode = tempNode->left;
                        }
                        deque.push_back(tempNode);
                    }
                }
            }
        }
    }
}

int main() {
    BinaryTree tree;
    tree.AddValues("in.txt");
    tree.RemoveMinCentreValueFromMinHalfway();
    tree.PreOrderTraversal();
    return 0;
}

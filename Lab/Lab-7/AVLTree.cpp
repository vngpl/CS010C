#include "AVLTree.h"

AVLTree::AVLTree() : root(nullptr) {}
AVLTree::~AVLTree() { destructTree(root); }

// recursively deallocates left and right subtree, lastly deleting final node (root)
void AVLTree::destructTree(Node* node) {
    if (node == nullptr) { return; }

    destructTree(node->left);
    destructTree(node->right);
    delete node;
}

// Insert an item to the binary search tree and perform rotation if necessary.
void AVLTree::insert(const string& key) {
    if (search(root, key)) {
        throw runtime_error("inserting a duplicate");
    }

    Node* newNode = new Node(key);

    // empty root case, key becomes root
    if (root == nullptr) {
        root = newNode;
        return;
    }

    // searches for key's position and inserts, assigning inserted node a parent
    Node* currNode = root;
    while (currNode != nullptr) {
        if (key < currNode->key) {
            // if left of current is nullptr, enter the node on the left
            if (currNode->left == nullptr) {
                currNode->left = newNode;
                newNode->parent = currNode;
                break;
            }
            // else, continue moving down left
            else {
                currNode = currNode->left;
            }
        }
        else {
            // enters node on the right once nullptr is reached
            if (currNode->right == nullptr) {
                currNode->right = newNode;
                newNode->parent = currNode;
                break;
            }
            else {
                currNode = currNode->right;
            }
        }
    }
    
    // reaches here after insertion (breaking out of while loop)
    // performs rotation on parent until root is reached
    newNode = newNode->parent;
    while (newNode != nullptr) {
        rotate(newNode);
        newNode = newNode->parent;
    }
}

// Return the balance factor of a given node.
int AVLTree::balanceFactor(Node* node) const {
    // if node's child is not null, gets height, otherwise height is -1
    int leftHeight = (node->left != nullptr) ? node->left->height : -1;
    int rightHeight = (node->right != nullptr) ? node->right->height : -1;
    return leftHeight - rightHeight;
}

// Prints the tree inorder with node's balance factor in parentheses
void AVLTree::printBalanceFactors() const { 
    if (root == nullptr) { 
        throw runtime_error("called printBalanceFactors() on an empty tree");
    }
    printBalanceFactors(root);
    cout << endl;
}
void AVLTree::printBalanceFactors(Node *node) const {
    if (node == nullptr) { return; }

    printBalanceFactors(node->left);
    cout << node->key << "(" << balanceFactor(node) << "), ";
    printBalanceFactors(node->right);
}

void AVLTree::updateHeight(Node* node) {
    // if node's child is not null, gets height, otherwise height is -1
    int leftHeight = (node->left != nullptr) ? node->left->height : -1;
    int rightHeight = (node->right != nullptr) ? node->right->height : -1;
    node->height = 1 + max(leftHeight, rightHeight);
}

void AVLTree::setChild(Node* parent, const string& whichChild, Node* child) {
    if (whichChild != "left" && whichChild != "right") {
        throw runtime_error("specify 'left' or 'right'");
    }
    // uses 'left' or 'right' to control whether child is on the left or right of parent
    if (whichChild == "left") {
        parent->left = child;
    }
    else {
        parent->right = child;
    }
    // sets child's parent to new parent
    if (child != nullptr) {
        child->parent = parent;
    }
    // recalculates height of the parent after moving child node
    updateHeight(parent);
}

void AVLTree::replaceChild(Node* parent, Node* currChild, Node* newChild) {
    // handles case for internal node for relocating child node
    if (parent->left == currChild) {
        setChild(parent, "left", newChild);
    }
    else if (parent->right == currChild) {
        setChild(parent, "right", newChild);
    }
}

void AVLTree::rotate(Node* node) {
    // updates the height of the node and stores the balance factor for comparison
    updateHeight(node);
    int balanceFactorOfNode = balanceFactor(node);

    // balance factor of -2 or 2 triggers rotation of node
    if (balanceFactorOfNode == -2) {
        // double rotation occurs when child's balance factor is positive 1
            // performs right rotation then left rotation
        if (balanceFactor(node->right) == 1) {
            rotateRight(node->right);
        }
        // performs left rotation due to right heaviness
        rotateLeft(node);
    }
    else if (balanceFactorOfNode == 2) {
        // performs left rotation then right rotation if left child's balance factor is -1
        if (balanceFactor(node->left) == -1) {
            rotateLeft(node->left);
        }
        rotateRight(node);
    }
}

// Rotate the subtree to left at the given node and returns the new subroot.
void AVLTree::rotateLeft(Node* node) {
    // get child of right node for rotation
    Node* rightLeftChild = node->right->left;
    // internal node case (has a parent)
    if (node->parent != nullptr) {
        replaceChild(node->parent, node, node->right);
    }
    // root case (parent is nullptr)
    else {
        root = node->right;
        root->parent = nullptr;
    }
    // performs rotation and fixes children of node
    setChild(node->right, "left", node);
    setChild(node, "right", rightLeftChild);
}

// Rotate the subtree to right at the given node and returns the new subroot.
void AVLTree::rotateRight(Node* node) {
    // get child of left node for rotation
    Node* leftRightChild = node->left->right;
    if (node->parent != nullptr) {
        replaceChild(node->parent, node, node->left);
    }
    else {
        root = node->left;
        root->parent = nullptr;
    }
    setChild(node->left, "right", node);
    setChild(node, "left", leftRightChild);
}

bool AVLTree::search(Node* node, const string& key) const {
	if (node == nullptr) { 
        return false;
    }

    // recursively search for key, returning true if found
	if (node->key == key) { 
        return true;
    }
	else if (key < node->key) { 
        return search(node->left, key);
    }
	else { 
        return search(node->right, key);
    }
}
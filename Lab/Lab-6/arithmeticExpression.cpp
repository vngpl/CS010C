#include "arithmeticExpression.h"

arithmeticExpression::arithmeticExpression(const string &expression) : infixExpression(expression), root(nullptr) {}
arithmeticExpression::~arithmeticExpression() { delete root; }

void arithmeticExpression::buildTree() {
    // get post fix expression from infix to postfix
    string postfixExpression = infix_to_postfix();
    // creates a stack to push on nodes
    stack<TreeNode*> nodeStack;

    // iterates character by character through post fix expression
    for (char c : postfixExpression) {
        // push non operand characters
        if (!(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')) {
            nodeStack.push(new TreeNode(c, c));
        }
        // handle operands
        else {
            // pop left and right operands off
            TreeNode* rightOperand = nodeStack.top();
            nodeStack.pop();
            TreeNode* leftOperand = nodeStack.top();
            nodeStack.pop();

            // construct new expression tree
            TreeNode* operatorNode = new TreeNode(c, c);
            operatorNode->right = rightOperand;
            operatorNode->left = leftOperand;

            // push expression to stack
            nodeStack.push(operatorNode);
        }
    }

    // set tree's root to top node
    root = nodeStack.top();
}

void arithmeticExpression::infix() { infix(root); }
void arithmeticExpression::prefix() { prefix(root); }
void arithmeticExpression::postfix() {postfix(root); }

// void arithmeticExpression::visualizeTree(const string &outputFilename) {
//     ofstream outFS(outputFilename.c_str());
//     if(!outFS.is_open()){
//         cout<<"Error opening "<< outputFilename<<endl;
//         return;
//     }
//     outFS<<"digraph G {"<<endl;
//     visualizeTree(outFS,root);
//     outFS<<"}";
//     outFS.close();
//     string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
//     string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
//     system(command.c_str());
// }

int arithmeticExpression::priority(char op){
    int priority = 0;
    if (op == '(') { priority =  3; }
    else if (op == '*' || op == '/') { priority = 2; }
    else if (op == '+' || op == '-') { priority = 1; }
    return priority;
}

string arithmeticExpression::infix_to_postfix() {
    stack<char> s;
    ostringstream oss;
    char c;
    // iterate through expression
    for (unsigned i = 0; i< infixExpression.size();++i) {
        c = infixExpression.at(i);
        // ignore spaces
        if (c == ' ') {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') { //c is an operator
            if( c == '(') {
                s.push(c);
            }
            else if(c == ')') {
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else {
                // checks priority before popping and appending to stack
                while (!s.empty() && priority(c) <= priority(s.top())) {
                    if (s.top() == '(') { break; }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else { //c is an operand
            oss << c;
        }
    }
    // send first element to output stream then pop
    while (!s.empty()) {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

// recursively print trees in infix, prefix, and postfix order
void arithmeticExpression::infix(TreeNode *tree) {
    if (tree == nullptr) { return; }
    if (tree->left != nullptr || tree->right != nullptr) { cout << "("; }
    infix(tree->left);
    cout << tree->data;
    infix(tree->right);
    if (tree->left != nullptr || tree->right != nullptr) { cout << ")"; }
}

void arithmeticExpression::prefix(TreeNode *tree) {
    if (tree == nullptr) { return; }
    cout << tree->data;
    prefix(tree->left);
    prefix(tree->right);
}

void arithmeticExpression::postfix(TreeNode *tree) {
    if (tree == nullptr) { return; }
    postfix(tree->left);
    postfix(tree->right);
    cout << tree->data;
}




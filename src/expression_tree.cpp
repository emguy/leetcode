/**
 * 1628. Design an Expression Tree With Evaluate Function
 * 
 * Given the postfix tokens of an arithmetic expression, build and return the
 * binary expression tree that represents this expression.
 * 
 * Postfix notation is a notation for writing arithmetic expressions in which
 * the operands (numbers) appear before their operators. For example, the
 * postfix tokens of the expression 4*(5-(7+2)) are represented in the array
 * postfix = ["4","5","7","2","+","-","*"].
 * 
 * The class Node is an interface you should use to implement the binary
 * expression tree. The returned tree will be tested using the evaluate
 * function, which is supposed to evaluate the tree's value. You should not
 * remove the Node class; however, you can modify it as you wish, and you can
 * define other classes to implement it if needed.
 * 
 * A binary expression tree is a kind of binary tree used to represent
 * arithmetic expressions. Each node of a binary expression tree has either
 * zero or two children. Leaf nodes (nodes with 0 children) correspond to
 * operands (numbers), and internal nodes (nodes with two children) correspond
 * to the operators '+' (addition), '-' (subtraction), '*' (multiplication),
 * and '/' (division).
 * 
 * It's guaranteed that no subtree will yield a value that exceeds 109 in
 * absolute value, and all the operations are valid (i.e., no division by
 * zero).
 * 
 * Follow up: Could you design the expression tree such that it is more
 * modular? For example, is your design able to support additional operators
 * without making changes to your existing evaluate implementation?
 * 
 *  
 * 
 * Example 1:
 * 
 * 
 * Input: s = ["3","4","+","2","*","7","/"]
 * Output: 2
 * Explanation: this expression evaluates to the above binary tree with
 * expression ((3+4)*2)/7) = 14/7 = 2.
 * Example 2:
 * 
 * 
 * Input: s = ["4","5","2","7","+","-","*"]
 * Output: -16
 * Explanation: this expression evaluates to the above binary tree with
 * expression 4*(5-(2+7)) = 4*(-4) = -16.
 *
 */


/**
 * This is the interface for the expression tree Node.
 * You should not remove it, and you can define some classes to implement it.
 */

class Node {
public:
  virtual ~Node () {};
  virtual int evaluate() const = 0;
protected:
    // define your fields here
};

class OpNode: public Node {
  public:
    OpNode* left{nullptr};
    OpNode* right{nullptr};
    char op{'x'};
    int value{0};
  
    OpNode(int value): value{value} {}
    OpNode(char op):  op{op} {}
    virtual int evaluate() const {
      if (!this->left && !this->right) {
        return this->value;
      }
      int l = this->left->evaluate();
      int r = this->right->evaluate();
      switch (this->op) {
        case '+':
          return l + r;
        case '-':
          return l - r;
        case '*':
          return l * r;
        case '/':
          return l / r;
        default:
          return 0;
      }
    }
    virtual ~OpNode() {
      if (this->left) {
        delete this->left;
      }
      if (this->right) {
        delete this->right;
      }
    }
};


/**
 * This is the TreeBuilder class.
 * You can treat it as the driver code that takes the postinfix input 
 * and returns the expression tree represnting it as a Node.
 */

class TreeBuilder {
public:
  Node* buildTree(vector<string>& postfix) {
      stack<OpNode*> stk{};
    
      for (int i = 0; i < postfix.size(); ++i) {
        bool isOp = postfix[i][0] < '0' || postfix[i][0] > '9';
        OpNode* cur = isOp ? new OpNode(postfix[i][0]) : new OpNode(stoi(postfix[i]));
        
        if (!isOp) {
          stk.push(cur);
          continue;
        }
        
        cur->right = stk.top();
        stk.pop();
        cur->left = stk.top();
        stk.pop();
        stk.push(cur);
      }
      return stk.top();
  }
};


/**
 * Your TreeBuilder object will be instantiated and called as such:
 * TreeBuilder* obj = new TreeBuilder();
 * Node* expTree = obj->buildTree(postfix);
 * int ans = expTree->evaluate();
 */

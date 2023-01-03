#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <stack>

using std::stack;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::pow;
using std::shared_ptr;
using std::make_shared;

void pressEnterToContinue();

class Node {
public:
    string data{};
    shared_ptr<Node> left{ nullptr };
    shared_ptr<Node> right{ nullptr };
};

class TreeParser : public Node {
private:
    stack<string> mathStack;
    double castStrToDouble(string const& s);
    string castDoubleToStr(const double d);
    void initialize();
    bool isDigit(char c);
    bool isOperator(char c);
    void processExpression(shared_ptr<Node> p);
    void computeAnswer(shared_ptr<Node> p);
    void inOrderTraversal(shared_ptr<Node> p) const; 
    void postOrderTraversal(shared_ptr<Node> p) const; 
protected:
    string expression;
    int position;
    shared_ptr<Node> root{ nullptr };
public:
    TreeParser();
    void displayParseTree();
    void processExpression(string& expression);
    string computeAnswer();
    void inOrderTraversal() const;
    void postOrderTraversal() const;
};

bool TreeParser::isDigit(char c) {
    if ((c >= 48) && (c <= 57))
        return true;
    else
        return false;
}

bool TreeParser::isOperator(char c) {
    if ((c == '-') || (c == '+') || (c == '*') || (c == '/') || (c == '^'))
        return true;
    else
        return false;
}

void TreeParser::processExpression(string& expression) {
    //void processExpression();

    if (sizeof(expression) == 0)
        return;

    this->expression = expression;
    this->position = 0;
    shared_ptr<Node> temp = make_shared<Node>();
    this->root = temp;
    processExpression(this->root);

}

void TreeParser::processExpression(shared_ptr<Node> p) {
    while (this->expression[position] >= this->position) {
        
            if (this->expression.at(position) == '(') {
                shared_ptr<Node> temp = make_shared<Node>();
                p->left = temp;
                this->position++;
                processExpression(p->left);
            }
            else if ((isDigit(this->expression[position])) || (this->expression[position] == '.')) {
                string temp = "";
                while ((isDigit(this->expression[position])) || (this->expression[position] == '.')) {
                    temp += this->expression.at(position);
                    this->position++;
                }
                //Had this->data here before, there is no data inside this object - hence nothing was being written
                p->data = temp;
                return;
            }
            else if ((this->expression.at(position) == '+') || (this->expression.at(position) == '-') || (this->expression.at(position) == '^') || (this->expression.at(position) == '/') || (this->expression.at(position) == '*')) {

                p->data = this->expression.at(position);
                shared_ptr<Node> temp = make_shared<Node>();
                //temp->left = nullptr;
                //temp->right = nullptr;
                p->right = temp;
                this->position++;
                processExpression(p->right);
            }
            else if (this->expression.at(position) == ')') {
                this->position++;
                return;
            }
            else if (this->expression.at(position) == ' ') {
                this->position++;
            }
        
    }
}

void TreeParser::inOrderTraversal() const {
    
    inOrderTraversal(this->root);
}

void TreeParser::inOrderTraversal(shared_ptr<Node> p) const {
    if (p) {
        inOrderTraversal(p->left); 
        cout << " " << p->data;        
        inOrderTraversal(p->right);
    }
}

void TreeParser::postOrderTraversal() const {
    
    postOrderTraversal(this->root);
}

void TreeParser::postOrderTraversal(shared_ptr<Node> p) const {
    if (p) {
        postOrderTraversal(p->left);
        postOrderTraversal(p->right);
        cout << " " << p->data;
    }
}


string TreeParser::computeAnswer() {
    computeAnswer(this->root);
    return mathStack.top();
}

void TreeParser::computeAnswer(shared_ptr<Node> p) {
    if (p) {
        computeAnswer(p->left);
        computeAnswer(p->right);

        if (isDigit(p->data[0])) { 
            mathStack.push(p->data);
        }
        else if (isOperator(p->data[0])) {
            string t1, t2;
            double result = 0.0;

            t1 = mathStack.top();
            double y = std::stod(t1);
            mathStack.pop();

            t2 = mathStack.top();
            double x = std::stod(t2);
            mathStack.pop();

            if (p->data.at(0) == '+')
                result = x + y;
            if (p->data.at(0) == '-')
                result = x - y;
            if (p->data.at(0) == '^')
                result = pow(x, y);
            if (p->data.at(0) == '*')
                result = x * y;
            if (p->data.at(0) == '/')
                result = x / y;

            string sresult = castDoubleToStr(result);
            mathStack.push(sresult);
        }
    }
}

void TreeParser::initialize() {
    expression = "";
    position = 0;
    while (!mathStack.empty()) {
        mathStack.pop();
    }
}

double TreeParser::castStrToDouble(const string& s) {
    istringstream iss(s);
    double x;
    iss >> x;
    return x;
}

string TreeParser::castDoubleToStr(const double d) {
    ostringstream oss;
    oss << d;
    return oss.str();

}

TreeParser::TreeParser() {
    initialize();
}


void TreeParser::displayParseTree() {
    cout << "The expression seen using in-order traversal: ";
    inOrderTraversal();
    cout << endl;
    cout << "The expression seen using post-order traversal: ";
    postOrderTraversal();
    cout << endl;

}

void pressEnterToContinue() {
    printf("Press Enter to continue\n");

    std::cin.get();

}

// Copyright 2021, Bradley Peterson, Weber State University, all rights reserved. (07/2021)

int main() {

    TreeParser* tp = new TreeParser;

    string expression = "(4+7)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 11 as a double output

    expression = "(7-4)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 3 as a double output

    expression = "(9*5)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 45 as a double output

    expression = "(4^3)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 64 as a double output

    expression = "((2-5)-5)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display -8 as a double output

    expression = "(5 * (6/2))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 15 as a double output

    expression = "((6 / 3) + (8 * 2))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 18 as a double output

    expression = "(543+321)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 864 as a double output

    expression = "(7.5-3.25)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 4.25 as a double output

    expression = "(5 + (34 - (7 * (32 / (16 * 0.5)))))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 11 as a double output
    //this is wrong 
    //figured out, needed >= rather than = in expression while loop

    expression = "((5*(3+2))+(7*(4+6)))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 95 as a double output


    expression = "(((2+3)*4)+(7+(8/2)))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 31 as a double output

    expression = "(((((3+12)-7)*120)/(2+3))^3)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display close to 7077888 as a double output
                                                                //NOTE, it won't be exact, it will display as scientific notation!

    expression = "(((((9+(2*(110-(30/2))))*8)+1000)/2)+(((3^4)+1)/2))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display close to 1337 as a double/decimal output
    //not quite right either
    //fixed by changing sizeof(this->expression) to this->expression[position] in the while loop.

    pressEnterToContinue();
    return 0;
}
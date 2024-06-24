#include <iostream>
#include <string>
#include "calculator.hpp"

using namespace std;

BinOp *Parser::parse_add_min(void)
{
    BinOp *node = this->parse_mul_div();
    BinOp *right = NULL;
    token_type_t op = UNKNOWN;
    while (current < tokens.size() && (tokens[current]->type == ADD_OPERATOR || tokens[current]->type == MIN_OPERATOR)) {
        op = tokens[current++]->type;
        right = this->parse_mul_div();
        node = new BinOp(node, right, 0, op);
    }
    return node;
}

BinOp *Parser::parse_mul_div(void)
{
    BinOp *node = this->parse_parantheses();
    BinOp *right = NULL;
    token_type_t op = UNKNOWN;
    while (current < tokens.size() && (tokens[current]->type == MUL_OPERATOR || tokens[current]->type == DIV_OPERATOR)) {
        op = tokens[current++]->type;
        right = this->parse_parantheses();
        node = new BinOp(node, right, 0, op);
    }
    return node;
}

BinOp *Parser::parse_parantheses(void)
{
    int open_p = 0;
    vector<token_t *> private_tokens;

    if (tokens.size() == 0)
        return new BinOp(NULL, NULL, 0, NUMBER);
    if (tokens[current]->type != O_PARENTHESE)
        return parse_nb();
    ++current;
    ++open_p;
    while (current < tokens.size() && open_p != 0) {
        if (tokens[current]->type == C_PARENTHESE)
            --open_p;
        if (tokens[current]->type == O_PARENTHESE)
            ++open_p;
        private_tokens.push_back(tokens[current]);
        ++current;
    }
    Parser newparser(private_tokens);
    BinOp *node = newparser.parse_add_min();
    private_tokens.clear();
    return node;
}

BinOp *Parser::parse_nb(void)
{
    if (tokens[current]->type == NUMBER) {
        int nb = stoi(tokens[current++]->value);
        return new BinOp(NULL, NULL, nb, NUMBER);
    } else {
        cout << tokens[current]->value << " Invalid\n";
        return new BinOp(NULL, NULL, 1, NUMBER);
    }
}

float BinOp::process_op(void)
{
    if (this->op == NUMBER)
        return value;
    switch (this->op) {
        case ADD_OPERATOR:
            return this->left->process_op() + this->right->process_op();
        case MIN_OPERATOR:
            return this->left->process_op() - this->right->process_op();
        case MUL_OPERATOR:
            return this->left->process_op() * this->right->process_op();
        case DIV_OPERATOR:
            return this->left->process_op() / this->right->process_op();
        default:
            cout << "Processing Error\n";
            return 1.0;
    }
}

BinOp::BinOp(BinOp *left, BinOp *right, float value, token_type_t op)
{
    this->left = left;
    this->right = right;
    this->op = op;
    this->value = value;
}

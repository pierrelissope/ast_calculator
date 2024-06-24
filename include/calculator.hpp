#include <iostream>
#include <vector>

#pragma once

enum token_type_t {
    NUMBER,

    ADD_OPERATOR,
    MIN_OPERATOR,
    MUL_OPERATOR,
    DIV_OPERATOR,

    O_PARENTHESE,
    C_PARENTHESE,

    UNKNOWN,
};

struct token_t {
    token_type_t type;
    std::string value;

    token_t(token_type_t token_type, std::string &token_value);
};


class BinOp {
public:
    token_type_t op;

    BinOp *left;
    BinOp *right;

    float value;

    BinOp(BinOp *left, BinOp *right, float value, token_type_t op);
    float process_op(void);
};

class Parser {
    public:
        std::vector<token_t *> tokens;
        size_t current = 0;

        Parser(std::vector<token_t *> tokens) { this->tokens = tokens; };
        ~Parser(void) = default;

        BinOp *parse_add_min(void);
        BinOp *parse_mul_div(void);
        BinOp *parse_parantheses(void);
        BinOp *parse_nb(void);
};

std::vector<token_t *> tokenizer(std::string expression);
void run(void);

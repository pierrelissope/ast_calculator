#include <iostream>
#include <string>
#include "calculator.hpp"

using namespace std;

void delete_binOp(BinOp *head)
{
    if (head->left == NULL && head->right == NULL) {
        delete head;
        return;
    }
    delete_binOp(head->left);
    delete_binOp(head->right);
    delete head;
}

void run(void)
{
    std::string user_input;

    cout << "Enter Your Math Expression: ";
    while (std::getline(cin, user_input)) {
        if (user_input == "exit")
            break;
        vector<token_t *> tokens = tokenizer(user_input);
        Parser parser(tokens);
        BinOp *head = parser.parse_add_min();
        cout << "Result: " << head->process_op() << "\n";
        for (auto i = tokens.begin(); i != tokens.end(); ++i)
            delete (*i);
        delete_binOp(head);
        tokens.clear();
        cout << "Enter Your Math Expression: ";
    }
}

#include <algorithm>
#include <ctype.h>
#include <map>

#include "calculator.hpp"

using namespace std;


static const map<string, token_type_t> operators_map =
{
    {"+", ADD_OPERATOR},
    {"-", MIN_OPERATOR},
    {"*", MUL_OPERATOR},
    {"/", DIV_OPERATOR},
    {"(", O_PARENTHESE},
    {")", C_PARENTHESE}
};

token_t::token_t(token_type_t token_type, std::string &token_value)
{
    this->type = token_type;
    this->value = token_value;
}

vector<token_t *> tokenizer(string expression)
{
    vector<token_t *> token_array;
    expression.erase(remove_if(expression.begin(), expression.end(), ::isspace), expression.end());

    token_t *token = NULL;
    size_t index = 0;
    size_t nb_len = 0;
    size_t expression_len = expression.length();

    while (index != expression_len) {
        if (isdigit(expression[index])) {
            nb_len = 0;
            while (isdigit(expression[index + nb_len]))
                ++nb_len;
            string value = expression.substr(index, nb_len);
            token = new token_t(NUMBER, value);
            token_array.push_back(token);
            index += (nb_len - 1);
        } else {
            string value(1, expression[index]);
            bool token_found = false;
            for (auto it = operators_map.begin(); it != operators_map.end(); ++it)
                if (it->first == value) {
                    token = new token_t(it->second, value);
                    token_array.push_back(token);
                    token_found = true;
                    break;
                }
            if (!token_found)
                cout << "Token: " << value << " Not reconized\n";
        }
        ++index;
    }
    return token_array;
}

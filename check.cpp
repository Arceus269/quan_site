#include <iostream>
#include <stack>
#include <string>

bool isMatchingPair(char character1, char character2) {
    if (character1 == '(' && character2 == ')')
        return true;
    else if (character1 == '[' && character2 == ']')
        return true;
    else if (character1 == '{' && character2 == '}')
        return true;
    else if (character1 == '<' && character2 == '>')
        return true;
    else
        return false;
}

bool areBracketsBalanced(const std::string& expression) {
    std::stack<char> stack;
    for (char bracket : expression) {
        if (bracket == '(' || bracket == '[' || bracket == '{' || bracket == '<') {
            stack.push(bracket);
        } else if (bracket == ')' || bracket == ']' || bracket == '}' || bracket == '>') {
            if (stack.empty() || !isMatchingPair(stack.top(), bracket)) {
                return false;
            } else {
                stack.pop();
            }
        }
    }
    return stack.empty();
}

int main() {
    std::string expression;
    std::cout << "Nhập biểu thức toán học: ";
    std::getline(std::cin, expression);

    if (areBracketsBalanced(expression)) {
        std::cout << "Các dấu ngoặc trong biểu thức được sắp xếp đúng." << std::endl;
    } else {
        std::cout << "Lỗi: Các dấu ngoặc trong biểu thức được sắp xếp sai." << std::endl;
    }

    return 0;
}

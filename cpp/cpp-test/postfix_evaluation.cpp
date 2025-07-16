







namespace others {

namespace postfix_expression {

class Stack {
 public:
    std::array<float, 20> stack{};
    int stackTop = -1;
};


void push(float operand, Stack *stack) {
    stack->stackTop++;
    stack->stack[stack->stackTop] = operand;
}


float pop(Stack *stack) {
    float operand = stack->stack[stack->stackTop];
    stack->stackTop--;
    return operand;
}


bool is_number(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}


void evaluate(float a, float b, const std::string &operation, Stack *stack) {
    float c = 0;
    const char *op = operation.c_str();
    switch (*op) {
        case '+':
            c = a + b;
            others::postfix_expression::push(c, stack);
            break;

        case '-':
            c = a - b;
            others::postfix_expression::push(c, stack);
            break;

        case '*':
            c = a * b;
            others::postfix_expression::push(c, stack);
            break;

        case '/':
            c = a / b;
            others::postfix_expression::push(c, stack);
            break;

        default:
            std::cout << "Operator not defined\n";
            break;
    }
}


template <std::size_t N>
float postfix_evaluation(std::array<std::string, N> input) {
    Stack stack;
    int j = 0;

    while (j < N) {
        std::string scan = input[j];
        if (is_number(scan)) {
            push(std::stof(scan), &stack);

        } else {
            float op2 = pop(&stack);
            float op1 = pop(&stack);

            evaluate(op1, op2, scan, &stack);
        }
        j++;
    }

    std::cout << stack.stack[stack.stackTop] << "\n";

    return stack.stack[stack.stackTop];
}
}
}



static void test_function_1() {
    std::array<std::string, 7> input = {"2", "3", "1", "*", "+", "9", "-"};

    float answer = others::postfix_expression::postfix_evaluation(input);

    assert(answer == -4);
}


static void test_function_2() {
    std::array<std::string, 9> input = {"100", "200", "+", "2", "/",
                                        "5",   "*",   "7", "+"};
    float answer = others::postfix_expression::postfix_evaluation(input);

    assert(answer == 757);
}


int main() {
    test_function_1();
    test_function_2();

    std::cout << "\nTest implementations passed!\n";

    return 0;
}

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

constexpr double evaluate_expression(const std::string& expression, std::size_t& index);

// Функция для вычисления значения числа
constexpr double evaluate_number(const std::string& expression, std::size_t& index) {
    // Инициализируем переменные
    double result = 0;
    bool negative = false;

    // Проверяем, есть ли знак "минус"
    if (expression[index] == '-') {
        negative = true;
        ++index; // Пропускаем знак "минус"
    }

    // Проверяем, является ли символ цифрой
    while (index < expression.length() && std::isdigit(expression[index])) {
        result = result * 10 + (expression[index] - '0');
        ++index;
    }

    // Возвращаем результат с учетом знака
    return negative ? -result : result;
}

// Функция для вычисления значения выражения
constexpr double evaluate_expression(const std::string& expression, std::size_t& index) {
    // Инициализируем переменные
    double result = 0;
    char last_operator = '+';

    // Парсим и вычисляем выражение до достижения закрывающей скобки или конца строки
    while (index < expression.length()) {
        // Пропускаем пробелы
        if (expression[index] == ' ') {
            ++index;
            continue;
        }

        // Если символ является числом, вычисляем его и применяем оператор к результату
        if (std::isdigit(expression[index])) {
            double number = evaluate_number(expression, index);
            if (last_operator == '+')
                result += number;
            else if (last_operator == '-')
                result -= number;
            else if (last_operator == '*')
                result *= number;
            else if (last_operator == '/')
                result /= number;
            else if (last_operator == '^')
                result = std::pow(result, number);
        }
            // Если символ является открывающей скобкой, вызываем функцию evaluate_expression рекурсивно для вычисления вложенного выражения
        else if (expression[index] == '(') {
            ++index;
            double nested_result = evaluate_expression(expression, index);
            if (last_operator == '+')
                result += nested_result;
            else if (last_operator == '-')
                result -= nested_result;
            else if (last_operator == '*')
                result *= nested_result;
            else if (last_operator == '/')
                result /= nested_result;
            else if (last_operator == '^')
                result = std::pow(result, nested_result);
        }
            // Если символ является знаком операции, сохраняем его
        else if (expression[index] == '+' || expression[index] == '-' ||
                 expression[index] == '*' || expression[index] == '/' ||
                 expression[index] == '^') {
            last_operator = expression[index];
            ++index;
        }
            // Если символ является закрывающей скобкой, выходим из функции и возвращаем результат
        else if (expression[index] == ')') {
            ++index;
            return result;
        }
            // Если символ не является допустимым символом в выражении, бросаем исключение
        else {
            throw std::runtime_error("Invalid character in expression");
        }
    }

    // Возвращаем результат
    return result;
}

int main() {
    std::string expression = "(67+987^(7-3*2))*(34-123)+17^2+(-1)";
    std::size_t index = 0;
    double result = evaluate_expression(expression, index);

    std::cout << "Expression: " << expression << std::endl;
    std::cout << "Result: " << result << std::endl;

    return 0;
}

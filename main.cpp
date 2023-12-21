#include <iostream>
#include <cctype>
#include <cstdlib>

class Parser
{
public:
    Parser(const std::string& input) : input_(input), pos_(0) {}

    int parse()
    {
        return parseExpression();
    }

private:
    char peek() const
    {
        return (pos_ < input_.size()) ? input_[pos_] : '\0';
    }

    char get()
    {
        return (pos_ < input_.size()) ? input_[pos_++] : '\0';
    }

    int parseExpression()
    {
        int result = parseTerm();
        while (peek() == '+' || peek() == '-')
        {
            if (get() == '+')
            {
                result += parseTerm();
            }
            else
            {
                result -= parseTerm();
            }
        }
        return result;
    }

    int parseTerm()
    {
        int result = parseFactor();
        while (peek() == '*' || peek() == '/')
        {
            if (get() == '*')
            {
                result *= parseFactor();
            }
            else
            {
                int divisor = parseFactor();
                if (divisor == 0)
                {
                    std::cerr << "Error: Division by zero\n";
                    std::exit(1);
                }
                result /= divisor;
            }
        }
        return result;
    }

    int parseFactor()
    {
        if (std::isdigit(peek()))
        {
            return get() - '0';
        }
        else if (peek() == '(')
        {
            get(); // Consume '('
            int result = parseExpression();
            if (get() != ')')
            {
                std::cerr << "Error: Expected ')'\n";
                std::exit(1);
            }
            return result;
        }
        else
        {
            std::cerr << "Error: Unexpected character\n";
            std::exit(1);
        }
    }

    std::string input_;
    std::size_t pos_;
};

int main()
{
    std::string input;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, input);

    Parser parser(input);
    int result = parser.parse();

    std::cout << "Result: " << result << std::endl;

    return 0;
}


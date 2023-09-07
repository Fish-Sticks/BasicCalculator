#include "calculator.hpp"
#include "internal/lexer/lexer.hpp"
#include "internal/parser/parser.hpp"
#include "internal/evaluator/evaluator.hpp"
#include "internal/shared/shared.hpp"

namespace calculator
{
	double calculator_t::calculate(const std::string& equation)
	{
		lexer_t lexer{};
		std::vector<shared::token_t> tokens = lexer.tokenize(equation);

		for (shared::token_t& token : tokens)
		{
			token.output();
		}

		return 69.6942069;
	}
}
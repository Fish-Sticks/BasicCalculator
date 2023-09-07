#include "calculator.hpp"
#include "internal/lexer/lexer.hpp"
#include "internal/parser/parser.hpp"
#include "internal/evaluator/evaluator.hpp"
#include "internal/shared/shared.hpp"

using namespace calculator::internal;

namespace calculator
{
	double calculator_t::calculate(const std::string& equation)
	{
		try
		{
			lexer_t lexer{};
			std::vector<shared::token_t> tokens = lexer.tokenize(equation);

			parser_t parser{};
			std::shared_ptr<shared::base_expr_t> main_stmt = parser.parse(tokens);

			evaluator_t evaluator{};
			double result = evaluator.eval(main_stmt);

			return result;
		}
		catch (std::exception& except)
		{
			std::printf("Error: %s\n", except.what());
		}

		return 0;
	}
}
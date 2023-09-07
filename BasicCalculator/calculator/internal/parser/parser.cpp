#include "parser.hpp"
#include <stdexcept>

using namespace calculator::internal;
using shared::token_tt;

namespace calculator
{
	namespace internal
	{
		std::optional<shared::token_t> parser_t::eat_token()
		{
			if (current_index < tokens.size())
				return this->tokens[this->current_index++];

			return std::nullopt;
		}

		std::optional<shared::token_t> parser_t::peak_token()
		{
			if (current_index < tokens.size())
				return this->tokens[this->current_index];

			return std::nullopt;
		}

		std::shared_ptr<shared::base_expr_t> parser_t::parse_primary()
		{
			if (auto token = this->eat_token())
			{
				switch (token->value)
				{
					case token_tt::NUMBER:
					{
						std::shared_ptr<shared::number_expr_t> number = std::make_shared<shared::number_expr_t>(token->number);
						return std::move(number);
						break;
					}
					default:
						token->output();
						throw std::runtime_error("Received invalid token!");
						break;
				}
			}
			else
				throw std::runtime_error("Expected primary token!");
		}

		std::shared_ptr<shared::base_expr_t> parser_t::parse_paren()
		{
			std::shared_ptr<shared::base_expr_t> rtn_expr;

			if (auto next_token = this->peak_token())
			{
				if (next_token->value == token_tt::OPEN_PAREN)
				{
					this->eat_token();
					rtn_expr = this->parse();
					next_token = this->peak_token();
					if (next_token && next_token->value == token_tt::CLOSE_PAREN)
						this->eat_token();
					else
					{
						throw std::runtime_error("Closing parenthesis expected!");
					}
				}
			}

			if (rtn_expr.get() == nullptr)
				rtn_expr = parse_primary();

			return rtn_expr;
		}

		std::shared_ptr<shared::base_expr_t> parser_t::parse_unary()
		{
			std::shared_ptr<shared::base_expr_t> rtn_expr;

			if (auto next_token = this->peak_token())
			{
				if (next_token->value == token_tt::SUB)
				{
					this->eat_token();
					std::shared_ptr<shared::base_expr_t> left_expr = parse_paren();
					rtn_expr = std::make_unique<shared::unary_expr_t>(std::move(left_expr));
				}
			}

			if (rtn_expr.get() == nullptr)
				rtn_expr = parse_paren();

			return rtn_expr;
		}

		std::shared_ptr<shared::base_expr_t> parser_t::parse_powmod()
		{
			std::shared_ptr<shared::base_expr_t> rtn_expr;
			std::shared_ptr<shared::base_expr_t> left_expr = parse_unary();

			if (auto next_token = this->peak_token())
			{
				while (next_token)
				{
					if (next_token->value == token_tt::MOD || next_token->value == token_tt::POW)
					{
						shared::token_t current = *this->eat_token();
						left_expr = std::make_unique<shared::binary_expr_t>(std::move(left_expr), this->parse_powmod(), current.value);
						rtn_expr = left_expr;
					}
					else
						break;

					next_token = this->peak_token();
				}
			}

			if (rtn_expr.get() == nullptr)
				rtn_expr = left_expr;

			return rtn_expr;
		}

		std::shared_ptr<shared::base_expr_t> parser_t::parse_muldiv()
		{
			std::shared_ptr<shared::base_expr_t> rtn_expr;
			std::shared_ptr<shared::base_expr_t> left_expr = parse_powmod();

			if (auto next_token = this->peak_token())
			{
				while (next_token)
				{
					if (next_token->value == token_tt::MUL || next_token->value == token_tt::DIV)
					{
						shared::token_t current = *this->eat_token();
						left_expr = std::make_unique<shared::binary_expr_t>(std::move(left_expr), this->parse_muldiv(), current.value);
						rtn_expr = left_expr;
					}
					else
						break;

					next_token = this->peak_token();
				}
			}

			if (rtn_expr.get() == nullptr)
				rtn_expr = left_expr;

			return rtn_expr;
		}

		std::shared_ptr<shared::base_expr_t> parser_t::parse_addsub()
		{
			std::shared_ptr<shared::base_expr_t> rtn_expr;
			std::shared_ptr<shared::base_expr_t> left_expr = parse_muldiv();

			if (auto next_token = this->peak_token())
			{
				while (next_token)
				{
					if (next_token->value == token_tt::ADD || next_token->value == token_tt::SUB)
					{
						shared::token_t current = *this->eat_token();
						left_expr = std::make_unique<shared::binary_expr_t>(std::move(left_expr), this->parse_addsub(), current.value);
						rtn_expr = left_expr;
					}
					else
						break;

					next_token = this->peak_token();
				}
			}

			if (rtn_expr.get() == nullptr)
				rtn_expr = left_expr;

			return rtn_expr;
		}

		std::shared_ptr<shared::base_expr_t> parser_t::parse()
		{
			return this->parse_addsub();
		}

		std::shared_ptr<shared::base_expr_t> parser_t::parse(const std::vector<shared::token_t>& tokens)
		{
			this->tokens = tokens;
			this->current_index = 0;

			return this->parse();
		}
	}
}
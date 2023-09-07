#pragma once
#include <string>
#include <cstdint>
#include <memory>

namespace calculator
{
	namespace internal
	{
		namespace shared
		{
			// Lexer structs

			enum struct token_tt : std::uint8_t
			{
				NONE, NUMBER, ADD, SUB, MUL, DIV, MOD, POW, OPEN_PAREN, CLOSE_PAREN
			};

			struct token_t
			{
			public:
				token_t(token_tt value) : value{ value } {}
				token_t(double num) : value{ token_tt::NUMBER }, number{ num } {}

				token_tt value = token_tt::NONE;
				union
				{
					double number = 0;
				};
			};

			// Parser structs

			enum struct expr_tt : std::uint8_t
			{
				BASE, NUMBER, BINARY, UNARY
			};

			struct base_expr_t
			{
			private:
				expr_tt expr_type = expr_tt::BASE;
			public:
				base_expr_t(expr_tt expr_type) : expr_type{ expr_type } {}

				expr_tt get_type()
				{
					return this->expr_type;
				}

				virtual std::string beautify()
				{
					return "NONE";
				}
			};

			struct unary_expr_t : base_expr_t
			{
			public:
				unary_expr_t(std::shared_ptr<base_expr_t> child) : base_expr_t{ expr_tt::UNARY }, child{ child } {}

				std::shared_ptr<base_expr_t> child;


				std::string beautify() override
				{
					return "(-" + this->child->beautify() + ")";
				}
			};

			struct number_expr_t : base_expr_t
			{
			public:
				number_expr_t(double number) : base_expr_t{ expr_tt::NUMBER }, value{ number } {}

				double value = 0;

				std::string beautify() override
				{
					return std::to_string(value);
				}
			};

			struct binary_expr_t : base_expr_t
			{
			public:
				binary_expr_t(std::shared_ptr<base_expr_t> left, std::shared_ptr<base_expr_t> right, token_tt operation) 
					: base_expr_t{ expr_tt::BINARY }, left{ std::move(left) }, right{ std::move(right) }, operation{ operation } {}

				token_tt operation = token_tt::NONE;
				std::shared_ptr<base_expr_t> left{};
				std::shared_ptr<base_expr_t> right{};

				std::string beautify() override
				{
					char op = '&';
					switch (operation)
					{
					case token_tt::ADD:
						op = '+';
						break;
					case token_tt::SUB:
						op = '-';
						break;
					case token_tt::MUL:
						op = '*';
						break;
					case token_tt::DIV:
						op = '/';
						break;
					case token_tt::MOD:
						op = '%';
						break;
					case token_tt::POW:
						op = '^';
						break;
					}

					return "(" + this->left->beautify() + " " + op + " " + this->right->beautify() + ")";
				}
			};
		}
	}
}
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

				void output() const
				{
					switch (this->value)
					{
					case token_tt::NONE:
						std::printf("NONE\n");
						break;
					case token_tt::NUMBER:
						std::printf("NUMBER: %.8f\n", number);
						break;
					case token_tt::ADD:
						std::printf("ADD\n");
						break;
					case token_tt::SUB:
						std::printf("SUBTRACT\n");
						break;
					case token_tt::MUL:
						std::printf("MULTIPLY\n");
						break;
					case token_tt::DIV:
						std::printf("DIVIDE\n");
						break;
					case token_tt::MOD:
						std::printf("MODULO\n");
						break;
					case token_tt::POW:
						std::printf("POWER\n");
						break;
					default:
						std::printf("INVALID\n");
						break;
					}
				}
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
			};

			struct unary_expr_t : base_expr_t
			{
			public:
				unary_expr_t(std::shared_ptr<base_expr_t> child) : base_expr_t{ expr_tt::UNARY }, child{ child } {}

				std::shared_ptr<base_expr_t> child;
			};

			struct number_expr_t : base_expr_t
			{
			public:
				number_expr_t(double number) : base_expr_t{ expr_tt::NUMBER }, value{ number } {}

				double value = 0;
			};

			struct binary_expr_t : base_expr_t
			{
			public:
				binary_expr_t(std::shared_ptr<base_expr_t> left, std::shared_ptr<base_expr_t> right, token_tt operation) 
					: base_expr_t{ expr_tt::BINARY }, left{ std::move(left) }, right{ std::move(right) }, operation{ operation } {}

				token_tt operation = token_tt::NONE;
				std::shared_ptr<base_expr_t> left{};
				std::shared_ptr<base_expr_t> right{};
			};
		}
	}
}
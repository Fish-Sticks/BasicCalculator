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
			enum struct token_tt : std::uint8_t
			{
				NONE, NUMBER, ADD, SUB, MUL, DIV, MOD, POW
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

				void output()
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

			struct base_expr_t
			{
			private:
				base_expr_t() = default;
			};

			struct number_expr_t : base_expr_t
			{
			public:
				double value = 0;
			};

			struct binary_expr_t : base_expr_t
			{
			public:
				token_tt operation;
				std::shared_ptr<base_expr_t> left{};
				std::shared_ptr<base_expr_t> right{};
			};

			struct program_expr_t : base_expr_t
			{
			public:

			};
		}
	}
}
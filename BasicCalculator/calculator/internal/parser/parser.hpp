#pragma once
#include <vector>
#include <optional>
#include "../shared/shared.hpp"

namespace calculator
{
	namespace internal
	{
		class parser_t
		{
		private:
			std::size_t current_index = 0;
			std::vector<shared::token_t> tokens{};

			std::optional<shared::token_t> eat_token();
			std::optional<shared::token_t> peak_token();

			std::shared_ptr<shared::base_expr_t> parse_primary();
			std::shared_ptr<shared::base_expr_t> parse_paren();
			std::shared_ptr<shared::base_expr_t> parse_unary();
			std::shared_ptr<shared::base_expr_t> parse_powmod();
			std::shared_ptr<shared::base_expr_t> parse_muldiv();
			std::shared_ptr<shared::base_expr_t> parse_addsub();
			std::shared_ptr<shared::base_expr_t> parse();
		public:
			parser_t() = default;
			parser_t(const parser_t&) = delete;

			std::shared_ptr<shared::base_expr_t> parse(const std::vector<shared::token_t>& tokens);
		};
	}
}
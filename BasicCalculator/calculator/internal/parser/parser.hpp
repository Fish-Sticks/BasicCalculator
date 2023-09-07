#pragma once
#include <vector>
#include "../shared/shared.hpp"

namespace calculator
{
	namespace internal
	{
		class parser_t
		{
		public:
			parser_t() = default;
			parser_t(const parser_t&) = delete;

			shared::base_expr_t parse(const std::vector<shared::token_t>& tokens);
		};
	}
}
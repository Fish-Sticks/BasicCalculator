#pragma once
#include <string>
#include <vector>
#include "../shared/shared.hpp"

using namespace calculator::internal;

namespace calculator
{
	namespace internal
	{
		class lexer_t
		{
		public:
			lexer_t() = default;
			lexer_t(const lexer_t&) = delete;

			std::vector<shared::token_t> tokenize(const std::string& value);
		};
	}
}
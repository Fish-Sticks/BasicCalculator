#pragma once
#include "../shared/shared.hpp"

namespace calculator
{
	namespace internal
	{
		class evaluator_t
		{
		public:
			evaluator_t() = default;
			evaluator_t(const evaluator_t&) = delete;

			double eval(std::shared_ptr<shared::base_expr_t> expression);
		};
	}
}
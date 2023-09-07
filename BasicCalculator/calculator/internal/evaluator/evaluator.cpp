#include "evaluator.hpp"
#include <stdexcept>

using namespace calculator::internal;
using shared::token_tt, shared::expr_tt;

namespace calculator
{
	namespace internal
	{
		double evaluator_t::eval(std::shared_ptr<shared::base_expr_t> current)
		{
			switch (current->get_type())
			{
				case expr_tt::BINARY:
				{
					std::shared_ptr<shared::binary_expr_t> binary_expr = std::reinterpret_pointer_cast<shared::binary_expr_t>(current);
					switch (binary_expr->operation)
					{
						case token_tt::ADD:
							return this->eval(binary_expr->left) + this->eval(binary_expr->right);
							break;
						case token_tt::SUB:
							return this->eval(binary_expr->left) - this->eval(binary_expr->right);
							break;
						case token_tt::MUL:
							return this->eval(binary_expr->left) * this->eval(binary_expr->right);
							break;
						case token_tt::DIV:
							return this->eval(binary_expr->left) / this->eval(binary_expr->right);
							break;
						case token_tt::MOD:
							return fmod(this->eval(binary_expr->left), this->eval(binary_expr->right));
							break;
						case token_tt::POW:
							return pow(this->eval(binary_expr->left), this->eval(binary_expr->right));
						default:
							throw std::runtime_error("Unknown operation used!");
							break;
					}
				
					break;
				}
				case expr_tt::NUMBER:
				{
					std::shared_ptr<shared::number_expr_t> number_expr = std::reinterpret_pointer_cast<shared::number_expr_t>(current);
					return number_expr->value;
					break;
				}
				case expr_tt::UNARY:
				{
					std::shared_ptr<shared::unary_expr_t> unary_expr = std::reinterpret_pointer_cast<shared::unary_expr_t>(current);
					return -this->eval(unary_expr->child);
				}
				default:
					throw std::runtime_error("Unexpected node to evaluate!");
					break;
			}
		}
	}
}
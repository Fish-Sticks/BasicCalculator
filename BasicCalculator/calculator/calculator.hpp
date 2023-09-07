#pragma once
#include <cstdint>
#include <string>

namespace calculator
{
	class calculator_t
	{
	public:
		calculator_t() = default;
		calculator_t(const calculator_t&) = delete;

		double calculate(const std::string& equation);
	};
}
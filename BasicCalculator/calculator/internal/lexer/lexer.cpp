#include "lexer.hpp"
#include <optional>
#include <stdexcept>

std::vector<shared::token_t> lexer_t::tokenize(const std::string& value)
{
	std::vector<shared::token_t> tokens{};
	std::size_t current_index = 0;

	if (!value.size())
		throw std::runtime_error("Invalid calculator input");

	auto eat_character = [tokens, value, &current_index]() -> std::optional<char>
	{
		if (current_index < value.size())
			return value[current_index++];

		return std::nullopt;
	};

	auto peak_character = [value, &current_index]() -> std::optional<char>
	{
		if (current_index < value.size())
			return value[current_index];

		return std::nullopt;
	};

	while (std::optional<char> current = eat_character())
	{
		if (std::isdigit(*current))
		{
			std::string string_number = "";
			while (true)
			{
				string_number.push_back(*current);
				if (std::optional<char> next = peak_character())
				{
					if (!(std::isdigit(*next) || *next == '.'))
						break;
					else
						current = eat_character();
				}
				else
					break;
			}

			tokens.emplace_back(std::stod(string_number));
			continue;
		}

		shared::token_tt operation = shared::token_tt::NONE;
		switch (*current)
		{
		case '+':
			operation = shared::token_tt::ADD;
			break;
		case '-':
			operation = shared::token_tt::SUB;
			break;
		case '/':
			operation = shared::token_tt::DIV;
			break;
		case '*':
			operation = shared::token_tt::MUL;
			break;
		case '%':
			operation = shared::token_tt::MOD;
			break;
		case '^':
			operation = shared::token_tt::POW;
			break;
		}

		if (operation != shared::token_tt::NONE)
		{
			tokens.emplace_back(operation);
			continue;
		}
	}

	return tokens;
}
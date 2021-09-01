#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

#include <core/highlight.h>

namespace text_painter::core
{

struct CharacterColors
{
	explicit CharacterColors(std::string text)
	{
		std::transform(
			text.begin(),
			text.end(),
			text.begin(),
			[](char c) -> char
			{
				return (c == (char)u'\u00C2') || c < 0 ? ' ': c;
			}
		);
		text.erase(
			std::remove_if(
				text.begin(), text.end(),
				[](char c)
				{
					return std::iscntrl(c);
				}
			),
			text.end()
		);

		this->characters_ = std::vector<char>(text.begin(), text.end());
		this->colors_.reserve(this->characters_.size());

		std::for_each(
			this->characters_.cbegin(),
			this->characters_.cend(),
			[this] (const auto& chara)
			{
			  this->colors_.emplace_back(Color{0,0,0});
			}
		);
	}
	std::vector<char> characters_;
	std::vector<Color> colors_;
};

}
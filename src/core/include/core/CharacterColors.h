#pragma once

#include <algorithm>
#include <string_view>
#include <vector>
#include <core/highlight.h>

namespace text_painter::core
{

struct CharacterColors
{
	explicit CharacterColors(const std::string_view text)
	{
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
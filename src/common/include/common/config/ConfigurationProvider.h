#pragma once

#include <string>

#include <AppCore/App.h>

namespace text_painter::common::config
{

class ConfigurationProvider final
{
public:
	[[nodiscard]] std::string logfilePath();
	[[nodiscard]] ultralight::Settings ultralightConfig();
};

}

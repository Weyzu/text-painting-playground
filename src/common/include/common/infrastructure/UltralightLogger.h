#pragma once

#include <Ultralight/Ultralight.h>

namespace text_painter::common::infrastructure
{

class UltralightLogger : public ultralight::Logger
{
public:
	UltralightLogger() = default;
	~UltralightLogger() override = default;

	void LogMessage(ultralight::LogLevel log_level, const ultralight::String16& message) override;
};

}
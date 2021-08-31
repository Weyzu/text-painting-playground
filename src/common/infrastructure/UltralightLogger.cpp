#include "common/infrastructure/UltralightLogger.h"
using text_painter::common::infrastructure::UltralightLogger;
using ultralight::LogLevel;
using ultralight::String16;
using ultralight::String;

#include <string>
using std::string;

#include <fmt/core.h>
using fmt::format;
#include <spdlog/spdlog.h>
using spdlog::error;
using spdlog::info;
using spdlog::warn;

void UltralightLogger::LogMessage(LogLevel log_level, const String16& message)
{
	const string logMessage{format("[Ultralight] {}", String(message).utf8().data())};
	switch (log_level)
	{
		case LogLevel::kLogLevel_Info:
			info(logMessage);
			break;
		case LogLevel::kLogLevel_Warning:
			warn(logMessage);
			break;
		case LogLevel::kLogLevel_Error:
			error(logMessage);
			break;
	}
}

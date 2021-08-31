#include "core/Application.h"
using text_painter::core::Application;

#include <chrono>
using namespace std::literals::chrono_literals;
#include <string>
using std::string;

#include <Ultralight/Ultralight.h>
using ultralight::Platform;
#include <spdlog/async.h>
using spdlog::async_factory;
#include <spdlog/spdlog.h>
using spdlog::info;
using spdlog::set_default_logger;
using spdlog::set_pattern;
#include <spdlog/sinks/basic_file_sink.h>
using spdlog::basic_logger_mt;

#include "common/config/ConfigurationProvider.h"
using text_painter::common::config::ConfigurationProvider;
#include "common/infrastructure/UltralightLogger.h"
using text_painter::common::infrastructure::UltralightLogger;

void setupLogging(const string& logFilePath)
{
	auto logger = basic_logger_mt<async_factory>(
		"main",
		logFilePath
	);
	logger->set_pattern("[%H:%M:%S %z] [%^%l%$] [thread %t] %v");
	set_default_logger(logger);
	spdlog::flush_every(1s);

	Platform::instance().set_logger(new UltralightLogger());
}

int main()
{
	ConfigurationProvider configProvider{};

	setupLogging(configProvider.logfilePath());
	info("Starting application.");

	Application app{configProvider};
	app.Run();

	return 0;
}

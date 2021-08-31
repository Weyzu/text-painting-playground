#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <thread>

#include "common/utilities/ThreadSafeQueue.h"
#include "core/UiResponseService.h"

namespace text_painter::core
{

class ColoringService
{
public:
	using InputQueue = std::shared_ptr<common::utilities::ThreadSafeQueue<std::string>>;

	ColoringService(const std::shared_ptr<UiResponseService>& uiResponseService);
	ColoringService(const ColoringService&) = delete;
	ColoringService& operator=(const ColoringService&) = delete;
	ColoringService(ColoringService&& move_this) = delete;
	~ColoringService() = default;

	void start();
	void join();
	void scheduleColoring(std::string text);

private:
	void processQueue();

	std::atomic_bool shouldProcess_;
	std::unique_ptr<std::thread> thread_;
	InputQueue queue_;
	std::shared_ptr<UiResponseService> uiResponseService_;
};

}
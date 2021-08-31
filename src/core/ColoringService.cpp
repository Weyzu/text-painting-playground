#include "core/ColoringService.h"
using std::make_shared;
using std::make_unique;
using std::move;
using std::shared_ptr;
using std::string;
using std::thread;
using text_painter::core::ColoringService;
using text_painter::core::UiResponseService;

#include <vector>
using std::vector;

#include <core/highlight.h>
#include <spdlog/spdlog.h>
using spdlog::info;

#include "common/utilities/ThreadSafeQueue.h"
using text_painter::common::utilities::ThreadSafeQueue;
#include "core/CharacterColors.h"
using text_painter::core::CharacterColors;
#include "core/UiOutgoingMessage.h"
using text_painter::core::UiNewStateOutgoingMessage;

ColoringService::ColoringService(const shared_ptr<UiResponseService>& uiResponseService) :
	shouldProcess_{true},
	queue_{make_shared<ThreadSafeQueue<string>>()},
	uiResponseService_(uiResponseService)
{}

void ColoringService::start()
{
	this->shouldProcess_.store(true);
	this->thread_ = make_unique<thread>(&ColoringService::processQueue, this);
}

void ColoringService::join()
{
	this->shouldProcess_.store(false);
	this->thread_->join();
}

void ColoringService::scheduleColoring(string text)
{
	this->queue_->push(move(text));
}

void ColoringService::processQueue()
{
	while (this->shouldProcess_.load())
	{
		const auto text{this->queue_->wait_and_pop()};

		CharacterColors colorizedTextData(*text);
		highlight(
			colorizedTextData.characters_,
			[this] () { return ! this->shouldProcess_.load(); },
			colorizedTextData.colors_.begin()
		);

		this->uiResponseService_->enqueue(
			make_unique<UiNewStateOutgoingMessage>(colorizedTextData)
		);
	}
}

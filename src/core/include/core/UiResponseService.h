#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <thread>

#include "common/utilities/ThreadSafeQueue.h"
#include "core/UiOutgoingMessage.h"
#include "core/UiMessageProcessor.h"
#include "core/VueStoreProxy.h"

namespace text_painter::core
{

class UiResponseService : public UiMessageProcessor
{
public:
	using InputQueue = std::shared_ptr<
	    common::utilities::ThreadSafeQueue<std::unique_ptr<UiOutgoingMessage>>
	>;

	UiResponseService();
	UiResponseService(const UiResponseService&) = delete;
	UiResponseService& operator=(const UiResponseService&) = delete;
	UiResponseService(UiResponseService&& move_this) = delete;
	~UiResponseService() = default;

	void processQueue();
	void enqueue(std::unique_ptr<UiOutgoingMessage> outgoingMessage);
private:
	void handleMessage(const std::unique_ptr<UiOutgoingMessage>& outgoingMessage);

	void process(UiNewStateOutgoingMessage* outgoingMessage) override;

	std::atomic_bool shouldProcess_;
	VueStoreProxy uiState_;
	InputQueue queue_;
};

}

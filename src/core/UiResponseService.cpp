#include "core/UiResponseService.h"
using std::make_shared;
using std::string;
using std::unique_ptr;
using text_painter::common::utilities::ThreadSafeQueue;
using text_painter::core::UiOutgoingMessage;
using text_painter::core::UiResponseService;


UiResponseService::UiResponseService() :
	queue_{make_shared<ThreadSafeQueue<unique_ptr<UiOutgoingMessage>>>()}
{
}

void UiResponseService::processQueue()
{
	if(!this->queue_->empty())
	{
		const auto outgoingMessage{this->queue_->try_pop()};

		if(outgoingMessage != nullptr)
		{
			this->handleMessage(*outgoingMessage);
		}
	}
}
void UiResponseService::enqueue(unique_ptr<UiOutgoingMessage> outgoingMessage)
{
	this->queue_->push(move(outgoingMessage));
}

void UiResponseService::handleMessage(const unique_ptr<UiOutgoingMessage>& outgoingMessage)
{
	outgoingMessage->accept(this);
}

void UiResponseService::process(UiNewStateOutgoingMessage* outgoingMessage)
{
	this->uiState_.setText(outgoingMessage->getState());
}

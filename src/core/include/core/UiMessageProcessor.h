#pragma once

namespace text_painter::core
{

class UiNewStateOutgoingMessage;

class UiMessageProcessor
{
public:
	virtual void process(UiNewStateOutgoingMessage* message) = 0;

};

}
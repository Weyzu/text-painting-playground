#include "core/UiOutgoingMessage.h"
using text_painter::core::CharacterColors;
using text_painter::core::UiMessageProcessor;
using text_painter::core::UiNewStateOutgoingMessage;
using text_painter::core::UiOutgoingMessage;

#include <utility>
using std::move;

UiNewStateOutgoingMessage::UiNewStateOutgoingMessage(CharacterColors characterColors) :
	newState_(move(characterColors))
{}

CharacterColors text_painter::core::UiNewStateOutgoingMessage::getState() const
{
	return this->newState_;
}

void UiNewStateOutgoingMessage::accept(UiMessageProcessor *processor)
{
	processor->process(this);
}

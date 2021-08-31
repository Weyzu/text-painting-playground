#pragma once

#include "core/CharacterColors.h"
#include "core/UiMessageProcessor.h"

namespace text_painter::core
{

class UiOutgoingMessage
{
public:
	virtual void accept(UiMessageProcessor* processor) = 0;
};

class UiNewStateOutgoingMessage : public UiOutgoingMessage
{
public:
	explicit UiNewStateOutgoingMessage(CharacterColors newState);

	void accept(UiMessageProcessor* processor) override;

	[[nodiscard]] CharacterColors getState() const;
private:
	CharacterColors newState_;
};

}

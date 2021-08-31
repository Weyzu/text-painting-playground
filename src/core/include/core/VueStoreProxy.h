#pragma once

#include <optional>
#include <string>
#include <vector>

#include <AppCore/AppCore.h>

#include "core/CharacterColors.h"

namespace text_painter::core
{

class VueStoreProxy
{
public:
	VueStoreProxy() = default;
	~VueStoreProxy() = default;

	void setText(const CharacterColors& colorizedTextData);

private:
	void SendToVueStore(
		const std::string& commandName,
		const std::optional<ultralight::JSObject>& data
	) const;
	ultralight::JSObject GetVueStore() const;
};

}

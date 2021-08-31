#include "core/VueStoreProxy.h"
using std::nullopt;
using std::optional;
using std::string;
using text_painter::core::CharacterColors;
using text_painter::core::VueStoreProxy;
using ultralight::JSGlobalObject;
using ultralight::JSObject;

#include <memory>
using std::make_unique;
using std::unique_ptr;

#include <JavaScriptCore/JSRetainPtr.h>
#include <spdlog/spdlog.h>
using spdlog::error;

#include "common/utilities/JsonParsing.h"
using text_painter::common::utilities::fromJsStringRef;

void VueStoreProxy::SendToVueStore(const string& commandName, const optional<JSObject>& data) const
{
	auto globalContext{JSGlobalObject().context()};
	JSObjectRef vueStore{this->GetVueStore()};
	JSRetainPtr<JSStringRef> vueStoreCommitName{adopt(JSStringCreateWithUTF8CString("commit"))};
	auto commitProperty{
		JSObjectGetProperty(
			globalContext,
			vueStore,
			vueStoreCommitName.get(),
			nullptr
		)
	};
	auto vueStoreCommit{
		JSValueToObject(
			globalContext,
			commitProperty,
			nullptr
		)
	};

	if (vueStoreCommit && JSObjectIsFunction(globalContext, vueStoreCommit))
	{
		JSStringRef commandNameRef{JSStringCreateWithUTF8CString(commandName.c_str())};
		const size_t num_args{data ? 2ul : 1ul};
		unique_ptr<JSValueRef[]> args{make_unique<JSValueRef[]>(num_args)};
		args[0] = JSValueMakeString(globalContext, commandNameRef);

		if (data)
		{
			args[1] = data.value();
		}

		JSValueRef exception{nullptr};

		JSObjectCallAsFunction(
			globalContext,
			vueStoreCommit,
			nullptr,
			num_args,
			args.get(),
			&exception
		);
		JSStringRelease(commandNameRef);

		if (exception)
		{
			error(fromJsStringRef(JSValueToStringCopy(globalContext, exception, nullptr)));
		}
	}
}

JSObject VueStoreProxy::GetVueStore() const
{
	auto globalContext{JSGlobalObject().context()};
	JSRetainPtr<JSStringRef> str{adopt(JSStringCreateWithUTF8CString("VueStore"))};
	JSValueRef rawVueStoreGetter{
		JSEvaluateScript(
			globalContext,
			str.get(),
			nullptr,
			nullptr,
			0,
			nullptr
		)
	};
	auto vueStoreGetter{JSValueToObject(globalContext, rawVueStoreGetter, nullptr)};
	auto vueStoreRef = JSObjectCallAsFunction(
		globalContext,
		vueStoreGetter,
		nullptr,
		0,
		{},
		nullptr
	);

	return JSObject(JSValueToObject(globalContext, vueStoreRef, nullptr));
}
void VueStoreProxy::setText(const CharacterColors& colorizedTextData)
{
	auto globalContext{JSGlobalObject().context()};
	auto colors{JSObjectMakeArray(globalContext, 0, nullptr, nullptr)};
	JSObject rootObject;

	for (int i{0}; i < colorizedTextData.characters_.size(); i++)
	{
		JSObject colorObject;
		JSObjectSetProperty(
			globalContext,
			colorObject,
			JSStringCreateWithUTF8CString("r"),
			JSValueMakeNumber(globalContext, colorizedTextData.colors_[i].r),
			kJSPropertyAttributeNone,
			nullptr
		);
		JSObjectSetProperty(
			globalContext,
			colorObject,
			JSStringCreateWithUTF8CString("g"),
			JSValueMakeNumber(globalContext, colorizedTextData.colors_[i].g),
			kJSPropertyAttributeNone,
			nullptr
		);
		JSObjectSetProperty(
			globalContext,
			colorObject,
			JSStringCreateWithUTF8CString("b"),
			JSValueMakeNumber(globalContext, colorizedTextData.colors_[i].b),
			kJSPropertyAttributeNone,
			nullptr
		);
		JSObjectSetPropertyAtIndex(
			globalContext,
			colors,
			i,
			colorObject,
			nullptr
		);
	}

	const string text(colorizedTextData.characters_.begin(), colorizedTextData.characters_.end());

	JSObjectSetProperty(
		globalContext,
		rootObject,
		JSStringCreateWithUTF8CString("text"),
		JSValueMakeString(
			globalContext,
			JSStringCreateWithUTF8CString(text.c_str())
		),
		kJSPropertyAttributeNone,
		nullptr
	);
	JSObjectSetProperty(
		globalContext,
		rootObject,
		JSStringCreateWithUTF8CString("textColors"),
		colors,
		kJSPropertyAttributeNone,
		nullptr
	);

	this->SendToVueStore("set_text", rootObject);
}

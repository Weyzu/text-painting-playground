#pragma once

#include <AppCore/AppCore.h>

#include "common/config/ConfigurationProvider.h"
#include "core/ColoringService.h"
#include "core/UiResponseService.h"

namespace text_painter::core
{

class Application final :
	public ultralight::AppListener,
	public ultralight::WindowListener,
	public ultralight::LoadListener,
	public ultralight::ViewListener
{
public:
	explicit Application(text_painter::common::config::ConfigurationProvider configProvider);
	~Application() override;

	virtual void Run();
	void OnUpdate() override;
	void OnClose() override;
	void OnResize(uint32_t width, uint32_t height) override;
	void OnFinishLoading(
		ultralight::View* caller,
		uint64_t frame_id,
		bool is_main_frame,
		const ultralight::String& url
	) override;
	void OnDOMReady(
		ultralight::View* caller,
		uint64_t frame_id,
		bool is_main_frame,
		const ultralight::String& url
	) override;
	void OnChangeCursor(ultralight::View* caller, ultralight::Cursor cursor) override;
	void OnChangeTitle(ultralight::View* caller, const ultralight::String& title) override;
	void OnAddConsoleMessage(
		ultralight::View* caller,
		ultralight::MessageSource source,
		ultralight::MessageLevel level,
		const ultralight::String& message,
		uint32_t line_number,
		uint32_t column_number,
		const ultralight::String& source_id
	) override;

protected:
	ultralight::RefPtr<ultralight::App> app_;
	ultralight::RefPtr<ultralight::Window> window_;
	ultralight::RefPtr<ultralight::Overlay> overlay_;

private:
	ultralight::JSValue OnInputEvent(
		const ultralight::JSObject& thisObject,
		const ultralight::JSArgs& args
	);

	common::config::ConfigurationProvider configProvider_;
	UiResponseService uiResponseService_;
	ColoringService coloringService_;
};

}

#include "core/Application.h"
using namespace ultralight;
using text_painter::common::config::ConfigurationProvider;
using text_painter::core::Application;
using text_painter::core::UiResponseService;

#include <memory>
using std::shared_ptr;
#include <string>
using std::string;

#include <spdlog/spdlog.h>
using spdlog::debug;
using spdlog::error;
using spdlog::info;
using spdlog::warn;

#include "common/utilities/JsonParsing.h"
using text_painter::common::utilities::fromJsStringRef;

namespace
{
	constexpr int windowWidth{1200};
	constexpr int windowHeight{800};

	inline string toUTF8(const String& str)
	{
		String8 utf8 = str.utf8();
		return {utf8.data(), utf8.length()};
	}

	inline const char* stringify(MessageSource source)
	{
		switch(source) {
			case kMessageSource_XML: return "XML";
			case kMessageSource_JS: return "JS";
			case kMessageSource_Network: return "Network";
			case kMessageSource_ConsoleAPI: return "ConsoleAPI";
			case kMessageSource_Storage: return "Storage";
			case kMessageSource_AppCache: return "AppCache";
			case kMessageSource_Rendering: return "Rendering";
			case kMessageSource_CSS: return "CSS";
			case kMessageSource_Security: return "Security";
			case kMessageSource_ContentBlocker: return "ContentBlocker";
			case kMessageSource_Other: return "Other";
			default: return "unknown";
		}
	}

}

Application::Application(ConfigurationProvider configProvider) :
	configProvider_{configProvider},
	uiResponseService_{},
	coloringService_{shared_ptr<UiResponseService>(&uiResponseService_)}
{
	this->app_ = App::Create(configProvider.ultralightConfig());
	this->window_ = Window::Create(
		app_->main_monitor(),
		windowWidth,
		windowHeight,
		false,
		kWindowFlags_Titled | kWindowFlags_Resizable
	);
	this->app_->set_window(*window_);
	this->overlay_ = Overlay::Create(*window_, 1, 1, 0, 0);
	this->overlay_->Resize(this->window_->width(), window_->height());
	this->overlay_->view()->LoadURL("file:///index.html");
	this->app_->set_listener(this);
	this->window_->set_listener(this);
	this->overlay_->view()->set_load_listener(this);
	this->overlay_->view()->set_view_listener(this);
}

Application::~Application()
{
	this->coloringService_.join();
}

void Application::Run()
{
	this->coloringService_.start();
	this->app_->Run();
}

void Application::OnUpdate()
{
	this->uiResponseService_.processQueue();
}

void Application::OnClose()
{
}

void Application::OnResize(uint32_t width, uint32_t height)
{
	this->overlay_->Resize(width, height);
}

void Application::OnFinishLoading(
	View* caller,
	uint64_t frame_id,
	bool is_main_frame,
	const String& url
)
{
	info("Finished loading frame {}.", frame_id);
}

void Application::OnDOMReady(
	View* caller,
	uint64_t frame_id,
	bool is_main_frame,
	const String& url
)
{
	Ref<JSContext> context = caller->LockJSContext();
	SetJSContext(context.get());

	JSObject global = JSGlobalObject();

	global["OnInputEvent"] = BindJSCallbackWithRetval(&Application::OnInputEvent);
}

void Application::OnChangeCursor(View* caller, Cursor cursor)
{
	window_->SetCursor(cursor);
}

void Application::OnChangeTitle(View* caller, const String& title)
{
	window_->SetTitle(title.utf8().data());
}

void Application::OnAddConsoleMessage(
	View* caller,
	MessageSource source,
	MessageLevel level,
	const String& message,
	uint32_t line_number,
	uint32_t column_number,
	const String& source_id
)
{
	string messageFormat{"[{}] {}"};

	switch(level)
	{
		case kMessageLevel_Log:
		case kMessageLevel_Info:
			info(messageFormat, stringify(source), toUTF8(message));
			return;
		case kMessageLevel_Warning:
			warn(messageFormat, stringify(source), toUTF8(message));
			return;
		case kMessageLevel_Error:
			error(messageFormat, stringify(source), toUTF8(message));
			return;
		case kMessageLevel_Debug:
			debug(messageFormat, stringify(source), toUTF8(message));
			return;
	};
}

JSValue Application::OnInputEvent(const JSObject& thisObject, const JSArgs& args)
{
	debug("Received text to colour from UI");

	this->coloringService_.scheduleColoring(fromJsStringRef(args.data()[0].ToString()));

	return JSValueMakeNull(nullptr);
}

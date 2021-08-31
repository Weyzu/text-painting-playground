#pragma once

#include <string>

#include <JavaScriptCore/JSStringRef.h>

namespace text_painter::common::utilities
{

std::string fromJsStringRef(JSStringRef str);

}

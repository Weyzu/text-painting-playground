#include "common/utilities/JsonParsing.h"
using std::string;

string text_painter::common::utilities::fromJsStringRef(JSStringRef str)
{
	size_t buffer_size = JSStringGetMaximumUTF8CStringSize(str);

	if(buffer_size < 1)
	{
		return "";
	}

	char *buffer = new char[buffer_size];
	size_t real_size{JSStringGetUTF8CString(str, buffer, buffer_size)};
	string ret(buffer, real_size - 1);

	delete[] buffer;
	return ret;
}

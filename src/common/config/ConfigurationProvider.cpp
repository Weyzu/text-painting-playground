#include "common/config/ConfigurationProvider.h"
using text_painter::common::config::ConfigurationProvider;
using std::string;
using ultralight::Settings;

#include <filesystem>
using std::filesystem::path;

#ifdef _WIN32
#include <shlobj.h>
#elif __APPLE__
#import <Foundation/Foundation.h>
#endif

namespace
{

path systemApplicationDataPath()
{
	auto targetPath{path("")};
#ifdef _WIN32
	char folder_path[MAX_PATH];
	SHGetFolderPathA(
		NULL,
		CSIDL_APPDATA | CSIDL_FLAG_CREATE,
		NULL,
		0,
		folder_path
	);
	targetPath = path(folder_path);
#elif __APPLE__
	NSArray *paths = NSSearchPathForDirectoriesInDomains(
		NSApplicationSupportDirectory,
		NSUserDomainMask,
		YES
	);
	NSString *applicationSupportDirectory = [paths firstObject];
	targetPath = path([applicationSupportDirectory UTF8String]);
#endif
	return targetPath;
}
		
}

string ConfigurationProvider::logfilePath()
{
	auto loggingPath{systemApplicationDataPath()};
	loggingPath /= "TextPainter";
	loggingPath /= "TextPainter.log";
	return loggingPath.string();
}

Settings ConfigurationProvider::ultralightConfig()
{
	return Settings{
		"wzurawik",
		"ultralight",
		"./assets/",
		false,
		false
	};
}

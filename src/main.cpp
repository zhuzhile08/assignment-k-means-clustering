#include <Common/FileSystem.h>
#include <Common/Logger.h>
#include <Common/JSON.h>

#include <matplot/matplot.h>

int main(int, char** argv) {
	lstd::initLoggingSystem();
	lstd::initFileSystem(argv);

	lstd::Json data = lstd::Json::parse(lstd::StringStream("data/data.json").data());

	lstd::log::debug(data.stringifyPretty());
}
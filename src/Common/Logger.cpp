#include <Common/Logger.h>
#include <Common/UniquePointer.h>

#include <ios>
#include <mutex>
#include <Common/UnorderedSparseMap.h>

#ifdef _WIN32
#include <windows.h>
#endif

namespace lstd {

namespace {

class LoggingContext {
public:
	LoggingContext() {
		std::ios::sync_with_stdio(true);

#ifdef _WIN32
		DWORD outMode = 0;
		HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		GetConsoleMode(stdoutHandle, &outMode);
		outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

		SetConsoleMode(stdoutHandle, outMode);
#endif

		defaultLogger = UniquePointer<Logger>::create();
	}

	std::mutex mutex;

	UniquePointer<Logger> defaultLogger;
	UnorderedSparseMap<std::string, UniquePointer<Logger>> loggers;
};

}

static LoggingContext* globalLoggingContext = nullptr;

namespace log {

Logger* logger(std::string_view name) {
	std::lock_guard<std::mutex> guard(globalLoggingContext->mutex);
	return globalLoggingContext->loggers.find(name.data())->second.get();
}

UniquePointer<Logger> releaseLogger(std::string_view name) {
	return globalLoggingContext->loggers.extract(name.data()).second;
}

Logger* defaultLogger() {
	std::lock_guard<std::mutex> guard(globalLoggingContext->mutex);
	return globalLoggingContext->defaultLogger.get();
}

Logger* addLogger(UniquePointer<Logger>&& logger) {
	return globalLoggingContext->loggers.emplace(logger->name(), logger.release()).first->second.get();
}

UniquePointer<Logger> setDefaultLogger(UniquePointer<Logger>&& logger) {
	auto p = std::move(globalLoggingContext->defaultLogger);
	globalLoggingContext->defaultLogger = UniquePointer<Logger>(logger.release());
	return p;
}

} // namespace log

void initLoggingSystem() {
	if (globalLoggingContext)
		log::error("initLoggingSystem(): The logging system is already initialized!");
	else
		globalLoggingContext = new LoggingContext();
}

} // namespace lstd


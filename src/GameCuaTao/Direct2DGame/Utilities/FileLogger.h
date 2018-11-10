#pragma once

#define FMT_HEADER_ONLY
#include "Library/fmt/Include/fmt/format.h"
#include <string>
#include <fstream>
#include <filesystem>

using Path = std::filesystem::path;

class FileLogger
{
public:
	static FileLogger &GetInstance();

	std::string GetFilename();
	std::string GetFullPath();

	// TODO: remove
	void Debug(std::string logMessage);
	void Info(std::string logMessage);
	void Warn(std::string logMessage);
	void Error(std::string logMessage);

	template<typename... Args>
	void Debug(Args... args);

	template<typename... Args>
	void Info(Args... args);

	template<typename... Args>
	void Warn(Args... args);

	template<typename... Args>
	void Error(Args... args);

	virtual ~FileLogger();

private:
	FileLogger();

	Path directory = "Logs";
	std::ofstream logFile;

	const std::string DEBUG_TAG = "[DEBUG] ";
	const std::string INFO_TAG = "[INFO] ";
	const std::string WARN_TAG = "[WARN] ";
	const std::string ERROR_TAG = "[ERROR] ";

	int warningCount = 0;
	int errorCount = 0;

	std::string GetLogTime(const char *format = "");

	template<typename... Args>
	void PrintLog(std::string tag, Args... logMessage);
	void PrintLog(std::string logMessage);
};


#pragma region Implementation

template<typename ...Args>
inline void FileLogger::Debug(Args ...args)
{
	PrintLog(DEBUG_TAG, std::forward<Args>(args)...);
}

template<typename ...Args>
inline void FileLogger::Info(Args ...args)
{
	PrintLog(INFO_TAG, std::forward<Args>(args)...);
}

template<typename ...Args>
inline void FileLogger::Warn(Args ...args)
{
	PrintLog(WARN_TAG, std::forward<Args>(args)...);
}

template<typename ...Args>
inline void FileLogger::Error(Args ...args)
{
	PrintLog(ERROR_TAG, std::forward<Args>(args)...);
}

template<typename ...Args>
inline void FileLogger::PrintLog(std::string tag, Args ...logMessage)
{
	logFile
		<< GetLogTime()
		<< tag
		<< fmt::format(std::forward<Args>(logMessage)...)
		<< std::endl;
}

#pragma endregion
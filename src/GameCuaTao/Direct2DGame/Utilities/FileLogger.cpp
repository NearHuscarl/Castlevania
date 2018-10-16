#include <filesystem>
#include "FileLogger.h"
#include "TimeHelper.h"

FileLogger &FileLogger::GetInstance()
{
	static auto instance = FileLogger{};
	return instance;
}

FileLogger::FileLogger()
{
	if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory))
	{
		std::filesystem::create_directory(directory);
	}

	logFile.open(GetFullPath());

	if (logFile.is_open())
	{
		logFile << "Game Log file. Created at " << GetLogTime() << std::endl;
		logFile << std::endl;
	}
}

std::string FileLogger::GetFilename()
{
	return "log-" + GetLogTime("%Y-%m-%d") + ".txt";
}

std::string FileLogger::GetFullPath()
{
	return (directory / GetFilename()).string();
}

void FileLogger::Debug(std::string logMessage)
{
	PrintLog(DEBUG_TAG + logMessage);
}

void FileLogger::Info(std::string logMessage)
{
	PrintLog(INFO_TAG + logMessage);
}

void FileLogger::Warn(std::string logMessage)
{
	PrintLog(WARN_TAG + logMessage);
	warningCount++;
}

void FileLogger::Error(std::string logMessage)
{
	PrintLog(ERROR_TAG + logMessage);
	errorCount++;
}

std::string FileLogger::GetLogTime(const char *format)
{
	if (format == "")
	{
		format = "[%Y-%m-%d %X] "; // [2018-10-20 11:50:23]
	}
	return TimeHelper::GetTimeNow(format);
}

void FileLogger::PrintLog(std::string logMessage)
{
	logFile << GetLogTime() << logMessage << std::endl;
}

FileLogger::~FileLogger()
{
	if (logFile.is_open())
	{
		logFile << std::endl;
		logFile << "Number of warnings: " << warningCount << std::endl;
		logFile << "Number of errors: " << errorCount << std::endl;

		logFile.close();
	}
}
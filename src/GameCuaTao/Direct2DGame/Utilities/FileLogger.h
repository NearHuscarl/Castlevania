#pragma once

#include <string>
#include <fstream>
#include <filesystem>

class FileLogger
{
public:
	static FileLogger *GetInstance();

	std::string GetFilename();
	std::string GetFullPath();

	void Debug(std::string logMessage);
	void Info(std::string logMessage);
	void Warn(std::string logMessage);
	void Error(std::string logMessage);

	virtual ~FileLogger();

private:
	static FileLogger *instance;
	FileLogger();

	std::filesystem::path directory = "Logs";
	std::ofstream logFile;

	std::string DEBUG_TAG = "[DEBUG] ";
	std::string INFO_TAG = "[INFO] ";
	std::string WARN_TAG = "[WARN] ";
	std::string ERROR_TAG = "[ERROR] ";

	int warningCount = 0;
	int errorCount = 0;

	std::string GetLogTime(const char *format = "");
	void PrintLog(std::string logMessage);
};
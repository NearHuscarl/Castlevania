#pragma once

#include <memory>
#include <string>

class ContentManager;

template <typename T>
class AbstractReader
{
public:
	virtual std::shared_ptr<T> Read(std::string filePath, ContentManager &contentManager) = 0;
	virtual ~AbstractReader() {};
};
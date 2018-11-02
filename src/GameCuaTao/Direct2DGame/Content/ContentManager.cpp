#include "ContentManager.h"

ContentManager::ContentManager(std::shared_ptr<ServiceProvider> serviceProvider)
{
	this->serviceProvider = serviceProvider;
	this->contentReader = std::make_unique<ContentReader>(*this);
}

std::string ContentManager::GetRootDirectory()
{
	return rootDirectory;
}

void ContentManager::SetRootDirectory(std::string path)
{
	rootDirectory = Path{ path }.make_preferred().string();
}

ServiceProvider &ContentManager::GetServiceProvider()
{
	return *serviceProvider;
}
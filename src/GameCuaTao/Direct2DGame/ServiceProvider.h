#pragma once

#include <string>
#include <any>
#include <map>
#include <typeinfo>

// https://stackoverflow.com/questions/412165/c-service-providers#412200
class ServiceProvider
{
public:
	template<typename T>
	void Add(T &service);

	template<typename T>
	std::shared_ptr<T> Get();

private:
	std::map<std::string, std::any> services;
};

template<typename T>
inline void ServiceProvider::Add(T &service)
{
	auto typeName = typeid(T).name();
	services[typeName] = std::shared_ptr<T>(&service);
}

template<typename T>
inline std::shared_ptr<T> ServiceProvider::Get()
{
	auto typeName = typeid(T).name();
	auto it = services.find(typeName);

	if (it == services.end())
		return nullptr;

	return std::any_cast<std::shared_ptr<T>>(services[typeName]);
}
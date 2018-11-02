#pragma once

#include <string>
#include <any>
#include <map>
#include <typeindex>
#include <stdexcept>

// https://stackoverflow.com/questions/412165/c-service-providers#412200
class ServiceProvider
{
public:
	template<typename T>
	void Add(T *service);

	template<typename T>
	T *Get();

private:
	std::map<std::type_index, std::any> services;
};

template<typename T>
inline void ServiceProvider::Add(T *service)
{
	auto typeName = std::type_index{ typeid(T) };
	services.emplace(typeName, service);
}

template<typename T>
inline T *ServiceProvider::Get()
{
	auto typeName = std::type_index{ typeid(T) };
	auto it = services.find(typeName);

	if (it == services.end())
		throw std::invalid_argument("service not found");

	return std::any_cast<T*>(services[typeName]);
}
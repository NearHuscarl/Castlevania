#pragma once

#include <string>
#include <any>
#include <map>
#include <typeinfo>
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
	std::map<std::string, std::any> services;
};

template<typename T>
inline void ServiceProvider::Add(T *service)
{
	auto typeName = typeid(T).name();
	services.emplace(typeName, service);
}

// TODO: should we use std::shared_ptr instead of raw pointer?
template<typename T>
inline T *ServiceProvider::Get()
{
	auto typeName = typeid(T).name();
	auto it = services.find(typeName);

	if (it == services.end())
		throw std::invalid_argument("service not found");

	return std::any_cast<T*>(services[typeName]);
}
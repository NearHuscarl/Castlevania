#pragma once

#include <string>
#include <map>
#include <typeinfo>

// https://stackoverflow.com/questions/412165/c-service-providers#412200
class ServiceProvider
{
public:
	template<typename T>
	void Add(T *service);

	template<typename T>
	T *Get();

private:
	// Cannot store reference in map. So we have to use (TODO: smart) pointer
	std::map<std::string, void*> services;
};

template<typename T>
inline void ServiceProvider::Add(T *service)
{
	std::string typeName = typeid(T).name();
	services[typeName] = static_cast<void*>(service);
}

template<typename T>
inline T *ServiceProvider::Get()
{
	std::string typeName = typeid(T).name();
	auto it = services.find(typeName);

	if (it == services.end())
		return nullptr;

	return static_cast<T*>(services[typeName]);
}
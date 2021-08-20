#pragma once
#include <iostream>
namespace nc
{
	template<class T>
	class Singleton
	{
	public:
		Singleton(const Singleton&) = delete;
		Singleton& operator = (const Singleton&) = delete;

		static T& instance()
		{
			static T instance;
			return instance;
		}

	protected:
		Singleton() {}
	};
}

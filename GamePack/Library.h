#pragma once

#include <string>
#include <map>

template <class T>
class Library
{

	public:

		Library();
		~Library();

		bool has(std::string path);
		void add(std::string path, T* object);
		T* get(std::string path);

		void flush();

	private:

		std::map<std::string, T*> m__objects;

};


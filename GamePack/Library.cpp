#include "Library.h"

using namespace std;

Library::Library(): m__objects()
{



}


Library::~Library()
{



}


bool Library::has(string path)
{

	return m__objects.find(path) != m__objects.end();

}


void Library::add(string path, T* object)
{

	m__objects.insert(pair<string, T*>(path, object));

}


T* Library::get(string path)
{

	return m__objects.at(path);

}


void Library::flush()
{

	m__objects.clear();

}


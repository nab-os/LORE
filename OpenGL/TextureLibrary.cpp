#include "stdafx.h"
#include "TextureLibrary.h"

using namespace std;

TextureLibrary* TextureLibrary::m__instance = new TextureLibrary();

TextureLibrary::TextureLibrary(): m__textures()
{



}


TextureLibrary::~TextureLibrary()
{



}


TextureLibrary* TextureLibrary::getInstance()
{

	return TextureLibrary::m__instance;

}


bool TextureLibrary::has(string path)
{

	return m__textures.find(path) != m__textures.end();

}


void TextureLibrary::add(string path, Texture* object)
{

	m__textures.insert(pair<string, Texture*>(path, object));

}


Texture* TextureLibrary::get(string path)
{

	return m__textures.at(path);

}


void TextureLibrary::flush()
{

	m__textures.clear();

}


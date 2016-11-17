#include "Loadable.h"

using namespace std;

Loadable::Loadable(): m__id(), m__camera()
{

	cout << this << " [Loadable] constructor" << endl;

}


Loadable::~Loadable()
{

	delete m__camera;

}


void Loadable::load()
{

	cout << this << " [Loadable] load" << endl;
	m__loaded = true;

}


void Loadable::unload()
{

	m__loaded = false;

}
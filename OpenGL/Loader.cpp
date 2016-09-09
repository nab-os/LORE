#include "stdafx.h"
#include "Loader.h"

using namespace std;

Loader::Loader(std::string path, string name): m__emplacementFichier(path), m__nom(name)
{



}


Loader::~Loader()
{



}


bool Loader::ouvrir()
{
	
	m__fichier = new ifstream(m__emplacementFichier);
	if (!m__fichier->is_open() && !m__fichier->good())
	{
		std::cout << "Erreur d'ouverture du fichier : " << m__emplacementFichier << endl;
		return false;
	}

	return true;

}


void Loader::fermer()
{

	m__fichier->close();

}


long Loader::getPositionCurseur()
{

	return (long) m__fichier->tellg();

}


long Loader::setPositionCurseur(int offset, char whence)
{
	if (whence == DEBUT)
	{
		m__fichier->seekg(offset, ios_base::beg);
	}
	if (whence == CURSEUR)
	{
		m__fichier->seekg(offset, ios_base::cur);
	}

	if (whence == FIN)
	{
		m__fichier->seekg(offset, ios_base::end);
	}
	return getPositionCurseur();
}

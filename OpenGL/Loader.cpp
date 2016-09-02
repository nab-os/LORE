#include "stdafx.h"
#include "Loader.h"

using namespace std;

Loader::Loader(std::string path): m__emplacementFichier(path)
{



}


Loader::~Loader()
{



}


bool Loader::ouvrir()
{
	
	m__fichier = new ifstream(m__emplacementFichier + "/default.obj", ios::in);
	if (m__fichier == nullptr)
	{
		std::cout << "Erreur d'ouverture du fichier : " << m__emplacementFichier;
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

	return m__fichier->tellg();

}


long Loader::setPositionCurseur(int offset, char whence)
{
	if (whence == DEBUT)
	{
		m__fichier->seekg(offset, ios::beg);
	}
	if (whence == CURSEUR)
	{
		m__fichier->seekg(offset, ios::cur);
	}

	if (whence == FIN)
	{
		m__fichier->seekg(offset, ios::end);
	}
	return getPositionCurseur();
}

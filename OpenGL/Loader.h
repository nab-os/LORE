#pragma once

#include <string>
#include <iostream>
#include <fstream>

#define DEBUT 0
#define CURSEUR 1
#define FIN 2

class Loader
{

	public:

		Loader(std::string path = "", std::string name = "");
		virtual ~Loader();

		void* load() {};
		
	protected:

		bool ouvrir();
		void fermer();

		long getPositionCurseur();
		long setPositionCurseur(int offset, char whence);

		std::string m__nom;
		std::string m__emplacementFichier;
		std::ifstream* m__fichier;

};


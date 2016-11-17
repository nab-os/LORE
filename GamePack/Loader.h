#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define DEBUT 0
#define CURSEUR 1
#define FIN 2

class Loader
{

	public:

		Loader(std::string path = "", std::string name = "");
		virtual ~Loader();

		void* load() { return nullptr; };

	protected:

		bool ouvrir();
		void fermer();

		long getPositionCurseur();
		long setPositionCurseur(int offset, char whence);

		glm::vec3 getVec3();
		glm::vec2 getVec2();
		std::string getString();

		std::string m__nom;
		std::string m__emplacementFichier;
		std::ifstream* m__fichier;

};


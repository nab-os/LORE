#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SOIL.h>

namespace LORE
{

    class Texture
    {

        public:

            Texture(std::string name = "");
            virtual ~Texture();

            void load();

            GLuint getID() { return m__id; };

        protected:

            GLuint m__id;

            std::string m__nom;
            std::string m__emplacementFichier;

    };

}

#endif

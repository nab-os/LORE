#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SOIL.h>

using std::string;

namespace LORE {
    class Texture {
        public:
            Texture(string name = "");
            virtual ~Texture();

            void load();

            GLuint getID() { return m__id; };

        protected:
            GLuint m__id;

            string m__name;
            string m__filePath;
    };
}

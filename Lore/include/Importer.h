#ifndef IMPORTER_H
#define IMPORTER_H

#include <string>

#include <gltf2/glTF2.hpp>

#include "Library.h"
#include "Scene.h"

namespace LORE
{

    class Importer
    {

        public:

            Importer(string colladaFile);
            ~Importer();

            void import();
            void importScene(gltf2::Asset asset, unsigned int i);
            void importCamera(gltf2::Asset asset, unsigned int i);
            void importNode(gltf2::Asset asset, unsigned int i);
            void importObject(gltf2::Asset asset, unsigned int i);
            void importMesh(gltf2::Asset asset, unsigned int i);
            void importAccessor(gltf2::Asset asset, unsigned int i);


        private:

            string m__filePath;

    };

}

#endif

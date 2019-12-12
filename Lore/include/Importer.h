#pragma once

#include <string>
#include <vector>

#include <gltf2/glTF2.hpp>

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

namespace LORE {
    class Importer {
        public:
            Importer(std::string file);
            ~Importer();

            Scene* import();

        private:
            void importScene(gltf2::Asset asset, unsigned int i);
            void importCamera(gltf2::Asset asset, unsigned int i);
            void importNode(gltf2::Asset asset, unsigned int i);
            void importObject(gltf2::Asset asset, unsigned int i);
            void importMesh(gltf2::Asset asset, unsigned int i);
            void importMaterial(gltf2::Asset asset, unsigned int i);
            void importShader(gltf2::Asset asset, unsigned int i);
            void importTexture(gltf2::Asset asset, unsigned int i);

            void buildTree(gltf2::Asset asset, unsigned int i);
            void buildNodeTree(gltf2::Asset asset, Scene* scene, unsigned int i);

            std::vector<float> importData(gltf2::Asset asset, gltf2::Accessor accessor);

            std::string m__filePath;

            std::vector<Scene*> m__scenes;
            std::vector<Camera*> m__cameras;
            std::vector<Mesh*> m__meshes;
            std::vector<Node*> m__nodes;
            std::vector<Material*> m__materials;
            std::vector<Texture*> m__textures;
    };
}

#include "Loader.h"

#include <iostream>

using namespace std;

Loader::Loader()
{



}

Loader::~Loader()
{



}


bool Loader::load(string path, Library<OpenGL_Window>* windowLibrary, Library<Scene>* sceneLibrary, Library<Camera>* cameraLibrary, Library<Object>* objectLibrary, Library<ModelRender>* modelRenderlibrary, Library<ModelBullet>* modelBulletLibrary, Library<Material>* materialLibrary, Library<Texture>* textureLibrary, Library<Shader>* shaderLibrary)
{


/*
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile( path,
            aiProcess_CalcTangentSpace       |
            aiProcess_Triangulate            |
            aiProcess_JoinIdenticalVertices  |
            aiProcess_SortByPType);

    if(!scene)
    {

        cout << "File does not exist or is corrupted : " << path << endl;

        return false;

    }else
    {

        cout << "Let's load !" << endl;

        for(unsigned int i = 0; i < scene->mNumMeshes; i++ )
        {

            aiMesh* mesh = scene->mMeshes[i];
            unsigned int numFaces = mesh->mNumFaces;
            for(unsigned int j = 0; j < numFaces; j++)
            {

                const aiFace& face = mesh->mFaces[j];
                for(unsigned int k = 0; k < 3; k++)
                {

                    aiVector3D pos = mesh->mVertices[face.mIndices[k]];
                    aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[k]];
                    aiVector3D normal = mesh->mNormals[face.mIndices[k]];

                }

            }

        }

        unsigned int numMaterials = scene->mNumMaterials;

        for(unsigned int i = 0; i < numMaterials; i++)
        {

            const aiMaterial* material = scene->mMaterials[i];
            aiString path;
            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
            {



            }

        }

    }*/

    return true;

}

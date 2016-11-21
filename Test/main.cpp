#include <iostream>
#include <string>

#include <GamePack.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
int main(int argc, char** argv)
{

    cout << "===== INIT =====" << endl;

    OpenGL_Window* window = GamePack::init(); // Initializes OpenGL context and creates a Window
    if(!window)
    {
        cout << "Error during OpenGL context initialization." << endl;
        GamePack::unload();
        return -1;
    }

    string file = "/home/guy/Bureau/simple.dae";

    if(argc >= 2)
    {

        file = argv[1];

    }

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile( file,
            aiProcess_CalcTangentSpace       |
            aiProcess_Triangulate            |
            aiProcess_JoinIdenticalVertices  |
            aiProcess_SortByPType);

    if(!scene)
    {

        cout << "File does not exist or is corrupted : " << file << endl;

    }else
    {

        cout << "Let's load !" << endl;

        for(int i = 0; i < scene->mNumMeshes; i++ )
        {

            aiMesh* mesh = scene->mMeshes[i];
            int numFaces = mesh->mNumFaces;
            for(int j = 0; j < numFaces; j++)
            {

                const aiFace& face = mesh->mFaces[j];
                for(int k = 0; k < 3; i++)
                {

                    aiVector3D pos = mesh->mVertices[face.mIndices[k]];
                    aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[k]];
                    aiVector3D normal = mesh->mNormals[face.mIndices[k]];


                }

            }

        }

        int numMaterials = scene->mNumMaterials;

        for(int i = 0; i < numMaterials; i++)
        {

            const aiMaterial* material = scene->mMaterials[i];
            aiString path;
            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
            {

                string filename =  path.data;

            }

        }

    }

    //----------

    Controller* controller = new Controller(); // a Controller to bind the ESCAPE key to the Window

    controller->bind(GLFW_KEY_ESCAPE, [&window](double x, double y) {

            window->close();

            });

    //===================================
    cout << "===== RENDER =====" << endl;

    while (!window->shouldClose())
    {

        int start = window->startFrame(); // Begin the frame render process

        controller->check(window); // Checks all bindings for the Window and execute de fonction if it matches

        window->render(); //

        window->endFrame(start); // End the frame render process and display the image on the window

    }

    //================================
    cout << "===== END =====" << endl;

    GamePack::unload(); // Unload all dictionnaries, and unload OpenGL context

    return 0;

}

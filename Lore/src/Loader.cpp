#include "Loader.h"

#include <iostream>

#include "Importer.h"

using namespace std;
using namespace LORE;

Loader::Loader()
{



}

Loader::~Loader()
{



}


bool Loader::load(string path, Library<Window>* windowLibrary, Library<Scene>* sceneLibrary, Library<Camera>* cameraLibrary, Library<Object>* objectLibrary, Library<ModelRender>* modelRenderlibrary, /*Library<ModelBullet>* modelBulletLibrary,*/ Library<Material>* materialLibrary, Library<Texture>* textureLibrary, Library<Shader>* shaderLibrary)
{

    string a = "/home/nabos/test.dae";

    Importer* importer = new LORE::Importer(a);

    importer->import();

    return true;

}

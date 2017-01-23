#ifndef LOADER_H
#define LOADER_H

#include <string>

#include <COLLADAFramework/COLLADAFWIWriter.h>

#include "Library.h"

#include "Window.h"
#include "Scene.h"
#include "Controller.h"
#include "ModelRender.h"
//#include "ModelBullet.h"
#include "Material.h"
//#include "Effect.h"
#include "Texture.h"
//#include "Light.h"
#include "Camera.h"
#include "Shader.h"

namespace LORE
{

    class Loader: public COLLADAFW::IWriter
    {

        public:

            static bool load(std::string path, Library<Window>* windowLibrary, Library<Scene>* sceneLibrary, Library<Camera>* cameraLibrary, Library<Object>* objectLibrary, Library<ModelRender>* modelRenderlibrary, /*Library<ModelBullet>* modelBulletLibrary,*/ Library<Material>* materialLibrary, Library<Texture>* textureLibrary, Library<Shader>* shaderLibrary);

        private:

            Loader();
            virtual ~Loader();

    };

}

#endif

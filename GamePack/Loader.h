#pragma once

#include <string>

#include "Library.h"

#include "OpenGL_Window.h"
#include "Scene.h"
#include "Controller.h"
#include "ModelRender.h"
#include "ModelBullet.h"
#include "Material.h"
//#include "Effect.h"
#include "Texture.h"
//#include "Light.h"
#include "Camera.h"
#include "Shader.h"



class Loader
{

	public:

        bool load(std::string path, Library<OpenGL_Window> windowLibrary, Library<Scene> sceneLibrary, Library<Camera> cameraLibrary, Library<Object> objectLibrary, Library<ModelRender> modelRenderlibrary, Library<ModelBullet> modelBulletLibrary, Library<Material> materialLibrary, Library<Texture> textureLibrary, Library<Shader> shaderLibrary);

	private:

        Loader();
        virtual ~Loader();

};

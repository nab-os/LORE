#include "Importer.h"

#include <iostream>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Scene.h"
#include "Lore.h"

using namespace glm;
using namespace std;
using namespace LORE;

Importer::Importer(string file): m__filePath(file)
{



}

Importer::~Importer()
{

}

void Importer::import()
{

    cout << "[Importer]: import()" << endl;

    gltf2::Asset asset = gltf2::load(m__filePath);
    
    cout << "[Importer]: import(): copyright " << asset.metadata.copyright << endl; 
    cout << "[Importer]: import(): version " << asset.metadata.version << endl; 
    cout << "[Importer]: import(): generator " << asset.metadata.generator << endl; 

    for(unsigned int i = 0; i < asset.scenes.size(); ++i)
    {
        importScene(asset, i);
    }
    
    //Not yet implemented by glTF2-loader
    /*for(unsigned int i = 0; i < asset.cameras.size(); ++i)
    {
        importCamera(asset, i);
    }*/

    for(unsigned int i = 0; i < asset.nodes.size(); ++i)
    {
        importNode(asset, i);
    }

    for(unsigned int i = 0; i < asset.meshes.size(); ++i)
    {
        importMesh(asset, i);
    }

}

void Importer::importScene(gltf2::Asset asset, unsigned int i)
{
    gltf2::Scene gscene = asset.scenes[i];
    Scene* scene = Lore::createScene(gscene.name);
    cout << "[Importer]: Scene: " << gscene.name << endl;
}


void Importer::importCamera(gltf2::Asset asset, unsigned int i)
{
    //Not yet implemented by glTF2-loader
    /*gltf2::Camera gcamera = asset.cameras[i];
    Camera* camera = Lore::createCamera(gcamera.name);
    cout << "[Importer]: Camera: " << gcamera.name << endl;
    camera->setRatio(gcamera.perspective.aspectRatio);
    camera->setFar(gcamera.perspective.zfar);
    camera->setNear(gcamera.perspective.znear);*/
}


void Importer::importNode(gltf2::Asset asset, unsigned int i)
{
    gltf2::Node gnode = asset.nodes[i];
    cout << "[Importer]: Node: " << gnode.name << endl;

    Node* node;

    if(gnode.camera != -1)
    {
        node = Lore::createCamera(gnode.name);
    }else if(gnode.mesh != -1)
    {
        node = Lore::createObject(gnode.name);
        importMesh(asset, gnode.mesh);
    }else if(gnode.skin != -1)
    {
        cout << "[Importer] Skin not implemented" << endl;
    }else
    {
        node = Lore::createNode(gnode.name);
    }
    
    node->setPosition(vec3(gnode.translation[0], gnode.translation[1], gnode.translation[2]));
    node->setScale(vec3(gnode.scale[0], gnode.scale[1], gnode.scale[2]));

}


void Importer::importMesh(gltf2::Asset asset, unsigned int i)
{
    gltf2::Mesh gmesh = asset.meshes[i];
    Mesh* mesh = Lore::createMesh(gmesh.name);
    
    for(unsigned int j = 0; j < gmesh.primitives.size(); ++j)
    {
        gltf2::Primitive primitive = gmesh.primitives[j];

        switch(primitive.mode)
        {
            case(gltf2::Primitive::Mode::Points):
                cout << "[Importer]: " << "Points primitive mode" << endl;
                break;
            case(gltf2::Primitive::Mode::Lines):
                cout << "[Importer]: " << "Lines primitive mode" << endl;
                break;
            case(gltf2::Primitive::Mode::LineLoop):
                cout << "[Importer]: " << "LineLoop primitive mode" << endl;
                break;
            case(gltf2::Primitive::Mode::LineStrip):
                cout << "[Importer]: " << "LineStrip primitive mode" << endl;
                break;
            case(gltf2::Primitive::Mode::Triangles):
                cout << "[Importer]: " << "Triangles primitive mode" << endl;
                cout << "[Importer]: " << "Indices: " << primitive.indices << endl;
                break;
            case(gltf2::Primitive::Mode::TriangleStrip):
                cout << "[Importer]: " << "TriangleStrip primitive mode" << endl;
                break;
            case(gltf2::Primitive::Mode::TriangleFan):
                cout << "[Importer]: " << "TriangleFan primitive mode" << endl;
                break;
            default:
                cout << "[Importer]: Unknown primitive mode." << endl;
        }

        gltf2::Attributes attributes = primitive.attributes;
        for(auto it: attributes)
        {
            //gltf2::Accessor accessor = asset.accessors[it.second];
            //gltf2::BufferView buffer_view = asset.bufferViews[accessor.bufferView];
            if( it.first == "POSITION")
            {
                cout << "[Importer]: " << "POSITION primitive" << endl;
            }else if(it.first == "NORMAL")
            {
                cout << "[Importer]: " << "NORMAL primitive" << endl;
            }else if(it.first == "TANGENT")
            {    
                cout << "[Importer]: " << "TANGENT primitive" << endl;
            }else if(it.first == "TEXCOORD_0")
            {        
                cout << "[Importer]: " << "TEXCOORD_0 primitive" << endl;
            }else   
            {    
                cout << "[Importer]: " << it.first << " not implemented." << endl;
            }
        }
    }
}


void Importer::importAccessor(gltf2::Asset asset, unsigned int i)
{
    
}

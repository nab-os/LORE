#include "Importer.h"

#include <iostream>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Library.h"
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

Scene* Importer::import()
{

    cout << "[Importer]: import()" << endl;

    if(m__filePath.substr(m__filePath.find_last_of(".") + 1) != "gltf")
    {
        cout << "File extension must be .gltf" << endl;
        exit(1);
        return NULL;
    }

    gltf2::Asset asset = gltf2::load(m__filePath);
    
    cout << "[Importer]: import(): copyright " << asset.metadata.copyright << endl; 
    cout << "[Importer]: import(): version " << asset.metadata.version << endl; 
    cout << "[Importer]: import(): generator " << asset.metadata.generator << endl; 

    for(unsigned int i = 0; i < asset.scenes.size(); ++i)
    {
        importScene(asset, i);
    }
    
    for(unsigned int i = 0; i < asset.cameras.size(); ++i)
    {
        importCamera(asset, i);
    }

    for(unsigned int i = 0; i < asset.images.size(); ++i)
    {
        cout << "[Import] Texture: " << i << endl;
        importTexture(asset, i);
    }

    for(unsigned int i = 0; i < asset.materials.size(); ++i)
    {
        cout << "[Import] Material: " << i << endl;
        importMaterial(asset, i);
    }

    /*
    for(unsigned int i = 0; i < asset..size(); ++i)
    {
        cout << "[Import] Shader: " << i << endl;
        importShader(asset, i);
    }*/

    for(unsigned int i = 0; i < asset.nodes.size(); ++i)
    {
        importNode(asset, i);
    }

    for(unsigned int i = 0; i < asset.meshes.size(); ++i)
    {
        cout << "[Import] Mesh: " << i << endl;
        importMesh(asset, i);
    }

    for(unsigned int i = 0; i < asset.scenes.size(); ++i)
    {
        buildTree(asset, i);
    }

    return m__scenes[asset.scene];

}

void Importer::importScene(gltf2::Asset asset, unsigned int i)
{
    gltf2::Scene gscene = asset.scenes[i];
	string name = gscene.name;
	if(name == "")
		name = "Scene";
    cout << "[Importer]: Scene: " << name << endl;
    Scene* scene = Lore::createScene(name);
	m__scenes.push_back(scene);
}


void Importer::importCamera(gltf2::Asset asset, unsigned int i)
{
    gltf2::Camera gcamera = asset.cameras[i];
	string name = gcamera.name;
	if(name == "")
		name = "Camera";
    cout << "[Importer]: Camera: " << name << endl;
    Camera* camera = Lore::createCamera(name);
	m__cameras.push_back(camera);

    camera->setRatio(gcamera.perspective.aspectRatio);
    camera->setFar(gcamera.perspective.far);
    camera->setNear(gcamera.perspective.near);
}


void Importer::importTexture(gltf2::Asset asset, unsigned int i)
{
    gltf2::Image image = asset.images[i];
    cout << "[Importer]: Texture: " << image.name << endl;
    Texture* texture = Lore::createTexture(image.uri);
	m__textures.push_back(texture);
    texture->load();
}


void Importer::importMaterial(gltf2::Asset asset, unsigned int i)
{
    gltf2::Material gmaterial = asset.materials[i];
	string name = gmaterial.name;
	if(name == "")
		name = "Material";
    cout << "[Importer]: Material: " << name << endl;
    Material* material = Lore::createMaterial(name);
	m__materials.push_back(material);

    material->setShader(Lore::getShader("default-120"));

    gltf2::Material::Pbr pbr = gmaterial.pbr;
    if(pbr.metallicRoughnessTexture.index != -1)
        material->setPbrTexture(m__textures[pbr.metallicRoughnessTexture.index]);
    if(pbr.baseColorTexture.index != -1)
        material->setDiffuseTexture(m__textures[pbr.baseColorTexture.index]);
    if(gmaterial.normalTexture.index != -1)
        material->setNormalTexture(m__textures[gmaterial.normalTexture.index]);
    if(gmaterial.occlusionTexture.index != -1)
        material->setOcclusionTexture(m__textures[gmaterial.occlusionTexture.index]);

    material->setDiffuseColor(glm::vec4(pbr.baseColorFactor[0], pbr.baseColorFactor[1], pbr.baseColorFactor[2], pbr.baseColorFactor[3]));
    material->setMetallness(pbr.metallicFactor);
    material->setRoughness(pbr.roughnessFactor);
    
    material->setCulling(!gmaterial.doubleSided);

    material->load();

}


void Importer::importNode(gltf2::Asset asset, unsigned int i)
{
    gltf2::Node gnode = asset.nodes[i];

    Node* node;
	string name = gnode.name;

    if(gnode.camera != -1)
    {
		if(name == "")
			name = "CameraNode";
        node = m__cameras[gnode.camera];
    }else if(gnode.mesh != -1)
    {
		if(name == "")
			name = "Object";
        node = Lore::createObject(name);
    }else if(gnode.skin != -1)
    {
		if(name == "")
			name = "Skin";
        cout << "[Importer] Skin not implemented" << endl;
    }else
    {
		if(name == "")
			name = "Node";
        node = Lore::createNode(name);
    }
    cout << "[Importer]: Node: " << name << endl;
	m__nodes.push_back(node);
    
    node->setPosition(vec3(gnode.translation[0], gnode.translation[1], gnode.translation[2]));
    node->setScale(vec3(gnode.scale[0], gnode.scale[1], gnode.scale[2]));

}


void Importer::importMesh(gltf2::Asset asset, unsigned int i)
{
    gltf2::Mesh gmesh = asset.meshes[i];
	string name = gmesh.name;
	if(name == "")
		name = "Mesh";
    cout << "[Importer]: Mesh: " << name << endl;
    Mesh* mesh = Lore::createMesh(name);
	m__meshes.push_back(mesh);
    
    for(auto primitive: gmesh.primitives)
    {
        if(primitive.indices != -1)
        {
            vector<float> indices_temp = importData(asset, asset.accessors[primitive.indices]);
            vector<unsigned int> indices;
            for(auto it: indices_temp)
            {
                //cout << "[Importer] Indice: " << it << endl;
                indices.push_back((unsigned int)it);
            }
            mesh->setIndexed(true);
            mesh->setIndices(indices);
        }else
        {
            mesh->setIndexed(false);
        }

        mesh->setMode((int)primitive.mode);
        
        gltf2::Attributes attributes = primitive.attributes;
        for(auto it: attributes)
        {
            gltf2::Accessor accessor = asset.accessors[it.second];
            vector<float> values = importData(asset, accessor);
            cout << "[Importer]: " << values.size() << endl;
            if( it.first == "POSITION")
            {
                cout << "[Importer]: " << "POSITION attribute: " << (int)accessor.componentType << endl;
                mesh->setVertices(values);
            }else if(it.first == "NORMAL")
            {
                cout << "[Importer]: " << "NORMAL attribute" << endl;
                mesh->setNormals(values);
            }else if(it.first == "TANGENT")
            {    
                cout << "[Importer]: " << "TANGENT attribute" << endl;
                mesh->setTangents(values);
            }else if(it.first == "COLOR_0")
            {    
                cout << "[Importer]: " << "COLOR_0 attribute" << endl;
                mesh->setColors(values);
            }else if(it.first == "TEXCOORD_0")
            {        
                cout << "[Importer]: " << "TEXCOORD_0 attribute: " << (int)accessor.type << endl;
                mesh->setUVs(values);
            }else   
            {    
                cout << "[Importer]: " << it.first << " not implemented." << endl;
            }
        }

        cout << "[Importer] Material: " << primitive.material << endl;
        if(primitive.material != -1)
            mesh->setMaterial(m__materials[primitive.material]);
        else
            mesh->setMaterial(Lore::getMaterial("default"));
    }
    cout << " [Importer]: Finished mesh import" << endl;
    mesh->load();
}


vector<float> Importer::importData(gltf2::Asset asset, gltf2::Accessor accessor)
{
    gltf2::BufferView buffer_view = asset.bufferViews[accessor.bufferView];
    gltf2::Buffer buffer = asset.buffers[buffer_view.buffer];
    unsigned int begin = accessor.byteOffset + buffer_view.byteOffset;
    unsigned int end = buffer_view.byteLength + buffer_view.byteOffset;
    unsigned int all = end - begin;
    cout << "Target: " << (int)buffer_view.target << endl;
    cout << "Begin: " << begin << " End: " << end << " Buffer size: " << all << " Count: " << accessor.count << endl;
    unsigned int size;

    vector<float> values;
    switch(accessor.componentType)
    {
        case(gltf2::Accessor::ComponentType::Byte):
            cout << "[Import] Byte component type" << endl;
            size = sizeof(char);
            for(unsigned int ptr = begin; ptr < end; ptr+=size)
            {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << (int)(*(char*)&buffer.data[ptr]) << endl;
                    values.push_back(*(char*)&buffer.data[ptr]);
                //}
            }
            break;
        case(gltf2::Accessor::ComponentType::UnsignedByte):
            cout << "[Import] UnsignedByte component type" << endl;
            size = sizeof(unsigned char);
            for(unsigned int ptr = begin; ptr < end; ptr+=size)
            {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << (int)(*(unsigned char*)&buffer.data[ptr]) << endl;
                    values.push_back(*(unsigned char*)&buffer.data[ptr]);
                //}
            }
            break;
        case(gltf2::Accessor::ComponentType::Short):
            cout << "[Import] Short component type" << endl;
            size = sizeof(short);
            for(unsigned int ptr = begin; ptr < end; ptr+=size)
            {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << *(short*)&buffer.data[ptr] << endl;
                    values.push_back(*(short*)&buffer.data[ptr]);
                //}
            }
            break;
        case(gltf2::Accessor::ComponentType::UnsignedShort):
            cout << "[Import] UnsignedShort component type" << endl;
            size = sizeof(unsigned short);
            for(unsigned int ptr = begin; ptr < end; ptr+=size)
            {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << *(unsigned short*)&buffer.data[ptr] << endl;
                    values.push_back(*(unsigned short*)&buffer.data[ptr]);
                //}
            }
            break;
        case(gltf2::Accessor::ComponentType::UnsignedInt):
            cout << "[Import] UnsignedInt component type" << endl;
            size = sizeof(unsigned int);
            for(unsigned int ptr = begin; ptr < end; ptr+=size)
            {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << *(unsigned int*)&buffer.data[ptr] << endl;
                    values.push_back(*(unsigned int*)&buffer.data[ptr]);
                //}
            }
            break;
        case(gltf2::Accessor::ComponentType::Float):
            cout << "[Import] Float component type: " << sizeof(float) << endl;
            size = sizeof(float);
            for(unsigned int ptr = begin; ptr < end; ptr+=size)
            {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << *(float*)&buffer.data[ptr] << endl;
                    values.push_back(*(float*)(&buffer.data[ptr]));
                //}
            }
            break;
        default:
            cout << "Unknown component type." << endl;
    }
    return values;
}


void Importer::buildTree(gltf2::Asset asset, unsigned int i)
{
    gltf2::Scene gscene = asset.scenes[i];
    Scene* scene = m__scenes[i];
    
    for(unsigned int j = 0; j < gscene.nodes.size(); ++j)
    {
        scene->addChild(m__nodes[gscene.nodes[j]]);
        buildNodeTree(asset, scene, j);
    }
}


void Importer::buildNodeTree(gltf2::Asset asset, Scene* scene, unsigned int i)
{
    cout << "[Importer]: buildNodeTree: " << i << endl;
    if(asset.nodes.size() > i)
    {
        gltf2::Node gnode = asset.nodes[i];
        Node* node = m__nodes[i];
        
        if(gnode.camera != -1)
        {
            Camera* camera = (Camera*)node;
    		camera->setScene(scene);
        }
        
		if(gnode.mesh != -1)
        {
            Object* obj = (Object*)node;
            obj->setMesh(m__meshes[gnode.mesh]);
        }

        for(unsigned int j = 0; j < gnode.children.size(); ++j)
        {
            node->addChild(m__nodes[gnode.children[j]]);
            buildNodeTree(asset, scene, gnode.children[j]);
        }
    }else
    {
        cout << "[Importer] Import error: node not found during tree construction!" << endl;
    }
}

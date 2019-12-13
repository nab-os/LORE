#include "Importer.h"

#include <iostream>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Library.h"
#include "Lore.h"

LORE::Importer::Importer(std::string file): m__filePath(file) {}

LORE::Importer::~Importer() {}

LORE::Scene* LORE::Importer::import() {
    std::cout << "[Importer]: import()" << std::endl;

    if(m__filePath.substr(m__filePath.find_last_of(".") + 1) != "gltf") {
        std::cout << "File extension must be .gltf" << std::endl;
        exit(1);
        return NULL;
    }

    gltf2::Asset asset = gltf2::load(m__filePath);

    std::cout << "[Importer]: import(): copyright " << asset.metadata.copyright << std::endl;
    std::cout << "[Importer]: import(): version " << asset.metadata.version << std::endl;
    std::cout << "[Importer]: import(): generator " << asset.metadata.generator << std::endl;

    for(unsigned int i = 0; i < asset.scenes.size(); ++i) {
        importScene(asset, i);
    }

    for(unsigned int i = 0; i < asset.cameras.size(); ++i) {
        importCamera(asset, i);
    }

    for(unsigned int i = 0; i < asset.images.size(); ++i) {
        std::cout << "[Import] Texture: " << i << std::endl;
        importTexture(asset, i);
    }

    for(unsigned int i = 0; i < asset.materials.size(); ++i) {
        std::cout << "[Import] Material: " << i << std::endl;
        importMaterial(asset, i);
    }

    /*
    for(unsigned int i = 0; i < asset..size(); ++i) {
        std::cout << "[Import] Shader: " << i << std::endl;
        importShader(asset, i);
    }*/

    for(unsigned int i = 0; i < asset.nodes.size(); ++i) {
        importNode(asset, i);
    }

    for(unsigned int i = 0; i < asset.meshes.size(); ++i) {
        std::cout << "[Import] Mesh: " << i << std::endl;
        importMesh(asset, i);
    }

    for(unsigned int i = 0; i < asset.scenes.size(); ++i) {
        buildTree(asset, i);
    }

    return m__scenes[asset.scene];
}

void LORE::Importer::importScene(gltf2::Asset asset, unsigned int i) {
    gltf2::Scene gscene = asset.scenes[i];
	std::string name = gscene.name;
	if(name == "")
		name = "Scene";
    std::cout << "[Importer]: Scene: " << name << std::endl;
    Scene* scene = Lore::createScene(name);
	m__scenes.push_back(scene);
}

void LORE::Importer::importCamera(gltf2::Asset asset, unsigned int i) {
    gltf2::Camera gcamera = asset.cameras[i];
	std::string name = gcamera.name;
	if(name == "")
		name = "Camera";
    std::cout << "[Importer]: Camera: " << name << std::endl;
    Camera* camera = Lore::createCamera(name);
	m__cameras.push_back(camera);

    camera->setRatio(gcamera.perspective.aspectRatio);
    camera->setFar(gcamera.perspective.far);
    camera->setNear(gcamera.perspective.near);
}

void LORE::Importer::importTexture(gltf2::Asset asset, unsigned int i) {
    gltf2::Image image = asset.images[i];
    std::cout << "[Importer]: Texture: " << image.name << std::endl;
    Texture* texture = Lore::createTexture(image.uri);
	m__textures.push_back(texture);
    texture->load();
}

void LORE::Importer::importMaterial(gltf2::Asset asset, unsigned int i) {
    gltf2::Material gmaterial = asset.materials[i];
	std::string name = gmaterial.name;
	if(name == "")
		name = "Material";
    std::cout << "[Importer]: Material: " << name << std::endl;
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

void LORE::Importer::importNode(gltf2::Asset asset, unsigned int i) {
    gltf2::Node gnode = asset.nodes[i];

    Node* node;
	std::string name = gnode.name;

    if(gnode.camera != -1) {
		if(name == "")
			name = "CameraNode";
        node = m__cameras[gnode.camera];
    }else if(gnode.mesh != -1) {
		if(name == "")
			name = "Object";
        node = Lore::createObject(name);
    }else if(gnode.skin != -1) {
		if(name == "")
			name = "Skin";
        std::cout << "[Importer] Skin not implemented" << std::endl;
    }else
    {
		if(name == "")
			name = "Node";
        node = Lore::createNode(name);
    }
    std::cout << "[Importer]: Node: " << name << std::endl;
	m__nodes.push_back(node);

    node->setPosition(glm::vec3(gnode.translation[0], gnode.translation[1], gnode.translation[2]));
    node->setScale(glm::vec3(gnode.scale[0], gnode.scale[1], gnode.scale[2]));

}

void LORE::Importer::importMesh(gltf2::Asset asset, unsigned int i) {
    gltf2::Mesh gmesh = asset.meshes[i];
	std::string name = gmesh.name;
	if(name == "")
		name = "Mesh";
    std::cout << "[Importer]: Mesh: " << name << std::endl;
    Mesh* mesh = Lore::createMesh(name);
	m__meshes.push_back(mesh);

    for(auto primitive: gmesh.primitives) {
        if(primitive.indices != -1) {
            std::vector<float> indices_temp = importData(asset, asset.accessors[primitive.indices]);
            std::vector<unsigned int> indices;
            for(auto it: indices_temp) {
                //cout << "[Importer] Indice: " << it << std::endl;
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
        for(auto it: attributes) {
            gltf2::Accessor accessor = asset.accessors[it.second];
            std::vector<float> values = importData(asset, accessor);
            std::cout << "[Importer]: " << values.size() << std::endl;
            if( it.first == "POSITION") {
                std::cout << "[Importer]: " << "POSITION attribute: " << (int)accessor.componentType << std::endl;
                mesh->setVertices(values);
            }else if(it.first == "NORMAL") {
                std::cout << "[Importer]: " << "NORMAL attribute" << std::endl;
                mesh->setNormals(values);
            }else if(it.first == "TANGENT") {
                std::cout << "[Importer]: " << "TANGENT attribute" << std::endl;
                mesh->setTangents(values);
            }else if(it.first == "COLOR_0") {
                std::cout << "[Importer]: " << "COLOR_0 attribute" << std::endl;
                mesh->setColors(values);
            }else if(it.first == "TEXCOORD_0") {
                std::cout << "[Importer]: " << "TEXCOORD_0 attribute: " << (int)accessor.type << std::endl;
                mesh->setUVs(values);
            }else
            {
                std::cout << "[Importer]: " << it.first << " not implemented." << std::endl;
            }
        }

        std::cout << "[Importer] Material: " << primitive.material << std::endl;
        if(primitive.material != -1)
            mesh->setMaterial(m__materials[primitive.material]);
        else
            mesh->setMaterial(Lore::getMaterial("default"));
    }
    std::cout << " [Importer]: Finished mesh import" << std::endl;
    mesh->load();
}

std::vector<float> LORE::Importer::importData(gltf2::Asset asset, gltf2::Accessor accessor) {
    gltf2::BufferView buffer_view = asset.bufferViews[accessor.bufferView];
    gltf2::Buffer buffer = asset.buffers[buffer_view.buffer];
    unsigned int begin = accessor.byteOffset + buffer_view.byteOffset;
    unsigned int end = buffer_view.byteLength + buffer_view.byteOffset;
    unsigned int all = end - begin;
    std::cout << "Target: " << (int)buffer_view.target << std::endl;
    std::cout << "Begin: " << begin << " End: " << end << " Buffer size: " << all << " Count: " << accessor.count << std::endl;
    unsigned int size;

    std::vector<float> values;
    switch(accessor.componentType) {
        case(gltf2::Accessor::ComponentType::Byte):
            std::cout << "[Import] Byte component type" << std::endl;
            size = sizeof(char);
            for(unsigned int ptr = begin; ptr < end; ptr+=size) {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << (int)(*(char*)&buffer.data[ptr]) << std::endl;
                    values.push_back(*(char*)&buffer.data[ptr]);
                //}
            }
            break;
        case(gltf2::Accessor::ComponentType::UnsignedByte):
            std::cout << "[Import] UnsignedByte component type" << std::endl;
            size = sizeof(unsigned char);
            for(unsigned int ptr = begin; ptr < end; ptr+=size) {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << (int)(*(unsigned char*)&buffer.data[ptr]) << std::endl;
                    values.push_back(*(unsigned char*)&buffer.data[ptr]);
                //}
            }
            break;
        case(gltf2::Accessor::ComponentType::Short):
            std::cout << "[Import] Short component type" << std::endl;
            size = sizeof(short);
            for(unsigned int ptr = begin; ptr < end; ptr+=size) {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << *(short*)&buffer.data[ptr] << std::endl;
                    values.push_back(*(short*)&buffer.data[ptr]);
                //}
            }
            break;
        case(gltf2::Accessor::ComponentType::UnsignedShort):
            std::cout << "[Import] UnsignedShort component type" << std::endl;
            size = sizeof(unsigned short);
            for(unsigned int ptr = begin; ptr < end; ptr+=size) {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << *(unsigned short*)&buffer.data[ptr] << std::endl;
                    values.push_back(*(unsigned short*)&buffer.data[ptr]);
                //}
            }
            break;
        case(gltf2::Accessor::ComponentType::UnsignedInt):
            std::cout << "[Import] UnsignedInt component type" << std::endl;
            size = sizeof(unsigned int);
            for(unsigned int ptr = begin; ptr < end; ptr+=size) {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << *(unsigned int*)&buffer.data[ptr] << std::endl;
                    values.push_back(*(unsigned int*)&buffer.data[ptr]);
                //}
            }
            break;
        case(gltf2::Accessor::ComponentType::Float):
            std::cout << "[Import] Float component type: " << sizeof(float) << std::endl;
            size = sizeof(float);
            for(unsigned int ptr = begin; ptr < end; ptr+=size) {
                //if(ptr != buffer_view.byteStride)
                //{
                    //cout << "Value: " << *(float*)&buffer.data[ptr] << std::endl;
                    values.push_back(*(float*)(&buffer.data[ptr]));
                //}
            }
            break;
        default:
            std::cout << "Unknown component type." << std::endl;
    }
    return values;
}

void LORE::Importer::buildTree(gltf2::Asset asset, unsigned int i) {
    gltf2::Scene gscene = asset.scenes[i];
    Scene* scene = m__scenes[i];

    for(unsigned int j = 0; j < gscene.nodes.size(); ++j) {
        scene->addChild(m__nodes[gscene.nodes[j]]);
        buildNodeTree(asset, scene, j);
    }
}

void LORE::Importer::buildNodeTree(gltf2::Asset asset, Scene* scene, unsigned int i) {
    std::cout << "[Importer]: buildNodeTree: " << i << std::endl;
    if(asset.nodes.size() > i) {
        gltf2::Node gnode = asset.nodes[i];
        Node* node = m__nodes[i];

        if(gnode.camera != -1) {
            Camera* camera = (Camera*)node;
    		camera->setScene(scene);
        }

		if(gnode.mesh != -1) {
            Object* obj = (Object*)node;
            obj->setMesh(m__meshes[gnode.mesh]);
        }

        for(unsigned int j = 0; j < gnode.children.size(); ++j) {
            node->addChild(m__nodes[gnode.children[j]]);
            buildNodeTree(asset, scene, gnode.children[j]);
        }
    }else
    {
        std::cout << "[Importer] Import error: node not found during tree construction!" << std::endl;
    }
}

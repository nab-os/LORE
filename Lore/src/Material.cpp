#include "Material.h"

#include <iostream>

using namespace std;
using namespace glm;
using namespace LORE;

Material::Material(): m__shader(), m__diffuseColor(vec4(0.5, 0, 0, 1)),
    m__metallness(0.0),
    m__roughness(0.5),
    m__customIntUniforms(),
    m__customFloatUniforms(),
    m__customVec2Uniforms(),
    m__customVec3Uniforms(),
    m__pbrTexture(),
    m__diffuseTexture(),
    m__normalTexture(),
    m__occlusionTexture(),
    m__textures(),
    m__culling(true)
{
	cout << this << " [Material] constructor" << endl;
}


Material::~Material()
{
}


void Material::load()
{
	cout << this << " [Material] load" << endl;
}
        

void Material::addCustomIntUniform(std::string name, int* value)
{
    m__customIntUniforms.insert(pair<string, int*>(name, value));
}


void Material::addCustomFloatUniform(std::string name, float* value)
{
    m__customFloatUniforms.insert(pair<string, float*>(name, value));
}


void Material::addCustomVec2Uniform(std::string name, glm::vec2* value)
{
    m__customVec2Uniforms.insert(pair<string, vec2*>(name, value));
}


void Material::addCustomVec3Uniform(std::string name, glm::vec3* value)
{
    m__customVec3Uniforms.insert(pair<string, vec3*>(name, value));
}


void Material::sendCustomUniforms()
{

    for(auto p: m__customIntUniforms)
    {
        m__shader->sendIntUniform(p.first, *p.second);
    }

    for(auto p: m__customFloatUniforms)
    {
        m__shader->sendFloatUniform(p.first, *p.second);
    }

    for(auto p: m__customVec2Uniforms)
    {
        m__shader->sendVec2Uniform(p.first, *p.second);
    }

    for(auto p: m__customVec3Uniforms)
    {
        m__shader->sendVec3Uniform(p.first, *p.second);
    }

}


void Material::sendTextures()
{
/*
    int i = 0;
    for(auto it: m__textures)
    {
        string name = it.first;
        GLuint texture_type = it.second.first;
        GLuint texture_id = it.second.second;

        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        m__shader->sendIntUniform(name, i); 

        i++;
    }
*/
}

#pragma once

#include "Shader.h"
#include "Texture.h"

class Material
{

public:

	Material();
	virtual ~Material();

	void load();

	Shader* getShader() { return m__shader; };
	void setShader(Shader* shader) { m__shader = shader; };

	glm::vec3 getDiffuseColor() { return m__diffuseColor; };
	void setDiffuseColor(glm::vec3 color) { m__diffuseColor = color; };

	glm::vec3 getSpecularColor() { return m__specularColor; };
	void setSpecularColor(glm::vec3 color) { m__specularColor = color; };

	Texture* getDiffuseTexture() { return m__diffuseTexture; };
	void setDiffuseTexture(Texture* texture) { m__diffuseTexture = texture; };

	Texture* getSpecularTexture() { return m__diffuseSpecular; };
	void setSpecularTexture(Texture* texture) { m__diffuseSpecular = texture; };

	private:

		Shader* m__shader;

		glm::vec3 m__diffuseColor;
		glm::vec3 m__specularColor;

		Texture* m__diffuseTexture;
		Texture* m__diffuseSpecular;

};


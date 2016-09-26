#pragma once

#include "Shader.h"

class Material
{

public:

	Material();
	virtual ~Material();

	void load();

	Shader* getShader();
	void setShader(Shader*);

	glm::vec3 getDiffuseColor() { return m__diffuseColor; };
	void setDiffuseColor(glm::vec3 color) { m__diffuseColor = color; };

	glm::vec3 getSpecularColor() { return m__specularColor; };
	void setSpecularColor(glm::vec3 color) { m__specularColor = color; };

	private:

		Shader* m__shader;

		glm::vec3 m__diffuseColor;
		glm::vec3 m__specularColor;

};


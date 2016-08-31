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

	private:

		Shader* m__shader;

};


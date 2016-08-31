#pragma once

#include <vector>

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"

#ifndef BUFFER_OFFSET

	#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

class Model
{

	public:

		Model();
		virtual ~Model();

		void load();

		int getVertexCount();
		int getVerticesSize();
		std::vector<glm::vec3> getVertices();
		float* getVerticesFloat();

		Material* getMaterial() { return m__material;  };

	private:


		Material* m__material;

	protected:

		std::vector<glm::vec3> m__vertices;

		static float* vec3ToFloat(std::vector<glm::vec3>);

};


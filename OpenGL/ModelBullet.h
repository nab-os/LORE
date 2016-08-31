#pragma once

#include <vector>

#include "Model.h"


#ifndef BUFFER_OFFSET

	#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

class ModelBullet : public Model
{

	public:

		ModelBullet();
		virtual ~ModelBullet();

		void load();

	private:

		

};


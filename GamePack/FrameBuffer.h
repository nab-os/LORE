#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SOIL.h>

#include "Texture.h"
#include "Camera.h"

class FrameBuffer
{

	public:

		FrameBuffer(int width = 768, int height = 768);
		virtual ~FrameBuffer();

		void load();
		void render();

		Camera* getCamera() { return m__camera; };
		void setCamera(Camera* camera) { m__camera = camera; };

		Texture* getRenderTexture() { return m__renderTexture; };

	protected:

		int m__width;
		int m__height;

		GLuint m__bufferID;

		Camera* m__camera;
		Texture* m__renderTexture;

		GLuint* m__depthBuffer;

};


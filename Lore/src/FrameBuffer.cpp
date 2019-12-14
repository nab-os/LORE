#include "FrameBuffer.h"

using std::cout;
using std::endl;

using namespace LORE;

FrameBuffer::FrameBuffer(int width, int height):
m__width(width),
m__height(height),
m__renderTexture() {
	cout << this << " [FrameBuffer] constructor" << endl;
}

FrameBuffer::~FrameBuffer() {
	delete m__renderTexture;
}

void FrameBuffer::load() {
	m__renderTexture = new Texture();
    m__renderTexture->load();

    glGenFramebuffers(1, &m__bufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m__bufferID);
		glBindTexture(GL_TEXTURE_2D, m__renderTexture->getID());

			// Give an empty image to OpenGL ( the last "0" )
			glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, m__width, m__height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

			// Poor filtering. Needed !
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			GLuint m__depthBuffer;
			glGenRenderbuffers(1, &m__depthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, m__depthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m__width, m__height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m__depthBuffer);

			// Set "renderedTexture" as our colour attachement #0
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m__renderTexture->getID(), 0);

			// Set the list of draw buffers.
			GLenum drawBuffers[2] = {GL_COLOR_ATTACHMENT0};
			glDrawBuffers(1, drawBuffers); // "1" is the size of DrawBuffers

		glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, m__bufferID);
	m__camera->render();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

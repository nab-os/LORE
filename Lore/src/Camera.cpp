#include "Camera.h"

#include <iostream>

#include <stb_image.h>

#include <Lore.h>
#include <Cube.h>

LORE::Camera::Camera(int width, int height, glm::vec3 position, glm::vec3 target, glm::vec3 verticalAxis, float sensibility, float speed): Node(),
    m__scene(),
    m_target(target),
    m_verticalAxis(verticalAxis),
    m_phi(0),
    m_theta(0),
    m_orientation(glm::vec3(1, 0, 0)),
    m_sensibility(sensibility),
    m_speed(0.05),
    m__ratio(16.0/9.0),
    m__far(500.0),
    m__near(0.1),
    m__backgroundColor(glm::vec3(0.2, 0.2, 0.2)),
    m__fbo(),
    m__rbo(),
    m__render() {
    std::cout << this << " [Camera] constructor" << std::endl;

	updatePerspective();

    glGenTextures(1, &m__environmentMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m__environmentMap);

    std::vector<std::string> textures_faces =
    {"Textures/right.jpg","Textures/left.jpg","Textures/top.jpg","Textures/bottom.jpg","Textures/back.jpg","Textures/front.jpg"};
    int imageWidth, imageHeight, nrChannels;
    unsigned char *data;
    for(GLuint i = 0; i < textures_faces.size(); i++) {
        data = stbi_load(textures_faces[i].c_str(), &imageWidth, &imageHeight, &nrChannels, 0);
        if (data) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                             0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap texture failed to load at path: " << textures_faces[i] << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    Node::setPosition(position);
	setOrientation(0,0);
/*
    m__render = new Texture();
    m__render->load();
    std::cout << "Texture loaded" << std::endl;
    glBindTexture(GL_TEXTURE_2D, m__render->getID());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0,
        //        GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    std::cout << "BBBB" << std::endl;

    glGenFramebuffers(1, &m__fbo);
    std::cout << "BBBB_" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, m__fbo);
        std::cout << "CCC" << std::endl;

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m__render->getID(), 0);
        //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m__render->getID(), 0);
        std::cout << "DDD" << std::endl;

        glGenRenderbuffers(1, &m__rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, m__rbo);
            std::cout << "EEE" << std::endl;

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m__rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    std::cout << "FFF" << std::endl;*/

    m__environmentCube = new Cube();
    m__environmentCube->load();
    m__environmentCube->setMaterial(Lore::getMaterial("environmentMap"));
}

LORE::Camera::~Camera() {
    std::cout << this << " [Camera] destructor" << std::endl;
    delete m__render;
    delete m__environmentCube;
}

void LORE::Camera::render() {
    //cout << this << " [Camera] render" << std::endl;
    render(NULL, m__projection, getView(), getModel(glm::mat4(1.0)));
}

void LORE::Camera::render(Node* renderer, glm::mat4 projection, glm::mat4 view, glm::mat4 model) {
//    if(renderer != this)
//   {
        //cout << this << " [Camera] render" << std::endl;
       // glBindFramebuffer(GL_FRAMEBUFFER, m__fbo);
            glViewport(0, 0, 1280, 768);

            glClearColor(m__backgroundColor.x, m__backgroundColor.y, m__backgroundColor.z, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            glm::mat4 _view = getView();

            glDepthMask(GL_FALSE);
            m__environmentCube->render(this, m__projection, glm::mat4(glm::mat3(_view)), glm::mat4(1.0));
            glDepthMask(GL_TRUE);
            if(m__scene)
                m__scene->render(this, m__projection, _view, glm::mat4(1.0));
            else
                std::cout << "[Camera]: Scene not set !" << std::endl;

        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    }
//    Node::render(renderer, projection, view, model);
}

// Méthodes

void LORE::Camera::updatePerspective() {
    m__projection = glm::perspective(90.0, m__ratio, m__near, m__far);
}

void LORE::Camera::setOrientation(double xRel, double yRel) {
    // Récupération des angles
    m_phi += -yRel * m_sensibility;
    m_theta += -xRel * m_sensibility;

    // Limitation de l'angle phi
    if (m_phi > 89.0)
        m_phi = 89.0;
    else if (m_phi < -89.0)
        m_phi = -89.0;

    // Conversion des angles en radian
    double phiRadian = m_phi * PI / 180;
    double thetaRadian = m_theta * PI / 180;

    // Si l'axe vertical est l'axe X
    if (m_verticalAxis.x == 1.0) {
        // Calcul des coordonnées sphériques
        m_orientation.x = sin(phiRadian);
        m_orientation.y = cos(phiRadian) * cos(thetaRadian);
        m_orientation.z = cos(phiRadian) * sin(thetaRadian);
    }
    else if (m_verticalAxis.y == 1.0) // Si c'est l'axe Y
    {
        // Calcul des coordonnées sphériques
        m_orientation.x = cos(phiRadian) * sin(thetaRadian);
        m_orientation.y = sin(phiRadian);
        m_orientation.z = cos(phiRadian) * cos(thetaRadian);
    }
    else // Sinon c'est l'axe Z
    {
        // Calcul des coordonnées sphériques
        m_orientation.x = cos(phiRadian) * cos(thetaRadian);
        m_orientation.y = cos(phiRadian) * sin(thetaRadian);
        m_orientation.z = sin(phiRadian);
    }

    // Calcul du point ciblé pour OpenGL
    m_target = Node::getPosition() + m_orientation;
}

void LORE::Camera::move(glm::vec3 pos) {
    Node::move(pos);
    m_target = Node::getPosition() + m_orientation;
}

void LORE::Camera::forward() {
    move(m_orientation * m_speed);
    m_target = Node::getPosition() + m_orientation;
}

void LORE::Camera::backward() {
    move(-m_orientation * m_speed);
    m_target = Node::getPosition() + m_orientation;
}

void LORE::Camera::left() {
    glm::vec3 side = normalize(cross(m_verticalAxis, m_orientation));
    move(side * m_speed);
    m_target = Node::getPosition() + m_orientation;
}

void LORE::Camera::right() {
    glm::vec3 side = normalize(cross(m_verticalAxis, m_orientation));
    move(-side * m_speed);
    m_target = Node::getPosition() + m_orientation;
}

void LORE::Camera::up() {
    move(m_verticalAxis * m_speed);
    m_target = Node::getPosition() + m_orientation;
}

void LORE::Camera::down() {
    move(-m_verticalAxis * m_speed);
    m_target = Node::getPosition() + m_orientation;
}

glm::mat4 LORE::Camera::getView() {
    return glm::lookAt(Node::getPosition(), m_target, glm::vec3(0, 1, 0));
}

// Getters et Setters
void LORE::Camera::setTarget(glm::vec3 target) {
    // Calcul du vecteur orientation
    glm::vec3 position = Node::getPosition();

    m_orientation = m_target - position;
    m_orientation = normalize(m_orientation);
	float phi, theta;

    // Si l'axe vertical est l'axe X
    if (m_verticalAxis.x == 1.0) {
        // Calcul des angles
        phi = asin(m_orientation.x);
        theta = acos(m_orientation.y / cos(phi));

        if (m_orientation.y < 0)
            theta *= -1;
    }
    else if (m_verticalAxis.y == 1.0) // Si c'est l'axe Y
    {
        // Calcul des angles
        phi = asin(m_orientation.y);
        theta = acos(m_orientation.z / cos(phi));

        if (m_orientation.z < 0)
            theta *= -1;
    }
    else // Sinon c'est l'axe Z
    {
        // Calcul des angles
        phi = asin(m_orientation.x);
        theta = acos(m_orientation.z / cos(phi));

        if (m_orientation.z < 0)
            theta *= -1;
    }

    // Conversion en degrés
    phi = phi * 180 / PI;
    theta = theta * 180 / PI;
}

float LORE::Camera::getSensibility() const {
    return m_sensibility;
}

float LORE::Camera::getSpeed() const {
    return m_speed;
}

void LORE::Camera::setSensibility(float sensibility) {
    m_sensibility = sensibility;
}

void LORE::Camera::setSpeed(float speed) {
    m_speed = speed;
}

bool LORE::Camera::getFly() const {
    return m_fly;
}

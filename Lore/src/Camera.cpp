#include "Camera.h"

#include <iostream>

#include <stb_image.h>

#include <Lore.h>
#include <Cube.h>

using namespace std;
using namespace glm;
using namespace LORE;

Camera::Camera(int width, int height, vec3 position, vec3 pointCible, vec3 axeVertical, float sensibilite, float vitesse): Node(),
    m__scene(),
    m_pointCible(pointCible),
    m_axeVertical(axeVertical),
    m_phi(0),
    m_theta(0),
    m_orientation(vec3(0)),
    m_sensibilite(sensibilite),
    m_vitesse(0.05),
    m__ratio(16.0/9.0),
    m__far(500.0),
    m__near(0.1),
    m__backgroundColor(vec3(0.2, 0.2, 0.2)),
    m__fbo(),
    m__render(),
    m__rbo()
{

    cout << this << " [Camera] constructor" << endl;

    m__projection = perspective(M_PI / 2.0, m__ratio, m__near, m__far);



    glGenTextures(1, &m__environmentMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m__environmentMap);

    std::vector<std::string> textures_faces = 
    {"Textures/right.jpg","Textures/left.jpg","Textures/top.jpg","Textures/bottom.jpg","Textures/back.jpg","Textures/front.jpg"};
    int imageWidth, imageHeight, nrChannels;
    unsigned char *data;  
    for(GLuint i = 0; i < textures_faces.size(); i++)
    {
        data = stbi_load(textures_faces[i].c_str(), &imageWidth, &imageHeight, &nrChannels, 0);
        if (data)
            {
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
/*   
    m__render = new Texture();
    m__render->load();
    cout << "Texture loaded" << endl;
    glBindTexture(GL_TEXTURE_2D, m__render->getID());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0, 
        //        GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    cout << "BBBB" << endl;

    glGenFramebuffers(1, &m__fbo);
    cout << "BBBB_" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, m__fbo);
        cout << "CCC" << endl;

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m__render->getID(), 0);
        //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m__render->getID(), 0);
        cout << "DDD" << endl;
        
        glGenRenderbuffers(1, &m__rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, m__rbo);  
            cout << "EEE" << endl;

            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m__rbo);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;  

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    cout << "FFF" << endl;*/

    m__environmentCube = new Cube();
    m__environmentCube->load();
    m__environmentCube->setMaterial(Lore::getMaterial("environmentMap"));

}


Camera::~Camera()
{
    cout << this << " [Camera] destructor" << endl;
    delete m__render;
    delete m__environmentCube;
}


void Camera::render()
{
    //cout << this << " [Camera] render" << endl;
    render(NULL, m__projection, getView(), getModel(mat4(1.0)));
}


void Camera::render(Node* renderer, glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
//    if(renderer != this)
//   {
        //cout << this << " [Camera] render" << endl;
       // glBindFramebuffer(GL_FRAMEBUFFER, m__fbo);
            glViewport(0, 0, 1280, 768);

            glClearColor(m__backgroundColor.x, m__backgroundColor.y, m__backgroundColor.z, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            glm::mat4 _view = getView();

            glDepthMask(GL_FALSE);
            m__environmentCube->render(this, m__projection, mat4(mat3(_view)), mat4(1.0));
            glDepthMask(GL_TRUE);
            if(m__scene)
                m__scene->render(this, m__projection, _view, mat4(1.0));
            else
                cout << "[Camera]: Scene not set !" << endl;
            
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    }
//    Node::render(renderer, projection, view, model);
}

// Méthodes

void Camera::updatePerspective()
{
    m__projection = perspective(90.0, m__ratio, m__near, m__far);
}

void Camera::orienter(double xRel, double yRel)
{
    // Récupération des angles
    m_phi += -yRel * m_sensibilite;
    m_theta += -xRel * m_sensibilite;

    // Limitation de l'angle phi
    if (m_phi > 89.0)
        m_phi = 89.0;
    else if (m_phi < -89.0)
        m_phi = -89.0;

    // Conversion des angles en radian
    double phiRadian = m_phi * PI / 180;
    double thetaRadian = m_theta * PI / 180;

    // Si l'axe vertical est l'axe X
    if (m_axeVertical.x == 1.0)
    {
        // Calcul des coordonnées sphériques
        m_orientation.x = sin(phiRadian);
        m_orientation.y = cos(phiRadian) * cos(thetaRadian);
        m_orientation.z = cos(phiRadian) * sin(thetaRadian);
    }
    else if (m_axeVertical.y == 1.0) // Si c'est l'axe Y
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
    m_pointCible = Node::getPosition() + m_orientation;
}


void Camera::move(glm::vec3 pos)
{
    Node::move(pos);
    m_pointCible = Node::getPosition() + m_orientation;
}


void Camera::forward()
{
    move(m_orientation * m_vitesse);
    m_pointCible = Node::getPosition() + m_orientation;
}


void Camera::backward()
{
    move(-m_orientation * m_vitesse);
    m_pointCible = Node::getPosition() + m_orientation;
}


void Camera::left()
{
    glm::vec3 side = normalize(cross(m_axeVertical, m_orientation)); 
    move(side * m_vitesse);
    m_pointCible = Node::getPosition() + m_orientation;
}


void Camera::right()
{
    glm::vec3 side = normalize(cross(m_axeVertical, m_orientation)); 
    move(-side * m_vitesse);
    m_pointCible = Node::getPosition() + m_orientation;
}


void Camera::up()
{
    move(m_axeVertical * m_vitesse);
    m_pointCible = Node::getPosition() + m_orientation;
}


void Camera::down()
{
    move(-m_axeVertical * m_vitesse);
    m_pointCible = Node::getPosition() + m_orientation;
}


void Camera::deplacer(glm::vec3 direction)
{
    Node::move(normalize(direction * m_orientation) * m_vitesse);
}


glm::mat4 Camera::getView()
{
    return glm::lookAt(Node::getPosition(), m_pointCible, glm::vec3(0, 1, 0));
}


// Getters et Setters
void Camera::setPointcible(glm::vec3 pointCible)
{
    // Calcul du vecteur orientation
    glm::vec3 position = Node::getPosition();

    m_orientation = m_pointCible - position;
    m_orientation = normalize(m_orientation);

    // Si l'axe vertical est l'axe X
    if (m_axeVertical.x == 1.0)
    {
        // Calcul des angles
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.y / cos(m_phi));

        if (m_orientation.y < 0)
            m_theta *= -1;
    }
    else if (m_axeVertical.y == 1.0) // Si c'est l'axe Y
    {
        // Calcul des angles
        m_phi = asin(m_orientation.y);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if (m_orientation.z < 0)
            m_theta *= -1;
    }
    else // Sinon c'est l'axe Z
    {
        // Calcul des angles
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if (m_orientation.z < 0)
            m_theta *= -1;
    }

    // Conversion en degrés
    m_phi = m_phi * 180 / PI;
    m_theta = m_theta * 180 / PI;
}


float Camera::getSensibilite() const
{
    return m_sensibilite;
}


float Camera::getVitesse() const
{
    return m_vitesse;
}


void Camera::setSensibilite(float sensibilite)
{
    m_sensibilite = sensibilite;
}


void Camera::setVitesse(float vitesse)
{
    m_vitesse = vitesse;
}


bool Camera::getFly() const
{
    return m_fly;
}

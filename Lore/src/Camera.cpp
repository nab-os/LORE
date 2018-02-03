#include "Camera.h"

#include <iostream>

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
    m_vitesse(vitesse),
    m__model(mat4(1.0)),
    m__far(0.1),
    m__near(500.0),
    m__backgroundColor(vec3(0.2, 0.2, 0.2))
{

    cout << this << " [Camera] constructor" << endl;

    updatePerspective();

    Node::setPosition(position);

}


Camera::~Camera()
{

    cout << this << " [Camera] destructor" << endl;

}


void Camera::load()
{

    cout << this << " [Camera] load" << endl;

    Node::load(/*m__scene->getWorld()*/);

}


void Camera::render()
{

    glViewport(0, 0, 1920, 1080);

    glClearColor(m__backgroundColor.x, m__backgroundColor.y, m__backgroundColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glm::mat4 view = mat4(1.0);

    if(m__scene)
    {

        view = getView();

    }

    m__scene->render(m__projection, m__model, view);

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


    // Si c'est l'axe Y

    else if (m_axeVertical.y == 1.0)
    {
        // Calcul des coordonnées sphériques

        m_orientation.x = cos(phiRadian) * sin(thetaRadian);
        m_orientation.y = sin(phiRadian);
        m_orientation.z = cos(phiRadian) * cos(thetaRadian);
    }


    // Sinon c'est l'axe Z

    else
    {
        // Calcul des coordonnées sphériques

        m_orientation.x = cos(phiRadian) * cos(thetaRadian);
        m_orientation.y = cos(phiRadian) * sin(thetaRadian);
        m_orientation.z = sin(phiRadian);
    }


    // Calcul de la normale

    m_deplacementLateral = cross(m_axeVertical, m_orientation);
    m_deplacementLateral = normalize(m_deplacementLateral);
    m_deplacement = cross(m_axeVertical, m_deplacementLateral);
    m_deplacement = -normalize(m_deplacement);


    // Calcul du point ciblé pour OpenGL

    m_pointCible = Node::getPosition() + m_orientation;
}


void Camera::deplacer(glm::vec3 direction)
{

    //glm::vec3 position = Node::getPosition();

    Node::move(direction * m_orientation * m_vitesse);

    //glm::vec3 deplacement = normalize(m_orientation + direction);

    /*position = position + deplacement * m_vitesse;

      m_pointCible = position + m_orientation;

      Node::setPosition(position);*/

}


glm::mat4 Camera::getView()
{

    //return glm::lookAt( glm::vec3(10,10, 10), glm::vec3(m_pointCible), glm::vec3(0, 1, 0));
    return glm::lookAt( Node::getPosition(), glm::vec3(m_pointCible), glm::vec3(0, 1, 0));

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


    // Si c'est l'axe Y

    else if (m_axeVertical.y == 1.0)
    {
        // Calcul des angles

        m_phi = asin(m_orientation.y);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if (m_orientation.z < 0)
            m_theta *= -1;
    }


    // Sinon c'est l'axe Z

    else
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
    return m_vitesse;
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

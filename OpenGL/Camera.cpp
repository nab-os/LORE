#include "stdafx.h"
#include "Camera.h"

#include <iostream>

using namespace std;
using namespace glm;

Camera::Camera(vec3 position, vec3 pointCible, vec3 axeVertical, float sensibilite, float vitesse)
{



}


Camera::~Camera()
{



}


// Méthodes
void Camera::orienter(int xRel, int yRel)
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

	m_pointCible = m_position + m_orientation;
}


void Camera::deplacer(/*Controller* c*/)
{
	// Gestion de l'orientation

	//std::cout<< "Fly mode : " << m_fly << "\n";
	/*if (input.mouvementSouris())
		orienter(input.getXRel(), input.getYRel());


	if (!m_fly) {

		// Avancée de la caméra
		if ((input.getTouche(GLFW_KEY_UP)) || (input.getTouche(GLFW_KEY_W)) || (input.getTouche(GLFW_KEY_Z)))
		{
			m_position = m_position + m_deplacement * m_vitesse;
			m_pointCible = m_position + m_orientation;
		}

		// Recul de la caméra
		if ((input.getTouche(GLFW_KEY_DOWN)) || (input.getTouche(GLFW_KEY_S)))
		{
			m_position = m_position - m_deplacement * m_vitesse;
			m_pointCible = m_position + m_orientation;
		}

	}
	else
	{

		// Avancée de la caméra
		if ((input.getTouche(GLFW_KEY_UP)) || (input.getTouche(GLFW_KEY_W)) || (input.getTouche(GLFW_KEY_Z)))
		{
			m_position = m_position + m_orientation * m_vitesse;
			m_pointCible = m_position + m_orientation;
		}

		// Recul de la caméra

		if (input.getTouche(GLFW_KEY_DOWN) || (input.getTouche(GLFW_KEY_S)))
		{
			m_position = m_position - m_orientation * m_vitesse;
			m_pointCible = m_position + m_orientation;
		}
	}


	// Déplacement vers la gauche
	if ((input.getTouche(GLFW_KEY_LEFT)) || (input.getTouche(GLFW_KEY_Q)) || (input.getTouche(GLFW_KEY_A)))
	{
		m_position = m_position + m_deplacementLateral * m_vitesse;
		m_pointCible = m_position + m_orientation;
	}

	// Déplacement vers la droite
	if ((input.getTouche(GLFW_KEY_RIGHT)) || (input.getTouche(GLFW_KEY_D)))
	{
		m_position = m_position - m_deplacementLateral * m_vitesse;
		m_pointCible = m_position + m_orientation;
	}

	if (input.getTouche(GLFW_KEY_SPACE))
	{
		m_position = m_position + vec3(0.0, 1.0, 0.0) * m_vitesse;
		m_pointCible = m_position + m_orientation;
	}

	if (input.getTouche(GLFW_KEY_LEFT_SHIFT))
	{
		m_position = m_position - vec3(0.0, 1.0, 0.0)  * m_vitesse;
		m_pointCible = m_position + m_orientation;
	}

	if (input.getTouche(GLFW_KEY_F))
	{
		if (m_fly == false) {
			m_fly = true;
		}
		else {
			m_fly = false;
		}
	}*/
}


void Camera::lookAt(glm::mat4 &modelview)
{
	// Actualisation de la vue dans la matrice
	modelview = glm::lookAt(m_position, m_pointCible, m_axeVertical);
}


// Getters et Setters
void Camera::setPointcible(glm::vec3 pointCible)
{
	// Calcul du vecteur orientation

	m_orientation = m_pointCible - m_position;
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


void Camera::setPosition(glm::vec3 position)
{
	// Mise à jour de la position

	m_position = position;


	// Actualisation du point ciblé

	m_pointCible = m_position + m_orientation;
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



glm::dvec3 Camera::getPosition() const
{

	return m_position;

}


glm::dvec3 Camera::getRotation() const
{
	return m_orientation;//180/PI * atan2( m_position.x - m_pointCible.x  , m_position.z - m_pointCible.z);
}


bool Camera::getFly() const
{

	return m_fly;

}
#pragma once

#ifndef PI
	#define PI 3.14159265359
#endif

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Controller.h"

class Camera
{

	public:

		Camera(glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 pointCible = glm::vec3(1, 0, 0), glm::vec3 axeVertical = glm::vec3(0, 1, 0), float sensibilite = 0.1, float vitesse = 0.5);
		virtual ~Camera();

		void orienter(int xRel, int yRel);
		void deplacer(/*Controller* c*/);
		void lookAt(glm::mat4 &modelview);

		void setPointcible(glm::vec3 pointCible);
		void setPosition(glm::vec3 position);

		float getSensibilite() const;
		float getVitesse() const;
		glm::dvec3 getPosition() const;

		bool getFly() const;

		void setSensibilite(float sensibilite);
		void setVitesse(float vitesse);

		glm::dvec3 getRotation() const;

	private:

		double m_phi;
		double m_theta;
		glm::dvec3 m_orientation;

		glm::dvec3 m_axeVertical;
		glm::dvec3 m_deplacementLateral;
		glm::dvec3 m_deplacement;

		glm::dvec3 m_position;
		glm::dvec3 m_pointCible;

		float m_sensibilite;
		float m_vitesse;

		bool m_fly;

};


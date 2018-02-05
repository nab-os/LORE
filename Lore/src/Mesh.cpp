#include "Mesh.h"

#include <iostream>

using namespace std;
using namespace glm;
using namespace LORE;

Mesh::Mesh(): m__VAO(), m__elementBuffer(), m__vertexBuffer(), m__UVBuffer(), m__normalBuffer(), m__colorBuffer(), m__material(), m__vertices(), m__indexed(false), m__mode(GL_TRIANGLES)
{
	//cout << this << " [Mesh] constructor" << endl;
}


Mesh::~Mesh()
{
	//cout << this << " [Mesh] destructor" << endl;
}


void Mesh::load()
{

	cout << "[Mesh] load: " << m__vertices.size() << endl;

	//Tangent compute
	//vector<float> vecTangents = m__normals;
	//vector<float> vecBytangents = m__normals;

	//computeTangentBasis(m__vertices, m__UVs, m__normals, vecTangents, vecBytangents);
   /* 
	cout << "[Mesh] load() : Indices : " << endl;
    for(unsigned int i = 0; i < m__indices.size(); i+=3)
    {
		cout << (i/3) << ": " << m__indices[i] << ", " << m__indices[i+1] << ", " << m__indices[i+2] << endl;
	}

	cout << "[Mesh] load() : Vertices : " << endl;
    for(unsigned int i = 0; i < m__vertices.size(); i+=3)
    {
		cout << (i/3) << ": " << m__vertices[i] << ", " << m__vertices[i+1] << ", " << m__vertices[i+2] << endl;
	}
	cout << "[Mesh] load() : UVs : \n";
	for (unsigned int i = 0; i < m__UVs.size(); i+=2)
	{
		cout << (i/2) << ": " << m__UVs[i] << ", " << m__UVs[i+1] << endl;
	}
	cout << "[Mesh] load() : Normals : \n";
	for (int i = 0; i < this->getNormalCount(); i++)
	{

		cout << m__normals[i].x << ", " << m__normals[i].y << ", " << m__normals[i].z << endl;

	}
	*/

	//===============================VBOs================================

    if(m__indexed)
    {
        // Destruction d'un éventuel ancien VBO
        if (glIsBuffer(m__elementBuffer) == GL_TRUE)
            glDeleteBuffers(1, &m__elementBuffer);

        // Génération de l'ID
        glGenBuffers(1, &m__elementBuffer);

        // Verrouillage du VBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m__elementBuffer);

            // Allocation de la mémoire vidéo
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m__indices.size() * sizeof(unsigned int), &m__indices[0], GL_STATIC_DRAW);

        // Déverrouillage de l'objet
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    // Destruction d'un éventuel ancien VBO
	if (glIsBuffer(m__vertexBuffer) == GL_TRUE)
		glDeleteBuffers(1, &m__vertexBuffer);

	// Génération de l'ID
	glGenBuffers(1, &m__vertexBuffer);

	// Verrouillage du VBO
	glBindBuffer(GL_ARRAY_BUFFER, m__vertexBuffer);

		// Allocation de la mémoire vidéo
		glBufferData(GL_ARRAY_BUFFER, m__vertices.size() * sizeof(float), &m__vertices[0], GL_STATIC_DRAW);

	// Déverrouillage de l'objet
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
    
    if(m__UVs.size() > 0)
    {
        // Destruction d'un éventuel ancien VBO
        if (glIsBuffer(m__UVBuffer) == GL_TRUE)
            glDeleteBuffers(1, &m__UVBuffer);

        // Génération de l'ID
        glGenBuffers(1, &m__UVBuffer);

        // Verrouillage du VBO
        glBindBuffer(GL_ARRAY_BUFFER, m__UVBuffer);

            // Allocation de la mémoire vidéo
            glBufferData(GL_ARRAY_BUFFER, m__UVs.size() * sizeof(float), &m__UVs[0], GL_STATIC_DRAW);

        // Déverrouillage de l'objet
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
	
    
    if(m__normals.size() > 0)
    {
        // Destruction d'un éventuel ancien VBO
        if (glIsBuffer(m__normalBuffer) == GL_TRUE)
            glDeleteBuffers(1, &m__normalBuffer);

        // Génération de l'ID
        glGenBuffers(1, &m__normalBuffer);

        // Verrouillage du VBO
        glBindBuffer(GL_ARRAY_BUFFER, m__normalBuffer);

            // Allocation de la mémoire vidéo
            glBufferData(GL_ARRAY_BUFFER, m__normals.size() * sizeof(float), &m__normals[0], GL_STATIC_DRAW);

        // Déverrouillage de l'objet
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
	
    
    if(m__colors.size() > 0)
    {
        // Destruction d'un éventuel ancien VBO
        if (glIsBuffer(m__colorBuffer) == GL_TRUE)
            glDeleteBuffers(1, &m__colorBuffer);

        // Génération de l'ID
        glGenBuffers(1, &m__colorBuffer);

        // Verrouillage du VBO
        glBindBuffer(GL_ARRAY_BUFFER, m__colorBuffer);

            // Allocation de la mémoire vidéo
            glBufferData(GL_ARRAY_BUFFER, m__colors.size() * sizeof(float), &m__colors[0], GL_STATIC_DRAW);

        // Déverrouillage de l'objet
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


	//=======================================================================
	// Destruction d'un éventuel ancien VAO

	if (glIsVertexArray(m__VAO) == GL_TRUE)
		glDeleteVertexArrays(1, &m__VAO);

	// Génération de l'identifiant du VAO
	glGenVertexArrays(1, &m__VAO);

	// Verrouillage du VAO
	glBindVertexArray(m__VAO);

		// Verrouillage du VBO
		glBindBuffer(GL_ARRAY_BUFFER, m__vertexBuffer);

			// Accès aux vertices dans la mémoire vidéo

			//Vertices
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(0);

		// Déverrouillage du VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

        if(m__UVs.size() > 0)
        {
            // Verrouillage du VBO
            glBindBuffer(GL_ARRAY_BUFFER, m__UVBuffer);

                // Accès aux uvs dans la mémoire vidéo

                //UVs
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                glEnableVertexAttribArray(1);

            // Déverrouillage du VBO
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        if(m__normals.size() > 0)
        {
            // Verrouillage du VBO
            glBindBuffer(GL_ARRAY_BUFFER, m__normalBuffer);

                // Accès aux normales dans la mémoire vidéo

                //Normals
                glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                glEnableVertexAttribArray(2);

            // Déverrouillage du VBO
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        if(m__colors.size() > 0)
        {
            // Verrouillage du VBO
            glBindBuffer(GL_ARRAY_BUFFER, m__colorBuffer);

                // Accès aux colores dans la mémoire vidéo

                //colors
                glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                glEnableVertexAttribArray(5);

            // Déverrouillage du VBO
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
/*
			//Tangents
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(3);

			//Bytangents
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
			glEnableVertexAttribArray(4);*/

	// Déverrouillage du VAO
	glBindVertexArray(0);
}






void Mesh::render(mat4 projection, mat4 view, mat4 model, GLuint environmentMapID)
{
    //cout << this << "[Mesh] render" << endl;

	glEnable(GL_DEPTH_TEST);
    if(m__material->getCulling())
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    Shader* s = m__material->getShader();

	glUseProgram(s->getProgramID());

	glBindVertexArray(m__VAO);

    s->envoyerMat4("projection", projection);
    s->envoyerMat4("view", view);
    s->envoyerMat4("model", model);

    s->envoyerVec4("u_diffuseColor", m__material->getDiffuseColor());
    s->envoyerFloat("u_metalness", m__material->getMetallness());
    s->envoyerFloat("u_roughness", m__material->getRoughness());
    
    if(m__material->getDiffuseTexture())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m__material->getDiffuseTexture()->getID());
        s->envoyer1I("u_diffuseTexture", 0); 
        s->envoyer1I("u_useDiffuseTexture", 1); 
    }else
    {
        s->envoyer1I("u_useDiffuseTexture", 0); 
    }
    
    if(m__material->getPbrTexture())
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m__material->getPbrTexture()->getID());
        s->envoyer1I("u_pbrTexture", 1); 
        s->envoyer1I("u_usePbrTexture", 1); 
    }else
    {
        s->envoyer1I("u_usePbrTexture", 0); 
    }
    
    if(m__material->getNormalTexture())
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m__material->getNormalTexture()->getID());
        s->envoyer1I("u_normalTexture", 2); 
        s->envoyer1I("u_useNormalTexture", 1); 
    }else
    {
        s->envoyer1I("u_useNormalTexture", 0); 
    }

    /*glPatchParameteri(GL_PATCH_VERTICES, 3);
	glDrawArrays(GL_PATCHES, 0, getVertexCount());*/
    //cout << this << "[Mesh] render 2" << endl;

    if(m__indexed)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m__elementBuffer);

        // Draw the triangles !
        glDrawElements(
                m__mode,      // mode
                m__indices.size(),    // count
                GL_UNSIGNED_INT,   // type
                (void*)0           // element array buffer offset
        );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }else
    {
        glDrawArrays(m__mode, 0, m__vertices.size());
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

	glUseProgram(0);
/*
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((const GLfloat*)&projection[0]);

	glMatrixMode(GL_MODELVIEW);
	glm::mat4 MV = view * model;
	glLoadMatrixf((const GLfloat*)&MV[0]);


	glColor3f(0,0,1);

	glBegin(GL_LINES);

    cout << "[Mesh] render(): a : " << m__vertices.size() << endl;
	for (unsigned int i=0; i < m__vertices.size(); i+=3)
    {

        cout << "[Mesh] render(): b : " << m__vertices[i] << " ; " << m__vertices[i] << " ; " << m__vertices[i] << endl;

		glVertex3fv(&m__vertices[i]);

//		glm::vec3 o = glm::normalize(m__normals[i]);
//		p+=o*0.1f;
//		glVertex3fv(&p.x);

	}

	glEnd();
*/
}


/*
void Mesh::computeTangentBasis(   // inputs
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals,

	// outputs
	std::vector<glm::vec3> & tangents,
	std::vector<glm::vec3> & bitangents)
{

	for (unsigned int i = 0; i<vertices.size(); i += 3) {


		// Shortcuts for vertices
		glm::vec3 & v0 = vertices[i + 0];
		glm::vec3 & v1 = vertices[i + 1];
		glm::vec3 & v2 = vertices[i + 2];


		// Shortcuts for UVs
		glm::vec2 & uv0 = uvs[i + 0];
		glm::vec2 & uv1 = uvs[i + 1];
		glm::vec2 & uv2 = uvs[i + 2];


		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;


		// UV delta
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;


		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;


		// Set the same tangent for all three vertices of the triangle.

		// They will be merged later, in vboindexer.cpp
		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		// Same thing for binormals
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);

	}

}*/

#include "Mesh.h"

#include <iostream>
#include "Camera.h"

using namespace std;
using namespace glm;
using namespace LORE;

Mesh::Mesh(): m__VAO(),
    m__elementBuffer(),
    m__vertexBuffer(),
    m__UVBuffer(),
    m__normalBuffer(),
    m__tangentBuffer(),
    m__bitangentBuffer(),
    m__colorBuffer(),
    m__material(),
    m__vertices(),
    m__indexed(false),
    m__mode(GL_TRIANGLES)
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
	/*
    cout << "[Mesh] load() : Indices : " << endl;
    for(unsigned int i = 0; i < m__indices.size(); i++)
    {
		//cout << (i/3) << ": " << m__indices[i] << ", " << m__indices[i+1] << ", " << m__indices[i+2] << endl;
        vec3 normal(m__normals[m__indices[i]*3], m__normals[m__indices[i]*3 + 1], m__normals[m__indices[i]*3 + 1]);
        vec3 tangent(m__tangents[m__indices[i]*3], m__tangents[m__indices[i]*3 + 1], m__tangents[m__indices[i]*3 + 1]);
        vec3 bitangent = cross(normal, tangent);
        cout << i << ": " << normal.x << ", " << normal.y << ", " << normal.z << endl;
        cout << i << ": " << tangent.x << ", " << tangent.y << ", " << tangent.z << endl;
        //cout << i << ": " << bitangent.x << ", " << bitangent.y << ", " << bitangent.z << endl;
	}*/

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
	
    if(m__normals.size() > 0 && m__tangents.size() > 0)
        computeBitangents();
    else if(m__normals.size() > 0 && m__UVs.size() > 0)
        computeTangentBasis();
    else
        cout << "[Mesh] Cant compute tangent basis" << endl;
    
    if(m__tangents.size() > 0)
    {
        /*
        cout << "[Mesh] load() : Tangents : " << endl;
        for (int i = 0; i < m__tangents.size(); i+=3)
        {

            cout << m__tangents[i] << ", " << m__tangents[i+1] << ", " << m__tangents[i+2] << endl;

        }*/

        // Destruction d'un éventuel ancien VBO
        if (glIsBuffer(m__tangentBuffer) == GL_TRUE)
            glDeleteBuffers(1, &m__tangentBuffer);

        // Génération de l'ID
        glGenBuffers(1, &m__tangentBuffer);

        // Verrouillage du VBO
        glBindBuffer(GL_ARRAY_BUFFER, m__tangentBuffer);

            // Allocation de la mémoire vidéo
            glBufferData(GL_ARRAY_BUFFER, m__tangents.size() * sizeof(float), &m__tangents[0], GL_STATIC_DRAW);

        // Déverrouillage de l'objet
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    if(m__bitangents.size() > 0)
    {
        // Destruction d'un éventuel ancien VBO
        if (glIsBuffer(m__bitangentBuffer) == GL_TRUE)
            glDeleteBuffers(1, &m__bitangentBuffer);

        // Génération de l'ID
        glGenBuffers(1, &m__bitangentBuffer);

        // Verrouillage du VBO
        glBindBuffer(GL_ARRAY_BUFFER, m__bitangentBuffer);

            // Allocation de la mémoire vidéo
            glBufferData(GL_ARRAY_BUFFER, m__bitangents.size() * sizeof(float), &m__bitangents[0], GL_STATIC_DRAW);

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

        if(m__tangents.size() > 0)
        {
            // Verrouillage du VBO
            glBindBuffer(GL_ARRAY_BUFFER, m__tangentBuffer);

                // Accès aux tangentes dans la mémoire vidéo

                //tangents
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                glEnableVertexAttribArray(3);

            // Déverrouillage du VBO
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        if(m__bitangents.size() > 0)
        {
            // Verrouillage du VBO
            glBindBuffer(GL_ARRAY_BUFFER, m__bitangentBuffer);

                // Accès aux bitangentes dans la mémoire vidéo

                //bitangents
                glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                glEnableVertexAttribArray(4);

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

	// Déverrouillage du VAO
	glBindVertexArray(0);
}


void Mesh::render(Node* renderer, mat4 projection, mat4 view, mat4 model, GLuint environmentMapID)
{
    //cout << this << "[Mesh] render" << endl;

	glEnable(GL_DEPTH_TEST);
    //if(m__material->getCulling())
    //    glEnable(GL_CULL_FACE);
    //else
    glDisable(GL_CULL_FACE);

    Shader* s = m__material->getShader();

	glUseProgram(s->getProgramID());

	glBindVertexArray(m__VAO);

    s->sendMat4Uniform("projection", projection);
    s->sendMat4Uniform("view", view);
    s->sendMat4Uniform("model", model);

    s->sendVec3Uniform("u_cameraPosition", renderer->getPosition());
    s->sendVec3Uniform("u_lightPosition", Light::lightPosition);

    s->sendVec4Uniform("u_diffuseColor", m__material->getDiffuseColor());
    s->sendFloatUniform("u_metalness", m__material->getMetallness());
    s->sendFloatUniform("u_roughness", m__material->getRoughness());

    glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ((Camera*)renderer)->getEnvironmentMap());
    s->sendIntUniform("u_environmentMap", 9);

    if(m__colors.size() >  0)
    {
        s->sendIntUniform("u_useVertexColor", 1); 
    }else
    {
        s->sendIntUniform("u_useVertexColor", 0); 
    }

    if(m__material->getDiffuseTexture())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m__material->getDiffuseTexture()->getID());
        s->sendIntUniform("u_diffuseTexture", 0); 
        s->sendIntUniform("u_useDiffuseTexture", 1); 
    }else
    {
        s->sendIntUniform("u_useDiffuseTexture", 0); 
    }
    
    if(m__material->getPbrTexture())
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m__material->getPbrTexture()->getID());
        s->sendIntUniform("u_pbrTexture", 1); 
        s->sendIntUniform("u_usePbrTexture", 1); 
    }else
    {
        s->sendIntUniform("u_usePbrTexture", 0); 
    }

    if(m__material)
        m__material->sendCustomUniforms();
    
    if(m__material->getNormalTexture())
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m__material->getNormalTexture()->getID());
        s->sendIntUniform("u_normalTexture", 2); 
        s->sendIntUniform("u_useNormalTexture", 1); 
    }else
    {
        s->sendIntUniform("u_useNormalTexture", 0); 
    }
    
    if(m__material->getOcclusionTexture())
    {
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, m__material->getOcclusionTexture()->getID());
        s->sendIntUniform("u_occlusionTexture", 3); 
        s->sendIntUniform("u_useOcclusionTexture", 1); 
    }else
    {
        s->sendIntUniform("u_useOcclusionTexture", 0); 
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

	for (unsigned int i=0; i < m__vertices.size(); i+=3)
    {

       // cout << "[Mesh] render(): b : " << m__vertices[i] << " ; " << m__vertices[i] << " ; " << m__vertices[i] << endl;

//		glVertex3fv(&m__vertices[i]);

        vec3 p(m__vertices[i], m__vertices[i+1], m__vertices[i+2]);
        vec3 o(m__normals[i], m__normals[i+1], m__normals[i+2]);

		o = glm::normalize(o);
		p += o*0.1f;
		glVertex3fv(&p.x);

	}

	glEnd();
    */
}


void Mesh::computeBitangents()
{
    cout << "[Mesh] Computing tangent basis from Normals and Tangent" << endl;
    m__bitangents = m__tangents;
    for(unsigned int i = 0; i < m__indices.size(); ++i)
    {
        unsigned int index = m__indices[i]*3;

        vec3 normal = vec3(m__normals[index], m__normals[index+1], m__normals[index+2]);
        vec3 tangent = vec3(m__tangents[index], m__tangents[index+1], m__tangents[index+2]);
        vec3 bitangent = cross(normal, tangent);
    
        m__bitangents[index] = bitangent.x;
        m__bitangents[index+1] = bitangent.y;
        m__bitangents[index+2] = bitangent.z;
    }
    /*for(unsigned int i = 0; i < m__normals.size(); i+=3)
    {
        vec3 normal = vec3(m__normals[i], m__normals[i+1], m__normals[i+2]);
        vec3 tangent = vec3(m__tangents[i], m__tangents[i+1], m__tangents[i+2]);
        vec3 bitangent = cross(normal, tangent);
    
        m__bitangents.push_back(bitangent.x);
        m__bitangents.push_back(bitangent.y);
        m__bitangents.push_back(bitangent.z);
    }*/
}


void Mesh::computeTangentBasis()
{
    cout << "[Mesh] Computing tangent basis from Normals and UVs directions" << endl;
    m__tangents = m__normals;
    m__bitangents = m__normals;
    for (unsigned int i=0; i < m__indices.size(); i+=3){

        // Shortcuts for vertices
        unsigned int index1_vec2 = m__indices[i] * 2;
        unsigned int index2_vec2 = m__indices[i + 1] * 2;
        unsigned int index3_vec2 = m__indices[i + 2] * 2;
        unsigned int index1_vec3 = m__indices[i] * 3;
        unsigned int index2_vec3 = m__indices[i + 1] * 3;
        unsigned int index3_vec3 = m__indices[i + 2] * 3;

        glm::vec3 v0 = vec3(m__vertices[index1_vec3], m__vertices[index1_vec3 + 1], m__vertices[index1_vec3 + 2]);
        glm::vec3 v1 = vec3(m__vertices[index2_vec3], m__vertices[index2_vec3 + 1], m__vertices[index2_vec3 + 2]);
        glm::vec3 v2 = vec3(m__vertices[index3_vec3], m__vertices[index3_vec3 + 1], m__vertices[index3_vec3 + 2]);

        // Shortcuts for UVs
        glm::vec2 uv0 = vec2(m__UVs[index1_vec2], m__UVs[index1_vec2 + 1]);
        glm::vec2 uv1 = vec2(m__UVs[index2_vec2], m__UVs[index2_vec2 + 1]);
        glm::vec2 uv2 = vec2(m__UVs[index3_vec2], m__UVs[index3_vec2 + 1]);

        // Edges of the triangle : postion delta
        glm::vec3 deltaPos1 = v1-v0;
        glm::vec3 deltaPos2 = v2-v0;

        // UV delta
        glm::vec2 deltaUV1 = uv1-uv0;
        glm::vec2 deltaUV2 = uv2-uv0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;
        //cout << i << ": " << m__tangents[index1_vec3] << ", " << m__tangents[index1_vec3+1] << ", " << m__tangents[index1_vec3+2] << endl;
        //cout << i << ": " << tangent.x << ", " << tangent.y << ", " << tangent.z << endl;
        
        m__tangents[index1_vec3] = tangent.x;
        m__tangents[index1_vec3 + 1] = tangent.y;
        m__tangents[index1_vec3 + 2] = tangent.z;
        m__tangents[index2_vec3] = tangent.x;
        m__tangents[index2_vec3 + 1] = tangent.y;
        m__tangents[index2_vec3 + 2] = tangent.z;
        m__tangents[index3_vec3] = tangent.x;
        m__tangents[index3_vec3 + 1] = tangent.y;
        m__tangents[index3_vec3 + 2] = tangent.z;
        
        m__bitangents[index1_vec3] = bitangent.x;
        m__bitangents[index1_vec3 + 1] = bitangent.y;
        m__bitangents[index1_vec3 + 2] = bitangent.z;
        m__bitangents[index2_vec3] = bitangent.x;
        m__bitangents[index2_vec3 + 1] = bitangent.y;
        m__bitangents[index2_vec3 + 2] = bitangent.z;
        m__bitangents[index3_vec3] = bitangent.x;
        m__bitangents[index3_vec3 + 1] = bitangent.y;
        m__bitangents[index3_vec3 + 2] = bitangent.z;

    }
}

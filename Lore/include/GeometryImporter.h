#ifndef GEOMETRYIMPORTER_H
#define GEOMETRYIMPORTER_H

#include <string>

#include <COLLADAFramework/COLLADAFWGeometry.h>
#include <COLLADAFWMeshPrimitive.h>
#include <COLLADAFWMeshVertexData.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Library.h"
#include "Mesh.h"

namespace LORE
{

    class Importer;

    class GeometryImporter
    {

        public:

            GeometryImporter(Importer* documentImporter, const COLLADAFW::Geometry* geometry);
            ~GeometryImporter();

            bool import();

        private:

            Importer* mImporter;

            /** The number of all triangles in all primitives that contain triangles (Triangles,
             *      Tristrips, Trisfans).*/
            size_t mTotalTrianglesCount;

            /** True, if the geometry has per vertex color.*/
            bool mHasVertexColor;

            /** The geometry that should be imported.*/
            const COLLADAFW::Geometry* mGeometry;

            /** Converts @a originalValue in units provided by file info to units currently set in max.*/
            float convertSpaceUnit(float originalValue);

            /** Performs the import of the mesh.
             *      @return True on success, false otherwise.*/
            bool importMesh();

            /** Performs the import of a mesh that contains only triangles.
             *      @return True on success, false otherwise.*/
            bool importTriangleMesh();

            /** Performs the import of the mesh.
             *      @return True on success, false otherwise.*/
            bool importPolygonMesh();


            /** Performs the import of the mesh positions of a mesh that contains only triangles.
             *      @return True on success, false otherwise.*/
            bool importTriangleMeshPositions(Mesh* triangleMesh);

            /** Performs the import of the mesh positions of a mesh that contains only triangles.
             *      @return True on success, false otherwise.*/
            bool importPolygonMeshPositions(Mesh* triangleMesh);
    };

}

#endif

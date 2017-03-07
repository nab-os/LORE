#include "GeometryImporter.h"

#include <iostream>
#include <vector>

#include <COLLADAFramework/COLLADAFWMesh.h>
#include <COLLADAFramework/COLLADAFWTriangles.h>
#include <COLLADAFramework/COLLADAFWTristrips.h>
#include <COLLADAFramework/COLLADAFWTrifans.h>

#include "Importer.h"
#include "ModelRender.h"

using namespace std;
using namespace glm;
using namespace LORE;

GeometryImporter::GeometryImporter(Importer* importer, const COLLADAFW::Geometry* geometry): mImporter(importer), mGeometry(geometry)
{



}


GeometryImporter::~GeometryImporter()
{



}


float GeometryImporter::convertSpaceUnit(float originalValue)
{

    return mImporter->convertSpaceUnit(originalValue);

}


bool GeometryImporter::import()
{
    if ( mGeometry->getType() == COLLADAFW::Geometry::GEO_TYPE_MESH  )
    {
        cout << "TODO: importing mesh" << endl;
        importMesh();

    }
    return true;

}


bool GeometryImporter::importMesh()
{

    COLLADAFW::Mesh* mesh = (COLLADAFW::Mesh*) mGeometry;

    bool success = true;
    mTotalTrianglesCount = mesh->getTrianglesTriangleCount() + mesh->getTristripsTriangleCount() + mesh->getTrifansTriangleCount();

    if ( mesh->getPolygonsPolygonCount() > 0 || mesh->getPolylistPolygonCount() > 0  )
    {
        cout << "polygon" << endl;
        //success = importPolygonMesh();

    }
    else if ( mTotalTrianglesCount > 0  )
    {
        cout << "triangle" << endl;
        success = importTriangleMesh();

    }

    if ( mHasVertexColor && success )
    {
        //addVertexColorObjects( mGeometry->getUniqueId()  );

    }


    return success;

}


bool GeometryImporter::importTriangleMesh(  )
{

    COLLADAFW::Mesh* mesh = (COLLADAFW::Mesh*) mGeometry;

    Mesh* triangleMesh = new Mesh();

    if ( !importTriangleMeshPositions(triangleMesh)  )
        return false;

    /*if ( !importTriangleMeshNormals(triangleObject)  )
      return false;

      if ( !importTriangleMeshUVCoords(triangleObject)  )
      return false;
      */
    //triangleMesh.InvalidateGeomCache();
    //triangleMesh.InvalidateTopologyCache();

    //handleObjectReferences(mesh, triangleObject);

    return true;

}


//------------------------------
bool GeometryImporter::importTriangleMeshPositions( Mesh* triangleMesh )
{
    COLLADAFW::Mesh* mesh = (COLLADAFW::Mesh*) mGeometry;

    const COLLADAFW::MeshVertexData& meshPositions = mesh->getPositions();

    int positionsCount = (int)meshPositions.getValuesCount() / 3;

    vector<vec3> positions(positionsCount);
    cout << "test : " << positionsCount << endl;
    if ( meshPositions.getType() == COLLADAFW::MeshVertexData::DATA_TYPE_DOUBLE )
    {
        const COLLADAFW::DoubleArray* positionsArray = meshPositions.getDoubleValues();
        for ( int i = 0; i < positionsCount; ++i)
        {
            positions[i] = vec3(
                    convertSpaceUnit((float)(*positionsArray)[3*i]),
                    convertSpaceUnit((float)(*positionsArray)[3*i + 1]),
                    convertSpaceUnit((float)(*positionsArray)[3*i + 2])
                    );
            cout << positions[i].x << " ; " << positions[i].y << " ; " << positions[i].z << endl;
        }
    }
    else
    {
        const COLLADAFW::FloatArray* positionsArray = meshPositions.getFloatValues();
        for ( int i = 0; i < positionsCount; ++i)
        {
            positions[i] = vec3(
                    convertSpaceUnit((*positionsArray)[3*i]),
                    convertSpaceUnit((*positionsArray)[3*i + 1]),
                    convertSpaceUnit((*positionsArray)[3*i + 2])
                    );
            cout << positions[i].x << " ; " << positions[i].y << " ; " << positions[i].z << endl;
        }
    }


    vector<vec3> finalPositions((int)mTotalTrianglesCount);
    COLLADAFW::MeshPrimitiveArray& meshPrimitiveArray =  mesh->getMeshPrimitives();
    size_t faceIndex = 0;
    for ( size_t i = 0, count = meshPrimitiveArray.getCount(); i < count; ++i)
    {

        const COLLADAFW::MeshPrimitive* meshPrimitive = meshPrimitiveArray[i];
        if ( ! meshPrimitive )
            continue;

        switch (meshPrimitive->getPrimitiveType())
        {

            case COLLADAFW::MeshPrimitive::TRIANGLES:
                {
                    const COLLADAFW::Triangles* triangles = (const COLLADAFW::Triangles*) meshPrimitive;
                    const COLLADAFW::UIntValuesArray& positionIndices =  triangles->getPositionIndices();
                    for ( size_t j = 0, count = positionIndices.getCount() ; j < count; j++ )
                    {
                        finalPositions[faceIndex+j] =  positions[positionIndices[j]];
                    }
                    ++faceIndex;
                    break;
                }
            case COLLADAFW::MeshPrimitive::TRIANGLE_STRIPS:
                {
                    const COLLADAFW::Tristrips* tristrips = (const COLLADAFW::Tristrips*) meshPrimitive;
                    const COLLADAFW::UIntValuesArray& positionIndices =  tristrips->getPositionIndices();
                    const COLLADAFW::UIntValuesArray& faceVertexCountArray = tristrips->getGroupedVerticesVertexCountArray();
                    /*size_t nextTristripStartIndex = 0;
                      for ( size_t k = 0, count = faceVertexCountArray.getCount(); k < count; ++k)
                      {
                      unsigned int faceVertexCount = faceVertexCountArray[k];
                      bool switchOrientation = false;
                      for ( size_t j = nextTristripStartIndex + 2, lastVertex = nextTristripStartIndex +  faceVertexCount; j < lastVertex; ++j )
                      {
                      Face& face = triangleMesh.faces[faceIndex];
                    //   						face.setMatID(fWMaterialIdMaxMtlIdMap[meshPrimitive->getMaterialId()]);
                    face.setEdgeVisFlags(1, 1, 1);
                    if ( maxMaterialId != 0 )
                    face.setMatID(maxMaterialId);
                    if ( switchOrientation )
                    {
                    face.setVerts(positionIndices[j - 1], positionIndices[j - 2], positionIndices[j]);
                    switchOrientation = false;
                    }
                    else
                    {
                    face.setVerts(positionIndices[j - 2], positionIndices[j - 1], positionIndices[j]);
                    switchOrientation = true;
                    }
                    ++faceIndex;
                    }
                    nextTristripStartIndex += faceVertexCount;
                    }*/
                    break;
                }
            case COLLADAFW::MeshPrimitive::TRIANGLE_FANS:
                {
                    const COLLADAFW::Trifans* trifans = (const COLLADAFW::Trifans*) meshPrimitive;
                    const COLLADAFW::UIntValuesArray& positionIndices =  trifans->getPositionIndices();
                    const COLLADAFW::UIntValuesArray& faceVertexCountArray = trifans->getGroupedVerticesVertexCountArray();
                    /*size_t nextTrifanStartIndex = 0;
                      for ( size_t k = 0, count = faceVertexCountArray.getCount(); k < count; ++k)
                      {
                      unsigned int faceVertexCount = faceVertexCountArray[k];
                      unsigned int commonVertexIndex = positionIndices[nextTrifanStartIndex];
                      for ( size_t j = nextTrifanStartIndex + 2, lastVertex = nextTrifanStartIndex +  faceVertexCount; j < lastVertex; ++j )
                      {
                      Face& face = triangleMesh.faces[faceIndex];
                    //   						face.setMatID(fWMaterialIdMaxMtlIdMap[meshPrimitive->getMaterialId()]);
                    if ( maxMaterialId != 0 )
                    face.setMatID(maxMaterialId);
                    face.setEdgeVisFlags(1, 1, 1);
                    face.setVerts(commonVertexIndex, positionIndices[j - 1], positionIndices[j]);
                    ++faceIndex;
                    }
                    nextTrifanStartIndex += faceVertexCount;
                    }*/
                    break;
                }
            default:
                continue;
        }


        for(int i=0; i< finalPositions.size(); i++)
        {

            cout << finalPositions[i].x << " ; " << finalPositions[i].y << " ; " << finalPositions[i].z << endl;

        }

    }

    triangleMesh->setVertices(finalPositions);

    return true;
}


bool GeometryImporter::importPolygonMesh(  )
{

    COLLADAFW::Mesh* mesh = (COLLADAFW::Mesh*) mGeometry;

    //PolyObject* polygonObject = CreateEditablePolyObject();
    //MNMesh& polygonMesh = polygonObject->GetMesh();


    //if ( !importPolygonMeshPositions(polygonObject)  )
        //return false;

    //if ( !importPolygonMeshNormals(polygonObject)  )
      //  return false;

    //if ( !importPolygonMeshUVCoords(polygonObject)  )
       // return false;


    //polygonMesh.InvalidateGeomCache();

    h//andleObjectReferences(mesh, polygonObject);

    return true;

}


bool GeometryImporter::importPolygonMeshPositions( PolyObject* polygonObject )
	{
		COLLADAFW::Mesh* mesh = (COLLADAFW::Mesh*) mGeometry;

		MNMesh& polgonMesh = polygonObject->GetMesh();

		const COLLADAFW::MeshVertexData& meshPositions = mesh->getPositions();

		int positionsCount = (int)meshPositions.getValuesCount() / 3;

		polgonMesh.setNumVerts(positionsCount);

		if ( meshPositions.getType() == COLLADAFW::MeshVertexData::DATA_TYPE_DOUBLE )
		{
			const COLLADAFW::DoubleArray* positionsArray = meshPositions.getDoubleValues();
			for ( int i = 0; i < positionsCount; ++i)
			{
				MNVert* vertex = polgonMesh.V(i);
				vertex->p = Point3( convertSpaceUnit((float)(*positionsArray)[3*i]), 
					                convertSpaceUnit((float)(*positionsArray)[3*i + 1]), 
									convertSpaceUnit((float)(*positionsArray)[3*i + 2]));
			}
		}
		else
		{
			const COLLADAFW::FloatArray* positionsArray = meshPositions.getFloatValues();
			for ( int i = 0; i < positionsCount; ++i)
			{
				MNVert* vertex = polgonMesh.V(i);
				vertex->p = Point3( convertSpaceUnit((*positionsArray)[3*i]),
					                convertSpaceUnit((*positionsArray)[3*i + 1]), 
									convertSpaceUnit((*positionsArray)[3*i + 2]));
			}
		}

		size_t polygonsCount = mTotalTrianglesCount + mesh->getPolygonsPolygonCount() + mesh->getPolylistPolygonCount();
		polgonMesh.setNumFaces((int)polygonsCount);
		COLLADAFW::MeshPrimitiveArray& meshPrimitiveArray =  mesh->getMeshPrimitives();
		size_t faceIndex = 0;
		for ( size_t i = 0, count = meshPrimitiveArray.getCount(); i < count; ++i)
		{
			const COLLADAFW::MeshPrimitive* meshPrimitive = meshPrimitiveArray[i];
			if ( ! meshPrimitive )
				continue;
			MtlID maxMaterialId = (MtlID)meshPrimitive->getMaterialId();
			switch ( meshPrimitive->getPrimitiveType() )
			{
			case COLLADAFW::MeshPrimitive::TRIANGLES:
				{
					const COLLADAFW::Triangles* triangles = (const COLLADAFW::Triangles*) meshPrimitive;
					const COLLADAFW::UIntValuesArray& positionIndices =  triangles->getPositionIndices();
					for ( size_t j = 0, count = positionIndices.getCount() ; j < count; j+=3 )
					{
						MNFace* face = polgonMesh.F((int)faceIndex);
						face->MakePoly(3, (int*) (&positionIndices[j]));
						if ( maxMaterialId != 0 )
							face->material = maxMaterialId;

						++faceIndex;
					}
					break;
				}
			case COLLADAFW::MeshPrimitive::TRIANGLE_STRIPS:
				{
					const COLLADAFW::Tristrips* tristrips = (const COLLADAFW::Tristrips*) meshPrimitive;
					const COLLADAFW::UIntValuesArray& positionIndices =  tristrips->getPositionIndices();
					const COLLADAFW::UIntValuesArray& faceVertexCountArray = tristrips->getGroupedVerticesVertexCountArray();
					size_t nextTristripStartIndex = 0;
					for ( size_t k = 0, count = faceVertexCountArray.getCount(); k < count; ++k)
					{
						unsigned int faceVertexCount = faceVertexCountArray[k];
						bool switchOrientation = false;
						for ( size_t j = nextTristripStartIndex + 2, lastVertex = nextTristripStartIndex +  faceVertexCount; j < lastVertex; ++j )
						{
							MNFace* face = polgonMesh.F((int)faceIndex);
							if ( switchOrientation )
							{
								int indices[3];
								indices[0] = (int)positionIndices[j - 1];
								indices[1] = (int)positionIndices[j - 2];
								indices[2] = (int)positionIndices[j ];
								face->MakePoly(3, indices);
								if ( maxMaterialId != 0 )
									face->material = maxMaterialId;
								switchOrientation = false;
							}
							else
							{
								face->MakePoly(3, (int*) (&positionIndices[j - 2]));
								if ( maxMaterialId != 0 )
									face->material = maxMaterialId;
								switchOrientation = true;
							}

							++faceIndex;
						}
						nextTristripStartIndex += faceVertexCount;
					}
					break;
				}
			case COLLADAFW::MeshPrimitive::TRIANGLE_FANS:
				{
					const COLLADAFW::Trifans* trifans = (const COLLADAFW::Trifans*) meshPrimitive;
					const COLLADAFW::UIntValuesArray& positionIndices =  trifans->getPositionIndices();
					const COLLADAFW::UIntValuesArray& faceVertexCountArray = trifans->getGroupedVerticesVertexCountArray();
					size_t nextTrifanStartIndex = 0;
					for ( size_t k = 0, count = faceVertexCountArray.getCount(); k < count; ++k)
					{
						unsigned int faceVertexCount = faceVertexCountArray[k];
						int trianglePositionsIndices[3];
						//the first vertex is the same for all fans
						trianglePositionsIndices[0] = (int)positionIndices[nextTrifanStartIndex];
						for ( size_t j = nextTrifanStartIndex + 2, lastVertex = nextTrifanStartIndex +  faceVertexCount; j < lastVertex; ++j )
						{
							trianglePositionsIndices[1] = (int)positionIndices[j - 1];
							trianglePositionsIndices[2] = (int)positionIndices[j];
							MNFace* face = polgonMesh.F((int)faceIndex);
							face->MakePoly(3, trianglePositionsIndices);
							if ( maxMaterialId != 0 )
								face->material = maxMaterialId;

							++faceIndex;
						}
						nextTrifanStartIndex += faceVertexCount;
					}
					break;
				}
			case COLLADAFW::MeshPrimitive::POLYGONS:
				{
					const COLLADAFW::Polygons* polygons = (const COLLADAFW::Polygons*) meshPrimitive;
					const COLLADAFW::UIntValuesArray& positionIndices =  polygons->getPositionIndices();
					const COLLADAFW::IntValuesArray& faceVertexCountArray = polygons->getGroupedVerticesVertexCountArray();
					size_t currentIndex = 0;
					for ( size_t j = 0, count = faceVertexCountArray.getCount() ; j < count; ++j )
					{
						int faceVertexCount = faceVertexCountArray[j];
						// TODO for now, we ignore holes in polygons
						if ( faceVertexCount <= 0 )
							continue;
						MNFace* face = polgonMesh.F((int)faceIndex);
						face->MakePoly(faceVertexCount, (int*) (&positionIndices[currentIndex]));
						if ( maxMaterialId != 0 )
							face->material = maxMaterialId;
						currentIndex += faceVertexCount;
						++faceIndex;
					}
					break;
				}
			case COLLADAFW::MeshPrimitive::POLYLIST:
				{
					const COLLADAFW::Polylist* polylist = (const COLLADAFW::Polylist*) meshPrimitive;
					const COLLADAFW::UIntValuesArray& positionIndices =  polylist->getPositionIndices();
					const COLLADAFW::IntValuesArray& faceVertexCountArray = polylist->getGroupedVerticesVertexCountArray();
					size_t currentIndex = 0;
					for ( size_t j = 0, count = faceVertexCountArray.getCount() ; j < count; ++j )
					{
						int faceVertexCount = faceVertexCountArray[j];
						// polylist does not support holes!
						if ( faceVertexCount <= 0 )
							continue;
						MNFace* face = polgonMesh.F((int)faceIndex);
						face->MakePoly(faceVertexCount, (int*) (&positionIndices[currentIndex]));
						if ( maxMaterialId != 0 )
							face->material = maxMaterialId;
						currentIndex += faceVertexCount;
						++faceIndex;
					}
					break;
				}
			}

		}
		return true;
}

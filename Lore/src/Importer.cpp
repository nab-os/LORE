#include "Importer.h"

#include <iostream>

#include <COLLADABaseUtils/COLLADABUPlatform.h>
#include <COLLADASaxFrameworkLoader/COLLADASaxFWLLoader.h>
#include <COLLADAFramework/COLLADAFWRoot.h>

#include "ImportErrorHandler.h"

using namespace std;
using namespace LORE;

Importer::Importer(string colladaFile): m__filePath(colladaFile)
{



}

Importer::~Importer()
{



}

bool Importer::import()
{

    cout << "[Importer]: import()" << endl;

    ImportErrorHandler errorHandler;
    COLLADASaxFWL::Loader loader(&errorHandler);
    COLLADAFW::Root root(&loader, this);

    if ( !root.loadDocument(m__filePath))
        return false;

}


bool Importer::writeGlobalAsset( const COLLADAFW::FileInfo* asset )
{
    cout << "GlobalAsset" << endl;
    /*
    mFileInfo.absoluteFileUri = asset->getAbsoluteFileUri();

    const COLLADAFW::FileInfo::ValuePairPointerArray& valuePairs = asset->getValuePairArray();

    for ( size_t i = 0, count = valuePairs.getCount(); i < count; ++i)
    {
        const COLLADAFW::FileInfo::ValuePair* valuePair = valuePairs[i];
        const String& key = valuePair->first;
        const String& value = valuePair->second;
        if ( key == AUTORING_TOOL )
        {
            int googleSketchUpResult6 = value.compare(0, sizeof(GOOGLE_SKETCHUP6)-1, GOOGLE_SKETCHUP6);
            int googleSketchUpResult70 = value.compare(0, sizeof(GOOGLE_SKETCHUP70)-1, GOOGLE_SKETCHUP70);
            int microstationResult = value.compare(0, sizeof(MICROSTATION)-1, MICROSTATION);
            if ( (googleSketchUpResult6 == 0) || (microstationResult == 0) || (googleSketchUpResult70 == 0))
            {
                mInvertTransparency = true;
            }
        }
    }

    float systemUnitScale = 1.0f;

    // Retrieve the system unit information
    int systemUnitType = UNITS_CENTIMETERS;
    GetMasterUnitInfo(&systemUnitType, &systemUnitScale);

    switch (systemUnitType)
    {
        case UNITS_INCHES:
            systemUnitScale *= 0.0254f;
            break;
        case UNITS_FEET:
            systemUnitScale *= 0.3048f;
            break;
        case UNITS_MILES:
            systemUnitScale *= 1609.344f;
            break;
        case UNITS_MILLIMETERS:
            systemUnitScale *= 0.001f;
            break;
        case UNITS_CENTIMETERS:
            systemUnitScale *= 0.01f;
            break;
        case UNITS_METERS:
            break;
        case UNITS_KILOMETERS:
            systemUnitScale *= 1000.0f;
            break;
        default: break;
    }
    mFileInfo.unitScale = (float)asset->getUnit().getLinearUnitMeter() / systemUnitScale;
    delete mUnitConversionFunctors.lengthConversion;
    mUnitConversionFunctors.lengthConversion = new ScaleConversionFunctor(mFileInfo.unitScale);
    if ( mFileInfo.unitScale != 0)
    {
        mUnitConversionFunctors.inverseLengthConversion = new ScaleConversionFunctor(1/mFileInfo.unitScale);
    }

    COLLADAFW::FileInfo::Unit::AngularUnit angularUnit = asset->getUnit().getAngularUnit();
    if ( angularUnit == COLLADAFW::FileInfo::Unit::DEGREES )
    {
        delete mUnitConversionFunctors.angleConversion;
        mUnitConversionFunctors.angleConversion = ConversionFunctors::degToRad.clone();
    }

    mFileInfo.upAxis = asset->getUpAxisType();
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeVisualScene( const COLLADAFW::VisualScene* visualScene )
{
    cout << "Geometry" << endl;
    /*
    if ( mCurrentParsingPass != GENERAL_PASS )
        return true;

    VisualSceneImporter visualSceneImporter(this, visualScene);
    return visualSceneImporter.import();
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeLibraryNodes( const COLLADAFW::LibraryNodes* libraryNodes )
{

    cout << "LibNodes" << endl;
    /*
    if ( mCurrentParsingPass != GENERAL_PASS )
        return true;

    LibraryNodesImporter libraryNodesImporter(this, libraryNodes);
    bool success = libraryNodesImporter.import();
    return success;
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeGeometry( const COLLADAFW::Geometry* geometry )
{

    cout << "Geometry" << endl;

    /*
    if ( mCurrentParsingPass != GENERAL_PASS )
        return true;

    GeometryImporter geometryImporter(this, geometry);
    return geometryImporter.import();
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeMaterial( const COLLADAFW::Material* material )
{

    cout << "Material" << endl;

    /*
    if ( mCurrentParsingPass != GENERAL_PASS )
        return true;

    MaterialImporter materialImporter(this, material);
    return materialImporter.import();
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeEffect( const COLLADAFW::Effect* effect )
{

    cout << "Effect" << endl;
    /*
    if ( mCurrentParsingPass != GENERAL_PASS )
        return true;

    EffectImporter effectImporter(this, effect);
    return effectImporter.import();
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeCamera( const COLLADAFW::Camera* camera )
{

    cout << "Camera" << endl;
    /*
    if ( mCurrentParsingPass != GENERAL_PASS )
        return true;

    CameraImporter cameraImporter(this, camera);
    return cameraImporter.import();
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeImage( const COLLADAFW::Image* image )
{

    cout << "Image" << endl;
    /*
    if ( mCurrentParsingPass != GENERAL_PASS )
        return true;

    ImageImporter imageImporter(this, image);
    return imageImporter.import();
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeLight( const COLLADAFW::Light* light )
{

    cout << "Light" << endl;
    /*
    if ( mCurrentParsingPass != GENERAL_PASS )
        return true;

    LightImporter lightImporter(this, light);
    return lightImporter.import();
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeAnimation( const COLLADAFW::Animation* animation )
{

    cout << "Animation" << endl;
    /*
    if ( mCurrentParsingPass != GENERAL_PASS )
        return true;

    AnimationImporter animationImporter(this, animation);
    return animationImporter.import();
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeAnimationList( const COLLADAFW::AnimationList* animationList )
{

    cout << "AnimationList" << endl;
    /*
    if ( mCurrentParsingPass != GENERAL_PASS )
        return true;

    AnimationListImporter animationListImporter(this, animationList);
    return animationListImporter.import();
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeController( const COLLADAFW::Controller* controller )
{

    cout << "Controller" << endl;
    /*
    if ( mCurrentParsingPass != GENERAL_PASS )
        return true;

    ControllerImporter controllerImporter(this, controller);
    return controllerImporter.import();
*/
    return true;
}

//---------------------------------------------------------------
bool Importer::writeSkinControllerData( const COLLADAFW::SkinControllerData* skinControllerData )
{

    cout << "SkinControllerData" << endl;
    /*
    if ( mCurrentParsingPass != CONTROLLER_DATA_PASS )
        return true;

    SkinControllerDataImporter skinControllerDataImporter(this, skinControllerData);
    return skinControllerDataImporter.import();
*/
    return true;
}

bool Importer::writeScene( const COLLADAFW::Scene* scene  )
{

    cout << "Scene" << endl;
/*    if( scene == 0  )
        return true;

    const COLLADAFW::InstanceVisualScene* instanceVisualScene = scene->getInstanceVisualScene();
    COLLADAFW::UniqueId id = instanceVisualScene->getInstanciatedObjectId();
    if(id.getFileId() == 0)
        mVisualSceneUniqueId = id;
   */ return true;

}

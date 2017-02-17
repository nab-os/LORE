#ifndef IMPORTER_H
#define IMPORTER_H

#include <string>

#include <COLLADAFramework/COLLADAFWIWriter.h>
#include <COLLADASaxFrameworkLoader/COLLADASaxFWLIError.h>
#include <COLLADAFramework/COLLADAFWTypes.h>

#include <COLLADAFramework/COLLADAFWMaterial.h>
#include <COLLADAFramework/COLLADAFWEffect.h>
#include <COLLADAFramework/COLLADAFWColor.h>
#include <COLLADAFramework/COLLADAFWImage.h>
#include <COLLADAFramework/COLLADAFWInstanceGeometry.h>
#include <COLLADAFramework/COLLADAFWController.h>
#include <COLLADAFramework/COLLADAFWMorphController.h>
#include <COLLADAFramework/COLLADAFWSkinController.h>
#include <COLLADAFramework/COLLADAFWFileInfo.h>

#include "Library.h"
#include "GeometryImporter.h"

namespace LORE
{

    class Importer: public COLLADAFW::IWriter
    {

        public:

            Importer(string colladaFile);
            ~Importer();

            bool import();

            /** Deletes the entire scene.
             *      @param errorMessage A message containing informations about the error that occurred.
             *              */
            void cancel(const string& errorMessage){};

            /** Prepare to receive data.*/
            void start(){};

            /** Remove all objects that don't have an object. Deletes unused visual scenes.*/
            void finish(){};

            virtual bool writeGlobalAsset ( const COLLADAFW::FileInfo* asset  );;

            virtual bool writeScene ( const COLLADAFW::Scene* scene  );

            virtual bool writeVisualScene ( const COLLADAFW::VisualScene* visualScene  );

            virtual bool writeLibraryNodes( const COLLADAFW::LibraryNodes* libraryNodes  );

            virtual bool writeGeometry ( const COLLADAFW::Geometry* geometry  );

            virtual bool writeMaterial( const COLLADAFW::Material* material  );

            virtual bool writeEffect( const COLLADAFW::Effect* effect  );

            virtual bool writeCamera( const COLLADAFW::Camera* camera  );

            virtual bool writeImage( const COLLADAFW::Image* image  );

            virtual bool writeLight( const COLLADAFW::Light* light  );

            virtual bool writeAnimation( const COLLADAFW::Animation* animation  );

            virtual bool writeAnimationList( const COLLADAFW::AnimationList* animationList  );

            virtual bool writeSkinControllerData( const COLLADAFW::SkinControllerData* skinControllerData  );

            virtual bool writeController( const COLLADAFW::Controller* Controller  );

            virtual bool writeFormulas( const COLLADAFW::Formulas* formulas  ) { return true;  }

            virtual bool writeKinematicsScene( const COLLADAFW::KinematicsScene* kinematicsScene  ) { return true;  }


        private:

            string m__filePath;

    };

}

#endif

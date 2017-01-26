#ifndef IMPORTER_H
#define IMPORTER_H

#include <string>

//#include <COLLADAFramework/COLLADAFWIWriter.h>
//#include <COLLADASaxFrameworkLoader/COLLADASaxFWLIError.h>

#include "Library.h"
//#include "GeometryImporter.h"

namespace LORE
{

    class Importer//: public COLLADAFW::IWriter
    {

        public:

            Importer(string colladaFile);
            ~Importer();

            bool import();

        private:

            string m__filePath;

            bool importGeometry();

    };

}

#endif

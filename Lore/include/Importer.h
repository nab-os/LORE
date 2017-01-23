#pragma once

#include <string>

#include <COLLADAFramework/COLLADAFWIWriter.h>
#include <COLLADASaxFrameworkLoader/COLLADASaxFWLIError.h>

#include "Library.h"
#include "GeometryImporter.h"

class Importer: public COLLADAFW::IWriter
{

	public:

        Importer(string colladaFile);
        ~Importer();

        bool import();

	private:

        string m__filePath;

        bool importGeometry();

};

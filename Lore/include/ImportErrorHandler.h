#ifndef IMPORTERERRORHANDLER_H
#define IMPORTERERRORHANDLER_H

#include <COLLADASaxFrameworkLoader/COLLADASaxFWLIErrorHandler.h>

namespace LORE
{

    class ImportErrorHandler: public COLLADASaxFWL::IErrorHandler
    {

        private:
            bool mHasCriticalError;

        public:

            /** Constructor. */
            ImportErrorHandler();

            /** Destructor. */
            virtual ~ImportErrorHandler();

            /** If this method returns true, the loader stops parsing immediately. If
             * severity is nor CRITICAL
             *      and this method returns true, the loader continues loading.*/
            bool virtual handleError(const COLLADASaxFWL::IError* error);

            bool hasCriticalError();

        private:

            /** Disable default copy ctor. */
            ImportErrorHandler( const ImportErrorHandler& pre  );

            /** Disable default assignment operator. */
            const ImportErrorHandler& operator= ( const ImportErrorHandler& pre  );


    };

}

#endif

#include "ImportErrorHandler.h"

ImportErrorHandler::ImportErrorHandler()
    : mHasCriticalError( false  )
{

}


ImportErrorHandler::~ImportErrorHandler()
{

}


bool ImportErrorHandler::handleError( const COLLADASaxFWL::IError* error  )
{
    /*std::string msg;
    COLLADASaxFWL::IError::Severity severity = error->getSeverity();
    switch ( error->getErrorClass() )
    {
        case COLLADASaxFWL::IError::ERROR_SAXPARSER:
            msg = ((COLLADASaxFWL::SaxParserError*)error)->getError().getErrorMessage();
            break;
        case COLLADASaxFWL::IError::ERROR_SAXFWL:
            msg = ((COLLADASaxFWL::SaxFWLError*)error)->getFullErrorMessage();
            break;

    }
    msg;

    bool criticalError = (severity == COLLADASaxFWL::IError::SEVERITY_CRITICAL);
    if( criticalError  )
        mHasCriticalError = true;

    return criticalError ? true : false;
*/

    return false;
}


bool ImportErrorHandler::hasCriticalError()
{
    return mHasCriticalError;

}

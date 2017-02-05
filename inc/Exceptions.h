////////////////////////////////////////////////////
//  File    : Exceptions.h
//  Project : Gang's Keyboard Framework
//
//  Created by Jacques Tronconi on 30/01/2017.
//    Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
////////////////////////////////////////////////////

#ifndef Gang_s_Keyboard_Framework_Exceptions_h
#define Gang_s_Keyboard_Framework_Exceptions_h

#include "Base.h"

#   ifdef GkfThrowExceptions

#include <stdexcept>
#include <exception>
#include <string>

/// @brief Defines a basic Exception.
class GkfException : public std::exception
{
public:
    
    /// @brief Builds the exception with given error.
    GkfException ( int error , const std::string& msg ) ;
    virtual ~GkfException ();
    
    /// @brief Returns a description of the message with the file name and line number.
    virtual const char * what () const noexcept ;
    
    /// @brief Returns the error number.
    int error () const noexcept ;
    
protected:
    
    /// @brief Error number.
    int iError ;
    
    /// @brief Error Message.
    std::string iMessage ;
};

/// @brief Prints every exceptions thorwed with std::throw_with_nested. The 'level' parameter specify the deep of the
/// exception launched.
void GkfPrintExceptions ( const std::exception& e , int level = 0 ) ;

/// @brief Uses this macro to send an exception. The file name and the line number are added
/// automatically. You can use GkfPrintExceptions to print every exceptions message, using the std nested
/// exceptions system.
#define GkfThrow(err, msg) std::throw_with_nested( GkfException(err, std::string("[") + __FILE__ + ":" + std::to_string(__LINE__) + "]" + msg ) )

#   else // GkfThrowExceptions

#define GkfThrow(err, msg) std::cerr << std::string("[") + __FILE__ + ":" + __LINE__ + "]" + msg << std::endl ;

#   endif // GkfThrowExceptions

#endif

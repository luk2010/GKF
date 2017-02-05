////////////////////////////////////////////////////
//  File    : Exceptions.cpp
//  Project : Gang's Keyboard Framework
//
//  Created by Jacques Tronconi on 30/01/2017.
//    Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
////////////////////////////////////////////////////

#include "Exceptions.h"
#include <iostream>

#ifdef GkfThrowExceptions

GkfException::GkfException ( int error , const std::string & message )
: iError(error) , iMessage(message)
{
    
}

GkfException::~GkfException()
{
    
}

const char* GkfException::what() const noexcept
{
    return iMessage.c_str() ;
}

int GkfException::error() const noexcept
{
    return iError ;
}

void GkfPrintExceptions ( const std::exception& e , int level )
{
    // Code from http://en.cppreference.com/w/cpp/error/nested_exception
    
    std::cerr << "[" << level << "] " << e.what() << std::endl ;
    
    try {
        std::rethrow_if_nested(e);
    } catch ( const std::exception& e ) {
        GkfPrintExceptions(e, level+1);
    } catch (...) { }
}

#endif // GkfThrowExceptions

////////////////////////////////////////////////////
//  File    : Translation.h
//  Project : Gang's Keyboard Framework
//
//  Created by Jacques Tronconi on 30/01/2017.
//    Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
////////////////////////////////////////////////////

#ifndef Gang_s_Keyboard_Framework_Translation_h
#define Gang_s_Keyboard_Framework_Translation_h

#include "Base.h"

GkfBegin

/// @brief Defines a new Translation.
///
/// A Translation can be loaded from a file, or created by the user and then inserted into
/// a LocaleFile for writing purpose, by example.
///
/// It is composed of a KEY , which identify the Translation , a VALUE , which is the translation , and
/// a DEFINITION which is what the translation is meant to translate (contextually). The DEFINITION is
/// optional but alone in a file, it can create a new translation key.
///
/// The VALUE property is a string that has up to 10 parameters, identified by a '%' and the number of the
/// parameter. You can set arbitrary numbers from 0 to 9. To write a '%', you can write '%%' instead.
class Translation
{
public:
    
    Translation () ;
    
    Translation ( const std::string & name , const std::string & value , const std::string & definition = std::string() ) ;
    
    /// @brief Set given parameter.
    void setParameter ( int i , const std::string & value ) const ;
    
    /// @brief Uses the parameter to give the complete sentence.
    std::string translate () const ;
    
    /// @brief Returns the Definition.
    const std::string & getDefinition () const ;
    
    /// @brief Set the Definition for this Translation.
    void setDefinition ( const std::string & definition ) ;
    
    /// @brief Returns the Value.
    const std::string & getValue () const ;
    
    /// @brief Changes the Value.
    void setValue ( const std::string & value ) ;
    
    /// @brief Returns the Key.
    const std::string & getKey () const ;
    
    /// @brief Changes the Key. This Key should not be changed when this translation
    /// has been loaded from a LocaleFile, because the LocaleFile will not update its
    /// map and the Key will be unchanged from its point of view. To change the Key in
    /// a LocaleFile, use 'LocaleFile::setKey()' .
    void setKey ( const std::string & key ) ;
    
protected:
    
    /// @brief Name and value.
    std::string iName ; std::string iValue ;
    
    /// @brief Definition of this Translation. This can be understood as a commentary let to know what
    /// this translation refers to.
    std::string iDefinition ;
    
    /// @brief Parameters map. As those parameters do not change the basics of the Translation,
    /// they can be changed even in constant mode.
    mutable std::map < int , std::string > iParameters ;
};

GkfEnd

#endif

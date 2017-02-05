////////////////////////////////////////////////////
//  File    : Locales.cpp
//  Project : GFK
//
//  Created by Jacques Tronconi on 01/02/2017.
//  
//
////////////////////////////////////////////////////

#include "Locales.h"
#include "LocaleFile.h"

GkfBegin

Locale::Locale ( const std::string & lang )
{
    iLanguage = "" ;
}

Locale::~Locale()
{
    
}

std::string Locale::getIdentifier() const
{
    return std::string() ;
}

std::string Locale::getCountryCode() const
{
    return std::string () ;
}

std::string Locale::getCountryName() const
{
    return std::string () ;
}

std::string Locale::getLangCode() const
{
    return std::string () ;
}

std::string Locale::getLangName() const
{
    return std::string () ;
}

std::string Locale::getUsername() const
{
    return std::string () ;
}

const Translation* Locale::findTranslation(const std::string &name, const std::vector<LocaleFile *> &files) const
{
    for ( auto & f : files )
    {
        if ( f ) {
            
            if ( f->getLanguageCode() == getLangCode() ) {
                
                const Translation* t = f->getTranslation(name) ;
                if ( t ) return t ;
            }
        }
    }
    
    for ( auto & f : files )
    {
        if ( f ) {
            
            if ( f->getLanguageName() == getLangName() ) {
                
                const Translation* t = f->getTranslation(name) ;
                if ( t ) return t ;
            }
        }
    }
    
    return nullptr ;
}

GkfEnd

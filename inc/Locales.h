////////////////////////////////////////////////////
//  File    : Locales.h
//  Project : Gang's Keyboard Framework
//
//  Created by Jacques Tronconi on 30/01/2017.
//    Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
////////////////////////////////////////////////////

#ifndef Gang_s_Keyboard_Framework_Locales_h
#define Gang_s_Keyboard_Framework_Locales_h

#include "Base.h"
#include "Translation.h"

GkfBegin

class LocaleFile ;

/// @brief Defines an object that holds localized informations. Use Gkf::GetCurrentLocale() to get a
/// copy of the current used Locale object.
class Locale
{
public:
    
    /// @brief Initializes the Locale object with current language specification. Those languages are
    /// defined using the syntax provided here :
    /// https://developer.apple.com/library/content/documentation/MacOSX/Conceptual/BPInternational/LanguageandLocaleIDs/LanguageandLocaleIDs.html
    Locale ( const std::string& lang ) ;
    
    virtual ~Locale () ;
    
    /// @brief Returns the language identifier for this Locale.
    virtual std::string getIdentifier () const ;
    
    /// @brief Returns the Country Code for this locale.
    virtual std::string getCountryCode () const ;
    
    /// @brief Returns the Country Name for this locale.
    virtual std::string getCountryName () const ;
    
    /// @brief Returns the Language Code for this locale.
    virtual std::string getLangCode () const ;
    
    /// @brief Returns the Language Name for this locale.
    virtual std::string getLangName () const ;
    
    /// @brief Returns the user's current name.
    virtual std::string getUsername () const ;
    
    /// @brief Find a suitable translation from given set of LocalFiles.
    const Translation* findTranslation ( const std::string & name , const std::vector < LocaleFile* > & files ) const ;
    
protected:
    
    /// @brief Remember the given language.
    std::string iLanguage ;
};

/// @brief Returns a new Locale object, used by the current user as default locale. The user is responsible
/// for the deletion of this object.
Locale* GetCurrentLocale () ;

/// @brief Returns the Locale from given language identifier. The implementation of this
/// function is platform dependent.
Locale* GetLocale ( const std::string & loc ) ;

GkfEnd

#endif

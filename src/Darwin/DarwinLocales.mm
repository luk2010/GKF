////////////////////////////////////////////////////
//  File    : Locales.cpp
//  Project : Gang's Keyboard Framework
//
//  Created by Jacques Tronconi on 30/01/2017.
//    Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
////////////////////////////////////////////////////

#include "Locales.h"

#include <pwd.h>
#include <unistd.h>

#include <CoreFoundation/CoreFoundation.h>

#define GKF_ECFLOCALE 1001
#define GKF_ECFLOCALEINVALID 1002

std::string GkfCFStringGetString ( CFStringRef str )
{
    std::string ret = "" ;
    
    CFIndex length = CFStringGetLength(str);
    CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8) + 1;
    
    if ( length == 0 )
        return ret ;
    
    char *buffer = (char *) malloc(maxSize);
    if (CFStringGetCString(str, buffer, maxSize, kCFStringEncodingUTF8)) {
        ret = std::string (buffer) ;
    }
    
    free(buffer);
    return ret ;
}

class GkfLocaleDarwin : public GKF::Locale
{
public:
    
    GkfLocaleDarwin ( CFLocaleRef locale )
    : GKF::Locale("")
    {
        // Code from http://stackoverflow.com/questions/9166291/converting-a-cfstringref-to-char
        
        CFStringRef localeid = CFLocaleGetIdentifier(locale) ;
        
        if ( !localeid ) {
            GkfThrow(GKF_ECFLOCALEINVALID, "Can't get an identifier from given CFLocale.");
        }
        
        iLanguage = GkfCFStringGetString(localeid) ;
        iLocale = locale ;
        
        init ( locale ) ;
    }
    
    GkfLocaleDarwin ( const std::string & lang )
    : GKF::Locale(lang)
    {
        iLocale = CFLocaleCreate(NULL, CFStringCreateWithCString(NULL, lang.c_str(), kCFStringEncodingUTF8) ) ;
        
        if ( !iLocale ) {
            GkfThrow(GKF_ECFLOCALE, "Can't create CFLocale Object.");
        }
        
        init ( iLocale ) ;
    }
    
    virtual ~GkfLocaleDarwin ()
    {
        if ( iLocale ) {
            CFRelease((CFLocaleRef) iLocale);
        }
    }
    
private:
    
    void init ( CFLocaleRef locale )
    {
        CFStringRef counCode, counName ;
        counCode = (CFStringRef) CFLocaleGetValue(locale, kCFLocaleCountryCode) ;
        counName = (CFStringRef) CFLocaleCopyDisplayNameForPropertyValue(locale, kCFLocaleCountryCode, counCode) ;
        
        CFStringRef langCode, langName ; CFArrayRef langs ;
        langs = CFLocaleCopyPreferredLanguages() ;
        langCode = (CFStringRef) CFArrayGetValueAtIndex(langs, 0) ;
        langName = (CFStringRef) CFLocaleCopyDisplayNameForPropertyValue(locale, kCFLocaleLanguageCode, langCode) ;
        
        iCountryCode = GkfCFStringGetString( counCode ) ;
        iCountryName = GkfCFStringGetString( counName ) ;
        iLangCode = GkfCFStringGetString( langCode ) ;
        iLangName = GkfCFStringGetString( langName ) ;
        
        struct passwd * u = getpwuid(getuid());
        iUsername = std::string ( u->pw_name ) ;
    }
    
public:
    
    virtual std::string getIdentifier () const
    {
        if ( iLocale ) {
            return GkfCFStringGetString(CFLocaleGetIdentifier(iLocale));
        } else {
            return Locale::getIdentifier() ;
        }
    }
    
    virtual std::string getCountryCode () const
    {
        return iCountryCode ;
    }
    
    virtual std::string getCountryName () const
    {
        return iCountryName;
    }
    virtual std::string getLangCode () const
    {
        return iLangCode ;
    }
    virtual std::string getLangName () const
    {
        return iLangName ;
    }
    
    virtual std::string getUsername () const
    {
        return iUsername ;
    }
    
protected:
    
    /// @brief The CFLocale object.
    CFLocaleRef iLocale ;
    
    /// @brief Country Code and Name.
    std::string iCountryCode ; std::string iCountryName ;
    
    /// @brief Language Code and Name.
    std::string iLangCode ; std::string iLangName ;
    
    /// @brief User name.
    std::string iUsername ;
};

GkfBegin

Locale* GetCurrentLocale ()
{
    return new GkfLocaleDarwin ( CFLocaleCopyCurrent() ) ;
}

Locale* GetLocale ( const std::string & loc )
{
    return new GkfLocaleDarwin ( loc ) ;
}

GkfEnd

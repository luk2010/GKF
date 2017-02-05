////////////////////////////////////////////////////
//  File    : Base.h
//  Project : Gang's Keyboard Framework
//
//  Created by Jacques Tronconi on 30/01/2017.
//    Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
////////////////////////////////////////////////////

#ifndef Gang_s_Keyboard_Framework_Base_h
#define Gang_s_Keyboard_Framework_Base_h

/// The Gang's Keyboard Framework is a library that tends to unify multiplatform
/// and multilanguages keyboards support.

/// Here is an example of how this library should be used :

/*
 
 GKF::Locale* locale = GKF::GetCurrentLocale () ;
 if ( !locale ) exit(-1) ;
 
 std::cout << locale -> getIdentifier() << std::endl;
 std::cout << locale -> getCountryCode () << ":" << locale -> getCountryName () << std::endl;
 std::cout << locale -> getLangCode () << ":" << locale -> getLangName () << std::endl;
 
 GKF::LocaleFileManager fmanager ;
 fmanager.load ( "gkf-samples/english.gkf" ) ;
 fmanager.load ( "gkf-samples/french.gkf" ) ;
 
 std::cout << "Getting correct sentence from current localization." << std::endl;
 
 auto translation = fmanager -> findTranslation ( "EX_HELLOWORLD" , locale ) ;
 if ( !translation ) exit(-1) ;
 
 translation -> setParameter ( 0 , locale -> getUsername () ) ;
 
 std::cout << translation -> translate () << std::endl ;
 delete locale ;
 
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>

/// @brief Defines if you want this library to send exceptions.
#define GkfThrowExceptions 
#include "Exceptions.h"

/// @brief Defines beginning of the GKF namespace.
#define GkfBegin namespace GKF {

/// @brief Defines ending of the GKF namespace.
#define GkfEnd }

/// Platforms definitions

#if defined(__APPLE__) && defined(__MACH__)
#   define GkfPlatformDarwin
#endif

/// Errors definitions

#define GKF_EOPENFILE 1
#define GKF_EGETLINE  2

#endif

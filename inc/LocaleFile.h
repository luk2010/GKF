////////////////////////////////////////////////////
//  File    : LocaleFile.h
//  Project : Gang's Keyboard Framework
//
//  Created by Jacques Tronconi on 30/01/2017.
//    Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
////////////////////////////////////////////////////

#ifndef Gang_s_Keyboard_Framework_LocaleFile_h
#define Gang_s_Keyboard_Framework_LocaleFile_h

#include "Base.h"
#include "Translation.h"

GkfBegin

class Locale ;

/// @brief Describes a basic GKF Local File format. This file can be loaded using 'LoadLocalFile()', and is
/// associated with a 'GKF::Locale' object.
class LocaleFile
{
public:
    
    /// @brief Initializes the LocaleFile from given file.
    LocaleFile ( const std::string & filepath ) ;
    
    virtual ~LocaleFile () ;
    
    /// @brief Returns the translation with given name, or null.
    const Translation* getTranslation ( const std::string & name ) const ;
    
    /// @brief Returns the translation with given key, or null.
    Translation* getTranslation ( const std::string & key ) ;
    
    /// @brief Returns an array with every Translation.
    std::vector< const Translation* > getTranslations () const ;
    
    /// @brief Returns the 'l' value.
    const std::string & getLanguageCode () const ;
    
    /// @brief Returns the 'lang' value.
    const std::string & getLanguageName () const ;
    
    /// @brief Changes the key for given translation.
    ///
    /// This function erase the translation at original KEY and creates a new
    /// entree with the new KEY. Also, it returns the Translation object with
    /// the new KEY.
    ///
    /// @note If the new key already exists, this function overwrites it.
    Translation * setKey ( const std::string& key , Translation* trans ) ;
    
    /// @brief Adds a new Translation to this LocaleFile.
    /// The added translation is copied, so the given one can be deleted promptly after
    /// calling this function. This is done in order to keep new/delete into the same library.
    void addTranslation ( const Translation & trans ) ;
    
    /// @brief Write this LocaleFile to given filepath.
    void write ( const std::string & filepath ) const ;
    
    /// @brief Read the given file.
    /// If this LocaleFile was already loaded, it will reset it load the given file.
    void read ( const std::string & filepath ) ;
    
    /// @brief Resets the LocaleFile and makes it empty.
    void reset () ;
    
    /// @brief Returns the original filepath.
    const std::string & getFilepath () const ;
    
    /// @brief Changes the filepath this LocaleFile is owned.
    void setFilepath ( const std::string & path ) ;
    
protected:
    
    /// @brief Loads the file.
    virtual void init () ;
    
protected:
    
    /// @brief File where comes this locale.
    std::string iFilepath ;
    
    /// @brief Comments ('?').
    std::string iComments ;
    
    /// @brief Locale statement ('l').
    std::string iLocale ;
    
    /// @brief Language statement ('lang').
    std::string iLanguage ;
    
    /// @brief Translation's map.
    std::map < std::string , Translation* > iTranslations ;
};

LocaleFile* LoadLocalFile ( const std::string & filepath ) ;

/// @brief Groups every loaded local file.
class LocaleFileManager
{
public:
    
    LocaleFileManager () ;
    
    /// @brief Loads a LocaleFile from given filepath.
    /// Returns the loaded one if it has already been done.
    LocaleFile* load ( const std::string & filepath ) ;
    
    /// @brief Returns the LocalFile if it has been loaded.
    const LocaleFile * get ( const std::string & filepath ) const ;
    
    /// @brief Clears the LocaleFileManager.
    void reset () ;
    
    /// @brief Finds a translation file that suits the given Locale.
    /// If none, returns null.
    const Translation* findTranslation ( const std::string & key , const Locale * loc ) const ;
    
protected:
    
    /// @brief Holds the LocalFile .
    std::vector < LocaleFile* > iLocaleFiles ;
};

GkfEnd

#endif

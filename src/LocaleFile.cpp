////////////////////////////////////////////////////
//  File    : LocaleFile.cpp
//  Project : Gang's Keyboard Framework
//
//  Created by Jacques Tronconi on 30/01/2017.
//    Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
////////////////////////////////////////////////////

#include "Locales.h"
#include "LocaleFile.h"

GkfBegin

LocaleFile::LocaleFile ( const std::string& filepath )
: iFilepath(filepath)
{
    if ( !filepath.empty() ) {
        init() ;
    }
}

LocaleFile::~LocaleFile()
{
    reset() ;
}

const Translation * LocaleFile::getTranslation(const std::string &name) const
{
    if ( iTranslations.find(name) == iTranslations.end() ) {
        return nullptr ;
    } else {
        return iTranslations.at(name) ;
    }
}

Translation* LocaleFile::getTranslation(const std::string &key)
{
    if ( iTranslations.find(key) == iTranslations.end() ) {
        return nullptr ;
    } else {
        return iTranslations.at(key) ;
    }
}

std::vector< const Translation* > LocaleFile::getTranslations() const
{
    std::vector < const Translation* > ret ;
    
    for ( auto it : iTranslations ) {
        if ( it.second ) ret.push_back(it.second);
    }
    
    return ret ;
}

const std::string & LocaleFile::getLanguageCode() const
{
    return iLocale ;
}

const std::string & LocaleFile::getLanguageName() const
{
    return iLanguage ;
}

void LocaleFile::init()
{
    if ( !iFilepath.empty() )
    {
        std::ifstream f ( iFilepath , std::ios_base::in ) ;
        if ( !f ) {
            GkfThrow(GKF_EOPENFILE, "Can't open given file.");
        }
        
        int linecount = 0 ;
        
        while ( !f.eof() )
        {
            std::string line; std::getline(f, line, '\n');
            linecount ++ ;
            
            if ( f.bad() ) {
                std::cerr << "An error occured while parsing file '" << iFilepath << "' at line " << linecount << "." << std::endl;
                GkfThrow(GKF_EGETLINE, "Error while parsing file.") ;
            }
            
            else if ( !line.empty() )
            {
                std::stringstream ss (line) ;
                
                while ( !ss.eof() )
                {
                    std::string str ; ss >> str ;
                    
                    if ( str == "?" ) {
                        std::getline(ss, str, '\n');
                        iComments.push_back('\n'); iComments.append(str);
                        break ;
                    }
                    
                    else if ( str == "l" ) {
                        ss >> str ; iLocale = str ;
                        break ;
                    }
                    
                    else if ( str == "lang" ) {
                        ss >> str ; iLanguage = str ;
                        break ;
                    }
                    
                    else if ( str == "t" ) {
                        std::string name , translation ;
                        ss >> name >> str ; std::getline(ss, translation, '\n') ;
                        
                        // Just pop the normally space included at the beginning because of std::getline.
                        
                        translation.erase(translation.begin());
                        
                        // See if the Translation already exists ( it can be done when using 'd' keyword
                        // before using the 't' keyword ). Notes that if the KEY has already been defined
                        // with another translation, it will be overwritten.
                        
                        auto it = iTranslations.find(name) ;
                        
                        if ( it != iTranslations.end() ) {
                            (*it).second->setValue(translation) ;
                        } else {
                            iTranslations[name] = new Translation ( name , translation ) ;
                        }
                        
                        break ;
                    }
                    
                    else if ( str == "d" ) {
                        std::string key , definition ;
                        ss >> key >> str ; std::getline(ss, definition, '\n') ;
                        
                        // Just pop the normally space included at the beginning because of std::getline.
                        
                        definition.erase(definition.begin());
                        
                        // See if the Translation already exists. If not, we create one with an empty
                        // value and set the definition.
                        
                        auto it = iTranslations.find(key) ;
                        
                        if ( it != iTranslations.end() ) {
                            (*it).second->setDefinition(definition) ;
                        } else {
                            iTranslations[key] = new Translation ( key , std::string() , definition ) ;
                        }
                        
                        break ;
                    }
                    
                    else {
                        std::cerr << "Bad keyword given. ('" << str << "')" << std::endl;
                        break;
                    }
                }
            }
        }
    }
}

Translation* LocaleFile::setKey(const std::string &newkey, GKF::Translation * trans)
{
    std::string oldkey = trans->getKey() ;
    auto it = iTranslations.find(oldkey) ;
    
    if ( it != iTranslations.end() ) {
        iTranslations.erase(it);
    }
    
    iTranslations[newkey] = trans ;
    iTranslations[newkey]->setKey(newkey) ;
    return iTranslations[newkey] ;
}

void LocaleFile::addTranslation(const GKF::Translation & trans)
{
    iTranslations[trans.getKey()] = new Translation ( trans ) ;
}

void LocaleFile::write(const std::string &filepath) const
{
    std::ofstream out ( filepath , std::ios_base::out ) ;
    
    if ( !out ) {
        GkfThrow(GKF_EOPENFILE, "Can't open given file.");
    }
    
    // First writes the name of the file and our marks.
    
    out << "? " << filepath << std::endl;
    out << "? Created by libgkf (2017) ." << std::endl << std::endl ;
    
    // Then writes the locale mode.
    
    if ( !iLocale.empty() )
        out << "l " << iLocale << std::endl;
    if ( !iLanguage.empty() )
        out << "lang " << iLanguage << std::endl;
    
    out << std::endl ;
    
    // Writes definitions.
    
    for ( auto it : iTranslations )
    {
        if ( it.second )
        {
            if ( !it.second->getDefinition().empty() ) {
                out << "d " << it.second->getKey() << " ? " << it.second->getDefinition() << std::endl;
            }
        }
    }
    
    // Writes translations.
    
    for ( auto it : iTranslations )
    {
        if ( it.second )
        {
            if ( !it.second->getValue().empty() ) {
                out << "t " << it.second->getKey() << " ? " << it.second->getValue() << std::endl;
            }
        }
    }
    
    // Close file.
    
    out.close() ;
}

void LocaleFile::read(const std::string &filepath)
{
    if ( !iFilepath.empty() )
        reset () ;
    
    iFilepath = filepath ;
    init() ;
}

void LocaleFile::reset()
{
    iFilepath = std::string () ;
    iComments = std::string () ;
    iLocale   = std::string () ;
    iLanguage = std::string () ;
    
    for ( auto it : iTranslations ) {
        if ( it.second ) delete it.second ;
    }
    
    iTranslations.clear() ;
}

const std::string & LocaleFile::getFilepath() const
{
    return iFilepath ;
}

void LocaleFile::setFilepath(const std::string &path)
{
    iFilepath = path ;
}

LocaleFile* LoadLocalFile ( const std::string & filepath )
{
    return new LocaleFile ( filepath ) ;
}

LocaleFileManager::LocaleFileManager ()
{
    
}

LocaleFile* LocaleFileManager::load(const std::string &filepath)
{
    for ( auto it : iLocaleFiles ) {
        if ( it && it->getFilepath() == filepath )
            return it ;
    }
    
    LocaleFile * ret = new LocaleFile ( filepath ) ;
    if ( ret ) iLocaleFiles.push_back(ret) ;
    
    return ret ;
}

const LocaleFile* LocaleFileManager::get(const std::string &filepath) const
{
    for ( auto it : iLocaleFiles ) {
        if ( it && it->getFilepath() == filepath )
            return it ;
    }
    
    return nullptr ;
}

void LocaleFileManager::reset()
{
    for ( auto it : iLocaleFiles ) {
        if ( it ) delete it ;
    }
    
    iLocaleFiles.clear() ;
}

const Translation* LocaleFileManager::findTranslation(const std::string &key, const GKF::Locale *loc) const
{
    if ( !loc || key.empty() ) return nullptr ;
    return loc->findTranslation(key, iLocaleFiles) ;
}

GkfEnd

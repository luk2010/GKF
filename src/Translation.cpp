////////////////////////////////////////////////////
//  File    : Translation.cpp
//  Project : Gang's Keyboard Framework
//
//  Created by Jacques Tronconi on 30/01/2017.
//    Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
////////////////////////////////////////////////////

#include "Translation.h"

GkfBegin

Translation::Translation ()
{
    
}

Translation::Translation ( const std::string & name , const std::string & value , const std::string & definition )
{
    iName = name ;
    iValue = value ;
    iDefinition = definition ;
}

void Translation::setParameter(int i, const std::string &value) const
{
    iParameters[i] = value ;
}

std::string Translation::translate() const
{
    std::string ret ;
    
    for ( unsigned int i = 0 ; i < iValue.size() ; i++ )
    {
        if ( iValue[i] == '%' && iValue[i+1] == '%' ) {
            ret.push_back('%') ; i++ ;
        }
        else if ( iValue[i] == '%' ) {
            int num = (int) ( iValue[i+1] - '0' ) ;
            
            if ( iParameters.find(num) != iParameters.end() ) {
                ret.append(iParameters[num]);
            }
            
            i++ ;
        }
        else {
            ret.push_back(iValue[i]) ;
        }
    }
    
    return ret ;
}

const std::string & Translation::getDefinition() const
{
    return iDefinition ;
}

void Translation::setDefinition(const std::string &definition)
{
    iDefinition = definition ;
}

const std::string & Translation::getValue() const
{
    return iValue ;
}

void Translation::setValue(const std::string &value)
{
    iValue = value ;
}

const std::string & Translation::getKey() const
{
    return iName ;
}

void Translation::setKey(const std::string &key)
{
    iName = key ;
}

GkfEnd

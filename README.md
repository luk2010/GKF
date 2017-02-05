# GKF
A little library made to handle small translations files.

## A simple example

Say you have a program 'main.c'. You want to say hello, but in the correct user language. This is effectivly possible with the 
GKF library, as shown below. 

```c++

#include <GKF/LocaleFile.h>
#include <GKF/Locales.h>

int main ( int argc, char** argv )
{
  GKF::LocaleFileManager fmanager ;
  int count = fmanager.loadDirectory ( "langs" ) ;
  
  std::cout << "Available languages : " << count << std::endl;
  
  GKF::Locale* current = GKF::GetCurrentLocale () ;
  if ( !current ) return 1 ;
  
  auto translation = fmanager.findTranslation ( "HELLO" , current ) ;
  if ( !translation ) {
    std::cout << "No translation found for language : " << current->getLangName () << std::endl;
    delete current ;
    return 2 ;
  }
  
  translation->setParameter(0, argv[0]) ;
  std::cout << translation->translate() << std::endl;
  
  delete current ;
  return 0 ;
}

```

This simple example shows you how to load GKF's translation files in a given directory, load the current locale object, and 
use those informations to get the correct translation object. 

Note that the translation object can be used with the 'translate' method with given parameter, but you also can use printf 
functions if you put traditionnal '%s' or else in your string, by using 'getValue' instead.

## Creating a GKF Translation file

Simply create a text file with your favorite text editor. We advise you to use the '.gkf' extension to recognize those files
but this is not a rule. Below is an example of a very simple file, wich can be used with the given example above.

```

? example-french.gkf
? There is just one translation named HELLO. 

l fr

t HELLO ? Bonjour , %0 :-) !
d HELLO ? The 'hello' sentence.

```

- *l* is a keyword to indicate wich language code can use this file.
- *t* defines a translation with a KEY and a VALUE, or add a VALUE to the KEY if it already exists. 
- *d* defines a translation with a KEY and a DEFINITION, or add a DEFINITION to the KEY if it already exists.

For *t* and *d*, the *?* indicates the parser that the rest of the line is the value. Every *?* in beginning of a line 
indicates a comment and is so ignored (or stored in the LocaleFile structure).

## Compiling

You have to use CMake to generate a project. Then use the generated project to make the library.

## Things to do

Currently, only Mac OS X is supported. So the first thing to do is to add Unix and Windows implementation.

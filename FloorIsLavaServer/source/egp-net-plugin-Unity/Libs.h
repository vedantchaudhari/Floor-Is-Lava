#ifndef _LIBS_H
#define _LIBS_H

//	configuring the DLL
#ifdef LAVAPLUGIN_EXPORT
#define LAVAPLUGIN_SYMBOL __declspec(dllexport)
#else 
#ifdef LAVAPLUGIN_IMPORT
#define LAVAPLUGIN_IMPORT __declspec(dllimport)
#else
#define	LAVAPLUGIN_SYMBOL
#endif // LAVAPLUGIN_IMPORT
#endif
#endif // !LIBS_H

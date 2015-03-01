#ifndef _DLL_H_
#define _DLL_H_

#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */


DLLIMPORT void HelloWorld (void);
DLLIMPORT int suma(int a, int b);
DLLIMPORT int resta(int a, int b);
DLLIMPORT int multiplica(int a, int b);
DLLIMPORT int divide(int a, int b);
DLLIMPORT int modulo(int a, int b);
DLLIMPORT float fsuma(float a, float b);
DLLIMPORT float fresta(float a, float b);
DLLIMPORT float fmultiplica(float a, float b);
DLLIMPORT float fdivide(float a, float b);
DLLIMPORT float smultiplica(char *aa, char *bb);
DLLIMPORT float sdivide(char *aa, char *bb);
#endif /* _DLL_H_ */

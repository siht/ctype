/* Replace "dll.h" with the name of your header */
/*
 * compilado con un gcc a 32 bits las opciones estan en el 
 * makefile.
 * la sintaxis es de un ensamblador AT&T.
 * tambien hay que notar que en algunas funciones no se incluye
 * una sentencia return, ya que al escribir el valor en el regitro
 * eax equivale a hacer return value. Eso hasta ahorita he visto
 * que sirve con los registros que han sido procesados con operaciones
 * normales de enteros, sin embargo para los regitros de "tipo" float
 * no lo he logrado, al parecer necesitan alguna directiva extra
 * para poder hacerlo. Lo anterior rompe un esquema importante
 * lo explicito es mejor que lo implicito, pero se rompio esa regla
 * con el fin de explorar como funciona un ensamblador.
 */
#include "basic_op.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

DLLIMPORT void HelloWorld ()
{
    MessageBox (0, "Hello World from DLL!\n", "Hi", MB_ICONINFORMATION);
}


DLLIMPORT int suma(int a, int b)
{
	 // volatile evita que el compilador intente "mejorar" el código,
	 // tal como esta aparecera ese codigo assembly sin optimizacion
     __asm__ __volatile__(
     "addl %%ebx,%%eax;"
     :"=a"(a) //se esribe en eax, no necesitamos return
     :"a"(a), "b"(b) // entradas
     );
}

DLLIMPORT int resta(int a, int b)
{
     __asm__ __volatile__(
     "subl %%ebx,%%eax;"
     :"=a"(a)
     :"a"(a), "b"(b)
     );
}

DLLIMPORT int multiplica(int a, int b)
{
     __asm__ __volatile__(
     "imull %%ebx, %%eax;"
     :"=a"(a)
     :"a"(a), "b"(b)
     );
}

DLLIMPORT int divide(int a, int b)
{
     __asm__ __volatile__(
     "xorl %%edx, %%edx;"
     "movl %2, %%eax;"
     "movl %3, %%ebx;"
     "idivl %%ebx;"
     : "=d" (b), "=a" (a)
     : "g" (a), "g" (b)
     );
}

DLLIMPORT int modulo(int a, int b)
{
     __asm__ __volatile__(
     "xorl %%edx, %%edx;"
     "movl %2, %%eax;"
     "movl %3, %%ebx;"
     "idivl %%ebx;"
     : "=a" (a), "=d" (b)
     : "g" (a), "g" (b)
     );
}

DLLIMPORT float fsuma(float a, float b)
{
    float r;
     __asm__ __volatile__(
     "fld %1;"
     "fld %2;"
     "faddp;"
     "fstp %0;"
     : "=g" (r) // si escribo a eax me da un valor que no espero
     : "g" (a), "g" (b)
     );
     return r;
}

DLLIMPORT float fresta(float a, float b)
{
    float r;
     __asm__ __volatile__(
     "fld %1;"
     "fld %2;"
     "fsubp;"
     "fstp %0;"
     : "=g" (r)
     : "g" (b), "g" (a)
     );
     return r;
}

DLLIMPORT float fmultiplica(float a, float b)
{
     printf("a = %f -------- b=%f",a,b);
     float r;
     __asm__ __volatile__(
     "fld %1;"
     "fld %2;"
     "fmulp;"
     "fstp %0;"
     : "=g" (r)
     : "g" (a), "g" (b)
     );
     return r;
}

DLLIMPORT float fdivide(float a, float b)
{
    float r;
     __asm__ __volatile__(
     "fld %1;"
     "fld %2;"
     "fdivp;"
     "fstp %0;"
     : "=g" (r)
     : "g" (b), "g" (a)
     );
     return r;
}

DLLIMPORT float smultiplica(char *aa, char *bb)
{
    float a = atof(aa);
    float b = atof(bb);
    float r = 0;
     __asm__ __volatile__(
     "fld %1;"
     "fld %2;"
     "fmulp;"
     "fstp %0;"
     : "=g" (r)
     : "g" (a), "g" (b)
     );
     return r;
}

DLLIMPORT float sdivide(char *aa, char *bb)
{
    float a = atof(aa);
    float b = atof(bb);
    float r = 0;
     __asm__ __volatile__(
     "fld %1;"
     "fld %2;"
     "fdivp;"
     "fstp %0;"
     : "=g" (r)
     : "g" (b), "g" (a)
     );
     return r;
}

DLLIMPORT int mcd(int a, int b)
{
     int r;
    __asm__ __volatile__ (
     "movl %1, %%eax;"
     "movl %2, %%ebx;"
     "CONTD: cmpl $0, %%ebx;"
     "je DONE;"
     "xorl %%edx, %%edx;"
     "idivl %%ebx;"
     "movl %%ebx, %%eax;"
     "movl %%edx, %%ebx;"
     "jmp CONTD;"
     "DONE: movl %%eax, %0;"
     : "=g" (r)
     : "g" (a), "g" (b)
    );
    return r;
}


BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
        break;

      case DLL_PROCESS_DETACH:
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}

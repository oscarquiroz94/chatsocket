#ifndef __PRINTERCHAT__
#define __PRINTERCHAT__

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>
#include <cstdlib>

/*
    Clase abstracta para la funcion virtual pura "printData"
*/
class PrinterChat
{
    public:
        
        virtual void printData(char *szTypes, ... ) = 0;
    
    protected:
        time_t t;
        struct tm timeinfo;
        char strtime[100];
        static const uint16_t _defaultbuflen = 512;
};

#endif
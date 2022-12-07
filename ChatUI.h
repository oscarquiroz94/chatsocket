#ifndef __CHATUI__
#define __CHATUI__

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>

/*
    Capa de visualizacion
*/
class ChatUI 
{
    private:
        time_t t;
        struct tm timeinfo;
        char strtime[100];
        static const uint16_t _defaultbuflen = 512;
    public:

        /*
            Recibe argumentos sin cantidad fija para concatenar entre si y con adicion de fecha-hora
            i = int     f = float   c = char    s = string (char *)
            "fcsi", 32.4f, 'a', "Test string", 4
        */
        void printUI(char *szTypes, ... );

        /*
            Solicitar al usuario el nickname y devolver string
        */
        std::string getNickname();

        ChatUI() = default;
        ~ChatUI() = default;
};

#endif

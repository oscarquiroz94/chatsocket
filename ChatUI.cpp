#include "ChatUI.h"
#include <iostream>
#include <string>

std::string ChatUI::getNickname(){
    
    printf("*** PARA SALIR CIERRE PROGRAMA ***\n");
    printf("Escriba su nickname: ");
    
    std::string nickstr = "STRNICK";
    std::string name;

    std::getline (std::cin,name);

    name = nickstr + name;

    return name;
}

void ChatUI::printUI(char *szTypes, ... ){
    time(&t);
    localtime_s(&timeinfo, &t);
    char buffertime[100];
    strftime (buffertime,80,"%x-%X ", &timeinfo);
    printf(buffertime);

    va_list vl;
    va_start( vl, szTypes );

    for(int i = 0; szTypes[i] != '\0'; ++i ) {
        union Printable_t {
            int     i;
            float   f;
            char    c;
            char   *s;
        } Printable;

        switch( szTypes[i] ) {   
            case 'i':
                Printable.i = va_arg( vl, int );
                printf_s( "%i", Printable.i );
            break;

            case 'f':
                Printable.f = va_arg( vl, float );
                printf_s( "%f", Printable.f );
            break;

            case 'c':
                Printable.c = va_arg( vl, char );
                printf_s( "%c", Printable.c );
            break;

            case 's':
                Printable.s = va_arg( vl, char * );
                printf_s( "%s", Printable.s );
            break;

            default:
            break;
        }
    }
    printf_s("\n");
    va_end( vl );
}


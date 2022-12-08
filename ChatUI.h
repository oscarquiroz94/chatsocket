#ifndef __CHATUI__
#define __CHATUI__

#include "PrinterChat.h"

/*
    CAPA DE VISUALIZACION
    Adicion de caracteristicas a los mensajes recibidos y enviados en consola
*/
class ChatUI : public PrinterChat
{
    public:
        /*
            Recibe argumentos sin cantidad fija para concatenar entre si y con adicion de fecha-hora
            i = int     f = float   c = char    s = string (char *)
            "fcsi", 32.4f, 'a', "Test string", 4
        */
        void printData(char *szTypes, ... ) override;

        /*
            Solicitar al usuario el nickname y devolver string
        */
        std::string getNickname();

        ChatUI() = default;
        ~ChatUI() = default;
};

#endif

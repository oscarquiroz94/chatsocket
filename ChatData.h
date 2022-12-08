#ifndef __CHATDATA__
#define __CHATDATA__

#include "PrinterChat.h"
#include "ChatUI.h"

/*
    CAPA DE DATOS
    Se almacena el historial en un archivo de texto
*/
class ChatData : public PrinterChat
{
    private:
        std::string _namefile = "C:/Users/User/Desktop/PruebasC++/testchat/chatsocket/historial.txt";
    public:
        /*
            Recibe argumentos sin cantidad fija para concatenar entre si y con adicion de fecha-hora
            i = int     f = float   c = char    s = string (char *)
            "fcsi", 32.4f, 'a', "Test string", 4
        */
        void printData(char *szTypes, ... ) override;

        ChatData() = default;

        ~ChatData() = default;
};



#endif
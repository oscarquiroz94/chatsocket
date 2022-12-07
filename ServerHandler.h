#ifndef __SERVERHANDLER__
#define __SERVERHANDLER__

#include <winsock2.h>
#include "ChatUI.h"
#include <mutex>
#include <list>

/*
    CAPA DE CONTROL
    Gestion de recepcion de mensajes y echo a los clientes
*/
class ServerHandler 
{
    
    public:
        /*
            Gestionar clientes conectados
        */
        void handler(int sock, std::list<SOCKET>& listClient);

    private:
        std::mutex mtx;
        ChatUI svui;
        static const uint16_t _default_buflen = 512;
        bool comparar(const char *cadena, const char *subcadena);

};

#endif
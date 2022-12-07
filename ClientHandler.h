#ifndef __CLIENTHANDLER__
#define __CLIENTHANDLER__

#include "ClientChat.h"

/*
    CAPA DE CONTROL
    Gestion de las comunicaciones, envio y recepcion
*/
class ClientHandler
{
    public:
        /*
            Gestionar el envio de mensajes al servidor
        */
        void sendToServer(int sock);

        /*
            Gestionar la recepcion de mensajes del servidor
        */
        void receiveFromServer(int sock);

    private:
        static const uint16_t _default_buflen = 512;
    
};





#endif
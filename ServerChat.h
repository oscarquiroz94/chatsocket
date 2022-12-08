#ifndef __SERVERCHAT__
#define __SERVERCHAT__

#ifndef UNICODE
#define UNICODE
#endif

#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <Ws2tcpip.h>
#include <list>
#include <memory>

#include "ChatUI.h"


#pragma comment(lib, "Ws2_32.lib")

/*
    CAPA DE CONTROL
    Servidor socket de escucha y respuesta no-asincrona
    Bloqueo del thread por metodo recv()
*/
class ServerChat
{
    public:
        ServerChat(const int port, const char* IP);

        /*
            Inicializa el uso de la DLL de Winsock.
        */
        void startup();

        /*
            Crear socket
        */
        void create();

        /*
            Vincular socket al puerto e IP del sistema operativo
        */
        void bindMethod();

        /*
            Cerrar socket
        */
        void cleanup() const;

        /*
            Esperar conexiones entrantes
        */
        int16_t listenMethod();


        ~ServerChat() = default;

    private:
        SOCKET _listenSocket;
        SOCKET _acceptSocket;
        std::list<SOCKET> listClients;
        ChatUI _chatui;
        int _port;
        char _IP[20];
        
};

#endif
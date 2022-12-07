#ifndef __CLIENTCHAT__
#define __CLIENTCHAT__

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "iostream"
#include <thread>
#include <mutex>
#include "ChatUI.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


/*
    CAPA DE CONTROL
    Creacion, conexion y limpieza del socket cliente
*/
class ClientChat{
    public:
        /*
            Inicializa el uso de la DLL de Winsock.
        */
        void Startup();

        /*
            Construir objeto de configuracion socket
            pasar IP como argumento
        */
        void Resolve(char** argv);

        /*
            Crear socket y probar conexion
        */
        void AttemptConnection();

        /*
            Conectar a servidor 
            Pasar nickname como argumento
        */
        SOCKET Conectar(std::string str);

        void Cleanup();

    private:
        ChatUI _chatui;
        WSADATA _wsaData;
        SOCKET _connectSocket = INVALID_SOCKET;
        struct addrinfo *_result = NULL,
                        *_ptr = NULL,
                        _hints;

        char* _port = "8080";
};


#endif
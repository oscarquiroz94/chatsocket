#include "ClientChat.h"

void ClientChat::Startup(){
    // Initializar Winsock

    int iResult = WSAStartup(MAKEWORD(2,2), &_wsaData);
    if (iResult != 0) {
        _chatui.printData("si","WSAStartup fallo con error:", iResult);
    }

    ZeroMemory( &_hints, sizeof(_hints) );
    _hints.ai_family = AF_UNSPEC;
    _hints.ai_socktype = SOCK_STREAM;
    _hints.ai_protocol = IPPROTO_TCP;
}

void ClientChat::Resolve(char** argv){

    int iResult = getaddrinfo(argv[1], _port, &_hints, &_result);
    if ( iResult != 0 ) {
        _chatui.printData("si","Getaddrinfo fallo con error: ", iResult);
        WSACleanup();
    }
}

void ClientChat::AttemptConnection(){
    for(_ptr=_result; _ptr != NULL ;_ptr=_ptr->ai_next) {

        // Crear socket para conectar a server
        _connectSocket = socket(_ptr->ai_family, _ptr->ai_socktype, _ptr->ai_protocol);
        if (_connectSocket == INVALID_SOCKET) {
            _chatui.printData("si","Socket fallo con error: ", WSAGetLastError());
            WSACleanup();
        }

        // Connect a server
        int iResult = connect( _connectSocket, _ptr->ai_addr, (int)_ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(_connectSocket);
            _connectSocket = INVALID_SOCKET;
            continue;
        }
        freeaddrinfo(_result);
        break;
    }
}

SOCKET ClientChat::Conectar(std::string str){

    const char* strnick = str.c_str();

    if (_connectSocket == INVALID_SOCKET) {
        _chatui.printData("s","No es posible conectar a servidor!");
        WSACleanup();
        return -1;
    }else{
        send( _connectSocket, strnick, (int)strlen(strnick), 0 );
        _chatui.printData("s","Conectado, escriba un mensaje!");
        return _connectSocket;
    }
}

void ClientChat::Cleanup(){
    // cleanup
    closesocket(_connectSocket);
    WSACleanup();
}

#include "ServerChat.h"


ServerChat::ServerChat(const int port, const char* ip)
{
    _port = port;
    strcpy_s(_IP, ip);
}


void ServerChat::startup(){
    WSADATA wsaData;
    
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != NO_ERROR) {
        _chatui.printData("si","Error iniciando WSAStartup: ", result);

    }else _chatui.printData("s","Startup Okay");
}


void ServerChat::create(){
    _listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_listenSocket == INVALID_SOCKET) {
        _chatui.printData("si","Creacion de Socket fallo con error: ", WSAGetLastError());
        WSACleanup();

    }else _chatui.printData("s","Socket creado");
}


void ServerChat::bindMethod(){
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(_IP);
    service.sin_port = htons((u_short)_port);

    //InetPton(AF_INET, (PCWSTR)_IP, &service.sin_addr.s_addr);

    if (bind(_listenSocket, (SOCKADDR *)& service, sizeof (service)) == SOCKET_ERROR) {
        _chatui.printData("si","bind fallo con error: ", WSAGetLastError());
        closesocket(_listenSocket);
        WSACleanup();
    }else _chatui.printData("s","Socket enlazado");
}


int16_t ServerChat::listenMethod(){

    if(listen(_listenSocket, SOMAXCONN) == SOCKET_ERROR ) return -1;

    _chatui.printData("s","Esperando conexion de cliente...");
    _acceptSocket = accept(_listenSocket, NULL, NULL);

    if(_acceptSocket != INVALID_SOCKET){
        _chatui.printData("sis","Cliente ", (int)_acceptSocket, " conectado");
        
    } else return -1;

    return (int16_t)_acceptSocket;
}


void ServerChat::cleanup() const{
    // cleanup
    closesocket(_listenSocket);
    WSACleanup();
}


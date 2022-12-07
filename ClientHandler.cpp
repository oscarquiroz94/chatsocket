#include "ClientHandler.h"

void ClientHandler::sendToServer(int sock){

    while(true){

        printf("---->");
        char msg[_default_buflen];
        std::cin.getline(msg, _default_buflen);
 
        int iResult = send( sock, msg, (int)strlen(msg), 0 );
        if (iResult == SOCKET_ERROR) {
            printf("sendToServer fallo con error: %d\n", WSAGetLastError());
        }
        memset(msg, 0, _default_buflen);
    }
}


void ClientHandler::receiveFromServer(int sock){
    ChatUI svui;
    
    char recvbuf[_default_buflen] = "";
    int iResult;
    int recvbuflen = _default_buflen;

    while (true){

        iResult = recv(sock, recvbuf, recvbuflen, 0);

        char *nick = strtok(recvbuf,",");
        char* msg = strtok(NULL,",");
        
        if (iResult > 0){
            svui.printUI("sss",nick,": ",msg);
            printf("---->");
            memset(recvbuf, 0, _default_buflen);
        }
    }
}
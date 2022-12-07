#include "ServerHandler.h"

void ServerHandler::handler(int sock, std::list<SOCKET>& listClient){
    std::list<SOCKET>::iterator index = listClient.end();
    
    char msg[_default_buflen];
    char nickname[100];
    memset(msg, 0, _default_buflen);
    memset(nickname, 0, 100);

    //Hilo que finaliza con programa
    while(true){
        int iResult = recv(sock, msg, sizeof(msg),0);
        if (iResult <= 0) continue;


        //Si llega comando de asignacion de nombre
        if(comparar(msg,"STRNICK")){
            strcpy_s(nickname, msg + 7);
            memset(msg, 0, _default_buflen);
            continue;
        }
        svui.printUI("sss",nickname,": ",msg);


        //Echo a todos los clientes
        mtx.lock();
        for (index = listClient.begin(); index != listClient.end(); ++index){
            char clientmsg[_default_buflen];
            strcpy_s(clientmsg,nickname);
            strcat_s(clientmsg,",");
            strcat_s(clientmsg,msg);

            //Enviar al cliente *index
            int iSendResult = send( *index, clientmsg, (int)strlen(clientmsg), 0 );

            if (iSendResult == SOCKET_ERROR) {
                svui.printUI("si","send failed with error: ", WSAGetLastError());
            }
        }
        mtx.unlock();
        
        memset(msg, 0, _default_buflen);
                
    }
}

bool ServerHandler::comparar(const char *cadena, const char *subcadena){
    for(size_t i=0; i < strlen(subcadena); i++){
        if(cadena[i] != subcadena[i]) return false;
    }
    return true;
}


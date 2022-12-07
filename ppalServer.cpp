#include "ServerChat.h"
#include "ServerHandler.h"
#include "ChatUI.h"
#include <memory>
#include <list>
#include <thread>
#include <mutex>
#include <iostream>
#include <sstream>

std::mutex mtx;

/*
#define DEFAULT_BUFLEN 512
bool comparar(const char *cadena, const char *subcadena){
    for(size_t i=0; i < strlen(subcadena); i++){
        if(cadena[i] != subcadena[i]) 
            return false;
    }
    return true;
}

void handle_client(int sock, std::list<SOCKET>& listClient){
    ChatUI svui;
    std::list<SOCKET>::iterator index = listClient.end();
    std::stringstream ss;
    ss << std::this_thread::get_id();
    printf("en hilo");
    char msg[DEFAULT_BUFLEN];
    char nick[100];
    memset(msg, 0, DEFAULT_BUFLEN);
    memset(nick, 0, 100);
    while(1){
        int iResult = recv(sock, msg, sizeof(msg),0);

        if(comparar(msg,"STRNICK")){
            strcpy_s(nick, msg + 7);
            memset(msg, 0, DEFAULT_BUFLEN);
            continue;
        }
       

        //verificar funcionamiento
        if (strstr(msg,"EXIT")) break;

        if (iResult <= 0) continue;

        //svui.print("ssss",nick,": ",msg,"\n");
        printf("%s: %s\n", nick, msg);

        //Echo a todos los clientes
        for (index = listClient.begin(); index != listClient.end(); ++index){
            char clientmsg[DEFAULT_BUFLEN];
            strcpy_s(clientmsg,nick);
            strcat_s(clientmsg,",");
            strcat_s(clientmsg,msg);

            //Enviar al cliente *index
            int iSendResult = send( *index, clientmsg, (int)strlen(clientmsg), 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                mtx.lock();
                listClient.remove(*index);
                mtx.unlock();
            }
        }
        memset(msg, 0, DEFAULT_BUFLEN);
                
    }

}*/

int main(){
    ServerChat svc(8080, "127.0.0.1");
    std::list<SOCKET> listClients;
    
    std::shared_ptr<ServerHandler> svh = std::make_shared<ServerHandler>();
    //ServerHandler* svh = new ServerHandler;

    ChatUI svui;
    svui.printUI("s","*** PARA SALIR CIERRE PROGRAMA ***");
    
    svc.startup();
    svc.create();
    svc.bindMethod();

    while(true){
        int16_t client = svc.listenMethod();
        if(client == -1) continue;

        mtx.lock();
        listClients.push_back(client);
        mtx.unlock();

        //std::thread th(handle_client, (int)client, std::ref(listClients));
        std::thread th(&ServerHandler::handler, svh, (int)client, std::ref(listClients));
        th.detach();
        
    }
    
    svc.cleanup();

    return 0;
}
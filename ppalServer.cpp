#include "ServerChat.h"
#include "ServerHandler.h"
//#include "ChatUI.h"
#include <memory>
#include <list>
#include <thread>
#include <mutex>
#include <iostream>
#include <sstream>

std::mutex mtx;

int main(){
    ServerChat svc(8080, "127.0.0.1");
    std::list<SOCKET> listClients;
    
    std::shared_ptr<ServerHandler> svh = std::make_shared<ServerHandler>();

    //ChatUI svui;
    //svui.printData("s","*** PARA SALIR CIERRE PROGRAMA ***");
    
    svc.startup();
    svc.create();
    svc.bindMethod();

    while(true){
        int16_t client = svc.listenMethod();
        if(client == -1) continue;

        mtx.lock();
        listClients.push_back(client);
        mtx.unlock();

        std::thread th(&ServerHandler::handler, svh, (int)client, std::ref(listClients));
        th.detach();
        
    }
    
    svc.cleanup();

    return 0;
}
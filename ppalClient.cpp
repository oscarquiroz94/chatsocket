
#include "ClientChat.h"
#include "ClientHandler.h"


int main(int argc, char **argv) 
{

    ClientChat clc;
    SOCKET connectSocket = INVALID_SOCKET;
    ChatUI svui;

    clc.Startup();
    clc.Resolve(argv);
    clc.AttemptConnection();
    connectSocket = clc.Conectar(svui.getNickname());

    std::shared_ptr<ClientHandler> ptrsend = std::make_shared<ClientHandler>();
    std::shared_ptr<ClientHandler> ptrrecv = std::make_shared<ClientHandler>();


    std::thread thsend(&ClientHandler::sendToServer, ptrsend, (int)connectSocket);
    std::thread thrcv(&ClientHandler::receiveFromServer, ptrrecv, (int)connectSocket);


    if(thsend.joinable()) thsend.join();
    if(thrcv.joinable()) thrcv.join();

    clc.Cleanup();

    return 0;
}
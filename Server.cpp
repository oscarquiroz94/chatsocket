#ifndef UNICODE
#define UNICODE
#endif

#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>

// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512

std::vector<SOCKET> listClients;
std::mutex mtx;

void handle_client(int sock, std::vector<SOCKET>& listClient){
    //std::hash<std::thread::id> hasher;
    //size_t numid = hasher(std::this_thread::get_id());

    //std::cout<<"Worker Thread "<<sock<<" is Executing"<<std::endl;
    char msg[DEFAULT_BUFLEN];
    memset(msg, 0, DEFAULT_BUFLEN);
    while(1){
        int iResult = recv(sock, msg, sizeof(msg),0);

        if (strstr(msg,"EXIT")) break;

        if (iResult <= 0) continue;

        printf("message from client %i: %s\n", sock, msg);

        //Echo a todos los clientes
        for(auto index = listClient.begin(); index != listClient.end(); index++){
            printf("echo a %i", *index);
            printf(" con %s\n",msg);
            int iSendResult = send( *index, msg, iResult, 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                mtx.lock();
                listClient.erase(std::remove(listClient.begin(), listClient.end(), *index), listClient.end());
                mtx.unlock();
            }
        }
        memset(msg, 0, DEFAULT_BUFLEN);
                
    }

}

class Clients
{
    private:
        /* data */
    public:
        void operator()()     
        {
            std::cout<<"Worker Thread "<<std::this_thread::get_id()<<" is Executing"<<std::endl;
        }
        Clients() = default;
        ~Clients() = default;
};



int main(void)
{
    //std::vector<std::thread> list_Threads;

    //----------------------
    // Initialize Winsock.
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %ld\n", iResult);
        return 1;
    }
    //----------------------
    // Create a SOCKET for listening for
    // incoming connection requests.
    SOCKET ListenSocket;
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port for the socket that is being bound.
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(8080);

    if (bind(ListenSocket,(SOCKADDR *)& service, sizeof (service)) == SOCKET_ERROR) {
        wprintf(L"bind failed with error: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    /*
    //----------------------
    // Listen for incoming connection requests.
    // on the created socket
    if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
        wprintf(L"listen failed with error: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    //----------------------
    // Create a SOCKET for accepting incoming requests.
    SOCKET AcceptSocket;
    wprintf(L"Waiting for client to connect...\n");

    //----------------------
    // Accept the connection.
    AcceptSocket = accept(ListenSocket, NULL, NULL);
    if (AcceptSocket == INVALID_SOCKET) {
        wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    } else
        wprintf(L"Client connected.\n");

    // No longer need server socket
    closesocket(ListenSocket);
    char recvbuf[512];
    int recvbuflen = 512;
    int iSendResult;
    char mensaje[100];
*/
    

    //char msg[512];
    SOCKET AcceptSocket;
    
    while(1){
        
        if(listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR ) continue;
            
        printf("Waiting for client to connect...\n");

        AcceptSocket = accept(ListenSocket, NULL, NULL);
        if(AcceptSocket != INVALID_SOCKET){
            printf("Client connected %i.\n", (int)AcceptSocket);

            mtx.lock();
            listClients.push_back(AcceptSocket);
            mtx.unlock();

            std::thread th(handle_client, (int)AcceptSocket, std::ref(listClients));
            th.detach();

            /*
            std::for_each(list_Threads.begin(),list_Threads.end(), std::mem_fn(&std::thread::join));
            for (auto index = list_Threads.begin(); index != list_Threads.end(); index++) {
                std::mem_fn();
            }*/
        }
        /*
        int iResult = recv(AcceptSocket, msg, sizeof(msg),0);
        if (strstr(msg,"EXIT")){break;}
        if (iResult > 0){
            printf("message from client: %s\n",msg);
            memset(msg,0,512);
        }*/
    }

    // cleanup
    closesocket(AcceptSocket);
    WSACleanup();

    /*
    while(!strstr(mensaje, "EXIT")){
        
        printf("--->");
        std::cin.getline(mensaje, 100);
        iResult = send( AcceptSocket, mensaje, (int)strlen(mensaje), 0 );

        memset(recvbuf,0,512);
        iResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0){
            printf("message from client: %s\n",recvbuf);
            WSACleanup();
        }
    }

    
    // Receive until the peer shuts down the connection
    do {

        iResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);
            printf("message from client: %s\n",recvbuf);

            // Echo the buffer back to the sender
            iSendResult = send( AcceptSocket, recvbuf, iResult, 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(AcceptSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent to client: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(AcceptSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);
    

    // shutdown the connection since we're done
    iResult = shutdown(AcceptSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(AcceptSocket);
        WSACleanup();
        return 1;
    }
*/
    
    return 0;
}

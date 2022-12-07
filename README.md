# ChatSocket
 Aplicacion de comunicacion bidireccional servidor-cliente mediante sockets (chat en vivo)
 
 Para compilar se requiere Microsoft Visual C++ (MSVC) compiler toolset. 
 Puede encontrar una guia de configuracion en https://code.visualstudio.com/docs/cpp/config-msvc

## Compilar
Abra el **Commad Prompt** y dirijase a la carpeta donde descargó el codigo, por ejemplo: *C:\Users\User\Desktop\PruebasC++\testchat\chatsocket*

Para compilar el codigo del servidor escriba: *cl /W4 /EHsc ppalServer.cpp  ServerChat.cpp ChatUI.cpp ServerHandler.cpp*

Para compilar el codigo del cliente escriba: *cl /W4 /EHsc ppalClient.cpp ChatUI.cpp ClientChat.cpp ClientHandler.cpp*

## Ejecutar
Debe ejecutar primero ppalServer.exe antes de ppalClient.exe. Abra cuantos CMD desee, uno para el servidor y los demas para clientes


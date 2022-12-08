# ChatSocket
 Aplicacion de comunicacion socket bidireccional cliente-cliente y servidor (chat en vivo)
 
 Para compilar se requiere Microsoft Visual C++ (MSVC) compiler toolset. 
 Puede encontrar una guia de configuracion en https://code.visualstudio.com/docs/cpp/config-msvc

## Compilar
Abra el **Commad Prompt** y dirijase a la carpeta donde descargó el codigo, por ejemplo: *C:\Users\User\Desktop\PruebasC++\testchat\chatsocket*

Para compilar el codigo del servidor escriba: *cl /W4 /EHsc ppalServer.cpp  ServerChat.cpp ChatUI.cpp ServerHandler.cpp ChatData.cpp*

Para compilar el codigo del cliente escriba: *cl /W4 /EHsc ppalClient.cpp ChatUI.cpp ClientChat.cpp ClientHandler.cpp*

Si aparece un mensaje de que no se reconoce el comando **cl** debe abrir la consola **Developer Command Prompt for VS 2019** dirigirse a la carpeta del codigo y ejecutar **code .** (incluyendo el espacio y el punto). Se abrira el VSCode con el entorno de compilacion apropiado.

## Ejecutar
Debe ejecutar primero ppalServer.exe antes de ppalClient.exe. Abra cuantos CMD desee, uno para el servidor y los demas para clientes


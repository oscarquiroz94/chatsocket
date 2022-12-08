#include "ChatData.h"

void ChatData::printData(char *szTypes, ... ){
    FILE *mfile;
    ChatUI chatui;
    errno_t err;
    err = fopen_s(&mfile, _namefile.c_str(), "a");
    
    if (err != 0){
        chatui.printData("s","No se pudo abrir el archivo");
        return;
    }


    time(&t);
    localtime_s(&timeinfo, &t);
    char buffertime[100];
    strftime (buffertime,80,"%x-%X ", &timeinfo);

    fputs(buffertime, mfile);

    va_list vl;
    va_start( vl, szTypes );
    for(int i = 0; szTypes[i] != '\0'; ++i ) {
        union Printable_t {
            int     i;
            float   f;
            char    c;
            char   *s;
        } Printable;

        switch( szTypes[i] ) {   
            case 'i':
                Printable.i = va_arg( vl, int );
                fprintf(mfile, "%i", Printable.i);
            break;

            case 'f':
                Printable.f = va_arg( vl, float );
                fprintf(mfile, "%f", Printable.f);
            break;

            case 'c':
                Printable.c = va_arg( vl, char );
                fprintf(mfile, "%c", Printable.c);
            break;

            case 's':
                Printable.s = va_arg( vl, char * );
                fprintf(mfile, "%s", Printable.s);
            break;

            default:
            break;
        }
    }
    fputs("\n", mfile);
    fclose(mfile);
    va_end( vl );
   
}
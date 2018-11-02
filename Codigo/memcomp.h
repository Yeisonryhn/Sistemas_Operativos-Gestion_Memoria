#ifdef __unix__
    #define OS_Windows 0
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    
#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows 1
    #include <windows.h>
    #include <conio.h>
    #include <tchar.h>

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHARS 100 // Maximos caractes en el mensaje

void esperar(){

    if(OS_Windows){
        system("pause");

    }else if(!OS_Windows){
        printf("\nPulsa enter para continuar...");
        while(getchar()!='\n');

    }
    
}

void limpiar(){

    if(OS_Windows){
        system("cls");

    }else if(!OS_Windows){
        system("clear");

    }

}


int agregar_msg(char *msg){

    if(OS_Windows){

    }else if(!OS_Windows){

    }

return 0;
}

void modificar_msg(int clave, char valor[MAX_CHARS]){

    if(OS_Windows){

    }else if(!OS_Windows){

        // CREO QUE ESTE REALMENTE ES EL "AGREGAR MENSAJE"
        
        char *p;
        int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);

        p = shmat(varComp, NULL, 0);
        strcpy(p, valor);
        shmdt(p);
        

    }

}

char* consultar_msg(int clave){

    if(OS_Windows){

    }else if(!OS_Windows){  

        char *p, valor[MAX_CHARS];
        int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);
        
        p = shmat(varComp,NULL,0);

        if(strcmp(p, "") == 0){
            printf("Sin mensajes...");
        }else{
            printf("%s", p);
        }

        shmdt(p);
        
    }

}

void destruir_msg(int clave){

    if(OS_Windows){

    }else if(!OS_Windows){

        char *p;
        int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);

        p = shmat(varComp,NULL,0);
        strcpy(p, "");
        shmdt(p);

    }

}

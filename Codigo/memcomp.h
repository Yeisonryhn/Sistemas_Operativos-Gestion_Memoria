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


void agregar_msg(int clave, char valor[MAX_CHARS]){

    if(OS_Windows){

    }else if(!OS_Windows){

        char *p;
        int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);

        p = shmat(varComp, NULL, 0);
        strcpy(p, valor);
        shmdt(p);

    }

}

void modificar_msg(int clave){

    if(OS_Windows){

    }else if(!OS_Windows){

        char *p, valor[MAX_CHARS];
        int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);
        
        p = shmat(varComp,NULL,0);

        if(strcmp(p, "") == 0){
            printf("No existen mensajes para modificar...");
            esperar();

        }else{

            if(strstr(p, "(modificado)")){

                // Aqui se deberia partir la cadena, eliminar el segmento "(modificado)" y permitir volver a modificar
                printf("El mensaje ya fue modificado..");
                esperar();

            }else{

                printf("Mensaje a modificar: %s\n", p);
                printf("Modificar: ");
                scanf("%s%*c", valor);
                strcat(valor, " (modificado).");
                strcpy(p, valor);

            }
            
        }

        shmdt(p);

    }

}

void consultar_msg(int clave){

    if(OS_Windows){

    }else if(!OS_Windows){  

        char *p, valor[MAX_CHARS];
        int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);
        
        p = shmat(varComp,NULL,0);

        if(strcmp(p, "") == 0){
            printf("No existen mensajes para consultar...");
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

        if(strcmp(p, "") == 0){
            printf("\nNo existen mensajes para eliminar...");
        }else{
            strcpy(p, "");
            printf("\nMensaje eliminado...");
        }

        shmdt(p);

    }

}

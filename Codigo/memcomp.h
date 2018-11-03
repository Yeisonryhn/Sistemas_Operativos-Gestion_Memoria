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
	
    #elif defined(_WIN32) || defined(WIN32)
        system("pause");

    #ifdef __unix__
        printf("\nPulsa enter para continuar...");
        while(getchar()!='\n');
	#endif
        
}

void limpiar(){

    #elif defined(_WIN32) || defined(WIN32)
        system("cls");

    #ifdef __unix__
        system("clear");

    #endif     

}

//---------------------------------METODO AGREGAR MENSAJE EN LINUX Y WINDOWS-----------------------------------------------------------------------
#ifdef __unix__
void agregar_msg(int clave, char valor[MAX_CHARS]){
	
	//else if(!OS_Windows){

        char *p;
        int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);

        p = shmat(varComp, NULL, 0);
        strcpy(p, valor);
        shmdt(p);

}

#elif defined(_WIN32) || defined(WIN32)
void agregar_msg(char* clave, char valor[MAX_CHARS]){
	
        LPCTSTR p;       
		HANDLE varComp;
		varComp = CreateFileMapping( INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(int),clave);

        if(varComp != NULL){

            p = (LPTSTR) MapViewOfFile(varComp, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
            CopyMemory((PVOID) p, valor, sizeof(TCHAR) * MAX_CHARS);
            UnmapViewOfFile(p);

        }else{
             _tprintf(TEXT("Could not create file mapping object (%d).\n"),GetLastError());
        }
}
#endif

//---------------------------------METODO CONSULTAR MENSAJE EN LINUX Y WINDOWS------------------------------------------------------------------
#ifdef __unix__
void consultar_msg(int clave){

	
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
#elif defined(_WIN32) || defined(WIN32)
void consultar_msg(char clave[MAX_CHARS]){  
		HANDLE varComp;
		varComp = OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, clave);
		printf("funcion");
		if(varComp != NULL){
			
			LPCTSTR p = (LPTSTR) MapViewOfFile(varComp, FILE_MAP_READ, 0, 0, sizeof(TCHAR) * MAX_CHARS);
			printf("El valor actual es %s\n\n", p);
			UnmapViewOfFile(p);
		} }else{
             _tprintf(TEXT("Could not access file mapping object (%d).\n"),GetLastError());
        }
}
        
#endif    

//-------------------------------------LOS OTROS DOS METODOS QUE AUN NO SE HAN ARREGLADO ESTAN AQUI------------------------------------------------
/*
void modificar_msg(int clave){

    if(OS_Windows){


    }else if(!OS_Windows){

        char *p, valor[MAX_CHARS];
        int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666),posicion,i;
        
        p = shmat(varComp,NULL,0);

        if(strcmp(p, "") == 0){
            printf("No existen mensajes para modificar...");
            esperar();

        }else{

            if(strstr(p, "(modificado)")){

                //extrae la posicion de la subcadena
                posicion = strlen( p ) - strlen( strstr( p,"(modificado)" ) );

                //copia en una nueva variable hasta donde está la subcadena
                for(i = 0; i < posicion; i++ ){
                    valor[ i ] = p[ i ];    
                }   
                //agrega el cierre de linea
                valor[ i ] = '\0';
            }else{

                strcpy(valor,p);
            }               

                printf("Mensaje a modificar: %s\n", valor);
                printf("Modificar: ");
                scanf("%[^\n]", valor);//lee cadenas de texto con varias palabras
                strcat(valor, " (modificado).");
                strcpy(p, valor);
        }

        shmdt(p);

    }

}
*/



/*
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

}*/

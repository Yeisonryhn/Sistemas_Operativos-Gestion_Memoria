
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MENSAJE 10      // caracteres maximos para el mensaje compartido
#define edit 15             // caracteres adicionales para el (modificado)

#ifdef __unix__

    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>

    #define MAX_CLAVE 4 

    int convertir(char clave[MAX_CLAVE]){

        char mensaje[MAX_CLAVE + 6], aux[MAX_CLAVE], letra[2];
        static char num [] = "0123456789abcdefghijklmnopqrstuvwxyz";
        int i, j, xClave, xNum;

        xClave = strlen(clave);
        xNum = strlen(num);

        strcpy(mensaje, "");
        for(i=0; i<xClave; i++){
            for(j=0; j<xNum; j++){

                if(clave[i] == num[j]){
                    sprintf(letra, "%i", j);
                    strcat(mensaje, letra);
                }

            }

        }

        return atoi(mensaje);
    }

#elif defined(_WIN32) || defined(WIN32)

    #include <windows.h>
    #include <conio.h>
    #include <tchar.h>

    #define MAX_CLAVE 5
    
#endif

void esperar(){
	
    #ifdef __unix__

        printf("\nPulsa enter para continuar...");
        while(getchar()!='\n');

    #elif defined(_WIN32) || defined(WIN32)
		
		printf("\n");
        system("pause");

	#endif
        
}

void limpiar(){

    #ifdef __unix__

        system("clear");

    #elif defined(_WIN32) || defined(WIN32)

        system("cls");

    #endif     

}


//AGREGAR
void agregar_msg(char key[MAX_CLAVE]){

    char mensaje[MAX_MENSAJE];

    printf("\nIngrese mensaje (maximo de %i caracteres).\n>: ", MAX_MENSAJE);
    fflush(stdin);
    scanf("%[^\n]%*c", mensaje);

    if(strlen(mensaje) > MAX_MENSAJE){
        printf("\nNo se puede enviar un mensaje tan grande...");
        esperar();

    }else{

        #ifdef __unix__

            int clave = convertir(key);
            char *p;
            int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);

            p = shmat(varComp, NULL, 0);
            strcpy(p, mensaje);

            shmdt(p);

        #elif defined(_WIN32) || defined(WIN32)
			
            LPCTSTR p;       
            HANDLE varComp;
            varComp = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int), key);

            if(varComp != NULL){

                p = (LPTSTR)MapViewOfFile(varComp, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
                CopyMemory((PVOID) p, mensaje, sizeof(CHAR) * MAX_MENSAJE);
                UnmapViewOfFile(p);
                
            }else{
                
                _tprintf(TEXT("Could not create file mapping object (%d).\n"), GetLastError());
                
            }
            
        #endif

        printf("\nMensaje agregado...");
        esperar();
        
    }    

}

//CONSULTAR
void consultar_msg(char key[MAX_CLAVE]){
	
	#ifdef __unix__
	
	    int clave = convertir(key);
	    char *p;
	    int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);   

    	p = shmat(varComp,NULL,0);
	
	#elif defined(_WIN32) || defined(WIN32)
		
		LPCTSTR p;
		HANDLE varComp;
	    varComp = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, key);
	    
	    if(varComp != NULL){
            p = (LPTSTR)MapViewOfFile(varComp, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(CHAR) * (MAX_MENSAJE + edit));
         
        }else{
            
            _tprintf(TEXT("\nNo existen mensajes para consultar..."),GetLastError());
            esperar();
            return;
            
        }
	
	#endif
	
	if(strcmp(p, "") == 0){
                
    	printf("\nNo existen mensajes para consultar...");
                
    }else{
        
        printf("** Mensaje **\n%s\n", p);
        
        #ifdef __unix__
        	shmdt(p); 
        #elif defined(_WIN32) || defined(WIN32)
        	UnmapViewOfFile(p);
        #endif
        
    }
	
	esperar();	 

}

//MODIFICAR
void modificar_msg(char key[MAX_CLAVE]){
	
	char mensaje[MAX_MENSAJE], aux[MAX_MENSAJE + edit];
    int posicion, i;
    
    #ifdef __unix__
    	
    	char *p;
        int clave = convertir(key);
        int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);
        
        p = shmat(varComp,NULL,0);
    	
    #elif defined(_WIN32) || defined(WIN32)
    	
		LPCTSTR p;
    	HANDLE varComp = OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, key);
        
        if(varComp != NULL){
            p = (LPTSTR)MapViewOfFile(varComp, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(TCHAR)*(MAX_MENSAJE + edit));
            
        }else{
        	
        	printf("\nNo se puede editar el mensaje...");
	        esperar();
        	return;
		}
		
    #endif
    
    if(strcmp(p, "") == 0){
                
        printf("\nNo existen mensajes para modificar...");
        esperar();
        return;

    }else{
        
        if(strstr(p, "(modificado)")){
            
            posicion = strlen(p) - strlen(strstr(p, "(modificado)"));
            
            for(i=0; i<posicion; i++){
                
                mensaje[i] = p[i];

            }
            
            mensaje[i] = '\0';
            
        }else{
            
            strcpy(mensaje, p);
            
        }
        
    }
    
    while(1){

	    limpiar();
	    printf("NOTA: El nuevo mensaje no debe contener mas de %i caracteres.\n** Mensaje a modificar **\n%s\n\n", MAX_MENSAJE, mensaje);
	    printf("** Modificar **\n>: ");
	    scanf("%[^\n]%*c", aux);  //lee cadenas de texto con varias palabras
	
	    if(strlen(aux) > MAX_MENSAJE){
	        printf("\nNo se puede editar el mensaje...");
	        esperar();
	
	    }else{
	    	
	    	strcat(aux, " (modificado)");
	    	
	    	#ifdef __unix__
	    		
	    		strcpy(p, aux);
	    		shmdt(p);
	    		
	    	#elif defined(_WIN32) || defined(WIN32)
	    		
	    		CopyMemory((PVOID) p, aux, sizeof(CHAR)*(MAX_MENSAJE + edit));
	    		UnmapViewOfFile(p);	
	    	
	    	#endif
	
	        printf("\nEl Mensaje ha sido modificado...");
	        esperar();
	        break;
	        
	    }

	};	
	
}

//ELIMINAR
void destruir_msg(char key[MAX_CLAVE]){
	
	#ifdef __unix__
	
		char *p;
        int clave = convertir(key);
        int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);

        p = shmat(varComp,NULL,0);
		
	#elif defined(_WIN32) || defined(WIN32)
	
		LPCTSTR p;
        HANDLE varComp;		
        varComp = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, key);
        
        if(varComp != NULL){
        	
            p = (LPTSTR) MapViewOfFile(varComp, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(TCHAR)*MAX_CLAVE);
    
        }else{
            
            _tprintf(TEXT("\nNo existen mensajes para eliminar..."), GetLastError());
            esperar();
            return;
            
        }
	
	#endif
	
    if(strcmp(p, "") == 0){

        printf("\nNo existen mensajes para eliminar...");
        
    }else{

        strcpy(p, "");
        printf("\nMensaje eliminado...");
        
        #ifdef __unix__
	    		
    		strcpy(p, "");
    		shmdt(p);
    		
	    #elif defined(_WIN32) || defined(WIN32)
	    		
    		CopyMemory((PVOID) p, "", sizeof(CHAR)*(MAX_MENSAJE + edit));
    		UnmapViewOfFile(p);	
	    	
	   	#endif
    }
    
    esperar();
	
}

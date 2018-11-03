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
	
    #ifdef __unix__
        printf("\nPulsa enter para continuar...");
        while(getchar()!='\n');
    #elif defined(_WIN32) || defined(WIN32)
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

#ifdef __unix__
//-----------------------------------------------------------------------UNIX-----------------------------------------------------------------------
//AGREGAR
void agregar_msg(int clave, char valor[MAX_CHARS]){
	
	char *p;
    int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);
    p = shmat(varComp, NULL, 0);
    strcpy(p, valor);
    shmdt(p);
    printf("Mensaje agregado\n");
    esperar();

}
//CONSULTAR
void consultar_msg(int clave){

	char *p, valor[MAX_CHARS];
    int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);        
    p = shmat(varComp,NULL,0);

    if(strcmp(p, "") == 0){
    	
        printf("No existen mensajes para consultar...\n");
        
    }else{
    	
        printf("%s", p);
        
    }
	
	esperar();
    shmdt(p);  
        
}
//MODIFICAR
void modificar_msg(int clave){  

    char *p, valor[MAX_CHARS];
    int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666),posicion,i;
    p = shmat(varComp,NULL,0);

    if(strcmp(p, "") == 0){
    	
        printf("No existen mensajes para modificar...\n");
        
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
            printf("El Mensaje ha sido modificado: %s\n\n", valor);
            
    }
    
	esperar();
    shmdt(p);
    
}
//ELIMINAR
void destruir_msg(int clave){

    char *p;
    int varComp = shmget((key_t) clave, sizeof(int), IPC_CREAT|0666);
    p = shmat(varComp,NULL,0);
    
    if(strcmp(p, "") == 0){
    	
	    printf("\nNo existen mensajes para eliminar...\n");
	    
    }else{
    	
        strcpy(p, "");
        printf("\nMensaje eliminado...\n");
    }
    
    esperar();
    shmdt(p);
}

#elif defined(_WIN32) || defined(WIN32)
//-----------------------------------------------------------------WINDOWS--------------------------------------------------------------------------
//AGREGAR
void agregar_msg(char* clave, char valor[MAX_CHARS]){
	
    LPCTSTR p;       
	HANDLE varComp;
	varComp = CreateFileMapping( INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(int),clave);

    if(varComp != NULL){

        p = (LPTSTR) MapViewOfFile(varComp, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));
        CopyMemory((PVOID) p, valor, sizeof(TCHAR) * MAX_CHARS);
        UnmapViewOfFile(p);
		printf("Mensaje agregado\n");
		
    }else{
    	
        _tprintf(TEXT("Could not create file mapping object (%d).\n"),GetLastError());
        
    }
    
    esperar();
    
}
//CONSULTAR
void consultar_msg(char clave[MAX_CHARS]){  

	HANDLE varComp;
	varComp = OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, clave);
		
	if(varComp != NULL){
			
		LPCTSTR p = (LPTSTR) MapViewOfFile(varComp, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(TCHAR) * MAX_CHARS);
		
		if(strcmp(p, "") == 0){
			
			printf("No existen mensajes para consultar...\n");
			
		}else{
			
			printf("El valor actual es %s\n\n", p);
			UnmapViewOfFile(p);
			
		}
			
	}else{
		
        _tprintf(TEXT("No existen mensajes para consultar...\n"),GetLastError());
        
    }
    
    esperar();
    
}
//MODIFICAR
void modificar_msg(char clave[MAX_CHARS]){  

	HANDLE varComp;		
	varComp = OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, clave);
	int posicion,i;
	char valor[MAX_CHARS];
	
	if(varComp != NULL){
				
		LPCTSTR p = (LPTSTR) MapViewOfFile(varComp, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(TCHAR) * MAX_CHARS);
		
		if(strcmp(p, "") == 0){
			
	        printf("No existen mensajes para modificar...\n");
	    }else{
	    	
				
			if(strstr(p, "(modificado)")){
				
				posicion = strlen( p ) - strlen( strstr( p,"(modificado)" ) );
				
				for(i = 0; i < posicion; i++ ){
					
	                valor[ i ] = p[ i ];    
	            }
	            
	            valor[ i ] = '\0';
	            
			}else{
				
				strcpy(valor,p);
				
			}
					
			printf("Mensaje a modificar: %s\n\n", valor);
			printf("Modificar: ");
	        scanf("%[^\n]", valor);//lee cadenas de texto con varias palabras
	        strcat(valor, " (modificado).");
	        CopyMemory((PVOID) p, valor, sizeof(TCHAR) * MAX_CHARS);
	        printf("El Mensaje ha sido modificado: %s\n\n", valor);
	        
	    }
	    
		UnmapViewOfFile(p);	
		
	}else{
		
        _tprintf(TEXT("No existen mensajes para modificar...\n"),GetLastError());
        
    }
        
    esperar();
}
//ELIMINAR
void destruir_msg(char clave[MAX_CHARS]){ 
 
	HANDLE varComp;		
	varComp = OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, clave);
	char valor[MAX_CHARS];
	
	if(varComp != NULL){
				
		LPCTSTR p = (LPTSTR) MapViewOfFile(varComp, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(TCHAR) * MAX_CHARS);
		
		if(strcmp(p, "") == 0){
			
			printf("\nNo existen mensajes para eliminar...\n");	
			            
		}else{
			
			strcpy(valor,"");
			
		}
		
		CopyMemory((PVOID) p, valor, sizeof(TCHAR) * MAX_CHARS);
		UnmapViewOfFile(p);	
		esperar();
		
	}else{
		
        _tprintf(TEXT("No existen mensajes para eliminar.\n"),GetLastError());
        esperar();
        
    }
}
#endif

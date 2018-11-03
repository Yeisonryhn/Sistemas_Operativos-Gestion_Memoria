#include "memcomp.h"

#ifdef __unix__
void menu(int clave){
#elif defined(_WIN32) || defined(WIN32)
void menu(char* clave){
#endif
    int r;
    char *msg = malloc(MAX_CHARS);
    char valor[MAX_CHARS];
    int modified;

    do{ 
        
        limpiar();
        printf("MENU");
        printf("\n\n1.- Agregar mensaje.");
        printf("\n2.- Modificar mensaje.");
        printf("\n3.- Ver mensaje.");
        printf("\n4.- Eliminar mensaje.");
        printf("\n0.- Salir.");
        printf("\n\nIngresar la opcion: ");
        setbuf(stdin,NULL);
        scanf("%i%*c", &r);        

        switch(r){

            case 1:
            	
                printf("\n");
                printf("Ingrese mensaje: ");
                setbuf(stdin,NULL);
                scanf("%[^\n]", valor);
                agregar_msg(clave, valor);
                
            break;

            case 2:
            	
                printf("\n");
                modificar_msg(clave);
												
            break;

            case 3:
                
				printf("\n");
                consultar_msg(clave);  
            
			break;

            case 4:
                
				destruir_msg(clave);
            
			break;

            case 0:
            	
                limpiar();
            
			break;

            default:
            	
                limpiar();
                printf("Opcion incorrecta, vuelve a intentarlo.\n");
                esperar();
                
            break;
            
        }        

    }while(r != 0);

}

int main(int argc, char** argv) {

    char clave[20], salas[20][20];
     // Clave identificadora de la sala del chat (en int por el momento)
    printf("Ingresar el nombre de la sala, maximo 20 caracteres: ");
    fflush(stdin);
    scanf("%[^\n]", clave);
    //FALTA ARREGLAR QUE EN LINUX LA CLAVE DE LA MEMORIA COMPARTIDA SEA UNA CADENA 
    //ES POR ESTO QUE AUN SE HACE LO SIGUIENTE
    #ifdef __unix__
    menu(atoi(clave));
    #elif defined(_WIN32) || defined(WIN32)
    menu(clave);
    #endif

	return 0;
}

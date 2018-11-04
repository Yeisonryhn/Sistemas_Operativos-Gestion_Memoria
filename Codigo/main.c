#include "memcomp.h"

void menu(char clave[MAX_CLAVE]){

    int r;
    char valor[MAX_MENSAJE];

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
                agregar_msg(clave);
            break;

            case 2:
                modificar_msg(clave);				
            break;

            case 3:
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
	
    char clave[MAX_CLAVE];

    while(1){

        limpiar();
        printf("Ingresar el nombre de la sala, maximo %i caracteres: ", MAX_CLAVE);
        fflush(stdin);
        scanf("%[^\n]%*c", clave);

        if(strlen(clave) > MAX_CLAVE){
            printf("\nNo se puede crear una sala con un nombre tan grande...");
            esperar();

        }else{
            break;
        }

    };

    menu(clave);

    return 0;
}

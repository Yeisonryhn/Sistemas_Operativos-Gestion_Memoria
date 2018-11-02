#include "memcomp.h"

void menu(int clave){

    int r;
    char *msg = malloc(MAX_CHARS);
    char valor[MAX_CHARS];

    do{ 
        
        limpiar();
        printf("MENU");
        printf("\n\n1.- Agregar mensaje.");
        printf("\n2.- Modificar mensaje.");
        printf("\n3.- Ver mensaje.");
        printf("\n4.- Eliminar mensaje.");
        printf("\n0.- Salir.");

        printf("\n\nIngresar la opcion: ");
        scanf("%i%*c", &r);
        fflush(stdin);

        switch(r){

            case 1:
                limpiar();
                // No entiendo que va aqui, ya que el metodo agregar mensaje, recibe un char *msg y nisiquiera recibe la clave
                esperar();
            break;

            case 2:
                //limpiar();
                printf("\n");
                printf("Ingrese mensaje: ");
                scanf("%s%*c", valor);
                modificar_msg(clave, valor);
            break;

            case 3:
                //limpiar();
                printf("\n");
                consultar_msg(clave);  
                esperar();     
            break;

            case 4:
                //limpiar();
                destruir_msg(clave);
                printf("\n");
                printf("Mensaje eliminado...");
                esperar();    
            break;

            case 0:
                limpiar();
                //printf("Saliendo del programa.\n");
                //esperar();
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

    int clave; // Clave identificadora de la sala del chat (en int por el momento)
    printf("Ingresar el identificador de la sala (numero entero): ");
    scanf("%i%*c", &clave);
    fflush(stdin);

    menu(clave);

	return 0;
}
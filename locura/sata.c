/*programa   : sata.c
 *descripcion: contiene las funciones y procedimientos necesarios para el juego
 *autor(es)  : juan sebastián rojas garcia, ivan alexander cardona rodrigues
 *fecha      : febrero 2021
 *licencia   : GNU GPL v3
 */
#include<stdio.h>
#include<stdlib.h>
#include"uniquindio.h"
//declaración de prototipos
int eleccionMenuI();
void imprimirMenu();
//main temporal(ya que se hará en python
int main()
{
    eleccionMenuI();
    return 0;
}

//----------------------------------------------MENU DEL JUEGO-----------------
//funcion que imprime el menú del juego
//return: retorna la decición tomada por el usuario como un entero
int eleccionMenuI()
{
    int  error=0;
    char eleccion;
    do
    {
	clrscr();
	imprimirMenu();
	eleccion=leerCaracter("ingrese el caracter");
	if(eleccion<49 || eleccion>51)
	{
	    printf("el número vale mondá2");
	}
    }while(eleccion<49 || eleccion>51); 
    return 0;
}
void imprimirMenu()
{
    printf("sissas");
}

	    
    


/* 
 * Programa   : uniquindio.h
 * Descripción: Prototipos de la biblioteca uniquindio.h.
 * Autor      : Julián E. Gutiérrez P.
 * Fecha      : Abril 2020
 * Licencia   : GNU GPL v3
 */

 // Prototipos de las funciones / procedimientos

#ifndef UNIQUINDIO

  #define UNIQUINDIO

  int   leerEntero         ( char pregunta[] );
  float leerReal           ( char pregunta[] );
  char  leerCaracter       ( char pregunta[] );
  void  leerCadena         ( char pregunta[], char *cadena, int longitud );
 

  void  imprimirEntero     ( char texto[], int valor     );
  void  imprimirReal       ( char texto[], float valor   );
  void  imprimirCaracter   ( char texto[], char caracter );
  void  imprimirCadena     ( char texto[], char cadena[] );

  int   sumarEnteros       ( int n1, int n2 );
  int   multiplicarEnteros ( int n1, int n2 );
 
  void          clrscr     ( );  
  unsigned char getch      ( );
  void          gotoxy     ( int x, int y   );
  void          getString  ( unsigned char *cadena, int longitud );

#endif



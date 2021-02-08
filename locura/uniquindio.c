/* 
 * Programa   : uniquindio.c
 * Descripción: Implementación de la biblioteca uniquindio.h.
 * Autor      : Julián E. Gutiérrez P.
 * Fecha      : Abril 2020
 * Licencia   : GNU GPL v3
 */
 
 #include <stdio.h>

// Se verifica si el sistema operativos es Windows de 32 o 64 bits

#if defined(_WIN64) || defined(_WIN32) 

	#include <windows.h> 

    /*
     * Procedimiento para borrar la pantalla.
     */ 
	void clrscr ( )
	{
		DWORD w;
		CONSOLE_SCREEN_BUFFER_INFO pantalla;

		COORD esquina  = { 0, 0 };
		HANDLE consola = GetStdHandle( STD_OUTPUT_HANDLE );
		
        GetConsoleScreenBufferInfo( consola, &pantalla );
        
        FillConsoleOutputCharacterA(
                                      consola, 
                                      ' ', 
                                      pantalla.dwSize.X * pantalla.dwSize.Y, 
                                      esquina, &w
                                   );
                                   
		FillConsoleOutputAttribute (
			                          consola, 
			                          FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			                          pantalla.dwSize.X * pantalla.dwSize.Y, 
			                          esquina, &w
								   );
									
		SetConsoleCursorPosition   ( consola, esquina );
	}
	
	
   /*
    * Función para ubicar el cursos en una posición de la pantalla
    * param:  coordinadas x/y en la pantalla.
    */ 
	void gotoxy( int x, int y )
	{
		COORD c;
		
		c.X = x;
		c.Y = y;
		
		SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );
	}


   /*
    * Función para leer una tecla sin necesidad de presionar ENTER y sin eco
    * return: Código ASCII de la tecla presionada
    */ 	 	
	unsigned char getch() 
	{
		TCHAR  c = 0;
		DWORD  mode, cc;
		HANDLE h;
		
		h = GetStdHandle( STD_INPUT_HANDLE );
		
		if (h != NULL) 
		{
			GetConsoleMode( h, &mode );
			SetConsoleMode( h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT) );
			ReadConsole   ( h, &c, 1, &cc, NULL );
			SetConsoleMode( h, mode );
		}
		
		return (unsigned char)c;
	}

    

#else
    // No es Windows, se asume que es un Unix o similar

	#include <termios.h>

    /*
     * Procedimiento para borrar la pantalla.
     */ 
	void clrscr()
	{
		printf ( "\033[2J\033[0;0f" );
	}
	
	
   /*
    * Función para ubicar el cursos en una posición de la pantalla
    * param:  coordinadas x/y en la pantalla.
    */ 
	void gotoxy( int x, int y )
	{
		printf ( "\e[%d;%df", y, x );
	}
	
	
   /*
    * Función para leer una tecla sin necesidad de presionar ENTER y sin eco
    * return: Código ASCII de la tecla presionada
    */ 		
	unsigned char getch()
	{
		unsigned char   c;
		struct termios viejo, nuevo;
		
		tcgetattr ( 0, &viejo ); 
		nuevo          = viejo; 
		nuevo.c_lflag &= ~ICANON;  
        nuevo.c_lflag &= ~ECHO; 
  
        tcsetattr( 0, TCSANOW, &nuevo ); 
        
        c = getchar();
        
		tcsetattr( 0, TCSANOW, &viejo );
		
		return c;
	}

#endif


/*
 * Procedimiento para leer una cadena bloqueando en el máximo de cacteres.
 * param:  Dirección de la variable en donde se almacena la cadena ingresada
 *         Longitud máxima de la cadena a leer
 */ 
void getString ( unsigned char *cadena, unsigned long longitud )
{
    unsigned char tecla;
    int  i, j;
    
    i     = 0;
    j     = 0;
    tecla = '\0';

    longitud--;
    
    do
    {
       tecla = getch();
       
       if ( j == 0 && (tecla == '\n' || tecla == '\r')) 
       { 
            tecla = getch(); 
       }
       j = 1;
       
       if ( tecla != 127 &&  tecla != 8 )
       {
            if ( tecla >= 32 && i < longitud )
            {
                printf("%c", tecla );
                cadena [ i ] = tecla;
                i++;
            }
            else
            {
                printf ("\a");
            }
       }
       else
       {
            i--;
            
            if ( i < 0 )
            {
                printf ("\a");
                i = 0;
            }
            else
            {
                printf("\b \b");
            }
        
       }
    } while ( tecla != '\n' && tecla != '\r' );
    
    printf ( "\n" );
    tecla = '\0';
    cadena [ i ] = tecla;
}


/*
 * Función para leer un número entero
 * param:  Texto que se emplea como pregunta para el usuario
 * return: Valor entero ingresado por el usuario
 */ 
int leerEntero ( char pregunta[] )
{
	int valor;
	
	printf ( "%s",   pregunta );
	scanf  ( "%d%*c", &valor   );
	
	return valor; 
}


/*
 * Función para leer un número real (float)
 * param:  Texto que se emplea como pregunta para el usuario
 * return: Valor real ingresado por el usuario
 */ 
 float leerReal ( char pregunta[] )
 {
	float valor;
	
	printf ( "%s",   pregunta );
	scanf  ( "%f%*c", &valor   );
	
	return valor; 
}


/*
 * Función para leer un caracter
 * param:  Texto que se emplea como pregunta para el usuario
 * return: Caracter ingresado por el usuario
 */ 
char leerCaracter ( char pregunta[] )
{
	char caracter;
	
	printf ( "%s",   pregunta );
	scanf  ( "%c%*c", &caracter );
	
	return caracter; 
}

/*
 * Procedimiento para leer una cadena
 * param:  Texto que se emplea como pregunta para el usuario
 * return: Cadena ingresada por el usuario
 */ 
void leerCadena ( char pregunta[], char *cadena, unsigned long longitud )
{
	printf    ( "%s", pregunta   );
	getString ( cadena, longitud );
}
 
/*
 * Función para sumar dos números enteros
 * param:  Dos enteros a sumar
 * return: Valor entero resultado de sumar los enteros
 */ 
int sumarEnteros ( int n1, int n2  )
{
	int sumaEntero;
	
    sumaEntero = n1 + n2;
	
	return sumaEntero; 
}

/*
 * Procedimiento para imprimir un texto acompañado de un número entero
 * param: Texto que se desea imprimir
 *        Valor entero a imprimir al lado del texto ingresado 
 */ 
void imprimirEntero ( char texto[], int valor )
{
	printf ( "%s %d\n", texto, valor );
}

/*
 * Procedimiento para imprimir un texto acompañado de un número real
 * param: Texto que se desea imprimir
 *        Valor entero a imprimir al lado del texto ingresado 
 */ 
void imprimirReal ( char texto[], float valor )
{
	printf ( "%s %.2f\n", texto, valor );
}

/*
 * Procedimiento para imprimir un texto acompañado de un caracter
 * param: Texto que se desea imprimir
 *        Caracter a imprimir al lado del texto ingresado 
 */ 
void imprimirCaracter ( char texto[], char caracter )
{
	printf ( "%s %c\n", texto, caracter );
}

/*
 * Procedimiento para imprimir un texto acompañado de una cadena
 * param: Texto que se desea imprimir
 *        Cadena a imprimir al lado del texto ingresado
 */ 
void imprimirCadena ( char texto[], char cadena[]  )
{
	printf ( "%s %s\n", texto, cadena);
}

/*
 * Función para multiplicar dos números enteros
 * param:  Dos enteros a multiplicar
 * return: Valor entero resultado de multiplicar los enteros
 */ 
int multiplicarEnteros ( int n1, int n2  )
{
	int sumaEntero;
	
    sumaEntero = n1 * n2;
	
	return sumaEntero; 
}

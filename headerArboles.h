#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <windows.h>



#include <stdio.h>
#include <stdlib.h>
#include  <time.h>
#include <string.h>
#include "headerArboles.h"
#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string)   "\x1b[31m" string "\x1b[0m"
#define BLUE(string)  "\x1b[34m" string "\x1b[0m"
#define YEL(string)   "\x1b[33m" string "\x1b[0m"
#define MAG(string)   "\x1b[35m" string "\x1b[0m"
#define CYAN(string)  "\x1b[36m" string "\x1b[0m"

typedef struct {
    char nombre[20];
    char apellido[20];
    int edad;
    char dni[20];
    int anio,division;
    int diaA,mesA,anioA,diaC,mesC,anioC; //lo usamos para saber la fecha de la cuota a vencer, fecha de alta y baja
}stAlumno;

typedef struct{

    char nombre[20];
    char apellido[20];
    int edad;
    char materia[20];
    char dni[20];
    int anio;
    int division;
    int baja; ///0:inactivo, 1:activo
    int diaA,mesA,anioA;

}stDocente;


typedef struct nodoArbolDocente{
    stDocente docente;
    struct  nodoArbolDocente *izq;           //en el arbol tengo toda la informacion de los  docentes
    struct nodoArbolDocente *der;
}nodoArbolDocente;


typedef struct nodoAlumno
{
 stAlumno alumno;
  struct nodoAlumno* siguiente;
} nodoAlumno;



typedef struct celdaCursosAlumnos
{
    int anio,division;
    nodoAlumno* listaAlumnos;
}celdaCursosAlumnos;

typedef struct celdaCursosDocentes
{
    int anio,division;
    nodoArbolDocente * arbolDocentes;
}celdaCursosDocentes;



typedef struct listaDeudores{
    int anio,division;
    struct nodoAlumno *alumno;
    struct listaDeudores *sig;
}listaDeudores;


///funciones menu
void menu_principal(char alumnos[],char docentes[]) ;
void menu_administracion_docentes(char alumnos[],char docentes[]);
int control_menu_opcion(int cant_opciones);
////////////////////////TDA ADA////////////////////////
int pasarArchivoToADA(celdaCursosDocentes B[],int dimension,int validos,char docentes[]);
int altaDocentes(celdaCursosDocentes B[],int validos,stDocente aux);
nodoArbolDocente* crearNodoArbol(stDocente aux);
int buscaPosicionDocente(celdaCursosDocentes B[],int validos,int anio, int division);
int agregarCurso(celdaCursosDocentes B[],int validos,int anio,int division);
nodoArbolDocente* inicArbol();
nodoArbolDocente* insertarNodo(nodoArbolDocente* arbol, nodoArbolDocente* nuevoNodo);
///mostrar arreglo de arboles
void mostrarADA(celdaCursosDocentes B[], int validos);
void inOrder(nodoArbolDocente* arbol);
void mostrarDocente(stDocente aux);
////carga DOcente
int cargaDocente(celdaCursosDocentes B[],int validos,int dimension);//
stDocente cargaDatosDocentes();
int  buscaArbolDni(nodoArbolDocente * arbol, char dni[]);
int   buscaADA(celdaCursosDocentes B[],int validos, char dni[]);
//////baja docente
void bajaDocente(celdaCursosDocentes B[],int validos);
void borrarNodoArbol(nodoArbolDocente *arbol,char dni[]);
/////////Consulta un Docente
void consultaDocente(celdaCursosDocentes B[],int validos);
void infoDocente(nodoArbolDocente  *arbol,char dni[]);
////modifica Docente
int modificaDocente(celdaCursosDocentes  A[],int validos,int dimension);
///Guardar datos

void  guardarDocentes(celdaCursosDocentes B[],int validos,char docentes[]);
void guardarArbol(nodoArbolDocente *arbol,char docentes[]);
void salvarDocente(stDocente docente,char docentes[]);




#endif // HEADER_H_INCLUDED

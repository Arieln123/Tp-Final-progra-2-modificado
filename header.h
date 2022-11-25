#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include<windows.h>
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
    int anio[10];
    int division[10];
    int cantCursos;
    int diaA,mesA,anioA;

}stDocente;


typedef struct nodoArbolDocente{
    stDocente docente;
    struct  nodoArbolDocente *izq;           //en el arbol tengo toda la informacion de los  y docentes
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
    nodoArbolDocente *listaDocentes;
}celdaCursosDocentes;



typedef struct nodoAlumnoDoble
{
 stAlumno alumno;
  struct nodoAlumnoDoble* sig;
  struct nodoAlumnoDoble* ant;
} nodoAlumnoDoble;




typedef struct celdaDeudores{
    int anio,division;
    nodoAlumnoDoble *listaD;
}celdaDeudores;








///Menú.

void menu_principal(char alumnos[],char docentes[]); /// MENU PRINCIPAL
int control_menu_opcion(int cant_opciones); ///CONTROLA LA SELECCION DEL MENU
void menu_administracion_alumnos(char alumnos[],char docentes[]); ///MENU DE ADMINISTRACION DE Alumnos

void menu_administracion_docentes(char alumnos[],char docentes[]);

////menu alumnos///
int  pasarArchivoToADL(celdaCursosAlumnos arreglo[],int dimension,int validos,char alumnos[]);

//carga de arreglo de listas
int altaAlumnos(celdaCursosAlumnos a[],int validos,stAlumno aux);
int buscaPosicionAlumno(celdaCursosAlumnos A[],int validos,int anio, int division);

int agregarCursoAlumnos(celdaCursosAlumnos B[],int validos,int anio,int division);
nodoAlumno * inicListaAlumno();
nodoAlumno* crearNodoAlumno(stAlumno alumno);
nodoAlumno* agregarAlFinalAlumno(nodoAlumno* lista, nodoAlumno* nuevoNodo);
nodoAlumno* buscarUltimoAlumno(nodoAlumno* lista);


////////Mostrar ADL/////////
void mostrarADL(celdaCursosAlumnos A[],int validos);
void mostrarListaAlumnos(nodoAlumno* lista);
void mostrarUnAlumno(stAlumno auxAlumno);


/////////Carga De Alumno
int cargaAlumno(celdaCursosAlumnos A[],int validos,int dimension);
stAlumno cargaDatosAlumno(celdaCursosAlumnos A[],int validos);
int buscaADL(celdaCursosAlumnos A[],int validos, char dni[]);

int  buscaListaDni(nodoAlumno * lista, char dni[]);

//////////////Baja Alumno
void bajaAlumno(celdaCursosAlumnos A[],int validos);
nodoAlumno * borrarNodoAlumnos(nodoAlumno * lista, char dni[]);

// modificacion del alumno
int modificaAlumno(celdaCursosAlumnos  A[],int valido,int dimension);

void consultaAlumno(celdaCursosAlumnos A[],int validos);
void infoAlumno(nodoAlumno  *lista,char dni[]);
stAlumno copiarDatos(nodoAlumno *lista,char dni[]);
stAlumno cargaDatosModificados(stAlumno auxAlumno);

//////////////arreglo Deudores
void listaAlumnosDeudores(celdaDeudores D[],celdaCursosAlumnos A[],int validos);
nodoAlumnoDoble *inicListaD();
nodoAlumnoDoble * crearNodoDoble (stAlumno dato);
nodoAlumnoDoble * agregarPpioDoble (nodoAlumnoDoble * lista, nodoAlumnoDoble * nuevo);

////mostrar lista de lista con deudores
void   mostrarDeudores(celdaDeudores D[],int validos);
void mostrarListaDeudores(nodoAlumnoDoble *lista );
////////////Pagar deuda////
int   pagarDeuda(celdaDeudores D[],celdaCursosAlumnos A[],int validos);
nodoAlumnoDoble *borrarNodoDoble(nodoAlumnoDoble *lista,char dni[]);




////salvar datos
void  guardarAlumnos(celdaCursosAlumnos A[],int validos,char alumnos[]);




#endif // HEADER_H_INCLUDED

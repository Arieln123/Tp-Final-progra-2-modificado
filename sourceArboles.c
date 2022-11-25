#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headerArboles.h"
#include "header.h"






void menu_administracion_docentes(char alumnos[],char docentes[]) ///MENU DE ADMINISTRACION DE DOCENTES
{
    int dimension=40;
    celdaCursosDocentes B[40];
    int validos=0;
    int control=0;
    validos=pasarArchivoToADA(B,validos,dimension,docentes);
    do
    {
        system("cls");
        /// Menu Administracion de Docentes
        printf("Menu Administracion de docentes: \n\n");
        printf(GREEN("1] Alta docente \n"));
        printf(RED("2] Baja docente \n"));
        printf(BLUE("3] Modifica Docente\n"));
        printf(MAG("4] Consulta un Docente \n"));
        printf(YEL("5] Listado de Docentes \n\n"));
        printf("0] Volver al menu Principal \n\n");
        printf("OPCION: ");

        int cant_opciones = 6;


        ///Listado de opciones disponibles en el menu.

        switch(control=control_menu_opcion(cant_opciones))
        {
        case 1 :
            validos=cargaDocente(B,validos,dimension);
            system("PAUSE");
            break;
        case 2 :
            bajaDocente(B,validos);
            system("cls");
            break;
        case 3 :
            validos=modificaDocente(B,validos,dimension);
            system("cls");
            break;
        case 4 :
            consultaDocente(B,validos);

            system("cls");
            break;
        case 5 :
            mostrarADA(B,validos);
            system("cls");
            break;

        case 0 :
            guardarDocentes(B,validos,docentes);
            menu_principal(alumnos,docentes);
            system("cls");
            break;
        }
    }
    while(control!=0);
}


//////////////////////////////TDA ADA/////////////////////////////////

int pasarArchivoToADA(celdaCursosDocentes B[],int validos,int dimension,char docentes[])
{

  FILE *archDocentes;
  archDocentes=fopen(docentes,"rb");


  stDocente auxDocente;
    if(archDocentes)
        {
        while(fread(&auxDocente,sizeof(stDocente),1,archDocentes)>0 && validos<dimension )
        {
            validos=altaDocentes(B,validos,auxDocente);
        }
        fclose(archDocentes);

    }
    else{
        printf("Error al abrir el archivo Docentes \n");
    }


return validos;

}



int altaDocentes (celdaCursosDocentes B[],int validos,stDocente aux)
{
    int pos=buscaPosicionDocente(B,validos,aux.anio,aux.division);

    if(pos==-1)
    {
        validos=agregarCurso(B,validos,aux.anio,aux.division);
        pos=validos-1;
    }
    nodoArbolDocente* nuevo=crearNodoArbol(aux);
    B[pos].arbolDocentes=insertarNodo(B[pos].arbolDocentes,nuevo);

    return validos;
}

nodoArbolDocente* crearNodoArbol(stDocente aux)
{
    nodoArbolDocente* nuevo=(nodoArbolDocente*) malloc(sizeof(nodoArbolDocente));
    nuevo->docente=aux;
    nuevo->izq=NULL;
    nuevo->der=NULL;

    return nuevo;
}


int buscaPosicionDocente(celdaCursosDocentes B[],int validos,int anio, int division)
{
    int pos=-1;
    int i=0;

    while(i<validos && pos==-1)
    {
        if((B[i].anio==anio) && (B[i].division==division))
            pos=i;
        i++;
    }

    return pos;
}

int agregarCurso(celdaCursosDocentes B[],int validos,int anio,int division)
{
    B[validos].anio=anio;
    B[validos].division=division;
    B[validos].arbolDocentes=inicArbol();
    validos++;

    return validos;
}

nodoArbolDocente* inicArbol()
{
    return NULL;
}

nodoArbolDocente* insertarNodo(nodoArbolDocente* arbol, nodoArbolDocente* nuevoNodo)
{
    if(!arbol || strcmp(nuevoNodo->docente.dni,arbol->docente.dni)==0)
        arbol=nuevoNodo;
    else
    {
        if(strcmp(nuevoNodo->docente.dni,arbol->docente.dni)>0)
            arbol->der=insertarNodo(arbol->der,nuevoNodo);
        else
            arbol->izq=insertarNodo(arbol->izq,nuevoNodo);
    }
    return arbol;
}



///////////////////CArgar un nuevo docente/////////////////////////

int cargaDocente(celdaCursosDocentes B[],int validos,int dimension)
{
    int control=0;
    stDocente auxDocente;
    while(control==0 && validos<dimension){
        auxDocente=cargaDatosDocentes();
        validos=altaDocentes(B,validos,auxDocente);
        system("cls");
        printf("Desea cargar otro docente? 1-No/ 0-Si \n");
        scanf("%i",&control);
    }
        system("cls");

return validos;
}


stDocente cargaDatosDocentes()
{
    stDocente docente;
    int control=0;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);

    while(control==0)
    {
        system("cls");
        printf(GREEN("\t\tCARGA DE DOCENTE\n"));
        printf(GREEN("---CARGA DE DATOS ---\n"));
        printf("Ingrese DNI del Docente: \n");
        fflush(stdin);
        scanf("%s",docente.dni);

          printf("Ingrese nombre del Docente: \n");
        fflush(stdin);
        scanf("%s",docente.nombre);
        printf("Ingrese apellido del Docente:\n");
        fflush(stdin);
        scanf("%s",docente.apellido);
        printf("Ingrese edad del Docente: \n");
        scanf("%i",&docente.edad);
        printf("Ingrese materia del Docente: \n");
        fflush(stdin);
        scanf("%s",docente.materia);
        printf("Ingrese anio donde enseña: \n");
        scanf("%i",&docente.anio);
        printf("Ingrese Division donde ensenia: \n");
        scanf("%i",&docente.division);
        docente.baja=1;
        docente.diaA=tm->tm_mday;
        docente.mesA=tm->tm_mon+1;
        docente.anioA=1900+tm->tm_year;
        system("cls");
        printf("LOS DATOS SON \n");
        printf("Nombre y Apellido:%s %s \nEdad: %i \nDNI: %s \nAnio y Division:%i-%i\n",docente.nombre,docente.apellido,docente.edad,docente.dni,docente.anio,docente.division);
        printf("Fecha de alta %i /%i /%i\n",docente.diaA,docente.mesA,docente.anioA);
        printf("Desea Volver a cargar los datos  1-No/ 0-Si \n");
        scanf("%d",&control);




    }
  return docente;
}


///////////////////////////////Baja de docente//////////////////////////////////////////
int   buscaADA(celdaCursosDocentes B[],int validos, char dni[])
{
    int i=0;
    int control=-1;
    while(i<validos && control==-1)
    {
       int encontrado=buscaArbolDni(B[i].arbolDocentes,dni);
       if(encontrado ==0)
         control=i;
       i++;
    }



return control;
}

int  buscaArbolDni(nodoArbolDocente * arbol, char dni[])
{
    int control=1;
    if(arbol)
    {
        if(strcmp(dni, arbol->docente.dni)==0)
        {
            control=0;
        }
        else
        {
            if(strcmp(dni, arbol->docente.dni)>0)
              control=buscaArbolDni(arbol->der,dni);
            if(control==1)
                control=buscaArbolDni(arbol->izq,dni);
        }
    }

    return control;
}

//////////////////////////////Baja Docente//////////////////////
void bajaDocente(celdaCursosDocentes B[],int validos)
{
    char dni[20];
    int control=1;
    int i=0;
    printf("Ingrese el dni del docente a "RED( "eliminar \n"));
    fflush(stdin);
    scanf("%s",dni);

    while(i<validos && control==1)
    {
        control=buscaArbolDni(B[i].arbolDocentes,dni);
        if(control==0){
          borrarNodoArbol(B[i].arbolDocentes,dni);
        }

        i++;
    }

    if(control==1){
        printf("El DNI ingresado"RED(" no ") "es valido\n");
        system("pause");
    }
    else{
        printf("El docente fue dado de baja" GREEN(" exitosamente \n"));
        system("pause");

    }


}



void borrarNodoArbol(nodoArbolDocente *arbol,char dni[]){

   if(arbol)
    {
        borrarNodoArbol(arbol->izq,dni);
        if( strcmp(arbol->docente.dni,dni)==0){
          arbol->docente.baja=0;
        }

        borrarNodoArbol(arbol->der,dni);
    }
}




///////////////////////////////Mostrar ADA/////////////////////////////////////////////

void mostrarADA(celdaCursosDocentes B[], int validos)
{
    int i=0;

    while(i<validos)
    {
        printf("\n----------------------------------------------------------\n");
        printf(YEL("\t\t\t\t Docentes %i-%i\n"),B[i].anio,B[i].division);
        printf("----------------------------------------------------------\n");
        inOrder(B[i].arbolDocentes);
        i++;
    }
    system("pause");
}

void inOrder(nodoArbolDocente* arbol)
{
    if(arbol)
    {
        inOrder(arbol->izq);
        mostrarDocente(arbol->docente);
        inOrder(arbol->der);
    }
}

void mostrarDocente(stDocente aux)
{
    if(aux.baja==1){
        printf("Nombre: %s   ",aux.nombre);
        printf("Apellido: %s ",aux.apellido);
        printf("Materia: %s  ",aux.materia);
        printf("Dni: %s   ",aux.dni);
        printf("Fecha de alta: %d/%d/%d\n",aux.diaA,aux.mesA,aux.anioA);
    }

}

////////////Consulta un docente

void consultaDocente(celdaCursosDocentes B[],int validos){

    int i=0;
    int control=1;
    char dni[20];
    printf("\t\t "MAG(" CONSULTA \n") );
    printf("Ingrese el Dni del Docente para buscar sus datos\n");
    fflush(stdin);
    scanf("%s",dni);
    while(i<validos && control==1){
        control=buscaArbolDni(B[i].arbolDocentes,dni);
        if(control==0){
            system("cls");
            printf("\t\t " MAG("LOS DATOS SON ") "\n");
            infoDocente(B[i].arbolDocentes,dni);
        }

    i++;
    }
    if(control==1){
        printf("El DNI ingresado" RED(" NO ") " es valido \n");
        system("pause");
        }


}

void infoDocente(nodoArbolDocente  *arbol,char dni[]){




    if(arbol)
    {
        infoDocente(arbol->izq,dni);
       if( strcmp(dni, arbol->docente.dni)==0 ){
            if(arbol->docente.baja==1){
               mostrarDocente(arbol->docente);
                system("pause");
            }
            else{
                printf("El Docente Fue dado de" RED(" BAJA ")"\n");
                system("pause");
            }


       }
        infoDocente(arbol->der,dni);
    }


}

/////////////////modifica docente
int modificaDocente(celdaCursosDocentes  B[],int validos,int dimension){

    char dni[20];
    int control=1;
    stDocente auxDocente;

    while(validos<dimension && control==1){
            system("cls");
            printf("Ingrese el DNI del Docente para" BLUE (" MODIFICAR ") "los datos\n");
            fflush(stdin);
            scanf("%s",dni);
            control=buscaADA(B,validos,dni);
            if(control!=-1){
               infoDocente(B[control].arbolDocentes,dni);
               borrarNodoArbol(B[control].arbolDocentes,dni);
            }
        if(control!=-1){
            system("cls");
            auxDocente=cargaDatosDocentes();
            validos=altaDocentes(B,validos,auxDocente);
            control=0;
        }
        else{
            printf("El DNI ingresado" RED(" NO ") " es valido \n");
            printf("Ingresar DNI de nuevo  1-SI / 0-No\n");
            scanf("%i",&control);

        }

    }
return validos;

}

///////////////Salvar Docentes
void  guardarDocentes(celdaCursosDocentes B[],int validos,char docentes[]){

FILE *arch;
    arch=fopen(docentes,"w+b");

    for(int i=0;i<validos;i++){
        nodoArbolDocente *seg=B[i].arbolDocentes;
        guardarArbol(seg,docentes);

    }
  fclose(arch);

}

void guardarArbol(nodoArbolDocente *arbol,char docentes[]){


   if(arbol){

        guardarArbol(arbol->izq,docentes);
        if(arbol->docente.baja==1){
            salvarDocente(arbol->docente,docentes);

        }
        guardarArbol(arbol->der,docentes);
    }

}


void salvarDocente(stDocente docente,char docentes[]){

    FILE *arch;
    arch=fopen(docentes,"a+b");
    stDocente aux=docente;
    fwrite(&aux, sizeof(stDocente), 1, arch);

fclose(arch);
}

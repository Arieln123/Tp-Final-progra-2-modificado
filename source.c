#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#include "headerArboles.h"



///Menú.

void menu_principal(char alumnos[],char docentes[])  /// MENU PRINCIPAL
{




    system("cls");
    printf("Menu Principal: \n\n");
    printf("1] Administracion de alumnos \n");
    printf("2] Administracion de docentes \n");
    printf("0] Salir del programa. \n\n");
    printf("OPCION: ");
    int cant_opciones = 3;

    ///Listado de opciones disponibles en el menu.

    switch(control_menu_opcion(cant_opciones))
    {
    case 1 :
        menu_administracion_alumnos(alumnos,docentes);
        break;

    case 2 :
        menu_administracion_docentes(alumnos,docentes);
        break;
    case 0 :
        exit(0);
        break;
    }
}

int control_menu_opcion(int cant_opciones) ///CONTROLA LA SELECCION DEL MENU
{
    int menu_opcion;
    int exito=0;

    do
    {
        fflush(stdin);
        scanf("%d", &menu_opcion);

        if (menu_opcion < 0 || menu_opcion > cant_opciones-1)
        {
            printf("La opcion seleccionada "RED(" No ") "es valida\n");
        }
        else
        {
            exito=1;
        }
    }
    while ( exito == 0);

    system("cls");
    return menu_opcion;
}






void menu_administracion_alumnos(char alumnos[],char docentes[]) ///MENU DE ADMINISTRACION DE CLIENTES
{
    int control;

    int validos=0;
    int dimension=10;
    celdaCursosAlumnos  A[dimension];
    validos=pasarArchivoToADL(A,dimension,validos,alumnos);

    celdaDeudores D[dimension];
    listaAlumnosDeudores(D,A,validos);

    do
    {

        /// Menu Administracion de Alumnos
        printf("Men%c Administraci%cn de Alumnos: \n\n", 163, 162);
        printf(GREEN("1] Alta Alumno \n"));
        printf(RED("2] Baja Alumno \n"));
        printf(BLUE("3] Modificacion Alumno \n"));
        printf(MAG("4] Consulta \n"));
        printf(YEL("5] Listado de Alumnos\n"));
        printf(YEL("6] Listado de Alumnos con deudas\n"));
        printf(CYAN("7] Pagar Deuda\n"));
        printf("0] Volver al menu Principal \n\n");
        printf("OPCION: ");

        int cant_opciones = 8;

        ///Listado de opciones disponibles en el menu.

        switch(control=control_menu_opcion(cant_opciones))
        {
        case 1 :
                validos=cargaAlumno(A,validos,dimension);
                system("cls");
            break;
        case 2 :
                bajaAlumno(A,validos);
                system("cls");
            break;
        case 3 :
                validos=modificaAlumno(A,validos,dimension);
                system("cls");
            break;
        case 4 :
               consultaAlumno(A,validos);
                system("cls");
            break;
        case 5 :
            mostrarADL(A,validos);
            system("cls");
            break;
        case 6 :
            mostrarDeudores(D,validos);
            system("cls");
            break;
        case 7 :
            validos=pagarDeuda(D,A,validos);
            system("cls");
            break;
        case 0 :
            guardarAlumnos(A,validos,alumnos);
            menu_principal(alumnos,docentes);
            system("cls");
            break;
        }
    }
    while(control!=0);
}


int  pasarArchivoToADL(celdaCursosAlumnos A[],int dimension,int validos,char alumnos[]){


  FILE *archAlumnos;
  archAlumnos=fopen(alumnos,"rb");


  stAlumno   auxAlumno;
    if(archAlumnos){
        while(fread(&auxAlumno,sizeof(stAlumno),1,archAlumnos)>0 && validos<dimension ){
            validos=altaAlumnos(A,validos,auxAlumno);


        }
        fclose(archAlumnos);

    }
    else{
        printf("Error al abrir el archivo Alumnos \n");
    }



return validos;


}




int altaAlumnos(celdaCursosAlumnos A[],int validos,stAlumno aux)
{
    int pos=buscaPosicionAlumno(A,validos,aux.anio,aux.division);

    if(pos==-1)
    {
        validos=agregarCursoAlumnos(A,validos,aux.anio,aux.division);
        pos=validos-1;
    }
    nodoAlumno* nuevo=crearNodoAlumno(aux);
    A[pos].listaAlumnos=agregarAlFinalAlumno(A[pos].listaAlumnos,nuevo);

    return validos;
}


int buscaPosicionAlumno(celdaCursosAlumnos A[],int validos,int anio, int division)
{
    int pos=-1;
    int i=0;

    while(i<validos && pos==-1)
    {
        if((A[i].anio==anio) && (A[i].division==division))
            pos=i;
        i++;
    }

    return pos;
}

int agregarCursoAlumnos(celdaCursosAlumnos A[],int validos,int anio,int division)
{
    A[validos].anio=anio;
    A[validos].division=division;
    A[validos].listaAlumnos=inicListaAlumno();
    validos++;

    return validos;
}
nodoAlumno * inicListaAlumno() {
return NULL;
}
nodoAlumno* crearNodoAlumno(stAlumno alumno){
    nodoAlumno* aux=(nodoAlumno*) malloc (sizeof(nodoAlumno));
    aux->alumno=alumno;
    aux->siguiente=NULL;

    return aux;
}
nodoAlumno* agregarAlFinalAlumno(nodoAlumno* lista, nodoAlumno* nuevoNodo){
   if(lista == NULL)
    {
      lista = nuevoNodo;
    }
   else
    {
      nodoAlumno * ultimo = buscarUltimoAlumno(lista);
      ultimo->siguiente = nuevoNodo;
    }
   return lista;
}

nodoAlumno* buscarUltimoAlumno(nodoAlumno* lista){
   nodoAlumno* seg = lista;
   if(seg != NULL)
      while(seg->siguiente != NULL)
        {
         seg = seg->siguiente;
        }
    return seg;
 }


 /////////////Lista de alumnos ////////
 void mostrarADL(celdaCursosAlumnos A[],int validos)
{
    int i=0;
    printf("\n LISTADO DE ALUMNOS .\n");
    while(i<validos)
    {
        printf(YEL("\t\t\t\t Alumnos %i-%i\n"),A[i].anio,A[i].division);
        mostrarListaAlumnos(A[i].listaAlumnos);
        printf("\n");
        printf("-------------------------");
        printf("\n");
        i++;
    }
    system("pause");
}

void mostrarListaAlumnos(nodoAlumno* lista)
{
    nodoAlumno* aux=lista;

    while(aux!=NULL)
    {
      mostrarUnAlumno(aux->alumno);
      aux=aux->siguiente;
    }
}

void mostrarUnAlumno(stAlumno auxAlumno){
printf("Nombre:|  %s\t| Apellido:|  %s\t|  DNI:|  %s\t| Fecha Deuda %i/%i/%i \n",auxAlumno.nombre,auxAlumno.apellido,auxAlumno.dni,auxAlumno.diaC,auxAlumno.mesC,auxAlumno.anioC);
}
//////////////////Carga de Alumno
int cargaAlumno(celdaCursosAlumnos A[],int validos,int dimension){

    int control=0;
    stAlumno auxAlumno;
    while(control==0 && validos<dimension){
        auxAlumno=cargaDatosAlumno(A,validos);
        validos=altaAlumnos(A,validos,auxAlumno);
        system("cls");
        printf("Desea cargar otro alumno 1-No/ 0-Si \n");
        scanf("%i",&control);
        system("cls");
    }



return validos;
}

stAlumno cargaDatosAlumno(celdaCursosAlumnos A[],int validos){

    stAlumno alumno;
    int control=0;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);


    while(control ==0){
        int encontrado=1;
        system("cls");
        printf(GREEN("\t\tCARGA DE ALUMNO\n"));
        printf(GREEN("---CARGA DE DATOS ---\n"));
        printf("Ingrese DNI del alumno \n");
        fflush(stdin);
        scanf("%s",alumno.dni);
        encontrado=buscaADL(A,validos,alumno.dni);
        if(encontrado==1){
             printf("Ingrese nombre  \n");
        fflush(stdin);
        scanf("%s",alumno.nombre);
        printf("Ingrese Apellido\n");
        fflush(stdin);
        scanf("%s",alumno.apellido);
        printf("Ingrese edad \n");
        scanf("%i",&alumno.edad);

        printf("Ingrese anio a cursar \n");
        scanf("%i",&alumno.anio);
        printf("Ingrese Division a cursar \n");
        scanf("%i",&alumno.division);

        alumno.diaA=tm->tm_mday;
        alumno.mesA=tm->tm_mon+1;
        alumno.anioA=1900+tm->tm_year;
        alumno.diaC=tm->tm_mday;
        alumno.mesC=tm->tm_mon+2;
        alumno.anioC=1900+tm->tm_year;


        printf("LOS DATOS SON \n");
        printf("Nombre y Apellido:%s %s \nEdad: %i \nDNI: %s \nAnio y Division:%i-%i\n",alumno.nombre,alumno.apellido,alumno.edad,alumno.dni,alumno.anio,alumno.division);
        printf("Fecha de alta %i /%i /%i\n",alumno.diaA,alumno.mesA,alumno.anioC);
        printf("Fecha Proxima Cuota %i/%i/%i\n",alumno.diaC,alumno.mesC,alumno.anioC);
        printf("Desea Volver a cargar los datos  1-No/ 0-Si \n");
        scanf("%i",&control);


        }
        else{
            printf("El Alumno ya fue cargado anteriormente \n");
            system("pause");

        }



    }

return alumno;

}

int   buscaADL(celdaCursosAlumnos A[],int validos, char dni[]){


    int i=0;
    int control=1;
    while(i<validos && control==1){
       int encontrado=buscaListaDni(A[i].listaAlumnos,dni);

       if(encontrado ==0){
        control=0;


       }
       i++;
    }



return control;
}

int  buscaListaDni(nodoAlumno * lista, char dni[]) {

    nodoAlumno * seg;
    seg = lista;
    int control=1;
    while (seg != NULL)  {
        if( strcmp(dni, seg->alumno.dni)==0 ){
            control=0;

            return control;
           }
        else{

          seg=seg->siguiente; //avanzo hacia el siguiente nodo.

        }
    }
return control;
}
//////////////////////////////Baja Alumno
void bajaAlumno(celdaCursosAlumnos A[],int validos){
    char dni[20];
    int control=1;
    int i=0;
    printf("Ingrese el dni del alumno a "RED( "eliminar \n"));
    fflush(stdin);
    scanf("%s",dni);

    while(i<validos && control==1)
    {
        control=buscaListaDni(A[i].listaAlumnos,dni);
        if(control==0){
           A[i].listaAlumnos=borrarNodoAlumnos(A[i].listaAlumnos,dni);
        }
     i++;
    }
     if(control==1){
        printf("El DNI ingresado" RED(" no ") "es valido\n");
        system("pause");
    }
    else{
        printf("El Alumno fue dado de baja" GREEN(" exitosamente \n"));
        system("pause");

    }
}

nodoAlumno * borrarNodoAlumnos(nodoAlumno * lista, char dni[]) {
    nodoAlumno * seg;
    nodoAlumno * ante;

    if((lista != NULL) && (strcmp(dni, lista->alumno.dni)==0 )) {
        nodoAlumno * aux = lista;
        lista = lista->siguiente;
        free(aux);
    }else {
        seg = lista;
        while((seg != NULL) && (strcmp(dni, seg->alumno.dni)!=0 )) {
            ante = seg;
            seg = seg->siguiente;
        }

        if(seg!=NULL) {
            ante->siguiente = seg->siguiente;

            free(seg);

        }
    }
    return lista;
}
//////////////////////MODIFICA ALUMNOS
int modificaAlumno(celdaCursosAlumnos  A[],int validos,int dimension){

    char dni[20];
    int control=1;
    stAlumno auxAlumno;
    int i=0;
    printf("Ingrese el DNI del alumno para" BLUE (" MODIFICAR ") "los datos\n");
    fflush(stdin);
    scanf("%s",dni);
    while(validos<dimension && control==1){
        while(i<validos && control==1)
        {
            control=buscaListaDni(A[i].listaAlumnos,dni);
            if(control==0){
               auxAlumno=copiarDatos(A[i].listaAlumnos,dni);
               A[i].listaAlumnos=borrarNodoAlumnos(A[i].listaAlumnos,dni);
            }
         i++;
        }
        if(control==0){
            auxAlumno=cargaDatosModificados(auxAlumno);
            validos=altaAlumnos(A,validos,auxAlumno);
        }
        else{
            printf("El DNI ingresado no es valido \n");
            printf("Ingresar DNI de nuevo  1-SI / 0-No\n");
            scanf("%i",&control);

        }

    }
return validos;

}

stAlumno copiarDatos(nodoAlumno * lista,char dni[]){
    stAlumno aux;
    nodoAlumno *seg=lista;
    while(seg!=NULL){
        if( strcmp(seg->alumno.dni,dni)==0){
            aux=seg->alumno;
        }
        seg=seg->siguiente;
    }
    return aux;
}
stAlumno cargaDatosModificados(stAlumno auxAlumno){

        stAlumno alumno=auxAlumno;
        printf("Ingrese DNI del alumno \n");
        fflush(stdin);
        scanf("%s",alumno.dni);
        printf("Ingrese nombre  \n");
        fflush(stdin);
        scanf("%s",alumno.nombre);
        printf("Ingrese Apellido\n");
        fflush(stdin);
        scanf("%s",alumno.apellido);
        printf("Ingrese edad \n");
        scanf("%i",&alumno.edad);

        printf("Ingrese anio a cursar \n");
        scanf("%i",&alumno.anio);
        printf("Ingrese Division a cursar \n");
        scanf("%i",&alumno.division);


return alumno;
}

////////////////Consulta Alumno///////////
void consultaAlumno(celdaCursosAlumnos A[],int validos){

    int i=0;
    int control=1;
    char dni[20];
    printf("\t\t "MAG(" CONSULTA \n") );
    printf("Ingrese el Dni del Alumno para buscar sus datos\n");
    fflush(stdin);
    scanf("%s",dni);
    while(i<validos && control==1){
        control=buscaListaDni(A[i].listaAlumnos,dni);
        if(control==0){
            infoAlumno(A[i].listaAlumnos,dni);
        }

    i++;
    }
    if(control==1){
        printf("El DNI ingresado " RED(" NO ") " es valido \n");
        system("pause");
        }


}

void infoAlumno(nodoAlumno  *lista,char dni[]){


    nodoAlumno * seg;
    seg = lista;
    system("cls");
    while (seg != NULL)  {
        if( strcmp(dni, seg->alumno.dni)==0 ){
            printf("\t\t " MAG("LOS DATOS SON ") "\n");
            printf("Nombre y Apellido:%s %s \nEdad: %i \nDNI: %s \nAnio y Division:%i-%i\n",seg->alumno.nombre,seg->alumno.apellido,seg->alumno.edad,seg->alumno.dni,seg->alumno.anio,seg->alumno.division);
            printf("Fecha de alta %i /%i /%i\n",seg->alumno.diaA,seg->alumno.mesA,seg->alumno.anioC);
            printf("Fecha Proxima Cuota %i/%i/%i\n",seg->alumno.diaC,seg->alumno.mesC,seg->alumno.anioC);
            system("pause");
            seg=seg->siguiente; //avanzo hacia el siguiente nodo.

           }
        else{

          seg=seg->siguiente; //avanzo hacia el siguiente nodo.

        }
    }


}


void  listaAlumnosDeudores(celdaDeudores D[],celdaCursosAlumnos A[],int validos)
{
    int dia,mes;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);

    dia=tm->tm_mday;
    mes=tm->tm_mon+1;


   for(int i=0;i<validos;i++){
        nodoAlumno *seg=A[i].listaAlumnos;
        D[i].anio=A[i].anio;
        D[i].division=A[i].division;
        D[i].listaD=inicListaD();

        while(seg!=NULL){

             if(seg->alumno.mesC <mes || (seg->alumno.diaC<dia && seg->alumno.mesC==mes)){




              nodoAlumnoDoble* nuevo=crearNodoDoble(seg->alumno);
              D[i].listaD=agregarPpioDoble(D[i].listaD,nuevo);
             }

            seg=seg->siguiente;

        }
   }


}

nodoAlumnoDoble *inicListaD(){
return NULL;
}


///////Salvar datos
void  guardarAlumnos(celdaCursosAlumnos A[],int validos,char alumnos[]){

FILE *arch;
    arch=fopen(alumnos,"w+b");
    stAlumno  aux;
    for(int i=0;i<validos;i++){
        nodoAlumno *seg=A[i].listaAlumnos;
          while(seg!=NULL){

                aux=seg->alumno;
                fwrite(&aux, sizeof(stAlumno), 1, arch);
                seg=seg->siguiente;
          }

    }
  fclose(arch);

}


nodoAlumnoDoble * crearNodoDoble (stAlumno dato) {
    nodoAlumnoDoble * aux = (nodoAlumnoDoble*) malloc(sizeof(nodoAlumnoDoble));
    aux->alumno = dato;

    aux->ant = NULL;
    aux->sig = NULL;
return aux;
}


nodoAlumnoDoble * agregarPpioDoble (nodoAlumnoDoble * lista, nodoAlumnoDoble * nuevo) {
    nuevo->sig = lista;
    if(lista != NULL)
    lista->ant=nuevo;
return nuevo;
}

void mostrarDeudores(celdaDeudores D[],int validos){

 int i=0;
    printf("\n LISTADO DE ALUMNOS CON DEUDAS.\n");
    while(i<validos)
    {
        printf(YEL("\t\t\t\t Alumnos  %i-%i\n"),D[i].anio,D[i].division);
        mostrarListaDeudores(D[i].listaD);
        printf("\n");

        i++;
    }
    system("pause");

}
void mostrarListaDeudores(nodoAlumnoDoble *lista ){
 nodoAlumnoDoble* aux=lista;

    while(aux!=NULL)
    {
      mostrarUnAlumno(aux->alumno);
      aux=aux->sig;
    }
}


/////////////pagar deuda
int   pagarDeuda(celdaDeudores D[],celdaCursosAlumnos A[],int validos){

int dia,mes;
    time_t t;
    struct tm *tm;
    t=time(NULL);
    tm=localtime(&t);

    dia=tm->tm_mday;
    mes=tm->tm_mon+2;

   char dni[20];
    int control=1;
    stAlumno auxAlumno;
    int i=0;
    printf("Ingrese el DNI del alumno que desea "  CYAN(" PAGAR ") " la cuota\n");
    fflush(stdin);
    scanf("%s",dni);
    while( control==1){
        while(i<validos && control==1)
        {
            control=buscaListaDni(A[i].listaAlumnos,dni);

            if(control==0){
               auxAlumno=copiarDatos(A[i].listaAlumnos,dni);
               auxAlumno.diaC=dia;
               auxAlumno.mesC=mes;
               D[i].listaD=borrarNodoDoble(D[i].listaD,dni);
               A[i].listaAlumnos=borrarNodoAlumnos(A[i].listaAlumnos,dni);
            }
         i++;
        }
        if(control==0){
            validos=altaAlumnos(A,validos,auxAlumno);
        }
        else{
            printf("El DNI ingresado " RED(" NO ") " es valido \n");
            printf("Ingresar DNI de nuevo  1-SI / 0-No\n");
            scanf("%i",&control);

        }

    }

  return validos;

}


nodoAlumnoDoble *borrarNodoDoble(nodoAlumnoDoble *lista,char dni[]){

   nodoAlumnoDoble *nodo;

   /* Buscar el nodo de valor v */
   nodo =lista;
   while(nodo && strcmp(nodo->alumno.dni,dni)!=0) nodo = nodo->sig;


   /* El valor v no está en la lista */
   if(!nodo || strcmp(nodo->alumno.dni,dni)!=0) return lista;

   /* Borrar el nodo */
   /* Si lista apunta al nodo que queremos borrar, apuntar a otro */
   if(nodo == lista){
     if(nodo->ant) lista = nodo->ant;
     else lista = nodo->sig;}

   if(nodo->ant) /* no es el primer elemento */
      nodo->ant->sig = nodo->sig;
   if(nodo->sig) /* no es el último nodo */
      nodo->sig->ant = nodo->ant;
   free(nodo);

return lista;
}








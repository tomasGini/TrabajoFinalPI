#include <iostream>
#include <stdlib.h>
using namespace std;
void limpiar(){
system ("cls");
}

/*
Exponer el programa funcionando, realizando algunas pruebas entre las que se deben incluir:

Mostrar las estructuras dinámicas sobre las que se basa el sistema. Jona y Emily

ABM de categorías, prestatarios y préstamos. Marcos y Juampi

Mostrar cada consulta de Préstamos:

Cantidad de objetos prestados por categoría Marcos

Listado de préstamos por categoría Emily

Listado de préstamos ordenados por categoría o prestatario Juampi

Listar todos los prestatarios que tienen al menos un objeto prestado Jona
*/

//ARREGLOS PARA ALMACENAR LOS DATOS//
struct prestatario{
    int codigoprestatario;
    string nombre;
    string apellido;
}pres[1000];//Estructura de datos tipo struct que almacena tres bloques en este caso dos variables una de tipo string para el nombre del prestatario y otra de tipo int que contiene el codigo que identifica al prestatario.

struct categoria{
    int codigocategoria;
    string descripcion;
}ca[1000];//Estructura de datos tipo struct que almacena dos bloques en este caso dos variables una de tipo string para la descripcion de la categoria y otra de tipo int que contiene el codigo que identifica a la categoria.

struct prestamo{
    int co_prestatario;
    int co_categoria;
    string descripcion;
    bool estado;
};//Estructura de datos tipo struct que almacena cuatro bloques en este caso variables para almacenar todos los datos del prestamo.

struct Nodo{
    prestamo pr;
    Nodo* siguiente;
}; //Estructura para cada nodo de prestamos

//FUNCIONES: Estas son las funciones que vamos a utilizar en todo el programa//

                                                           /* ===================

                                                                 SUBFUNCIONES

                                                             =================== */
/*
=============
De impresion
=============
*/

//DE IMPRESION EN PANTALLA: Estas funciones son para que la funcion principal no este muy cargada y se logre entender mejor//
void menu_principal(int & a){ //Funcion que imprime en pantalla las opciones del menu principal y le indica al usuario que ingrese la opcion que desee
    cout<<"*******************************************************************"<<endl;
    cout<<"                            Bienvenido                            "<<endl;
    cout<<"\n";
    cout<<"Opcion 1: Administrar y consultar Categorias y Prestatarios"<<endl;
    cout<<"Opcion 2: Administrar Prestamos"<<endl;
    cout<<"Opcion 3: Consultar Prestamos"<<endl;
    cout<<"Opcion 4: Finalizar"<<endl;
    cout<<"\n";
    cout<<"Ingrese la opcion que desee"<<endl;
    cin>>a;
    cout<<"*******************************************************************"<<endl<<endl;
    limpiar();
}

void case_1(char & a){ //En el caso de que el usuario ingrese 1 el programa imprime en pantalla las siguientes opciones y le indica al usuario que ingrese una nuevaa opcion que desea para que cumpla su objetivo
    cout<<"\n";
    cout<<"Opcion A: Agregar Categoria"<<endl;
    cout<<"Opcion B: Modificar Categoria"<<endl;
    cout<<"Opcion C: Eliminar Categoria"<<endl;
    cout<<"Opcion D: Agregar Prestatario"<<endl;
    cout<<"Opcion E: Modificar Prestatario"<<endl;
    cout<<"Opcion F: Eliminar Prestatario"<<endl;
    cout<<"\n";;
    cout<<"Ingrese la opcion que desee"<<endl;
    cin>>a;
    a=toupper(a);}

void case_2(char & a){ //En el caso de que el usuario ingrese 2 el programa imprime en pantalla las siguientes opciones y le indica al usuario que ingrese una nuevaa opcion que desea para que cumpla su objetivo
    cout<<"\n";
    cout<<"Opcion A: Agregar Prestamo"<<endl;
    cout<<"Opcion B: Modificar Prestamo"<<endl;
    cout<<"Opcion C: Eliminar Prestamo"<<endl;
    cout<<"Opcion D: Devolver Prestamo"<<endl;
    cout<<"\n";
    cout<<"Ingrese la opcion que desee"<<endl;
    cin>>a;
    a=toupper(a);
    limpiar();
}

void case_3(char & a){ //En el caso de que el usuario ingrese 3 el programa imprime en pantalla las siguientes opciones y le indica al usuario que ingrese una nuevaa opcion que desea para que cumpla su objetivo
    cout<<"\n";
    cout<<"Opcion A: Cantidad de objetos prestados por categoria"<<endl;
    cout<<"Opcion B: Listado de prestamos que se ecuentran en una misma categoria"<<endl;
    cout<<"Opcion C: Listado de prestamos ordenados por prestatario o categoria"<<endl;
    cout<<"Opcion D: Listado de todos los prestatarios que tienen al menos un objeto prestado"<<endl;
    cout<<"\n";
    cout<<"Ingrese la opcion que desee"<<endl;
    cin>>a;
    a=toupper(a);
    limpiar();
}

void imprimir_categorias(int c){ //Funcion que imprime todas las categorias que se encuentran ingresadas
    for ( int i = 0; i < c; i++){
            cout<<"la categoria "<<ca[i].descripcion<<" Tiene el codigo: "<<ca[i].codigocategoria<<endl;}}

void imprimir_prestatarios(int p){ //Funcion que imprime todos los prestatarios que se encuentran ingresados
    for ( int i = 0; i < p; i++){
        cout<<"El prestatario "<<pres[i].nombre<<" "<<pres[i].apellido<<" tiene el codigo: "<<pres[i].codigoprestatario<<endl;}}

void imprimir_prestamos(Nodo* lista){
    Nodo* actual=new Nodo();
    actual=lista;
    int contador = 0;
    while (actual !=NULL){
        cout<<endl<<"El prestamo numero: "<<contador<<endl<<"Contiene el codigo de prestatario: "<<actual->pr.co_prestatario<<endl<<"Contiene el codigo de categoria: "<<actual->pr.co_categoria<<endl<<"Y la descripcion: "<<actual->pr.descripcion<<endl;
        if (actual->pr.estado==true)
            cout<<"Todavia no se ha devuelto"<<endl;
        else cout<<"Ya se devolvio"<<endl;
        actual=actual->siguiente;
        contador ++;}}

/*
============================
De disminucion en prestamos
============================
*/

//En caso de que quisieramos disminuir una categoria o prestatario en los prestamos todos los prestatarios o categoria con codigo mayor al eliminado deben restarse en uno
void disminuir_enprestamo_categorias(Nodo* lista,int codigo){
    Nodo* aux=new Nodo;
    aux=lista;
    while(aux!=NULL){
        if(codigo<aux->pr.co_categoria){
            aux->pr.co_categoria--;}
        aux=aux->siguiente;}}

void disminuir_enprestamo_prestatarios(Nodo* lista,int codigo){
    Nodo* aux=new Nodo;
    aux=lista;
    while(aux!=NULL){
        if(codigo<aux->pr.co_prestatario){
            aux->pr.co_prestatario--;}
        aux=aux->siguiente;}}

/*
===============================
De modificacion de los strings
===============================
*/

/*
Se utiliza para colocar en mayuscula la primer letra y toda letra luego de un espacio
*/
void mayusculas(string & a){ //Funcion que coloca en mayusculas la primer letra de cada palabra (luego de un espacio)
    for (int i = 0; i < a.length(); i++){ //Recorre todo el string
        a[i]= tolower(a[i]); //Coloca en minusculas toda la palabra
       a[0]=toupper(a[0]); //Coloca en mayusucula la primer letra
       if (a[i]==' '){ //En caso de que sea un espacio el caracter entra aca
           (a[i+1])=toupper(a[i+1]); //La siguiente letra se coloca en mayusucula
          i=1+i;}}}

/*Las proximas dos funciones consulta si el codigo ingresado por el usuario se encuentra dentro del bloque las categorias o de los prestatarios del struct de prestamos
(Funcionan especificamente para eliminar una categoria o un prestatario y que no se encuentre en uso, es decir en los prestamos) y en el caso de que se elimine
todas los codigos en los prestamos que sean superior al que se elimino disminuye en uno.
*/

void encontrarenprestamo_c(Nodo* lista,int usuario, bool & encontrado){
    encontrado=true;
    Nodo* aux=new Nodo;
    aux=lista;
    while(aux!=NULL){
        if(usuario==aux->pr.co_categoria){
            encontrado=false;
            break;}
        aux=aux->siguiente;}}

void encontrarenprestamo_p(Nodo* lista,int usuario, bool & encontrado){
    encontrado=true;
    Nodo* aux=new Nodo;
    aux=lista;
    while(aux!=NULL){
        if(usuario==aux->pr.co_categoria){
            encontrado=false;
            break;}
        aux=aux->siguiente;}}

/*
==========================
De actividad en prestamos
==========================
*/

/*
Son las que por alguna razon estan activas en el struct de los prestamos y se encuentran aqui para explicar mejor para que se utilizan y no se llena de lineas de codigo
la funcion de prestamos. Ya que solo ingresa los datos el usuario y estas lineas de codigo se encargan de cargarlos
*/

void agregar_p(Nodo* & lista, int codigoc, int codigop, string d, int & pr){
    //Esta funcion se encarga de agregar los prestamos con los datos que ingreso el usuario
    Nodo* agregar =new Nodo();
    agregar->pr.co_prestatario=codigop;
    agregar->pr.co_categoria=codigoc;
    agregar->pr.descripcion=d;
    agregar->pr.estado=true;

    Nodo* aux1=lista; //aux 1 pasa a valer el inicio de la lista
    Nodo* aux2;

    while(aux1!=NULL){ //Si entra aca significa que la lista tiene contenido y lo que hace es recorrer hasta el final de la cadena
        aux2=aux1;
        aux1=aux1->siguiente;
    }
    if (lista==aux1){ //Si entra aca quiere decir que es el inicio de la cadena
        lista=agregar;
    }
    else //Si entra aca significa que entro al while y se enecuentra en el final de la cadena y lo que hace es agregar el nodo
        aux2->siguiente=agregar;

    agregar->siguiente=aux1;
    pr++;}

void modificar_p(Nodo* lista,int c_prestamos, int usuario, int codigoc, int codigop, string d, bool estado){
    Nodo* aux=new Nodo;
    aux=lista;
    for (int i=0;i<c_prestamos;i++){ //Mientras i sea menos que la dimension logica de los prestamos
        if(i==usuario){ //En caso de que i sea igual al codigo de prestamo seleccionado por el usuario
            //Hace el reemplazo de los datos seleccionados en la funcion de modificar_prestamos
            aux->pr.co_categoria=codigoc;
            aux->pr.co_prestatario=codigop;
            aux->pr.descripcion=d;
            aux->pr.estado=estado;
            break;}
        //Si no es igual sigue recorriendo
        aux=aux->siguiente;}}

void eliminar_p(Nodo* & lista, int usuario, int & c_prestamos){
    int i=0; //Variable para identificar numero de prestamo
    Nodo* actual; //Declaramos un puntero
    Nodo* anterior=NULL; //Declaramos otro puntero con valor NULL
    actual=lista; //Le damos el valor a actual el mismo que lista
    while (i != usuario){ //Mientras el puntero actual sea distinto a null (sera null cuando finalice de recorrer toda la lista
        //Recorre la lista
        anterior=actual;
        actual=actual->siguiente;
        i++;}
    //En el caso de que el numero de prestamo sea igual al numero seleccionado por el usuario cambia el valor a false del estado del prestamo
    if(anterior == NULL && actual->pr.estado == false){ //Si esta comparacion es correcta significa que el prestamo a eliminar es el primero
        //El puntero lista apuntara al siguiente
        lista=lista->siguiente;
        delete actual;
        cout<<"Prestamo eliminado"<<endl;
        c_prestamos--;}
    if (anterior != NULL && actual->pr.estado == false){
        //El puntero anterior tendra el valor de siguiente y el valor del puntero actual se eliminara ademas de que se disminuira uno de la dimension logica de los prestamos
        anterior->siguiente=actual->siguiente;
        delete actual;
        cout<<"Prestamo eliminado"<<endl;
        c_prestamos--;}
    if (actual->pr.estado==true)
        cout<<"El prestamo aun se encuentra activo. Por lo tanto no se eliminara"<<endl;}

void devolver_p(Nodo* & lista, int usuario){
    int i=0; //Variable para identificar numero de prestamo
    Nodo* actual; //Declaramos un puntero
    Nodo* anterior=NULL; //Declaramos otro puntero con valor NULL
    actual=lista; //Le damos el valor a actual el mismo que lista
        while ( i != usuario){ //Mientras el contador sea distinto del numero seleccionado por el usuario
            //Recorre la lista
            anterior=actual;
            actual=actual->siguiente;
            i++;}
        //En el caso de que el numero de prestamo sea igual al numero seleccionado por el usuario cambia el valor a false del estado del prestamo
        if (i==usuario){
            actual->pr.estado=false;
            cout<<"Prestamo devuelto"<<endl;}}

/*
Esta funcion a continuacion se encarga de imprimir todos los prestamos que se encuentra el codigo de prestatario que el usuario indica
A la hora de modificar un prestamo
*/
void imprimir_prestamos_prestatario(Nodo*lista, int usuario){
    int contador =0; //Variable para identificar numero de prestamo
    Nodo* actual; //Declaramos un puntero
    Nodo* anterior=NULL; //Declaramos otro puntero con valor NULL
    actual=lista; //Le damos el valor a actual el mismo que lista
    while (actual !=NULL){ //Mientras actual sea distinto a null (sera null cuando finalice de recorrer toda la lista)
        if (actual->pr.co_prestatario==usuario){ //Busca que el codigo de prestatario sea igual al ingresado por el usuario
            //En caso de que lo sea imprime todos los prestamos
            cout<<endl<<"El prestamo numero: "<<contador<<endl<<"Contiene el codigo de prestatario: "<<actual->pr.co_prestatario<<endl<<"Contiene el codigo de categoria: "<<actual->pr.co_categoria<<endl<<"Y la descripcion: "<<actual->pr.descripcion<<endl;
            if (actual->pr.estado==true)
                cout<<"Todavia no se ha devuelto"<<endl;
            else cout<<"Ya se devolvio"<<endl;
                }
        //Sigue recorriendo
        anterior=actual;
        actual=actual->siguiente;
        contador++;}}


//CASE1: Todas las funciones que vamos a utilizar en el case 1

//Funciones para agregar categorias y prestatarios

void agregar_categoria(int & c, string & d){ //En esta funcion el codigo debe darle al usuario la posibilidad de agregar una categoria
    cout<<"Ingrese la descripcion de una categoria: "; //Se le solicita al usuario que ingrese la descripcion de la categoria que desea ingresar
    getline(cin>>ws,d);
    mayusculas(d); //Se invoca la funcion mayusuculas
    ca[c].descripcion=d; //Almacena el string en el en bloque descripcion del struct c (categoria)
    ca[c].codigocategoria=c; //Almacena el valor de la dimension logica en el bloque codigo categoria del struct c (categoria)
    cout<<"Se ha agregado con exito"<<endl;
    c++; //Se le suma 1 a la variable de la dimension logica para que el valor se guarde como el codigo de la proxima categoria
}

void agregar_prestatario(int & p, string & n, string & a){ //En esta funcion el codigo debe darle al usuario la posibilidad de agregar una categoria
    cout<<"Nombre del prestatario: "; //Se le solicita al usuario que ingrese el nombre del prestatario que desea ingresar
    getline(cin>>ws,n);
    cout<<"Apellido del prestatario: "; //Se le solicita al usuario que ingrese el apellido del prestatario que desea ingresar
    getline(cin>>ws,a);
    cout<<"Se ha agregado con exito"<<endl;
    mayusculas(n); //Se invoca la funcion mayusuculas
    mayusculas(a); //Se invoca la funcion mayusuculas
    pres[p].nombre = n; //Almacena el string en el en bloque nombre del struct p (prestatario)
    pres[p].apellido = a; //Almacena el string en el en bloque apellido del struct p (prestatario)
    pres[p].codigoprestatario = p; //Almacena el valor de la dimension logica en el bloque codigo prestatario del struct p (prestatario)
    p++; //Se le suma 1 a la variable de la dimension logica para que el valor se guarde como el codigo del proximo prestatario
}

//Funciones para modificar categorias y prestatarios

void modificar_categoria(int c, int & usuario, string & d){//En esta funcion el codigo debe darle al usuario la posibilidad de modificar una categoria
    imprimir_categorias(c);
    cout<<endl<<"Indique el codigo de la categoria que desea modificar: "; //Le solicitamos al usuario de que indique el codigo de la categoria que desea modificar
    cin>>usuario;
    cout<<"\n";
    if (usuario < c){
        cout<<"Indique la descripcion de la categoria que desea colocar en su lugar "; //Le solicitamos al usuario que indique una nueva categoria que reemplazara a la anterior
        getline(cin>>ws,d);
        mayusculas(d); //Invoca la funcion mayusculas
        ca[usuario].descripcion = d; //Se reemplaza lo que contiene el bloque descripcion por el nuevo string
        cout<<"Se ha modificado con exito"<<endl;}

    else {
        cout<<"No se ha podido modificar la categoria dado que no se ha encontrado una categoria con el codigo indicado"<<endl;}}

void modificar_prestatario(int p, int & usuario, string & n, string & a){//En esta funcion el codigo debe darle al usuario la posibilidad de modificar un prestatario
    imprimir_prestatarios(p);
    cout<<endl<<"Indique el codigo del prestatario que desea modificar: "; //Le solicitamos al usuario de que indique el codigo del prestatario que desea modificar
    cin>>usuario;
    cout<<"\n";
    if (usuario < p){
        cout<<"Indique el nombre del prestatario que desea colocar en su lugar: "; //Le solicitamos al usuario que indique un nuevo prestatario que reemplazara al anterior
        getline(cin>>ws,n);
        cout<<"Indique el apellido del prestatario que desea colocar en su lugar: "; //Le solicitamos al usuario que indique un nuevo prestatario que reemplazara al anterior
        getline(cin>>ws,a);
        cout<<"Se ha modificado con exito"<<endl;
        mayusculas(n); //Invoca la funcion mayusculas
        mayusculas(a); //Se invoca la funcion mayusuculas
        pres[usuario].nombre=n; //Se reemplaza lo que contiene el bloque nombre por el nuevo string
        pres[usuario].apellido=a;}

    else {
        cout<<"No se ha podido modificar el prestatario dado que no se ha encontrado un prestatario con el codigo indicado"<<endl;}}

void eliminar_categoria(int & c, int & usuario, bool & consulta, Nodo* lista) { //En esta funcion el codigo debe darle al usuario la posibilidad de eliminar una categoria
    imprimir_categorias(c);
    cout<<endl<<"Seleccione el codigo de la categoria que desea eliminar: ";
    cin>>usuario;
    encontrarenprestamo_c(lista,usuario,consulta); //Se disminuyen los codigos de categorias mayores al eliminado en los prestamos que se encuentran
    if (usuario < c && consulta == true){
        disminuir_enprestamo_categorias(lista,usuario);
        cout<<"Se ha eliminado con exito"<<endl; //Le avisa al usuario que se elimino con exito
        for (int i=usuario; i < c; i++){
            ca[i].descripcion=ca[i+1].descripcion;} //La descripcion pasa a ser la misma que la siguiente
        c--;} //Se disminuye en 1 la dimension logica

    if (consulta == true && usuario > c) //En el caso de que el booleano sea falso se imprime en pantalla avisando de que no se encontro el codigo
        cout<<"No se ha podido eliminar la categoria dado que no se ha encontrado una categoria con el codigo indicado"<<endl;

    if (usuario < c && consulta == false){
        cout<<"La categoria se encuentra ligada a un prestamo, para poder eliminarla debe eliminar antes el prestamo"<<endl;}}

void eliminar_prestatario(int & p, int & usuario, bool & consulta, Nodo* &lista) { //En esta funcion el codigo debe darle al usuario la posibilidad de eliminar un prestatario
    imprimir_prestatarios(p);
    cout<<endl<<"Seleccione el codigo del prestatario que desea eliminar: ";
    cin>>usuario;
    encontrarenprestamo_p(lista,usuario,consulta);
    if (consulta == true && usuario < p){
        disminuir_enprestamo_prestatarios(lista,usuario); //Se disminuyen los codigos de prestatarios mayores al eliminado en los prestamos que se encuentran
        cout<<"Se ha eliminado con exito"<<endl; //Se imprime en pantalla que se elimino con exito
        for (int i=usuario; i < p; i++){
            pres[i].nombre=pres[i+1].nombre; //El nombre pasa a ser el mismo misma que el siguiente
            pres[i].apellido=pres[i+1].apellido;} //El apellido pasa a ser el mismo que el siguiente
            p--;} //Se disminuye en 1 la dimension logica
    if (consulta == true && usuario > p) //En el caso de que el booleano sea falso se imprime en pantalla avisando de que no se encontro el codigo
        cout<<"No se ha podido eliminar el prestatario dado que no se ha encontrado un prestatario con el codigo indicado"<<endl;

    if (usuario < p && consulta == false){
        cout<<"El prestatario se encuentra ligado a un prestamo, para poder eliminarlo debe eliminar antes el prestamo"<<endl;}}

//CASE 2: Todas las funciones que vamos a utilizar en el case 2

void agregar_prestamo(Nodo* & lista, int & c_prestamos, int p, int c, int & codigoc, int & codigop, string & d) { //En esta funcion el codigo debe darle al usuario la posibilidad de agregar un prestamo
    //El usuario ingresa los datos del prestamo
    cout<<endl<<"Los prestatarios son:"<<endl<<endl;
    imprimir_prestatarios(p); //Invoca la funcion para imprimir los prestatarios
    cout<<endl<<"Las categorias son:"<<endl<<endl;
    imprimir_categorias(c); //Invoca la funcion para imprimir las categorias
    cout<<"\n";
    cout<<"Seleccione el codigo de prestatario que desea agregar al prestamo: ";
    cin>>codigop; //Se ingresa el codigo del prestatario
    cout<<"Seleccione el codigo de categoria que desea agregar al prestamo: ";
    cin>>codigoc; //Se ingresa el codigo de la categoria
    cout<<"Indique una descripcion del prestamo: ";
    getline(cin>>ws,d); //Se ingresa una descripcion del prestamo
    mayusculas(d); //Se invoca la funcion mayusculas
    //En el caso de que los codigos sean correctos se hace el llamado a la funcion
    if (codigoc < c && codigop < p){
        agregar_p(lista, codigoc, codigop, d, c_prestamos);
        cout<<"Se ha agregado con exito"<<endl;}
    //En el caso de que no sean correctos se le informa al usuario cual es el error
    if (codigoc < c && codigop >= p)
        cout<<endl<<"El prestamo no se ha agregado por motivos de que no se ha encontrado el codigo de prestatario"<<endl;
    if (codigoc >= c && codigop < p)
        cout<<endl<<"El prestamo no se ha agregado por motivos de que no se ha encontrado el codigo de categoria"<<endl;
    if (codigoc >= c && codigop >= p)
        cout<<endl<<"El prestamo no se ha agregado por motivos de que no se ha encontrado el codigo de categoria y de prestatario"<<endl;}

void modificar_prestamo(Nodo* & lista, int c_prestamos, int p, int c, int & usuario, int & codigoc, int & codigop, string  & d, bool & estado) { //En esta funcion el codigo debe darle al usuario la posibilidad de agregar un prestamo
    int es=0;
    imprimir_prestatarios(p);
    //Le solicitamos al usuario que ingrese un prestatario y corroboramos que se encuentre ligado a un prestamo
    cout<<endl<<"Indique el codigo del prestatatario que desea modificar un prestamo: "; //Le solicitamos al usuario de que indique el codigo de la categoria que desea modificar
    cin>> usuario;
    encontrarenprestamo_p(lista,usuario, estado);
    //Si se encuentra imprimimos los prestamos
    if (estado == false){
        imprimir_prestamos_prestatario(lista, usuario);
        cout<<"Seleccione el codigo de prestamo que desea modificar: ";
        cin>>usuario;
        if (usuario < c_prestamos){
            //Le solicitamos al usuario que ingrese los datos
            cout<<endl<<"Los prestatarios son:"<<endl;
            imprimir_prestatarios(p);
            cout<<endl<<"Las categorias son:"<<endl;
            imprimir_categorias(c);
            cout<<"\n";
            cout<<endl<<"Seleccione el codigo de prestatario que desea agregar al prestamo: ";
            cin>>codigop;
            cout<<"Seleccione el codigo de categoria que desea agregar al prestamo: ";
            cin>>codigoc;
            cout<<"Indique una descripcion del prestamo: ";
            getline(cin>>ws,d);
            mayusculas(d);
            //Esto le da la opcion al usuario de marcar el prestamo como pendiente de devolucion o devuelto
            cout<<"Presione 1 si quiere que el estado del prestamo sea devuelto o 2 si el estado del prestamo esta pendiente de devolucion: ";
            cin>>es;
            if (es==1)
                estado = false;
            else estado = true;
            //En el caso de que los codigos sean correctos se hace el llamado a la funcion
            if (codigoc < c && codigop < p){
                modificar_p(lista,c_prestamos, usuario, codigoc, codigop, d, estado); //Llamado a la funcion que modifica el prestamo
                cout<<"Se ha modificado con exito"<<endl;} //Le avisa al usuario que se modifico con exito
            //En el caso de que no sean correctos se le informa al usuario cual es el error
            if (codigoc >= c && codigop < p)
                cout<<"El prestamo no se ha modificado por motivos de que no se ha encontrado el codigo de categoria"<<endl; //Le avisa al usuario que hubo problemas con la categoria y el prestatario
            if (codigoc < c && codigop >= p)
                cout<<"El prestamo no se ha modificado por motivos de que no se ha encontrado el codigo de prestatario"<<endl;
            if (codigoc >= c && codigop >= p)
                cout<<endl<<"El prestamo no se ha agregado por motivos de que no se ha encontrado el codigo de categoria y de prestatario"<<endl;} //Le avisa al usuario que hubo problemas con la categoria y el prestatario
        else
            cout<<"No se ha podido modificar el prestamo dado que no se ha encontrado un prestamo con el codigo indicado"<<endl;} //Le avisa al usuario que no se encontro el codigo

    else
        cout<<"El prestatario no se encuentra en un prestamo"<<endl;}

//Funcion que se encarga de eliminar los prestamos
void eliminar_prestamo(Nodo* & lista, int usuario, int & c_prestamos) {
    imprimir_prestamos(lista);
    //El usuario indica el numero de prestamo a eliminar
    cout<<endl<<"Seleccione el codigo de prestamo que desea eliminar: "<<endl;
    cin>>usuario;
    if (usuario < c_prestamos)
        eliminar_p(lista, usuario, c_prestamos); //Llamado a la funcion que elimina el prestamo
    else
        cout<<"El prestamo solicitado aun no se ingreso"<<endl;}

//Funcion que se encarga de marcar como devuelto los prestamos
void devolver_prestamo(Nodo* & lista, int usuario, int c_prestamos){
    imprimir_prestamos(lista);
    //El usuario indica el numero de prestamo a marcar como devuelto
    cout<<endl<<"Seleccione el codigo de prestamo que desea marcar como devuelto: ";
    cin>>usuario;
    if (usuario < c_prestamos)
        devolver_p(lista, usuario); //Llamado a la funcion que cambia el valor del estado
    else
        cout<<"El prestamo solicitado aun no se ingreso"<<endl;}

//Case 3

/*
Funcion que se encarga de mostrar la cantidad de prestamos que se encuentran activos por cada una de las categorias.
Se declaran dos variables de tipo entero una que se encarga de contar los prestamos activos de la categoria (contador) y el otro se encarga de
que se busquen los prestamos de cada codigo de categoria (se va aumentando en 1 el codigo de categoria cuando se termina de recorrer la lista
para poder reestablecer y mostrar los prestamos que contengan el codigo de categoria posterior, esta variable tiene de nombre categoria)
*/
void cantidad_por_categoria(Nodo* lista, int c){
    int contador = 0;
    int categoria=0;
    Nodo* actual;
    Nodo* anterior=NULL;
    actual=lista;
        while (categoria < c){
            while (actual !=NULL){
                if (actual->pr.co_categoria==categoria && actual->pr.estado==true)
                    contador++;
                anterior=actual;
                actual=actual->siguiente;}
            cout<<"La cantidad de prestamos activos que contienen la categoria: "<<categoria<<endl<<"Con la descripcion: "<<ca[categoria].descripcion<<endl<<"Son: "<<contador<<endl;;
            //Se reestablecen los datos para que haga el conteo pero con el codigo de categoria posterior
            contador=0;
            actual = lista;
            anterior=NULL;
            categoria++;}}

/*
Funcion que se encarga de mostrar todos los prestamos que contengan el codigo de categoria solicitado por el usuario.
Se declara un booleano para identificar de que la categoria se encuentra ligada aunque sea a un prestamo
Se declara una variable de tipo entero llamada prestamo para identificar que numero de prestamo es el que se imprime
*/
void Listado_categorias(Nodo* & lista, int usuario, int c){
    bool encontrado = false;
    imprimir_categorias(c);
    cout<<"Seleccione el codigo de categoria: ";
    cin>>usuario;
    int prestamo = 0;
    Nodo* actual;
    Nodo* anterior=NULL;
    actual=lista;
        while (actual!=NULL){
            if (actual->pr.co_categoria==usuario){ //Compara y busca que el codigo de categoria del prestamo sea igual al ingresado por el usuario
                //Si es igual imprime todo el prestamo
                cout<<endl<<"El prestamo numero: "<<prestamo<<endl<<"Contiene el codigo de prestatario: "<<actual->pr.co_prestatario<<endl<<"Contiene el codigo de categoria: "<<actual->pr.co_categoria<<endl<<"Y la descripcion: "<<actual->pr.descripcion<<endl;
                if (actual->pr.estado==true)
                    cout<<"Todavia no se ha devuelto"<<endl;
                else cout<<"Ya se devolvio"<<endl;
                encontrado=true;
            }
            //Sigue recorriendo la lista
            anterior=actual;
            actual=actual->siguiente;
            prestamo++;}
        //En el caso de que no se haya encontrado le avisa al usuario de que la categoria no se encuentra ligada a un prestamo
        if (actual==NULL && encontrado==false)
            cout<<"No se han encontrado prestamo que contenga el codigo de categoria: "<<usuario<<endl;}

/*
Funcion que se encarga de mostrar todos los prestamos ordenados por categoria del menor al mayor.
Se declaran dos variables de tipo entero una que se encarga de contar los prestamos para identificarlos (contador) y el otro se encarga de
que se busquen los prestamos de cada categoria (se va aumentando en 1 el codigo de categoria cuando se termina de recorrer la lista
para poder reestablecer y mostrar los prestamos que contengan el codigo de categoria posterior, esta variable tiene de nombre categoria)
*/
void Listado_orden_categoria(Nodo* lista, int c){
    int categoria=0;
    int contador=0;
    Nodo* actual;
    Nodo* anterior=NULL;
    actual=lista;
        while (categoria < c){
            while (actual !=NULL){
                if (actual->pr.co_categoria==categoria){
                    cout<<endl<<"El prestamo numero: "<<contador<<endl<<"Contiene el codigo de prestatario: "<<actual->pr.co_prestatario<<endl<<"Contiene el codigo de categoria: "<<actual->pr.co_categoria<<endl<<"Y la descripcion: "<<actual->pr.descripcion<<endl;
                    if (actual->pr.estado==true)
                        cout<<"Todavia no se ha devuelto"<<endl;
                    else cout<<"Ya se devolvio"<<endl;
                }
                anterior=actual;
                actual=actual->siguiente;
                contador ++;
            }
            //Se reestablecen los datos para que haga el conteo e imprima los prestamos pero con el codigo de categoria posterior
            contador = 0;
            actual = lista;
            anterior=NULL;
            categoria++;}}

/*
Funcion que se encarga de mostrar todos los prestamos ordenados por prestatario del menor al mayor.
Se declaran dos variables de tipo entero una que se encarga de contar los prestamos para identificarlos (contador) y el otro se encarga de
que se busquen los prestamos de cada prestatario (se va aumentando en 1 el codigo de prestatario cuando se termina de recorrer la lista
para poder reestablecer y mostrar los prestamos que contengan el codigo de prestatario posterior, esta variable tiene de nombre prestatario)
*/
void Listado_orden_prestatario(Nodo* lista, int p){
    int prestatario=0;
    int contador=0;
    Nodo* actual;
    Nodo* anterior=NULL;
    actual=lista;
        while (prestatario < p){
            while (actual !=NULL){
                if (actual->pr.co_prestatario==prestatario){
                    cout<<endl<<"El prestamo numero: "<<contador<<endl<<"Contiene el codigo de prestatario: "<<actual->pr.co_prestatario<<endl<<"Contiene el codigo de categoria: "<<actual->pr.co_categoria<<endl<<"Y la descripcion: "<<actual->pr.descripcion<<endl;
                    if (actual->pr.estado==true)
                        cout<<"Todavia no se ha devuelto"<<endl;
                    else cout<<"Ya se devolvio"<<endl;

                }
                contador ++;
                anterior=actual;
                actual=actual->siguiente;
            }
            //Se reestablecen los datos para que haga el conteo e imprima los prestamos pero con el codigo de prestatario posterior
            contador=0;
            actual = lista;
            anterior=NULL;
            prestatario++;}}

/*
Funcion que se encarga de mostrar la cantidad de prestamos que se encuentran activos por cada una de los prestatarios.
Se declaran dos variables de tipo entero una que se encarga de contar los prestamos activos del prestatario (contador) y el otro se encarga de
que se busquen los prestamos de cada codigo de prestatario (se va aumentando en 1 el codigo de prestatario cuando se termina de recorrer la lista
para poder reestablecer y mostrar los prestamos que contengan el codigo de prestatario posterior, esta variable tiene de nombre categoria)
*/
void cantidad_por_prestatario(Nodo* lista, int p){
    int contador = 0;
    int prestatario=0;
    Nodo* actual;
    Nodo* anterior=NULL;
    actual=lista;
        while (prestatario < p){
            while (actual !=NULL){
                if (actual->pr.co_prestatario==prestatario && actual->pr.estado==true)
                    contador++;
                anterior=actual;
                actual=actual->siguiente;}
            cout<<"La cantidad de prestamos activos que contienen el codigo de prestatario: "<<prestatario<<endl<<"Con el nombre: "<<pres[prestatario].nombre<<endl<<"Con el apellido: "<<pres[prestatario].apellido<<endl<<"Son: "<<contador<<endl;;
            contador=0;
            actual = lista;
            anterior=NULL;
            prestatario++;}}


int main()
{
    Nodo* lista=nullptr;
    int mp = 0;
    char usuario; //Esta variable basicamente guarda la opcion que el usuario desea en los menus
    int codigo = 0; //Variable que almacena el codigo que el usuario desea modificar o eliminar
    int codigo2 = 0;
    int codigo3=0;
    int pre=0;
    int c_categoria = 0; //Variable que actua como dimension logica de las categorias
    int c_prestatario = 0; //Variable que actua como dimension logica de los prestatarios
    int c_prestamos = 0; //Variable que actua como dimension logica de los prestamos
    bool consulta;
    string a; //Variable que almacena el apellido
    string n; //Variable qu almacena el nombre
    string d; //Variable que almacena la descripcion de la categoria y del prestamo
    menu_principal(mp);
    while (mp!=4){//mientras el usuario no ingrese el numero 4
    switch (mp) {
    case 1:{ //En el caso de que el usuario ingrese 1 el programa entrara aca
        case_1(usuario);
        //cin>>usuario;
        //usuario=toupper(usuario);
        switch (usuario) {
        /*Cada uno de los case es si el usuario ingresa la letra escrita el programa deberia entrar ahi  y realizar lo que
        esta con el cout en este momento, debido a que todavia no esta finalizado*/
        case 'A':{
            agregar_categoria(c_categoria, d);
            break;}
        case 'B':{
            if (c_categoria == 0){
                cout<<"Aun no se han agregado categorias"<<endl;
                break;}
            modificar_categoria(c_categoria, codigo , d);
            break;}
        case 'C':{
            if (c_categoria == 0){
                cout<<"Aun no se han agregado categorias"<<endl;
                break;}
            eliminar_categoria(c_categoria, codigo, consulta, lista);
            break;}
        case 'D':{
            agregar_prestatario(c_prestatario, n, a);
            break;}
        case 'E':{
            if (c_prestatario == 0){
                cout<<"Aun no se han agregado prestatarios"<<endl;
                break;}
            modificar_prestatario(c_prestatario, codigo , n, a);
            break;}
        case 'F':{
            if (c_prestatario == 0){
                cout<<"Aun no se han agregado prestatarios"<<endl;
                break;}
            eliminar_prestatario(c_prestatario, codigo, consulta, lista);
            break;}
        default: {
            cout<<"Has ingresado una opcion incorrecta por lo tanto volvera al inicio"<<endl;}}
        break;}//LISTO
    case 2:{ //En el caso de que el usuario ingrese 2 el programa entrara aca
        if (c_categoria==0 && c_prestatario == 0){
            cout<<"Aun no se han agregado prestatarios ni categorias"<<endl;
            break;}
        if (c_categoria > 0 && c_prestatario == 0){
            cout<<"Aun no se han agregado prestatarios"<<endl;
            break;}
        if (c_categoria == 0 && c_prestatario > 0){
            cout<<"Aun no se han agregado categorias"<<endl;
            break;}
        case_2(usuario);
        switch (usuario) {
        /*Cada uno de los case es si el usuario ingresa la letra escrita el programa deberia entrar ahi  y realizar lo que
        esta con el cout en este momento, debido a que todavia no esta finalizado*/
        case 'A':{
            agregar_prestamo(lista, c_prestamos, c_prestatario, c_categoria, codigo, codigo2, d);
            break;}
        case 'B':{
            if (c_prestamos == 0){
                cout<<"Aun no se han agregado prestamos"<<endl;
                break;}
            modificar_prestamo(lista, c_prestamos, c_prestatario, c_categoria, codigo, codigo2, codigo3, d, consulta);
            break;}
        case 'C':{
            if (c_prestamos == 0){
                cout<<"Aun no se han agregado prestamos"<<endl;
                break;}
            eliminar_prestamo(lista, codigo, c_prestamos);
            break;}
        case 'D':{
            if (c_prestamos == 0){
                cout<<"Aun no se han agregado prestamos"<<endl;
                break;}
            devolver_prestamo(lista, codigo, c_prestamos);
            break;}
        default: {
            cout<<"Has ingresado una opcion incorrecta por lo tanto volvera al inicio"<<endl;}}
        break;}

    case 3:{ //En el caso de que el usuario ingrese 3 el programa entrara aca
        if (c_prestamos == 0){
            cout<<"Aun no se han agregado prestamos"<<endl;
            break;}
        case_3(usuario);
        switch (usuario) {
        /*Cada uno de los case es si el usuario ingresa la letra escrita el programa deberia entrar ahi  y realizar lo que
            esta con el cout en este momento, debido a que todavia no esta finalizado*/
        case 'A':{
            cantidad_por_categoria(lista, c_categoria);
            break;}
        case 'B':{
            Listado_categorias(lista, codigo, c_categoria);
            break;}
        case 'C':{
            char a=0;
            cout<<"Si desea clasificar el listado por categoría presione C y si desea clasificarlo por prestatario presione P: ";
            cin>>a;
            a=toupper(a);
            if (a=='C')
                Listado_orden_categoria(lista, c_categoria);
            if (a=='P')
                Listado_orden_prestatario(lista, c_prestatario);
            if (a!='P'&&a!='C')
                cout<<"La opcion ingresada es incorrecta"<<endl;
            break;}
        case 'D':{
            cantidad_por_prestatario(lista, c_prestatario);
            break;}
        default: {

            cout<<"Has ingresado una opcion incorrecta por lo tanto volvera al inicio"<<endl;}}
        break;}//LISTO
    default:{
       cout<<"Ingreso una opcion incorrecta"<<endl;}
    }
    menu_principal(mp); //Aca el programa le vuelve a solicitar una opcion del menu principal
    } //En el caso de que el usuario ingrese 4 el programa entrara aca y finalizara el programa
    cout<<"Gracias"<<endl;
    return 0;}

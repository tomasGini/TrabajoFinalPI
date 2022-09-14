#include<iostream>
#include<map>
#include<string>
#include<list>

using namespace std;


void alta_de_pacientes(int dni, string nombre, string apellido, string numero_telefono){
    
    cout << "══Dar de alta a un paciente══"<<endl;
    
    cout << "Ingrese el numero de DNI: " << endl;
    cin >> dni;
    cout << "Ingrese el nombre: " << endl;
    cin >> nombre;
    cout << "Ingrese el apellido: " << endl;
    cin >> apellido;
    cout << "Ingrese el numero de telefono: " << endl;
    cin >> numero_telefono;

    list<string> lista_datos_pacientes{nombre, apellido, numero_telefono};
    map<int, list<string>> diccionario_pacientes;               //Se crea el diccionario e indico la key: dni(int)

    diccionario_pacientes.insert(pair<int, list<string>>(dni, lista_datos_pacientes));

    cout << "Presione ENTER para continuar ... ";cin.get();
}

// void baja_de_pacientes(){
//     diccionario_pacientes.erase(dni);
// }
// void modificaciones_de_pacientes(diccionario_pacientes){

// }

int main()
{
    int opcion_caso4, opcion_administrar_turnos;

    cout<<"══Administrar Pacientes══"<<endl;
    cout<<"Ingrese la opcion deseada: "<<endl;
    cout<<"1. Alta de paciente"<<endl;
    cout<<"2. Modificar paciente"<<endl;
    cout<<"3. Baja de paciente"<<endl;
    cout<<"4. Listado de turnos"<<endl;
    cout<<"0. Volver al Menu principal"<<endl;
    cin>>opcion_administrar_turnos;

    switch (opcion_administrar_turnos)
    {
    case 1:
        alta_de_pacientes(0,"","",""); // Funcion alta_de_pacientes() a corregir...
        break;
    case 2:
        // modificar_pacientes()
        break;
    case 3:
        // baja_pacientes()
        break;
    case 4:
        cout<<"1. Listado completo"<<endl;
        cout<<"2. Busqueda"<<endl;
        cin>>opcion_caso4;

        switch (opcion_caso4)
        {
        case 1:
            // Listado completo
            break;
        case 2:
            // Busqueda paciente
            break;
        }
        break;
    case 0:
        // Menu anterior
    break;
    }

}

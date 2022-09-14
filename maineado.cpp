#include<iostream>
#include<map>
#include<string>
#include<list>

using namespace std;


int dni;
string nombre;
string apellido;
string numero_telefono;

int main(int dni, string nombre, string apellido, string numero_telefono)
{
    cout << "Dar de alta a un paciente."<<endl;
    
    cout << "Ingrese el numero de DNI: " << endl;
    cin >> dni >> endl;
    
    cout << "Ingrese el nombre" << endl;
    cin >> nombre >> endl;
    
    cout << "Ingrese el apellido" << endl;
    cin >> apellido >> endl;
    
    cout << "Ingrese el numero de telefono" << endl;
    cin >> numero_telefono >> endl;

    
    list<string> lista_datos_pacientes{nombre, apellido, numero_telefono};
    map<int, list<string>> diccionario_pacientes;               //Se crea el diccionario e indico la key: dni(int)

    diccionario_pacientes.insert(pair<int, list<string>>(dni, lista_datos_pacientes));

    for (auto pair : diccionario_pacientes) {
    cout << pair.first << " - ";
    for (auto datos : pair.second){
        cout << datos << ", ";
    }
    cout << endl;

    return 0;
}


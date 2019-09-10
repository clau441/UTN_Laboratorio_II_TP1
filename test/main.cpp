#include <iostream>
#include "funciones.h"

using namespace std;

int main()
{
    char texto[11]="hola mundo";

    // obtenerCad(texto);

    modificarLetra(&texto[2]);
    cout << texto;


    return 0;
}
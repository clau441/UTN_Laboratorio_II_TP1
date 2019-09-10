#include <iostream>

using namespace std;

void obtenerCad(char *texto)
{
    int cantidad=0;
    int x=0;
    while (texto[x]!='\0')
    {
        cantidad++;
        x++;
    }
    
    cout << cantidad <<endl;
}


void modificarLetra(char *unaletra)
{
    *unaletra='B';
}
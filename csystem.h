//#############################################################################
//                             AVIS SOFTWARE                                 //
//                     (Productos de Software Libre)                         //
//                                                                           //
//#############################################################################
//
//  **************************************************************************
//  * El software libre no es una cuestion economica sino una cuestion etica *
//  **************************************************************************
//
// Avis Software es marca registrada.
//
// Este programa es software libre; puede redistribuirlo o modificarlo bajo los
// terminos de la Licencia Publica General de GNU tal como se publica por la
// Free Software Foundation; ya sea la version 3 de la Licencia, o (a su
// eleccion) cualquier version posterior.
//
// Este programa se distribuye con la esperanza de que le sea util, pero SIN
// NINGUNA GARANTIA; sin incluso la garantia implicita de MERCANTILIDAD o
// IDONEIDAD PARA UN PROPOSITO PARTICULAR.
//
// Vea la Licencia Publica General GNU para mas detalles.
//
// Deberia haber recibido una copia de la Licencia Publica General de GNU
// junto con este programa, si no es asi, escriba a la Free Software Foundation,
// Inc, 59 Temple Place - Suite 330, Boston, MA 02111-1307, EE.UU.
//
//#############################################################################
// ARCHIVO             : csystem.h
// AUTOR               : Ruben Alberto Calabuig.
// COLABORADORES       : Sebastian Florin.
// VERSION             : 5.04 estable.
// FECHA DE CREACION   : 08/11/2011.
// ULTIMA ACTUALIZACION: 29/08/2012.
// LICENCIA            : GPL (General Public License) - Version 3.
//=============================================================================
// SISTEMA OPERATIVO   : Linux (Ubuntu) / Windows XP / Windows 7.
// IDE                 : Code::Blocks - 8.02 / 10.05
// COMPILADOR          : GNU GCC Compiler (Linux) / MinGW (Windows).
// LICENCIA            : GPL (General Public License) - Version 3.
//=============================================================================
// DEDICATORIA: A mi Padre Amadeo Calabuig (28/12/1924 - 10/03/1995).
//=============================================================================
// DESCRIPCION:
//             Este archivo incluye la definicion de la libreria csystem
//
//             Las funciones csystem permiten compatibilidad entre Linux y
//             Windows en algunas funciones basicas del modo consola como:
//             cls() y pause(), y agrega otras como getch(), generando una
//             interfaz que permita realizar codigos verdaderamente portables.
//
//-------------------------------------------------------------------------------
// ARCHIVO DE CABECERA: #include csystem.h
//
// FUNCIONES DEFINIDAS:
//==============================================================================|
//     NOMBRE     |  TIPO  |                    ACCION                          |
//================+========+====================================================|
// cls()          |  void  | Limpia la pantalla en modo consola.                |
//----------------+--------+----------------------------------------------------|
// confirm()      |  bool  | Confirma por SI o por NO                           |
//----------------+--------+----------------------------------------------------|
// getch()        |  char  | Lee un caracter por teclado.                       |
//----------------+--------+----------------------------------------------------|
// gotoxy(x,y)    |  void  | Ubica el cursor en las coordenadas x,y de la       |
//                |        | pantalla.                                          |
//----------------+--------+----------------------------------------------------|
// pause()        |  void  | Realiza una pausa hasta que se presione la tecla   |
//                |        | ENTER.                                             |
//----------------+--------+----------------------------------------------------|
// randomize()    |  void  | Inicializa la secuencia de numeros aleatorios.     |
//----------------+--------+----------------------------------------------------|
// random(n)      |  int   | Devuelve un numero aleatorio entero entre 0 y n-1. |
//================+========+====================================================|
//
//-------------------------------------------------------------------------------
// MODIFICACIONES REALIZADAS EN ESTA VESION
//
// Se ha incluido la libreria "ctime" para un correcto funcionamiento de las
// funciones randomize() y random().
//
// AUTOR DE LA MODIFICACION: Sebastian Florin.
//
/////////////////////////////////////////////////////////////////////////////////

#ifndef CSYSTEM_H
#define CSYSTEM_H

//*****************************************************************************
//                             INCLUSIONES ESTANDAR
//=============================================================================
#include <iostream> // Libreria que incluye los flujos de entrada y salida para
                    // el lenguaje C++.
                    //
                    // En esta libreria se desarrollan las definiciones de las
                    // clases "cin" y "cout".

#include <cstdlib>  // Libreria que incluye funciones relacionadas con el
                    // sistema estandar para el lenguaje C++.
                    //
                    // En esta libreria se desarrolla, entre otras, a las
                    // funciones "system()" y "time()", utilizadas para el
                    // desarrollo de algunas de las funciones de este espacio
                    // de nombres, tales como: cls(), randomize() y random().

#include <cstdio>   // Libreria que incluye funciones relacionadas con el
                    // sistema de entrada/salida estandar par el lenguaje C++.
                    //
                    // En esta libreria se desarrolla, entre otras, la funcion
                    // "printf()", utilizada en la funcion gotoxy().

#include <ctime>   // Libreria que incluye funciones relacionadas con el
                   // tiempo.

//*****************************************************************************
//                DEFINICION DEL ESPACIO DE NOMBRES sys
//*****************************************************************************
namespace sys
{
  //***************************************************************************
  //                     FUNCIONES COMUNES PARA LINUX Y WINDOWS
  //===========================================================================
  // FUNCION   : void cls().
  // ACCION    : Borra la pantalla en modo consola.
  // PARAMETROS: NADA.
  // DEVUELVE  : NADA
  //...........................................................................
  // NOTA: Esta funcion presenta dos versiones diferentes, una par el sistema
  //       operativo WINDOWS, y otra para LINUX. Ambas estan definidas a
  //       continuacion.
  //---------------------------------------------------------------------------
  #ifdef _WIN32 // VERSION PARA WINDOWS.
    void cls()
    {
      system("cls");
    }
  #endif // Fin de version para Windows.

  //---------------------------------------------------------------------------
  #ifdef _LINUX // VERSION PARA LINUX
    void cls()
    {
      system("clear");
    }
  #endif // Fin de version para Linux.

  //===========================================================================
  // FUNCION   : char getch().
  // ACCION    : Lee un caracter por teclado.
  // PARAMETROS: NADA.
  // DEVUELVE  : char --> el caracter leido.
  //---------------------------------------------------------------------------
   char getch()
   {
      const char LF=10; // LINEFID --> ASCII del caracter de salto de linea.
      char aux;

      aux = std::cin.get();
      if(aux==LF) // Si quedo un LF en el buffer, vuelve a leer.
      {
          aux=std::cin.get();
      }

      return aux;
   }


  //===========================================================================
  // FUNCION   : bool confirm().
  // ACCION    : Confirma por SI o por NO
  // PARAMETROS: NADA.
  // DEVUELVE  : bool --> true  si se presiono 'S','s','Y' o 'y'.
  //                      false si se presiono 'N' o 'n'.
  //---------------------------------------------------------------------------
    bool confirm()
    {
        char option;
        while(1)
        {
            option = getch();
            switch(option)
            {
                case 's':
                case 'S':
                case 'y':
                case 'Y': return true;

                case 'n':
                case 'N': return false;
            }
        }
    }


  //===========================================================================
  // FUNCION   : void gotoxy(int x,int y).
  // ACCION    : Posiciona el cursor en la fila x, columna y.
  // PARAMETROS: int x -> fila en la que debe posicionarse el cursor.
  //             int y -> columna en la que debe posicionarse el cursor.
  // DEVUELVE  : NADA.
  //---------------------------------------------------------------------------
  void gotoxy(int x, int y)
  {
     printf("\033[%d;%dH", y, x); 	// Posiciona el cursor en X, Y
  }

  //===========================================================================
  // FUNCION   : void pause().
  // ACCION    : Realiza una pausa hasta que se presione ENTER.
  // PARAMETROS: NADA.
  // DEVUELVE  : NADA.
  //---------------------------------------------------------------------------
  void pause()
  {
    const char LF=10; // LINEFID --> ASCII del caracter de salto de linea.
    char aux;
    aux = std::cin.get();
    if(aux==LF) // Si quedo un LF en el buffer, vuelve a leer.
    {
      std::cin.get();
    }
  }

  //===========================================================================
  // FUNCION   : void randomize()
  // ACCION    : Inicializa la secuencia de numeros aleatorios.
  // PARAMETROInicializa la secuencia de numeros aleatorios.S: NADA.
  // DEVUELVE  : NADA.
  //...........................................................................
  // NOTA: Esta funcion utiliza la funcion time() y debe ser utilizada por
  //       unica vez al comenzar la funcion main() del programa.
  //---------------------------------------------------------------------------
  void randomize()
  {
    time_t t;
    srand((unsigned) time(&t));
  }

  //===========================================================================
  // FUNCION   : int random(int n)
  // ACCION    : Devuelve un numero aleatorio entero entre 0 y n-1.
  // PARAMETROS: int n -> numero tope del rango aleatorio.
  // DEVUELVE  : int n -> numero aleatorio generado entre 0 y n-1.
  //----------------------------------------------------------------------
  int random(int n)
  {
    return rand() % n;
  }

} // Fin del espacio de nombres "sys".
//*****************************************************************************

#endif // CSYSTEM_H
//### FIN DE ARCHIVO ##########################################################

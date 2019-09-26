#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "csystem.h"

using std::setw;
using std::left;
using std::right;

using namespace std;

const char ALUMNOS[]="alumnos.dat";
const char MATERIAS[]="materias.dat";
const char ALUMAT[]="alumnosmateria.dat";

const int ANIOACTUAL=2019;
/// constante usado para validar que el año en el alta o modificacion de un Alumno
/// sea menor al año en curso

void ceroAtras(int esteNum){
    if (esteNum < 10){
        cout<<"0"<<esteNum;
    }
    else{
        cout<<esteNum;
    }
}

/////////////////
// ESTRUCTURAS //
/////////////////

struct tMateria{
    int id_materia;
    char nombreM[50];
    char profesorM[50];
    bool eliminado;
};

struct tAlumno{
    int legajo;
    char nombre[50];
    int dia;
    int mes;
    int anio;
    bool eliminado;
};

struct tAsignacion{
    int id_materia;
    int legajo;
    bool eliminado;
};

//////////////////
// VALIDACIONES //
//////////////////

//____________________//
// VALIDACION DE CHAR //
//--------------------//

bool validarChar(char *palabra){
    bool valido=true;
    int x=0;

    if (palabra[0]=='\0' || palabra[0] == ' ')
    {
        return false;
    }

    while(palabra[x]!='\0')
    {
        if (!((palabra[x]>='a' && palabra[x]<='z') || (palabra[x]>='A' && palabra[x]<='Z') || (palabra[x]==' ')))
        {
            valido=false;
        }
        x++;
    }

    return valido;
} // TERMINADO


//_______________________//
// VALIDACION DE NUMEROS //
//-----------------------//

bool validarEntero(char *numero){
    bool  valido=true;
    int x=0;

    if (numero[0] =='\0' || numero[0] == ' ')
    {
        valido = false;
    }

    while(numero[x]!='\0')
    {
        if ((numero[x]<'0' || numero[x]>'9'))
        {
            valido=false;
        }
        x++;
    }

    return valido;
} //TERMINADO

//_______________________//
// VALIDACION DE FECHA   //
//-----------------------//

//__________________________//
// VALIDACION DE FECHA DIA  //
//--------------------------//

bool validarDiaRango(char *numero){
    bool valido=true;
    int dia=atoi(numero);
    if(dia<1 || dia>31){
        valido=false;
    }
    return valido;
} //TERMINADO

//__________________________//
// VALIDACION DE FECHA MES  //
//--------------------------//

bool validarMesRango(char *numero){
    bool valido=true;
    int mes=atoi(numero);
    if(mes<1 || mes>12){
        valido=false;
    }
    return valido;
} // TERMINADO

//___________________________//
// VALIDACION DE FECHA ANIO  //
//---------------------------//

bool validarAnioRango(char *numero){
    bool valido=true;
    int anio=atoi(numero);
    if(anio<1900 || anio>=ANIOACTUAL){
        valido=false;
    }
    return valido;
} //TERMINADO

//--------------------------------------------------------------//

//__________//
// MATERIAS //
//----------//

int obtenerIDM(){
    FILE *p;
    p=fopen(MATERIAS,"ab");
    if (p==NULL) exit(1);
    fseek(p,0,SEEK_END);
    return (ftell(p)/sizeof(tMateria)+1);
} // TERMINADO

void altaMateria(tMateria *mat){
    cout << setw(44) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(35) << right << "ALTA DE MATERIA" << setw(20) <<right <<"|" <<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout <<endl;

    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " "<< "El ID DE ESTA MATERIA ES  " << mat->id_materia<<endl;
    cout << setw(45) << left << " "<< "INGRESE EL NOMBRE DE LA MATERIA A DAR DE ALTA" << endl;
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;

    cout << setw(45) << left << " "<< cin.getline(mat->nombreM,50);

    bool vm=validarChar(mat->nombreM);

    while(!vm){
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< " HA INGRESADO UN CARACTER NO VALIDO"<< endl;
        cout << setw(45) << left << " "<< " INGRESE EL NOMBRE DE LA MATERIA A DAR DE ALTA DAR DE ALTA" << setw(20) <<right <<"|" << endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< cin.getline(mat->nombreM,50);

        vm=validarChar(mat->nombreM);
    }

    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " "<< "INGRESE EL NOMBRE DEL PROFESOR A CARGO DE LA MATERIA" << endl;
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << endl;
    cout << setw(45) << left << " "<< cin.getline(mat->profesorM,50);

    bool vp=validarChar(mat->profesorM);
    while (!vp)
    {
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< " HA INGRESADO UN CARACTER NO VALIDO"<< endl;
        cout << setw(45) << left << " "<< " INGRESE EL NOMBRE DEl PROFESOR A CARGO DE LA MATERIA" << setw(20) <<right <<"|" << endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< cin.getline(mat->profesorM,50);

        vp=validarChar(mat->profesorM);
    }


    mat->eliminado=false;
} // TERMINADO CON VALIDACION CHAR

bool guardarMateria(tMateria mat){
    bool guardo=false;
    FILE *p;
    p=fopen(MATERIAS,"ab");
    if(p!=NULL)
        {
            fwrite(&mat,sizeof(tMateria),1,p);
            fclose(p);
            guardo=true;
        }
    return guardo;
} // TERMINADO 

void mostrarMateria(tMateria mat){
    cout << setw(13) << left << mat.id_materia << setw(35) << left << mat.nombreM << setw(65) << left << mat.profesorM <<endl;
}

void leerMaterias(){
    tMateria mat;
    FILE *p;
    p=fopen(MATERIAS,"rb");
    if (p!=NULL)
    {
        cout << setw(44) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << "     LISTADO DE MATERIAS DADOS DE ALTA EN EL SISTEMA" << setw(3) <<right <<"|" <<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << endl;
        cout << setw(40) << left << " "<< "ID MATERIA" << setw(18)<< right <<"NOMBRE MATERIA "<< setw(36)<< "PROFESOR A CARGO"<<endl;
        cout <<endl;

        while(fread(&mat,sizeof(tMateria),1,p))
        {
            cout << setw(40) << left << " ";
            mostrarMateria(mat);
        }
        fclose(p);
    }
}

//--------------------------------------------------------------//

//_________//
// ALUMNOS //
//---------//

int obtenerIDA(){
    FILE *p;
    p=fopen(ALUMNOS,"ab");
    fseek(p,0,SEEK_END);
    return (ftell(p)/sizeof(tAlumno)+1);
} // TERMINADO 

void altaAlumno(tAlumno *alum){
    char diachar[1000];
    char meschar[1000];
    char aniochar[1000];

    cout << setw(44) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(35) << right << "ALTA DE ALUMNO" << setw(20) <<right <<"|" <<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << endl;
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << setw(44) << left << " "<<" INGRESE EL NOMBRE Y APELLDIO DEL ALUMNO A DAR DE ALTA" << endl;
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << setw(44) << left << " "<< cin.getline(alum->nombre,50);


    bool x=validarChar(alum->nombre);

    while(!x){
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< " HA INGRESADO UN CARACTER NO VALIDO"<< endl;
        cout << setw(45) << left << " "<< " INGRESE EL NOMBRE Y APELLDIO DEL ALUMNO A DAR DE ALTA" << setw(20) <<right <<"|" << endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cin.getline(alum->nombre,50);
        x=validarChar(alum->nombre);
    }

    cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " " << " INGRESE EL DIA DE NACIMIENTO " << endl;
    cout << setw(45) << left << " " << " IMPORTANTE=tiene que ser numerico entre 1 y 31"<< endl;
    cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;

    cout << setw(45) << left << " " << cin.getline(diachar,1000);

    bool v=validarEntero(diachar) , dr=validarDiaRango(diachar);

    while((!v) || (!dr)){
        cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " " <<  " HA INGRESADO UN FORMATO DE DIA NO VALIDO"<< endl;
        cout << setw(45) << left << " " <<  " INGRESE EL DIA DE NACIMIENTO "<< endl;
        cout << setw(45) << left << " " <<  " IMPORTANTE=tiene que ser numerico entre 1 y 31"<< endl;
        cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " " << cin.getline(diachar,1000);

        v=validarEntero(diachar);
        dr=validarDiaRango(diachar);
    }

    int dia=atoi(diachar);

    alum->dia=dia;

    cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " " << " INGRESE EL MES DE NACIMIENTO " << endl;
    cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
    cout << endl;
    cout << setw(45) << left << " " << cin.getline(meschar,1000);

    bool mr=validarMesRango(meschar);

    while((!v) || (!mr)){
        cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " " << " HA INGRESADO UN FORMATO DE MES NO VALIDO"<< endl;
        cout << setw(45) << left << " " << " INGRESE EL MES DE NACIMIENTO"<< endl;
        cout << setw(45) << left << " " << " IMPORTANTE=tiene que ser numerico entre 1 y 12"<< endl;
        cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
        cin.getline(meschar,1000);

        v=validarEntero(meschar);
        mr=validarMesRango(meschar);
    }

    int mes=atoi(meschar);

    alum->mes=mes;


    cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " " << " INGRESE EL AÑO DE NACIMIENTO  " << endl;
    cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;

    cout << setw(45) << left << " " << cin.getline(aniochar,1000);

    bool ar=validarAnioRango(aniochar);

    while((!v) || (!ar)){
        cout << setw(45) << left << " " << " ----------------------------------------------------- "<< endl;
        cout << setw(45) << left << " " << " HA INGRESADO UN FORMATO DE AÑO NO VALIDO "<< endl;
        cout << setw(45) << left << " " << " INGRESE EL AÑO DE NACIMIENTO "<< endl;
        cout << setw(45) << left << " " << " IMPORTANTE=tiene que menor a "<< ANIOACTUAL << endl;
        cout << setw(45) << left << " " << " ----------------------------------------------------- "<< endl;
        cin.getline(aniochar,1000);

        v=validarEntero(aniochar);
        ar=validarAnioRango(aniochar);
    }

    int anio=atoi(aniochar);

    alum->anio=anio;

    alum->eliminado=false;
} // TERMINADO VALIDADO POR CHAR 

bool guardarAlumno(tAlumno alum){
    bool guardo=false;
    FILE *p;
    p=fopen(ALUMNOS,"ab");
    if(p!=NULL)
        {
            fwrite(&alum,sizeof(tAlumno),1,p);
            fclose(p);
            guardo=true;
        }
    return guardo;
} // TERMINADO

void mostrarAlumno(tAlumno alum){

    cout << setw(45) << left << " "<< alum.legajo << setw(20) << right <<  alum.nombre <<setw(33);
    ceroAtras(alum.dia);
    cout << "/";
    ceroAtras(alum.mes);
    cout <<"/" << alum.anio <<endl;
}

void leerAlumno(){
    tAlumno alum;
    FILE *p;
    p=fopen(ALUMNOS,"rb");
    if (p!=NULL)
    {

        cout << setw(43) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << " LISTADO DE ALUMNOS DADOS DE ALTA EN EL SISTEMA  |" <<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << endl;
        cout << setw(40) << left << " "<< "ID ALUMNO" << setw(20)<< right <<"NOMBRE Y APELLIDO "<< setw(33)<< "FECHA DE NACIMIENTO"<<endl;
        while(fread(&alum,sizeof(tAlumno),1,p))
        {
            mostrarAlumno(alum);
        }
        fclose(p);
    }
}

void mostrarLegajoAlumno(int leg){
    tAlumno alum;
    FILE *p;
    p=fopen(ALUMNOS,"rb");
    if (p!=NULL)
    {
        while(fread(&alum,sizeof(tAlumno),1,p))
        {
            if (leg==alum.legajo)
            {
                mostrarAlumno(alum);
            }
        }
        fclose(p);
    }

}

//--------------------------------------------------------------//

//________________________________//
// ASIGNACION DE ALUMNO A MATERIA //
//--------------------------------//

bool buscarAlumnoID(int legajo){
    tAlumno alum;
    bool existeAlum=false;
    FILE *p;
    p=fopen(ALUMNOS,"rb");
    if(p!=NULL)
    {
        while(fread(&alum,sizeof(tAlumno),1,p)!=0)
        {
            if(legajo==alum.legajo)
                {
                    existeAlum=true;
                    fclose(p);
                }
        }
        return existeAlum;
    }
} // TERMINADO

bool buscarMateria(int id_mat){
    tMateria mat;
    bool existeMat=false;
    FILE *p;
    p=fopen(MATERIAS,"rb");
    if(p!=NULL)
    {
        while (fread(&mat,sizeof(tMateria),1,p)==1)
        {
            if (id_mat==mat.id_materia)
            {
                existeMat=true;
                fclose(p);
            }
        }
        return existeMat;
    }
} // TERMINADO

int buscarLegajo(char alumno[50]){
    tAlumno alum;
    int legajo=0;
    FILE *p;
    p=fopen(ALUMNOS,"rb");
    if(p!=NULL)
    {
        while(fread(&alum,sizeof(tAlumno),1,p)!=0)
        {
            if(strcmp(alumno, alum.nombre)==0)
                {
                    legajo=alum.legajo;
                    fclose(p);
                }
        }
        return legajo;
    }
} // TERMINADO

bool guardarAlumMat(int legajo, int id_materia){
    tAsignacion alta;
    bool guardo=false;
    FILE *p;
    p=fopen(ALUMAT,"ap");
    if(p!=NULL)
    {
        alta.legajo=legajo;
        alta.id_materia=id_materia;
        alta.eliminado=false;
        fwrite(&alta,sizeof(tAsignacion),1,p);
        fclose(p);
        guardo=true;
    }
    return guardo;
} // TERMINADO

void altaAsigMat(){
    bool salir=true;
    char legajochar[50];

    cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
    cout << setw(45) << left << " "<< "| INGRESE EL LEGAJO DEL ALUMNO A DAR DE ALTA           |" << endl;
    cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
    cout << setw(45) << left << " "<< "  LEGAJO : " << cin.getline(legajochar,1000);
    bool e=validarEntero(legajochar);

    while (!e ){
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< " HA INGRESADO UN CARACTER NO VALIDO"<< endl;
        cout << setw(45) << left << " "<< " INGRESE EL LEGAJO DEL ALUMNO" << endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< "  LEGAJO : " << cin.getline(legajochar,1000);
    
        e=validarEntero(legajochar);
    }    

    int leg=atoi(legajochar);
    // int id_mat;
    bool vid=buscarAlumnoID(leg);

    if(vid){
        
        char op[1000];


        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< " EL LEGAJO CARGADO CORRESPONDE AL ALUMNO"<< endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        mostrarLegajoAlumno(leg);
        cout << setw(45) << left << " "<< "¿ES EL ALUMNO QUE DESEA DAR DE ALTA EN MATERIA?"<<endl;
        cout << setw(45) << left << " "<< " 1 (SI) O 2 (NO) " <<endl;
        cout << setw(45) << left << " "; 
        cout << setw(45) << left << " "<< cin.getline(op,1000);
        bool v=validarEntero(op);
        while(!v){
            cout << setw(45) << left << " "<< "OPCION NO VALIDA!!! - INGRESE LA OPCION CORRECTA 1 (SI) O 2 (NO) "<<endl;
            cout << setw(45) << left << " "<< cin.getline(op,1000);
            v=validarEntero(op);
        }

        int op2=atoi(op);

        switch (op2){
        case 1:{
            char idchar[1000];
            cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
            cout << setw(45) << left << " "<< "ELIJA DE LA SIGUIENTE LISTA EL ID DE LA MATERIA A LA QUE" <<endl; 
            cout << setw(45) << left << " "<< "SE DARA DE ALTA AL ALUMNO"<< endl;
            cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
            cout << endl;
            leerMaterias();
            cout << endl;
            cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
            cout << setw(45) << left << " "<< "POR FAVOR INGRESE EL ID DE LA MATERIA A LA QUE QUIERE SE" <<endl;
            cout << setw(45) << left << " "<< "DARA DE ALTA EL ALUMNO" <<endl;
            cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
            cout << setw(45) << left << " "<< cin.getline(idchar,1000);

            bool vid=validarEntero(idchar);
            while(!vid){
                cout << setw(45) << left << " "<< "HA INGRESADO UN CARACTER INCORRECTO" << endl;
                cout << setw(45) << left << " "<< "DEBE INGRESAR NUMEROS ENTEROS" << endl;
                cout << setw(45) << left << " "<< cin.getline(op,1000);
                vid=validarEntero(idchar);
            }

            // cin >> id_mat;
            //cin.ignore();

            int id_mat=atoi(idchar);
            if(buscarMateria(id_mat)){
                if(guardarAlumMat(leg, id_mat)){
                    cout << setw(45) << left << " "<< "EL ALUMNO SE ASIGNO CORRECTAMENTE A LA MATERIA SOLICITADA";
                }
            }
            else{
                    cout << setw(45) << left << " "<< "EL ALUMNO NO SE PUDO ASIGNAR CORRECTAMENTE A LA MATERIA SOLICITADA" << endl;
                    cout << setw(45) << left << " "<< "POR FAVOR PRESIONE ENTER PARA INTENTARLO NUEVAMENTE" << endl;
                }           
            }
            break;
        
        case 2:{
                salir=false;
            }
            break;
        
        default:{
                cout << setw(45) << left << " "<< "OPCION NO VALIDA"<<endl;
            }
            break;

        }
    }else{
             cout << setw(45) << left << " "<< "El LEGAJO NO EXISTE";
         }

} // TERMINADO CON VALIDACION POR CHAR Y VALIDACION DE LEGAJO TRAYENDO NOMBRE DE ALUMNO Y FECHA DE NACIMIENTO

void mostarAsigMat(tAsignacion alta){
    if (alta.eliminado==false)
    {
        cout << setw(45) << left << " "<< alta.legajo << alta.id_materia <<endl;
    }
}

void leerAsigMat(){
    tAsignacion alta;
    FILE *p;
    p=fopen(ALUMAT,"rb");
    if(p!=NULL)
        {
            cout << setw(44) << left << " "<< "--------------------------------------------------------" <<endl;
            cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
            cout << setw(45) << left << " "<< "|" <<  "        MOSTRAR ASIGNACION ALUMNOS POR MATERIA" << setw(9) <<right <<"|" <<endl;
            cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
            cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
            cout << endl;
            cout << setw(45) << left << " "<< "LEGAJO"<< "MATERIA" << endl;

            while (fread(&alta,sizeof(tAsignacion),1,p))
            {
                mostarAsigMat(alta);
            }
        fclose(p);
        }
}

//________________________//
// MODIFICAR DATOS ALUMNO //
//------------------------//

bool modificarFechAlum(int legajo){
    tAlumno alum;
    bool modificado=false;
    //char alumnom[50];
    FILE *p;
    p=fopen(ALUMNOS,"rb+");
    if(p!=NULL)
    {
        //cout <<"Ingrese el nombre del Alumno"<<endl;
        //cin.getline(alumnom,50);

        while(fread(&alum,sizeof(tAlumno),1,p)==1)
        {
            if (legajo==alum.legajo)
            {
                char diachar[1000];
                char meschar[1000];
                char aniochar[1000];

                cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
                cout << setw(45) << left << " " << " INGRESE EL DIA DE NACIMIENTO " << endl;
                cout << setw(45) << left << " " << " IMPORTANTE=tiene que ser numerico entre 1 y 31"<< endl;
                cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;

                cout << setw(45) << left << " " << cin.getline(diachar,1000);

                bool v=validarEntero(diachar) , dr=validarDiaRango(diachar);

                while((!v) || (!dr)){
                    cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
                    cout << setw(45) << left << " " <<  " HA INGRESADO UN FORMATO DE DIA NO VALIDO"<< endl;
                    cout << setw(45) << left << " " <<  " INGRESE EL DIA DE NACIMIENTO "<< endl;
                    cout << setw(45) << left << " " <<  " IMPORTANTE=tiene que ser numerico entre 1 y 31"<< endl;
                    cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
                    cout << setw(45) << left << " " << cin.getline(diachar,1000);

                    v=validarEntero(diachar);
                    dr=validarDiaRango(diachar);
                }

                int dia=atoi(diachar);

                alum.dia=dia;

                cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
                cout << setw(45) << left << " " << " INGRESE EL MES DE NACIMIENTO " << endl;
                cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
                cout << endl;
                cout << setw(45) << left << " " << cin.getline(meschar,1000);

                bool mr=validarMesRango(meschar);

                while((!v) || (!mr)){
                    cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
                    cout << setw(45) << left << " " << " HA INGRESADO UN FORMATO DE MES NO VALIDO"<< endl;
                    cout << setw(45) << left << " " << " INGRESE EL MES DE NACIMIENTO"<< endl;
                    cout << setw(45) << left << " " << " IMPORTANTE=tiene que ser numerico entre 1 y 12"<< endl;
                    cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
                    cin.getline(meschar,1000);

                    v=validarEntero(meschar);
                    mr=validarMesRango(meschar);
                }

                int mes=atoi(meschar);

                alum.mes=mes;

                cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;
                cout << setw(45) << left << " " << " INGRESE EL AÑO DE NACIMIENTO  " << endl;
                cout << setw(45) << left << " " << "--------------------------------------------------------" <<endl;

                cout << setw(45) << left << " " << cin.getline(aniochar,1000);

                bool ar=validarAnioRango(aniochar);

                while((!v) || (!ar)){
                    cout << setw(45) << left << " " << " ----------------------------------------------------- "<< endl;
                    cout << setw(45) << left << " " << " HA INGRESADO UN FORMATO DE AÑO NO VALIDO "<< endl;
                    cout << setw(45) << left << " " << " INGRESE EL AÑO DE NACIMIENTO "<< endl;
                    cout << setw(45) << left << " " << " IMPORTANTE=tiene que menor a "<< ANIOACTUAL << endl;
                    cout << setw(45) << left << " " << " ----------------------------------------------------- "<< endl;
                    cin.getline(aniochar,1000);

                    v=validarEntero(aniochar);
                    ar=validarAnioRango(aniochar);
                }

                int anio=atoi(aniochar);

                alum.anio=anio;

                fseek(p,ftell(p)-sizeof alum,0);
                fwrite(&alum, sizeof alum,1,p);
                fclose(p);
                modificado=true;
            }
        }
        fclose(p);
        return modificado;
    }
} // TERMINADO VALIDADO POR CHAR ENTERO

bool modificarNomAlum(int legajo){
    tAlumno alum;

    char alumnom[50];

    FILE *p;
    p=fopen(ALUMNOS,"rb+");
    if(p!=NULL)
    {
        bool modificado=false;
        while(fread(&alum,sizeof(tAlumno),1,p)==1)
        {
            if (legajo==alum.legajo)
            {
                cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
                cout << setw(45) << left << " "<< "INGRESE EL NUEVO NOMBRE DEL ALUMNO" << endl;
                cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
                cout << endl;
                cin.getline(alumnom,50);

                bool x=validarChar(alumnom);

                while(!x){
                    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
                    cout << setw(45) << left << " "<< " HA INGRESADO UN CARACTER NO VALIDO"<< endl;
                    cout << setw(45) << left << " "<< " INGRESE EL NOMBRE Y APELLDIO DEL ALUMNO A DAR DE ALTA  " << endl;
                    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
                    cin.getline(alumnom,50);
                    x=validarChar(alumnom);
                }

                strcpy(alum.nombre,alumnom);
                fseek(p,ftell(p)-sizeof alum,0);
                fwrite(&alum, sizeof alum,1,p);
                fclose(p);
                modificado=true;
                cin.ignore();
            }
        }
        fclose(p);
        return modificado;
    }
}

void modificarAlumno(int legajo){
        char op[1000];
        bool salir=false;

        while (!salir){
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "|          ¿QUE DESEA MODIFICAR DEL ALUMNO?            |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 1.- MODIFICAR NOMBRE Y APELLIDO                      |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 2.- MODIFICAR FECHA DE NACIMIENTO                    |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 0.- SALIR                                            |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << endl;
        cout << setw(45) << left << " "<<"INGRESE UNA OPCION" << endl;

        cin.getline(op,1000);
        bool v=validarEntero(op);
        while(!v){
            cout << setw(45) << left << " "<< "HA INGRESADO UN CARACTER INCORRECTO" << endl;
            cout << setw(45) << left << " "<< "DEBE INGRESAR NUMEROS ENTEROS" << endl;
            cout << setw(45) << left << " "<<cin.getline(op,1000);
            v=validarEntero(op);
            }
        int op2=atoi(op);


        switch (op2)
        {
        case 1:
            {
                if (modificarNomAlum(legajo))
                {
                    cout << setw(45) << left << " "<< "El nombre del Alumno se modifico correctamente" << endl;
                }
                else
                {
                    cout << setw(45) << left << " "<< "El nombre no se pudo modificar" << endl;
                }
            }
            break;
        case 2:
            {
                if (modificarFechAlum(legajo))
                {
                    cout << setw(45) << left << " "<<  "Se pudo modificar la fecha de nacimiento del Alumno" <<endl;
                }
                else
                {
                    cout << setw(45) << left << " "<< "No se pudo modificar la fecha de nacimiento del Alumno" <<endl;
                }

            }
            break;

        case 0:
            {
                salir=true;
            }
            break;
        default:
                break;
        }
    }
} // TERMINADO CON VALIDAR ENTERO CHAR

void subMenuModificarAlumno(){
    bool salir=false;   
    char legajochar[1000], nombre[1000];


    cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
    cout << setw(45) << left << " "<< "| INGRESE EL LEGAJO DEL ALUMNO A MODIFICAR SUS DATOS   |" << endl;
    cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
    cout << setw(45) << left << " "<< "  LEGAJO : " << cin.getline(legajochar,1000);

    // bool v=validarChar(legajochar);
    bool e=validarEntero(legajochar);

    while (!e)
    {
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< " HA INGRESADO UN CARACTER NO VALIDO"<< endl;
        cout << setw(45) << left << " "<< " INGRESE EL LEGAJO DEL ALUMNO A MODIFICAR SUS DATOS" << endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< "  LEGAJO : " << cin.getline(legajochar,1000);
    
        e=validarEntero(legajochar);
    }
    
    int leg=atoi(legajochar);
    
    bool vid=buscarAlumnoID(leg);

    if(vid==true){
        
        char op[1000];
        cout << setw(45) << left << " "<< " EL LEGAJO CARGADO CORRESPONDE AL ALUMNO"<< endl;
        mostrarLegajoAlumno(leg);
        cout << setw(45) << left << " "<< "¿ES EL ALUMNO QUE DESEA MODIFICAR?"<<endl;
        cout << setw(45) << left << " "<< " 1 (SI) O 2 (NO) " <<endl;
        cout << setw(45) << left << " "; 
        cin>>op;

        bool v=validarEntero(op);

        while(!v){
            cout << setw(45) << left << " "<<  "OPCION NO VALIDA!!! POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
            cout << setw(45) << left << " "<<cin.getline(op,1000);
            v=validarEntero(op);
        }
        int op2=atoi(op);

        switch (op2)
        {
        case 1:
            {
                modificarAlumno(leg);
            }
            break;
        
        case 2:{
                salir=false;
            }
            break;
        
        default:
            {
                cout << setw(45) << left << " "<< "OPCION NO VALIDA"<<endl;
            }
            break;
        }

    }else{
        cout << setw(45) << left << " "<< "El LEGAJO NO EXISTE";
        
    }

} // TERMINADO



//_________________________________//
// DAR DE BAJA UN ALUMNO A MATERIA //
//---------------------------------//

void mostrarAsigM(tAsignacion alta){
    if (alta.eliminado==false)
    {
        cout << setw(45) << left << " "<< "||" << alta.id_materia << "||" << alta.legajo << endl;
    }
}

void leerAlumAsig(int legajo){
    tAsignacion alta;

    FILE *p;
    p=fopen(ALUMAT,"rb");
    if (p!=NULL)
    {
        cout << setw(45) << left << " "<< "||"<<"----ID-MATERIA----"<<"||"<<"----ID-LEGAJO---"<<"||"<<endl;
        while(fread(&alta,sizeof(tAsignacion),1,p))
        {
            if(legajo==alta.legajo && alta.eliminado==false)
            {
                mostrarAsigM(alta);
            }
        }
        fclose(p);
    }
}

bool bajaLogicaAsigMat(int materia,int legajo){
    tAsignacion asig;
    bool seborro=false;
    FILE *p;
    p=fopen(ALUMAT,"rb+");
    if(p!=NULL)
    {
        while(fread(&asig,sizeof asig,1,p)==1)
        {
            if (legajo==asig.legajo && materia==asig.id_materia)
            {
                asig.eliminado=true;
                fseek(p,ftell(p)-sizeof asig,0);
                fwrite(&asig, sizeof asig,1,p);
                fclose(p);
                seborro=true;
            }
        }
        fclose(p);
        return seborro;
    }
}

void darBajaAlumMat(){
    // int materia, legajo;
    char matchar[1000], legchar[1000];

    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " "<< " INGRESE EL LEGAJO DEL ALUMNO A DAR DE BAJA DE MATERIA  "<<endl;
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << endl;
    cout << setw(45) << left << " ";cin.getline(legchar,1000);
    
    bool e=validarEntero(legchar);

    while (!e)
        {
            cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
            cout << setw(45) << left << " "<< " HA INGRESADO UN CARACTER NO VALIDO"<< endl;
            cout << setw(45) << left << " "<< " INGRESE EL LEGAJO DEL ALUMNO A DAR DE BAJA DE MATERIA " << endl;
            cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
            cout << setw(45) << left << " "<< "  LEGAJO : " << cin.getline(legchar,1000);
    
            e=validarEntero(legchar);
    }
    
    int leg=atoi(legchar);

    bool vid=buscarAlumnoID(leg);

    if(vid==true){

        bool salir=true;
        
        char op[1000];
        cout << setw(45) << left << " "<< " EL LEGAJO CARGADO CORRESPONDE AL ALUMNO"<< endl;
        mostrarLegajoAlumno(leg);
        cout << setw(45) << left << " "<< "¿ES EL ALUMNO QUE DESEA MODIFICAR?"<<endl;
        cout << setw(45) << left << " "<< " 1 (SI) O 2 (NO) " <<endl;
        cout << setw(45) << left << " "; 
        cin>>op;

        bool v=validarEntero(op);

        while(!v){
            cout << setw(45) << left << " "<<  "OPCION NO VALIDA!!! POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
            cout << setw(45) << left << " "<<cin.getline(op,1000);
            v=validarEntero(op);
        }
        int op2=atoi(op);

        switch (op2)
        {
        case 1:{
                cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
                cout << setw(45) << left << " "<< " LAS MATERIAS ASIGNADAS AL ALUMNO SON "<<endl;
                cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
                leerAlumAsig(leg);
                cout << setw(45) << left << " "<<"INDIQUE EL ID DE LA MATERIA QUE SE DARA DE BAJA DEL ALUMNO" <<endl;
                cout << setw(45) << left << " "<< "  ID_MATERIA:  "; cin.getline(matchar,10000);

                bool m=validarEntero(matchar);

                while (!m)
                    {
                        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
                        cout << setw(45) << left << " "<< " HA INGRESADO UN CARACTER NO VALIDO"<< endl;
                        cout << setw(45) << left << " "<< " INGRESE EL ID MATERIA DAR DE BAJA DE MATERIA " << endl;
                        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
                        cout << setw(45) << left << " "<< "  ID_MATERIA : " << cin.getline(matchar,1000);
                
                        m=validarEntero(matchar);
                    }

                int materia=atoi(matchar);
                    
                if(bajaLogicaAsigMat(materia, leg))
                    {
                        cout << setw(45) << left << " "<<"LA BAJA SE REALIZO CORRECTAMENTE" <<endl;
                    }
                    else
                    {
                        cout << setw(45) << left << " "<<"LA BAJA NO SE PUDO REALIZAR CORRECTAMENTE" <<endl;
                    }
            }
            break;
        
        case 2:{
                salir=false;
            }
            break;
        
        default:
            {
                cout << setw(45) << left << " "<< "OPCION NO VALIDA"<<endl;
            }
            break;
        }

    }else{
        cout << setw(45) << left << " "<<"EL LEGAJO DEL ALUMNO NO EXISTE"<< endl;
   }

    // if (buscarAlumnoID(leg)){
    //     cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    //     cout << setw(45) << left << " "<< " LAS MATERIAS ASIGNADAS AL ALUMNO SON "<<endl;
    //     cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    //     leerAlumAsig(leg);
    //     cout << setw(45) << left << " "<<"INDIQUE EL ID DE LA MATERIA QUE SE DARA DE BAJA DEL ALUMNO" <<endl;
    //     cout << setw(45) << left << " "<< "  ID_MATERIA:  "; cin.getline(matchar,10000);

    //     bool m=validarEntero(matchar);

    //     while (!m)
    //         {
    //             cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    //             cout << setw(45) << left << " "<< " HA INGRESADO UN CARACTER NO VALIDO"<< endl;
    //             cout << setw(45) << left << " "<< " INGRESE EL ID MATERIA DAR DE BAJA DE MATERIA " << endl;
    //             cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    //             cout << setw(45) << left << " "<< "  LEGAJO : " << cin.getline(legchar,1000);
    
    //             m=validarEntero(legchar);
    //         }

    //     int materia=atoi(legchar);
        
    //     if(bajaLogicaAsigMat(materia, leg))
    //     {
    //         cout << setw(45) << left << " "<<"LA BAJA SE REALIZO CORRECTAMENTE" <<endl;
    //     }
    //     else
    //     {
    //         cout << setw(45) << left << " "<<"LA BAJA NO SE PUDO REALIZAR CORRECTAMENTE" <<endl;
    //     }

    // }
    // else
    // {
    //     cout << setw(45) << left << " "<<"EL LEGAJO DEL ALUMNO NO EXISTE"<< endl;
    // }
            

}

//_______//
// MENUS //
//-------//

void bienvenida(){
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(40) << right << "BIENVENIDOS AL PROGRAMA TP1"<< setw(15) << right <<"|" <<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cin.ignore();
    void cls();

} // TERMINADO

void subMenuMaterias(){
    bool salir=false;
    char op[1000];

    while (!salir)
    {
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 1.- ALTA DE MATERIA                                  |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 2.- LISTAR MATERIAS DADAS DE ALTA                    |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 0.- SALIR                                            |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<<cin.getline(op,1000);
        bool v=validarEntero(op);
        while(!v){
            cout << setw(45) << left << " "<< "Opcion no valida!!! - Ingrese la opcion como entero sin ingresar otro valor no deseado "<<endl;
            cout << setw(45) << left << " "<< cin.getline(op,1000);
            v=validarEntero(op);
            }
        int op2=atoi(op);

        void cls();

        switch (op2)
        {
        case 1:
            {
                void cls();
                tMateria mat;
                mat.id_materia=obtenerIDM();
                altaMateria(&mat);
                if(guardarMateria(mat))
                    {
                        cout << setw(45) << left << " "<<"LA MATERIA SE GUARDO CORRECTAME" << endl;
                    }
                else
                    {

                        cout << setw(45) << left << " "<< "LA MATERIA NO SE PUDO GUARDAR" << endl;
                    }
                cin.ignore();
            }
            break;

        case 2:
            {
                leerMaterias();
                cin.ignore();
            }
            break;

        case 0:
            {
                salir=true;
            }
            break;

        default:
            {
                cout << setw(45) << left << " "<< "OPCION NO VALIDA!!!. POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
                cout << setw(45) << left << " "<< "En caso de necesitar ayuda para elegir la opcion correcta por favor validar 9.- AYUDA" << endl;
            }
            break;
        }
    }
} // VALIDADO Y TERMINADO POR CHAR

void subMenuAlumnos(){
    bool salir=false;
    char op[1000];

    while (!salir)
    {
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 1.- ALTA DE ALUMNO                                   |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 2.- LISTAR ALUMNOS DADOS DE ALTA                     |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 0.- SALIR                                            |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cin.getline(op,1000);
        bool v=validarEntero(op);
        while(!v){
            cout << setw(45) << left << " "<< "HA INGRESADO UN CARACTER INCORRECTO" << endl;
            cout << setw(45) << left << " "<< "DEBE INGRESAR NUMEROS ENTEROS" << endl;
            cout << setw(45) << left << " "<<cin.getline(op,1000);
            v=validarEntero(op);
            }
        int op2=atoi(op);

        void cls();

        switch (op2)
        {
        case 1:
            {
                tAlumno alum;
                alum.legajo=obtenerIDA();
                altaAlumno(&alum);
                if(guardarAlumno(alum))
                {
                    cout << setw(45) << left << " "<<" EL ALUMNO SE CARGO CORRECTAMENTE";
                }
                else
                {
                    cout << setw(45) << left << " "<<" EL ALUMNO NO SE PUDO CARGAR";
                }
                cin.ignore();
            }
            break;

        case 2:
            {
                leerAlumno();
                cin.ignore();
            }
            break;

        case 0:
            {
                salir=true;
            }
            break;

        default:
            {
                cout << setw(45) << left << " "<<"OPCION NO VALIDA!!!. POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
                cout << setw(45) << left << " "<<"En caso de necesitar ayuda para elegir la opcion correcta por favor validar 9.- AYUDA" << endl;
            }
            break;

        }
    }
} // VALIDADO Y TERMINADO POR CHAR

void subMenuModificaicones(){
    bool salir=false;
    char op[1000];

    while (!salir)
    {
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 1.- MODIFICAR DATOS DE UN ALUMNO                     |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 2.- ELIMINAR ASIGNACION DE ALUMNO A UNA MATERIA      |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 0.- SALIR                                            |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< cin.getline(op,1000);
        bool v=validarEntero(op);
        while(!v){
            cout << setw(45) << left << " "<<"OPCION NO VALIDA!!!. POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
            cout << setw(45) << left << " "<<cin.getline(op,1000);
            v=validarEntero(op);
        }
        int op2=atoi(op);
        void cls();

        switch (op2)
        {
        case 1:
            {
                subMenuModificarAlumno();
                cin.ignore();
            }
            break;

        case 2:
            {
                darBajaAlumMat();
                cin.ignore();
            }
            break;

        case 0:
            {
                salir=true;
            }
            break;

        default:
            {
                cout << setw(45) << left << " "<<"OPCION NO VALIDA!!! POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
                cout << setw(45) << left << " "<<"En caso de necesitar ayuda para elegir la opcion correcta por favor validar 9.- AYUDA" << endl;
            }
            break;
        }
    }
} // VALIDADO Y TERMINADO POR CHAR

void subMenuAsignacion(){
    bool salir=false;
    char op[1000];

    while (!salir)
    {
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 1.- ASIGNACION DE ALUMNO A MATERIA                   |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 2.- LISTAR ASIGNACION DE ALUMNO A MATERIAS           |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "| 0.- SALIR                                            |" << endl;
        cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
        cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
        cout << setw(45) << left << " "<< cin.getline(op,1000);
        bool v=validarEntero(op);
        while(!v){
            cout << setw(45) << left << " "<<"OPCION NO VALIDA!!! POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
            cout << setw(45) << left << " "<< cin.getline(op,1000);
            v=validarEntero(op);
        }

        int op2=atoi(op);

        void cls();

        switch (op2)
        {
        case 1:
            {
                altaAsigMat();
                cin.ignore();
            }
            break;

        case 2:
            {
                leerAsigMat();
                cin.ignore();
                void cls();
            }
            break;

        case 0:
            {
                salir=true;
            }
            break;

        default:
            {
                cout << setw(45) << left << " "<<  "OPCION NO VALIDA!!! POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
            }
            break;
        }
    }
} // VALIDADO Y TERMINADO POR CHAR

void menu(){
    bool salir = false;
    char op[1000];

    while (!salir)
    {
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
    cout << setw(45) << left << " "<< "| 1.- MATERIAS                                         |" << endl;
    cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
    cout << setw(45) << left << " "<< "| 2.- ALUMNOS                                          |" << endl;
    cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
    cout << setw(45) << left << " "<< "| 3.- ASIGNACION DE ALUMNO A MATERIA                   |" << endl;
    cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
    cout << setw(45) << left << " "<< "| 4.- MODIFICACION DE CAMPOS                           |" << endl;
    cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
    cout << setw(45) << left << " "<< "| 0.- SALIR                                            |" << endl;
    cout << setw(45) << left << " "<< "| ---------------------------------------------------- |" << endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " "<<cin.getline(op,1000);
    bool v=validarEntero(op);
    while(!v){
        cout << setw(45) << left << " "<<  "OPCION NO VALIDA!!! POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
        cout << setw(45) << left << " "<<cin.getline(op,1000);
        v=validarEntero(op);
    }
    int op2=atoi(op);

    cin.ignore();
    void cls();

    switch (op2){
    case 1:{
            subMenuMaterias();
            cin.ignore();
        }
        break;

    case 2:{
            subMenuAlumnos();
            cin.ignore();
        }
        break;

    case 3:{
                subMenuAsignacion();
                cin.ignore();
            }
            break;

    case 4:{
                subMenuModificaicones();
                cin.ignore();
            }
            break;

    case 0:{
                salir=true;
            }
            break;

    default:{
                cout << setw(45) << left << " "<<"OPCION NO VALIDA!!! POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
                cout << setw(45) << left << " "<<"En caso de necesitar ayuda para elegir la opcion correcta por favor validar 9.- AYUDA" << endl;
            }
            break;
        }
    }
} // VALIDADO Y TERMINADO POR CHAR

void saludos(){
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(40) << right << "GRACIAS POR USAR ESTE PROGRAMA"<< setw(15) << right <<"|" <<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(40) << right << "DESARROLLADO POR CLAUDIO ACOSTA"<< setw(15) << right <<"|" <<endl;
    cout << setw(45) << left << " "<< "|" << setw(30) << right << "LEGAJO: 22728"<< setw(25) << right <<"|" <<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "|" << setw(55) << right << "|"<<endl;
    cout << setw(45) << left << " "<< "--------------------------------------------------------" <<endl;

} // TERMINADO

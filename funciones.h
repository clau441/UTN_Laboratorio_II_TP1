#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>

using std::setw;
using std::left;
using std::right;

using namespace std;

const char ALUMNOS[]="alumnos.txt";
const char MATERIAS[]="materias.txt";
const char ALUMAT[]="alumnosmateria.txt";

struct tMateria
{
    int id_materia;
    char nombreM[50];
    char profesorM[50];
    bool eliminado;
};

struct tAlumno
{
    int legajo;
    char nombre[50];
    int dia;
    int mes;
    int anio;
    bool eliminado;
};

struct tAsignacion
{
    int id_materia;
    int legajo;
    bool eliminado;
};

// Validacion //

// Validacion de CHAR //

// Validacion de Numero //



// MATERIAS

int obtenerIDM()
{
    FILE *p;
    p=fopen(MATERIAS,"ab");
    fseek(p,0,SEEK_END);
    return (ftell(p)/sizeof(tMateria)+1);
}

void altaMateria(tMateria *mat)
{
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;    
    cout << "|                                                     |" << endl;
    cout << "| ALTA DE MATERIAS  " << mat->id_materia<<           "|" << endl;
    cout << "|                                                     |" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;    
    cout <<endl;    
    cout << " INGRESE EL NOMBRE DE LA MATERIA A DAR DE ALTA" << endl;
    cin.getline(mat->nombreM,50);
    cin.ignore();
    cout << " INGRESE EL NOMBRE DEL PROFESOR A CARGO DE LA MATERIA" << endl;
    cin.getline(mat->profesorM,50);
    cin.ignore();
    mat->eliminado=false;
}

bool guardarMateria(tMateria mat)
{
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
}

void mostrarMateria(tMateria mat)
{
    cout<< setw(10) << right << "ID MATERIA" << setw(20) <<"NOMBRE MATERIA "<< endl; 
    cout << setw(5) << right << mat.id_materia << setw(15) << right << " - " << mat.nombreM << " - " << mat.profesorM <<endl;
}

void leerMaterias()
{
    tMateria mat;
    FILE *p;
    p=fopen(MATERIAS,"rb");
    if (p!=NULL)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;    
        cout << "|                                                     |" << endl;
        cout << "| LISTADO DE MATERIAS DADOS DE ALTA EN EL SISTEMA     |" << endl;
        cout << "|                                                     |" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;    
        cout <<endl;  

        while(fread(&mat,sizeof(tMateria),1,p))
        {
            mostrarMateria(mat);
        }
        fclose(p);
    }
}

// ALUMNOS

int obtenerIDA()
{
    FILE *p;
    p=fopen(ALUMNOS,"ab");
    fseek(p,0,SEEK_END);
    return (ftell(p)/sizeof(tAlumno)+5);
}

void altaAlumno(tAlumno *alum)
{
    cout << "||----------ALTA DE Alumno  " << alum->legajo << "---------------------" <<endl;
    cout << "||..............................................." <<endl;
    cout << " Ingrese Nombre Alumno" << endl;
    cin.getline(alum->nombre,50);
    cin.ignore();
    cout << " Ingrese Dia Nacimiento  " << endl;
    cin >> alum->dia;
    cin.ignore();
    cout << " Ingrese Mes Nacimiento  " << endl;
    cin >> alum->mes;
    cin.ignore();
    cout << " Ingrese Año Nacimiento  " << endl;
    cin >> alum->anio;
    cin.ignore();
    alum->eliminado=false;
}

bool guardarAlumno(tAlumno alum)
{
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
}

void mostrarAlumno(tAlumno alum)
{
    cout << '\t'<< "LEGAJO" <<  '\t' <<" - " << '\t' << '\t'<< "NOMBRE" << '\t'<< " - " << '\t' <<"FECHA DE NACIMIENTO" "-"<<endl;
    cout << '\t'<< alum.legajo << '\t' << " - " << '\t' << '\t' << alum.nombre << '\t'<< " - " << alum.dia << "/"<< alum.mes <<"/" << alum.anio << "-"<<endl;
}

void leerAlumno()
{
    tAlumno alum;
    FILE *p;
    p=fopen(ALUMNOS,"rb");
    if (p!=NULL)
    {
        while(fread(&alum,sizeof(tAlumno),1,p))
        {
            mostrarAlumno(alum);
        }
        fclose(p);
    }
}

// Asignacion a Materia //

bool buscarAlumno(char alumno[50])
{
    tAlumno alum;
    bool existeAlum=false;
    FILE *p;
    p=fopen(ALUMNOS,"rb");
    if(p!=NULL)
    {
        while(fread(&alum,sizeof(tAlumno),1,p)!=0)
        {
            if(strcmp(alumno, alum.nombre)==0)
                {
                    existeAlum=true;
                    fclose(p);
                }
        }
        return existeAlum;
    }
}

bool buscarMateria(int id_mat)
{
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
}

int buscarLegajo(char alumno[50])
{
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
}

bool guardarAlumMat(int legajo, int id_materia)
{
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
}

void altaAsigMat()
{
    char alumno[50];
    int id_mat;
    cout << "Ingrese el Nombre del Alumno" << endl;
    cin.getline(alumno,50);

    if(buscarAlumno(alumno))
    {
        cout << "El alumno existe en la bas. " << endl;
        cout << "Elija de la siguiente lista el ID de la materia a la que se dara de alta al Alumno"<< endl;
        leerMaterias();
        cout << "Por favor ingrese a que materia se dara de alta el alumno" <<endl;
        cin >> id_mat;
        if(buscarMateria(id_mat))
        {   
            int legajo=(buscarLegajo(alumno));
            if(guardarAlumMat(legajo, id_mat))
            {
                cout << "El Alumno se cargo correctamente";
            }
        }
        else
            {
                cout << "El codigo de materia elegido es incorrecto" << endl;
            }               
    }
    else
    {
        cout << "El alumno no esta dado de alta en el sistema" << endl;
    }
}

void mostarAsigMat(tAsignacion alta)
{
    if (alta.eliminado==false)
    {
    cout << '\t' << "LEGAJO"<< '\t'<< "MATERIA" << endl;
    cout << '\t' << alta.legajo << '\t'<< alta.id_materia <<endl;
    }
    
}

void leerAsigMat()
{
    tAsignacion alta;
    FILE *p;
    p=fopen(ALUMAT,"rb");
    if(p!=NULL)
        {
            while (fread(&alta,sizeof(tAsignacion),1,p))
            {
                mostarAsigMat(alta);
            }
        fclose(p);    
        }
}

// MODIFICAR DATOS USUARIO

bool modificarFechAlum()
{
    tAlumno alum;
    bool modificado=false;
    char alumnom[50];
    FILE *p;
    p=fopen(ALUMNOS,"rb+");
    if(p!=NULL)
    {   
        cout <<"Ingrese el nombre del Alumno"<<endl;
        cin.getline(alumnom,50);

        while(fread(&alum,sizeof(tAlumno),1,p)==1)
        {
            if (strcmp(alumnom,alum.nombre)==0)
            {
                char nombre[50];
                cout << "Ingrese la nueva fecha de Nacimiento" << endl;
                cout << "Ingrese el dia de Nacimiento" << endl;
                cin >> alum.dia;
                cin.ignore();
                cout << "Ingrese el mes de Nacimiento" << endl;
                cin >> alum.mes;
                cin.ignore();
                cout << "Ingrese el año de Nacimiento" << endl;
                cin >> alum.anio;
                cin.ignore();

                fseek(p,ftell(p)-sizeof alum,0);
                fwrite(&alum, sizeof alum,1,p);
                fclose(p);
                modificado=true;
            }
        }
        fclose(p);
        return modificado;
    }
}

bool modificarNomAlum()
{
    tAlumno alum;

    char alumnom[50];

    FILE *p;
    p=fopen(ALUMNOS,"rb+");
    if(p!=NULL)
    {   
        cout <<"Ingrese el nombre del Alumno"<<endl;
        cin.getline(alumnom,50);
        bool modificado=false;
        while(fread(&alum,sizeof(tAlumno),1,p)==1)
        {
            if (strcmp(alumnom,alum.nombre)==0)
            {
                cout << "Ingrese el nuevo Nombre" << endl;
                cin.getline(alum.nombre,50);
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

void modificarAlumno()
{
        int op;
        bool salir=false;

        while (!salir)
        {
        cout << "Que desea modificar del Alumno" << endl;
        cout << "1.- Nombre" << endl;
        cout << "2.- Fecha de Nacimiento" << endl;
        cout << "0.- Salir" << endl;
        cout << "Ingrese una opcion" << endl;
        cin >> op;
        cin.ignore();
        switch (op)
        {
        case 1:
            {
                if (modificarNomAlum())
                {
                    cout << "El nombre del usuario se modifico correctamente" << endl;
                }
                else
                {
                    cout << "El nombre no se pudo modificar" << endl;
                }
            }
            break;
        case 2:
            {
                if (modificarFechAlum())
                {
                    cout << "Se pudo modificar la fecha de nacimiento del Alumno" <<endl;
                }   
                else
                {
                    cout << "No se pudo modificar la fecha de nacimiento del Alumno" <<endl;
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
}

// DAR DE BAJA UN ALUMNO //
void mostrarAsigM(tAsignacion alta)
{
    if (alta.eliminado==false)
    {
        cout << "||"<<"----ID-MATERIA----"<<"||"<<"----ID-LEGAJO---"<<"||"<<endl;
        cout << "||" << alta.id_materia << "||" << alta.legajo << endl; 
    }
}


void leerAlumAsig(char alumno[50])
{
    tAsignacion alta;

    int legajo=buscarLegajo(alumno);

    FILE *p;
    p=fopen(ALUMAT,"rb");
    if (p!=NULL)
    {
        while(fread(&alta,sizeof(tAsignacion),1,p))
        {
            if(legajo==alta.legajo)
            {
                mostrarAsigM(alta);
            }
        }
        fclose(p);
    }
}

bool bajaLogicaAsigMat(int materia,int legajo)
{
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

void darBajaAlumMat()
{
    char alumno[50];
    int materia;

    cout << "Ingrese el Nombre del Alumno"<<endl;
    cin.getline(alumno,50);
    cin.ignore();
    if (buscarAlumno(alumno))
    {
        cout<<"Las materias asignadas de este Alumno son "<<endl; 
        leerAlumAsig(alumno);
        cout << "Indique el ID de la materia que se dara de baja del Alumno" <<endl;
        cin>>materia;
        int legajo=buscarLegajo(alumno);
        if(bajaLogicaAsigMat(materia, legajo))
        {
            cout << "La baja se realizo correctamente" <<endl;
        }
        else
        {
            cout << "La baja no se pudor realizar correctamente" <<endl;
        }

    }
    else
    {
        cout << "El alumno no existe"<< endl;
    }
}

// MENUs

void bienvenida()
{
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "|                                                     |" << endl;
    cout << "| BIENVENIDOS AL SISTEMA DE ALTA DE ALUMNOS Y MATERIA |" << endl;
    cout << "| --------------------------------------------------- |" << endl;
    cout << "|                                                     |" << endl;
    cout << "||||||||||||| UTN FACULTAD REGIONAL DE PACHECO ||||||||" << endl;
    cout << "||||||||||||| -------------------------------- ||||||||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cin.ignore();
    system("clear");
}

void subMenuMaterias()
{
    bool salir=false;
    int op;

    while (!salir)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|                                                     |" << endl;
        cout << "| 1.- ALTA DE MATERIA                                 |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "| 2.- LISTAR MATERIAS DADAS DE ALTA                   |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "| 0.- SALIR                                           |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "|                                                     |" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cin>>op;
        cin.ignore();
        system("clear");

        switch (op)
        {
        case 1:
            {
                tMateria mat; 
                mat.id_materia=obtenerIDM();
                altaMateria(&mat);
                if(guardarMateria(mat))
                    {
                        cout <<"La materia se guardo correctamente" << endl;
                    }
                else
                    {

                        cout <<"La mataria no se pudo guardar" << endl;
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
                cout << "OPCION NO VALIDA!!!. POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
                cout << "En caso de necesitar ayuda para elegir la opcion correcta por favor validar 9.- AYUDA" << endl;
            }
            break;
        }    
    }    
}

void subMenuAlumnos()
{
    bool salir=false;
    int op;

    while (!salir)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|                                                     |" << endl;
        cout << "| 1.- ALTA DE ALUMNO                                  |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "| 2.- LISTAR ALUMNOS DADOS DE ALTA                    |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "| 0.- SALIR                                           |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "|                                                     |" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cin>>op;
        cin.ignore();
        system("clear");

        switch (op)
        {
        case 1:
            {
                tAlumno alum;
                alum.legajo=obtenerIDA();
                altaAlumno(&alum);
                if(guardarAlumno(alum))
                {
                    cout << " Se cargo el alumno correctamente ";
                }
                else
                {
                    cout << " El alumno no pudo ser cargado";
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
                cout << "OPCION NO VALIDA!!!. POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
                cout << "En caso de necesitar ayuda para elegir la opcion correcta por favor validar 9.- AYUDA" << endl;
            }
            break;

        }    
    }      
}

void subMenuModificaicones()
{
    bool salir=false;
    int op;

    while (!salir)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|                                                     |" << endl;
        cout << "| 1.- MODIFICAR DATOS DE UN ALUMNO                    |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "| 2.- ELIMINAR ASIGNACION DE ALUMNO A UNA MATERIA     |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "| 0.- SALIR                                           |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "|                                                     |" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cin>>op;
        cin.ignore();
        system("clear");

        switch (op)
        {
        case 1:
            {
                modificarAlumno();
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
                cout << "OPCION NO VALIDA!!!. POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
                cout << "En caso de necesitar ayuda para elegir la opcion correcta por favor validar 9.- AYUDA" << endl;
            }
            break;
        }      
    }
}

void subMenuAsignacion()
{
    bool salir=false;
    int op;

    while (!salir)
    {
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|                                                     |" << endl;
        cout << "| 1.- ASIGNACION DE ALUMNO A MATERIA                  |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "| 2.- LISTAR ASIGNACION DE ALUMNO A MATERIAS          |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "| 0.- SALIR                                           |" << endl;
        cout << "| --------------------------------------------------- |" << endl;
        cout << "|                                                     |" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
        cin>>op;
        cin.ignore();
        system("clear");

        switch (op)
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
            }
            break;

        case 0:
            {
                salir=true;
            }
            break;

        default:
            {
                cout << "OPCION NO VALIDA!!!. POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
                cout << "En caso de necesitar ayuda para elegir la opcion correcta por favor validar 9.- AYUDA" << endl;
            }
            break;
        }
    }  
}

void menu()
{
    bool salir = false;

    int op;

    while (!salir)
    {
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "|                                                     |" << endl;
    cout << "| 1.- MATERIAS                                        |" << endl;
    cout << "| --------------------------------------------------- |" << endl;
    cout << "| 2.- ALUMNOS                                         |" << endl;
    cout << "| --------------------------------------------------- |" << endl;
    cout << "| 3.- ASIGNACION DE ALUMNO A MATERIA                  |" << endl;
    cout << "| --------------------------------------------------- |" << endl;
    cout << "| 4.- MODIFICACION DE CAMPOS                          |" << endl;
    cout << "| --------------------------------------------------- |" << endl;
    cout << "| 0.- SALIR                                           |" << endl;
    cout << "|                                                     |" << endl;    
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cin>>op;
    cin.ignore();
    system("clear");
    
    switch (op)
    {
    case 1:
        {
            subMenuMaterias();
            cin.get();
            cin.ignore();
        }
        break;
    
    case 2:
        {
            subMenuAlumnos();
            cin.ignore();
        }
        break;

        case 3:
            {
                subMenuAsignacion();
                cin.ignore();
            }
            break;

        case 4:
            {
                subMenuModificaicones();
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
                cout << "OPCION NO VALIDA!!!. POR FAVOR INGRESE LA OPCION CORRECTA." << endl;
                cout << "En caso de necesitar ayuda para elegir la opcion correcta por favor validar 9.- AYUDA" << endl;
            }
            break;
        }
    }
}
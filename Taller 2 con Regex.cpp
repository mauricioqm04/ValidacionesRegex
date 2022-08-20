#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <regex>
using namespace std;

struct Nodo{
	string cedula;
	string nombre;
	string apellido;
	string correo;
	double nota;
	Nodo *anterior=NULL;
	Nodo *siguiente=NULL;
};

void menu();
void llenarLista(Nodo *&, Nodo*&);
void modificarLista(Nodo *);
void eliminarLista(Nodo*&, Nodo *&);
bool buscar(Nodo *, string);
void mostrarTodos(Nodo *);
void vaciar(Nodo *&);
bool buscardato(Nodo *, string);
bool listaVacia(Nodo *);
void print(Nodo *);

//menu de informes con funciones
void informes();
void alumnosAprobados();
void alumnosDesaprobados();
void promedioGrupo();
void alumnosMasMenosPromedio();
void mejorAlumno();
void peorAlumno();

//funciones para validar regex
bool validarCedula(string);
bool validarNombre(string);
bool validarApellido(string);
bool validarCorreo(string);
bool validarNota(string);

Nodo *primero = NULL;
Nodo *ultimo =NULL;
int cantAlumnos = 0;
double contador = 0;

int main(){
	menu();
	return 0;
}

void menu(){
	int opcion;
	string identificacion;
		do{
		cout<<"---------MENU---------";
		cout<<"\n1. Insertar alumno.";
		cout<<"\n2. Modificar alumno. ";
		cout<<"\n3. Eliminar alumno. ";
		cout<<"\n4. Buscar alumno. ";
		cout<<"\n5. Lista de alumnos. ";
		cout<<"\n6. Informe de alumnos. ";
		cout<<"\n7. Salir.";
		cout<<"\nOpcion: ";
		cin>>opcion;	
	
		switch(opcion){
			case 1: llenarLista(primero, ultimo);								
					system("pause");
					break;
			case 2: modificarLista(primero);
					system("pause");
					break;
			case 3: eliminarLista(primero, ultimo);
					system("pause");
					break;
			case 4: cout<<"Ingrese identificacion del alumno para realizar la busqueda: ";
					cin>>identificacion;
					if(buscar(primero, identificacion)==false){
						cout<<"\nAlumno con idenfificacion "<<identificacion<<" No existe. "<<endl;
					}
					system("pause");
					break;
					
			case 5: if(listaVacia(primero)){
						cout<<"La lista se encuentra vacia. "<<endl;				
					}else{
						mostrarTodos(primero);
					}
					system("pause");
					break;
			case 6: if(listaVacia(primero)){
						cout<<"La lista se encuentra vacia. "<<endl;				
					}else{
						informes();
					}
					system("pause");
					break; 		
					
			case 7: vaciar(primero);
					break;			
			default: cout<<"\nOpcion no valida. ";	
					system("pause");
					break;	
		}
		system("cls");
	}while(opcion!=7);
}

//funcion para ingresar nuevos nodos a la lista
void llenarLista(Nodo *&primero, Nodo *&ultimo){
	Nodo *nuevo_nodo = new Nodo(); // se construye el nodo
	string nombre, apellido, correo, identificacion, nota1;
	double nota=0;
	cout<<"Ingrese identificacion del alumno en formato ###.###.###.###: ";
	cin>>identificacion;
	nuevo_nodo->cedula=identificacion;
	if (buscardato(primero, nuevo_nodo->cedula)||!validarCedula(identificacion)){	
		while(buscardato(primero, nuevo_nodo->cedula)||!validarCedula(identificacion)){
			cout<<"\nIdentificacion ya existe o no esta en formato ###.###.###.###: ";
			cin>>identificacion;
			nuevo_nodo->cedula=identificacion;
		}
	}
	cout<<"\nIngrese el Nombre del alumno con iniciales Mayusculas: ";
	cin.ignore();
	getline(cin, nombre);
	if (!validarNombre(nombre)){	
		while(!validarNombre(nombre)){
			cout<<"\nIngrese el Nombre del alumno con iniciales Mayusculas: ";
			getline(cin, nombre);
		}
	} 	//solo se debe poner en el primero, no en el segundo getline
	nuevo_nodo->nombre=nombre;
	cout<<"\nIngrese primer y segundo apellido del alumno: ";
	getline(cin, apellido);
	if (!validarApellido(apellido)){	
		while(!validarApellido(apellido)){
			cout<<"\nIngrese primer y segundo apellido con iniciales mayusculas: ";
			getline(cin, apellido);
		}
	}
	nuevo_nodo->apellido=apellido;
	cout<<"\nIngrese el correo del alumno: ";
	cin>>correo;
	if (buscardato(primero, correo)||!validarCorreo(correo)){	
		while(buscardato(primero, correo)||!validarCorreo(correo)){
			cout<<"\nFormato no valido, o correo ya existe. Ingrese nuevamente: ";
			cin>>correo;
		}
	}
	nuevo_nodo->correo=correo;
	cout<<"\nIngrese nota del alumno con decimales de 0.0 a 5.0: ";
	cin>>nota1;
	if (!validarNota(nota1)){	
		while(!validarNota(nota1)){
			cout<<"\nFormato no valido, recuerde usar decimales: 0.0 a 5.0: : ";
			cin>>nota1;
		}
	}
	nota=stod(nota1);
	nuevo_nodo->nota=nota;	
	cantAlumnos ++;
	contador=contador+nuevo_nodo->nota;	
	if(primero==NULL){
		primero = nuevo_nodo;
		primero->siguiente = NULL;
		primero->anterior = NULL;
		ultimo = primero;
	}else{
		ultimo->siguiente = nuevo_nodo;
		nuevo_nodo->siguiente = NULL;
		nuevo_nodo->anterior = ultimo;
		ultimo = nuevo_nodo;
	}
}

//funcion para imprimir toda la lista
void mostrarTodos(Nodo *primero){
	Nodo *actual=primero;
	cout<<"\n------Planilla de alumnos------"<<endl;
	while(actual!=NULL){		
		print(actual);
		actual=actual->siguiente;
	}
	cout<<"\nCantidad de alumnos: "<<cantAlumnos<<endl;	
}

//funcion para modificar un nodo, No se puedra modificar la identificacion 
void modificarLista(Nodo *primero){
	Nodo *actual=primero;
	int opci;
	char sino;
	string identificacion, nombre, apellido, correo, nota1;
	double nota;
	bool encontrado=false;
	
	cout<<"Ingrese identificacion del estudiante que desea modificar: ";
	cin>>identificacion;
	
	while(actual!=NULL){
		if(actual->cedula==identificacion){
			encontrado=true;
			print(actual);
			do{
				cout<<"\nQue datos desea modificar? ";
				cout<<"\n1. Nombres. ";			
				cout<<"\n2. Apellidos. ";
				cout<<"\n3. Correo. ";
				cout<<"\n4. Nota. ";
				cout<<"\n5. Cancelar. ";
				cout<<"\nOpcion: ";
				cin>>opci;
			
				switch(opci){
					case 1: cout<<"Ingrese el nombre de la persona: ";
							cin.ignore();
							getline(cin, nombre);
							if (!validarNombre(nombre)){	
								while(!validarNombre(nombre)){
									cout<<"\nIngrese el Nombre del alumno con iniciales Mayusculas: ";
									getline(cin, nombre);
								}
							}
							actual->nombre=nombre;
							cout<<"\nDesea cambiar otro campo? (s/n): ";
							cin>>sino;
							break;
								
					case 2: cout<<"Ingrese el apellido del alumno: ";
							cin.ignore();	
							getline(cin, apellido);
							if (!validarApellido(apellido)){	
								while(!validarApellido(apellido)){
									cout<<"\nIngrese primer y segundo apellido con iniciales mayusculas: ";
									getline(cin, apellido);
								}
							}
							actual->apellido=apellido;
							cout<<"\nDesea cambiar otro campo? (s/n): ";
							cin>>sino;
							break;
						
					case 3: cout<<"ingrese correo del alumno: ";
							cin>>correo;
							if (buscardato(primero, correo)||!validarCorreo(correo)){	
								while(buscardato(primero, correo)||!validarCorreo(correo)){
									cout<<"\nFormato no valido, o correo ya existe. Ingrese nuevamente: ";
									cin>>correo;
								}
							}
							actual->correo=correo;
							cout<<"\nDesea cambiar otro campo? (s/n): ";
							cin>>sino;
							break;
							
					case 4: cout<<"ingrese la nueva nota: ";
							cin>>nota1;
							
							if (!validarNota(nota1)){	
								while(!validarNota(nota1)){
									cout<<"\nFormato no valido, recuerde usar decimales: 0.0 a 5.0: : ";
									cin>>nota1;
								}
							}
							nota=stod(nota1);
							contador=contador-actual->nota;
							actual->nota=nota;
							contador=contador+actual->nota;
							cout<<"\nDesea cambiar otro campo? (s/n): ";
							cin>>sino;
							break;		
							
					case 5: sino='n';
							break;
						
					default: cout<<"\nOpcion no valida. "<<endl;
							 system("pause");
							break;				
				}			
			}while((sino=='s')||(sino=='S'));			
		}
		actual=actual->siguiente;
	}
	if(encontrado==false){
		cout<<"\nEl alumno con el numero de cedula "<<identificacion<<" no existe, por favor verifique. "<<endl;
	}
}

//funcion para eliminar un alumno en estepcifico
void eliminarLista(Nodo *&primero, Nodo *&ultimo){
	Nodo *actual = new Nodo();
	actual = primero;
	Nodo *atras = new Nodo();
	atras = NULL;
	bool encontrado = false;
	string identificacion;
	cout << " Ingrese la identificacion del alumno que desea eliminar: ";
	cin >> identificacion;
	if(primero!=NULL){
		
		while(actual!=NULL && encontrado!=true){			
			if(actual->cedula == identificacion){
				
				if(actual==primero){
					contador=contador-actual->nota;
					primero = primero->siguiente;
					primero->anterior = NULL;
				}else if(actual==ultimo){
					contador=contador-actual->nota;
					atras ->siguiente = NULL;
					ultimo = atras;
				}else{
					contador=contador-actual->nota;
					atras->siguiente = actual->siguiente;
					actual->siguiente->anterior = atras;
				}
				cantAlumnos--;
				cout << "\n Alumno eliminado exitosamente!!!"<<endl;
				encontrado = true;
			}
			atras = actual;
			actual = actual->siguiente;
		}
		
		if(!encontrado){
			cout << "\n Identificacion "<<identificacion<<" no existe. \n\n";
		}
		
	}else{
		cout << "\n La listas se encuentra Vacia\n\n";
	}
}


//funcion para buscar si una identificacion ya fue ingresada
bool buscardato(Nodo *primero, string dato){
	Nodo *actual = new Nodo();
	actual=primero;
	bool encontrado = false;
	
	while(actual != NULL){
		if(dato==actual->cedula){
			encontrado=true;
		}
		actual=actual->siguiente;
	}	
	return(encontrado==true)? true:false;	
}

//funcion para buscar e imprimir un alumno en especifico
bool buscar(Nodo *primero, string identificacion){
	Nodo *actual=primero;
	bool encontrado=false;
	while(actual!=NULL){
		if(actual->cedula==identificacion){
			encontrado=true;
			print(actual);
		}
		actual=actual->siguiente;
	}
	return(encontrado)? true:false;
}

//se crea esta funcion que imprime el nodo actual que se este solicitando en cada funcion
void print(Nodo *actual){
	cout<<"Nombre		   : "<<actual->nombre<<endl;
	cout<<"Apellido	   : "<<actual->apellido<<endl;
	cout<<"Identificacion	   : "<<actual->cedula<<endl;
	cout<<"Correo		   : "<<actual->correo<<endl;
	cout<<"Nota		   : "<<actual->nota<<endl;
	cout<<"--------------------------------------"<<endl;
}

//funcion para vaciar una lista completamente
void vaciar(Nodo *&primero){	
	while(primero!=NULL){
		Nodo *aux=primero;
		primero=aux->siguiente;
		delete aux;
	}	
}

//funcion para verificar si la lista esta vacia 
bool listaVacia(Nodo *primero){
	return(primero==NULL)? true:false;
}

bool validarCedula(string ced){
	//regex para validar que sea desde el año 2000
	const regex expReg("(\\d{2}.\\d{3}.\\d{3})|(\\d.\\d{3}.\\d{3}.\\d{3})");
	return regex_match(ced, expReg);
}

bool validarNombre(string nom){
	//regex para validar que sea desde el año 2000
	const regex expReg("([A-Z]{1}[a-z]{2,15}[ ][A-Z]{1}[a-z]{2,15})|([A-Z]{1}[a-z]{2,12})");
	return regex_match(nom, expReg);
}

bool validarApellido(string apelli){
	//regex para validar que sea desde el año 2000
	const regex expReg("[A-Z]{1}[a-z]{2,15}[ ][A-Z]{1}[a-z]{2,15}");
	return regex_match(apelli, expReg);
}

bool validarCorreo(string mail){
	//regex para validar que sea desde el año 2000
	const regex expReg("[a-z0-9.-_]+@[a-z0-9-_]+.[a-z]{3}(.[a-z]{2})?");
	return regex_match(mail, expReg);
}

bool validarNota(string calif){
	//regex para validar que sea desde el año 2000
	const regex expReg("([0-4]{1}.[0-9]+)|([0-5]{1}.[0])");
	return regex_match(calif, expReg);
}

//menu para hacer los informes solicitados
void informes(){
	int opcion;
	double promedio=0;	
	do{
		cout<<"\n---------INFORMES ESTUDIANTES---------"<<endl;
		cout<<"1. Alumnos aprobados. "<<endl;
		cout<<"2. Alumnos desaprobados. "<<endl;
		cout<<"3. Promedio del gupo. "<<endl;
		cout<<"4. Alumnos por encima y por debajo del promedio. "<<endl;
		cout<<"5. Mejor alumno. "<<endl;
		cout<<"6. Peor alumno. "<<endl;
		cout<<"7. Salir. "<<endl;
		cout<<"1. Opcion: ";
		cin>>opcion;
		
		switch(opcion){
			case 1: alumnosAprobados();
					system("pause");
					break;
			case 2: alumnosDesaprobados();
					system("pause");
					break;
			
			case 3: promedio=contador/cantAlumnos;
					cout<<"El promedio del grupo es: "<<promedio<<" "<<endl;
					system("pause");
					break;
			
			case 4: alumnosMasMenosPromedio();
					system("pause");
					break;
			
			case 5: mejorAlumno();
					system("pause");
					break;
			
			case 6: peorAlumno();
					system("pause");
					break;
			
			case 7: break;				
			
			default: cout<<"\nOpcion no valida.\nElija una opcion del 1 al 6, o 7 para volver al menu anterior."<<endl;
					system("pause");
					break;			
		}
		system("cls");
	}while(opcion!=7);
}

//informe para ver los alumnos aprobados 3 hasta 5
void alumnosAprobados(){
	Nodo *actual=primero;	
	while(actual!=NULL){
		if(actual->nota>=3){
			print(actual);
		}
		actual=actual->siguiente;
	}
}

//informe para ver los alumnos aprobados 3 hasta 5
void alumnosDesaprobados(){
	Nodo *actual=primero;	
	while(actual!=NULL){
		if(actual->nota<3){
			print(actual);
		}
		actual=actual->siguiente;
	}
}

//funcionque muestra los alimnos por encima del promedio y por debajo
void alumnosMasMenosPromedio(){
	Nodo *actual=primero;	
	double promedio=0;
	promedio=contador/cantAlumnos;
	cout<<"\nAlumnos por encima del promedio."<<endl;
	while(actual!=NULL){
		if(actual->nota>=promedio){
			print(actual);
		}
		actual=actual->siguiente;
	}
	actual=primero;
	cout<<"\nAlumnos por debajo del promedio."<<endl;
	while(actual!=NULL){
		if(actual->nota<promedio){
			print(actual);
		}
		actual=actual->siguiente;
	}
}

//funcion para buscar el mejor alumno
void mejorAlumno(){
	Nodo *actual=primero;
	Nodo *aux=primero;
	double mejor=0;	
	mejor=primero->nota;
	while(actual!=NULL){
		if(actual->nota>mejor){
			mejor=actual->nota;
			aux=actual;
		}
		actual=actual->siguiente;
	}
	cout<<"\nEl mejor alumno es: "<<endl;
	print(aux);
}

//funcion que muestra el peor alumno
void peorAlumno(){
	Nodo *actual=primero;
	Nodo *aux=primero;
	double peor=0;	
	peor=primero->nota;
	while(actual!=NULL){
		if(actual->nota<peor){
			peor=actual->nota;
			aux=actual;
		}
		actual=actual->siguiente;
	}
	cout<<"\nEl peor alumno es: "<<endl;
	print(aux);	
}
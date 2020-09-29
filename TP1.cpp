#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NOMBRE 16
#define MAX_NOMBRE 100
#define EMAIL 16
#define MAX_EMAIL 100
#define MIN_CONTRASENA 8
#define CONTRASENA 100

using namespace std;

struct Usuario {
    char nombre[NOMBRE]; 
    char email[EMAIL];
    char contrasenia[CONTRASENA];  
};

FILE *abrir(const char *nombreArchivo, const char *modo);
void cerrar(FILE *archivo);
void leerTxt(Usuario *registro, FILE *archivo);
bool validarNombre(char *cadena);
bool validarEmail(char *cadena);
bool validarContrasenia(char *cadena);

int main () {
    FILE *usersTxt = abrir("users.txt", "r");
    FILE *usersValidados = abrir("users.dat", "wb");
    FILE *usersNoValidos = abrir("rejected.txt", "w");

    Usuario usuario; // Estructura de registros para usersTxt.
    //leerTxt(&usuario, usersTxt);

    while (!feof(usersTxt)) 
    {
        leerTxt(&usuario, usersTxt);
      
        if (validarNombre(usuario.nombre) && validarEmail(usuario.email) && validarContrasenia(usuario.contrasenia)) 
        {
            fwrite(&usuario, sizeof(Usuario), 1, usersValidados);
        } 
        else {
            fprintf(usersNoValidos, "%s;%s;%s\n", usuario.nombre, usuario.email, usuario.contrasenia);
        }
    }
    
    cerrar(usersTxt);
    cerrar(usersValidados);
    cerrar(usersNoValidos);

    system("pause");
    return 0;
}

FILE *abrir(const char *nombreArchivo, const char *modo) {
    FILE *file = fopen(nombreArchivo, modo);
    if (file == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo: %s", nombreArchivo);
        exit(EXIT_FAILURE);
    }

    return file;
}

void cerrar(FILE *archivo) {
    fclose(archivo);
    archivo = NULL;
}

void leerTxt(Usuario *usuario, FILE *archivo) {
    char cadena[100];.
    while (fgets(cadena, 101, archivo) != NULL) { 
        strcpy(usuario->nombre, strtok(cadena, ";"));
        printf("%s\n", usuario->nombre);
        strcpy(usuario->email, strtok(NULL, ";")); 
        printf("%s\n", usuario->email);
        strcpy(usuario->contrasenia, strtok(NULL, ";"));
        printf("%s\n", usuario->contrasenia);
    }
    return;  
}

bool validarNombre(char *cadena) {  
    bool esNombre = false;
    int cantDigitos = 0;
    int i = 0;

    while(*(cadena + i) != '\0') {
        cantDigitos++;
        i++;
    }

    if (cantDigitos <= MAX_NOMBRE) {
        return true;
    } else {
        return false;
    }
}

bool validarEmail(char *cadena) {
    bool esEmail = false;
    int cantDigitos = 0;
    int i = 0;

    while (*(cadena + i) != '\0') {
        if (*(cadena + i) == '@') {
            esEmail = true;
        } 
        cantDigitos++;
        i++;
    }

    if (esEmail && cantDigitos <= MAX_EMAIL) {
        return true;
    } else {
        return false;
    }
    
}

bool validarContrasenia(char *cadena) {
    bool esNum = false;
    bool esLetra = false; 
    int cantDigitos = 0;
    int i = 0;

    while (*(cadena + i) != '\0') {
        if (*(cadena + i) >= '0' && *(cadena + i) <= '9') {
            esNum = true;
        } else if (*(cadena + i) >= 65 && *(cadena + i) <= 90 || *(cadena + i) >= 97 && *(cadena + i) <= 122) {
            esLetra = true;
        } else {
            return false;
        } 
        cantDigitos++;
        i++;
    }

    if (esNum && esLetra && cantDigitos >= MIN_CONTRASENA) {
        return true;
    } else {
        return false;
    }   
}
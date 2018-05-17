#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
typedef struct
{
    char nombre[50];
    char apellido[50];
    char cuit[11];
    int idCliente;
    int isEmpty;
}Cliente;
#endif // CLIENTE_H_INCLUDED

int cliente_init(Cliente* array,int limite);
int cliente_mostrarPorId(Cliente* array,int limite, int idCliente);
int cliente_mostrarDebug(Cliente* array,int limite);
int cliente_alta(Cliente* array,int limite);
int cliente_baja(Cliente* array,int limite, int idCliente);
int cliente_modificacion(Cliente* array,int limite, int idCliente);
int cliente_ordenar(Cliente* array,int limite, int orden);
int cliente_altaForzada(Cliente* array,int limite, char* nombre, char* apellido, char* cuit);
int cliente_buscarPorId(Cliente* array,int limite, int idCliente);

#ifndef PUBLICACION_H_INCLUDED
#define PUBLICACION_H_INCLUDED
#include "Cliente.h"
typedef struct
{
    char textoAviso[50];
    int rubro;
    int estado;
    int idPublicacion;
    int idCliente;
    int isEmpty;
}Publicacion;
#endif // PUBLICACION_H_INCLUDED


int publicacion_init(Publicacion* publicacion,int limite);
int publicacion_mostrar(Publicacion* publicacion,int limite, Cliente* array, int limCliente);
int publicacion_mostrar_porIdPublicacion(Publicacion* publicacion,int limite, Cliente* array, int limCliente, int id);
int publicacion_mostrarDebug(Publicacion* publicacion,int limite);
int publicacion_mostrarPorIdCliente(Publicacion* publicacion, int limite, int idCliente);
int publicacion_alta(Publicacion* publicacion,int limite,int id);
int publicacion_pausar(Publicacion* publicacion,int limite, int idPublicacion);
int publicacion_reanudar(Publicacion* publicacion,int limite, int idPublicacion);//
int publicacion_cliente_baja(Publicacion* publicacion,int limite,Cliente* array,int limCliente ,int id);
int publicacion_modificacion(Publicacion* publicacion,int limite, int id);
int publicacion_ordenar(Publicacion* publicacion,int limite, int orden);
int publicacion_altaForzada(Publicacion* publicacion,int limite,int idCliente, Cliente* array, int limCliente, char* textoAviso, int rubro, int estado);
int publicacion_buscarPorId(Publicacion* publicacion,int limite, int id);




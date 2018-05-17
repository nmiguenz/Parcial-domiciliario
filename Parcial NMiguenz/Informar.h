#ifndef INFORMAR_H_INCLUDED
#define INFORMAR_H_INCLUDED

int informar_cliente_imprimir(Cliente* array,int limite, Publicacion* publicaciones, int lenPublicacion);
int informar_publicaciones_imprimir(Cliente* arrayCliente,int limite, Publicacion* publicaciones, int lenPublicacion);

int informar_ClienteConMasPublicacionesActivas(Cliente* arrayCliente,int limite, Publicacion* publicaciones, int lenPublicacion);
int informar_ClienteConMasPublicacionesPausados(Cliente* arrayCliente,int limiteCliente, Publicacion* publicaciones, int lenPublicacion);
int informar_ClienteConMasPublicaciones(Cliente* arrayCliente,int lenCliente, Publicacion* publicaciones, int lenPublicacion);

int informar_cantidadPublicacionesPorRubro(Publicacion* publicacion, int lenPublicacion, int rubro);
int informar_rubroMasPublicacionesActivas(Publicacion* publicaciones,int lenPublicacion,int rubros);
int informar_rubroMenosPublicacionesActivas(Publicacion* publicaciones,int lenPublicacion,int rubros);
#endif // INFORMAR_H_INCLUDED

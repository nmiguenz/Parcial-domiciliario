#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Publicacion.h"
#include "Cliente.h"
#include "utn.h"
#include "Informar.h"
#define LEN_CLIENTE 100
#define LEN_PUB 1000

int main()
{
    Cliente cliente[LEN_CLIENTE];
    Publicacion publicacion[LEN_PUB];

    int menu;
    int auxiliarId;
    int opcion;
    int rubro;

    cliente_init(cliente,LEN_CLIENTE);
    publicacion_init(publicacion,LEN_PUB);

    cliente_altaForzada(cliente,LEN_CLIENTE,"Nico","Miguenz","20318223824");
    cliente_altaForzada(cliente,LEN_CLIENTE,"Martiun","Jrman","99318223824");
    cliente_altaForzada(cliente,LEN_CLIENTE,"Sani","Sanzaf","2718223824");
    cliente_altaForzada(cliente,LEN_CLIENTE,"Eli","Port","30318223824");

    publicacion_altaForzada(publicacion,LEN_PUB,0,cliente,LEN_CLIENTE,"Radoio grabador",1,1);
    publicacion_altaForzada(publicacion,LEN_PUB,3,cliente,LEN_CLIENTE,"Radio Despertador",2,1);
    publicacion_altaForzada(publicacion,LEN_PUB,3,cliente,LEN_CLIENTE,"Radio Despertador",2,1);

    do
    {
        getValidInt("1.Alta\n2.Modificar Cliente\n3.Baja Cliente\n4.Publicar\n5.Pausar publicacion\n6.Reanudar publicacion\n7.Imprimir Clientes\n8.Imprimir publicaciones\n9.Informar Clientes\n10.Informar Publicaciones\n11.Salir\n","\nNo valida\n\n",&menu,1,11,1);
        switch(menu)
        {
            case 1:
                cliente_alta(cliente,LEN_PUB);
                break;
            case 2:
                //cliente_mostrar(cliente,LEN_CLIENTE);
                getValidInt("ID del cliente? ","\nNumero no valido\n\n",&auxiliarId,0,2000,2);
                cliente_modificacion(cliente,LEN_CLIENTE,auxiliarId);
                break;
            case 3:
                getValidInt("ID del cliente? ","\nNumero no valido\n\n",&auxiliarId,0,2000,2);
                publicacion_mostrarPorIdCliente(publicacion,LEN_PUB,auxiliarId);
                publicacion_cliente_baja(publicacion,LEN_PUB,cliente,LEN_CLIENTE,auxiliarId);
                break;
            case 4:
                getValidInt("ID del cliente? ","\nNumero no valido\n\n",&auxiliarId,0,2000,2);
                publicacion_alta(publicacion,LEN_PUB,auxiliarId);
                break;
            case 5:
                getValidInt("Ingrese el ID de la publicacion: ","\nNumero no valido",&auxiliarId,0,2000,2);
                publicacion_mostrar_porIdPublicacion(publicacion,LEN_PUB,cliente,LEN_CLIENTE,auxiliarId);
                publicacion_pausar(publicacion,LEN_PUB,auxiliarId);
                break;
            case 6:
                getValidInt("Ingrese el ID de la publicacion: ","\nNumero no valido",&auxiliarId,0,2000,2);
                publicacion_mostrar_porIdPublicacion(publicacion,LEN_PUB,cliente,LEN_CLIENTE,auxiliarId);
                publicacion_reanudar(publicacion,LEN_PUB,auxiliarId);
                break;
            case 7:
                informar_cliente_imprimir(cliente,LEN_CLIENTE,publicacion,LEN_PUB);
                break;
            case 8:
                informar_publicaciones_imprimir(cliente,LEN_CLIENTE,publicacion,LEN_PUB);
                break;
            case 9:
                getValidInt("\nINGRESE LA OPCION DESEADA\n1.Cliente con mas avisos activos \n2.Cliente con mas avisos pausados \n3.Cliente con mas publicaciones \n","\nNo es una opcion valida\n",&opcion,1,3,2);
                if (opcion==1)
                    informar_ClienteConMasPublicacionesActivas(cliente,LEN_CLIENTE,publicacion,LEN_PUB);
                if (opcion==2)
                informar_ClienteConMasPublicacionesPausados(cliente,LEN_CLIENTE,publicacion,LEN_PUB);
                if (opcion==3)
                informar_ClienteConMasPublicaciones(cliente,LEN_CLIENTE,publicacion,LEN_PUB);
                break;
            case 10:
                getValidInt("\nINGRESE LA OPCION DESEADA\n1.Cantidad de publicaciones de un rubro \n2.Rubro con mas publicaciones activas \n3.Rubro con menos publicaciones activas \n","\nNo es una opcion valida\n",&opcion,1,3,2);
                if (opcion==1)
                {
                    getValidInt("Ingrese el numero de rubro a consultar\n","Esa no es un rubro valido\n",&rubro,1,10,2);
                    informar_cantidadPublicacionesPorRubro(publicacion,LEN_PUB,rubro);
                }
                if (opcion==2)
                    informar_rubroMasPublicacionesActivas(publicacion,LEN_PUB,10);
                if (opcion==3)
                    informar_rubroMenosPublicacionesActivas(publicacion,LEN_PUB,10);

                break;
        }

    }while(menu != 11);

    return 0;
}

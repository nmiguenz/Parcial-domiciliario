#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Publicacion.h"
#include "Cliente.h"
#include "utn.h"

/** \brief Imprime la cantidad de publicaciones que tiene cada cliente
 *
 * \param arrayCliente Cliente* puntero al array de clientes
 * \param limite int limite definido para cliente
 * \param publicaciones Publicacion* puntero a publicacion
 * \param lenPublicacion int limite definido para publicacion
 * \return int [-1] ERROR [0] OK
 *
 */
int informar_cliente_imprimir(Cliente* arrayCliente,int limite, Publicacion* publicaciones, int lenPublicacion)
{
    int retorno = -1;
    int i;
    int j;
    int idCliente;
    int contadorPublicaciones = 0;

    if(limite > 0 && arrayCliente != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            if(!arrayCliente[i].isEmpty)
            {
                idCliente = arrayCliente[i].idCliente;
                for(j=0; j<lenPublicacion;j++)
                {
                    if(!publicaciones[j].isEmpty && publicaciones[j].idCliente == idCliente)
                    {
                        contadorPublicaciones++;
                    }
                }
                printf("[RELEASE] -ID: %d -NOMBRE: %s -APELLIDO: %s -CUIT: %s -Cantidad de Publicaciones %d\n",arrayCliente[i].idCliente, arrayCliente[i].nombre, arrayCliente[i].apellido, arrayCliente[i].cuit,contadorPublicaciones);
            }
            contadorPublicaciones = 0;
        }
    }
    return retorno;
}

/** \brief Informa las publicaciones con el CUIT del cliente
 *
 * \param arrayCliente Cliente* puntero al array de cliente
 * \param limite int limite definido para cliente
 * \param publicaciones Publicacion* puntero a publicaciones
 * \param lenPublicacion int limite definido para publicacion
 * \return int [-1] ERROR [0] OK
 *
 */
int informar_publicaciones_imprimir(Cliente* arrayCliente,int limite, Publicacion* publicaciones, int lenPublicacion)
{
    int retorno = -1;
    int i;
    int j;
    int idCliente;
    char cuitCliente[11];

    if(lenPublicacion > 0 && publicaciones != NULL && limite>0 && arrayCliente !=NULL)
    {
        retorno = 0;
        for(i=0;i<lenPublicacion;i++)
        {
            if(!publicaciones[i].isEmpty && publicaciones[i].estado==1)
            {
                idCliente = publicaciones[i].idCliente;
                for(j=0; j<limite;j++)
                {
                    if(!arrayCliente[j].isEmpty && arrayCliente[j].idCliente == idCliente)
                    {
                        strcpy(cuitCliente,arrayCliente[j].cuit);
                    }
                }
                printf("ID Publicacion: %d - Aviso: %s - Estado: %d - Rubro: %d - CUIT cliente: %s\n",publicaciones[i].idPublicacion, publicaciones[i].textoAviso, publicaciones[i].estado, publicaciones[i].rubro, cuitCliente);
            }
        }
    }
    return retorno;
}

/** \brief Muestra al cliente con mas publicaciones activas
 *
 * \param arrayCliente Cliente* puntero al array de cliente
 * \param lenCliente int limite definido para cliente
 * \param publicaciones Publicacion* puntero a publicaciones
 * \param lenPublicacion int limite definido para publicaciones
 * \return int [-1] ERROR [0] OK
 *
 */
int informar_ClienteConMasPublicacionesActivas(Cliente* arrayCliente,int lenCliente, Publicacion* publicaciones, int lenPublicacion)
{
    int retorno = -1;
    int i;
    int j;
    int indiceCliente;
    int publicacionesActivas = 0;
    int maxAvisosActivos = 0;

    if(lenCliente > 0 && lenPublicacion > 0 && arrayCliente != NULL && publicaciones !=NULL)
    {
        retorno = 0;
        for(i=0;i<lenCliente;i++)
        {
            if(!arrayCliente[i].isEmpty)
            {
                publicacionesActivas= 0;
                for(j=0; j<lenPublicacion;j++)
                {
                    retorno = 0;
                    if(!publicaciones[j].isEmpty && publicaciones[j].idCliente == arrayCliente[i].idCliente && publicaciones[j].estado==1)
                    {
                        publicacionesActivas++;
                    }
                }
                if(publicacionesActivas>maxAvisosActivos)
                {
                    maxAvisosActivos = publicacionesActivas;
                    indiceCliente = i;
                }
            }

        }
        cliente_mostrarPorId(arrayCliente,lenCliente,indiceCliente);
        printf("La cantidad maxima de Publicaciones activas es %d\n",maxAvisosActivos);
    }
    return retorno;
}

/** \brief Muestra el cliente con mas publicaciones pausadas
 *
 * \param arrayCliente Cliente* puntero al array de cliente
 * \param lenCliente int limite definido para cliente
 * \param publicaciones Publicacion* puntero a publicaciones
 * \param lenPublicacion int limite definido para publicacion
 * \return int [-1] ERROR [0] OK
 *
 */
int informar_ClienteConMasPublicacionesPausados(Cliente* arrayCliente,int lenCliente, Publicacion* publicaciones, int lenPublicacion)
{
    int retorno = -1;
    int i;
    int j;
    int indiceCliente;
    int publicacionesPausadas = 0;
    int maxAvisosPausados = 0;

    if(lenCliente > 0 && lenPublicacion > 0 && arrayCliente != NULL && publicaciones !=NULL)
    {
        retorno = 0;
        for(i=0;i<lenCliente;i++)
        {
            if(!arrayCliente[i].isEmpty)
            {
                publicacionesPausadas= 0;
                for(j=0; j<lenPublicacion;j++)
                {
                    retorno = 0;
                    if(!publicaciones[j].isEmpty && publicaciones[j].idCliente == arrayCliente[i].idCliente && publicaciones[j].estado==0)
                    {
                        publicacionesPausadas++;
                    }
                }
                if(publicacionesPausadas>maxAvisosPausados)
                {
                    maxAvisosPausados = publicacionesPausadas;
                    indiceCliente = i;
                }
            }

        }
        if (maxAvisosPausados>0)
        {
            cliente_mostrarPorId(arrayCliente,lenCliente,indiceCliente);
            printf("La cantidad maxima de Publicaciones pausadas es %d\n",maxAvisosPausados);
        }
    }
    return retorno;
}

/** \brief Informa al cliente con mas publicaciones
 *
 * \param arrayCliente Cliente* puntero al array de cliente
 * \param lenCliente int limite definido para cliente
 * \param publicaciones Publicacion* puntero a publicaciones
 * \param lenPublicacion int limite definido para publicaciones
 * \return int [-1] ERROR [0] OK
 *
 */
int informar_ClienteConMasPublicaciones(Cliente* arrayCliente,int lenCliente, Publicacion* publicaciones, int lenPublicacion)
{
    int retorno = -1;
    int i;
    int j;
    int indiceCliente;
    int contadorPublicaciones = 0;
    int maxAvisos = 0;

    if(lenCliente > 0 && lenPublicacion > 0 && arrayCliente != NULL && publicaciones !=NULL)
    {
        retorno = 0;
        for(i=0;i<lenCliente;i++)
        {
            if(!arrayCliente[i].isEmpty)
            {
                contadorPublicaciones= 0;
                for(j=0; j<lenPublicacion;j++)
                {
                    retorno = 0;
                    if(!publicaciones[j].isEmpty && publicaciones[j].idCliente == arrayCliente[i].idCliente)
                    {
                        contadorPublicaciones++;
                    }
                }
                if(contadorPublicaciones>maxAvisos)
                {
                    maxAvisos = contadorPublicaciones;
                    indiceCliente = i;
                }
            }

        }
        cliente_mostrarPorId(arrayCliente,lenCliente,indiceCliente);
        printf("La cantidad de avisos es %d\n",maxAvisos);
    }
    return retorno;
}

/** \brief Muestra la cantidad de publicaciones por rubro
 *
 * \param publicacion Publicacion* puntero a publicaciones
 * \param lenPublicacion int limite definido para publicaciones
 * \param rubro int entero correspondiente a la cantidad total de rubros admitidos
 * \return int [-1] ERROR [0] OK
 *
 */
int informar_cantidadPublicacionesPorRubro(Publicacion* publicacion, int lenPublicacion, int rubro)
{
    int retorno=-1;
    int contadorPublicaciones=0;
    int i;

    if(lenPublicacion>0 && publicacion != NULL)
    {
        retorno=0;
        for(i=0;i<lenPublicacion;i++)
        {
            if(!publicacion[i].isEmpty && publicacion[i].estado && publicacion[i].rubro==rubro)
                contadorPublicaciones++;
        }
        printf("\nEl rubro N\147 %d tiene %d publicaciones activas \n",rubro,contadorPublicaciones);
    }
    return retorno;
}

/** \brief Muestra al rubro con mas publicaciones activas
 *
 * \param publicaciones Publicacion* puntero a publicaciones
 * \param lenPublicacion int limite definido para publicaciones
 * \param rubros int entero correspondiente a la cantidad total de rubros admitidos
 * \return int [-1] ERROR [0] OK
 *
 */
int informar_rubroMasPublicacionesActivas(Publicacion* publicaciones,int lenPublicacion,int rubros)
{
    int retorno=-1;
    int i;
    int j;
    int contadorPublicaciones=0;
    int indiceRubro;
    int maximoPublicaciones = 0;

    if(lenPublicacion>0 && publicaciones != NULL)
    {
        retorno=0;
        for(i=1;i<=rubros;i++)
        {
            contadorPublicaciones=0;

            for(j=0;j<lenPublicacion;j++)
            {
                if(!publicaciones[j].isEmpty && publicaciones[j].estado && publicaciones[j].rubro==i)
                    contadorPublicaciones++;
            }

            if(contadorPublicaciones>maximoPublicaciones)
            {
                maximoPublicaciones=contadorPublicaciones;
                indiceRubro=i;
            }
        }
        printf("\nLa cantidad maxima de publicaciones es %d y corresponde al rubro %d\n",maximoPublicaciones,indiceRubro);
    }
    return retorno;
}

/** \brief Muestra el rubro con menos publicaciones activas
 *
 * \param publicaciones Publicacion* puntero a publicaciones
 * \param lenPublicacion int limite definido para publicaciones
 * \param rubros int entero correspondiente a la cantidad total de rubros admitidos
 * \return int [-1] ERROR [0] OK
 *
 */
int informar_rubroMenosPublicacionesActivas(Publicacion* publicaciones,int lenPublicacion,int rubros)
{
    int retorno=-1;
    int i;
    int j;
    int contadorPublicaciones=0;
    int indiceRubro;
    int minimoPublicaciones=1000;

    if(lenPublicacion>0 && publicaciones != NULL)
    {
        retorno=0;
        for(i=1;i<=rubros;i++)
        {
            contadorPublicaciones=0;

            for(j=0;j<lenPublicacion;j++)
            {
                if(!publicaciones[j].isEmpty && publicaciones[j].estado && publicaciones[j].rubro==i)
                    contadorPublicaciones++;
            }

            if(contadorPublicaciones<minimoPublicaciones)
            {
                minimoPublicaciones=contadorPublicaciones;
                indiceRubro=i;
            }
        }
        printf("\nLa cantidad minima de publicaciones es %d y corresponde al rubro %d\n",minimoPublicaciones,indiceRubro);
    }
    return retorno;
}

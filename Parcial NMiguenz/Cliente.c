#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Cliente.h"
#include "utn.h"

static int proximoId();
static int buscarLugarLibre(Cliente* array,int limite);


/** \brief
 * \param array Cliente*
 * \param limite int
 * \return int
 *
 */
int cliente_init(Cliente* array,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            array[i].isEmpty=1;
        }
    }
    return retorno;
}

int cliente_mostrarDebug(Cliente* array,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            printf("[DEBUG] - %d - %s - %d\n",array[i].idCliente, array[i].nombre, array[i].isEmpty);
        }
    }
    return retorno;
}

int cliente_mostrarPorId(Cliente* array,int limite, int idCliente)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].idCliente==idCliente)
                printf("[RELEASE] -ID: %d -NOMBRE: %s -APELLIDO: %s -CUIT: %s\n",array[i].idCliente, array[i].nombre, array[i].apellido, array[i].cuit);
        }
    }
    return retorno;
}

int cliente_alta(Cliente* array,int limite)
{
    int retorno = -1;
    int i;
    char auxNombre[50];
    char auxApellido[50];
    char auxCuit[12];

    if(limite > 0 && array != NULL)
    {
        i = buscarLugarLibre(array,limite);
        if(i >= 0)
        {
            if(!getValidString("\nNombre? ","\nEso no es un nombre","El maximo es 40",auxNombre,50,2))
            {
                if(!getValidString("\nApellido? ","\nEso no es un apellido","El maximo es de 50",auxApellido,50,2))
                {
                    if(!getValidStringNumerico("\nCUIT? ","\nEl CUIT debe tener solo numeros","El maximo es de 11",auxCuit,12,2))
                    {
                        retorno = 0;
                        strcpy(array[i].nombre,auxNombre);
                        strcpy(array[i].apellido,auxApellido);
                        strcpy(array[i].cuit,auxCuit);
                        array[i].idCliente = proximoId();
                        array[i].isEmpty = 0;
                        printf("El ID del Cliente es: %d",array[i].idCliente);
                    }
                }
            }
            else
            {
                retorno = -3;
            }
        }
        else
        {
            retorno = -2;
        }

    }
    return retorno;
}


int cliente_baja(Cliente* array,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].idCliente==id)
            {
                array[i].isEmpty = 1;
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

int cliente_modificacion(Cliente* array,int limite, int id)
{
    int retorno = -1;
    int i;
    char auxNombre[50];
    char auxApellido[50];
    char auxCuit[12];
    if(limite > 0 && array != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].idCliente==id)
            {
                if(!getValidString("\nNombre? ","\nEso no es un nombre","El maximo es 50",auxNombre,50,2))
                {
                    if(!getValidString("\nApellido? ","\nEso no es un apellido","El maximo es de 50",auxApellido,50,2))
                    {
                        if(!getValidStringNumerico("\nCUIT? ","\nEl CUIT debe tener solo numeros","El maximo es de 11",auxCuit,12,2))
                        {
                            retorno = 0;
                            strcpy(array[i].nombre,auxNombre);
                            strcpy(array[i].apellido,auxApellido);
                            strcpy(array[i].cuit,auxCuit);
                            array[i].idCliente = proximoId();
                            array[i].isEmpty = 0;
                        }
                    }
                }
                else
                {
                    retorno = -3;
                }
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

int cliente_ordenar(Cliente* array,int limite, int orden)
{
    int retorno = -1;
    int i;
    int flagSwap;
    Cliente auxiliarEstructura;

    if(limite > 0 && array != NULL)
    {
        do
        {
            flagSwap = 0;
            for(i=0;i<limite-1;i++)
            {
                if(!array[i].isEmpty && !array[i+1].isEmpty)
                {
                    if((strcmp(array[i].nombre,array[i+1].nombre) > 0 && orden) || (strcmp(array[i].nombre,array[i+1].nombre) < 0 && !orden)) //******
                    {
                        auxiliarEstructura = array[i];
                        array[i] = array[i+1];
                        array[i+1] = auxiliarEstructura;
                        flagSwap = 1;
                    }
                }
            }
        }while(flagSwap);
    }
    return retorno;
}

static int buscarLugarLibre(Cliente* array,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        for(i=0;i<limite;i++)
        {
            if(array[i].isEmpty==1)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}


static int proximoId()
{
    static int proximoId = -1;
    proximoId++;
    return proximoId;
}

int cliente_altaForzada(Cliente* array,int limite, char* nombre, char* apellido, char* cuit)
{

    int retorno = -1;
    int i;

    if(limite > 0 && array != NULL)
    {
        i = buscarLugarLibre(array,limite);
        if(i >= 0)
        {
            retorno = 0;
            strcpy(array[i].nombre,nombre);
            strcpy(array[i].apellido,apellido);
            strcpy(array[i].cuit,cuit);
            array[i].idCliente = proximoId();
            array[i].isEmpty = 0;
        }
        retorno = 0;
    }
    return retorno;
}
//Retorna un entero que es = a la posicion del Id.
int cliente_buscarPorId(Cliente* array,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && array != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(!array[i].isEmpty && array[i].idCliente==id)
            {
                retorno=i;
                break;
            }
        }
    }
    return retorno;
}

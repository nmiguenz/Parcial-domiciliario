#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Publicacion.h"
#include "Cliente.h"
#include "utn.h"

static int proximoId();
static int buscarLugarLibre(Publicacion* publicacion,int limite);


/** \brief Inicializa el array de publicaciones
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \return int [0] OK [1] ERROR
 *
 */
int publicacion_init(Publicacion* publicacion,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && publicacion != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            publicacion[i].isEmpty=1;
        }
    }
    return retorno;
}

/** \brief Mustra el debug de publicacion
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \return int [0] OK [1] ERROR
 *
 */
int publicacion_mostrarDebug(Publicacion* publicacion,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && publicacion != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            printf("[DEBUG] - %d - %s - %d\n",publicacion[i].idPublicacion, publicacion[i].textoAviso, publicacion[i].isEmpty);
        }
    }
    return retorno;
}

/** \brief Muestra el contenido de publicacion en la posicion i
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \param array Cliente* puntero al array cliente
 * \param limCliente int limite definido para Cliente
 * \return int [0] OK [1] ERROR
 *
 */
int publicacion_mostrar(Publicacion* publicacion,int limite, Cliente* array, int limCliente)
{
    int retorno = -1;
    int i;
    if(limite > 0 && publicacion != NULL)
    {
        retorno = 0;
        for(i=0;i<limite;i++)
        {
            if(!publicacion[i].isEmpty)
                printf("[RELEASE] -ID Pub: %d - %s - %d - IDCliente: %d -Estado: %d\n",publicacion[i].idPublicacion, publicacion[i].textoAviso, publicacion[i].rubro,publicacion[i].idCliente,publicacion[i].estado);
        }
    }
    return retorno;
}

/** \brief Muestra los datos del cliente a quien corresponde esa publicacion
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \param array Cliente* puntero al array
 * \param limCliente int limite definido para cliente
 * \param id int id de la publicacion buscada
 * \return int [0] OK [1] ERROR
 *
 */
int publicacion_mostrar_porIdPublicacion(Publicacion* publicacion,int limite, Cliente* array, int limCliente, int id)
{
    int retorno = -1;
    int i;
    int indicePublicacion;

    if(limite > 0 && publicacion != NULL && limCliente > 0 && array != NULL)
    {
        indicePublicacion = publicacion_buscarPorId(publicacion, limite, id);
        retorno = 0;
        if(indicePublicacion>=0)
        {
            for(i=0;i<limCliente;i++)
            {
                if(!array[i].isEmpty && array[i].idCliente==publicacion[indicePublicacion].idCliente)
                    printf("ID Publicacion: %d -ID: %d -Nombre: %s -Apellido: %s -CUIT: %s\n",publicacion[indicePublicacion].idPublicacion,array[i].idCliente, array[i].nombre, array[i].apellido,array[i].cuit);
            }
        }
    }
    return retorno;
}

/** \brief Muestra la publicacion a partir del Id del cliente
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \param idCliente int id del cliente de quien estoy buscando las publicaciones
 * \return int [0] OK [1] ERROR
 *
 */
int publicacion_mostrarPorIdCliente(Publicacion* publicacion, int limite, int idCliente)
{
    int i;
    int retorno=-1;
    if(limite>0)
    {
        for(i=0;i<limite;i++)
        {
            retorno = 0;
            if(!publicacion[i].isEmpty && publicacion[i].idCliente==idCliente)
            {
                printf("ID Publicacion:%d - Aviso: %s - Rubro: %d\n", publicacion[i].idPublicacion,
                       publicacion[i].textoAviso, publicacion[i].rubro);
            }
        }
    }
    return retorno;
}

/** \brief Da de altas las publicaciones a partir del ID de cliente
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \param id int id del cliente de quien quiero dar de alta una publicacion
 * \return int [0] OK [1] ERROR
 *
 */
int publicacion_alta(Publicacion* publicacion,int limite,int id)
{
    int retorno = -1;
    int i;
    char auxAviso[50];
    int auxRubro;
    int estado;

    if(limite > 0 && publicacion != NULL)
    {
        i= buscarLugarLibre(publicacion,limite);
        if (i>=0)
        {
            if(!getValidString("\nAviso? ","\nEso no es un aviso","El maximo es 50",auxAviso,40,2))
            {
                if(!getValidInt("\nIngrese el numero de rubro: ","\nEso no es un rubro",&auxRubro,1,10,2))
                {
                    retorno = 0;
                    estado = 1;
                    strcpy(publicacion[i].textoAviso,auxAviso);
                    publicacion[i].rubro=auxRubro;
                    publicacion[i].idPublicacion = proximoId();
                    publicacion[i].estado = estado;
                    publicacion[i].idCliente = id;
                    publicacion[i].isEmpty = 0;
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

/** \brief Pone en pausa una publicacion activa al cambiar el [1] Activo por [0] Inactivo
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \param idPublicacion int Id de la publicacion a pausar
 * \return int [0] OK [1] ERROR
 *
 */
int publicacion_pausar(Publicacion* publicacion,int limite, int idPublicacion)
{
    int retorno = -1;
    int i;
    int opcion;

    getValidInt("Desea cambiar el estado a pausado? (1.SI / 2.NO) ","Esa no es una opcion valida",&opcion,0,1,2);

    if(opcion == 1)
    {
        if(limite > 0 && publicacion != NULL)
        {
            retorno = -2;
            for(i=0;i<limite;i++)
            {
                if(!publicacion[i].isEmpty && publicacion[i].idPublicacion==idPublicacion)
                {
                    publicacion[i].estado = 0;
                    retorno = 0;
                    break;
                }
            }
        }
    }
    return retorno;
}

/** \brief Pone en pausa una publicacion
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \param idPublicacion int Id de la publicacion a pausar
 * \return int [0] OK [1] ERROR
 *
 */
int publicacion_reanudar(Publicacion* publicacion,int limite, int idPublicacion)
{
    int retorno = -1;
    int i;
    int opcion;

    getValidInt("Desea cambiar el estado a activo? (1.SI / 2.NO) ","Esa no es una opcion valida",&opcion,0,1,2);

    if(opcion == 1)
    {
        if(limite > 0 && publicacion != NULL)
        {
            retorno = -2;
            for(i=0;i<limite;i++)
            {
                if(!publicacion[i].isEmpty && publicacion[i].idPublicacion==idPublicacion)
                {
                    publicacion[i].estado = 1;
                    retorno = 0;
                    break;
                }
            }
        }
    }
    return retorno;
}

/** \brief Da de baja al cliente y sus publicaciones
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \param array Cliente* puntero al array de cliente
 * \param limCliente int limite definido para cliente
 * \param id int id del cliente a eliminar
 * \return int [0] OK [1] ERROR
 *
 */
int publicacion_cliente_baja(Publicacion* publicacion,int limite,Cliente* array,int limCliente ,int id)
{
    int retorno = -1;
    int i;
    int opcion;

    getValidInt("Desea eliminar al cliente y la publicacion? (1.SI/2.NO)\n","Esa no es una opcion valida",&opcion,0,1,2);

    if(opcion== 1)
    {
        if(limite > 0 && publicacion != NULL)
        {
            retorno = -2;
            for(i=0;i<limite;i++)
            {
                if(!publicacion[i].isEmpty && publicacion[i].idCliente==id)
                {
                    publicacion[i].isEmpty = 1;
                }
            }
        }
        if(limCliente > 0 && array != NULL)
        {
            for(i=0;i<limCliente;i++)
            {
                retorno = -2;
                if(!array[i].isEmpty && array[i].idCliente==id)
                    {
                        array[i].isEmpty = 1;
                        retorno = 0;
                    }
            }
        }
    }
    return retorno;
}

/** \brief Modificar publicacion a partir de su Id
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \param id int Id de la publicacion a modificar
 * \return int [0] OK [1] ERROR
 *
 */
int publicacion_modificacion(Publicacion* publicacion,int limite, int id)
{
    int retorno = -1;
    int i;
    char buffer[50];
    if(limite > 0 && publicacion != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(!publicacion[i].isEmpty && publicacion[i].idPublicacion==id)
            {
                if(!getValidString("\nNombre? ","\nEso no es un nombre","El maximo es 40",buffer,40,2))
                {
                    retorno = 0;
                    strcpy(publicacion[i].textoAviso,buffer);
                    //------------------------------
                    //------------------------------
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

int publicacion_ordenar(Publicacion* publicacion,int limite, int orden)
{
    int retorno = -1;
    int i;
    int flagSwap;
    Publicacion auxiliarEstructura;

    if(limite > 0 && publicacion != NULL)
    {
        do
        {
            flagSwap = 0;
            for(i=0;i<limite-1;i++)
            {
                if(!publicacion[i].isEmpty && !publicacion[i+1].isEmpty)
                {
                    if((strcmp(publicacion[i].textoAviso,publicacion[i+1].textoAviso) > 0 && orden) || (strcmp(publicacion[i].textoAviso,publicacion[i+1].textoAviso) < 0 && !orden)) //******
                    {
                        auxiliarEstructura = publicacion[i];
                        publicacion[i] = publicacion[i+1];
                        publicacion[i+1] = auxiliarEstructura;
                        flagSwap = 1;
                    }
                }
            }
        }while(flagSwap);
    }
    return retorno;
}

/** \brief Busca un lugar libre en la estructura
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \return int retorna i correspondiente al lugar libre
 *
 */
static int buscarLugarLibre(Publicacion* publicacion,int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && publicacion != NULL)
    {
        for(i=0;i<limite;i++)
        {
            if(publicacion[i].isEmpty==1)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}


/** \brief Incrementa en uno el Id
 *
 * \return int retorna la proxima posicion de Id
 *
 */
static int proximoId()
{
    static int proximoId = -1;
    proximoId++;
    return proximoId;
}

/** \brief Fuerza el alta de la publicacion
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \param idCliente int Id de clienye
 * \param array Cliente* puntero al array cliente
 * \param limCliente int limite definido para cliente
 * \param textoAviso char* puntero al aviso
 * \param rubro int Define el rubro, que va desde 1 a 10
 * \param estado int [1] ACTIVO [0] INACTIVO
 * \return int [0] OK [1] ERROR
 *
 */
int publicacion_altaForzada(Publicacion* publicacion,int limite,int idCliente, Cliente* array, int limCliente, char* textoAviso, int rubro, int estado)
{

    int retorno = -1;
    int i;

    if(limite > 0 && publicacion != NULL)
    {
        i = buscarLugarLibre(publicacion,limite);
        if(i >= 0)
        {
            retorno = 0;
            publicacion[i].idCliente = idCliente;
            strcpy(publicacion[i].textoAviso,textoAviso);
            publicacion[i].rubro = rubro;
            publicacion[i].estado = estado;
            publicacion[i].idPublicacion = proximoId();
            publicacion[i].isEmpty = 0;
        }
        retorno = 0;
    }
    return retorno;
}
/** \brief retorna un entero que corresponde a la posicion del Id
 *
 * \param publicacion Publicacion* puntero a publicacion
 * \param limite int limite definido para publicacion
 * \param id int id de la publicacion buscada
 * \return int retorna un entero que corresponde a la posicion en la que se encuentra ese Id
 *
 */
int publicacion_buscarPorId(Publicacion* publicacion,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && publicacion != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(!publicacion[i].isEmpty && publicacion[i].idPublicacion==id)
            {
                retorno=i;
                break;
            }
        }
    }
    return retorno;
}

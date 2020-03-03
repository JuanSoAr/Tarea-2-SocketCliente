#include "socketcliente.h"
SocketCliente::SocketCliente()
{
}
/**
 * @brief SocketCliente::connectar
 * Conencta el cleinte con el servidor
 * @return
 * returna true si no existe ningu fallo en la conexion
 */
bool SocketCliente::connectar()
{
    descriptor = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(descriptor < 0)
        return false;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = ntohs(4050);
    memset(&info.sin_zero,0,sizeof(info.sin_zero));

    if((::connect(descriptor,(sockaddr*)&info,(socklen_t)sizeof(info))) < 0)
     return false;

    pthread_t hilo;
    pthread_create(&hilo,0,SocketCliente::controlador,(void *)this);
    pthread_detach(hilo);
    return true;
}

/**
 * @brief SocketCliente::controlador
 * Controla la llega de mensaje del servidor
 * @param obj
 * @return
 */
void * SocketCliente::controlador(void *obj)
{
    SocketCliente *padre = (SocketCliente*)obj;

    while (true) {
        string mensaje;
        while (1) {
            char buffer[10] = {0};
            int bytes = recv(padre->descriptor,buffer,10,0);
            mensaje.append(buffer,bytes);
            if(bytes <= 0)
            {
                close(padre->descriptor);
                pthread_exit(NULL);
            }
            if(bytes < 10)
                break;
        }
        emit padre->NewMensaje(QString::fromStdString(mensaje));
    }
    close(padre->descriptor);
    pthread_exit(NULL);
}

/**
 * @brief SocketCliente::setMensaje
 * @param msn
 * Escribe el mensaje que se va a enviar
 */
void SocketCliente::setMensaje(const char *msn)
{
    cout << "bytes enviados "<< send(descriptor,msn,strlen(msn),0) << endl;
}

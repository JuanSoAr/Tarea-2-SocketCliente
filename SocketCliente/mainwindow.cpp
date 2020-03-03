#include "mainwindow.h"
#include "ui_mainwindow.h"
int bandera = 1;

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    conexion = new SocketCliente;
    if(!conexion->connectar())
        QMessageBox::critical(this,"Error","Error al conectar con el servidor",QMessageBox::Ok);

    connect(conexion,SIGNAL(NewMensaje(QString)),SLOT(printMensaje(QString)));
    connect(ui->b_enviar,SIGNAL(clicked()),SLOT(sendMensaje()));
    connect(ui->c_enviar,SIGNAL(clicked()),SLOT(pedirMensaje()));
}
/**
 * @brief MainWindow::~MainWindow
 * La clase MainWindow controla la interfaz grafica,y el comportamiento de sus coponentes con el enterno
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::sendMensaje
 * Envia un mensaje el cual crea el grafo en en sokect
 */
void MainWindow::sendMensaje()
{
    if(bandera==1){
        conexion->setMensaje("Crear grafo");
        bandera +=1;
    }
    else{
        QMessageBox::critical(this,"Error","Ya se ha creado un grafo",QMessageBox::Ok);

    }
}
/**
 * @brief MainWindow::pedirMensaje
 * Envia un mensaje el cual pide que se implemente el Dijkstra
 */
void MainWindow::pedirMensaje(){
    conexion->setMensaje("Pedir datos");
}
/**
 * @brief MainWindow::printMensaje
 * @param msn
 * Imprime un mensaje recivido por el servidos
 */
void MainWindow::printMensaje(QString msn)
{
    ui->txt_log->setPlainText(msn);
}


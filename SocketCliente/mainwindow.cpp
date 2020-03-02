#include "mainwindow.h"
#include "ui_mainwindow.h"
int bandera = 1;
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
}

MainWindow::~MainWindow()
{
    delete ui;
}


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

void MainWindow::printMensaje(QString msn)
{
    ui->txt_log->setPlainText(msn);
}

void MainWindow::on_pushButton_clicked()
{

}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <socketcliente.h>
#include <QMessageBox>
/**
 *
 */
namespace Ui {
class MainWindow;
}
/**
 * @brief The MainWindow class
 * Clase controladora de la  interfaz
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SocketCliente *conexion;
private slots:
    void printMensaje(QString msn);
    void sendMensaje();
    void pedirMensaje();
};

#endif // MAINWINDOW_H

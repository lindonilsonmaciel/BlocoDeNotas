#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFile"
#include "QFileDialog"
#include "QTextStream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionNovo_triggered(){
    localArquivo="";
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}

void MainWindow::on_actionAbrir_triggered(){
    QString filtro = "Todos os Arquivos (*.*);;Arquivos de Texto (*.txt)";
    QString nomeArquivo = QFileDialog::getOpenFileName(this, "Abrir", QDir::homePath(), filtro);
    QFile arquivo(nomeArquivo);
    localArquivo = nomeArquivo;
    if(!arquivo.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Erro", "O arquivo não pode ser aberto.");
        return;
    }
    //Preciso colocar o & na frente da variável, assim ela vai pegar o endereço, caso não faça não funciona
    QTextStream entrada(&arquivo);
    QString texto = entrada.readAll();
    ui->textEdit->setText(texto);
    arquivo.close();
}

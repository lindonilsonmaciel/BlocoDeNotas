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

void MainWindow::on_actionSalvar_como_triggered(){
    QString filtro = "Todos os Arquivos (*.*);;Arquivos de Texto (*.txt)";
    //Posso passar apenas os dois primeiros parâmetros se preferir
    QString nome_arquivo = QFileDialog::getSaveFileName(this, "Salvar", QDir::homePath(), filtro);
    QFile arquivo(nome_arquivo);
    localArquivo = nome_arquivo;
    if(!arquivo.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Erro", "O arquivo não pode ser salvo.");
        return;
    }
    QTextStream saida(&arquivo);
    QString texto = ui->textEdit->toPlainText();
    saida << texto;
    arquivo.flush();
    arquivo.close();
}

void MainWindow::on_actionSalvar_triggered(){
    QFile arquivo(localArquivo);
    if(!arquivo.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Erro", "O arquivo não pode ser salvo.");
        return;
    }
    QTextStream saida(&arquivo);
    QString texto = ui->textEdit->toPlainText();
    saida << texto;
    arquivo.flush();
    arquivo.close();
}

void MainWindow::on_actionSair_triggered(){
    //Fechar
    close();
}

void MainWindow::on_actionCopiar_triggered(){
    //Copiar
    ui->textEdit->copy();
}

void MainWindow::on_actionRecortar_triggered(){
    //Recortar
    ui->textEdit->cut();
}

void MainWindow::on_actionColar_triggered(){
    //Colar
    ui->textEdit->paste();
}

void MainWindow::on_actionDesfazer_triggered(){
    //Desfazer
    ui->textEdit->undo();
}

void MainWindow::on_actionRefazer_triggered(){
    //Refazer
    ui->textEdit->redo();
}

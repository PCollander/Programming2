#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QtGlobal>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_findPushButton_pressed()
{
    QString file_input = ui->fileLineEdit->text();
    QString phrase_input = ui->keyLineEdit->text();
    QFile file(file_input);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->textBrowser->setText("File not found");
        return;
    }
    else if(phrase_input.isEmpty()){
        ui->textBrowser->setText("File found");
    }
    else{
        QTextStream in(&file);
        while (!in.atEnd()){
            QString line = in.readLine();
            if (ui->matchCheckBox->isChecked()){
                if (line.contains(phrase_input, Qt::CaseSensitive)){
                    ui->textBrowser->setText("Word found");
                    return;
                }
            }
            else{
                QString upper_line = line.toUpper();
                QString upper_phrase = phrase_input.toUpper();
                if (upper_line.contains(upper_phrase)){
                    ui->textBrowser->setText("Word found");
                    return;
                }
            }
        }
        ui->textBrowser->setText("Word not found");
    }
}

#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QProcess>
#include <QString>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <ctime>
#include <iostream>
#include<QtDebug>


using namespace std;

static QString cars[10],animals[10],countries[10],language,answer,word ="*",cat,alfabet,flit;
static int n = 0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand( static_cast<unsigned int>(time(nullptr)));
    ui->setupUi(this);
    ui->pushButton_4->setHidden(true);
    ui->pushButton_5->setHidden(true);
    ui->pushButton_6->setHidden(true);
    ui->pushButton_7->setHidden(true);
    ui->pushButton_8->setHidden(true);
    ui->pushButton_9->setHidden(true);
    ui->pushButton_10->setHidden(true);
    ui->pushButton_11->setHidden(true);
    ui->pushButton_12->setHidden(true);
    ui->pushButton_13->setHidden(true);
    ui->pushButton_14->setHidden(true);
    ui->pushButton_15->setHidden(true);
    ui->pushButton_16->setHidden(true);
    ui->pushButton_17->setHidden(true);
    ui->pushButton_18->setHidden(true);
    ui->pushButton_19->setHidden(true);
    ui->pushButton_20->setHidden(true);
    ui->pushButton_21->setHidden(true);
    ui->pushButton_22->setHidden(true);
    ui->pushButton_23->setHidden(true);
    ui->pushButton_24->setHidden(true);
    ui->pushButton_25->setHidden(true);
    ui->pushButton_26->setHidden(true);
    ui->pushButton_27->setHidden(true);
    ui->pushButton_28->setHidden(true);
    ui->pushButton_29->setHidden(true);
    ui->pushButton_30->setHidden(true);
    ui->pushButton_31->setHidden(true);
    ui->pushButton_32->setHidden(true);
    ui->pushButton_33->setHidden(true);
    ui->pushButton_34->setHidden(true);
    ui->pushButton_35->setHidden(true);
    ui->pushButton_36->setHidden(true);
    ui->pushButton_37->setHidden(true);
    ui->pushButton_38->setHidden(true);
    ui->pushButton_39->setHidden(true);
    ui->pushButton->setHidden(true);
    ui->pushButton_2->setHidden(true);
    ui->pushButton_3->setHidden(true);
    ui->label_5->setHidden(true);
    ui->label_2->setHidden(true);
    ui->label_3->setHidden(true);
    ui->label_4->setHidden(true);
    ui->label_6->setHidden(true);
    ui->label_7->setHidden(true);
    ui->label_8->setHidden(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::unhide_buttons(){
        ui->pushButton->setHidden(true);
        ui->pushButton_3->setHidden(true);
        ui->pushButton_2->setHidden(true);
        ui->pushButton_4->setHidden(false);
        ui->pushButton_5->setHidden(false);
        ui->pushButton_6->setHidden(false);
        ui->pushButton_7->setHidden(false);
        ui->pushButton_8->setHidden(false);
        ui->pushButton_9->setHidden(false);
        ui->pushButton_10->setHidden(false);
        ui->pushButton_11->setHidden(false);
        ui->pushButton_12->setHidden(false);
        ui->pushButton_13->setHidden(false);
        ui->pushButton_14->setHidden(false);
        ui->pushButton_15->setHidden(false);
        ui->pushButton_16->setHidden(false);
        ui->pushButton_17->setHidden(false);
        ui->pushButton_18->setHidden(false);
        ui->pushButton_19->setHidden(false);
        ui->pushButton_20->setHidden(false);
        ui->pushButton_21->setHidden(false);
        ui->pushButton_22->setHidden(false);
        ui->pushButton_23->setHidden(false);
        ui->pushButton_24->setHidden(false);
        ui->pushButton_25->setHidden(false);
        ui->pushButton_26->setHidden(false);
        ui->pushButton_27->setHidden(false);
        ui->pushButton_28->setHidden(false);
        ui->pushButton_29->setHidden(false);
        ui->pushButton_30->setHidden(false);
        ui->pushButton_31->setHidden(false);
        ui->pushButton_32->setHidden(false);
        ui->pushButton_33->setHidden(false);
        ui->pushButton_34->setHidden(false);
        ui->pushButton_35->setHidden(false);
        ui->pushButton_36->setHidden(false);
        ui->pushButton_37->setHidden(false);
        ui->pushButton_38->setHidden(false);
        if(language == "RU"){
            ui->pushButton_30->setHidden(true);
            ui->pushButton_38->setHidden(true);
        }
        QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
        dbase.setDatabaseName(qApp->applicationDirPath() + "/words.sqlite");
        dbase.open();
}

void MainWindow::unhide_buttons2(){
    ui->label_6->setAlignment(Qt::AlignCenter);
    ui->label_5->setAlignment(Qt::AlignCenter);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_7->setAlignment(Qt::AlignCenter);
    ui->label_8->setAlignment(Qt::AlignCenter);
    QPixmap back(qApp->applicationDirPath() + "/background.png");
    ui->label->setPixmap(back);
    QPixmap pix0(qApp->applicationDirPath() + "/grafika0.png");
    ui->label_2->setPixmap(pix0);
    ui->pushButton->setHidden(false);
    ui->pushButton_2->setHidden(false);
    ui->pushButton_3->setHidden(false);
    ui->label_5->setHidden(false);
    ui->label_2->setHidden(false);
    ui->label_3->setHidden(false);
    ui->label_4->setHidden(false);
    ui->label_6->setHidden(false);
    ui->pushButton_40->setHidden(true);
    ui->pushButton_41->setHidden(true);
    ui->pushButton_42->setHidden(true);
}

void MainWindow::on_pushButton_clicked(){
    unhide_buttons();
    QSqlQuery query("SELECT cars FROM "+language);
    QString samochody;
    int i = 0;
    while (query.next()) {
             samochody = query.value(0).toString();
             cars[i] = samochody;
             ++i;
    }
    if(language=="EN")cat+="Cars";
    if(language=="PL")cat+="Samochody";
    if(language=="RU")cat+="Транспорт";
    ui->label_5->setText(cat);
    answer = cars[rand() % 9 +0];
    for(int i = 1;i<answer.length();++i)word="*"+word;
    ui->label_6->setText(word);
    ui->label_6->setHidden(false);

}

void MainWindow::on_pushButton_3_clicked(){
     unhide_buttons();
     QSqlQuery query("SELECT animals FROM "+language);
     QString animalss;
     int i = 0;
     while (query.next()) {
              animalss = query.value(0).toString();
              animals[i] = animalss;
              ++i;
     }
     if(language=="EN")cat+="Animals";
     if(language=="PL")cat+="Zwierzęta";
     if(language=="RU")cat+="Животные";
     ui->label_5->setText(cat);
     answer = animals[rand() % 9 +0];
     for(int i = 1;i<answer.length();++i)word="*"+word;
     ui->label_6->setText(word);
     ui->label_6->setHidden(false);
}

void MainWindow::on_pushButton_2_clicked(){
     unhide_buttons();
     QSqlQuery query("SELECT countries FROM "+language);
     QString countriess;
     int i = 0;
     while (query.next()) {
              countriess = query.value(0).toString();
              countries[i] = countriess;
              ++i;
     }
     if(language=="EN")cat+="Countries";
     if(language=="PL")cat+="Państwa";
     if(language=="RU")cat+="Страны";
     ui->label_5->setText(cat);
     answer = countries[rand() % 9 +0];
     for(int i = 1;i<answer.length();++i)word="*"+word;
     ui->label_6->setText(word);
     ui->label_6->setHidden(false);
}

void MainWindow::gameover(){
    ui->pushButton_4->setHidden(true);
    ui->pushButton_5->setHidden(true);
    ui->pushButton_6->setHidden(true);
    ui->pushButton_7->setHidden(true);
    ui->pushButton_8->setHidden(true);
    ui->pushButton_9->setHidden(true);
    ui->pushButton_10->setHidden(true);
    ui->pushButton_11->setHidden(true);
    ui->pushButton_12->setHidden(true);
    ui->pushButton_13->setHidden(true);
    ui->pushButton_14->setHidden(true);
    ui->pushButton_15->setHidden(true);
    ui->pushButton_16->setHidden(true);
    ui->pushButton_17->setHidden(true);
    ui->pushButton_18->setHidden(true);
    ui->pushButton_19->setHidden(true);
    ui->pushButton_20->setHidden(true);
    ui->pushButton_21->setHidden(true);
    ui->pushButton_22->setHidden(true);
    ui->pushButton_23->setHidden(true);
    ui->pushButton_24->setHidden(true);
    ui->pushButton_25->setHidden(true);
    ui->pushButton_26->setHidden(true);
    ui->pushButton_27->setHidden(true);
    ui->pushButton_28->setHidden(true);
    ui->pushButton_29->setHidden(true);
    ui->pushButton_30->setHidden(true);
    ui->pushButton_31->setHidden(true);
    ui->pushButton_32->setHidden(true);
    ui->pushButton_33->setHidden(true);
    ui->pushButton_34->setHidden(true);
    ui->pushButton_35->setHidden(true);
    ui->pushButton_36->setHidden(true);
    ui->pushButton_37->setHidden(true);
    ui->pushButton_38->setHidden(true);
    ui->pushButton_39->setHidden(false);
    ui->label_7->setHidden(false);
    ui->label_8->setHidden(false);
    ui->label_6->setHidden(true);
    ui->label_7->setStyleSheet("QLabel { background-color: #8AB88C;border: 1px solid black;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;color : red; }");
    ui->label_7->setText("GAME OVER!");
    ui->label_8->setText(answer);
}

void MainWindow::victory(){
    ui->pushButton_4->setHidden(true);
    ui->pushButton_5->setHidden(true);
    ui->pushButton_6->setHidden(true);
    ui->pushButton_7->setHidden(true);
    ui->pushButton_8->setHidden(true);
    ui->pushButton_9->setHidden(true);
    ui->pushButton_10->setHidden(true);
    ui->pushButton_11->setHidden(true);
    ui->pushButton_12->setHidden(true);
    ui->pushButton_13->setHidden(true);
    ui->pushButton_14->setHidden(true);
    ui->pushButton_15->setHidden(true);
    ui->pushButton_16->setHidden(true);
    ui->pushButton_17->setHidden(true);
    ui->pushButton_18->setHidden(true);
    ui->pushButton_19->setHidden(true);
    ui->pushButton_20->setHidden(true);
    ui->pushButton_21->setHidden(true);
    ui->pushButton_22->setHidden(true);
    ui->pushButton_23->setHidden(true);
    ui->pushButton_24->setHidden(true);
    ui->pushButton_25->setHidden(true);
    ui->pushButton_26->setHidden(true);
    ui->pushButton_27->setHidden(true);
    ui->pushButton_28->setHidden(true);
    ui->pushButton_29->setHidden(true);
    ui->pushButton_30->setHidden(true);
    ui->pushButton_31->setHidden(true);
    ui->pushButton_32->setHidden(true);
    ui->pushButton_33->setHidden(true);
    ui->pushButton_34->setHidden(true);
    ui->pushButton_35->setHidden(true);
    ui->pushButton_36->setHidden(true);
    ui->pushButton_37->setHidden(true);
    ui->pushButton_38->setHidden(true);
    ui->pushButton_39->setHidden(false);
    ui->label_7->setHidden(false);
    ui->label_8->setHidden(false);
    ui->label_6->setHidden(true);
    ui->label_7->setText("VICTORY!");
    ui->label_7->setStyleSheet("QLabel { background-color: #8AB88C;border: 1px solid black;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;color : blue; }");
    ui->label_8->setText(answer);
}

bool MainWindow::ans(int anum){
    if(flit.contains(alfabet[anum])){
        bool fail = true;
        for(int i = 0;i<answer.length();++i){
            if(answer[i]==alfabet[anum]){
                word[i] = alfabet[anum];
                fail=false;
            }
        }
        if(word.contains("*")==false)victory();
        ui->label_6->setText(word);
        if(fail==true){
            flit=flit.replace(alfabet[anum],"0");
            QString status = ui->label_4->text();
            status.chop(2);
            ui->label_4->setText(status);
            ++n;
            switch (n) {
                case 1:
                    static QPixmap pix1(qApp->applicationDirPath() + "/grafika1.png");
                    ui->label_2->setPixmap(pix1);
                    break;
                case 2:
                    static QPixmap pix2(qApp->applicationDirPath() + "/grafika2.png");
                    ui->label_2->setPixmap(pix2);
                    break;
                case 3:
                    static QPixmap pix3(qApp->applicationDirPath() + "/grafika3.png");
                    ui->label_2->setPixmap(pix3);
                    break;
                case 4:
                    static QPixmap pix4(qApp->applicationDirPath() + "/grafika4.png");
                    ui->label_2->setPixmap(pix4);
                    break;
                case 5:
                    static QPixmap pix5(qApp->applicationDirPath() + "/grafika5.png");
                    ui->label_2->setPixmap(pix5);
                    break;
                case 6:
                    static QPixmap pix6(qApp->applicationDirPath() + "/grafika6.png");
                    ui->label_2->setPixmap(pix6);
                    break;
                case 7:
                    static QPixmap pix7(qApp->applicationDirPath() + "/grafika7.png");
                    ui->label_2->setPixmap(pix7);
                    break;
                case 8:
                    static QPixmap pix8(qApp->applicationDirPath() + "/grafika8.png");
                    ui->label_2->setPixmap(pix8);
                    break;
            }
            if(n>=8)gameover();
            return false;
        }else{
            return true;
        }
    }
}

void MainWindow::on_pushButton_4_clicked(){
    if(ans(0)==false){
        ui->pushButton_4->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_5_clicked(){
    if(ans(1)==false){
        ui->pushButton_5->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_6_clicked(){
    if(ans(2)==false){
        ui->pushButton_6->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_7_clicked(){
    if(ans(3)==false){
        ui->pushButton_7->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_8_clicked(){
    if(ans(4)==false){
        ui->pushButton_8->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_9_clicked(){
    if(ans(5)==false){
        ui->pushButton_9->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_17_clicked(){
    if(ans(6)==false){
        ui->pushButton_17->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_10_clicked(){
    if(ans(7)==false){
        ui->pushButton_10->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_11_clicked(){
    if(ans(8)==false){
        ui->pushButton_11->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_12_clicked(){
    if(ans(9)==false){
        ui->pushButton_12->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_13_clicked(){
    if(ans(10)==false){
        ui->pushButton_13->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_14_clicked(){
    if(ans(11)==false){
        ui->pushButton_14->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_15_clicked(){
    if(ans(12)==false){
        ui->pushButton_15->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_16_clicked(){
    if(ans(13)==false){
        ui->pushButton_16->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_18_clicked(){
    if(ans(14)==false){
        ui->pushButton_18->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_19_clicked(){
    if(ans(15)==false){
        ui->pushButton_19->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_20_clicked(){
    if(ans(16)==false){
        ui->pushButton_20->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_21_clicked(){
    if(ans(17)==false){
        ui->pushButton_21->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_22_clicked(){
    if(ans(18)==false){
        ui->pushButton_22->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_23_clicked(){
    if(ans(19)==false){
        ui->pushButton_23->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_36_clicked(){
    if(ans(20)==false){
        ui->pushButton_36->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_25_clicked(){
    if(ans(21)==false){
        ui->pushButton_25->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_26_clicked(){
    if(ans(22)==false){
        ui->pushButton_26->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}
void MainWindow::on_pushButton_27_clicked(){
    if(ans(23)==false){
        ui->pushButton_27->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_33_clicked(){
    if(ans(24)==false){
        ui->pushButton_33->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_29_clicked(){
    if(ans(25)==false){
        ui->pushButton_29->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_24_clicked(){
    if(ans(26)==false){
        ui->pushButton_24->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_37_clicked(){
    if(ans(27)==false){
        ui->pushButton_37->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_31_clicked(){
    if(ans(28)==false){
        ui->pushButton_31->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_32_clicked(){
    if(ans(29)==false){
        ui->pushButton_32->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_28_clicked(){
    if(ans(30)==false){
        ui->pushButton_28->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_34_clicked(){
    if(ans(31)==false){
        ui->pushButton_34->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_35_clicked(){
    if(ans(32)==false){
        ui->pushButton_35->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_30_clicked(){
    if(ans(33)==false){
        ui->pushButton_30->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_38_clicked(){
    if(ans(34)==false){
        ui->pushButton_38->setStyleSheet(" background-color: #af0000;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    }
}

void MainWindow::on_pushButton_39_clicked(){
    word = "*";
    flit = alfabet;
    n = 0;
    ui->pushButton->setHidden(false);
    ui->pushButton_3->setHidden(false);
    ui->pushButton_2->setHidden(false);
    ui->pushButton_39->setHidden(true);
    ui->label_7->setHidden(true);
    ui->label_8->setHidden(true);
    if(language=="EN"){
        ui->label_5->setText("Choose category:");
        cat = "Category:";
    }
    if(language=="PL"){
        ui->label_5->setText("Wybierz kategorie:");
        cat = "Kategoria:";
    }
    if(language=="RU"){
        ui->label_5->setText("Выберите категорию:");
        cat = "Категория:";
    }
    ui->label_4->setText(" ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥");
    QPixmap pix0(qApp->applicationDirPath() + "/grafika0.png");
    ui->label_2->setPixmap(pix0);
    ui->pushButton_4->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_5->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_6->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_7->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_8->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_9->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_10->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_11->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_12->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_13->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_14->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_15->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_16->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_17->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_18->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_19->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_20->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_21->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_22->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_23->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_24->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_25->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_26->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_27->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_28->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_29->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_30->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_31->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_32->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_33->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_34->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_35->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_36->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_37->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
    ui->pushButton_38->setStyleSheet(" background-color: #4CAF50;border: none;text-align: center;text-decoration: none;display: inline-block;color : white;font-size: 16px; ");
}

void MainWindow::on_pushButton_40_clicked()
{
    unhide_buttons2();
    ui->label_5->setText("Choose category:");
    ui->pushButton->setText("Cars");
    ui->pushButton_2->setText("Countries");
    ui->pushButton_3->setText("Animals");
    cat = "Category:";
    language = "EN";
    setWindowTitle("Hangman");
    alfabet ="AĄBCĆDEĘFGHIJKLŁMNŃOÓPRSŚTUWYZŹŻQVX";
    flit = alfabet;
}

void MainWindow::on_pushButton_41_clicked()
{
    unhide_buttons2();
    ui->label_5->setText("Выбери категорию:");
    ui->pushButton->setText("Транспорт");
    ui->pushButton_2->setText("Страны");
    ui->pushButton_3->setText("Животные");
    cat = "Категория:";
    language = "RU";
    setWindowTitle("Виселица");
    alfabet ="АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    flit = alfabet;
    ui->pushButton_4->setText("А");
    ui->pushButton_5->setText("Б");
    ui->pushButton_6->setText("В");
    ui->pushButton_7->setText("Г");
    ui->pushButton_8->setText("Д");
    ui->pushButton_9->setText("Е");
    ui->pushButton_17->setText("Ё");
    ui->pushButton_10->setText("Ж");
    ui->pushButton_11->setText("З");
    ui->pushButton_12->setText("И");
    ui->pushButton_13->setText("Й");
    ui->pushButton_14->setText("К");
    ui->pushButton_15->setText("Л");
    ui->pushButton_16->setText("М");
    ui->pushButton_18->setText("Н");
    ui->pushButton_19->setText("О");
    ui->pushButton_20->setText("П");
    ui->pushButton_21->setText("Р");
    ui->pushButton_22->setText("С");
    ui->pushButton_23->setText("Т");
    ui->pushButton_36->setText("y");
    ui->pushButton_25->setText("Ф");
    ui->pushButton_26->setText("Х");
    ui->pushButton_27->setText("Ц");
    ui->pushButton_33->setText("Ч");
    ui->pushButton_29->setText("Ш");
    ui->pushButton_24->setText("Щ");
    ui->pushButton_37->setText("Ъ");
    ui->pushButton_31->setText("Ы");
    ui->pushButton_32->setText("Ь");
    ui->pushButton_28->setText("Э");
    ui->pushButton_34->setText("Ю");
    ui->pushButton_35->setText("Я");
}

void MainWindow::on_pushButton_42_clicked()
{
    unhide_buttons2();
    ui->label_5->setText("Wybierz kategorie:");
    ui->pushButton->setText("Samochody");
    ui->pushButton_2->setText("Państwa");
    ui->pushButton_3->setText("Zwierzęta");
    language = "PL";
    cat = "Kategoria:";
    setWindowTitle("Wisielec");
    alfabet ="AĄBCĆDEĘFGHIJKLŁMNŃOÓPRSŚTUWYZŹŻQVX";
    flit = alfabet;
}

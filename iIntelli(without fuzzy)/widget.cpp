#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //=======Initialiaziing the first window==============//
    ui->screen2widget->setHidden(true);
    ui->loading->setHidden(true);
    ui->displayButton->setHidden(true);
    //====================================================//

    //Generate data into database map
}

void Widget::loaddata(){
    //Call the function
    string command="./runiIntelli ";
    query= ui->queryBox->text();
    command+= query.toStdString();

    system(command.c_str());

    //Put sentences in the edit boxes

    ifstream ifile;
    ifile.open("out.txt");

    string temp="";
    int count=0;
    char ch;
    while(!ifile.eof()){
            //cout << "Reading Char" << endl;
            ifile.get(ch);
            if(ch=='.'){
                vec.push_back(temp);
                temp="";
            }else{
                temp+=ch;
            }
     }

    ifile.close();

    int vec_size=vec.size();
    for(int i=0;i<penaltyvec.size();i++){
        penaltyvec[i]=0;
    }
    if(vec.size()>=1){
        ui->lineEdit1->setText(vec[0].c_str());
    }
    if(vec.size()>=2){
        ui->lineEdit2->setText(vec[1].c_str());
    }
    if(vec.size()>=3){
        ui->lineEdit3->setText(vec[2].c_str());
    }
    if(vec.size()>=4){
        ui->lineEdit4->setText(vec[3].c_str());
    }
    if(vec.size()>=5){
        ui->lineEdit5->setText(vec[4].c_str());
    }
    if(vec.size()>=6){
        ui->lineEdit6->setText(vec[5].c_str());
    }
    if(vec.size()>=7){
        ui->lineEdit7->setText(vec[6].c_str());
    }
    if(vec.size()>=8){
        ui->lineEdit8->setText(vec[7].c_str());
    }
    if(vec.size()>=9){
        ui->lineEdit9->setText(vec[8].c_str());
    }
    if(vec.size()>=10){
        ui->lineEdit10->setText(vec[9].c_str());
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_generateButton_clicked()
{
    ui->loading->setHidden(false);

    loaddata();

    //Make displayButton visible
    ui->displayButton->setHidden(false);
}

void Widget::penalty(int index)
{
    //Penalise sentence in the database
    string temp="";
    for(int i=0;i<vec[index].size();i++){
        if(vec[index][i]==' '){
            if(database.count(temp)!=0){
                int size_vec=database[temp].connections.size();
                for(int j=0;j<size_vec;j++){
                    if(database[temp].connections[j].topic==query.toStdString()){
                        database[temp].connections[j].weight-=PENALTY;
                        if(database[temp].connections[j].secondWord.key==temp){
                            int size2=database[database[temp].connections[j].firstWord.key].connections.size();
                            for(int k=0;k<size2;k++){
                                if(database[database[temp].connections[j].firstWord.key].connections[k].topic==query.toStdString()){
                                       database[database[temp].connections[j].firstWord.key].connections[k].weight-=PENALTY;
                                }
                            }
                        }else{
                            int size2=database[database[temp].connections[j].secondWord.key].connections.size();
                            for(int k=0;k<size2;k++){
                                if(database[database[temp].connections[j].secondWord.key].connections[k].topic==query.toStdString()){
                                       database[database[temp].connections[j].secondWord.key].connections[k].weight-=PENALTY;
                                }
                            }
                        }
                    }
                }
            }
            temp="";
        }
        temp+=vec[index][i];
    }
}

void Widget::on_displayButton_clicked()
{
    ui->enterFrame->setHidden(true);
    ui->screen2widget->setHidden(false);
}

void Widget::on_crossButton1_clicked()
{
    penalty(0);

    ui->lineEdit1->setHidden(true);
    ui->crossButton1->setHidden(true);
}

void Widget::on_crossButton2_clicked()
{
    penalty(1);

    ui->lineEdit2->setHidden(true);
    ui->crossButton2->setHidden(true);
}

void Widget::on_crossButton3_clicked()
{
    penalty(2);

    ui->lineEdit3->setHidden(true);
    ui->crossButton3->setHidden(true);
}

void Widget::on_crossButton4_clicked()
{
    penalty(3);

    ui->lineEdit4->setHidden(true);
    ui->crossButton4->setHidden(true);
}

void Widget::on_crossButton5_clicked()
{
    penalty(4);

    ui->lineEdit5->setHidden(true);
    ui->crossButton5->setHidden(true);
}


void Widget::on_crossButton6_clicked()
{
    penalty(5);

    ui->lineEdit6->setHidden(true);
    ui->crossButton6->setHidden(true);
}



void Widget::on_crossButton7_clicked()
{
    penalty(6);

    ui->lineEdit7->setHidden(true);
    ui->crossButton7->setHidden(true);
}

void Widget::on_crossButton8_clicked()
{
    penalty(7);

    ui->lineEdit8->setHidden(true);
    ui->crossButton8->setHidden(true);
}

void Widget::on_crossButton9_clicked()
{
    penalty(8);

    ui->lineEdit9->setHidden(true);
    ui->crossButton9->setHidden(true);
}



void Widget::on_crossButton10_clicked()
{
    penalty(9);

    ui->lineEdit10->setHidden(true);
    ui->crossButton10->setHidden(true);
}

void Widget::on_printButton_clicked()
{
    //Writes data back into the database
    //prints the info into file
    fstream oofile("result.txt",ios::out);

    oofile << "***"<<ui->topicLabel->text().toStdString()<<"***"<<endl;

    if(ui->lineEdit1->isVisible()){
        oofile << ui->lineEdit1->text().toStdString() << endl;
    }
    if(ui->lineEdit2->isVisible()){
        oofile << ui->lineEdit2->text().toStdString() << endl;
    }
    if(ui->lineEdit3->isVisible()){
        oofile << ui->lineEdit3->text().toStdString() << endl;
    }
    if(ui->lineEdit4->isVisible()){
        oofile << ui->lineEdit4->text().toStdString() << endl;
    }
    if(ui->lineEdit5->isVisible()){
        oofile << ui->lineEdit5->text().toStdString() << endl;
    }
    if(ui->lineEdit6->isVisible()){
        oofile << ui->lineEdit6->text().toStdString() << endl;
    }
    if(ui->lineEdit7->isVisible()){
        oofile << ui->lineEdit7->text().toStdString() << endl;
    }
    if(ui->lineEdit8->isVisible()){
        oofile << ui->lineEdit8->text().toStdString() << endl;
    }
    if(ui->lineEdit9->isVisible()){
        oofile << ui->lineEdit9->text().toStdString() << endl;
    }
    if(ui->lineEdit10->isVisible()){
        oofile << ui->lineEdit10->text().toStdString() << endl;
    }
    oofile.close();

}

void Widget::on_refreshButton_clicked()
{
//WRITE THE DATA BACK INTO DATABASE


}

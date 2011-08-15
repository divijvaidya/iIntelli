#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <QString>
#include <fstream>
#include <vector>


#define PENALTY 4
using namespace std;

class word;
class edge;

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_generateButton_clicked();

    void on_displayButton_clicked();

    void on_crossButton1_clicked();

    void on_crossButton2_clicked();

    void on_crossButton3_clicked();

    void on_crossButton4_clicked();

    void on_crossButton5_clicked();

    void on_crossButton6_clicked();

    void on_crossButton7_clicked();

    void on_crossButton8_clicked();

    void on_crossButton9_clicked();

    void on_crossButton10_clicked();

    void on_printButton_clicked();

    void on_refreshButton_clicked();

private:
    Ui::Widget *ui;
    void loaddata();
    vector<string> vec;
    vector<int> penaltyvec;
    void penalty(int);
    map<string,word> database;

    QString query;

};

class word{
public:
    string key;
    vector<edge> connections;

    word(){
        key="";
    }
};
class edge{
public:
    double weight;
    /*Weight given to the edges as per relations
     * This is defined in macros
     */
    string relation;
    /*Relations are defined as:
     * ST: Same type as determined by pos tagger
     * NN: Noun-Noun relationship as deteremined by stanford parser
     * SNN: Noun in the same sentence as the word
     * SA: Adjective in the same sentence as the word
     * HYN: Hyponym as obtained from wordnet
     * SYN: Synonym as obtained from wordnet
     * DERI: Derivative as obtained from wordnet
     */
    string topic;

    word firstWord;
    word secondWord;
};


#endif // WIDGET_H

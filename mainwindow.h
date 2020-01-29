#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml/QDomElement>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include "pCompany.h"
#include <QVector>
#include <QtXmlPatterns>
#include <algorithm>
#include <QFileDialog>
#include <QTreeWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

void ReadXML(QString file);
void Cancel();
void Return();
void Add();
int Delete();

void AddRoot(QString name,QString count,QString salary);
void AddChild(QTreeWidgetItem *parent,QString name_1, QString name_2,QString name_3,QString function,QString salary);

private slots:
//void on_comboBox_activated(const QString &arg1);

void on_pushButton_5_clicked();
void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;
  QString localPath;
  QVector<Department> pack_dep;
  QVector<Person> pack_members;
  QSet<QString> pack_dep_names;
  int tree_root=0;

};
#endif // MAINWINDOW_H

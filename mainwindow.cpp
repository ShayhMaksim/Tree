#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::ReadXML(QString filename)
{
    QVector<Person> pack;
    Person current_p;
    Department current_dep;
    QFile file(filename);

     int key=0;
     bool keyblock[]={false,false,false,false,false};
     QString Res;
     int c_department=0;
    if (file.open(QIODevice::ReadOnly)){
         QXmlStreamReader xml(&file);
         while(!xml.atEnd()){
             xml.readNext();
             qDebug() <<xml.tokenString()
                    <<xml.name()
                   <<xml.text();
          QXmlStreamAttributes attributes = xml.attributes();


          if ((xml.tokenString()=="StartElement")&&(xml.name().toString()=="department")){
          if (attributes.hasAttribute("name"))
                  Res = attributes.value("name").toString();

            }

          if ((xml.tokenString()=="EndElement")&&(xml.name().toString()=="department"))
            {
              current_dep.name=Res;
              QVector<QString> a={QString::number(pack.length())};
              current_dep.count=std::make_shared<QVector<QString>>(a);

              for(int i=0;i<pack.length();i++){
                  pack[i].department=std::make_shared<Department>(current_dep);
                  pack_members.push_back(pack[i]);
                }
              current_dep.members=std::make_shared<QVector<Person>>(pack);
              current_dep.getSalary();



              if (pack_dep_names.find(Res)!=pack_dep_names.end())
                {
                  for(int i=0;i<pack_dep.length();i++)
                    {
                      if (pack_dep.at(i).name==Res)
                        {
                          for(int j=0;j<current_dep.count->last().toInt();j++){
                              pack_dep.at(i).members->push_back(pack[j]);
                            }
                          pack_dep.at(i).count->push_back(QString::number(pack_dep.at(i).count->last().toFloat()+current_dep.count->last().toFloat()));
                          pack_dep.at(i).salary->push_back(QString::number((pack_dep.at(i).salary->last().toFloat()+current_dep.salary->last().toFloat())/2));
                        }                 
                    }
                }
              QString resultman;
              if (pack_dep_names.find(Res)==pack_dep_names.end())
                {
                  pack_dep.push_back(std::move(current_dep));
                  pack_dep_names.insert(Res);
                }

              c_department++;
              pack.clear();

            }

             if ((xml.tokenString()=="StartElement")&&(xml.name().toString()==keywords[key])){
                 keyblock[key]=true;
               }

             if ((xml.tokenString()=="EndElement")&&(xml.name().toString()==keywords[key])){
                 keyblock[key]=false;
                 if (key!=4) {
                     ++key;
                   }
                 else {
                     key=0;
                     pack.push_back(current_p);
                   }
               }

             if (xml.tokenString()=="Characters") {
                 switch(key){
                   case 0:
                     if (keyblock[0]==true){
                         current_p.employee[0]=xml.text().toString();
                       }
                     break;
                   case 1:
                     if (keyblock[1]==true){
                         current_p.employee[1]=xml.text().toString();
                       }
                     break;
                   case 2:
                     if (keyblock[2]==true){
                         current_p.employee[2]=xml.text().toString();
                       }
                     break;
                   case 3:
                     if (keyblock[3]==true){
                         current_p.function=xml.text().toString();
                       }
                     break;
                   case 4:
                     if (keyblock[4]==true){
                         current_p.salary=xml.text().toString();
                       }
                     break;
                   }
               }
           }
         if (xml.hasError()){
             qDebug()<<"Error:"<<xml.errorString();
           }
         file.close();
      }

}



void MainWindow::on_pushButton_5_clicked()
{
  // ¬ыбор целевого каталога дл€ скачивани€
  auto fileName = QFileDialog::getOpenFileName(this,
                                               tr("Open Image"), 0 , tr("XML files (*.xml)"));
  localPath=fileName;
  ui->label_5->setText("Complete");
  ui->lineEdit->clear();
  ui->lineEdit_2->clear();
  ui->lineEdit_3->clear();
  ui->lineEdit_4->clear();
  ui->lineEdit->setDisabled(true);
  ui->lineEdit_2->setDisabled(true);
  ui->lineEdit_3->setDisabled(true);
  ui->lineEdit_4->setDisabled(true);

}


void MainWindow::on_pushButton_clicked()
{
    if (ui->label_5->text()=="Complete"){
        ReadXML(localPath);

        if (tree_root<pack_dep.length())
          for(int i=0;i<pack_dep.length();i++){
              AddRoot(pack_dep[i].name,pack_dep[i].count->last(),pack_dep[i].salary->last());
              for(int j=0;j<pack_dep[i].count->last().toInt();j++){
                  pack_dep[i].members->at(j).employee;
                  AddChild(ui->treeWidget_2->topLevelItem(i),
                           pack_dep[i].members->at(j).employee[0],
                      pack_dep[i].members->at(j).employee[1],
                      pack_dep[i].members->at(j).employee[2],
                      pack_dep[i].members->at(j).function,
                      pack_dep[i].members->at(j).salary);
                }
            }
      }
}

void MainWindow::AddRoot(QString name,QString count,QString salary)
{

            QTreeWidgetItem *item=new QTreeWidgetItem(ui->treeWidget_2);
            item->setText(0,name);
            item->setText(1,count);
            item->setText(2,salary);
            ui->treeWidget_2->addTopLevelItem(item);
            if (tree_root<pack_dep.length()) tree_root++;


}

void MainWindow::AddChild(QTreeWidgetItem *parent,QString name_1, QString name_2,QString name_3,QString function,QString salary)
{

  QTreeWidgetItem *item=new QTreeWidgetItem(parent);
  item->setText(0,name_1+name_2+name_3);
  item->setText(1,function);
  item->setText(2,salary);
  parent->addChild(item);
}

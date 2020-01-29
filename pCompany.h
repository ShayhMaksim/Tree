#ifndef PCOMPANY_H
#define PCOMPANY_H
#include <QString>
#include <QVector>
#include <memory>

struct Department;

struct Person{
  std::shared_ptr<Department> department;
  QString employee[3];
  QString function;
  QString salary;
};

/*
 * нужны завернуть в векторы
*/

struct Department{
  std::shared_ptr<QVector<Person>> members;
  QString name;
  std::shared_ptr<QVector<QString>> count;
  std::shared_ptr<QVector<QString>> salary;
  void getSalary(){
    float sum=0;
    for(int i=0;i<count->last().toInt();++i){
        sum+=members->at(i).salary.toFloat();
      }
   QVector<QString> a={QString::number(sum/count->last().toFloat())};
    salary=std::make_shared<QVector<QString>>(a);
  }
  void AddPeople(QVector<Person> new_members){
    for(int i=0;i<new_members.length();i++){
        members->append(new_members.at(i));
      }
  }
};




static QString keywords[]={"surname","name","middleName","function","salary"};

#endif // PCOMPANY_H

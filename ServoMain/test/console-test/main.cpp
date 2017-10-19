#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QList>

#include <iostream>
using namespace std;

class parent
{
public:
    parent()
    { cout<<"parent"<<endl; }
    //!
    //! \brief ~parent 基类的析构函数要加virtual    如下demo,才能全部析构，如果没有virtual ，只析构父类
    //! parent * point = new child();
    //! delete point;
    //!
    virtual ~parent()
    { cout<<"~parent"<<endl; }
};

class something
{
public:
   something()
   { cout<<"something"<<endl; }
   ~something()
   { cout<<"~something"<<endl; }
};

class child : public parent
{
public:
   child()
   { cout<<"child"<<endl; }
   ~child()
   { cout<<"~child"<<endl; }
protected:
   something Mysometing;
};



int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  QString str="65535";
  int aa=str.toInt();
  qDebug()<<"toUShort:"<<str.toUShort();
  qDebug()<<"toUInt:"<<str.toUInt();
  qDebug()<<"toInt:"<<str.toInt();
  qDebug()<<"(ushort):"<<(quint16)aa;
  qDebug()<<"(short):"<<(qint16)aa;
  QList<double> vList;
  for(int i=0;i<100;i++)
    vList.append(i);
  foreach (double vtest, vList) {
    vtest+=10;
  }
  foreach (double vtest, vList) {
    qDebug()<<vtest;
  }
  parent * point = new child();
  delete point;

  int i;
  int *p=0; //初始化指针p
  cout<<"i的地址为："<<&i<<endl;
  cout<<"p的值为："<<p<<endl;
  cout<<"p的内存地址为："<<&p<<endl;
  i=3;
  cout<<"i的地址为："<<&i<<endl;
  cout<<"i的值为："<<i<<endl;
  p=&i;
  cout<<"p的值为："<<p<<endl;
  cout<<"p的内存地址为："<<&p<<endl;
  cout<<"p所指向的值为："<<*p<<endl;
  *p=5;
  cout<<"p所指向的变成："<<*p<<endl;
  cout<<"此时i的值变成："<<i<<endl;

  QVector<int>vec;
  for(int i=0;i<10;i++)
    vec.append(i);
  vec.removeAt(2);
  for(int i=0;i<vec.count();i++)
    cout<<i<<"="<<vec.at(i)<<endl;

  cout<<"-------------------------"<<endl;
  quint16 offsetAddr;
  QString num="32768";
  offsetAddr=num.toShort();
  cout<<"32768 toShort() "<<offsetAddr<<endl;
  offsetAddr=num.toInt();
  cout<<"32768 toInt() "<<offsetAddr<<endl;
  offsetAddr=num.toUShort();
  cout<<"32768 toUShort() "<<offsetAddr<<endl;
  num="32769";
  offsetAddr=num.toShort();
  cout<<num.toStdString()<<" toShort() "<<offsetAddr<<endl;
  offsetAddr=num.toInt();
  cout<<num.toStdString()<<" toInt() "<<offsetAddr<<endl;
  offsetAddr=num.toUShort();
  cout<<num.toStdString()<<" toUShort() "<<offsetAddr<<endl;

  num="65530";
  offsetAddr=num.toShort();
  cout<<num.toStdString()<<" toShort() "<<offsetAddr<<endl;
  offsetAddr=num.toInt();
  cout<<num.toStdString()<<" toInt() "<<offsetAddr<<endl;
  offsetAddr=num.toUShort();
  cout<<num.toStdString()<<" toUShort() "<<offsetAddr<<endl;

  qDebug()<<"sizeof uint="<<sizeof(uint);
  qDebug()<<"sizeof int="<<sizeof(int);
  qDebug()<<"sizeof ushort="<<sizeof(ushort);
  qDebug()<<"sizeof short="<<sizeof(short);
  qDebug()<<"sizeof ulong="<<sizeof(ulong);
  qDebug()<<"sizeof long="<<sizeof(long);
  qDebug()<<"sizeof double="<<sizeof(double);
  qDebug()<<"sizeof float="<<sizeof(float);


  return a.exec();
}


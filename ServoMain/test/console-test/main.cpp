#include <QApplication>
#include <QDebug>
#include <QString>
#include <QList>
#include <QMap>
#include <QMapIterator>
#include <QLabel>

#include <iostream>
#include <vector>
#include <list>

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
int testV[10]={100};
void readAddr(int *v)
{
  *v=testV[0];
}

void read(int &value)
{
  readAddr(&value);
}

int array[24][10];
void getArray(int **p)
{
  *p=array[0];
}

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
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

  QMap<QString ,int>map;
  map.insert("hello",1);
  map.insert("hello",2);
  map.insert("world",3);
  QMapIterator<QString ,int> it(map);
  while(it.hasNext())
  {
    it.next();
    qDebug()<<it.key()<<" "<<it.value();
  }

  std::vector<double> stdvector;
  stdvector.push_back(1.2);
  stdvector.push_back(0.5);
  stdvector.push_back(3.14);

  QVector<double> vector = QVector<double>::fromStdVector(stdvector);
//  stdvector.clear();
  for(int i=0;i<vector.size();i++)
    qDebug("%d=%f",i,vector.at(i));

  std::list<std::vector<double>>curves;
  curves.push_back(stdvector);
  stdvector.clear();
  stdvector.push_back(5);
  stdvector.push_back(6);
  stdvector.push_back(7);
  curves.push_back(stdvector);
  stdvector.clear();
  stdvector.push_back(8);
  stdvector.push_back(9);
  stdvector.push_back(10);
  curves.push_back(stdvector);
  stdvector.clear();
  stdvector.push_back(11);
  stdvector.push_back(12);
  stdvector.push_back(13);
  curves.push_back(stdvector);
  qDebug()<<"list size="<<curves.size();
//  std::list<std::vector<double>>::iterator itvec=curves.begin();
//  std::vector<double>::iterator it2;
  std::list<std::vector<double>>::const_iterator itvec=curves.cbegin();
  std::vector<double>::const_iterator it2;
  for(;itvec!=curves.cend();++itvec)
  {

    for(it2=(*itvec).cbegin();it2!=(*itvec).cend();it2++)
    {
      qDebug()<<"send "<<(*it2);
    }
    qDebug()<<"------";
//    qDebug()<<ii<<(*itvec).at(ii);
//    ii++;
  }
  std::list<double>cur;
  cur.push_back(1);
  cur.push_back(2);
  cur.push_back(3);
  std::list<double>::iterator itlist=cur.begin();
  for(;itlist!=cur.end();++itlist)
  {
    qDebug()<<"it="<<(*itlist);
  }

  int mv=0;
  read(mv);
  qDebug("mv=%d",mv);


  int crow=0;
  for(int row=0;row<24;row++)
  {
    crow=row;
    for(int col=0;col<10;col++)
    {
      array[row][col]=crow;
      printf("%4d",crow);
      crow++;
    }
    printf("\r\n");
  }

  printf("\r\n");
//  int (*ptr)[10];
//  ptr=array;
//  for(int row=0;row<24;row++)
//  {
//    for(int col=0;col<10;col++)
//    {
//      printf("%4d",*(*(ptr+row)+col));
//    }
//    printf("\r\n");
//  }
  int *ptr;
  getArray(&ptr);
  for(int row=0;row<24;row++)
  {
    for(int col=0;col<10;col++)
    {
      printf("%4d",*(ptr+row*10+col));
    }
    printf("\r\n");
  }

  QStringList slist;
  slist<<"aa"<<"bb"<<"cc";
  QLabel *label=new QLabel;
  QString strTest;
  for(int i=0;i<slist.count();i++)
  {
    strTest.append(slist.at(i)+"\n");
  }
  label->setText(strTest);
  label->show();
  label=new QLabel;
  label->setText(QString(slist.join('\n')));
  label->show();
  return a.exec();
}


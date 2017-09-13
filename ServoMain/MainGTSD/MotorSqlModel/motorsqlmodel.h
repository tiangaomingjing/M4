#ifndef MOTORSQLMODEL_H
#define MOTORSQLMODEL_H

#include <QObject>
#include <QSqlDatabase>
class SqlTableModel;

class MotorSqlModel : public QObject
{
  Q_OBJECT
public:
  explicit MotorSqlModel(QObject *parent = 0);
  ~MotorSqlModel();

  bool connectDataBase(const QString & fileName);
  bool disconnectDataBase();

  QSqlDatabase* db();

signals:

public slots:

private:
  QSqlDatabase m_db;
};

#endif // MOTORSQLMODEL_H

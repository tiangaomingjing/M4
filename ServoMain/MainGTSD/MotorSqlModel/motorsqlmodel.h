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

  SqlTableModel *companyTableModel() const;

  SqlTableModel *motorTableModel() const;

  SqlTableModel *prmTableModel() const;

  SqlTableModel *totalTableModel() const;

signals:

public slots:

private:
  QSqlDatabase m_db;
  SqlTableModel *m_companyTableModel;
  SqlTableModel *m_motorTableModel;
  SqlTableModel *m_prmTableModel;
  SqlTableModel *m_totalTableModel;
};

#endif // MOTORSQLMODEL_H

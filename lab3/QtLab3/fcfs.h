
#ifndef FCFS_H
#define FCFS_H

#include <QAbstractItemModel>
#include <QObject>
#include <QVector>

#include "processscheduler.h"

class FCFS : public ProcessScheduler {
  Q_OBJECT

 public:
  explicit FCFS(QObject* parent = nullptr);

  virtual void addProcess(ProcessStates& states);
  virtual int currentProcessExecute();

 public slots:
  virtual void tick();
  virtual void start();
};

#endif  // FCFS_H

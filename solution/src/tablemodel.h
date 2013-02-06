 #ifndef TABLEMODEL_H
 #define TABLEMODEL_H

 #include <QAbstractTableModel>
 #include <QPair>
 #include <QList>
 #include <QGraphicsPixmapItem>
 #include "record.h"

 /**
  * "Model-type" class used as "connector" between DataWidget and Record. It's used due to MVC architecture.
  * @see DataWidget
  * @see Record
  *
  *
  * @author Lukas Raska (RAS0053)
  * @author Nokia corporation (Qt official documentation) under BSD licence
  * @version 1.0
  */
 class TableModel : public QAbstractTableModel
 {
     Q_OBJECT

 public:
     TableModel(QObject *parent=0);
     TableModel(QList<Record> dataList, QObject *parent=0);

     int rowCount(const QModelIndex &parent) const;
     int columnCount(const QModelIndex &parent) const;
     QVariant data(const QModelIndex &index, int role) const;
     QVariant headerData(int section, Qt::Orientation orientation, int role) const;
     Qt::ItemFlags flags(const QModelIndex &index) const;
     bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
     bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
     bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
     QList<Record> getList();
     void clear();

 private:
     /** List containing all records */
     QList<Record> dataList;
 };

 #endif

#include "tablemodel.h"
 /**
  * Default Qt constructor due to QAbstractTableModel inheritance.
  * @see QAbstractTableModel
  *
  * @param parent Parent of this object
  */
 TableModel::TableModel(QObject *parent)
     : QAbstractTableModel(parent)
 {
 }

 /**
  * Custom constructor for assigning list of all records
  *
  * @see QAbstractTableModel
  *
  * @param list List of records
  * @param parent Parent of this object
  */
 TableModel::TableModel(QList<Record> list, QObject *parent)
     : QAbstractTableModel(parent)
 {
     dataList=list;
 }

 /**
  * Method for getting number of rows.
  *
  * @param parent Parent of this object
  * @return number of rows
  */
 int TableModel::rowCount(const QModelIndex &parent) const
 {
     Q_UNUSED(parent);
     return dataList.size();
 }

 /**
  * Method for getting column count
  *
  * @param parent Parent of this object
  * @return fixed number of columns
  */
 int TableModel::columnCount(const QModelIndex &parent) const
 {
     Q_UNUSED(parent);
     return 7;
 }

 /**
  * Method for handling every data obtaining. It's abstract-like due to MVC.
  * 
  * @param index object describing position in table (column/row)
  * @param role Role describing data using (decoration, data, item...)
  * @return object we want to display
  */
 QVariant TableModel::data(const QModelIndex &index, int role) const
 {
     if(role == Qt::DecorationRole && index.column() == 0){ // for displaying icon
	QPixmap icon;
	icon.load("pencil.png");
	return icon;	
     }
     if (!index.isValid())
         return QVariant();

     if (index.row() >= dataList.size() || index.row() < 0)
         return QVariant();

     if (role == Qt::DisplayRole) { // for displaying data
         Record record = dataList.at(index.row());

	switch (index.column()){
	  case 1:
		return record.name;
	  case 2:
		return record.profession;
	  case 3:
		return record.address;
	  case 4:
		return record.mobile;
	  case 5:
		return record.email;
	  case 6:
		return record.website;
	}
     }
     return QVariant(); // instead of 0 which is bad
 }

 /**
  * Method for handling header data. It's not directly called due to MVC architecture.
  *
  * @param section column
  * @param orientation orientation of cell
  * @param role QRole (display, decoration etc.)
  * @return object we want to display
  */
 QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
     if (role != Qt::DisplayRole) // since we want to display data only
         return QVariant();

     if (orientation == Qt::Horizontal) { // and we want only horizontal header
         switch (section) {
	     case 0:
		return tr("^");
             case 1:
                return tr("Name");
             case 2:
                return tr("Profession");
	     case 3:
		return tr("Address");
	     case 4:
		return tr("Mobile");
	     case 5:
		return tr("Email");
	     case 6:
		return tr("Website");
             default:
                 return QVariant();
         }
     }
     return QVariant();
 }

 /**
  * Method used for inserting row into table. It only inserts empty row
  * @see DataWidget::addEntry()
  *
  * @param position position of inserted row, default 0 -> adding to start
  * @param rows number of inserted rows
  * @param index index of row
  * @return boolean value if inserting was successful
  */
 bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginInsertRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; row++) {
	 Record record = Record(" ", " ", " "," ", " ", " "); //for creating desired objects
         dataList.insert(position, record); //and insert it into dataList
     }

     endInsertRows();
     return true;
 }

 /**
  * Method used for removing selected row.
  * @see DataWidget::removeEntry();
  *
  * @param position position of row in table
  * @param rows number of deleted rows
  * @param index index of row
  * @return boolean value if removing was successful
  */
 bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
 {
     if(rows<1){
	return true;
     }
     Q_UNUSED(index);
     beginRemoveRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; ++row) {
         dataList.removeAt(position);
     }

     endRemoveRows();
     return true;
 }

 /**
  * Abstract-like method used for handling every data change.
  * @see DataWidget
  *
  * @param index object describing record status (row/column)
  * @param value value to-be-set
  * @param role role of QVariant data (data / decoration / etc.)
  * @return boolean value if change was successful
  */
 bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
     /* icon */
     if(role == Qt::DecorationRole){
	return true;
     }
     if (index.isValid() && role == Qt::EditRole) {
         int row = index.row();

	Record record = dataList.value(row);

	switch(index.column()){	 
	   case 1:
		record.name=value.toString();
	   break;
	   case 2:
		record.profession=value.toString();
	   break;
	   case 3:
		record.address=value.toString();
	   break;
	   case 4:
		record.mobile=value.toString();
	   break;
	   case 5:
		record.email=value.toString();
	   break;
	   case 6:
		record.website=value.toString();
	   break;
	   default:
		//return false;
	   break;
	}

         dataList.replace(row, record);
         emit(dataChanged(index, index)); //emit change -> MVC

         return true;
     }

     return false;
 }


 /**
  * Method for getting item table status.
  *
  * @author Nokia corporation (Qt official documentation) under BSD licence
  * @param index index describing table data (row/column/is valid...)
  * @return Qt::ItemFlags
  */
 Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return Qt::ItemIsEnabled;

     return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
 }

 /**
  * Method for getting list of records
  * 
  * @return List of Records
  */
 QList<Record> TableModel::getList()
 {
     return dataList;
 }
 
 /**
  * Method for clearing whole table, used when "New project" or "Open file" is invoked.
  * @see DataWidget::clear();
  */
 void TableModel::clear(){
   if(dataList.size()>0){
     removeRows(0, dataList.size());
   }
 }

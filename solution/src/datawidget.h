 #ifndef DATAWIDGET_H
 #define DATAWIDGET_H

 #include <QTabWidget>
 #include <QItemSelection>
 #include "tablemodel.h"
 #include "choicedialog.h"

 class QSortFilterProxyModel;
 class QItemSelectionModel;

 /**
  * <p>
  * Class for complete management of data. It creates signal that is handled in MainWindow
  * @see MainWindow::updateActions();
  *
  * It also handles every file manipulation -> reading from file, saving to file, exporting and importing
  *
  * @author Lukas Raska (RAS0053)
  * @author Nokia corporation (Qt official documentation) under BSD licence
  * @version 1.0
  */ 
 class DataWidget : public QTabWidget
 {
     Q_OBJECT

 public:
     DataWidget(QWidget *parent=0);
     bool readFromFile(QString fileName);
     bool writeToFile(QString fileName);
     void importFile(QString fileName);
     void exportFile(QString fileName);
     void clear();

 public slots:
     void addEntry();
     void addEntry(QString name, QString profession, QString address, QString mobile, QString email, QString website);
     void editEntry();
     void doubleClick();
     void removeEntry();

 signals:
     void selectionChanged (const QItemSelection &selected);

 private:
     void setupTabs();

     void parseXMLFile(QString fileName);
     void readFromCSV(QString fileName);
     void saveCSV(QString fileName);
     void saveXML(QString fileName);
     void saveHTML(QString fileName, ChoiceDialog * cDialog);
     void saveSQL(QString fileName, ChoiceDialog * cDialog);
     /** Model used in MVC */
     TableModel *table;
     /** Proxy for filtering specified data */
     QSortFilterProxyModel *proxyModel;
 };

 #endif

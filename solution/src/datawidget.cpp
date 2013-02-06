 #include <QtGui>
 #include <iostream>
 #include "datawidget.h"
 #include "adddialog.h"

 /** 
  * Implicit constructor for DataWidget class handled by Qt.
  * It creates table for input data and call method for creating tabs.
  * 
  * @see setupTabs();
  * @param parent parent of the widget, not used - handled by Qt itself
  */
 DataWidget::DataWidget(QWidget *parent)
     : QTabWidget(parent)
 {
     table = new TableModel(this);
     setupTabs();
 }

 /**
  * Method overloading default addEntry() method. It's only used with add dialog.
  *
  */
 void DataWidget::addEntry()
 {
     AddDialog aDialog;

     if (aDialog.exec()) {
         QString name = aDialog.nameText->text();
	 QString profession = aDialog.professionText->text();
         QString address = aDialog.addressText->toPlainText();
	 QString mobile = aDialog.mobileText->text();
	 QString email = aDialog.emailText->text();
	 QString website = aDialog.websiteText->text();

	/* pass it to default method */
        addEntry(name, profession, address, mobile, email, website);
     }
 }

/**
  * Method for adding record to central list and data widget.
  * It checks for duplicit record and throws QMessageBox if it already exists.
  *
  * @param name
  * @param profession
  * @param address
  * @param mobile
  * @param email
  * @param website
  */
 void DataWidget::addEntry(QString name, QString profession, QString address, QString mobile, QString email, QString website)
 {

     QRegExp emailRegexp("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",Qt::CaseInsensitive);

     if(name.isEmpty()){
	QMessageBox::critical(this, tr("Invalid name"), tr("Name cannot be empty!"));
	return;
     }

     if(!email.contains(emailRegexp)){
	QMessageBox::warning(this, tr("Invalid email address"),tr("Email address is not valid!"));
	return;
     }

     QList<Record> list = table->getList();
     Record record = Record(name, profession, address, mobile, email, website);

     /* check for duplicite record */
     if (!list.contains(record)) {
         table->insertRows(0, 1, QModelIndex());

	/* icon */

         QPixmap icon(""); // only as "simulation"
         QModelIndex index = table->index(0, 0, QModelIndex());
         table->setData(index, icon, Qt::DecorationRole);

	/* inserting data */
         index = table->index(0, 1, QModelIndex());
         table->setData(index, name, Qt::EditRole);

	 index = table->index(0, 2, QModelIndex());
	 table->setData(index, profession, Qt::EditRole);

         index = table->index(0, 3, QModelIndex());
         table->setData(index, address, Qt::EditRole);

	 index = table->index(0, 4, QModelIndex());
	 table->setData(index, mobile, Qt::EditRole);

	 index = table->index(0, 5, QModelIndex());
	 table->setData(index, email, Qt::EditRole);

	 index = table->index(0, 6, QModelIndex());
	 table->setData(index, website, Qt::EditRole);

     } else {
	/* and show window */
         QMessageBox::information(this, tr("Duplicate Record"),tr("Record with the same data already exists!"));
     }
 }

/**
  * Method for adding record to central list and data widget.
  * It checks for duplicit record and throws QMessageBox if it already exists.
  *
  * @see AddDialog
  * @see QTableView
  * 
  */
 void DataWidget::editEntry()
 {
     QTableView *temp = static_cast<QTableView*>(currentWidget()); // because we know class of current widget
     QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model()); // same as ^
     QItemSelectionModel *selectionModel = temp->selectionModel();

     QModelIndexList indexes = selectionModel->selectedRows();
     QModelIndex index, i;
     QString name;
     QString profession;
     QString address;
     QString mobile;
     QString email;
     QString website;

     int row = -1;

     index=indexes.at(0); //be sure to edit only one row
	row = proxy->mapToSource(index).row();
	
	/* get current data from columns */
        i = table->index(row, 1, QModelIndex());
        name = table->data(i, Qt::DisplayRole).toString();

        i = table->index(row, 2, QModelIndex());
        profession = table->data(i, Qt::DisplayRole).toString();

        i = table->index(row, 3, QModelIndex());
        address = table->data(i, Qt::DisplayRole).toString();

        i = table->index(row, 4, QModelIndex());
        mobile = table->data(i, Qt::DisplayRole).toString();

        i = table->index(row, 5, QModelIndex());
        email = table->data(i, Qt::DisplayRole).toString();

        i = table->index(row, 6, QModelIndex());
        website = table->data(i, Qt:: DisplayRole).toString(); 


     /* raise dialog window */
     AddDialog aDialog;
     aDialog.setWindowTitle(tr("Edit business card"));

     aDialog.nameText->setText(name);
     aDialog.professionText->setText(profession);
     aDialog.addressText->setText(address);
     aDialog.mobileText->setText(mobile);
     aDialog.emailText->setText(email);
     aDialog.websiteText->setText(website);

     /* and if its ok, set modified data */
     if (aDialog.exec()) {
	     QRegExp emailRegexp("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",Qt::CaseInsensitive);

	     if(aDialog.nameText->text().isEmpty()){
		QMessageBox::critical(this, tr("Invalid name"), tr("Name cannot be empty!"));
		return;
	     }

	     if(!aDialog.emailText->text().contains(emailRegexp)){
		QMessageBox::warning(this, tr("Invalid email address"),tr("Email address is not valid!"));
		return;
	     }


	/* SET DATA */
	  i = table->index(row, 1, QModelIndex());
          table->setData(i, aDialog.nameText->text(), Qt::EditRole);

          i = table->index(row, 2, QModelIndex());
          table->setData(i, aDialog.professionText->text(), Qt::EditRole);

          i = table->index(row, 3, QModelIndex());
          table->setData(i, aDialog.addressText->toPlainText(), Qt::EditRole);

          i = table->index(row, 4, QModelIndex());
          table->setData(i, aDialog.mobileText->text(), Qt::EditRole);

          i = table->index(row, 5, QModelIndex());
          table->setData(i, aDialog.emailText->text(), Qt::EditRole);

          i = table->index(row, 6, QModelIndex());
          table->setData(i, aDialog.websiteText->text(), Qt::EditRole);
     }
 }

/**
  * Method for handling double click event.
  * 
  */
 void DataWidget::doubleClick()
 {
    editEntry();
    // method for another possible feature
 }

 /**
  * Method for deleting selected row in central list and table view
  *
  * @see QTableView
  */
 void DataWidget::removeEntry()
 {
     QTableView *temp = static_cast<QTableView*>(currentWidget());
     QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
     QItemSelectionModel *selectionModel = temp->selectionModel();

     QModelIndexList indexes = selectionModel->selectedRows();
     QModelIndex index = indexes.at(0); //only one row

         int row = proxy->mapToSource(index).row();
         table->removeRows(row, 1, QModelIndex());
 }

 /**
  * Method for creating special tabs of tableviews, every tab has specific part of records -> filtering. It also creates tab for special starting characters (different chars than a-z) and table with every record without filtering.
  *
  * @see QTableView
  * @see QSortFilterProxyModel
  */
 void DataWidget::setupTabs()
 {
     QStringList groups;

     /* add every tab to qstringlist */
     groups << "A";
     groups << "B";
     groups << "C";
     groups << "D";
     groups << "E";
     groups << "F";
     groups << "G";
     groups << "H";
     groups << "I";
     groups << "J";
     groups << "K";
     groups << "L";
     groups << "M";
     groups << "N";
     groups << "O";
     groups << "P";
     groups << "Q";
     groups << "R";
     groups << "S";
     groups << "T";
     groups << "U";
     groups << "V";
     groups << "W";
     groups << "X";
     groups << "Y";
     groups << "Z";

     /* and set up the tabs */
     for (int i = 0; i < groups.size(); ++i) {
         QString str = groups.at(i);

	 /* create filter */
         proxyModel = new QSortFilterProxyModel(this);
         proxyModel->setSourceModel(table);
         proxyModel->setDynamicSortFilter(true);

	/* create table view */
         QTableView *tableView = new QTableView;
         tableView->setModel(proxyModel);
	 tableView->setColumnWidth(0,30);
	 tableView->setColumnWidth(1,200);
	 tableView->setColumnWidth(2,150);
	 tableView->setColumnWidth(3,400);
	 tableView->setColumnWidth(4,150);
	 tableView->setColumnWidth(5,150);
         tableView->setSortingEnabled(true);
         tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
         tableView->horizontalHeader()->setStretchLastSection(true);
         tableView->verticalHeader()->hide();
         tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
         tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	/* regexp for first letter */
         QString newStr = QString("^[%1].*").arg(str);

         proxyModel->setFilterRegExp(QRegExp(newStr, Qt::CaseInsensitive)); // case insensitive filtering
         proxyModel->setFilterKeyColumn(1);
         proxyModel->sort(1, Qt::AscendingOrder);


         connect(tableView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this, SIGNAL(selectionChanged(QItemSelection)));

	 /* double click bind */
	 connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClick()));

         addTab(tableView, str);
     }

	// Others tab -> for non-english letters
        proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(table);
        proxyModel->setDynamicSortFilter(true);

        QTableView *tableView = new QTableView;
        tableView->setModel(proxyModel);
        tableView->setSortingEnabled(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	 tableView->setColumnWidth(0,30);
	 tableView->setColumnWidth(1,200);
	 tableView->setColumnWidth(2,150);
	 tableView->setColumnWidth(3,400);
	 tableView->setColumnWidth(4,150);
	 tableView->setColumnWidth(5,150);
	
	// every character except a-zA-Z
        QString newStr = QString("^[^a-zA-Z].*");

        proxyModel->setFilterRegExp(QRegExp(newStr, Qt::CaseInsensitive));
        proxyModel->setFilterKeyColumn(1);
        proxyModel->sort(1, Qt::AscendingOrder);

        connect(tableView->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
             this, SIGNAL(selectionChanged(QItemSelection)));

        /* double click bind */
        connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClick()));

        addTab(tableView, "Others");


	// ALL tabs
	proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(table);

        tableView = new QTableView;
        tableView->setModel(proxyModel);
        tableView->setSortingEnabled(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

	 tableView->setColumnWidth(0,30);
	 tableView->setColumnWidth(1,200);
	 tableView->setColumnWidth(2,150);
	 tableView->setColumnWidth(3,400);
	 tableView->setColumnWidth(4,150);
	 tableView->setColumnWidth(5,150);

	connect(tableView->selectionModel(),SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SIGNAL(selectionChanged(QItemSelection)));

        /* double click bind */
        connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClick()));
	addTab(tableView, "All");
 }



 /**
  * Method for reading default file type, throws dialog window if selected file doesnt contain any business card / IO error.
  *
  * Return value is used for title changing
  *
  * @param fileName name of binary file
  * @return true if read was successfull, false if not
  *
  * @see MainWindow::openFile();
  * @see operator<<(QDataStream &out, const Record &r);  
  */
 bool DataWidget::readFromFile(QString fileName)
 {
     QFile file(fileName);

     if (!file.open(QIODevice::ReadOnly)) {
         QMessageBox::warning(this, tr("Unable to open file"),
             file.errorString());
         return false;
     }

     QList<Record> pairs = table->getList();
     QDataStream in(&file);

     /* if its not binary file */
     try{
        in >> pairs;
     }catch(std::exception &e){
         QMessageBox::critical(this, tr("Invalid file!"),
             tr("This file is invalid! Try using import instead."));
	return false;
     }

     if (pairs.isEmpty()) {
         QMessageBox::information(this, tr("Empty file"),
             tr("Error: Selected file does not contain any business card."));
     } else {
	clear();
         for (int i=0; i<pairs.size(); ++i) {
             Record r = pairs.at(i);
             addEntry(r.name, r.profession, r.address, r.mobile, r.email, r.website);
         }
     }
     return true;
 }

 /**
  * Method for deleting all existing records -> emptying table. 
  * It is used for simulating "new project" feature.
  */
 void DataWidget::clear(){
   table->clear();
 }


 /**
  * Method for writing data to default file type, throws dialog window if IO error occurs
  *
  * Return value is used for title changing
  *
  * @param fileName name of binary file
  * @return true if writting was successfull, false if not
  *
  * @see void MainWindow::saveFile();
  * @see operator<<(QDataStream &out, const Record &r);
  */
 bool DataWidget::writeToFile(QString fileName)
 {
     QFile file(fileName);

     if (!file.open(QFile::WriteOnly)) {
         QMessageBox::critical(this, tr("Unable to save file"), file.errorString());
         return false;
     }

     QList<Record> list = table->getList();
     QDataStream out(&file);
     out << list;
     return true;
 }



 /**
  * Main export method called when export is initialized.
  * It calls special methods by file extensions. If there is no extension, CSV by default.
  *
  * Current export file formats are XML, HTML, SQL and CSV
  * @see saveXML();
  * @see saveHTML();
  * @see saveSQL();
  * @see saveCSV();
  *
  * @param fileName name of file selected for exporting
  */
 void DataWidget::exportFile(QString fileName){
    if(fileName.endsWith(".xml")){
	saveXML(fileName);
    }else if(fileName.endsWith(".html")){
      ChoiceDialog cDialog;
       /* disable inputs that are only for sql */
      cDialog.exportCreateTable->setEnabled(false);
      cDialog.exportCreateTableIfNotExists->setEnabled(false);
      cDialog.exportRecords->setEnabled(false);
      cDialog.autoIncrementFrom->setEnabled(false);
      if(cDialog.exec()){
	saveHTML(fileName, &cDialog);
      }
    }
    else if(fileName.endsWith(".sql")){
      ChoiceDialog cDialog;
      if(cDialog.exec()){
	saveSQL(fileName, &cDialog);
      }
    }else{
      saveCSV(fileName);
    }
 }


 /**
  * Main import method. It calls special methods by file extension.
  *
  * Current import file types are XML and CSV (default)
  *
  * @param fileName name of importing file
  */
 void DataWidget::importFile(QString fileName){
    if(fileName.endsWith(".xml")){
      parseXMLFile(fileName);
    }else{
      readFromCSV(fileName);
    }
 }


 /**
  * Method for exporting selected data to SQL (MySQL) format. Settings are taken from ChoiceDialog raised in "parent method".
  * If exportCreateTableIfNotExists is not checked, it adds "DROP TABLE" parameter.
  * 
  * @see exportFile();
  *
  * Throws message box if some error occurs (IO error, invalid options)
  * 
  * @param fileName name of saved file
  * @param cDialog pointer to raised ChoiceDialog to obtain selected options.
  *
  */
 void DataWidget::saveSQL(QString fileName, ChoiceDialog * cDialog){
     QFile file(fileName);
     int ai=0;
     if (!file.open(QFile::WriteOnly)) {
         QMessageBox::warning(this, tr("Unable to save file"), file.errorString());
         return;
     }
    /* check for valid input data */
    if((*cDialog).tableName->text().isEmpty()){
	QMessageBox::critical(this, tr("Table name cannot be empty!"), QString("Table name cannot be empty!"));
	return;
    }
    QTextStream out(&file);

    /* and create sql statements */
    ai=(*cDialog).autoIncrementFrom->text().toInt();
    if((*cDialog).exportCreateTable->isChecked()){
      if(!(*cDialog).exportCreateTableIfNotExists->isChecked()){
      	out << "DROP TABLE IF EXISTS `" << (*cDialog).tableName->text() << "`;" << '\n';
      }
      out << "CREATE TABLE IF NOT EXISTS `"<< (*cDialog).tableName->text() <<"` (" << '\n';
      out << "`id` int(11) NOT NULL AUTO_INCREMENT," << '\n';
      out << "`name` varchar(255) COLLATE utf16_bin NOT NULL," << '\n';
      out << "`profession` varchar(255) COLLATE utf16_bin NOT NULL," << '\n';
      out << "`address` text COLLATE utf16_bin NOT NULL," << '\n';
      out << "`mobile` varchar(16) COLLATE utf16_bin NOT NULL," << '\n';
      out << "`email` varchar(255) COLLATE utf16_bin NOT NULL," << '\n';
      out << "`website` varchar(255) COLLATE utf16_bin NOT NULL," << '\n';
      out << "PRIMARY KEY (`id`)" << '\n';
      out << ") ENGINE=InnoDB  DEFAULT CHARSET=utf16 COLLATE=utf16_bin AUTO_INCREMENT="<< ai << " ;" << '\n';
    }
	
  /* export data if user selects it */
  if((*cDialog).exportRecords->isChecked()){
    QString filter=(*cDialog).exportRecordsWithString->text();
    foreach(Record r, table->getList()){
     if(r.name.contains(filter,Qt::CaseInsensitive)||
	r.profession.contains(filter,Qt::CaseInsensitive)||
	r.address.contains(filter,Qt::CaseInsensitive)||
	r.mobile.contains(filter,Qt::CaseInsensitive)||
	r.email.contains(filter,Qt::CaseInsensitive)||
	r.website.contains(filter,Qt::CaseInsensitive)||
	filter.isEmpty()){
	  out << "INSERT INTO `"<< (*cDialog).tableName->text() <<"` (`id`, `name`, `profession`, `address`, `mobile`, `email`, `website`) VALUES (NULL, ";
	  out << "'" << r.name.replace("'","`").replace(";",",").replace("--","-").replace("\r","").replace("\n",",") << "', ";
	  out << "'" << r.profession.replace("'","`").replace(";",",").replace("--","-").replace("\r","").replace("\n",",") << "', ";
	  out << "'" << r.address.replace("'","`").replace(";",",").replace("--","-").replace("\r","").replace("\n",",") << "', ";
	  out << "'" << r.mobile.replace("'","`").replace(";",",").replace("--","-").replace("\r","").replace("\n",",") << "', ";
	  out << "'" << r.email.replace("'","`").replace(";",",").replace("--","-").replace("\r","").replace("\n",",") << "', ";
	  out << "'" << r.website.replace("'","`").replace(";",",").replace("--","-").replace("\r","").replace("\n",",") << "'";
	  out << ");" << '\n';
      }
    }
  }
  /* and raise information message box */
    QMessageBox::information(this, tr("Success"), QString("File has been successfully saved"));
 }


 /**
  * Method for saving CSV file. It replaces unwanted data with valid data.
  *
  * Throws message window if IO error occurs.
  *
  * @param fileName name of saved file
  */
 void DataWidget::saveCSV(QString fileName){
     QString separator(",");
     QString closing("");
     QFile file(fileName);

     if (!file.open(QFile::WriteOnly)) {
         QMessageBox::warning(this, tr("Unable to save file"), file.errorString());
         return;
     }

    QTextStream out(&file);
    foreach(Record r, table->getList()){
	out << closing << r.name.replace(",",";").replace("\"","\"\"").replace("\n",";").replace("\r","") << closing << separator;
        out << closing << r.profession.replace(",",";").replace("\"","\"\"").replace("\n",";").replace("\r","") << closing << separator;
	out << closing << r.address.replace(",",";").replace("\"","\"\"").replace("\n",";").replace("\r","") << closing << separator;
	out << closing << r.mobile.replace(",",";").replace("\"","\"\"").replace("\n",";").replace("\r","") << closing << separator;
	out << closing << r.email.replace(",",";").replace("\"","\"\"").replace("\n",";").replace("\r","") << closing << separator;
	out << closing << r.website.replace(",",";").replace("\"","\"\"").replace("\n",";").replace("\r","") << closing << '\n';
    }
    QMessageBox::information(this, tr("Success"), QString("File has been successfully saved"));
 }


 /**
  * Method for HTML export. It uses two params from ChoiceDialog raised in "parent method"
  * @see exportFile();
  *
  * Throws message window if some error occurs (IO error, invalid dialog data)
  *
  * @param fileName name of saved file
  * @param cDialog pointer to previously raised cDialog window
  */
 void DataWidget::saveHTML(QString fileName, ChoiceDialog * cDialog){
     int id=1;
     QFile file(fileName);
     QString filter = (*cDialog).exportRecordsWithString->text();

     if((*cDialog).tableName->text().isEmpty()){
	QMessageBox::critical(this, tr("Table name cannot be empty!"), QString("Table name cannot be empty!"));
	return;
     }

     if (!file.open(QFile::WriteOnly)) {
         QMessageBox::warning(this, tr("Unable to save file"), file.errorString());
         return;
     }

    QTextStream out(&file);

    /* header */
	out << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">" << '\n';
	out << "<html xmlns=\"http://www.w3.org/1999/xhtml\">" << '\n';
	out << "<head>" << '\n';
	out << "<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">" << '\n';
	out << "<title>Business cards</title>" << '\n';
	out << "<style type=\"text/css\">#wrap{width:800px;margin:10px auto;text-align:center;}table{width:800px;}.second{background:lightblue;}#footer{margin:10px 0;font-size:11px;}</style>" << '\n';
	out << "</head>" << '\n';
	out << "<body>" << '\n';
	out << "<div id=\"wrap\">" << '\n';

    /* data */
	out << "<h1>" << (*cDialog).tableName->text() << "</h1>" << '\n';
	// table first
	out << "\t<table>" << '\n';
	out << "\t\t<tr><th>ID</th><th>Name</th><th>Profession</th><th>Address</th><th>Mobile</th><th>Email</th><th>Website</th></tr>" << '\n';

    foreach(Record r, table->getList()){
	if(r.name.contains(filter,Qt::CaseInsensitive)||
	r.profession.contains(filter,Qt::CaseInsensitive)||
	r.address.contains(filter,Qt::CaseInsensitive)||
	r.mobile.contains(filter,Qt::CaseInsensitive)||
	r.email.contains(filter,Qt::CaseInsensitive)||
	r.website.contains(filter,Qt::CaseInsensitive)||
	filter.isEmpty()){

   	  out << "\t\t<tr" << ((id%2==0)? " class=\"second\"":"") << ">" << '\n';
	  out << "\t\t\t<th>" << id << "</td>\n";
	  out << "\t\t\t<td>" << r.name << "</td>\n";
	  out << "\t\t\t<td>" << r.profession << "</td>\n";
	  out << "\t\t\t<td>" << r.address << "</td>\n";
	  out << "\t\t\t<td>" << r.mobile << "</td>\n";
	  out << "\t\t\t<td>" << r.email << "</td>\n";
	  out << "\t\t\t<td>" << r.website << "</td>\n";
	  out << "\t\t</tr>\n";

	  id++;
	}
    }
	out << "\t</table>" << '\n';
    /* footer */
	out << "<div id=\"footer\">&copy; Lukas Raska (RAS0053) 2012, Semestral project for Fundamentals of programming @ vsb.cz</div>" << '\n';
	out << "</div>" << '\n';
	out << "</body>" << '\n';
	out << "</html>" << '\n';

    QMessageBox::information(this, tr("Success"), QString("File has been successfully saved"));
 }


 /**
  * Method for exporting data to XML file. It has given structure, so it can be used for importing as well.
  * 
  * Throws message box if IO error occurs.
  *
  * @param fileName name of saved file
  */
 void DataWidget::saveXML(QString fileName){
     int id=1;
     QFile file(fileName);

     if (!file.open(QFile::WriteOnly)) {
         QMessageBox::warning(this, tr("Unable to save file"), file.errorString());
         return;
     }

    QTextStream out(&file);

    /* header */
	out << "<?xml version=\"1.0\"?>" << '\n';
	out << "<records>" << '\n';

    /* data */

    foreach(Record r, table->getList()){
	out << "\t<card id=\"bc" << id << "\">" << '\n';
	out << "\t\t<name>" << r.name << "</name>\n";
	out << "\t\t<profession>" << r.profession << "</profession>\n";
	out << "\t\t<address>" << r.address << "</address>\n";
	out << "\t\t<mobile>" << r.mobile << "</mobile>\n";
	out << "\t\t<email>" << r.email << "</email>\n";
	out << "\t\t<website>" << r.website << "</website>\n";
	out << "\t</card>" << '\n';

	id++;
    }

    /* footer */
	out << "</records>" << '\n';

    QMessageBox::information(this, tr("Success"), QString("File has been successfully saved"));
 }


 /**
  * Method for importing data from CSV file. Separator is comma (,). If selected file is empty (eg. doesnt contain any valid records), it throws information window.
  *
  * Throws message box if IO error occurs
  *
  * @param fileName name of saved file
  */
 void DataWidget::readFromCSV(QString fileName){
    QString separator(",");
    QFile file(fileName);
    Record r;
    QString line;

    QList<Record> records;
    if(!file.open(QFile::ReadOnly)){
	QMessageBox::warning(this, tr("Unable to open file"), file.errorString());
	return;
    }

    QTextStream in(&file);

    /* read whole file */
    do{
     line=in.readLine();

     QStringList list = line.split(separator);

     /* line has to contain exactly 6 cells to be valid */
     if(list.size() != 6){
	continue;
     }else{
        r=Record(QString(list.at(0)).replace(";",","), QString(list.at(1)).replace(";",","),
		 QString(list.at(2)).replace(";",","), QString(list.at(3)).replace(";",","),
		 QString(list.at(4)).replace(";",","), QString(list.at(5)).replace(";",","));
	records.append(r);
     }
    }while(!line.isNull());

     if (records.isEmpty()) {
         QMessageBox::information(this, tr("Empty file"),
             tr("Error: Selected file does not contain any business card."));
     } else {
         for (int i=0; i<records.size(); ++i) {
             Record r = records.at(i);
             addEntry(r.name, r.profession, r.address, r.mobile, r.email, r.website);
         }
	QMessageBox::information(this, tr("Success"), QString("File has been successfully imported"));
     }

   return;
 }

 /**
  * Method for importing records from XML ficlee.
  * @see QXmlStreamReader
  *
  * Throws message box if some error occurs (IO error, invalid data format, empty file)
  */
 void DataWidget::parseXMLFile(QString fileName){
    QFile file(fileName);
    Record r;
    QString name;
    QString profession;
    QString address;
    QString mobile;
    QString email;
    QString website;

    QList<Record> records;
    if(!file.open(QFile::ReadOnly)){
	QMessageBox::warning(this, tr("Unable to open file"), file.errorString());
	return;
    }

    QXmlStreamReader xml(&file); // open stream
  
    // start reading file from start, ends if error occurs
    while(!xml.atEnd() && !xml.hasError()) {
      QXmlStreamReader::TokenType token = xml.readNext(); // obtain current token
      if(token == QXmlStreamReader::StartDocument) { // if it is header token, just read next token
        continue;
      }
      if(token == QXmlStreamReader::StartElement) { // parent element
     	if(xml.name() == "records") { // if it is tag "records", just continue, we need child elements
     	    continue;
      	}
      	if(xml.name() == "card") { // handle correct data
	    xml.readNext();

	    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "card")) { // and browse through all child elements
	        if(xml.tokenType() == QXmlStreamReader::StartElement) { 
	            if(xml.name() == "name") {
		        xml.readNext();
			name = xml.text().toString();
		    }

	            if(xml.name() == "profession") {
		        xml.readNext();
			profession = xml.text().toString();
		    }

	            if(xml.name() == "address") {
		        xml.readNext();
			address = xml.text().toString();
		    }

	            if(xml.name() == "mobile") {
		        xml.readNext();
			mobile = xml.text().toString();
		    }

	            if(xml.name() == "email") {
		        xml.readNext();
			email = xml.text().toString();
		    }

	            if(xml.name() == "website") {
		        xml.readNext();
		        website = xml.text().toString();
		    }
		}
		xml.readNext();
	    }
        }else{
	  xml.raiseError(); // since it contains invalid data, raise error
	}

	if(!name.isEmpty()){ // and add business card only if name is not empty
		r = Record(name,profession,address,mobile,email,website);
		records.append(r);
	}
        xml.readNext();
      } 
    }

    if(xml.hasError()){
        QMessageBox::warning(this, tr("Wrong format"), tr("Error: XML file is not in valid format!"));	
	return;
    }

    if (records.isEmpty()) {
        QMessageBox::information(this, tr("Empty file"),tr("Error: Selected file does not contain any business card."));
    } else {
	// insert data from buffer
         for (int i=0; i<records.size(); ++i) {
             Record r = records.at(i);
             addEntry(r.name, r.profession, r.address, r.mobile, r.email, r.website);
         }
	QMessageBox::information(this, tr("Success"), QString("File has been successfully imported"));
    }

   return;
 }

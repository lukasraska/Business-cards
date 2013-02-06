 #include <QtGui>
 #include "mainwindow.h"


 /**
  * Constructor of MainWindow class. It creates DataWidget (widget for data show) and sets it as main widget.
  * It also creates menu, binds shortcuts and creates initial symptom for unsaved project.
  */
 MainWindow::MainWindow()
 {
     dataWidget = new DataWidget;
     setCentralWidget(dataWidget);
     createMenus();
     bindShortcuts();
     setGeometry(20, 50, 800, 500); // initial window size

     setAcceptDrops(true); // drag&drop implementation
     setSaved(false,fileName);
     saved=true; // initial check
 }
 
 /**
  * Method for setting title of window. Used on project change (edit, file change, etc.)
  * 
  * @param title Title string
  */
 void MainWindow::setTitle(QString title){
   setWindowTitle(title);
 }
 
 /**
  * Method for binding desired shortcuts. It creates set shortcuts from given key sequence and binds/connects them to specific signal (when the key sequence is activated).
  * It sets default action for the shortcut.
  *
  * Most shortcuts are handled in this class.
  * 
  * Data-specific shortcuts are handled in Data widget
  * @see DataWidget
  * @see void setNotSaved(); 
  */
 void MainWindow::bindShortcuts(){
     saveShortcut = new QShortcut(QKeySequence(tr("Ctrl+S")), this);
     connect(saveShortcut, SIGNAL(activated()), this, SLOT(saveFile()));

     openShortcut = new QShortcut(QKeySequence(tr("Ctrl+O")), this);
     connect(openShortcut, SIGNAL(activated()), this, SLOT(openFile()));

     saveAsShortcut = new QShortcut(QKeySequence(tr("Ctrl+Shift+S")), this);
     connect(saveAsShortcut, SIGNAL(activated()), this, SLOT(saveFileAs()));

     importShortcut = new QShortcut(QKeySequence(tr("Ctrl+I")), this);
     connect(importShortcut, SIGNAL(activated()), this, SLOT(importFile()));

     exportShortcut = new QShortcut(QKeySequence(tr("Ctrl+E")), this);
     connect(exportShortcut, SIGNAL(activated()), this, SLOT(exportFile()));

     addShortcut = new QShortcut(QKeySequence(tr("Ctrl+A")), this);
     connect(addShortcut, SIGNAL(activated()), dataWidget, SLOT(addEntry()));
     connect(addShortcut, SIGNAL(activated()), this, SLOT(setNotSaved()));

     removeShortcut = new QShortcut(QKeySequence(tr("Del")), this);
     connect(removeShortcut, SIGNAL(activated()), dataWidget, SLOT(removeEntry()));
     connect(removeShortcut, SIGNAL(activated()), this, SLOT(setNotSaved()));

     newProjectShortcut = new QShortcut(QKeySequence(tr("Ctrl+N")), this);
     connect(newProjectShortcut, SIGNAL(activated()), this, SLOT(setNewProject()));
 }
 
 /**
  * Method for creating desired menus. It creates menu structure and connects it with default action. 
  * Most of these menu items are handled in this class.
  *
  * Mnemonic shortcuts are specified by Qt keychar & => &New means Alt+N
  * 
  * Data-specific menu items are handled in different class. It connects them to one more method for change check.
  * @see DataWidget
  * @see void setNotSaved(); 
  *
  * @author Lukas Raska (RAS0053)
  * @author Nokia corporation (Qt official documentation) under BSD licence 
  */
 void MainWindow::createMenus()
 {
     /* First main item */
     fileMenu = menuBar()->addMenu(tr("&Menu"));

     newProjectAct = new QAction(tr("&New project"), this);
     fileMenu->addAction(newProjectAct);
     connect(newProjectAct, SIGNAL(triggered()), this, SLOT(setNewProject()));

     fileMenu->addSeparator();

     openAct = new QAction(tr("&Open"), this);
     fileMenu->addAction(openAct);
     connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

     saveAct = new QAction(tr("&Save"), this);
     fileMenu->addAction(saveAct);
     connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

     saveAsAct = new QAction(tr("Sa&ve As"), this);
     fileMenu->addAction(saveAsAct);
     connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveFileAs()));

     fileMenu->addSeparator();

     exportAct = new QAction(tr("&Export"), this);
     fileMenu->addAction(exportAct);
     connect(exportAct, SIGNAL(triggered()), this, SLOT(exportFile()));

     importAct = new QAction(tr("&Import"), this);
     fileMenu->addAction(importAct);
     connect(importAct, SIGNAL(triggered()), this, SLOT(importFile()));

     fileMenu->addSeparator();

     exitAct = new QAction(tr("E&xit"), this);
     fileMenu->addAction(exitAct);
     connect(exitAct, SIGNAL(triggered()), this, SLOT(close())); // set default slot in Qt


     /* Second main item */
     toolMenu = menuBar()->addMenu(tr("&Data"));

     addAct = new QAction(tr("&Add Entry..."), this);
     toolMenu->addAction(addAct);
     connect(addAct, SIGNAL(triggered()), dataWidget, SLOT(addEntry()));
     connect(addAct, SIGNAL(triggered()), this, SLOT(setNotSaved()));


     editAct = new QAction(tr("&Edit Entry..."), this);
     editAct->setEnabled(false);
     toolMenu->addAction(editAct);
     connect(editAct, SIGNAL(triggered()), dataWidget, SLOT(editEntry()));
     connect(editAct, SIGNAL(triggered()), this, SLOT(setNotSaved()));


     toolMenu->addSeparator();

     removeAct = new QAction(tr("&Remove Entry"), this);
     removeAct->setEnabled(false);
     toolMenu->addAction(removeAct);
     connect(removeAct, SIGNAL(triggered()), dataWidget, SLOT(removeEntry()));
     connect(removeAct, SIGNAL(triggered()), this, SLOT(setNotSaved()));

 
     /* and create handler for activating data-specific menu items */
     connect(dataWidget, SIGNAL(selectionChanged(QItemSelection)), this, SLOT(updateActions(QItemSelection)));
     /* and double click bind */
     connect(dataWidget, SIGNAL(doubleClicked(QItemSelection)), this, SLOT(setNotSaved()));
 }


 /**
  * Method for creating new empty project. It checks for unsaved previous project first.
  * 
  * @see DataWidget::clear();
  * @see void checkSaved(); 
  */
 void MainWindow::setNewProject(){
     if(checkSaved()){
	dataWidget->clear();
	fileName.clear();
        setSaved(false,fileName);
     }
 }

 /**
  * Method for invoking Qt specific file dialog with default file type BCF. It checks for not-empty file name.
  * Checks for unsaved project first since it's data change.
  * 
  * Cross-check valid file with DataWidget. Sets new filename if file exists and is readable.
  *
  * @see DataWidget::readFromFile(QString fileName);
  * @see QFileDialog
  * @see void checkSaved(); 
  */
 void MainWindow::openFile()
 {
     if(checkSaved()){
     	QString fileN = QFileDialog::getOpenFileName(this,tr("Open project"),"",tr("Business card file (*.bcf);; All files (*)"));
     	if (!fileN.isEmpty()) {
          if(dataWidget->readFromFile(fileN)){
	    fileName = fileN;
	    setSaved(true, fileN);		
	  }
     	}
     }
 }



 /**
  * Method for saving data to previously specified file.
  * @see void saveFileAs();
  * @see void openFile();
  *
  * If no file has been specified, invokes saveFileAs() method.
  *
  * Cross-check valid file with DataWidget. Sets project as saved if file exists and is writeable. 
  *
  * @see DataWidget::writeToFile(QString fileName);
  * @see void checkSaved(); 
  */
 void MainWindow::saveFile(){
    if(!fileName.isEmpty()){
      if(dataWidget->writeToFile(fileName)){
	setSaved(true, fileName);
      }else{
	setSaved(false, fileName);
      }
    }else{
      saveFileAs();
    }
 }


 /**
  * Method for invoking Qt specific file dialog to obtain filename for saving data. Default is BCF file specific to this app.
  *
  * Cross-check valid file with DataWidget. Sets project as saved if file exists and is writeable. Then it sets new filename specified in dialog.
  *
  * @see DataWidget::writeToFile(QString fileName);
  * @see QFileDialog
  * @see void setSaved(bool b, QString FileN);
  */
 void MainWindow::saveFileAs()
 {
     QString fileN = QFileDialog::getSaveFileName(this,tr("Open project"),"",tr("Business card file (*.bcf);; All files (*)"));

     if (!fileN.isEmpty()) {
         if(dataWidget->writeToFile(fileN)){
	   setSaved(true, fileN);
         }else{
	   setSaved(false, fileName);
	 }
     }
 }


 /**
  * Method for invoking Qt specific file dialog to obtain filename for exporting data. 
  * If filename is not empty, passes that argument to data widget for processing. 
  *
  * @see DataWidget::exportFile(QString fileName);
  * @see QFileDialog
  */
 void MainWindow::exportFile(){
     QString fileN = QFileDialog::getSaveFileName(this,tr("Export project"),"",tr("CSV file (*.csv);; HTML file (*.html);; MySQL file (*.sql);; XML file (*.xml);; All files (*)"));
     if (!fileN.isEmpty()) {
         dataWidget->exportFile(fileN);
     }

 }

 /**
  * Method for invoking Qt specific file dialog. It checks for not-empty file name.
  * Sets project as "unsaved" since its data change.
  *
  * Passes filename as argument to data widget for processing
  *
  * @see DataWidget::importFile(QString fileName);
  * @see QFileDialog 
  * @see void setSaved(bool s, QString fileN);
  */
 void MainWindow::importFile(){  
  QString fileN = QFileDialog::getOpenFileName(this,tr("Import file"),"",tr("CSV file (*.csv);; XML file (*.xml);; All files (*)"));
  if(!fileN.isEmpty()){
    dataWidget->importFile(fileN);
    setSaved(false, fileName);
  }
 }

 /**
  * Wrapper method of type SLOT for signals connection singe it doesn't support arguments. Sets project as saved with previously given filename.
  *
  * @see void setSaved(bool s, QString fileN);
  */
 void MainWindow::setIsSaved(){
   setSaved(true, fileName);
 }

 /**
  * Wrapper method of type SLOT for signals connection singe it doesn't support arguments. Sets project as unsaved with previously given filename.
  *
  * @see void setSaved(bool s, QString fileN);
  */
 void MainWindow::setNotSaved(){
   setSaved(false, fileName);
 }


 /**
  * Method for handling saved/unsaved project. It sets default tile + file name. If filename is empty, it sets project to Untitle
  * Unsaved project is marked with * char 
  *
  * @see void setTitle(Qstring title);
  *
  * @param s boolean value describing project status - true(saved)/false(unsaved)
  * @param fileN filename used for displaying in title
  */
 void MainWindow::setSaved(bool s, QString fileN){
   saved=s;
   if(s==true){
     setTitle(QString("Business cards - ").append(fileN));
   }else{
     if(fileN.isEmpty()){
     	setTitle(QString("Business cards - Untitled").append("*"));
     }else{
	setTitle(QString("Business cards - ").append(fileN).append("*"));
     }
   }
 }

 /**
  * Method invoking Qt specifig dialog if project is marked as unsaved. User has three options how to response (Save / Cancel / Don't save)
  * 
  * @see QMessageBox
  * @see void saveFile();
  * 
  * @return boolean value if desired action can proceed
  */
 bool MainWindow::checkSaved(){
   while(!saved){
    switch(QMessageBox::information( this, "Save project.", "The data has been changed", "Save Now", "Cancel", "Don't save", 0, 1 )){
	case 0:
	  saveFile();
	break;
	case 1:
	  return false;
	case 2:
	  return true;
    }
   }
   return true;
 }

 /**
  * Method handling any data change (selection of some data). If it is valid date, enable data-specific menu items, else disable them.
  * 
  * @author Nokia corporation (Qt official documentation) under BSD licence  
  */
 void MainWindow::updateActions(const QItemSelection &selection)
 {
     QModelIndexList indexes = selection.indexes();

     if (!indexes.isEmpty()) {
         removeAct->setEnabled(true);
         editAct->setEnabled(true);
     } else {
         removeAct->setEnabled(false);
         editAct->setEnabled(false);
     }
 }

 /**
  * Overriden main method handling QCloseEvent to avoid losing unsaved projects.
  * If project is either saved or set as flushed it continues with default event purpose. If that condition is not met, it ignores this event
  *
  * @see QCloseEvent
  * @see bool checkSaved();
  *
  * @param event see Qt::QCloseEvent
  */
 void MainWindow::closeEvent ( QCloseEvent * event )
 {
   event->ignore();
   if(checkSaved()){
     event->accept();
   }
 }

 /**
  * Method for handling drop event (drag&drop system). It checks for valid data and pass it to other methods. It simulates open action.
  * Import method is not supported. So far, only binary files can be read!
  *
  * @param event dropevent with informations
  */
 void MainWindow::dropEvent(QDropEvent* event)
 {
    const QMimeData* mimeData = event->mimeData();
 
    if (mimeData->hasUrls())
    {
 	/* get only first file! */
        QList<QUrl> urlList = mimeData->urls();
      if(checkSaved()){
     	  if(dataWidget->readFromFile(urlList.at(0).toLocalFile())){
	    fileName = urlList.at(0).toLocalFile();
	    setSaved(true, fileName);		
            event->acceptProposedAction();
	  }
       } 
    }
 }

 /**
  * Overriden method that is called when files are moved into window. It's important to implement this method => default is deny.
  * @param event QDragEnterEvent
  */
 void MainWindow::dragEnterEvent(QDragEnterEvent* event)
 {
   event->acceptProposedAction();
 }
 
 /**
  * Overriden method that is called when files are moved in window. It's important to implement this method => default is deny.
  * @param event QDragMoveEvent
  */
 void MainWindow::dragMoveEvent(QDragMoveEvent* event)
 {
   event->acceptProposedAction();
 }
 
 
 /**
  * Overriden method that is called when files leave window. It's important to implement this method => default is deny.
  * @param event QDragLeaveEvent
  */
 void MainWindow::dragLeaveEvent(QDragLeaveEvent* event)
 {
    event->accept();
 }

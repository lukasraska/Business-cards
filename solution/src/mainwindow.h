 #ifndef MAINWINDOW_H
 #define MAINWINDOW_H

 #include <QtGui>
 #include "datawidget.h"

 /**
  * <p>
  * Main class that creates desired GUI. 
  * It has the purpose of wrapping - it covers the main data widget.
  * </p><p>
  * It handles menu, all menu actions and shortcuts. 
  * It also overrides main close event for case of closing unsaved project.
  * </p>
  *
  * @see mainwindow.cpp
  * @author Lukas Raska (RAS0053)
  * @author Nokia corporation (Qt official documentation) under BSD licence (where specified)
  * @version 1.0
  */ 
 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();
     void closeEvent(QCloseEvent * event); 

 private slots:
     void updateActions(const QItemSelection &selection);
     void openFile();
     void saveFile();
     void setIsSaved();
     void setNotSaved();
     void saveFileAs();
     void exportFile();
     void importFile();
     void setNewProject();

 private:
     /** variable used for checking saved/unsaved project */
     bool saved;
     bool checkSaved();
     void setSaved(bool s, QString fileN);
     void createMenus();
     void bindShortcuts();
     void setTitle(QString title);

     /** name of currently used file */
     QString fileName;
     /** variable containing our DataWidget */
     DataWidget *dataWidget;
     /** first menu item - Menu */
     QMenu *fileMenu;
     /** second menu item - Records manipulation - Data */
     QMenu *toolMenu;
     /** Open action handle */
     QAction *openAct;
     /** Save action handle */
     QAction *saveAct;
     /** Save as action handle */
     QAction *saveAsAct;
     /** Export data action handle */
     QAction *exportAct;
     /** Import data action handle */
     QAction *importAct;
     /** Exit app action handle */
     QAction *exitAct;
     /** Add record action handle */
     QAction *addAct;
     /** Edit record action handle */
     QAction *editAct;
     /** Remove record action handle */
     QAction *removeAct;
     /** New project action handle */
     QAction *newProjectAct;

     /* shortcuts */
     /** Save file shortcut */
     QShortcut *saveShortcut;
     /** Save file shortcut */
     QShortcut *openShortcut;
     /** Save file as shortcut */
     QShortcut *saveAsShortcut;
     /** Import data shortcut */
     QShortcut *importShortcut;
     /** Export data shortcut */
     QShortcut *exportShortcut;
     /** Add record shortcut */
     QShortcut *addShortcut;
     /** Remove record shortcut */
     QShortcut *removeShortcut;
     /** New project shortcut */
     QShortcut *newProjectShortcut;

  protected:
     void dropEvent(QDropEvent* event);
     void dragEnterEvent(QDragEnterEvent* event); 
     void dragMoveEvent(QDragMoveEvent* event);
     void dragLeaveEvent(QDragLeaveEvent* event);
 };

 #endif

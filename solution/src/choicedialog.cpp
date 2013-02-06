 #include <QtGui>
 #include "choicedialog.h"


/**
 * Constructor inherited from QDialog, dialog window for selection choice.
 * 
 * It's never called directly and it's not part of any widget, so param is null.
 * 
 * @author Lukas Raska (RAS0053)
 */ 
 ChoiceDialog::ChoiceDialog(QWidget *parent)
     : QDialog(parent)
 {
     /* set labels */
     exportCreateTableLabel = new QLabel("Add CREATE TABLE");
     exportCreateTableINELabel = new QLabel("Add \"IF NOT EXISTS\" to CREATE TABLE");
     exportRecordsLabel = new QLabel("Export records");
     exportRecordsWSLabel = new QLabel("Record filter");
     autoIncrementLabel = new QLabel("Auto increment starting value");
     tableNameLabel = new QLabel("Table name");
     okButton = new QPushButton("OK");
     cancelButton = new QPushButton("Cancel");

     /* create desired objects, they have to be public and "global" for other classes access */
     exportCreateTable = new QCheckBox;
     exportCreateTableIfNotExists = new QCheckBox;
     exportRecords = new QCheckBox;
     exportRecordsWithString = new QLineEdit;
     autoIncrementFrom = new QLineEdit;
     tableName = new QLineEdit;

     /* set default values */
     exportCreateTable->setChecked(true);
     exportRecords->setChecked(true);
     autoIncrementFrom->setText(QString("0"));
     tableName->setText(QString("business_cards"));


     /* create grid layout for good-looking ui, similar to html <table> tag */
     QGridLayout *gLayout = new QGridLayout;
     gLayout->setColumnStretch(1, 6); // size


     /* creating UI */
     gLayout->addWidget(exportCreateTableLabel, 0, 0); // object, x, y (, alignment)
     gLayout->addWidget(exportCreateTable, 0, 1);

     gLayout->addWidget(exportCreateTableINELabel, 1, 0);
     gLayout->addWidget(exportCreateTableIfNotExists, 1, 1);

     gLayout->addWidget(exportRecordsLabel, 2, 0);
     gLayout->addWidget(exportRecords, 2, 1);

     gLayout->addWidget(exportRecordsWSLabel, 3, 0);
     gLayout->addWidget(exportRecordsWithString, 3, 1);

     gLayout->addWidget(autoIncrementLabel, 4, 0);
     gLayout->addWidget(autoIncrementFrom, 4, 1);

     gLayout->addWidget(tableNameLabel, 5, 0);
     gLayout->addWidget(tableName, 5, 1);

     
     /* create special layout for buttons to good-looking design, since orignal layout is cut to two unequal pieces */
     QHBoxLayout *buttonLayout = new QHBoxLayout;
     buttonLayout->addWidget(okButton);
     buttonLayout->addWidget(cancelButton);

     gLayout->addLayout(buttonLayout, 6, 1, Qt::AlignRight);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addLayout(gLayout);
     setLayout(mainLayout);


     /* connect signals from buttons to default actions -> mandatory for exec() method, since it returns state of dialog */
     connect(okButton, SIGNAL(clicked()),this, SLOT(accept()));
     connect(cancelButton, SIGNAL(clicked()),this, SLOT(reject()));

     setWindowTitle(tr("Specify values for export"));
 }

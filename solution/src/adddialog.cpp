 #include <QtGui>
 #include "adddialog.h"


/**
 * Constructor inherited from QDialog, dialog window for adding record. 
 * Due to similar function with edit dialog it's also used for edditing
 * 
 * It's never called directly and it's not part of any widget, so param is null.
 * 
 * @author Lukas Raska (RAS0053)
 * @author Nokia corporation (Qt official documentation) under BSD licence (where specified)
 */ 
 AddDialog::AddDialog(QWidget *parent)
     : QDialog(parent)
 {
     /* set labels */
     nameLabel = new QLabel("Name");
     professionLabel = new QLabel("Profession");
     addressLabel = new QLabel("Address");
     mobileLabel = new QLabel("Mobile");
     emailLabel = new QLabel("Email");
     websiteLabel = new QLabel("Website");
     okButton = new QPushButton("OK");
     cancelButton = new QPushButton("Cancel");

     /* create desired objects, they have to be public and "global" for other classes access */
     nameText = new QLineEdit;
     professionText = new QLineEdit;
     addressText = new QTextEdit;
     mobileText = new QLineEdit;
     emailText = new QLineEdit;
     websiteText = new QLineEdit;


     /* create grid layout for good-looking ui, similar to html <table> tag */
     QGridLayout *gLayout = new QGridLayout;
     gLayout->setColumnStretch(1, 6); // size


     /* creating UI */
     gLayout->addWidget(nameLabel, 0, 0); // object, x, y (, alignment)
     gLayout->addWidget(nameText, 0, 1);

     gLayout->addWidget(professionLabel, 1, 0);
     gLayout->addWidget(professionText, 1, 1);

     gLayout->addWidget(addressLabel, 2, 0, Qt::AlignLeft|Qt::AlignTop); // label is at top, not at center
     gLayout->addWidget(addressText, 2, 1, Qt::AlignLeft);

     gLayout->addWidget(mobileLabel, 3, 0);
     gLayout->addWidget(mobileText, 3, 1);

     gLayout->addWidget(emailLabel, 4, 0);
     gLayout->addWidget(emailText, 4, 1);

     gLayout->addWidget(websiteLabel, 5, 0);
     gLayout->addWidget(websiteText, 5, 1);

     
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

     setWindowTitle(tr("Add new record"));
 }

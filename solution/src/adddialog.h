 #ifndef ADDDIALOG_H
 #define ADDDIALOG_H

 #include <QDialog>

 class QLabel;
 class QPushButton;
 class QTextEdit;
 class QLineEdit;

/**
 * <p>
 * Class creating only dialog window for adding new record.
 *
 * @author Lukas Raska (RAS0053)
 * @author Nokia corporation (Qt official documentation) under BSD licence
 * @version 1.0
 */ 
 class AddDialog : public QDialog
 {
     Q_OBJECT

 public:
     AddDialog(QWidget *parent=0);
     /** Edit box for name */
     QLineEdit *nameText;
     /** Edit box for profession */
     QLineEdit *professionText;
     /** Edit textbox for address */
     QTextEdit *addressText;
     /** Edit box for mobile */
     QLineEdit *mobileText;
     /** Edit box for email */
     QLineEdit *emailText;
     /** Edit box for website */
     QLineEdit *websiteText;

 private:
     /** Label describing what nameText is for */
     QLabel *nameLabel;
     /** Label describing what professionText is for */
     QLabel *professionLabel;
     /** Label describing what addressText is for */
     QLabel *addressLabel;
     /** Label describing what mobileText is for */
     QLabel *mobileLabel;
     /** Label describing what emailText is for */
     QLabel *emailLabel;
     /** Label describing what websiteText is for */
     QLabel *websiteLabel;
     /** OK Button */
     QPushButton *okButton;
     /** Cancel button */
     QPushButton *cancelButton;
 };

 #endif

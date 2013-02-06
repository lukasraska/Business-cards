 #ifndef CHOICEDIALOG_H
 #define CHOICEDIALOG_H

 #include <QDialog>

 class QLabel;
 class QPushButton;
 class QCheckBox;
 class QLineEdit;

/**
 * <p>
 * Class creating specific dialog window with choices
 *
 * @author Lukas Raska (RAS0053)
 * @version 1.0
 */ 
 class ChoiceDialog : public QDialog
 {
     Q_OBJECT

 public:
     ChoiceDialog(QWidget *parent=0);
     /** Checkbox used for exporting create table sql statement or not*/
     QCheckBox * exportCreateTable; // drop
     /** Checkbox used for not exporting drop table sql statement or yes */
     QCheckBox * exportCreateTableIfNotExists;
     /** Checkbox used for exporting records or not */
     QCheckBox * exportRecords;
     /** Textbox used for filtering exporting records */
     QLineEdit * exportRecordsWithString;
     /** Textbox used for specicying starting AI value */
     QLineEdit * autoIncrementFrom;
     /** Textbox used for specifying sql table name / html table heading */
     QLineEdit * tableName;

 private:
     /** Label describing what exportCreateTable does */
     QLabel * exportCreateTableLabel;
     /** Label describing what exportCreateTableIfNotExists does */
     QLabel * exportCreateTableINELabel;
     /** Label describing what exportRecords does */
     QLabel * exportRecordsLabel;
     /** Label describing what exportRecordsWithString does */
     QLabel * exportRecordsWSLabel;
     /** Label describing what autoIncrementFrom does */
     QLabel * autoIncrementLabel;
     /** Label describing what tableName does */
     QLabel * tableNameLabel;

     /** OK Button*/
     QPushButton *okButton;
     /** Cancel Button*/
     QPushButton *cancelButton;
 };

 #endif

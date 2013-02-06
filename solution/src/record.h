#ifndef RECORD_H
#define RECORD_H
 /**
  * Class for records (business cards), it's mandatory because of MVC architecture.
  *
  * It contains overloaded "==" operator used for checking duplicite data.
  *
  * @see DataWidget
  * @see TableModel
  *
  * @author Lukas Raska (RAS0053)
  * @version 1.0
  */
 class Record {
   public:
      Record();
      Record(QString _name, QString _profession, QString _address, QString _mobile, QString _email, QString _website);
      QString name;
      QString profession;
      QString address;
      QString mobile;
      QString email;
      QString website;
	

      bool operator==(const Record& ref) const;
 };

  QDataStream &operator <<(QDataStream &stream, const Record &r);
  QDataStream &operator >>(QDataStream &stream, Record &r);
#endif

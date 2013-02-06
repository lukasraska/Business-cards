#include <QtGui>
#include "record.h"

/**
 * "Virtual" constructor for Record class. Its only used if we dont know data for default constructor.
 * @see DataWidget
 */
Record::Record(){}


/**
 * Default (main) constructor for Record class. Its used whenever we need to create Business card object.
 * We assume we create object with valid data.
 *
 * @param _name name
 * @param _profession profession
 * @param _address address
 * @param _mobile mobile
 * @param _email email
 * @param _website website
 */
Record::Record(QString _name, QString _profession, QString _address, QString _mobile, QString _email, QString _website){
  name=_name;
  profession=_profession;
  address=_address;
  mobile=_mobile;
  email=_email;
  website=_website;

}

/**
 * Overloaded comparsion operator for duplicit data checking, since this is custom object. It primary use is with QList<Record>.contains(Record)
 * @see DataWidget::addEntry()
 *
 * @param ref another object for comparsion
 * @return boolean value describing status of those objects, true if they are similar, false if not
 */
bool Record::operator==(const Record& ref) const{
        if(ref.name.compare(name, Qt::CaseInsensitive)==0 && 
           ref.profession.compare(profession, Qt::CaseInsensitive)==0 &&            
           ref.address.compare(address, Qt::CaseInsensitive)==0 && 
           ref.mobile.compare(mobile, Qt::CaseInsensitive)==0 && 
           ref.email.compare(email, Qt::CaseInsensitive)==0 && 
           ref.website.compare(website, Qt::CaseInsensitive)==0){
           return true;
        }
        return false;
}

//datastream override
/**
 * Overloaded stream assignment (write-to-stream) method since this is custom class.
 * @see QDataStream
 *
 */
QDataStream& operator<<(QDataStream &out, const Record &r){
   out << r.name << r.profession << r.address << r.mobile << r.email << r.website;
   return out;
}

/**
 * Overloaded stream assignment (read-from-stream) method since this is custom class.
 * @see QDataStream
 *
 */
QDataStream& operator>>(QDataStream &in, Record &r){
  in >> r.name >> r.profession >> r.address >> r.mobile >> r.email >> r.website;
  return in;
}


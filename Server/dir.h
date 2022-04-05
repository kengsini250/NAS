#ifndef DIR_H
#define DIR_H

#include <QDir>
#include <QFile>
#include <QFileInfo>

#include <QDomDocument>
#include <QDomNamedNodeMap>

class Dir : public QObject
{
	Q_OBJECT
public:
	Dir(QObject* parent = Q_NULLPTR);
	Dir(const QString& ,QObject* parent = Q_NULLPTR);
	QString path();
	void changeDir(const QString&);
	void getAllFiles(QString&);
	void cdUp();
	bool isDir(const QString&);
	qintptr fileSize(const QString&);
	void newDir(const QString&);
	void removeDir(const QString&);
	void rename(const QString& name);

	QString filePath(const QString&);
private:
	QString root ="";
	QDir dir;
};



#endif

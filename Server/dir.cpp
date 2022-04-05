#include "dir.h"
#pragma execution_character_set("utf-8")

Dir::Dir(QObject* parent):QObject(parent)
{
	QString filePath = "config.xml";
	QFile xml(filePath);
	xml.open(QFile::ReadOnly);

	QDomDocument domDocument;
	domDocument.setContent(&xml);
	QDomElement _root = domDocument.documentElement();
	QDomNode node_a = _root.firstChild();//root
	while (!node_a.isNull())
	{
		QDomElement node_all = node_a.toElement();//rootDir
		QDomElement tag1 = node_all.firstChildElement("dir");
		root = tag1.text();
		node_a = node_a.nextSibling();
	}

	xml.close();
	dir.setPath(root);
}

Dir::Dir(const QString& s,QObject* parent) : QObject(parent)
{
	root = s;
	dir.setPath(root);
}

QString Dir::path()
{
	return dir.path();
}

void Dir::changeDir(const QString&c)
{
	dir.cd(c);
}

void Dir::getAllFiles(QString&d)
{
	QString data;
	dir.setFilter(QDir::Dirs | QDir::Files );
	dir.setSorting(QDir::DirsFirst);
	QFileInfoList list = dir.entryInfoList();

	//d fileName! 
	//- fileName! 
	for (auto p = list.begin(); p != list.end(); p++) {
		//¹ýÂË"."
		if ((*p).fileName() == "." )
			continue;

		if ((*p).isDir()) {
			data += "d " + (*p).fileName();
		}
		else {
			data += "- " + (*p).fileName();
		}
		//·Ö¸î
		data += "!";
	}
	d = data;
}

void Dir::cdUp()
{
	dir.cdUp();
}

bool Dir::isDir(const QString&name)
{
	QString curr = dir.path() + "/" + name;
	QFileInfo info(curr);
	if(info.isDir())
		return true;
	return false;
}

qintptr Dir::fileSize(const QString& name)
{
	QString curr = dir.path() + "/" + name;
	QFileInfo info(curr);
	if (info.isDir())
		return -1;
	return info.size();
}

void Dir::removeDir(const QString&name)
{
	bool end;
	QString curr = dir.path() + "/" + name;
	QFileInfo info(curr);
	//qDebug() << curr;
	if (info.isDir()) {
		end = dir.rmdir(name);
		//qDebug() << "remove dir : " << end;
	}
	else {
		end = dir.remove(name);
		//qDebug() << "remove file : " << end;
	}


}

void Dir::rename(const QString& name)
{
	QStringList temp = name.split('!');
	dir.rename(temp[0], temp[1]);
}

void Dir::newDir(const QString& name)
{
	bool end = dir.mkdir(name);
	//qDebug() << "new dir : " << name << " -> "<<end;
}

QString Dir::filePath(const QString&name)
{
	return dir.path() + "/" + name;
}


#include "dir.h"
#pragma execution_character_set("utf-8")

Dir::Dir(QObject* parent):QObject(parent)
{
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

QString Dir::filePath(const QString&name)
{
	return dir.path() + "/" + name;
}


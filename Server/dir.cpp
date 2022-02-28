#include "dir.h"

Dir::Dir(QObject* parent):QObject(parent)
{
}

Dir::Dir(const QString& s,QObject* parent) : QObject(parent)
{
	root = s;
	dir.setPath(root);
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
		if ((*p).fileName() == ".")
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

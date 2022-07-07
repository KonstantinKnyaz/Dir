#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>

#define HELP        "--help"
#define FRSTARG     0

void dirInfo(const QString &dirPath);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qInfo() << "Для справки введите в качестве аргемента: ''--help''";
    //Записываю аргументы в стринг лист
    QStringList strList = a.arguments();
    //Удаляю пустой аргумент
    strList.removeAt(FRSTARG);
    if(strList.count() > 0) {

        for(int i = 1; i < strList.count(); i++) {
            strList[0] += (" " + strList[i]);
        }

        if(strList.at(FRSTARG) == HELP) {
            qInfo() << "В качестве аргумента введите полный путь до папки.";
        } else {
            dirInfo(strList.at(FRSTARG));
        }
    } else {
        qInfo() << "Не были введены аргументы";
    }

    return a.exec();
}

// ---Рекурсия---
void dirInfo(const QString &dirPath) {

    QDirIterator itDir(dirPath, QDir::Dirs | QDir::NoDotAndDotDot);
    while (itDir.hasNext()) {
        itDir.next();
        QFileInfo info = itDir.fileInfo();
        qDebug() << "Папка:" << info;
        dirInfo(itDir.filePath());
    }

    QDirIterator itFile(dirPath, QDir::Files);
    while (itFile.hasNext()) {
        itFile.next();
        QFileInfo info = itFile.fileInfo();
        qDebug() << "Файл:" << info;
    }
}

#include <QGuiApplication>
#include <model.h>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickItem>
#include <QObject>

bool deleteGroup(int groupNum)
{

    return true;
}
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MyClass>("MyConnection",1,0,"MyClass");

    //    QVector<PlanModelAll> pmaArray(4);

    int GroupNum=5;
    PlanModelAll pmaArray[GroupNum];
    for(int i=0; i<GroupNum; i++){
        pmaArray[i].append("1", "#f44336", true, 1);
        pmaArray[i].append("Mandible", "#ff9800", true, 1);
        pmaArray[i].append("Mirror","#2196f3", true, 1);
        pmaArray[i].append("1", "#3f51b5", true, 1);
        pmaArray[i].append("2","#4caf50", true,1);
        pmaArray[i].append("3", "#9c27b0", true, 1);
    }


    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext *ctxt = view.rootContext();

    ctxt->setContextProperty ("myModel0", &pmaArray[0]);
    ctxt->setContextProperty("myModel1", &pmaArray[1]);
    ctxt->setContextProperty("myModel2", &pmaArray[2]);
    ctxt->setContextProperty("myModel3", &pmaArray[3]);
    ctxt->setContextProperty("myModel4", &pmaArray[4]);
    //    view.setFlags (Qt::FramelessWindowHint|Qt::Window|Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint);
    //    view.showFullScreen();
    view.setSource(QUrl("qrc:///main.qml"));
    QQuickItem *rootObject = view.rootObject ();
    MyClass class1;
    if(rootObject)
    {
        QObject::connect (rootObject, SIGNAL(nameChange(QString)), &class1, SLOT(PMNameChange(QString)));
    }

    view.show();
    return app.exec();
}














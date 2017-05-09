#ifndef MODEL_H
#define MODEL_H
#include <QAbstractListModel>
#include <QColor>
#include <QDebug>

class PlanModel
{
public:
    PlanModel(const QString &name, const QColor &color, const bool &isVisible, const double &opacity);

    QString name() const;
    QColor color() const;
    bool isVisible() const;
    double opacity() const;

private:
    QString m_name;
    QColor m_color;
    bool m_isVisible;
    double m_opacity;
};

class PlanModelAll: public QAbstractListModel
{
    Q_OBJECT
public:
    enum PlanModelRoles{
        NameRole = Qt::UserRole + 1,
        ColorRole,
        IsVisibleRole,
        Opacity
    };

    PlanModelAll(QObject *parent=0);
    int rowCount(const QModelIndex &parent=QModelIndex())const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const;

    Q_INVOKABLE QVariantMap get(int row)const;
    Q_INVOKABLE void append(const QString &name, const QColor &color, const bool &isVisible, const double &opacity);
    Q_INVOKABLE void set(int row, const QString &name, const QColor &color, const bool &isVisible, const double &opacity);
    Q_INVOKABLE void remove(int row);

protected:
    QHash<int, QByteArray> roleNames()const;
private:
    QList<PlanModel> m_planModel;
};

class MyClass: public QObject
{
    Q_OBJECT
signals:
    void test(QString info);
public slots:
    void PMNameChange(const QString &name){
        qDebug() << "PMNameChange: " << name;
    }
    void PMNameChange2(const QString &name){
        qDebug() << "PMNameChange2" << name;
    }
};

#endif // MODEL_H

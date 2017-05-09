#include "model.h"
#include <QVariantMap>

PlanModel::PlanModel(const QString &name, const QColor &color, const bool &isVisible, const double &opacity)
    :m_name(name), m_color(color), m_isVisible(isVisible), m_opacity(opacity)
{
}

QString PlanModel::name() const{
    return m_name;
}

QColor PlanModel::color() const{
    return m_color;
}

bool PlanModel::isVisible () const{
    return m_isVisible;
}

double PlanModel::opacity() const{
    return m_opacity;
}

PlanModelAll::PlanModelAll(QObject *parent)
    :QAbstractListModel(parent)
{
}

//void PlanModelAll::addPlanModel(const PlanModel &planModel)
//{
//    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//    m_planModel<<planModel;
//    endInsertRows();
//}

QVariant PlanModelAll::data(const QModelIndex &index, int role) const{
    if(index.row()<0 || index.row()>m_planModel.count())
        return QVariant();

    const PlanModel &planModel = m_planModel[index.row()];
    switch(role){
    case NameRole: return planModel.name();
    case ColorRole: return planModel.color();
    case IsVisibleRole: return planModel.isVisible ();
    case Opacity: return planModel.opacity();
    default: return QVariant();
    }
}

int PlanModelAll::rowCount(const QModelIndex &parent)const{
    Q_UNUSED(parent);
    return m_planModel.count();
}

QHash<int, QByteArray> PlanModelAll::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ColorRole] = "color";
    roles[IsVisibleRole] = "isVisible";
    roles[Opacity] = "opacity";
    return roles;
}

QVariantMap PlanModelAll::get(int row)const
{
    const PlanModel &planModel = m_planModel[row];
    return {{"name", planModel.name()}, {"color", planModel.color()}, {"isVisible", planModel.isVisible ()},{"opacity", planModel.opacity()}};
}

void PlanModelAll::append(const QString &name, const QColor &color, const bool &isVisible, const double &opacity)
{
//    int row = 0;
//    while (row < m_planModel.count() && name > m_planModel[row].name())
//        ++row;
    int row = m_planModel.count();
    beginInsertRows(QModelIndex(), row, row);
    m_planModel.insert(row, PlanModel(name, color, isVisible, opacity));
    endInsertRows();
}

void PlanModelAll::set(int row, const QString &name, const QColor &color, const bool &isVisible, const double &opacity)
{
    if(row < 0 || row >= m_planModel.count())
        return;
    m_planModel.replace(row, PlanModel(name,color, isVisible, opacity));
    dataChanged(index(row,0), index(row,0), {NameRole, ColorRole, IsVisibleRole, Opacity});
//    emit
//    qDebug()<<"PlanModelAll::set: ";
}

void PlanModelAll::remove(int row)
{
    if(row < 0 || row >= m_planModel.count())
        return;

    beginRemoveRows (QModelIndex(), row, row);
    m_planModel.removeAt (row);
    endRemoveRows ();
}

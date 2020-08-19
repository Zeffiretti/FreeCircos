#ifndef CIRCOS_H
#define CIRCOS_H
#include <QMainWindow>
#include <QElapsedTimer>
#include <QDebug>
#include "gene.h"
#include "category.h"
#include "paint/customdonut.h"
#include "paint/customslice.h"
#include "fileprocess/excelbase.h"
#include "fileprocess/qvariantlistlistmodel.h"
class Circos {
  public:
    Circos();

    QList<Gene *> back_bone;
    QList<int> back_bone_sequence;
    QList<Category *> category;
    QList<int> category_sequence;

    QScopedPointer<ExcelBase> m_xls;
    QList<QList<QVariant> > m_datas;

    void OpenFile(const QString&);
    void DataToBackBone(void);
    void DataToCategory(void);
    int IndexOfGene(const QString&);
    void BuildBackBoneDonut(CustomDonut*);
    void BuildCategoryDonut(CustomDonut*);
    Gene* FindGene(const QString name);
    Category* FindCategory(const QString name);
    int TakeGeneAt(int index);
    void InsertGene(int index, int value);
    int TakeCategoryAt(int index);
    void InsertCategory(int index, int value);
    void AdjustBackBoneToCategory(void);
};

#endif // CIRCOS_H

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
    bool category_enabled;
    QList<Category *> category;
    QList<int> category_sequence;

    QScopedPointer<ExcelBase> m_xls;
    QList<QList<QVariant> > m_datas;

    void openFile(const QString&);
    void dataToBackBone(void);
    void dataToCategory(void);
    int indexOfGene(const QString&);
    int indexofCategory(const QString&);
    void buildBackBoneSequence(QStandardItemModel *model);
    void buildBackBoneDonut(CustomDonut*);
    void buildCategorySequence(QStandardItemModel *model);
    void buildCategoryDonut(CustomDonut*);
    Gene* findGene(const QString name);
    Category* findCategory(const QString name);
    int takeGeneAt(int index);
    void insertGene(int index, int value);
    int takeCategoryAt(int index);
    void insertCategory(int index, int value);
    void adjustBackBoneToCategory(void);

    void setCategoryEnable(bool b);
    bool getCategoryEnable(void);
};

#endif // CIRCOS_H

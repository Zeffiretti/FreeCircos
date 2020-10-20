#ifndef CIRCOS_H
#define CIRCOS_H
#include <QMainWindow>
#include <QElapsedTimer>
#include <QDebug>
#include <QObject>
#include "gene.h"
#include "category.h"
#include "link.h"
#include "paint/customdonut.h"
#include "paint/customslice.h"
#include "paint/customlink.h"
#include "paint/customlinkcanvas.h"
#include "fileprocess/excelbase.h"
#include "fileprocess/qvariantlistlistmodel.h"
#include "tool/customtool.h"
class Circos : public QObject {
    Q_OBJECT
  public:
    Circos(QObject *parent = nullptr);
    ~Circos();

    void openFile(const QString&);
    void dataToBackBone(void);
    void dataToCategory(void);
    void dataToLink(void);
    int indexOfGene(const QString&);
    int indexOfCategory(const QString&);
    void buildBackBoneSequence(QStandardItemModel *model);
    void buildBackBoneDonut(CustomDonut*);
    void buildCategorySequence(QStandardItemModel *model);
    void buildCategoryDonut(CustomDonut*);
    void buildCustomLink(CustomLinkCanvas*);

    Gene* findGene(const QString name);
    Category* findCategory(const QString name);
    int takeGeneAt(int index);
    void insertGene(int index, int value);
    int takeCategoryAt(int index);
    void insertCategory(int index, int value);
    void adjustBackBoneToCategory(void);

    void setCategoryEnable(bool b);
    bool getCategoryEnable(void);

    void setLinkEnable(bool b);
    bool getLinkEnable(void);

    void setLinkType(CustomLinkCanvas::LinkTypes);
    CustomLinkCanvas::LinkTypes getLinkType(void);

    Gene* getGene(int index);
    void clearBackBone(void);
    void clearBackBoneSequence(void);
    void appendBackBoneSequence(int index);
    int getBackBoneSequence(int index);
    int getGeneNum(void);

    Link* getLink(int index);
    int getLinkNum(void);

  public slots:
    void onGeneAngleChanged(const QString& n, qreal s, qreal e);

  private:
    QList<Gene *> back_bone;
    QList<int> back_bone_sequence;
    bool category_enabled = false;
    QList<Category *> category;
    QList<int> category_sequence;
    bool link_enabled = false;
    QList<Link *> links;
    CustomLinkCanvas::LinkTypes link_type = CustomLinkCanvas::LinkType::IntroOut;

    QScopedPointer<ExcelBase> m_xls;
    QList<QList<QVariant> > m_datas;


};

#endif // CIRCOS_H

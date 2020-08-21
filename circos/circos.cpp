#include "circos.h"

Circos::Circos() {
    back_bone.clear();
    m_datas.clear();
    back_bone_sequence.clear();
    category.clear();
    category_sequence.clear();
}

void Circos::OpenFile(const QString &xlsFile) {
    m_datas.clear();
    if(xlsFile.isEmpty())
        return;
    QElapsedTimer timer;
    timer.start();
    if(m_xls.isNull())
        m_xls.reset(new ExcelBase);
    m_xls->open(xlsFile);
    qDebug() << "open cost:" << timer.elapsed() << "ms";
    timer.restart();
    m_xls->setCurrentSheet(1);
    m_xls->readAll(m_datas);
    qDebug() << "read data cost:" << timer.elapsed() << "ms";
    timer.restart();
    m_xls->close();
}

void Circos::DataToBackBone(void) {
    back_bone.clear();
    back_bone_sequence.clear();
    if(m_datas.at(0).at(2) != "") {
        for(int i = 1; i < m_datas.size(); ++i) {
            Gene *g = new Gene(m_datas.at(i).at(0).toString(),
                               m_datas.at(i).at(1).toUInt(),
                               m_datas.at(i).at(2).toUInt());
            back_bone.append(g);
            back_bone_sequence.append(i - 1);
        }
    } else {
        for(int i = 1; i < m_datas.size(); ++i) {
            Gene *g = new Gene(m_datas.at(i).at(0).toString(),
                               m_datas.at(i).at(1).toUInt());
            back_bone.append(g);
            back_bone_sequence.append(i - 1);
        }
    }
}

void Circos::DataToCategory(void) {
    category.clear();
    category_sequence.clear();
    QString category_name;
    QString gene_name;
    for(int i = 1, cnt = 0; i < m_datas.size(); ++i) {
        gene_name = m_datas.at(i).at(0).toString();
        if(!m_datas.at(i).at(1).isNull()) {
            category_name = m_datas.at(i).at(1).toString();
            Category* new_category = new Category(category_name);
            new_category->AddGene(gene_name);
            category.append(new_category);
            category_sequence.append(cnt);
            cnt++;
        } else {
            FindCategory(category_name)->AddGene(gene_name);
        }
    }

//    for(int i = 0; i < category.size(); ++i) {
//        qDebug() << "category name:[" << category.at(i)->name << "] " << category.at(i)->m_genes;
//    }
}

int Circos::IndexOfGene(const QString &n) {
    for(int i = 0; i < back_bone.size(); ++i) {
        if(back_bone.at(i)->name == n) {
            return i;
        }
    }
    return -1;
}

void Circos::BuildBackBoneDonut(CustomDonut *donut) {
    donut->Clear();
    for(int i = 0; i < back_bone_sequence.size(); ++i) {
        int index = back_bone_sequence.at(i);

        CustomSlice *slice = new CustomSlice(back_bone.at(index)->name,
                                             back_bone.at(index)->getLength());
        slice->SetBrush(QBrush(back_bone.at(index)->getFillColor()));
        slice->SetPen(QPen(back_bone.at(index)->getStrikeColor()));
        donut->AddSlice(slice);
    }
}

void Circos::BuildCategoryDonut(CustomDonut *donut) {
    donut->Clear();
    for(int i = 0; i < category_sequence.size(); ++i) {
        int index = category_sequence.at(i);
        Category* c = category.at(index);
        int sum = 0;
        for(int j = 0; j < c->Count(); ++j) {
            QString g = c->m_genes.at(j);
            sum += FindGene(g)->getLength();
        }
        CustomSlice* slice = new CustomSlice(c->name, sum);
        donut->AddSlice(slice);
    }
}

Gene* Circos::FindGene(const QString name) {
    for(int i = 0; i < back_bone.size(); ++i) {
        if(back_bone.at(i)->name == name) {
            return back_bone.at(i);
        }
    }
    return new Gene;
}

Category* Circos::FindCategory(const QString name) {
    for(int i = 0; i < category.size(); ++i) {
        if(category.at(i)->name == name) {
            return category.at(i);
        }
    }
    return new Category;
}

int Circos::TakeGeneAt(int index) {
    return back_bone_sequence.takeAt(index);
}

void Circos::InsertGene(int index, int value) {
    return back_bone_sequence.insert(index, value);
}

int Circos::TakeCategoryAt(int index) {
    return category_sequence.takeAt(index);
}

void Circos::InsertCategory(int index, int value) {
    return category_sequence.insert(index, value);
}

void Circos::AdjustBackBoneToCategory(void) {
    back_bone_sequence.clear();
    for(auto it = category_sequence.begin(); it != category_sequence.end(); ++it) {
        for(auto it2 = category.at(*it)->begin(); it2 != category.at(*it)->end(); ++it2) {
            back_bone_sequence.append(IndexOfGene(*it2));
        }
    }
}

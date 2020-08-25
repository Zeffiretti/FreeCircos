#include "circos.h"

Circos::Circos() {
    back_bone.clear();
    m_datas.clear();
    back_bone_sequence.clear();
    category.clear();
    category_sequence.clear();
    category_enabled = false;
}

void Circos::openFile(const QString &xlsFile) {
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

void Circos::dataToBackBone(void) {
    back_bone.clear();
    back_bone_sequence.clear();
    if(m_datas.at(0).at(2) != "") {
        for(int i = 1; i < m_datas.size(); ++i) {
            Gene *g = new Gene(m_datas.at(i).at(0).toString(),
                               m_datas.at(i).at(1).toUInt(),
                               m_datas.at(i).at(2).toUInt());
            g->setFillColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
            g->setStrikeColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
            g->setLabelState(CustomSlice::LabelSleep);
            g->setLabelPosition(CustomSlice::LabelOnDonut);
            back_bone.append(g);
            back_bone_sequence.append(i - 1);
        }
    } else {
        for(int i = 1; i < m_datas.size(); ++i) {
            Gene *g = new Gene(m_datas.at(i).at(0).toString(),
                               m_datas.at(i).at(1).toUInt());
            g->setFillColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
            g->setStrikeColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
            back_bone.append(g);
            back_bone_sequence.append(i - 1);
        }
    }
}

void Circos::dataToCategory(void) {
    category_enabled = true;
    category.clear();
    category_sequence.clear();
    QString category_name;
    QString gene_name;
    for(int i = 1, cnt = 0; i < m_datas.size(); ++i) {
        gene_name = m_datas.at(i).at(0).toString();
        if(!m_datas.at(i).at(1).isNull()) {
            category_name = m_datas.at(i).at(1).toString();
            Category* new_category = new Category(category_name);
            new_category->addGene(gene_name);
            findGene(gene_name)->setCategory(new_category);
            category.append(new_category);
            category_sequence.append(cnt);
            cnt++;
        } else {
            findCategory(category_name)->addGene(gene_name);
            findGene(gene_name)->setCategory(findCategory(category_name));
        }
    }
}

int Circos::indexOfGene(const QString &n) {
    for(int i = 0; i < back_bone.size(); ++i) {
        if(back_bone.at(i)->name == n) {
            return i;
        }
    }
    return -1;
}

void Circos::buildBackBoneSequence(QStandardItemModel *model) {
    back_bone_sequence.clear();
    for(int i = 0; i < model->rowCount(); ++i) {
        if(model->item(i, 0)->checkState() == Qt::Checked) {
            int index = model->item(i, 0)->text().toInt() - 1;
            back_bone_sequence.append(index);
        }
    }
}

void Circos::buildBackBoneDonut(CustomDonut *donut) {
    donut->Clear();
    for(int i = 0; i < back_bone_sequence.size(); ++i) {
        int index = back_bone_sequence.at(i);

        CustomSlice *slice = new CustomSlice(back_bone.at(index)->name,
                                             back_bone.at(index)->getLength());
        slice->setBrush(QBrush(back_bone.at(index)->getFillColor()));
        slice->setPen(QPen(back_bone.at(index)->getStrikeColor()));
        slice->setLabelPosition(back_bone.at(index)->getLabelPosition());
        slice->setLabelState(back_bone.at(index)->getLabelState());
        donut->addSlice(slice);
    }
}

void Circos::buildCategoryDonut(CustomDonut *donut) {
    donut->Clear();
    for(int i = 0; i < category_sequence.size(); ++i) {
        int index = category_sequence.at(i);
        Category* c = category.at(index);
        int sum = 0;
        for(int j = 0; j < c->count(); ++j) {
            QString g = c->m_genes.at(j);
            sum += findGene(g)->getLength();
        }
        CustomSlice* slice = new CustomSlice(c->name, sum);
        donut->addSlice(slice);
    }
}

Gene* Circos::findGene(const QString name) {
    for(int i = 0; i < back_bone.size(); ++i) {
        if(back_bone.at(i)->name == name) {
            return back_bone.at(i);
        }
    }
    return new Gene;
}

Category* Circos::findCategory(const QString name) {
    for(int i = 0; i < category.size(); ++i) {
        if(category.at(i)->name == name) {
            return category.at(i);
        }
    }
    return new Category;
}

int Circos::takeGeneAt(int index) {
    return back_bone_sequence.takeAt(index);
}

void Circos::insertGene(int index, int value) {
    return back_bone_sequence.insert(index, value);
}

int Circos::takeCategoryAt(int index) {
    return category_sequence.takeAt(index);
}

void Circos::insertCategory(int index, int value) {
    return category_sequence.insert(index, value);
}

void Circos::adjustBackBoneToCategory(void) {
    back_bone_sequence.clear();
    for(auto it = category_sequence.begin(); it != category_sequence.end(); ++it) {
        for(auto it2 = category.at(*it)->begin(); it2 != category.at(*it)->end(); ++it2) {
            back_bone_sequence.append(indexOfGene(*it2));
        }
    }
}

void Circos::setCategoryEnable(bool b) {
    category_enabled = b;
}

bool Circos::getCategoryEnable(void) {
    return category_enabled;
}

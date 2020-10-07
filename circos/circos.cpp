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
            new_category->setFillColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
            new_category->setStrikeColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
            new_category->setLabelState(CustomSlice::LabelSleep);
            new_category->setLabelPosition(CustomSlice::LabelOnDonut);
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

void Circos::dataToLink(void) {
    links.clear();
    // all varibles from file
    QString source_gene_name, dest_gene_name;
    int source_gene_start, source_gene_end, dest_gene_start, dest_gene_end;
    qreal stre, lwd;

    QListIterator<QList<QVariant> > it(m_datas);
//    it.peekNext();
    QList<QVariant> data = it.next();
    while (it.hasNext()) {
        data = it.next();
        source_gene_name = data.at(0).toString();
        dest_gene_name = data.at(3).toString();

        source_gene_start = data.at(1).toInt();
        if(!data.at(2).isNull()) {
            source_gene_end = data.at(2).toInt();
        } else {
            source_gene_end = -1;
        }
        dest_gene_start = data.at(4).toInt();
        if(!data.at(5).isNull()) {
            dest_gene_end = data.at(5).toInt();
        } else {
            dest_gene_end = -1;
        }

        stre = data.at(6).toReal();
        lwd = data.at(7).toReal();

        Link* l = new Link;
        l->setSGN(source_gene_name);
        l->setDGN(dest_gene_name);
        l->setSourceStart(source_gene_start);
        if(source_gene_end > 0) {
            l->setSourceEnd(source_gene_end);
        }
        l->setDestStart(dest_gene_start);
        if(dest_gene_end > 0) {
            l->setDestEnd(dest_gene_end);
        }
        l->setStreCode(stre);
        l->setLineWidth(lwd);
        links.append(l);
        qDebug() << l->getSGN() << "---" << l->getDGN();
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

int Circos::indexOfCategory(const QString &n) {
    for(int i = 0; i < category.size(); ++i) {
        if(category.at(i)->name == n) {
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
    donut->clear();
    QListIterator<Gene*> it(back_bone);
    while (it.hasNext()) {
        Gene* g = it.next();
        g->setOnCanvas(false);
    }
    for(int i = 0; i < back_bone_sequence.size(); ++i) {
        int index = back_bone_sequence.at(i);
        Gene *g = back_bone.at(index);
        g->setOnCanvas(true);
        CustomSlice *slice = new CustomSlice(g->getName(),
                                             g->getLength());

        slice->setBrush(QBrush(g->getFillColor()));
        slice->setPen(QPen(g->getStrikeColor()));
        slice->setLabelPosition(g->getLabelPosition());
        slice->setLabelState(g->getLabelState());
        donut->addSlice(slice);
    }
}

void Circos::buildCategorySequence(QStandardItemModel *model) {
    category_sequence.clear();
//    category.clear();
    QString last_cat_name = "mm";
    Category *c = new Category;
    for(int i = 0; i < model->rowCount(); ++i) {
        if(model->item(i, 0)->checkState() == Qt::Checked) {
            QString cat_name = model->item(i, 3)->text();
            QString gene_name = model->item(i, 1)->text();
            if(cat_name == last_cat_name) {
//                findCategory(cat_name)->addGene(model->item(i, 1)->text());
                c->addGene(gene_name);
            } else {
//                Category *c = new Category(cat_name);
//                c->addGene(model->item(i, 1)->text());
//                category.append(c);
//                category_sequence.append(cnt);
//                ++cnt;
//                last_cat_name = cat_name;
                int cat_index = indexOfCategory(cat_name);
                c = category.at(cat_index);
                c->clearGenes();
                c->addGene(gene_name);
                category_sequence.append(cat_index);
//                category_sequence.append(indexofCategory(cat_name));
                last_cat_name = cat_name;
            }
        }

    }
}

void Circos::buildCategoryDonut(CustomDonut *donut) {
    donut->clear();
    for(int i = 0; i < category_sequence.size(); ++i) {
        int index = category_sequence.at(i);
        Category* c = category.at(index);
        int sum = 0;
        for(int j = 0; j < c->count(); ++j) {
            QString g = c->m_genes.at(j);
            sum += findGene(g)->getLength();
        }
        CustomSlice* slice = new CustomSlice(c->name, sum);
        slice->setBrush(QBrush(c->getFillColor()));
        slice->setPen(QPen(c->getStrikeColor()));
        slice->setLabelPosition(c->getLabelPosition());
        slice->setLabelState(c->getLabelState());
        donut->addSlice(slice);
    }
}

void Circos::buildCustomLink(CustomLinkCanvas *custom_links) {
    QListIterator<Link*> it(links);
    qDebug("buildCustomLink starts...");
    while (it.hasNext()) {
        Link* l = it.next();
        Gene* sg = findGene(l->getSGN());
        Gene* dg = findGene(l->getDGN());
        qDebug() << sg->getName() << "---" << dg->getName();
        if(sg->getOnCanvas() && dg->getOnCanvas()) { // 开始与结束的Gene均在画布上，该link才会被绘出
            qDebug("----------------------------");
            CustomLink *custom_link = new CustomLink;
            custom_link->setPen(QPen(QColor(255, 0, 0)));
            custom_link->setBrush(QBrush(QColor(255, 255, 0)));
            custom_link->setSGN(sg->getName());
            custom_link->setDGN(dg->getName());

            // key process: set the start and end position(angle) of the link
            if(l->getSourceEnd() > 0) {
                if(l->getDestEnd() > 0) {
                    custom_link->setLinkClass(CustomLink::LinkClass::Block2Block);
                } else {
                    custom_link->setLinkClass(CustomLink::LinkClass::Block2End);
                }
            } else {
                if(l->getDestEnd() > 0) {
                    custom_link->setLinkClass(CustomLink::LinkClass::End2Block);
                } else {
                    custom_link->setLinkClass(CustomLink::LinkClass::End2End);
                    int s_i_min = sg->getStart();
                    int s_i_max = dg->getEnd();
                    qreal s_r_min = dg->getStartAngle();
                    qreal s_r_max = sg->getEndAngle();
                    int value = l->getSourceStart();
                    qreal angle = CustomTool::mapInt2Real(s_i_min, s_i_max, s_r_min, s_r_max, value);
                    custom_link->setSSA(angle);

                    s_i_min = dg->getStart();
                    s_i_max = dg->getEnd();
                    s_r_min = dg->getStartAngle();
                    s_r_max = dg->getEndAngle();
                    value = l->getDestStart();
                    angle = CustomTool::mapInt2Real(s_i_min, s_i_max, s_r_min, s_r_max, value);
                    custom_link->setDSA(angle);
                }
            }

            custom_links->addCustomLink(custom_link);
        }
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

void Circos::setLinkEnable(bool b) {
    link_enabled = b;
}

bool Circos::getLinkEnable(void) {
    return link_enabled;
}

#include "circos.h"

Circos::Circos(QObject *parent) : QObject(parent) {
  back_bone.clear();
  m_datas.clear();
  back_bone_sequence.clear();
  category.clear();
  category_sequence.clear();
  category_enabled = false;
  track_arrow.clear();
}

Circos::~Circos() {
  delete this;
}

void Circos::openFile(const QString &xlsFile) {
  qDebug() << "Open file thread is :" << QThread::currentThreadId();
  m_datas.clear();
  if (xlsFile.isEmpty())
    return;
  QElapsedTimer timer;
  timer.start();
  if (m_xls.isNull())
    m_xls.reset(new ExcelBase);
  m_xls->open(xlsFile);
//    qDebug() << "open cost:" << timer.elapsed() << "ms";
  timer.restart();
  m_xls->setCurrentSheet(1);
  m_xls->readAll(m_datas);
//    qDebug() << "read data cost:" << timer.elapsed() << "ms";
  timer.restart();
  m_xls->close();
}

Circos::DataProcessState Circos::dataToBackBone(void) {
  qDebug() << "Data to BB thread is :" << QThread::currentThreadId();
  back_bone.clear();
  back_bone_sequence.clear();
  int name_index = -1;
  int start_index = -1;
  int end_index = -1;
  int length_index = -1;
  if (!m_datas.empty()) {
    for (int i = 0; i < m_datas.at(0).size(); ++i) {
      if (m_datas.at(0).at(i).toString() == "Gene name") { name_index = i; }
      else if (m_datas.at(0).at(i).toString() == "from") { start_index = i; }
      else if (m_datas.at(0).at(i).toString() == "to") { end_index = i; }
      else if (m_datas.at(0).at(i).toString() == "length") { length_index = i; }
    }
    if (name_index < 0) {
//      qDebug() << "Open Backbone Error: No 'Gene name'!!!";
      auto err_dialog = new QErrorMessage;
      err_dialog->setParent(widget);
      err_dialog->setWindowTitle(tr("Open Backbone Error"));
      err_dialog->showMessage(tr("No 'Gene name'!!!"));
      return DataProcessState::Error;
    }
    if (length_index < 0) {
      if (start_index < 0) {
//        qDebug() << "Open Backbone Error: No 'from' or 'length'!!!";
        auto err_dialog = new QErrorMessage(widget);
//        err_dialog->setParent(widget);
        err_dialog->setWindowTitle(tr("Open Backbone Error"));
        err_dialog->showMessage(tr("No 'from' or 'length'!!!"));
        return DataProcessState::Error;
      } else if (end_index < 0) {
//        qDebug() << "Open Backbone Error: 'from' exists but No 'to'!!!";

//        auto err_dialog = new QErrorMessage(widget);
////        err_dialog->setParent(widget);
//        err_dialog->setWindowTitle(tr("Open Backbone Error"));
//        err_dialog->showMessage(tr("'from' exists but No 'to'!!!"));
        QMessageBox::critical(widget,
                              tr("Open Backbone Error"),
                              tr("'from' exists but No 'to'!!!"),
                              QMessageBox::Ok);
        return DataProcessState::Error;
      }
    }
    if (length_index < 0) {
      for (int i = 1; i < m_datas.size(); ++i) {
        Gene *g = new Gene(m_datas.at(i).at(name_index).toString(),
                           m_datas.at(i).at(start_index).toUInt(),
                           m_datas.at(i).at(end_index).toUInt());
        g->setFillColor(QColor(Qt::white));
        g->setStrikeColor(QColor(Qt::black));
        g->setLabelState(CustomSlice::LabelSleep);
        g->setLabelPosition(CustomSlice::LabelOnDonut);
        back_bone.append(g);
        back_bone_sequence.append(i - 1);
      }
    } else {
      for (int i = 1; i < m_datas.size(); ++i) {
        Gene *g = new Gene(m_datas.at(i).at(name_index).toString(),
                           m_datas.at(i).at(length_index).toUInt());
        g->setFillColor(QColor(Qt::white));
        g->setStrikeColor(QColor(Qt::black));
        back_bone.append(g);
        back_bone_sequence.append(i - 1);
      }
    }
  }
  return DataProcessState::Success;
}

Circos::DataProcessState Circos::dataToCategory(void) {
  category_enabled = true;
  category.clear();
  category_sequence.clear();
  QString category_name;
  QString gene_name;
  if (!m_datas.empty()) {
    int name_index = -1;
    int sys_index = -1;
    for (int i = 0; i < m_datas.at(0).size(); ++i) {
      if (m_datas.at(0).at(i).toString() == "Gene name") {
        name_index = i;
      } else if (m_datas.at(0).at(i).toString() == "System") {
        sys_index = i;
      }
    }
    if (name_index < 0) {
      QMessageBox::critical(widget,
                            tr("Open Category Error"),
                            tr("no \'Gene name\' item."),
                            QMessageBox::Ok);
      return DataProcessState::Error;
    } else if (sys_index < 0) {
      QMessageBox::critical(widget,
                            tr("Open Category Error"),
                            tr("no \'System\' item."),
                            QMessageBox::Ok);
      return DataProcessState::Error;
    }
    for (int i = 1, cnt = 0; i < m_datas.size(); ++i) {
      gene_name = m_datas.at(i).at(name_index).toString();
      if (!m_datas.at(i).at(sys_index).isNull()) {
        category_name = m_datas.at(i).at(sys_index).toString();
        Category *new_category = new Category(category_name);
        new_category->addGene(gene_name);
//        new_category->setFillColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
//        new_category->setStrikeColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
        QColor lightgray = QColor(Qt::lightGray);
        lightgray.setAlphaF(0.3);
        new_category->setFillColor(QColor(lightgray));
        new_category->setStrikeColor(QColor(Qt::white));
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
  return DataProcessState::Success;
}

Circos::DataProcessState Circos::dataToLink(void) {
  links.clear();
  // all varibles from file
  QString source_gene_name, dest_gene_name;
  int source_gene_start, source_gene_end, dest_gene_start, dest_gene_end;
  qreal stre, lwd;
  int stre_index = -1, lwd_index = -1;
  int gene1_index = -1, gene2_index = -1;
  int start1_index = -1, end1_index = -1;
  int start2_index = -1, end2_index = -1;
  if (!m_datas.empty()) {
    QListIterator<QList<QVariant> > it(m_datas);
//    it.peekNext();
    QList<QVariant> data = it.next();
    for (int i = 0; i < data.size(); ++i) {
      if (data.at(i).toString().toUpper().compare("STRE") == 0) {
        stre_index = i;
      } else if (data.at(i).toString().toUpper().compare("LWD") == 0) {
        lwd_index = i;
      } else if (data.at(i).toString().toUpper().compare("GENE1") == 0) {
        gene1_index = i;
      } else if (data.at(i).toString().toUpper().compare("START1") == 0) {
        start1_index = i;
      } else if (data.at(i).toString().toUpper().compare("END1") == 0) {
        end1_index = i;
      } else if (data.at(i).toString().toUpper().compare("GENE2") == 0) {
        gene2_index = i;
      } else if (data.at(i).toString().toUpper().compare("START2") == 0) {
        start2_index = i;
      } else if (data.at(i).toString().toUpper().compare("END2") == 0) {
        end2_index = i;
      }
    }
    if (gene1_index < 0) {
      QMessageBox::critical(widget,
                            tr("Open Link Error"),
                            tr("no \'GENE1\' item."),
                            QMessageBox::Ok);
      return DataProcessState::Error;
    } else if (gene2_index < 0) {
      QMessageBox::critical(widget,
                            tr("Open Link Error"),
                            tr("no \'GENE2\' item."),
                            QMessageBox::Ok);
      return DataProcessState::Error;
    }
    while (it.hasNext()) {
      data = it.next();
      source_gene_name = data.at(gene1_index).toString();
      dest_gene_name = data.at(gene2_index).toString();
      source_gene_start = data.at(start1_index).toInt();
      if (!data.at(end1_index).isNull()) {
        source_gene_start = qMin(data.at(start1_index).toInt(), data.at(end1_index).toInt());
        source_gene_end = qMax(data.at(start1_index).toInt(), data.at(end1_index).toInt());
      } else {
        source_gene_end = -1;
      }
      dest_gene_start = data.at(start2_index).toInt();
      if (!data.at(end2_index).isNull()) {
        dest_gene_start = qMax(data.at(start2_index).toInt(), data.at(end2_index).toInt());
        dest_gene_end = qMin(data.at(start2_index).toInt(), data.at(end2_index).toInt());
      } else {
//            qDebug() << source_gene_name << "----" << dest_gene_name << " empty";
        dest_gene_end = -1;
      }
      if (stre_index >= 0) {
        if (data.at(stre_index).isValid()) {
          stre = data.at(stre_index).toReal();
        } else {
          stre = 1.0;
        }
      }
      if (stre <= link_stre_min) {
        setLinkStre(stre, link_stre_max);
      }
      if (stre >= link_stre_max) {
        setLinkStre(link_stre_min, stre);
      }
      if (lwd_index >= 0) {
        lwd = data.at(lwd_index).toReal();
      } else {
        lwd = 1.0;
      }

      Link *l = new Link;
      l->setSGN(source_gene_name);
      findGene(source_gene_name)->addLink(l, "start");
      l->setDGN(dest_gene_name);
      findGene(dest_gene_name)->addLink(l, "end");
      l->setSourceStart(source_gene_start);
      if (source_gene_end > 0) {
        l->setSourceEnd(source_gene_end);
      }
      l->setDestStart(dest_gene_start);
      if (dest_gene_end > 0) {
        l->setDestEnd(dest_gene_end);
      }
      l->setStreCode(stre);
      l->setLineWidth(lwd);
      links.append(l);
//    connect(l,&Link::setColorFun
//        qDebug() << l->getSGN() << "---" << l->getDGN();
    }
  }
  return DataProcessState::Success;
}

Circos::DataProcessState Circos::dataToTrackArrow(void) {
  track_arrow.clear();
  if (!m_datas.empty()) {
    qDebug() << "TrackArrow Numbers: " << m_datas.size();
    int start_index = -1;
    int end_index = -1;
    int name_index = -1;
    int direction_index = -1;
    for (int i = 0; i < m_datas[0].size(); ++i) {
      QString str = m_datas[0][i].toString();
      if (str == "geneStart") { start_index = i; }
      else if (str == "geneEnd") { end_index = i; }
      else if (str == "Gene name") { name_index = i; }
      else if (str == "Direction") { direction_index = i; }
    }
    if (start_index < 0) {
      QMessageBox::critical(widget,
                            tr("Open TrackArrow Error"),
                            tr("no \'geneStart\' item."),
                            QMessageBox::Ok);
      return DataProcessState::Error;
    } else if (end_index < 0) {
      QMessageBox::critical(widget,
                            tr("Open TrackArrow Error"),
                            tr("no \'geneEnd\' item."),
                            QMessageBox::Ok);
      return DataProcessState::Error;
    } else if (name_index < 0) {
      QMessageBox::critical(widget,
                            tr("Open TrackArrow Error"),
                            tr("no \'Gene name\' item."),
                            QMessageBox::Ok);
      return DataProcessState::Error;
    }
    QList<QVariant> data;
    if (direction_index < 0) {
      track_arrow_type = TrackArrow::Type::Tile;
    } else {
      track_arrow_type = TrackArrow::Type::Arrow;
    }
    m_datas.removeAt(0);
      foreach (data, m_datas) {
        TrackArrow *ta = new TrackArrow;
        ta->setTypes(track_arrow_type);
        if (direction_index < 0) {
//      qDebug("this is tile file.");
//          ta->setDirections(TrackArrow::Direction::None);
//          ta->setTypes(TrackArrow::Type::Tile);
        } else {
//          ta->setTypes(TrackArrow::Type::Arrow);
          if (data.at(direction_index).toString().compare("+") == 0) {
            ta->setDirections(TrackArrow::Direction::ClockWise);
          } else {
            ta->setDirections(TrackArrow::Direction::AntiClockWise);
          }
        }
        ta->setName(data.at(name_index).toString());
        ta->setEnd(data.at(end_index).toInt());
        ta->setStart(data.at(start_index).toInt());
        track_arrow.append(ta);
      }
  }
  return DataProcessState::Success;
}

int Circos::indexOfGene(const QString &n) {
  for (int i = 0; i < back_bone.size(); ++i) {
    QString name = getGene(i)->getName();
    if (name == n) {
      return i;
    }
  }
  return -1;
}

int Circos::indexOfCategory(const QString &n) {
  for (int i = 0; i < category.size(); ++i) {
    if (category.at(i)->getName() == n) {
      return i;
    }
  }
  return -1;
}

void Circos::buildBackBoneSequence(QStandardItemModel *model) {
  back_bone_sequence.clear();
  qDebug() << "Row Cnt=" << model->rowCount();
  qDebug() << "Proceeding to " << __FILE__ << "in Line " << __LINE__;
  for (int i = 0; i < model->rowCount(); ++i) {
    if (model->item(i, 0)->checkState() == Qt::Checked) {
      int index = model->item(i, 0)->text().toInt() - 1;
      back_bone_sequence.append(index);
    }
  }
}

void Circos::buildBackBoneDonut(CustomDonut *donut) {
  donut->clear();
  QListIterator<Gene *> it(back_bone);
  while (it.hasNext()) {
    Gene *g = it.next();
    g->setOnCanvas(false);
  }
  QString next_cat_name_;
  for (int i = 0; i < back_bone_sequence.size(); ++i) {
    int index = back_bone_sequence.at(i);
    Gene *g = back_bone.at(index);
    g->setOnCanvas(true);
    CustomSlice *slice = new CustomSlice(g->getName(),
                                         g->getLength());
//    slice->setBrush(QBrush(g->getFillColor()));
//    slice->setPen(QPen(g->getStrikeColor()));
    slice->setBrush(QBrush(g->getFillColor()));
    slice->setPen(QPen(g->getStrikeColor()));
    slice->setLabelPosition(g->getLabelPosition());
    slice->setLabelState(g->getLabelState());
    int next_index = i + 1;
    if (next_index == back_bone_sequence.size()) {
      next_index = 0;
    }
    next_cat_name_ = back_bone.at(getBackBoneSequence(next_index))->getCategory()->getName();
    if (g->getCategory()->getName() == next_cat_name_) {
      qDebug() << "Current name: " << g->getCategory()->getName() << " ==" << next_cat_name_;
      slice->setGap(back_bone_gap);
    } else {
      qDebug() << "Current name: " << g->getCategory()->getName() << " !=" << next_cat_name_;
      slice->setGap(category_gap);
    }
//    next_cat_name_ = g->getCategory()->getName();
//    donut->setGaps(back_bone_gap);
//    slice->setSize(back_bone_inner_radius, back_bone_outer_radius);
    donut->addSlice(slice);
  }
//  donut->setGaps(back_bone_gap);
  donut->setSize(back_bone_inner_radius, back_bone_outer_radius);
}

void Circos::buildCategorySequence(QStandardItemModel *model) {
  category_sequence.clear();
//    category.clear();
  QString last_cat_name = "mm";
  Category *c = new Category;
  for (int i = 0; i < model->rowCount(); ++i) {
    if (model->item(i, 0)->checkState() == Qt::Checked) {
      QString cat_name = model->item(i, 3)->text();
      QString gene_name = model->item(i, 1)->text();
      if (cat_name == last_cat_name) {
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
//  donut->setSize(category_inner_raidus, category_outer_radius);
  for (int i = 0; i < category_sequence.size(); ++i) {
    int index = category_sequence.at(i);
    Category *c = category.at(index);
    int sum = 0;
    for (int j = 0; j < c->count(); ++j) {
      QString g = c->getGenes().at(j);
      sum += findGene(g)->getLength();
    }
    CustomSlice *slice = new CustomSlice(c->getName(), sum);
    slice->setBrush(QBrush(c->getFillColor()));
    slice->setPen(QPen(c->getStrikeColor()));
    slice->setLabelPosition(c->getLabelPosition());
    slice->setLabelState(c->getLabelState());
    slice->setGap(category_gap);
    donut->addSlice(slice);
  }
//  donut->setGaps(category_gap);
  donut->setSize(category_inner_raidus, category_outer_radius);
}

void Circos::buildCustomLink(CustomLinkCanvas *custom_links) {
  custom_links->clearLinks();
  QListIterator<Link *> it(links);
  custom_links->setLinkType(link_type);
  custom_links->setArrowDirection(link_arrow_direction);
  custom_links->setLineStyle(link_line_style);
  custom_links->setLineWidth(link_line_width);
//    qDebug("buildCustomLink starts...");
  while (it.hasNext()) {
    Link *l = it.next();
    if (l->getEnable()) {
      Gene *sg = findGene(l->getSGN());
      Gene *dg = findGene(l->getDGN());
      if (sg->getOnCanvas() && dg->getOnCanvas()) {
        CustomLink *custom_link = new CustomLink;
//            custom_link->setLinkDirection(link_arrow_direction);
        // key process: set the start and end position(angle) of the link
        // start link
        int s_i_min = sg->getStart();
        int s_i_max = sg->getEnd();
        qreal s_r_min = sg->getStartAngle();
        qreal s_r_max = sg->getEndAngle();
        int value = l->getSourceStart();
        qreal source_start_angle = CustomTool::mapInt2Real(s_i_min, s_i_max, s_r_min, s_r_max, value);
        s_i_min = dg->getStart();
        s_i_max = dg->getEnd();
        s_r_min = dg->getStartAngle();
        s_r_max = dg->getEndAngle();
        value = l->getDestStart();
        qreal dest_start_angle = CustomTool::mapInt2Real(s_i_min, s_i_max, s_r_min, s_r_max, value);
        qreal source_end_angle = source_start_angle;
        qreal dest_end_angle = dest_start_angle;
        bool source_mul = false, end_mul = false;
        if (l->getSourceEnd() > 0) {
          source_mul = true;
          s_i_min = sg->getStart();
          s_i_max = sg->getEnd();
          s_r_min = sg->getStartAngle();
          s_r_max = sg->getEndAngle();
          value = l->getSourceEnd();
          source_end_angle = CustomTool::mapInt2Real(s_i_min, s_i_max, s_r_min, s_r_max, value);
        }
        if (l->getDestEnd() > 0) {
          end_mul = true;
          s_i_min = dg->getStart();
          s_i_max = dg->getEnd();
          s_r_min = dg->getStartAngle();
          s_r_max = dg->getEndAngle();
          value = l->getDestEnd();
          dest_end_angle = CustomTool::mapInt2Real(s_i_min, s_i_max, s_r_min, s_r_max, value);
        }
        CustomLink::LinkClasses lc = CustomLink::LinkClass::End2End;
        if (source_mul && end_mul) {
          lc = CustomLink::LinkClass::Block2Block;
        } else if (source_mul) {
          lc = CustomLink::LinkClass::Block2End;
        } else if (end_mul) {
          lc = CustomLink::LinkClass::End2Block;
        }
//      Link::ColorFuns cf = l->getColorFun();
//      if(cf.testFlag(Link::ColorFun::Ramp)) {
//      } else if(cf.testFlag(Link::ColorFun::Rainbow)) {
//      } else {
//                  qreal stre_code = circos->getLinkStre(index);
//                  QColor c = QColor(link_gradient->color(stre_code,
//                                                         QCPRange(circos->getLinkStreMin(),
//                                                             circos->getLinkStreMax())));
//                  emit setLinkColor(index, c);
//          l->set
//      }


//        Link::ColorFuns cf = l->getColorFun();
//        if (cf.testFlag(Link::ColorFun::Ramp)) {
//          qreal stre_code = l->getStreCode();
//          QColor c = QColor(link_gradient->color(stre_code,
//                                                 QCPRange(getLinkStreMin(), getLinkStreMax())));
//          l->setColor(c);
//        } else if (cf.testFlag(Link::ColorFun::Rainbow)) {
//          switch (qrand() % 5) {
//            case 0:l->setColor(Qt::blue);
//              break;
//            case 1:l->setColor(Qt::green);
//              break;
//            case 2:l->setColor(Qt::yellow);
//              break;
//            case 3:l->setColor(Qt::red);
//              break;
//            case 4:l->setColor(Qt::darkRed);
//              break;
//            default:break;
//          }
//        } else {
//          l->setColor(Qt::black);
//        }
        custom_link->setLineWidth(1);
        custom_link->setLinkClass(lc);
        custom_link->setHoleSize(getLKHole());
        custom_link->setPieSize(getLKPie());
        custom_link->setPen(QPen(l->getColor()));
        custom_link->setBrush(QBrush(l->getColor()));
        custom_link->setSGN(sg->getName());
        custom_link->setDGN(dg->getName());
        custom_link->setSSA(source_start_angle);
        custom_link->setDSA(dest_start_angle);
        custom_link->setSEA(source_end_angle);
        custom_link->setDEA(dest_end_angle);
        custom_links->addCustomLink(custom_link);
      }
    }
  }
}

void Circos::buildCustomTrack(CustomTrackArrow *track) {
  track->clearArrow();
  track->setType(CustomTrackArrow::Type::Arrow);
  foreach(TrackArrow * it, track_arrow)
  {
    CustomTrack *tr = new CustomTrack;
    Gene *g = findGene(it->getName());
    if (g->getOnCanvas()) {
//      track->addArrow(tr);
      int int_min = g->getStart();
      int int_max = g->getEnd();
      qreal real_min = g->getStartAngle();
      qreal real_max = g->getEndAngle();
      qreal start = CustomTool::mapInt2Real(int_min, int_max,
                                            real_min, real_max,
                                            it->getStart());
      qreal end = CustomTool::mapInt2Real(int_min, int_max,
                                          real_min, real_max,
                                          it->getEnd());
//      qDebug("int_min:%d, int_max:%d, real_min:%.3f, real_max:%.3f", int_min, int_max, real_min, real_max);
//      qDebug("values:%d, valuee:%d, start:%.4f, end:%.4f", it->getStart(), it->getEnd(), start, end);
//      tr->setStart(start);
//      tr->setEnd(end);
//        if (it->getTypes().testFlag(TrackArrow::Type::Arrow)) {
      if (track_arrow_type.testFlag(TrackArrow::Type::Arrow)) {
        track->setType(CustomTrackArrow::Type::Arrow);
//          qreal boud = CustomTool::mapInt2Real(100, 0, start, end, 100 * it->getHeadRatio());
        qreal boud = CustomTool::mapInt2Real(100, 0, start, end, 100 * track_head_ratio);
        if (it->getDirections().testFlag(TrackArrow::Direction::ClockWise)) {
          tr->setDirection(CustomTrack::ArrowDirection::ClockWise);
          tr->setStart(qMin(start, end));
          tr->setEnd(qMax(start, end));
        } else {
//            boud = CustomTool::mapInt2Real(100, 0, end, start, 100 * it->getHeadRatio());
          boud = CustomTool::mapInt2Real(100, 0, end, start, 100 * track_head_ratio);
          tr->setDirection(CustomTrack::ArrowDirection::AntiClockWise);
          tr->setStart(qMax(start, end));
          tr->setEnd(qMin(start, end));
        }
        tr->setBoundary(boud);
        tr->setType(CustomTrack::Type::Arrow);
      } else {
        tr->setType(CustomTrack::Type::Tile);
        track->setType(CustomTrackArrow::Type::Tile);

        tr->setStart(qMin(start, end));
        tr->setEnd(qMax(start, end));

//        qDebug("this is tile");
      }
      qreal margin = 0.5 * (1.0 - track_head_width);
      qreal range = getTAPie() - getTAHole();
      qreal offset = margin * range;
      tr->setHoleSize(getTAHole() + offset);
      tr->setPieSize(getTAPie() - offset);
      margin = 0.5 * (1.0 - track_tail_width);
      range = getTAPie() - getTAHole();
      offset = margin * range;
      tr->setInnerTail(getTAHole() + offset);
      tr->setOuterTail(getTAPie() - offset);
      tr->setColor(track_color);
      track->addArrow(tr);
    }
  }
}

void Circos::reset() {
  clearBackBone();
  clearBackBoneSequence();
  clearCategory();
  clearCategorySequence();
  clearLink();
  clearTrackArrow();
}

Gene *Circos::findGene(const QString name) {
  QListIterator<Gene *> it(back_bone);
  while (it.hasNext()) {
    Gene *g = it.next();
    if (g->getName().compare(name) == 0) {
      return g;
    }
  }
  return new Gene;
}

Category *Circos::findCategory(const QString name) {
  for (int i = 0; i < category.size(); ++i) {
    if (category.at(i)->getName() == name) {
      return category.at(i);
    }
  }
  return new Category;
}

Category *Circos::getCategory(int index) { return category.at(index); }

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
  for (auto it = category_sequence.begin(); it != category_sequence.end(); ++it) {
    for (auto it2 = category.at(*it)->begin(); it2 != category.at(*it)->end(); ++it2) {
      back_bone_sequence.append(indexOfGene(*it2));
    }
  }
}

void Circos::clearCategory(void) {
  category.clear();
  category_enabled = false;
}

void Circos::clearCategorySequence(void) {
  category_sequence.clear();
}

int Circos::getCategoryNum() { return category.size(); }

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

void Circos::setLinkColorFunStr(int index, const QString &cf) {
  getLink(index)->setColorFunString(cf);
}

QString Circos::getLinkColorFunStr(int index) {
  return getLink(index)->getColorFunString();
}

void Circos::setLinkColorFunc(int index, Link::ColorFuns cf, QColor c) {
  if (cf.testFlag(Link::ColorFun::Ramp)) {
    for (auto &l:links) {
      qreal stre_code = l->getStreCode();
      QColor c = QColor(link_gradient->color(stre_code,
                                             QCPRange(getLinkStreMin(), getLinkStreMax())));
      l->setColor(c);
    }
    qDebug() << "This is Link::ColorFun::Ramp";
  } else if (cf.testFlag(Link::ColorFun::All)) {
    for (auto &l:links) { l->setColor(c); }
    qDebug() << "This is Link::ColorFun::All";
  } else if (cf.testFlag(Link::ColorFun::Single)) {
    getLink(index)->setColor(c);
    qDebug() << "This is Link::ColorFun::Single";
  } else if (cf.testFlag(Link::ColorFun::Gene)) {
    Link *l = getLink(index);
    qDebug() << "This is Link::ColorFun::Gene";
    if (cf.testFlag(Link::ColorFun::Start)) {
      Gene *g = findGene(l->getSGN());
      auto ls = g->getStartLinks();
      for (auto &l_i:ls) { l_i->setColor(c); }
      qDebug() << "This is Link::ColorFun::Start";
    }
    if (cf.testFlag(Link::ColorFun::End)) {
      Gene *g = findGene(l->getDGN());
      auto ls = g->getEndLinks();
      for (auto &l_i:ls) { l_i->setColor(c); }
      qDebug() << "This is Link::ColorFun::End";
    }
  } else if (cf.testFlag(Link::ColorFun::Category)) {
    Link *l = getLink(index);
    qDebug() << "This is Link::ColorFun::Category";
    if (cf.testFlag(Link::ColorFun::Start)) {
      Gene *g1 = findGene(l->getSGN());
      Category *cat = g1->getCategory();
      auto gs_n = cat->getGenes();
      for (auto &g_n:gs_n) {
        Gene *g = findGene(g_n);
        auto ls = g->getStartLinks();
        for (auto &l_i:ls) { l_i->setColor(c); }
      }
      qDebug() << "This is Link::ColorFun::Start";
    }
    if (cf.testFlag(Link::ColorFun::End)) {
      Gene *g1 = findGene(l->getDGN());
      Category *cat = g1->getCategory();
      auto gs_n = cat->getGenes();
      for (auto &g_n:gs_n) {
        Gene *g = findGene(g_n);
        auto ls = g->getStartLinks();
        for (auto &l_i:ls) { l_i->setColor(c); }
      }
      qDebug() << "This is Link::ColorFun::End";
    }
  }
}

void Circos::setLinkColorFunc(int index, Link::ColorFuns cf) {
  getLink(index)->setColorFun(cf);
}

void Circos::setLinkColorFunc(Link::ColorFuns cf) { color_funs_ = cf; }

Link::ColorFuns Circos::getLinkColorFunc(int index) {
  return getLink(index)->getColorFun();
}

Link::ColorFuns Circos::getLinkColorFunc(void) { return color_funs_; }

void Circos::setLinkColorName(int index, const QString &name) {
  getLink(index)->setColorName(name);
}

QString Circos::getLinkColorName(int index) {
  return getLink(index)->getColorName();
}

//void Circos::setLinkColorCode(int index, qreal code) {
//  getLink(index)->setColorCode(code);
//}

//qreal Circos::getLinkColorCode(int index) {
//  return getLink(index)->getColorCode();
//}

void Circos::setLinkLineStyle(Qt::PenStyle ps) {
  link_line_style = ps;
}

Qt::PenStyle Circos::getLinkLineStyle(void) {
  return link_line_style;
}

void Circos::setLinkType(CustomLinkCanvas::LinkTypes
                         lt) {
  link_type = lt;
}

CustomLinkCanvas::LinkTypes Circos::getLinkType(void) {
  return link_type;
}

void Circos::setLinkArrowDirection(CustomLink::LinkDirections ad) {
  link_arrow_direction = ad;
}

CustomLink::LinkDirections Circos::getLinkArrowDirection(void) {
  return link_arrow_direction;
}

qreal Circos::getLinkLineWidth(void) {
  return link_line_width;
}

void Circos::setLinkStre(qreal min, qreal max) {
  link_stre_max = max;
  link_stre_min = min;
}

qreal Circos::getLinkStre(int index) {
  return getLink(index)->getStreCode();
}

qreal Circos::getLinkStreMax(void) {
  return link_stre_max;
}

qreal Circos::getLinkStreMin(void) {
  return link_stre_min;
}

QCPRange *Circos::getLinkStreRange(void) {
  return new QCPRange(link_stre_min, link_stre_max);
}

void Circos::setLinkGradient(QCPColorGradient *g) {
  link_gradient = g;
}

QCPColorGradient *Circos::getLinkGradient(void) {
  return link_gradient;
}

void Circos::setLinkLineWidth(qreal w) {
  link_line_width = w;
}

Gene *Circos::getGene(int index) {
  return back_bone.at(index);
}

void Circos::clearBackBone(void) {
  back_bone.clear();
}

void Circos::clearBackBoneSequence(void) {
  back_bone_sequence.clear();
}

void Circos::appendBackBoneSequence(int index) {
  back_bone_sequence.append(index);
}

int Circos::getBackBoneSequence(int index) {
  return back_bone_sequence.at(index);
}

int Circos::getGeneNum(void) {
  return back_bone.size();
}

Link *Circos::getLink(int index) {
  return links.at(index);
}

int Circos::getLinkNum(void) {
  return links.size();
}

void Circos::clearLink(void) {
  links.clear();
  link_enabled = false;
}

void Circos::setTrackEnabled(bool b) {
  track_enabled = b;
}

bool Circos::getTrackEnabled(void) {
  return track_enabled;
}

void Circos::clearTrackArrow(void) {
  track_arrow.clear();
  track_enabled = false;
}

QList<TrackArrow *> Circos::getTrackArrow(void) {
  return track_arrow;
}

void Circos::onGeneAngleChanged(const QString &n, qreal s, qreal e) {
  findGene(n)->setAngle(s, e);
}

//void Circos::onLinkColorSet(int index, QColor c) {
//  getLink(index)->setColor(c);
//}

void Circos::onLinkColorFuncChanged(int index) {
  Link::ColorFuns cf = getLinkColorFunc(index);
  if (cf.testFlag(Link::ColorFun::Ramp)) {
  } else if (cf.testFlag(Link::ColorFun::Rainbow)) {
  } else {
    qreal stre_code = getLinkStre(index);
    QColor c = QColor(link_gradient->color(stre_code,
                                           QCPRange(getLinkStreMin(), getLinkStreMax())));
//    emit setLinkColor(index, c);
    getLink(index)->setColor(c);
  }
}

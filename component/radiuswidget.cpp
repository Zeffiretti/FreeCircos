//
// Created by Hiesh on 2021/6/17.
//

#include "freecircos.h"

void FreeCircos::initRadiusWidget(void) {
  gbset_win = new GlobalSetWin(circos, this);
  GlobalSetWin::Component component = GlobalSetWin::ComponentEnable::AllDisable;
  component |= GlobalSetWin::ComponentEnable::BackBone;
  if (circos->getCategoryEnable()) {
    component |= GlobalSetWin::ComponentEnable::Catgory;
  }
  if (circos->getTrackEnabled()) {
    component |= GlobalSetWin::ComponentEnable::TrackArrow;
  }
  if (circos->getLinkEnable()) {
    component |= GlobalSetWin::ComponentEnable::Link;
  }
  gbset_win->setComponents(component);
  gbset_win->setBbPos(circos->getBBPie(), circos->getBBHole());
  gbset_win->setCatPos(circos->getCGPie(), circos->getCGHole());
  gbset_win->setTrkPos(circos->getTAPie(), circos->getTAHole());
  gbset_win->setLinkPos(circos->getLKPie(), circos->getLKHole());
  gbset_win->show();
  gb_active = true;
  connect(gbset_win, &GlobalSetWin::closeSet,
          this, &FreeCircos::onWindowClosed);
//
//  connect(gbset_win, &GlobalSetWin::BBInnerRadiusChanged,
//          circos, &Circos::setBBHole);
//  connect(gbset_win, &GlobalSetWin::BBOuterRadiusChanged,
//          circos, &Circos::setBBPie);
//  connect(gbset_win, &GlobalSetWin::CatInnerRadiusChanged,
//          circos, &Circos::setCGHole);
//  connect(gbset_win, &GlobalSetWin::CatOuterRadiusChanged,
//          circos, &Circos::setCGPie);
//  connect(gbset_win, &GlobalSetWin::ARWInnerRadiusChanged,
//          circos, &Circos::setTAHole);
//  connect(gbset_win, &GlobalSetWin::ARWOuterRadiusChanged,
//          circos, &Circos::setTAPie);
//  connect(gbset_win, &GlobalSetWin::LinkInnerRadiusChanged,
//          circos, &Circos::setLKHole);
//  connect(gbset_win, &GlobalSetWin::LinkOuterRadiusChanged,
//          circos, &Circos::setLKPie);
}


#include "freecircos.h"

#include "ui_freecircos.h"

FreeCircos::FreeCircos(QWidget *parent)
  : QMainWindow(parent), ui(new Ui::FreeCircos) {
  ui->setupUi(this);
//  setWindowFlags(flags);
  setMinimumSize(1610, 650);
  setMaximumSize(1610, 650);
  this->setGeometry(200, 200, 1610, 650);
  major_font = new QFont;
  major_font->setFamily("Microsoft Yahei UI");
  major_font->setPixelSize(14);
//  major_font->setPointSize(10);
  major_font->setBold(true);
  //init canvas
  initCanvas();
  //init generate button
  initGenerateButton();
  gene_donut = new CustomDonut;
  category_donut = new CustomDonut;
  link_canvas = new CustomLinkCanvas;
  track_canvas = new CustomTrackArrow;
  circos = new Circos;
  table_edit_mode = EditGene;
  connect(gene_donut, &CustomDonut::sliceAngleChanged,
          circos, &Circos::onGeneAngleChanged);
  QPushButton *backbone_button = new QPushButton;
  backbone_button->setParent(this);
  backbone_button->setText("backbone");
  backbone_button->setGeometry(10, 10, 100, 40);
  backbone_button->setProperty("function", "openbackbonefile");
  backbone_button->setVisible(true);
  connect(backbone_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
  QPushButton *category_button = new QPushButton;
  category_button->setParent(this);
  category_button->setText("category");
  category_button->setGeometry(120, 10, 100, 40);
  category_button->setProperty("function", "opencategoryfile");
  category_button->setVisible(true);
  connect(category_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
  QPushButton *link_button = new QPushButton;
  link_button->setParent(this);
  link_button->setText("link");
  link_button->setGeometry(10, 60, 100, 40);
  link_button->setProperty("function", "openlinkfile");
  link_button->setVisible(true);
  connect(link_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
  QPushButton *trackarrow_button = new QPushButton;
  trackarrow_button->setParent(this);
  trackarrow_button->setText("trackarrow");
  trackarrow_button->setGeometry(120, 60, 100, 40);
  trackarrow_button->setProperty("function", "opentrackarrowfile");
  trackarrow_button->setVisible(true);
  connect(trackarrow_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
  QPushButton *setting_button = new QPushButton;
  setting_button->setParent(this);
  setting_button->setText("Global Setting");
  setting_button->setGeometry(230, 10, 100, 40);
  setting_button->setProperty("prefix", "global");
  setting_button->setProperty("function", "globalsetting");
  connect(setting_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
  QPushButton *save_button = new QPushButton;
  save_button->setParent(this);
  save_button->setText("Save");
  save_button->setProperty("function", "saveimage");
  save_button->setGeometry(230, 60, 100, 40);
  connect(save_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
//    QElapsedTimer timer;
//    timer.start();
//    int size = 50;
//    for (int i = 0; i < size; ++i) {
//        int value = qrand() % 10000;
//        CustomSlice *slice = new CustomSlice(QString("%1").arg(value), value);
//        gene_donut->addSlice(slice);
//    }
//    qDebug() << "Elapsed time1: " << timer.elapsed() << " ms";
//    timer.restart();
//    QVector<QColor> colors;
//    colors.resize(size);
//    std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
//    QList<QColor> strike_colors = colors.toList();
//    gene_donut->setPens(strike_colors);
//    std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
//    QList<QColor> fill_colors = colors.toList();
//    gene_donut->setBrushes(fill_colors);
//    gene_donut->setSize(0.7, 0.8);
//    gene_donut->drawDonut(canvas);
//    qDebug() << "Elapsed time2: " << timer.elapsed() << " ms";
//    timer.restart();
//    canvas->replot();
//    qDebug() << "Elapsed time3: " << timer.elapsed() << " ms";
//    timer.restart();
  control_panel = new QTabWidget;
  control_panel->setParent(this);
  control_panel->setGeometry(600, 30, 1000, 600);
  initBackBoneWidget(control_panel);
  initLinkWidget(control_panel);
  //qDebug() << CustomTool::mapInt2Real(202293916, 202585582, 0, 1, 202417563);
//    qDebug() << QColor(Qt::red).name();
}

FreeCircos::~FreeCircos() {
  delete ui;
}

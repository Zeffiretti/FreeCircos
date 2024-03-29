#include "freecircos.h"

#include "ui_freecircos.h"
qreal g_scale;
FreeCircos::FreeCircos(QWidget *parent)
  : QMainWindow(parent), ui(new Ui::FreeCircos) {
  QDesktopWidget *desktopWidget = QApplication::desktop();
  QRect screenRect = desktopWidget->screenGeometry();
  int w = screenRect.width();
  int h = screenRect.height();
  ui->setupUi(this);
//  setWindowFlags(flags);
//  if (g_app_base_width * g_scale > 0.8 * w) {
  g_scale = 0.85 * w / g_app_base_width;
//  }
  if (g_app_base_height * g_scale > 0.6 * h) {
    g_scale = 0.6 * h / g_app_base_height;
  }
  setMinimumSize(g_app_base_width * g_scale, g_app_base_height * g_scale);
  setMaximumSize(g_app_base_width * g_scale, g_app_base_height * g_scale);
  this->setGeometry(w / 15, h / 5, g_app_base_width * g_scale, g_app_base_height * g_scale);
  major_font = new QFont;
//  major_font->setFamily("Microsoft Yahei UI");
//  major_font->setPixelSize(14);
////  major_font->setPointSize(10);
//  major_font->setBold(true);
  //init canvas
  initCanvas();//deprecate
  //init generate button
  initGenerateButton();
//  painter = new CustomPainter;
  gene_donut = new CustomDonut;
  category_donut = new CustomDonut;
  link_canvas = new CustomLinkCanvas;
  track_canvas = new CustomTrackArrow;
  circos = new Circos;
//  canvas = new QCustomPlot;
//  painter->initCanvas(this,
//                      g_scale * canvas_pos_x,
//                      g_scale * canvas_pos_y,
//                      g_scale * canvas_width,
//                      g_scale * canvas_height);
  circos->setWidget(this);
  table_edit_mode = EditGene;
  connect(gene_donut, &CustomDonut::sliceAngleChanged,
          circos, &Circos::onGeneAngleChanged);//deprecate
//  connect(painter->getGeneDonut(), &CustomDonut::sliceAngleChanged,
//          circos, &Circos::onGeneAngleChanged);//deprecate
  QPushButton *backbone_button = new QPushButton;
  backbone_button->setParent(this);
  backbone_button->setText("backbone");
  backbone_button->setGeometry(button_box_pos_x * g_scale, button_box_pos_y * g_scale,
                               button_box_width * g_scale, button_box_height * g_scale);
  backbone_button->setProperty("function", "openbackbonefile");
  backbone_button->setVisible(true);
  connect(backbone_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
  QPushButton *category_button = new QPushButton;
  category_button->setParent(this);
  category_button->setText("category");
  category_button->setGeometry(g_scale * (button_box_pos_x + button_box_width + button_gap_x),
                               g_scale * button_box_pos_y,
                               button_box_width * g_scale,
                               button_box_height * g_scale);
  category_button->setProperty("function", "opencategoryfile");
  category_button->setVisible(true);
  connect(category_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
  QPushButton *link_button = new QPushButton;
  link_button->setParent(this);
  link_button->setText("link");
  link_button->setGeometry(g_scale * button_box_pos_x,
                           g_scale * (button_box_pos_y + button_box_height + button_gap_y),
                           button_box_width * g_scale,
                           button_box_height * g_scale);
  link_button->setProperty("function", "openlinkfile");
  link_button->setVisible(true);
  connect(link_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
  QPushButton *trackarrow_button = new QPushButton;
  trackarrow_button->setParent(this);
  trackarrow_button->setText("trackarrow");
  trackarrow_button->setGeometry(g_scale * (button_box_pos_x + button_box_width + button_gap_x),
                                 g_scale * (button_box_pos_y + button_box_height + button_gap_y),
                                 button_box_width * g_scale,
                                 button_box_height * g_scale);
  trackarrow_button->setProperty("function", "opentrackarrowfile");
  trackarrow_button->setVisible(true);
  connect(trackarrow_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
//  QPushButton *setting_button = new QPushButton;
//  setting_button->setParent(this);
//  setting_button->setObjectName("Global Setting");
//  setting_button->setText("Global Setting");
//  setting_button->setGeometry(g_scale * (button_box_pos_x + 2 * button_box_width + 2 * button_gap_x),
//                              g_scale * (button_box_pos_y + 0 * button_box_height + 0 * button_gap_y),
//                              button_box_width * g_scale,
//                              button_box_height * g_scale);
//  setting_button->setProperty("prefix", "global");
//  setting_button->setProperty("function", "globalsetting");
//  connect(setting_button, &QPushButton::clicked,
//          this, &FreeCircos::onButtonClicked);
//  setting_button->setEnabled(false);
  QPushButton *save_button = new QPushButton;
  save_button->setParent(this);
  save_button->setText("Save");
  save_button->setProperty("function", "saveimage");
  save_button->setGeometry(g_scale * (button_box_pos_x + 2 * button_box_width + 2 * button_gap_x),
                           g_scale * (button_box_pos_y + button_box_height + button_gap_y),
                           button_box_width * g_scale,
                           button_box_height * g_scale);
  connect(save_button, &QPushButton::clicked,
          this, &FreeCircos::onButtonClicked);
  QPushButton *reset_button = new QPushButton;
  reset_button->setParent(this);
  reset_button->setText("Reset");
  reset_button->setProperty("function", "reset");
//  reset_button->setGeometry(g_scale * (button_box_pos_x + 3 * button_box_width + 3 * button_gap_x),
//                            g_scale * (button_box_pos_y + button_box_height + button_gap_y),
//                            button_box_width * g_scale,
//                            button_box_height * g_scale);
  reset_button->setGeometry(g_scale * (button_box_pos_x + 2 * button_box_width + 2 * button_gap_x),
                            g_scale * (button_box_pos_y + 0 * button_box_height + 0 * button_gap_y),
                            button_box_width * g_scale,
                            button_box_height * g_scale);
  connect(reset_button, &QPushButton::clicked,
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
  control_panel->setGeometry(g_scale * config_widget_pos_x,
                             g_scale * config_widget_pos_y,
                             g_scale * config_widget_width,
                             g_scale * config_widget_height);
  initRadiusWidget();
  initBackBoneWidget(control_panel);
  initLinkWidget(control_panel);
  initArrowWidget(control_panel);
  connect(control_panel, &QTabWidget::currentChanged,
          this, &FreeCircos::onTabwidgetChanged);
  //qDebug() << CustomTool::mapInt2Real(202293916, 202585582, 0, 1, 202417563);
//    qDebug() << QColor(Qt::red).name();
//  initColorDialog();
//  auto *dlg = new color_widgets::ColorDialog;
//  dlg->setParent(this);
////  dlg->setGeometry(100,20,500,400);
//  dlg->show();

//  connectPaintThread();
//  connectCircosThread();
}

FreeCircos::~FreeCircos() {
  delete ui;
  file_process_thread.quit();
  file_process_thread.wait();
  paint_thread.quit();
  paint_thread.wait();
}

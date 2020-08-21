#include "freecircos.h"

#include "ui_freecircos.h"

FreeCircos::FreeCircos(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FreeCircos) {
    ui->setupUi(this);
    this->setGeometry(40, 40, 1800, 650);

    //init canvas
    initCanvas();

    gene_donut = new CustomDonut;
    category_donut = new CustomDonut;
    circos = new Circos;

    QPushButton *backbone_button = new QPushButton;
    backbone_button->setParent(this);
    backbone_button->setText("backbone");
    backbone_button->setGeometry(10, 10, 100, 40);
    backbone_button->setProperty("function", "openbackbonefile");
    backbone_button->setVisible(true);
    connect(backbone_button, &QPushButton::clicked, this,
            &FreeCircos::onButtonClicked);

    QPushButton *category_button = new QPushButton;
    category_button->setParent(this);
    category_button->setText("category");
    category_button->setGeometry(120, 10, 100, 40);
    category_button->setProperty("function", "opencategoryfile");
    category_button->setVisible(true);
    connect(category_button, &QPushButton::clicked, this,
            &FreeCircos::onButtonClicked);

    QElapsedTimer timer;
    timer.start();

    int size = 50;
    for (int i = 0; i < size; ++i) {
        int value = qrand() % 10000;
        CustomSlice *slice = new CustomSlice(QString("%1").arg(value), value);
        gene_donut->AddSlice(slice);
    }
    qDebug() << "Elapsed time1: " << timer.elapsed() << " ms";
    timer.restart();
    QVector<QColor> colors;
    colors.resize(size);
    std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
    QList<QColor> strike_colors = colors.toList();
    gene_donut->SetPens(strike_colors);
    std::generate(colors.begin(), colors.end(), ColorGen(colors.size()));
    QList<QColor> fill_colors = colors.toList();
    gene_donut->SetBrushes(fill_colors);
    gene_donut->SetSize(0.7, 0.8);
    gene_donut->DrawDonut(canvas);
    qDebug() << "Elapsed time2: " << timer.elapsed() << " ms";
    timer.restart();
    canvas->replot();
    qDebug() << "Elapsed time3: " << timer.elapsed() << " ms";
    timer.restart();

    control_panel = new QTabWidget;
    control_panel->setParent(this);
    control_panel->setGeometry(600, 30, 1000, 600);
    initBackBoneWidget(control_panel);

//    control_panel->addTab(backbone_widget, "BackBone");


}

FreeCircos::~FreeCircos() {
    delete ui;
}

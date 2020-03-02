#include <MainWindow.h>

#include <QLabel>
#include <QDoubleSpinBox>
#include <QWidget>
#include <QHBoxLayout>

#include <QStringList>
#include <QTableView>

#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_vec(0.0f)
{
    FDQUI::VectorModel *model = new FDQUI::VectorModel();
    FDQUI::RowVectorProxyModel *proxy_model = new FDQUI::RowVectorProxyModel();
    model->setVector(m_vec);
    proxy_model->setSourceModel(model);
    QTableView *lv = new QTableView();

    lv->setModel(proxy_model);
    setCentralWidget(lv);

    /*
    QWidget *wid = new QWidget();
    QHBoxLayout *hlay = new QHxLayout();
    QHBoxLayout *inhlay = new QHBoxLayout();

    QLabel *lab = new QLabel("x:");
    QDoubleSpinBox *spin = new QDoubleSpinBox();
    spin->setValue(0.0);
    inhlay->addWidget(lab);
    inhlay->addWidget(spin);
    hlay->addLayout(inhlay);

    inhlay = new QHBoxLayout();
    lab = new QLabel("y:");
    spin = new QDoubleSpinBox();
    spin->setValue(0.0);
    inhlay->addWidget(lab);
    inhlay->addWidget(spin);
    hlay->addLayout(inhlay);

    inhlay = new QHBoxLayout();
    lab = new QLabel("z:");
    spin = new QDoubleSpinBox();
    spin->setValue(0.0);
    inhlay->addWidget(lab);
    inhlay->addWidget(spin);
    hlay->addLayout(inhlay);

    wid->setLayout(hlay);
    setCentralWidget(wid);
    */
}

MainWindow::~MainWindow()
{

}

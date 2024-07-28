#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "tree.hpp"
#include "complex.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsView *graphicsView;
    QTextEdit *textOutput;
    QVBoxLayout *mainLayout;
    QHBoxLayout *contentLayout;
    QGraphicsScene *doubleScene;
    QGraphicsScene *intScene;
    QGraphicsScene *complexScene;
    QGraphicsScene *stringScene;

    void setupUI();
    void setupTrees();
    void displayDoubleTree();
    void displayIntTree();
    void displayComplexTree();
    void displayStringTree();

    template<typename T, int K>
    void displayTreeTraversal(const ariel::Tree<T, K>& tree);

    template<typename T>
    void drawTree(QGraphicsScene* scene, const ariel::Node<T>* node, qreal x, qreal y, qreal xOffset, qreal levelHeight);

    template<typename T, int K>
    void setupAndDrawTree(const ariel::Tree<T, K>& tree, QGraphicsScene* scene);
};

#endif // MAINWINDOW_HPP
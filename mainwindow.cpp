#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QString>
#include "tree.hpp"
#include "complex.hpp"
#include "tree_iterators.hpp"
using namespace ariel;
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
    setupTrees();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    contentLayout = new QHBoxLayout();

    graphicsView = new QGraphicsView(this);
    textOutput = new QTextEdit(this);
    textOutput->setReadOnly(true);

    contentLayout->addWidget(graphicsView, 3);
    contentLayout->addWidget(textOutput, 1);

    mainLayout->addLayout(contentLayout);

    doubleScene = new QGraphicsScene(this);
    intScene = new QGraphicsScene(this);
    complexScene = new QGraphicsScene(this);
    stringScene = new QGraphicsScene(this);
}

void MainWindow::setupTrees()
{
    displayDoubleTree();
    displayIntTree();
    displayComplexTree();
    displayStringTree();
}

template<typename T, int K>
void MainWindow::displayTreeTraversal(const ariel::Tree<T, K>& tree)
{
    QString output;

    auto appendValue = [](QString& str, const T& value) {
        if constexpr (std::is_same_v<T, ariel::Complex>) {
            str += QString::fromStdString(value.to_string()) + " ";
        } else if constexpr (std::is_same_v<T, std::string>) {
            str += QString::fromStdString(value) + " ";
        } else {
            str += QString::number(value) + " ";
        }
    };

    auto appendTraversal = [&](const QString& name, auto begin, auto end) {
        output += name + ": ";
        for (auto it = begin; it != end; ++it) {
            appendValue(output, it->value);
        }
        output += "\n";
    };

    appendTraversal("Pre-order", tree.begin_pre_order(), tree.end_pre_order());
    appendTraversal("Post-order", tree.begin_post_order(), tree.end_post_order());
    appendTraversal("In-order", tree.begin_in_order(), tree.end_in_order());
    appendTraversal("BFS", tree.begin_bfs(), tree.end_bfs());
    appendTraversal("DFS", tree.begin_dfs(), tree.end_dfs());

    textOutput->append(output);
}

template<typename T>
void MainWindow::drawTree(QGraphicsScene* scene, const ariel::Node<T>* node, qreal x, qreal y, qreal xOffset, qreal levelHeight)
{
    if (!node) return;

    qreal nodeRadius = 20;
    QGraphicsEllipseItem* ellipse = scene->addEllipse(x - nodeRadius, y - nodeRadius, 2*nodeRadius, 2*nodeRadius);
    ellipse->setBrush(Qt::white);

    QString nodeText;
    if constexpr (std::is_same_v<T, ariel::Complex>) {
        nodeText = QString::fromStdString(node->value.to_string());
    } else if constexpr (std::is_same_v<T, std::string>) {
        nodeText = QString::fromStdString(node->value);
    } else {
        nodeText = QString::number(node->value);
    }
    QGraphicsTextItem* textItem = scene->addText(nodeText);
    textItem->setPos(x - nodeRadius/2, y - nodeRadius/2);

    qreal childrenWidth = xOffset * (node->children.size() - 1);
    qreal startX = x - childrenWidth / 2;

    for (size_t i = 0; i < node->children.size(); ++i) {
        qreal childX = startX + i * xOffset;
        qreal childY = y + levelHeight;

        scene->addLine(x, y + nodeRadius, childX, childY - nodeRadius);

        drawTree(scene, node->children[i], childX, childY, xOffset / 2, levelHeight);
    }
}

template<typename T, int K>
void MainWindow::setupAndDrawTree(const ariel::Tree<T, K>& tree, QGraphicsScene* scene)
{
    scene->clear();
    if (tree.get_root()) {
        drawTree(scene, tree.get_root(), scene->width() / 2, 50, 100, 100);
    }
    scene->setSceneRect(scene->itemsBoundingRect());
}

void MainWindow::displayDoubleTree()
{
    ariel::Tree<double, 2> tree;
    ariel::Node<double>* root = new ariel::Node<double>(1.1);
    tree.add_root(root);
    tree.add_sub_node(root, new ariel::Node<double>(2.2));
    tree.add_sub_node(root, new ariel::Node<double>(3.3));
    tree.add_sub_node(root->children[0], new ariel::Node<double>(4.4));
    tree.add_sub_node(root->children[0], new ariel::Node<double>(5.5));
    tree.add_sub_node(root->children[1], new ariel::Node<double>(6.6));

    setupAndDrawTree(tree, doubleScene);
    graphicsView->setScene(doubleScene);
    displayTreeTraversal(tree);
}

void MainWindow::displayIntTree()
{
    ariel::Tree<int> tree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    tree.add_root(root);
    tree.add_sub_node(root, new ariel::Node<int>(2));
    tree.add_sub_node(root, new ariel::Node<int>(3));
    tree.add_sub_node(root->children[0], new ariel::Node<int>(4));
    tree.add_sub_node(root->children[0], new ariel::Node<int>(5));
    tree.add_sub_node(root->children[1], new ariel::Node<int>(6));

    setupAndDrawTree(tree, intScene);
    graphicsView->setScene(intScene);
    displayTreeTraversal(tree);
}

void MainWindow::displayComplexTree()
{
    ariel::Tree<ariel::Complex> tree;
    ariel::Node<ariel::Complex>* root = new ariel::Node<ariel::Complex>(ariel::Complex(1, 2));
    tree.add_root(root);
    tree.add_sub_node(root, new ariel::Node<ariel::Complex>(ariel::Complex(3, 4)));
    tree.add_sub_node(root, new ariel::Node<ariel::Complex>(ariel::Complex(5, 6)));

    setupAndDrawTree(tree, complexScene);
    graphicsView->setScene(complexScene);
    displayTreeTraversal(tree);
}

void MainWindow::displayStringTree()
{
    ariel::Tree<std::string> tree;
    ariel::Node<std::string>* root = new ariel::Node<std::string>("Root");
    tree.add_root(root);
    tree.add_sub_node(root, new ariel::Node<std::string>("Child1"));
    tree.add_sub_node(root, new ariel::Node<std::string>("Child2"));
    tree.add_sub_node(root->children[0], new ariel::Node<std::string>("GrandChild1"));
    tree.add_sub_node(root->children[0], new ariel::Node<std::string>("GrandChild2"));

    setupAndDrawTree(tree, stringScene);
    graphicsView->setScene(stringScene);
    displayTreeTraversal(tree);
}
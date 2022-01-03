/* Class: MainWindow
  * ----------
  * Carries out the functionalities of the program.
  *
  * Program author
  * Name: Pyry Collander
  * Student number: 255284
  * UserID: collande
  * E-Mail: pyry.collander@tuni.fi
  *
  * Notes: Kommentit englanniksi, koodi englanniksi ja käyttöohje suomeksi.
  *
  * Ohjelman toiminta assarille / kelle tahansa:
  * Pelin alkaessa luodaan neljä neliötä, blockia, jotka
  * asetetaan vektoriin block_vector. Vektori luo blokeista tetrominon,
  * joita on seitsemän erilaista muodoltaan ja väriltään. Kun peli alkaa ja
  * blockit on asetettu vektoriin, valitsee ohjelma randoEngineä apuna
  * käyttäen jonkin näistä määritellyistä muodoista palikalle muodostaen
  * tetrominon. Tetromino lähtee ensin alaspäin kerran sekunnissa ja kun se osuu
  * alareunaan, jää tetromino siihen apumuuttujien avulla, sen koordinaatit
  * tallennetaan vektoriin reserved_coordinatesiin pairina. Pelaajalle
  * tallennetaan jokaisesta blockista piste kyseisen tason (level) mukaisesti,
  * eli block * taso, jolloin tässä vaiheessa kertyy 4*(1*1)=4 pistettä. Kun
  * satunnaisia tetrominoja on pudonnut viisi kappeltta, on loogisesti
  * reserved_coordinates vektorin pituus 20. Tällöinv reserved_coordinates & 20
  * jakojäännös on 0. Aina tällöin, eli viiden palikan välein, pelin tasoa
  * nostetaan. Joka toisella tasolla palikan putoamisnopeus puolitetaan, jotta
  * pelistä tulee haastavampi. Pelissä ei ole ominaisuutta, jossa täydet rivit
  * katoaisivat, eikä tetrominoja voi kääntää.
  *
  * Kun pelin toinen tetromino tulee pelialueelle, voi se törmätä joko
  * alareunaan tai toiseen tetrominoon. Nämä tapaukset tarkastellaan hieman eri
  * tavoin, mutta palikat eivät voi mennä päällekkäin, vaan ne pinoutuvat.
  * Horisontaalisesti palikkaa voi siirtää WASD-näppäinten A- ja D-näppäimillä
  * vasemmalle ja oikealle ja tällöin tarkastellaan samaan tyyliin kuin
  * pudotessa, onko seuraavaksi haluttu koordinaatti vapaana. Tämä tehdään
  * jokaiselle blockille erikseen.
  *
  * Kun palikat alkavat saavuttaa pelin yläreunaa, lähestytään pelin loppua. Kun
  * palikkaa ollaan liikuttamassa, tarkastetaan aivan ensimmäisenä, onko palikan
  * sen hetkisistä koordinaateista jokin jo varattu. Tämä tilanne voi tapahtua
  * vain, jos pelialueelle tuotavan tetrominon koordinaateista jokin on jo
  * varattu. Tällöin peli loppuu, ajastin pysähtyy ja pelaajalle kerrotaan tieto
  * pelin päättymisestä.
  *
  * */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "QtGui"
#include "QGraphicsRectItem"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    initialize_blocks();

    // draw the initial block to the scene of game with a hidden boolean attribute
    define_tetromino(true);

    points = 0;
    level = 1;
    timer_count = 1000;

    ui->label_points->setText("Points: " + QString::number(points));
    ui->label_level->setText("Level: " + QString::number(level));
    ui->label_gameOver->clear();

    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::move_tetromino);
    timer_.start(timer_count);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize_blocks(){
    // give the blocks initial values
    block_1 = new QGraphicsRectItem(0, 0, 20, 20);
    block_2 = new QGraphicsRectItem(0, 0, 20, 20);
    block_3 = new QGraphicsRectItem(0, 0, 20, 20);
    block_4 = new QGraphicsRectItem(0, 0, 20, 20);

    // add the blocks to a vector that is basically the tetromino
    block_vector.push_back(block_1);
    block_vector.push_back(block_2);
    block_vector.push_back(block_3);
    block_vector.push_back(block_4);
}

void MainWindow::move_tetromino()
{
    // point to the scene of the game
    QRectF rect = scene_->sceneRect();

    // check if the game should end or not
    for (auto block : block_vector){
         if ( std::find(reserved_coordinates.begin(), reserved_coordinates.end(),
                        std::make_pair(int(block->x()),int(block->y()))) != reserved_coordinates.end()){
             end_game();
             return;
         }
    }

    // flag indicator of an impact to a border or another block when moving
    // vertically
    bool collision = false;

    // run through all the block of the tetromino and see if their next y-position
    // is available or not
    for (auto block: block_vector){
        qreal current_y = block->y();
        qreal current_x = block->x();

        current_y += SQUARE_SIDE;

        // check for border
        if(!rect.contains(current_x, current_y)) {
            border_hit();
            define_tetromino(false);
            collision = true;
            break;

        }
        // check for other blocks
        else if (std::find(reserved_coordinates.begin(), reserved_coordinates.end(),
                            std::make_pair((int)current_x, (int)current_y)) != reserved_coordinates.end()){
            border_hit();
            define_tetromino(false);
            collision = true;
            break;
        }
    }

    // move the blocks one by one if there is nothing stopping them
    if (!collision){
        for (auto kikkare : block_vector){
            kikkare->moveBy(0, SQUARE_SIDE);
        }
    }
}


void MainWindow::define_tetromino(bool first_time){

    // takes the integer from the random engine
    unsigned int i = 0;
    i = distr(randomEng);

    // paint the blocks of the vector and set them in the desired positions
    if (i == 0){
        for (auto kikkare : block_vector){
            kikkare->setBrush(QBrush(Qt::red));
        }
        // square
        block_1->setPos(120, 20);
        block_2->setPos(100, 20);
        block_3->setPos(100, 0);
        block_4->setPos(120, 0);
    }

    if (i == 1){
        for (auto kikkare : block_vector){
            kikkare->setBrush(QBrush(Qt::blue));
        }
        // horizontal
        block_1->setPos(120, 20);
        block_2->setPos(100, 20);
        block_3->setPos(80, 20);
        block_4->setPos(140, 20);
    }

    if (i == 2){
        for (auto kikkare : block_vector){
            kikkare->setBrush(QBrush(Qt::green));
        }
        // step to left
        block_1->setPos(120, 20);
        block_2->setPos(120, 0);
        block_3->setPos(100, 20);
        block_4->setPos(140, 0);
    }

    if (i == 3){
        for (auto kikkare : block_vector){
            kikkare->setBrush(QBrush(Qt::yellow));
        }
        // step to right
        block_1->setPos(120, 20);
        block_2->setPos(120, 0);
        block_3->setPos(100, 0);
        block_4->setPos(140, 20);
    }

    if (i == 4){
        for (auto kikkare : block_vector){
            kikkare->setBrush(QBrush(Qt::cyan));
        }
        // pyramid
        block_1->setPos(120, 20);
        block_2->setPos(120, 0);
        block_3->setPos(100, 20);
        block_4->setPos(140, 20);
    }

    if (i == 5){
        for (auto kikkare : block_vector){
            kikkare->setBrush(QBrush(Qt::darkYellow));
        }
        // L right
        block_1->setPos(120, 20);
        block_2->setPos(140, 0);
        block_3->setPos(100, 20);
        block_4->setPos(140, 20);
    }

    if (i == 6){
        for (auto kikkare : block_vector){
            kikkare->setBrush(QBrush(Qt::darkMagenta));
        }
        // L left
        block_1->setPos(120, 20);
        block_2->setPos(100, 0);
        block_3->setPos(100, 20);
        block_4->setPos(140, 20);
    }

    // adds blocks to the scene when they are defined the first time
    if (first_time){
        for ( auto kikkare : block_vector){
            scene_->addItem(kikkare);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    QRectF rect = scene_->sceneRect();

    // moving the tetromine to right or left with WASD-letters A and D
    if(event->key() == Qt::Key_A) {

        bool collision = false;

        // check for borders and other blocks
        for (auto block : block_vector){

            qreal current_y = block->y();
            qreal current_x = block->x();

            current_x -= SQUARE_SIDE;

            if(!rect.contains(current_x, current_y)) {
                collision = true;
                break;

            }else if (std::find(reserved_coordinates.begin(), reserved_coordinates.end(),
                           std::make_pair((int)current_x, (int)current_y)) != reserved_coordinates.end()){
                collision = true;
                break;
            }
        }

        // if block is able to move to the desired coordinates it will do so
        if (!collision){
            for (auto block : block_vector){
                block->moveBy(-SQUARE_SIDE, 0);
            }
        }
    }
    // same as above, only to other direction
    if(event->key() == Qt::Key_D) {

        bool collision = false;

            for (auto block : block_vector){

                qreal current_y = block->y();
                qreal current_x = block->x();

                current_x += SQUARE_SIDE;

                if(!rect.contains(current_x, current_y)) {
                    collision = true;
                    break;
                }else if (std::find(reserved_coordinates.begin(), reserved_coordinates.end(),
                               std::make_pair((int)current_x, (int)current_y)) != reserved_coordinates.end()){
                    collision = true;
                    break;
                }
            }
            if (!collision){
                for (auto block : block_vector){
                    block->moveBy(+SQUARE_SIDE, 0);
                }
            }
    }
}

void MainWindow::border_hit(){

       for (auto block : block_vector){
        // if there happens to be a collision with an edge or another block
        // temp_rects are created for the visualization of the fallen tetrominos
        QGraphicsRectItem* temp_rect = new QGraphicsRectItem(0, 0, 20, 20);

        temp_rect->setPos(block->x(), block->y());
        temp_rect->setBrush(QBrush(block->brush()));
        scene_->addItem(temp_rect);

        // make the coordinates used by the tetrominos unusable
        reserved_coordinates.push_back((std::make_pair(block->x(), block->y())));
        }

       point_calculations();

}

void MainWindow::point_calculations(){

    // add points per every block according to level of game
    points += level * 4;

    // add level for every five tetrominos (one tetromino is varatut_koordinaatit += 4)
    if (reserved_coordinates.size() % 20 == 0){
        level += 1;

        // make the tetromino drop faster for every second level of game
        if (level % 2 == 0){
            timer_count = timer_count / 2;
            timer_.setInterval(timer_count);
        }
    }

    ui->label_points->setText("Points: " + QString::number(points));
    ui->label_level->setText("Level: " + QString::number(level));

}

void MainWindow::end_game(){
    timer_.stop();
    ui->label_gameOver->setText("Sorry, you lost!");
}

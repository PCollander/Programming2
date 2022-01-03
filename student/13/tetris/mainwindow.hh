/* Class: MainWindow
  * ----------
  * Defines a contents of the mainwindow.
  *
  * Program author
  * Name: Pyry Collander
  * Student number: 255284
  * UserID: collande
  * E-Mail: pyry.collander@tuni.fi
  *
  * */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <random>
#include <QTimer>
#include <utility>
#include <QGraphicsSimpleTextItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_; // a surface for the game
    QGraphicsRectItem* block_1; // define four blocks to build the tetrominos with
    QGraphicsRectItem* block_2;
    QGraphicsRectItem* block_3;
    QGraphicsRectItem* block_4;

    // vector for taken coordinates in the scene of the game
    std::vector <std::pair <int, int>> reserved_coordinates;
    // the vector that contains the parts of the tetrominos
    std::vector <QGraphicsRectItem*> block_vector;

    QTimer timer_;          // for continuous moving

    // Constants describing scene coordinates
    // Copied from moving circle example and modified a bit
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HORIZONTAL,
                         STEP_UP_RIGHT,
                         STEP_UP_LEFT,
                         SQUARE,
                         PYRAMID,
                         L_RIGHT,
                         L_LEFT,
                         NUMBER_OF_TETROMINOS};
    // From the enum values above, only the last one is needed in this template.
    // The value of the last one is 7 at the moment.


    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    /* sets the block pieces to the vector reserved for them */
    void initialize_blocks();

    /* moves the tetrominos pieces, or the entire "palikka" by using the vector
     * kikkare_vektori
     */
    void move_tetromino();

    /* uses random engine to define the next tetrominos shape and colour and
     * passes the information forwards to the move_palikka function
     */
    void define_tetromino(bool first_time);

    /* checks if the next-to-be coordinate is free for taking over*/
    void border_hit();

    /* preapares the game board for the state of ending the game with the proper
     * information
     */
    void end_game();

    /* counts the points of the game and defines the level and difficulty accordingly */
    void point_calculations();

    /* points for the player */
    unsigned long int points;

    /* difficulty the player is on */
    unsigned long int level;

    /* time for the timer */
    double timer_count;
};

#endif // MAINWINDOW_HH

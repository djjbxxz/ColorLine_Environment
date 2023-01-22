# ColorLine
ColorLine is a puzzle board game. Score points by moving pieces of the same color together on a fixed size board(default is 5 by 5). Pieces can only be moved on empty spots and cannot jump over other pieces. When 5 pieces are connected horizontally, vertically and diagonally (45°), the connected pieces are eliminated and the score is based on the number of eliminated pieces. 

ColorLine 是一款益智类的棋盘游戏。在固定的棋盘尺寸上（默认为5乘5），通过把相同颜色的棋子移动到一起取得分数。棋子只能在空的位置上移动，不能跳过其它棋子。当棋子在水平，竖直，对角倾斜(45°)方向上相连达到5颗时，相连的棋子将会发生消除，并根据消除棋子的个数得分。


## Game Rule
At the beginning of the game, 5 pieces are placed on the board and the color of the next 3 pieces will be displayed (the position on the board is unknown). The user specifies a piece and moves it to the desired place. If the move does not result in 5 or more pieces of the same color being connected on the board, 3 new pieces will randomly appear in the empty space on the board; if the move results in 5 or more pieces of the same color being connected on the board, these pieces will be eliminated, rewarded. No new pieces will appear on the board in the next round.

The game ends when there is no space on the board for a new piece, or when no piece can move after a new piece is placed.

在游戏开始时，棋盘上会放置5颗棋子，并且会显示下次将会出现的3颗棋子的颜色（在棋盘上出现的位置是未知的）。用户指定一个棋子，将其移动到想要的地方，若这次移动没有使得棋盘上出现5颗或以上相同颜色的棋子相连，则将会有3颗新的棋子随机出现在棋盘上的空位置；若这次移动使得棋盘上出现了5颗及以上数量相同颜色的棋子相连，则这些棋子将会消除，得到奖励，并且用户能够再次进行移动，棋盘上不会出现新的棋子。

当棋盘上没有空位放置新的棋子，或者放置完新的棋子后任何棋子都无法进行移动时，游戏达到终局。


## Game configuration
The following parameters ard configurable in [`Base.h`](Base.h) 

| Configurable params          | Default        | Description |
| -----------------------------|----------------|------------------|
| COLOR_NUM                    | 4              | The number of color |
| BOARD_SIZE                   | 5              | The size of the board |
| COMING_CHESS_NUM             | 2              | The number of the chess will be placed in every round (if applicable) |
| MIN_ELEMINATABLE_NUM         | 4              | The minimal number of the connnected chess that can be eleminated |
| EACH_CHESS_ELEMINATED_REWARD | 2              | The reward from every eleminated chess |


## Compilation
C++20 standard required

For Linux, g++ version >=10 

For Windows, use latest MSVC

### CMake
```bash
mkdir build
cd build
cmake ..
make
```

This is a submodule, and is designed for **[this](https://github.com/djjbxxz/sac-discrete-tf-colorline)** project.

Please make sure the game configuration in this submodule is the same as the one in **[here](https://github.com/djjbxxz/sac-discrete-tf-colorline)**.

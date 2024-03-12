# Tetris-Game
The theme of the project is the popular tetris game in which you use the arrows to play the game
controls randomly generated figures cyclically moving towards the bottom of the board. The player sets the pieces like this
so that they fit together and fill the boards without creating gaps between them. When the player fills all the fields
horizontally scores a point, the horizontal line of these blocks disappears, and the remaining pieces move one space w
hole. The game ends when the pieces touch the top of the play area.

# Documentation
[documentation.pdf](https://github.com/mariuszwieclawek/Tetris-Game/files/8410216/documentation.pdf)

# How it works:
![image](https://user-images.githubusercontent.com/57256517/161565647-9fd5cbc8-9a09-42fb-9a79-3abf8b148ee0.png)

When we start the program, the game starts. The program generates random figures (consisting of 4
blocks / squares) in a random color. We control them with the use of left-right arrows. When we want
to rotate a given figure, click the up arrow, we can rotate only when it is possible, i.e.
the rotation of the piece will not go beyond the play area and will not contact another piece. If we want the figure to fall
we hold the down arrow faster. We try to arrange the figures so that they fill all fields without
gaps between the blocks. The player may check the next drawn piece to the right
game windows. When we fill the entire line of blocks horizontally, this line disappears and we score a point. Other figures
moves down one square. When the pieces are placed to the top, the game is over and saved
best result. In subsequent rounds, the player can beat his record results. After losing a round to
to start a new one, click the space key, which is signaled on the right side of the game window. To finish
the program works, click the Escape key.

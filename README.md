# Hive Helsinki: Filler
Algorithms, C and Joyful experimenting

## How to run it
Clone, make and then run following from resources folder:

`./filler_vm -f maps/map00 -p1 ../tlouekar.filler -p2 players/carli.filler | ./visual`

Visualiser by <a href="https://github.com/avocadohooman">@avocadohooman</a>.

## Challenge
Filler is an algorithmic game which consists in filling a grid of a known size in advance with pieces of random size and shapes, without the pieces being stacked more than one square above each other and without them exceeding the grid. If one of these conditions is not met, the game stops.

Each successfully placed piece yields a number of points, and has only one player, the goal of the game could be to get the best score possible. Each player tries to place as many pieces as possible while attempting to prevent his opponent from doing the same. At the end of the game, the one with the most points wins the match.

## Solution
This particular project took waaay longer than needed. I tried many different approaches and only when I stumbled upon the concept of heatmap, I was able to create an algorithm that was strong enough. Heatmap populates a 2D-array with distances to the closest opponent cell. Based on this, I place my piece.

## In hindsight
As it stands, the project could be far more compact and readable. However, trying different solutions on the way was educational in many ways, particularly on how the program flow. 

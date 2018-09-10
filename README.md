# [C] Lem-in (42 project)

_Some puzzles are more pleasant to solve when you can visually see the solution. This is the case here._
![Example](https://raw.githubusercontent.com/tbeauzam/42-project---lem-in/master/gifs/lem-in_simple.gif)

Lem-in is an algorithmic project where you have to guide ants through an anthill.
The program must read a text file that contains a certain number of indications to solve the problem.

### File requirements

Here is a valid map :
```
10
##start
A 3 0
B 1 3
C 5 3
D 1 6
E 5 6
F 1 9
G 5 9
##end
H 3 12
A-B
A-C
B-D
B-G
C-E
D-F
E-G
F-H
G-H
```

Let's deconstruct each part to see what is needed to make a great anthill:
- the number of ants to send through the maze:
```
10
```
- a list of rooms with coordinates:
```
##start
A 3 0
B 1 3
C 5 3
D 1 6
E 5 6
F 1 9
G 5 9
##end
H 3 12
```
Format: _< name_of_the_room > < X coordinate > < Y coordinate >_  
Please note that coordinates are useless without a proper anthill visualizer (which is not mandatory in this project).
For this part to be considered valid, at least one room should be preceded by the ##start instruction,
and another one by the ##end instruction.  
**These words mark respectively the beginning and the end of the maze and are needed.**

- Links between rooms
```
A-B
A-C
B-D
B-G
C-E
D-F
E-G
F-H
G-H
```
For this part to be valid, at least one path *must* exist between the starting room and the final room.


### Usage
After cloning:
```
make
./lem-in < ./maps/diamond
```
Where the content of a file is directly dumped onto standard output, and analyzed by the program.
This should output something like this:
```
10
##start
A 3 0
B 1 3
C 5 3
D 1 6
E 5 6
F 1 9
G 5 9
##end
H 3 12
A-B
A-C
B-D
B-G
C-E
D-F
E-G
F-H
G-H

L1-B 
L1-G L2-B 
L1-H L2-G L3-B 
L2-H L3-G L4-B 
L3-H L4-G L5-B 
L4-H L5-G L6-B 
L5-H L6-G L7-B 
L6-H L7-G L8-B 
L7-H L8-G L9-B 
L8-H L9-G L10-B 
L9-H L10-G 
L10-H 
```
We can see that it displays the file it took as input, followed by a certain amount of lines: these are the solution.
##### Decipher the solution:
Here are the rules of the puzzle:
- all ants start in the starting room, and must go to the end of the maze, the final room
- ants move turn by turn. Each turn, an ant may move **to an empty room** directly linked with the one where it stands 
- more precisely, a room other than the starting one and the final one **cannot contain more than one ant**
- the puzzle is solved when all ants are in the final room.
  
Of course, the challenge here is to guide all these ants as efficiently as possible. Each line of the solution represents a turn. Let's translate the solution we got above, knowing that 10 ants should go through the maze, and knowing that only one path was found in this map, which is A -> B -> G -> H:
- *L1-B* -> Ant 1 moves from A (starting room) to B.
- *L1-G L2-B* -> Ant 1 moves from B to G, _then_ Ant 2 moves from A (starting room) to B
- *L1-H L2-G L3-B* -> Ant 1 moves from G to H (final room), _then_ Ant 2 moves from B to G, _then_ Ant 3 moves from A to B
- *L2-H L3-G L4-B* -> Ant 2 moves from G to H (final room), _then_ And 3 moves from B to G, _then_ Ant 4 moves from A to B
- etc, etc.
- *L10-H* -> Finally, the last ant (Ant 10) moves to H. The puzzle is over in 12 turns!

##### What if a map is wrong?
If a map cannot be solved for whatever reason (invalid parameters in file, no link between enter and exit, wrong syntax etc.), the only thing to output is: ```ERROR```. Parsing is an important part of this project and maps should be checked carefully. Parsing is needed to check syntax and validity of the file, and of course to find all the potential paths between the starting room and the final room.

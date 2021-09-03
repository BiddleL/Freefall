
# Freefall
This project was the first programming project for CS degree. 

Freefall is a vertical shooter arcade  game similar to Space Invaders and Galaga. You, the player must defend the player from the falling stones with a laser. To start you have to input the rows of stones. Then you must move the player and fire the laser to destroy all the stones. 

# Allowed features
* _int_ and _double_ values
* _if_ statements
* _while_ loops
* _int_ arrays, both 1 and 2 dimensional
* _printf_ and _scanf_
* function declaration

# Stage 1
## Placing Stone
Asking how many lines of stones then taking in input for placing stones via input in the array in the format.  
_row column length value_  
e.g _0 0 5 1_ placing a stone starting at [0][0] and ending at [0][4]. Set to the value 1 (_STONE_)
## Moving the Player
Implementing moving the player left or right 
_command direction_  
command - 1  
left - -1  
right - 1  

## Firing the Laser
Firing the laser, destroying blocks directly above the player  
_command_   
command - 2  

# Stage 2
## Shifting Everything Down
Shifting all the rows down one row  
_command_   
command - 3  
## End Conditions
*Game is won if entire map is empty  
*Game is lost if any _STONE_ is on the last row as a 3 command is given

# Stage 3 
## Vertical Flip
Flipping the map vertically  
_command_  
command - 4  

## TNT Blocks
Adding a TNT block which hit, it explodes, destroying all blocks in a radius  
_x y 1 radius_  
eg. _7 7 1 5_ inserting a TNT block of explosion radius of 5  

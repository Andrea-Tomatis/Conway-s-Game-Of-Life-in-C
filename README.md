# Conway-s-Game-Of-Life-in-C
Implementation of Conway's Game of Life in C


![Example](/assets/images/example.png)


## How to compile 

* make sure gcc is installed by running

  > gcc --version 
  
  on your terminal. If it is not then install it following this [guide](https://www.geeksforgeeks.org/how-to-install-gcc-compiler-on-linux/).
* configure GTK+. If you need help see the [official guide](https://www.gtk.org/docs/installations/linux).
* compile the source code using

  > gcc -g -o game_of_life gui.c `pkg-config --cflags --libs gtk+-3.0`
* Run the program with *./game_of_life*
* ***Note***: if you want to change the initial conditions modify the *matrix.txt* file and the **DIM** constant in *header.c*





![Logo](/assets/images/icon.png)

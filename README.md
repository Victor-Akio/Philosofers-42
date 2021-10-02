# Philosofers-42

At this stage, it is important to understand the basics of a threading process and how to deal with such predicament. This project aims to solve the famous philosofers dilemma!!!

First of all, we need to know what is the dilemma....
Imagine that there is a round table and at the center there is a bowl of food.
Surrounding the table the philosofers will be placed and for each philosofer, there will be one fork.
There can be infinite philosofers at the table, although, there must be at least 2 of them to the programm work.

Each philosofer must follow a routine, which consist in eating, if possible. Once satisfied, he should sleep and during it's free time, he will think...

Although, life is not that easy... 
To eat, one must have two forks.
Also, if anyone gets hungry for too long, he will die and the simulation will stop.

There is an extra option, if set, it will limit the amount of times one philosofer must eat and after all philosofers reach this amount, the simulation should stop.

### Installation

To build the programm there is only a few steps:

First of all, you can download the repository through the following steps in any shell of your preference:
```
git clone https://github.com/Victor-Akio/Philosofers-42.git philosofers-42
cd philosofers-42/philo/
make
```
This commands will compile everything and a executable "philo" should be created.

To run the application you should input the programm with the arguments, the parameters to run the simulation. For example:
```
$ ./philo 4 410 200 200
or
$ ./philo 4 410 200 200 5
```
- The first number is the number of philosofers that will be present during the simulation;
- Second will be the time (in miliseconds) that each philosofers have to die. The time they have from the beggining of the simulation or the last meal to the incoming starvation and death;
- Third one is the time (in miliseconds) that each philosofers need to finish their meals;
- Fourth is the time (in milisecconds) that each philosofer takes to sleep after each meal;
- The last one is optional, it is the amount of meals that each philosofer must have to stop the simulation. If not set, the simulation should run continuously or up to one philosofers death.

#### Additional Information

This programm was written in C using a Virtual Machine with a Linux distribution. Although, that might present some issues with the time when you run it within a MacOS, due to the delay to get the time while using the usleep function.
While understanding the issue, we found a python script that might help to find the approximately delay for the current machine (time-measure.py). Thanks to Nesvoboda for the light (find below his github).



## Usefull links
- [Mutex basics](https://www.thegeekstuff.com/2012/05/c-mutex-examples/)
- [Working with Threads](https://www.geeksforgeeks.org/thread-functions-in-c-c/)
- [Nesvoboda tester](https://github.com/nesvoboda/socrates.git)
- 

<h3>What is this?</h3>
This is a simulation of natural selection in a virtual world.  Virtual
bugs compete for virtual food.  Only the best bugs are able to get enough
food to reproduce and grow their population.  Food is green and bugs
are multi-colored.  At every time step, bugs move, consume energy, try to eat food,
reproduce if they have enough energy, or die if they are out of energy.

<h3>How is this natural selection?</h3>
If bugs have enough energy they will asexually reproduce (like bacteria),
and split into two bugs.  There is a small chance its genome will undergo
a random mutation. The best mutations will have the best chance at
acquiring more food, while poor mutations will starve and die.  Each new bug genome is a new color.
The
simulation is an evolutionary algorithm to produce the best bug genome.

<h3>What are the bug's genomes?</h3>
Bugs movement is determined by their genome.   There are eight possible directions a bug can move.   The genome is the probability they will move in each of the directions.   In the table of the top bug’s you can see the winning genomes listed as an array of numbers starting with moving up and then proceeding clockwise.   Bugs with equal probability of movement tend to stay in the same area, where some genomes cause circular or straight line movement.   The best patterns of movements have the best probability of survival.

<h3>A little history...</h3>
<p>I first created a version of this program in Turbo C  for MSDOS in 1993 as part of
a <a href="https://www.us.edu/page/academics/independent-projects/creativity" target="_blank">
Strnad Fellowship</a> at <a href="https://www.us.edu/" target="_blank">University School</a> in Cleveland Ohio.
For the 50th Anniversary of the Strnad Fellowship, I
updated the code (long lost unfortunately!) in a modern web implementation.
Unlike the original one, this versions lets you change setting on the fly,
runs about 100 times faster and doesn't have a buffer overflow that my 16
year old, self-taught self, couldn't debug!
</p>
<p><a href="https://github.com/nickzinn/ArtificialLife" target="_blank">Source code is here.</a></p>
<em>Nicholas Zinn (nickzinn@gmail.com), 2018.</em>

This project was bootstrapped with [Create React App](https://github.com/facebookincubator/create-react-app).

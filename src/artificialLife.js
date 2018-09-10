class Bug{
  constructor(x, y, energy, id, genome){
    this.id = id;
    this.energy = energy;
    this.x = x;
    this.y = y;
    this.genome = genome.slice();
  }

  move(world){
    let sum=0;
    for(let i = 0; i<this.genome.length; i++){
      sum+= this.genome[i];
    }
    let guess = Math.random() * sum;
    let pos=0;
    for(let i = 0, running=0; i<this.genome.length; i++){
      running += this.genome[i];
      if(guess < running){
        pos = i;
        break;
      }
    }
    const xMoves = [0,1,1,1,0,-1,-1,-1];
    const yMoves = [1,1,0,-1,-1,-1,0,1];
    let wrapAround = (c, size) => ( c<0 ? size -1 : (c>=size ? 0: c) );
    let noWrap = (c,size) => ( c<0 ? 0 : (c>=size ? size-1: c) );
    let bounds = (world.wrapAround) ? wrapAround : noWrap;
    this.x = bounds(this.x+ xMoves[pos], world.width);
    this.y = bounds(this.y+ yMoves[pos], world.height);
  }

  mutate(){
    let pos = Math.floor(Math.random() * this.genome.length);
    this.genome[pos] = Math.max(0, this.genome[pos] + Math.random()*2 - 1);
    this.id = ++bugIDCount;
  }
}
let bugIDCount =1;

class World{
  constructor(){
    this.initialFood = 2000;
    this.foodGrowth = 20;
    this.energyConsumption = 1.0;
    this.foodValue = 10;
    this.maxFood = 300;
    this.reproductionEnergy =600;
    this.bugEnergyValue = 1.0;
    this.displayFactor = 4;
    this.stepsPerAnimation = 1;
    this.mutateProbability = .1;
    this.seed = 0;
    this.wrapAround = true;
  }
  init(){
    this.food = new Array(this.width);
    for(let i = 0; i < this.width; i++){
      this.food[i] = new Array(this.height);
      this.food[i].fill(0);
    }
    this.generateFood(this.initialFood);
    bugIDCount =1;
    this.bugs = [];
    this.bugs.push(new Bug(Math.floor(this.width/2), Math.floor(this.height/2),800, 1, [1,1,1,1,1,1,1,1]));
  }

  getFoodAt(x,y){
    return this.food[x][y];
  }

  eatFoodAt(x,y){
    let foodAt = this.getFoodAt(x,y);
    if(foodAt>0){
      const rv = Math.min(this.foodValue,foodAt);
      this.food[x][y] -= rv;
      return rv;
    }
    return 0;
  }

  generateFood(count){
    for(let i = 0; i < count; i++){
      const xPos = Math.floor(Math.random() * this.width);
      const yPos = Math.floor(Math.random() * this.height);
      this.addFood(xPos,yPos);
    }
  }

  addFood(x,y){
    x = Math.min(this.width-1, Math.max(0, x));
    y = Math.min(this.height-1, Math.max(0, y));
    this.food[x][y] = Math.min(this.foodValue + this.food[x][y], this.maxFood);
  }

  paintFood(x,y){
    for(let i=this.seed;i< this.seed + 250; i++){
      let r = Math.random() * 5;
      r = r*r;
      const theta = Math.random() * 6.29;
      const xPos = x+Math.floor(r * Math.cos(theta));
      const yPos = y+ Math.floor(r * Math.sin(theta));
      this.addFood( xPos, yPos);
    }
    this.seed +=250;
  }

  oneStep(){
    let currentBugs = this.bugs.slice();

    for(let i =0; i < currentBugs.length; i++){
      const bug = currentBugs[i];
      bug.energy -= this.energyConsumption;
      bug.move(this);

      bug.energy += this.eatFoodAt(bug.x, bug.y);

      if(bug.energy> this.reproductionEnergy){
        bug.energy = (this.reproductionEnergy/2.0)  * this.bugEnergyValue;
        const newBug = new Bug(bug.x, bug.y, bug.energy , bug.id, bug.genome);
        if(Math.random() < this.mutateProbability){
          newBug.mutate();
        }
        this.bugs.push(newBug);
      }
      if(bug.energy <= 0){
        this.bugs.splice( this.bugs.indexOf(bug), 1 );
        this.addFood(bug.x, bug.y);
      }
    }
    //update grid.
    this.generateFood(this.foodGrowth);
  }
}

export  {Bug, World};

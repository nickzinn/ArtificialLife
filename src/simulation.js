import {World} from './artificialLife.js'
class Simulation{
  constructor(onStatsUpdate){
    this.requestID =0;
    this.world = new World();
    this.generations =0;
    this.onStatsUpdate = onStatsUpdate;
  }
  setCanvasSize(width, height){
    this.canvasHeight = height;
    this.canvasWidth = width;
  }

  restart(){
    this.pause();//just incase
    const df = this.world.displayFactor;
    this.world.height = Math.round(this.canvasHeight/df);
    this.world.width = Math.round(this.canvasWidth/df);
    this.world.init();
    this.startTime =0;
    this.lastGraphUpdate =0;
    this.frames =0;
    this.lastGeneration=0;
    this.resume();
    this.populationHistory = [[[0, this.world.bugs.length]], [[0, this.world.initialFood]]];
  }
  step(timestamp) {
    if(this.drawing){
      this.world.paintFood(this.mousePoint.x, this.mousePoint.y);
    }
    if (!this.startTime) this.startTime = timestamp;
    for(let i =0; i< this.world.stepsPerAnimation; i++){
      this.world.oneStep();
      this.generations++;
    }
    if(this.canvasComponent) this.canvasComponent.updateCanvas();
    if(timestamp - this.lastGraphUpdate > 1000){
      const timeSinceLast = (timestamp - this.lastGraphUpdate)/1000;
      const fps = Math.floor(this.frames/timeSinceLast), gens = Math.floor((this.generations -
        this.lastGeneration)/timeSinceLast);
      this.frames =0;
      this.lastGeneration = this.generations;
      this.lastGraphUpdate = timestamp;
      //calc most common bug.
      const bugStats = createStats(this.world.bugs);
      const foodCount = this.countFood();
      this.populationHistory[0].push([this.generations, this.world.bugs.length]);
      this.populationHistory[1].push([this.generations, foodCount]);
      const summaryStats = { 'gps': gens, 'fps': fps, 'bugCount': this.world.bugs.length , 'food': foodCount};
      this.onStatsUpdate(bugStats, this.populationHistory, summaryStats);
    }
    this.frames++;
    this.requestID = null;
    this.resume();
  }
  resume(){
    if(this.requestID) return 1;
    this.requestID = window.requestAnimationFrame( (p) => this.step(p) );
  }
  pause(){
    if(!this.requestID) return 1;
    window.cancelAnimationFrame(this.requestID);
    this.requestID = null;
  }
  countFood(){
    let foodCount =0;
    const {world} = this;
    for (let x = 0; x < world.width; x++) {
      for (let y = 0; y < world.height; y++) {
        foodCount += world.getFoodAt(x, y);
      }
    }
    return foodCount;
  }
}

function createStats(bugs){
  let groupedBugsMap = new Map();
  bugs.forEach( bug => {
    let {id} = bug;
    if( !groupedBugsMap.get(id)){
      groupedBugsMap.set(id, [bug]);
    }else{
      groupedBugsMap.get(id).push(bug);
    }
  });
  let sortedBugGroups = Array.from( groupedBugsMap.values() );

  sortedBugGroups.sort((a,b) =>  b.length - a.length );
  return sortedBugGroups.map(e => [e[0].id, e.length, e[0].genome, e[0].color] );
}

export  {Simulation};

import {World} from './artificialLife.js'
var Highcharts = require('highcharts');

class Simulation{
  constructor(){
    this.requestID =0;
    this.world = new World();
    this.generations =0;
  }
  setCanvasSize(width, height){
    this.canvasHeight = height;
    this.canvasWidth = width;
    document.getElementById('populationChart').width = width-10;
  }

  restart(){
    this.pause();//just incase
    var df = this.world.displayFactor;
    this.world.height = this.canvasHeight/df;
    this.world.width = this.canvasWidth/df;
    this.world.init();
    this.startTime =0;
    this.lastGraphUpdate =0;
    this.frames =0;
    this.lastGeneration=0;
    this.resume();
    if(this.chart)
      this.chart.destroy();
    this.chart = new Chart([0,0], [0, this.world.initialFood]);
  }
  step(timestamp) {
    if(this.drawing){
      this.world.paintFood(this.mousePoint.x, this.mousePoint.y);
    }
    if (!this.startTime) this.startTime = timestamp;
    var i;
    for(i =0; i< this.world.stepsPerAnimation; i++){
      this.world.oneStep();
      this.generations++;
    }
    if(this.canvasComponent) this.canvasComponent.updateCanvas();
    if(timestamp - this.lastGraphUpdate > 1000){
      var timeSinceLast = (timestamp - this.lastGraphUpdate)/1000;
      var fps = Math.floor(this.frames/timeSinceLast), gens = Math.floor((this.generations -
        this.lastGeneration)/timeSinceLast);
      this.frames =0;
      this.lastGeneration = this.generations;
      this.lastGraphUpdate = timestamp;
      this.chart.updateChart([this.generations, this.world.bugs.length],
        [this.generations, this.foodCount]);
      document.getElementById('performance').innerHTML = "GPS: " +
       gens + " FPS: " + fps +" Bugs: " + this.world.bugs.length + " Food: " + this.foodCount;
      //calc most common bug.
      this.summaryTable.update(createStats(this.world.bugs));
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
}

class Chart{
  constructor(d1, d2 ){
    this.chart = Highcharts.chart('populationChart', {
      credits: { enabled: false},
      boost: { useGPUTranslations: true},
      title: { text: 'Realtime Population' },
      tooltip: { valueDecimals: 0},
      yAxis: [{
       lineWidth: 1,
       allowDecimals: false,
       title: {
           text: 'Bug Population'
       }
   }, {
       lineWidth: 1,
       allowDecimals: false,
       opposite: true,
       title: {
           text: 'Food Count'
       }
   }],
      series: [{
          data: [d1],
          lineWidth: 0.5,
          name:"Population"
      },{
        data: [d2],
        lineWidth: 0.5,
        yAxis: 1,
        name:"Food"
      }]
    });
  }
  updateChart(d1, d2){
    this.chart.series[0].addPoint(d1, true, false);
    this.chart.series[1].addPoint(d2, true, false);
  }
  destroy(){
    this.chart.destroy();
  }
}

function createStats(bugs){
  var groupedBugsMap = new Map();
  for(var i =0; i< bugs.length; i++){
    var bug = bugs[i];
    var id = bug.id;
    if( !groupedBugsMap.get(id)){
      groupedBugsMap.set(id, [bug]);
    }else{
      groupedBugsMap.get(id).push(bug);
    }
  }
  var sortedBugGroups = Array.from( groupedBugsMap.values() );

  sortedBugGroups.sort(function(a,b){ return b.length - a.length; });
  var results = [];
  for(var i=0; i< sortedBugGroups.length; i++){
    var bug = sortedBugGroups[i][0];
    var row = [bug.id, sortedBugGroups[i].length, bug.genome];
    results.push(row);
  }
  return results;
}

export  {Simulation};

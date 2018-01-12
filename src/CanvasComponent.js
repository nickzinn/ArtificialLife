import React from 'react';

import { Button  } from 'semantic-ui-react';
class CanvasComponent extends React.Component {
  first = true;
  idToColorMap = new Map();


  componentWillMount(){
    this.restart();
  }

  restart(){
    this.idToColorMap.set(1,'rgb(200,0,0)');
    var forceEven = (x) => ( x - (x % this.props.simulation.world.displayFactor));
    this.width  = forceEven(Math.min(window.innerWidth - 10, 500));
    this.height = forceEven(Math.min(window.innerHeight-90, 800));
  }
    componentDidMount() {
      const simulation = this.props.simulation;
      const world = simulation.world;
      const canvas = this.refs.canvas;

      this.drawing = false;
      this.mousePoint = null;


      function calcPoint(e){
        var df = world.displayFactor;
        return {x:Math.floor((e.offsetX)/ df),
              y:Math.floor((e.offsetY) / df)};
      }
      canvas.addEventListener("mousedown",  (e) => {
        this.drawing = true;
        this.mousePoint = calcPoint(e);
      }, false);
      canvas.addEventListener("mouseup", (e) => {
        this.drawing = false;
      }, false);
      canvas.addEventListener("mousemove", (e) => {
        this.mousePoint = calcPoint(e);
      }, false);
    }



    updateCanvas() {
      if(this.first){
        this.refs.startButton.style.visibility="hidden";
        this.first = false;
      }
      const simulation = this.props.simulation;
      const world = simulation.world;
      if(this.drawing){
        world.paintFood(this.mousePoint.x, this.mousePoint.y);
      }
      const canvas = this.refs.canvas;
      const ctx = canvas.getContext('2d');
      simulation.foodCount =0;
      ctx.clearRect(0, 0, canvas.width, canvas.height);
      ctx.fillStyle = 'rgb(0,200,0)';
      var df = world.displayFactor;
      for(var x =0; x < world.width; x++){
        for(var y=0; y < world.height; y++){
          var food = world.getFoodAt(x,y);
          if( food > 0){
            var color = Math.floor((100 - (food/world.maxFood) * 100) + 155);
            color = Math.min(color, 255);
            ctx.fillStyle = 'rgb(0,'+ color + ',0)';
            ctx.fillRect(x*df, y*df, df, df);
            simulation.foodCount += food;
          }
        }
      }

      for(var i =0; i< world.bugs.length;i++){
        var bug = world.bugs[i];
        if(!bug.color){
          var color = this.idToColorMap.get(bug.id);
          if(!color)
            this.idToColorMap.set(bug.id, color= bugColors[bug.id % bugColors.length] );
          bug.color = color;
        }
        ctx.fillStyle = bug.color;
        ctx.fillRect(bug.x*df-1, bug.y*df-1, df+1, df+1);
      }
    }
    start = () => {
        this.props.start();
    };
    render() {
         return (
           <div height={this.height} width={this.width} className="canvas-container">
           <canvas ref="canvas" height={this.height} width={this.width} className="world-canvas"></canvas>
           <button id='start-button' className='start-button ui teal button massive' onClick={this.start} ref="startButton">Start Simulation</button>
           </div>
         );
    }
}

var bugColors = ['#F44336','#9C27B0','#3F51B5','#FFEB3B','#EF5350','#9C27B0','#2196F3','#FFC107','#FF1744',
  '#AA00FF','#00BCD4','#FF9800','#D50000','#6200EA','#304FFE','#FF5722','#F44336','#6200EA','#304FFE','#FF5722',
  '#E91E63','#673AB7','#0091EA','#FFAB00','#C51162','#00B8D4','#FF6D00','#F50057','#FF3D00'];

export default CanvasComponent;

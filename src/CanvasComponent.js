import React from 'react';

import { Button  } from 'semantic-ui-react';
class CanvasComponent extends React.Component {
  first = true;
  componentWillMount(){
    var forceEven = (x) => ( x % 2 == 1 ? x-1 :x);
    this.width  = forceEven(Math.min(window.innerWidth - 10, 500));
    this.height = forceEven(Math.min(window.innerHeight-90, 800));
    console.log("w: " + this.width);
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
      const canvas = this.refs.canvas;
      const ctx = canvas.getContext('2d');
      if(this.drawing){
        world.paintFood(this.mousePoint.x, this.mousePoint.y);
      }
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
      ctx.fillStyle = 'rgb(200,0,0)';
      for(var i =0; i< world.bugs.length;i++){
        var bug = world.bugs[i];
        ctx.fillRect(bug.x*df, bug.y*df, df, df);
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

export default CanvasComponent;

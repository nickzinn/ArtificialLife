import React from 'react';
import Button from '@material-ui/core/Button';

class CanvasComponent extends React.Component {
  constructor(props){
    super(props)
    this.state = {showStartButton:true};
    this.idToColorMap = new Map();
    this.idToColorMap.set(1, 'rgb(200,0,0)');
  } 
  
  componentDidMount() {
      const {world} = this.props.simulation;
      const canvas = this.refs.canvas;

      this.drawing = false;
      this.mousePoint = null;

      function calcPoint(e){
        const df = world.displayFactor;
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
    componentWillUnmount(){
      this.dead = true;
    }

    updateCanvas() {
      if(this.dead) return;
      if (this.state.showStartButton){
        this.setState({ showStartButton:false});
      }
      const {world} = this.props.simulation;
      if(this.drawing){
        world.paintFood(this.mousePoint.x, this.mousePoint.y);
      }
      const canvas = this.refs.canvas;
      const ctx = canvas.getContext('2d');
      ctx.clearRect(0, 0, canvas.width, canvas.height);
      ctx.fillStyle = 'rgb(0,200,0)';
      const df = world.displayFactor;
      for(let x =0; x < world.width; x++){
        for(let y=0; y < world.height; y++){
          const food = world.getFoodAt(x,y);
          if( food > 0){
            let color = Math.floor((100 - (food/world.maxFood) * 100) + 155);
            color = Math.min(color, 255);
            ctx.fillStyle = 'rgb(0,'+ color + ',0)';
            ctx.fillRect(x*df, y*df, df, df);
          }
        }
      }

      for(let i =0; i< world.bugs.length;i++){
        const bug = world.bugs[i];
        if(!bug.color){
          let color = this.idToColorMap.get(bug.id);
          if(!color)
            this.idToColorMap.set(bug.id, color= bugColors[bug.id % bugColors.length] );
          bug.color = color;
        }
        ctx.fillStyle = bug.color;
        ctx.fillRect(bug.x*df-1, bug.y*df-1, df+1, df+1);
      }
    }

    render() {
         return (
           <div height={this.props.dimensions.height} width={this.props.dimensions.width} className="canvas-container">
           <canvas ref="canvas" height={this.props.dimensions.height} 
               width={this.props.dimensions.width} className="world-canvas"></canvas>
           { this.state.showStartButton && (
               <Button id='start-button' variant="extendedFab" color="secondary" onClick={this.props.start} 
           size="large" ref="startButton">
            Start Simulation
          </Button>
           )}
          </div>
         );
    }
}

var bugColors = ['#F44336','#9C27B0','#3F51B5','#FFEB3B','#EF5350','#9C27B0','#2196F3','#FFC107','#FF1744',
  '#AA00FF','#00BCD4','#FF9800','#D50000','#6200EA','#304FFE','#FF5722','#F44336','#6200EA','#304FFE','#FF5722',
  '#E91E63','#673AB7','#0091EA','#FFAB00','#C51162','#00B8D4','#FF6D00','#F50057','#FF3D00'];

export default CanvasComponent;
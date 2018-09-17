import React from 'react';

import { FormGroup, Card, CardHeader, CardContent} from '@material-ui/core';
import Slider from './Slider';
import CheckboxComponent from './CheckboxComponent';

//<Form.Input label={`Initial Food: ${this.state.initialFood}`}
// min={20000} max={200000} name='initialFood'
// onChange={this.handleChangeRestart} step={100} type='range'
// value={this.state.initialFood} />
//<FormComponent simulation={this.simulation} onUpdate={this.restart} />

export default class FormComponent extends React.Component {
  constructor(props) {
    super(props);
    const {world} = props.simulation;
    this.state = world;
    this.handleChange = this.handleChange.bind(this);
    this.handleChangeRestart = this.handleChangeRestart.bind(this);
  }
  // this.initialFood = 200000;
  // this.foodGrowth = 20;
  // this.energyConsumption = 1.0;
  // this.foodValue = 10;
  // this.maxFood = 300;
  // this.reproductionEnergy =600;
  // this.bugEnergyValue = 200;
  // this.displayFactor = 2;
  // this.stepsPerAnimation = 10;
  // this.mutateProbability = .1;

  handleChange(name, value ){
    this.setState({ [name]: value });
    if(Number.isFinite(this.props.simulation.world[name])){
      this.props.simulation.world[name] = Number.parseFloat(value,10);
    }else{
      this.props.simulation.world[name] = value;
    }
  }
  handleChangeRestart(name, value ){
    this.handleChange(name, value);
    this.props.onUpdate();
  }

  render() {
      const rowValue = true;
       return (
         <div style={{ minWidth: '250px', width: '100%' }} >
         <Card> 
           <CardHeader style={{paddingBottom:'0px'}} 
           title='Simulation Settings'  />
           <CardContent style={{ paddingBottom: '10px' }} >
           <FormGroup row={rowValue}>
           <Slider label='Mutation Probability' value={this.state.mutateProbability} name='mutateProbability'
             constraint={[0.0,.5,.01]} onChange={this.handleChange} />
           <Slider label='Speed' value={this.state.stepsPerAnimation} name='stepsPerAnimation'
             constraint={[1, 30, 1]} onChange={this.handleChange} />
         </FormGroup>
           <FormGroup row={rowValue}>
            <Slider label='InitialFood' value={this.state.initialFood} name='initialFood'
              constraint={[2000, 200000, 100]} onChange={this.handleChangeRestart} />
            <Slider label='Food Growth' value={this.state.foodGrowth} name='foodGrowth'
              constraint={[5, 100, 1]} onChange={this.handleChange} />
          </FormGroup>
           <FormGroup row={rowValue}>
            <Slider label='Energy Consumption' value={this.state.energyConsumption} name='energyConsumption'
              constraint={[.1,2,.1]} onChange={this.handleChange} />
            <Slider label='Food Value (energy)' value={this.state.foodValue} name='foodValue'
              constraint={[5, 100, 1]} onChange={this.handleChange} />
          </FormGroup>
           <FormGroup row={rowValue}>
            <Slider label='Max Food in Square' value={this.state.maxFood} name='maxFood'
              constraint={[100, 400, 10]} onChange={this.handleChange} />
            <Slider label='Reproduction Energy' value={this.state.reproductionEnergy} name='reproductionEnergy'
              constraint={[400, 1500, 10]} onChange={this.handleChange} />
          </FormGroup>
           <FormGroup row={rowValue}>
            <Slider label='New Bug Energy' value={this.state.bugEnergyValue} name='bugEnergyValue'
              constraint={[.1, 1.0, .1]} onChange={this.handleChange} />
            <Slider label='Display Factor' value={this.state.displayFactor} name='displayFactor'
              constraint={[1, 6, 1]} onChange={this.handleChangeRestart} />
          </FormGroup>
           <FormGroup row={rowValue}>
            <CheckboxComponent label='Enable Wrap Around' value={this.state.wrapAround} name='wrapAround'
               onChange={this.handleChange} />
          </FormGroup>
           </CardContent>
          </Card>
           {(this.props.responsive) && (<div style={{paddingTop:'70px' }}></div>) }
          </div>
       );
  }
}

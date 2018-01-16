import React from 'react';
import { Form, Checkbox } from 'semantic-ui-react';

// <Slider label='InitialFood' value={this.state.initialFood} name={'initialFood'}
//    constraint={[20000, 200000, 100]} onChange={this.handleChange} />
class Slider extends React.Component {
  constructor(props) {
    super(props);
    this.state = {'value': props.value};
    this.handleChange = this.handleChange.bind(this);
  }
  handleChange(e, { name, value }){
    this.setState({ 'value': value });
    this.props.onChange(e,{'name': name, 'value': value});
  }
  render() {
    const [min, max, step] = this.props.constraint;
     return (
       <Form.Input label={`${this.props.label}: ${this.state.value}`}
       min={min} max={max} step={step} name={this.props.name}
       onChange={this.handleChange}  type='range'
       value={this.state.value} />
     );
   }
}

class CheckboxComponent extends React.Component {
  constructor(props) {
    super(props);
    this.state = {'value': props.value};
    this.handleChange = this.handleChange.bind(this);
  }
  handleChange(e, { name, checked }){
    this.setState({ 'value': checked });
    this.props.onChange(e,{'name': name, 'value': checked});
  }
  render() {
     return (
       <Form.Field inline>


      <Checkbox  fitted name={this.props.name} onChange={this.handleChange}
      checked={this.state.value} label={{ children: this.props.label}}/>
    </Form.Field>
     );
   }
}
//<Form.Input label={`Initial Food: ${this.state.initialFood}`}
// min={20000} max={200000} name='initialFood'
// onChange={this.handleChangeRestart} step={100} type='range'
// value={this.state.initialFood} />
//<FormComponent simulation={this.simulation} onUpdate={this.restart} />

class FormComponent extends React.Component {
  constructor(props) {
    super(props);
    var world = props.simulation.world;
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

  handleChange(e, { name, value }){
    this.setState({ [name]: value });
    if(Number.isFinite(this.props.simulation.world[name])){
      this.props.simulation.world[name] = Number.parseFloat(value,10);
    }else{
      this.props.simulation.world[name] = value;
    }
  }
  handleChangeRestart(e, { name, value }){
    this.handleChange(e, {'name': name, 'value': value});
    this.props.onUpdate();
  }

  render() {
       return (
         <Form unstackable size='small'>
         <Form.Group widths='equal'>
           <Slider label='Mutation Probability' value={this.state.mutateProbability} name='mutateProbability'
             constraint={[0.0,.5,.01]} onChange={this.handleChange} />
           <Slider label='Speed' value={this.state.stepsPerAnimation} name='stepsPerAnimation'
             constraint={[1, 30, 1]} onChange={this.handleChange} />
         </Form.Group>
          <Form.Group widths='equal'>
            <Slider label='InitialFood' value={this.state.initialFood} name='initialFood'
              constraint={[2000, 200000, 100]} onChange={this.handleChangeRestart} />
            <Slider label='Food Growth' value={this.state.foodGrowth} name='foodGrowth'
              constraint={[5, 100, 1]} onChange={this.handleChange} />
          </Form.Group>
          <Form.Group widths='equal'>
            <Slider label='Energy Consumption' value={this.state.energyConsumption} name='energyConsumption'
              constraint={[.1,2,.1]} onChange={this.handleChange} />
            <Slider label='Food Value (energy)' value={this.state.foodValue} name='foodValue'
              constraint={[5, 100, 1]} onChange={this.handleChange} />
          </Form.Group>
          <Form.Group widths='equal'>
            <Slider label='Max Food in Square' value={this.state.maxFood} name='maxFood'
              constraint={[100, 400, 10]} onChange={this.handleChange} />
            <Slider label='Reproduction Energy' value={this.state.reproductionEnergy} name='reproductionEnergy'
              constraint={[400, 1500, 10]} onChange={this.handleChange} />
          </Form.Group>
          <Form.Group widths='equal'>
            <Slider label='New Bug Energy' value={this.state.bugEnergyValue} name='bugEnergyValue'
              constraint={[.1, 1.0, .1]} onChange={this.handleChange} />
            <Slider label='Display Factor' value={this.state.displayFactor} name='displayFactor'
              constraint={[1, 6, 1]} onChange={this.handleChangeRestart} />
          </Form.Group>
          <Form.Group widths='equal'>
            <CheckboxComponent label='Enable Wrap Around' value={this.state.wrapAround} name='wrapAround'
               onChange={this.handleChange} />
          </Form.Group>
          </Form>

       );
  }
}

export default FormComponent;

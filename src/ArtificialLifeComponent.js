import React from 'react';
import './ArtificialLifeComponent.css';
import {Simulation} from './simulation.js';
import CanvasComponent from './CanvasComponent.js';
import FormComponent from './FormComponent.js';
import InfoModal from './InfoModal.js'
import { Menu, Button, Icon, Table, Container, Message, Responsive } from 'semantic-ui-react';


//# <PauseButton onPause={this.pause} onResume={this.resume} />
class PauseButton extends React.Component {
  constructor(props) {
    super(props);
    this.state = {pause: false};
    this.handleClick = this.handleClick.bind(this);
  }
  handleClick(e) {
    if(!(this.state.pause ? this.props.onResume() : this.props.onPause()))
      this.setState({pause: !this.state.pause});
  }
  render() {
    if(this.props.small){
    return (
      <Button color={'teal'} icon onClick={this.handleClick}>
      <Icon name={this.state.pause ? 'play' : 'pause'} /></Button>
    );
  }else{
    return (
      <Button color={'teal'}  style={{width:"153px"}} icon labelPosition='left' onClick={this.handleClick}>
      <Icon name={this.state.pause ? 'play' : 'pause'} />
      {this.state.pause ? 'RESUME' : 'PAUSE'}
    </Button>
    );
  }
  }
}

//<BugSummaryTable ref={(ip) => this.summaryTable = ip} />
class BugSummaryTable extends React.Component {
  state = {stats:[]};
  update = (data) => this.setState({stats:data});

  render() {
    const stats = this.state.stats;
    var rows = [];
    stats.slice(0,10).forEach(function(stat, index) {
        rows.push(
          <Table.Row key={index}>
            <Table.Cell>{stat[0]}</Table.Cell>
            <Table.Cell>{stat[1]}</Table.Cell>
            <Table.Cell>[{stat[2].map( (x)=> x.toFixed(2) ).join(' ')}]</Table.Cell>
          </Table.Row>
      );
    }.bind(this));
    return (
    <Table style={{  width:"350px"}} compact unstackable striped >
       <Table.Header>
         <Table.Row>
           <Table.HeaderCell>ID</Table.HeaderCell>
           <Table.HeaderCell>#</Table.HeaderCell>
           <Table.HeaderCell>Genome</Table.HeaderCell>
         </Table.Row>
       </Table.Header>
       <Table.Body>
        {rows}
       </Table.Body>
    </Table>
    );
  }
}

class ArtificialLifeComponent extends React.Component {
  constructor(props) {
    super(props);
    this.simulation = new Simulation();
  }

  componentDidMount() {
    this.simulation.setCanvasSize(this.canvasComponent.width, this.canvasComponent.height);
    this.simulation.canvasComponent = this.canvasComponent;
    this.simulation.summaryTable = this.summaryTable;
  }

  componentWillUnmount() {
    this.simulation.stop();
  }

  restart = () =>  this.simulation.restart();
  pause = () =>  this.simulation.pause();
  resume = () =>  this.simulation.resume();

  render() {
    return (
      <div>

<Responsive {...Responsive.onlyMobile}>
  <Menu size={'small'} borderless>
    <Menu.Item header><Icon  name='bug'/>Artificial Life Simulation</Menu.Item>
    <Menu.Menu position='right'>
    <Menu.Item>
    <Button color={'teal'} icon onClick={this.restart}>
    <Icon name='refresh'/></Button>
    </Menu.Item>
    <Menu.Item>
    <PauseButton small onPause={this.pause} onResume={this.resume} />
    </Menu.Item>
    <Menu.Item> <InfoModal small/> </Menu.Item>
  </Menu.Menu>
  </Menu>
</Responsive>

<Responsive minWidth={Responsive.onlyTablet.minWidth}>
      <Menu size={'large'} stackable borderless>
        <Menu.Item header><Icon size={"large"} name='bug'/>Artificial Life Simulation</Menu.Item>
        <Menu.Menu position='right'>
        <Menu.Item>
        <Button color={'teal'} icon labelPosition='left' onClick={this.restart}>
        <Icon name='refresh'/>RESTART </Button>
        </Menu.Item>
        <Menu.Item>
        <PauseButton onPause={this.pause} onResume={this.resume} />
        </Menu.Item>
        <Menu.Item> <InfoModal /> </Menu.Item>
      </Menu.Menu>
      </Menu>
</Responsive>

      <div id="wrap-container">
        <div className='item-container'>
         <CanvasComponent ref={(ip) => this.canvasComponent = ip} className="world-canvas"
            simulation={this.simulation} start={this.restart}>
         </CanvasComponent>
        </div>
        <div className='item-container'>
         <div id="populationChart" style={{  height:"300px"}}></div>
         <Message>
         <FormComponent simulation={this.simulation} onUpdate={this.restart} />
         </Message>

        </div>
        <div className='item-container'>
          <h5 id="performance" ></h5>
          <BugSummaryTable ref={(ip) => this.summaryTable = ip} />
        </div>
      </div>

      </div>
    );
  }
}

export default ArtificialLifeComponent;

import React from 'react';
import './ArtificialLifeComponent.css';
import {Simulation} from './simulation';
import CanvasComponent from './CanvasComponent';
import FormComponent from './form/FormComponent';
import InfoModal from './InfoModal'
import PauseButton from './PauseButton'
import BugSummaryTable from './BugSummaryTable'
import BottomNavigationComponent from './BottomNavigationComponent'
import PopulationChart from './PopulationChart'

import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import IconButton from '@material-ui/core/IconButton';
import Typography from '@material-ui/core/Typography';
import RefreshIcon from '@material-ui/icons/Refresh';
import Hidden from '@material-ui/core/Hidden';
import Card from '@material-ui/core/Card';
import CardHeader from '@material-ui/core/CardHeader';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome'
import withWidth from '@material-ui/core/withWidth';

class ArtificialLifeComponent extends React.Component {
  constructor(props) {
    super(props);
    this.simulation = new Simulation(this.handleStatsUpdate);
    this.state = { 'bugStats': [], 'populationHistory': [[[0,0]],[[0,0]]], 
      'summaryStats': { gps: 0, fps: 0, bugCount: 0, food: 0 }, responsiveScreen: "simulation" };
    this.dimensions = this.calcDimensions();
    this.simulation.setCanvasSize(this.dimensions.width, this.dimensions.height);
  }
  isResponsive = () => this.props.width === 'xs';
  calcDimensions(){
    const forceEven = (x) => (x - (x % this.simulation.world.displayFactor));
    const heightMod = this.isResponsive() ? 120 : 78;
    return {
      width: forceEven(Math.max(Math.min(window.innerWidth - 10, 500), 300)),
      height: forceEven(Math.max(Math.min(window.innerHeight - heightMod, 800), 400))};
  }

  componentWillUnmount() {
    this.simulation.stop();
  }

  restart = () =>  {
    this.pauseButton.setState({ pause: false });
    this.simulation.restart();
  }
  pause = () =>  this.simulation.pause();
  resume = () =>  this.simulation.resume();

  handleStatsUpdate = (bugStats, populationHistory, summaryStats) =>{
    this.setState({ 'bugStats': bugStats, 'populationHistory': populationHistory, 'summaryStats': summaryStats});
  }
  handleBottomNavChange = (e, value) =>{
    this.setState({ responsiveScreen: value });
  }
  render() {
    const simulation = () =>(
      <CanvasComponent ref={(ip) => this.simulation.canvasComponent = ip} className="world-canvas"
      simulation={this.simulation} start={this.restart} dimensions={this.dimensions} />
    );
    const charts = () => (
      <Card>
        <CardHeader title='Realtime Population' />
        <PopulationChart populationHistory={this.state.populationHistory} />
      </Card>
    );
    const stats = () => (
      <BugSummaryTable bugStats={this.state.bugStats} summaryStats={this.state.summaryStats} />
    );
    const settings = () =>(
        <FormComponent simulation={this.simulation} onUpdate={this.restart} 
        responsive={ this.isResponsive() } />
    );
    const components = {simulation, charts, stats, settings};
    const responsiveUI = () => Object.keys(components).map( v => 
      <div className='item-containerES' key={v} 
      style={{ display: (this.state.responsiveScreen === v) ? 'inherit': 'none'}}>
        {components[v]()}
      </div>
     );

    return (
      <React.Fragment>
        <AppBar position="fixed" color="primary">
          <Toolbar>
            <FontAwesomeIcon icon="bug" size="lg" color="inherit" />
            <Typography variant="title" color="inherit" className="app-bar-title">
              &nbsp;&nbsp;Artificial Life&nbsp;<Hidden xsDown>Simulation</Hidden>
            </Typography>
            <IconButton color="inherit" onClick={this.restart}>
              <RefreshIcon/></IconButton>
            <PauseButton onPause={this.pause} onResume={this.resume}
              ref={(ip) => this.pauseButton = ip} />
            <InfoModal /> 
          </Toolbar>
        </AppBar>
        <div id="wrap-container" style={{ paddingTop: this.isResponsive() ? '59px':'66px' }}>
          {this.isResponsive() ? (
            <React.Fragment>{responsiveUI()}</React.Fragment>
      ) : (
        <React.Fragment>
        <div className='item-container'>
            {simulation()}
        </div>
        <div className='item-container'>
          {charts()}
          &nbsp;
          {stats()}
        </div>
        <div className='item-container'>
            {settings()}
        </div>
        </React.Fragment>
      )}
      </div>
        <BottomNavigationComponent 
          value={this.state.responsiveScreen} 
          onChange={this.handleBottomNavChange } />
      </React.Fragment>
    );
  }
}

export default withWidth()(ArtificialLifeComponent);
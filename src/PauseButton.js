import React from 'react';

import PlayArrow from '@material-ui/icons/PlayArrow';
import Pause from '@material-ui/icons/Pause';

import IconButton from '@material-ui/core/IconButton';

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
    return (
      <IconButton color="inherit" onClick={this.handleClick}>
        {(this.state.pause) ? (<PlayArrow />) : (<Pause />)}
      </IconButton>
    );
  }
}

export default PauseButton;

import React from 'react';

import PlayArrow from '@material-ui/icons/PlayArrow';
import Pause from '@material-ui/icons/Pause';
import IconButton from '@material-ui/core/IconButton';

//# <PauseButton onPause={this.pause} onResume={this.resume} />
class PauseButton extends React.Component {
  render() {
    return (
      <IconButton color="inherit" onClick={this.props.onClick}>
        {(this.props.pause) ? (<PlayArrow />) : (<Pause />)}
      </IconButton>
    );
  }
}

export default PauseButton;

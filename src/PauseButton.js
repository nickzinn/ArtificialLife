import React from 'react';

import PlayArrow from '@material-ui/icons/PlayArrow';
import Pause from '@material-ui/icons/Pause';
import IconButton from '@material-ui/core/IconButton';

//# <PauseButton onPause={this.pause} onResume={this.resume} />
const PauseButton = ({pause, onClick}) =>  {
    return (
      <IconButton color="inherit" onClick={onClick}>
        {(pause) ? (<PlayArrow />) : (<Pause />)}
      </IconButton>
    );
}
export default  PauseButton;

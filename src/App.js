import React, { Component } from 'react';
import ArtificialLifeComponent from './ArtificialLifeComponent';
import { library } from '@fortawesome/fontawesome-svg-core'
import { faBug } from '@fortawesome/free-solid-svg-icons'
import { MuiThemeProvider, createMuiTheme } from '@material-ui/core/styles';
import CssBaseline from '@material-ui/core/CssBaseline';
import teal from '@material-ui/core/colors/teal';
import green from '@material-ui/core/colors/green';

library.add(faBug)

const theme = createMuiTheme({
  palette: {
    primary: teal,
    secondary: green,
  }
});

export default class App extends Component {
  render() {
    return (
      <React.Fragment>
      <CssBaseline />
      <MuiThemeProvider theme={theme}>
        <ArtificialLifeComponent />
      </MuiThemeProvider>
      </React.Fragment>
    );
  }
}

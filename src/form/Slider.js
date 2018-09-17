import React from 'react';

import {Typography, FormControl} from '@material-ui/core';
import SliderControl from '@material-ui/lab/Slider';

export default class Slider extends React.Component {
  constructor(props) {
    super(props);
    this.handleChange = this.handleChange.bind(this);
  }

  handleChange(event, value) {
    this.props.onChange(this.props.name, value );
  }

  render() {
    const [min, max, step] = this.props.constraint;
    return (
      <FormControl fullWidth={true} >
        <Typography id="label">{`${this.props.label}: ${this.props.value}`}</Typography>
        <SliderControl
          id={this.props.label}
          value={this.props.value}
          onChange={this.handleChange}
          name={this.props.name}
          min={min}
          max={max}
          step={step}
        />
      </FormControl>
    );
  }
}
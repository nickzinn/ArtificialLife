import React from 'react';

import { Typography, FormControl } from '@material-ui/core';
import SliderControl from '@material-ui/lab/Slider';

const Slider = ({ name, onChange, label, value, constraint: [min, max, step] }) => {
  return (
    <FormControl fullWidth={true} >
      <Typography id="label">{`${label}: ${value}`}</Typography>
      <SliderControl
        id={label}
        value={value}
        onChange={(event, value) => onChange(name, value)}
        name={name}
        min={min}
        max={max}
        step={step}
      />
    </FormControl>
  );
}

export default Slider;
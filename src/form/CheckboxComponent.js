import React from 'react';
import { FormControlLabel, Checkbox} from '@material-ui/core';

const CheckboxComponent = ({value, name, label, onChange}) =>  {
    return (
      <FormControlLabel
        control={
          <Checkbox
            checked={value}
            onChange={(e) => onChange(name, e.target.checked)}
            name={name}
            color="primary"
          />
        }
        label={label }
      />
    );
}
export default CheckboxComponent;


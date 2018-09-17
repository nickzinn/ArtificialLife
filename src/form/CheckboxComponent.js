import React from 'react';
import { FormControlLabel, Checkbox} from '@material-ui/core';

export default class CheckboxComponent extends React.Component {
  constructor(props) {
    super(props);
    this.handleChange = this.handleChange.bind(this);
  }

  handleChange(event) {
    this.props.onChange(this.props.name,event.target.checked);
  }

  render() {
    return (
      <FormControlLabel
        control={
          <Checkbox
            checked={this.props.value}
            onChange={this.handleChange}
            name={this.props.name}
            color="primary"
          />
        }
        label={this.props.label }
      />
    );
  }
}



import React from 'react';

import { Button, Modal, Icon } from 'semantic-ui-react';

class InfoModal extends React.Component {
  state = { open: false };

  show =  () => this.setState({ open: true });
  close = () => this.setState({ open: false });

  render() {
    const { open } = this.state;
    var button;
    if(this.props.small){
      button = (<Button color={'teal'} icon onClick={this.show}>
      <Icon name='info circle'/></Button>);
    }else{
      button = (<Button color={'teal'} icon labelPosition='left' onClick={this.show}>
      <Icon name='info circle'/>ABOUT</Button>);
    }
    return (
      <div>
      {button}
        <Modal dimmer='blurring'  size='small' open={open} onClose={this.close}>
          <Modal.Header>
            <Icon size={"large"} name='bug'/>
          Artificial Life Simulator</Modal.Header>
          <Modal.Content >
            <Modal.Description>
            <h3>What is this?</h3>
            This is a simulation of natural selection in a virtual world.  Virtual
            bugs compete for virtual food.  Only the best bugs are able to get enough
            food to reproduce and grow their population.  Food is green and bugs
            are red.  At every time step, bugs move, consume energy, try to eat food,
            reproduce if they have enough energy, or die if they are out of energy.

            <h3>How is this natural selection?</h3>
            If bugs have enough energy they will asexually reproduce (like bacteria),
            and split into two bugs.  There is a small chance its genome will undergo
            a random mutation. The best mutations will have the best chance at
            acquiring more food, while poor mutations will starve and die.  The
            simulation is an evolutionary algorithm to produce the best bug genome.

            <h3>What are the bug's genomes?</h3>
            Every time a bug moves there is a probability of what direction it will move.
            The genome represents the probability a bug will move in a certain direction.
            Bugs need to move to find food.

            <h3>A little history...</h3>
            <p>I first created a version of this program in Turbo C in 1993 as part
            of a Strand Research Fellowship at University School in Cleveland Ohio.
            For the 50th Anniversary of the Strand Fellowship, I
            updated the code (long lost unfortunately!) in a modern web implementation.
            Unlike the original one, this versions lets you change setting on the fly,
            runs about 100 times faster and doesn't have a memory leak that my 16
            year old, self-taught self couldn't find, and it only took me
            a weekend to write (not the 1 year of the original)!
            </p>
            <p><a href="https://github.com/nickzinn/ArtificialLife">Source code is here.</a></p>
            <em>Nicholas Zinn (nickzinn@gmail.com), 2017.</em>
            </Modal.Description>
          </Modal.Content>
          <Modal.Actions>
            <Button positive  content="Close" onClick={this.close} />
          </Modal.Actions>
        </Modal>
      </div>
    )
  }
}

export default InfoModal;

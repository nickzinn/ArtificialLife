import React from 'react';
import PropTypes from 'prop-types';

import {IconButton, DialogTitle, Dialog, DialogContent, DialogActions, Button, Slide } from '@material-ui/core';
import withMobileDialog from '@material-ui/core/withMobileDialog';

function Transition(props) {
    return <Slide direction="up" {...props} />;
}

const styles = {
};

class ButtonModal extends React.Component {
    state = {
        open: false,
    };

    handleOpen = () => {
        this.setState({ open: true });
    };

    handleClose = () => {
        this.setState({ open: false });
    };

    render() {
        const { fullScreen } = this.props;
        return (
            <React.Fragment>
                <IconButton color="inherit" aria-label="Edit" onClick={this.handleOpen}>
                    {this.props.dialogButton}
                </IconButton>
                <Dialog
                    aria-labelledby="modal-title"
                    open={this.state.open}
                    onClose={this.handleClose}
                    fullScreen={fullScreen}
                    scroll={'paper'}
                    TransitionComponent={Transition}
                    maxWidth="md"
                >
                    <DialogTitle id="modal-title">
                        {this.props.dialogTitle}
                    </DialogTitle>
                    <DialogContent>
                        {this.props.children}
                    </DialogContent>
                    <DialogActions>
                        <Button onClick={this.handleClose} color="primary">
                            CLOSE
              </Button>
                    </DialogActions>
                </Dialog>
            </React.Fragment>
        );
    }
}

ButtonModal.propTypes = {
    onClose: PropTypes.func
};

const ButtonModalWrapped = withMobileDialog(styles)(ButtonModal);

export default ButtonModalWrapped;

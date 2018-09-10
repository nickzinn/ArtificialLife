import React from 'react';
import BottomNavigation from '@material-ui/core/BottomNavigation';
import BottomNavigationAction from '@material-ui/core/BottomNavigationAction';
import Hidden from '@material-ui/core/Hidden';
import ShowChart from '@material-ui/icons/ShowChart';
import SpaIcon from '@material-ui/icons/Spa';
import LocationOnIcon from '@material-ui/icons/LocationOn';
import ListIcon from '@material-ui/icons/List';


class BottomNavigationComponent extends React.Component {
    render() {

        return (
            <Hidden smUp>
            <BottomNavigation
                style={{ position: "fixed", bottom: "0", width: "100%" , zIndex:1001}}
                value={this.props.value}
                onChange={this.props.onChange}
                showLabels
            >
                <BottomNavigationAction label="Simulation" value="simulation" icon={<SpaIcon />} />
                <BottomNavigationAction label="Charts" value="charts" icon={<ShowChart />} />
                <BottomNavigationAction label="Settings" value="settings" icon={<ListIcon />} />
                <BottomNavigationAction label="Stats" value="stats" icon={<LocationOnIcon />} />
            </BottomNavigation>
            </Hidden>
        );
    }
}

export default BottomNavigationComponent;

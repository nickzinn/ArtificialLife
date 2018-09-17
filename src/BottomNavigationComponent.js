import React from 'react';
import { BottomNavigation, BottomNavigationAction, Hidden } from '@material-ui/core';
import ShowChart from '@material-ui/icons/ShowChart';
import SpaIcon from '@material-ui/icons/Spa';
import LocationOnIcon from '@material-ui/icons/LocationOn';
import ListIcon from '@material-ui/icons/List';


class BottomNavigationComponent extends React.Component {
    render() {
        const {value, onChange} = this.props;
        return (
            <Hidden smUp>
            <BottomNavigation
                style={{ position: "fixed", bottom: "0", width: "100%" , zIndex:1001}}
                value={value}
                onChange={onChange}
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

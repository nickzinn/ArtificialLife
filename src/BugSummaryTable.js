import React from 'react';
import './BugSummaryTable.css';
import { Table, TableBody, TableCell, TableHead, TableRow, Paper, Typography, CardContent } from '@material-ui/core';
import { withStyles } from '@material-ui/core/styles';

const TightTableCell = withStyles({
    root: {
        paddingRight: '10px',
        paddingLeft: '10px'
    }
})(TableCell);

const BugSummaryTable = ({ bugStats: stats, summaryStats: { gps, fps, bugCount, food } }) => {
    if (stats.length === 0) {
        stats.push([0, 0, [1, 1, 1, 1, 1, 1, 1, 1]])
    }
    const rows = stats.slice(0, 5).map(function (stat, index) {
        return(
            <TableRow key={index} >
                <TightTableCell numeric style={{ color: stat[3] }}>{stat[0]}</TightTableCell>
                <TightTableCell numeric style={{ color: stat[3] }}>{stat[1]}</TightTableCell>
                <TightTableCell style={{ color: stat[3] }}>[{stat[2].map((x) => x.toFixed(2)).join(' ')}]</TightTableCell>
            </TableRow>
        );
    });
    return (
        <Paper style={{ width: '100%' }} >
            <CardContent>
                <Typography variant="subheading" id="performance" >
                    GPS: {gps} FPS: {fps} Bugs: {bugCount} Food: {food}</Typography>
            </CardContent>
            <Table style={{ minWidth: "324px" }} padding={'dense'} >
                <TableHead>
                    <TableRow>
                        <TightTableCell>ID</TightTableCell>
                        <TightTableCell>#</TightTableCell>
                        <TightTableCell>Genome</TightTableCell>
                    </TableRow>
                </TableHead>
                <TableBody>
                    {rows}
                </TableBody>
            </Table>
        </Paper>
    );
}
export default BugSummaryTable;
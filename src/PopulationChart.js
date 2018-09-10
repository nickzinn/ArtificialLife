import React from 'react'
import Highcharts from 'highcharts'

const options = {
    credits: { enabled: false },
    boost: { useGPUTranslations: true },
    title: { text: '' },
    tooltip: { valueDecimals: 0 },
    yAxis: [{
        lineWidth: 1,
        allowDecimals: false,
        title: {
            text: 'Bug Population'
        }
    }, {
        lineWidth: 1,
        allowDecimals: false,
        opposite: true,
        title: {
            text: 'Food Count'
        }
    }],
    series: [{
        data: [],
        lineWidth: 0.5,
        name: "Population"
    }, {
        data: [],
        lineWidth: 0.5,
        yAxis: 1,
        name: "Food"
    }]
};

export default class PopulationChart extends React.Component {

    componentDidMount() {
        let newOptions = JSON.parse(JSON.stringify(options));
        this.props.populationHistory.forEach((d, i) => newOptions.series[i].data = d);
        this.chart = Highcharts.chart('populationChart2',newOptions);
    }

    componentWillUnmount() {
        this.chart.destroy()
    }


    render() {
        //make size a little smaller by 10 px.
        //document.getElementById('populationChart').style.width = width-10;
        if(this.chart){
            this.props.populationHistory.forEach((d, i) => this.chart.series[i].setData(d));
        }
        return (
            <div id="populationChart2" style={{ height: "300px" }}></div>
        );
    }
}
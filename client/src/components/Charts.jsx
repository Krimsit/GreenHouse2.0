import React from 'react';
import ReactDOM from 'react-dom';

import './index.css';
import Temp from './Chart/Temp.jsx';
import HumSoil from './Chart/HumSoil.jsx';
import HumAirSoil from './Chart/HumAirSoil.jsx';
import Idr from './Chart/Idr.jsx';

import ee from "../events/ee.js"


class Charts extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      activeChart: "Idr",
      _max_time_showed: 60
    };
  };

  componentWillMount() {
    let self = this;
    let _data = this.state.main_data;

    ee.on("chart_conf", data => {
      switch(data.type){
        case "Idr":
          _data.Idr.runing = data.payload;break;
      }
      self.setState({main_data: _data})
    })

    ee.on("navigate", data => {
      this.setState({activeChart: data.payload});
    })
    
  }
  render() {
    return(
      <div className="container_charts" style={{width: "73%", float: "right"}}>
        {(() => {
            switch (this.state.activeChart) {
                case 'Idr':
                  return <Idr />
                case 'Temp':
                  return <Temp />
            }
        })()}
      </div>
    )
  }
}

export default Charts;
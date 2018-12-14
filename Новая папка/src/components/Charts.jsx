import React from 'react';
import ReactDOM from 'react-dom';
import io from 'socket.io-client';
import Temp from './Chart/Temp.jsx';
import HumSoil from './Chart/HumSoil.jsx';
import HumAirSoil from './Chart/HumAirSoil.jsx';
import Idr from './Chart/Idr.jsx';
import './index.css';

var socket = io('192.168.0.138:9000');

class Charts extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
    };
  };

  componentWillMount() {
    socket.on("click", (data) => {
      this.setState({ button: data.data }); 
    });
  }
  render() {
    return(
      <div className="container_charts" style={{width: "950px", float: "right"}}>
        <Temp />
        <HumSoil />
        <HumAirSoil />
        <Idr />
      </div>
    )
  }
}

export default Charts;
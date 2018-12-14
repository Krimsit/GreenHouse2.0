import React from 'react';
import ReactDOM from 'react-dom';
import io from 'socket.io-client';
import { Line } from 'react-chartjs-2';

var socket = io('192.168.0.138:9000');

class Temp extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      data: { 
        labels: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],
        datasets: [{
        label: "Temperature",
        backgroundColor: 'rgb(255, 99, 132)',
        borderColor: 'rgb(255, 99, 132)',
        data: [0, 10, 5, 2, 20, 30, 45],
        }]
      }
    };
  };

  componentWillMount() {

  }

  render() {
    return(
      <div>HumSoil</div>
    )
  }
}

export default Temp;
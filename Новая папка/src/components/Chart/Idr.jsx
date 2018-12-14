import React from 'react';
import ReactDOM from 'react-dom';
import io from 'socket.io-client';

var socket = io('192.168.0.138:9000');

class Idr extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
    };
  };

  componentWillMount() {

  }

  render() {
    return(
      <div>Idr</div>
    )
  }
}

export default Idr;
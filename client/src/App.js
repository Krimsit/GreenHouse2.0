import React from 'react';
import ReactDOM from 'react-dom';
import io from 'socket.io-client';

import Panel from './components/Panel.jsx';
import Charts from './components/Charts.jsx';
import ee from "./events/ee.js";


var socket = io('localhost:9000');

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      buttonState: false,
      button: false
    };
  };

  componentWillMount() {
    // Events

    socket.on("GET_DATA", (data) => {
    	// console.log(data)
    	ee.emit("GET_DATA", data)
    });

    ee.on("navigate", data => {
    	socket.emit("change_get_data", {type: data.payload, payload: 1});
    })


  }

  handleWelcome() {
    var bS = !this.state.buttonState
    socket.emit("welcome", { data: bS });
    this.setState({ buttonState: bS});
  }

  render() {
    return(
      <div>
        <Panel />
        <Charts />
      </div>
    );
  }
}

export default App;
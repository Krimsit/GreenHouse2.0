import React from 'react';
import ReactDOM from 'react-dom';
import io from 'socket.io-client';

import Panel from './components/Panel.jsx';
import Charts from './components/Charts.jsx';
import Controls from './components/controls/Colntrols.jsx';
import Welcome from './components/welcome.jsx';


import ee from "./events/ee.js";


var socket = io('localhost:9000');

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      active: "Chart"
    };
  };

  componentWillMount() {
    let self = this;
    // Events

    socket.on("GET_DATA", (data) => {
    	// console.log(data)
    	ee.emit("GET_DATA", data)
    });
    ee.on("navigate", data => {
    	switch(data.payload){
    		case "Controls":
    			self.setState({active: "Controls"});break;
    		case "Idr":
    		case "Temp":
    			socket.emit("change_get_data", {type: data.payload, payload: 1});
    			self.setState({active: "Chart"});break;
    		case "Introduction":
    			self.setState({active: "Introduction"});break;
    	}

    })
   	ee.on("control", data => {
   		socket.emit("control", data)
   	});


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
       	{(() => {
					switch(this.state.active){
						case "Chart":
							return <Charts />
						case "Controls":
							return <Controls/>
						case "Introduction":
							return <Welcome text={"Введение"}/>
					}
        })()}
       
      </div>
    );
  }
}

export default App;
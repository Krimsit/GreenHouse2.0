import React from 'react';
import ReactDOM from 'react-dom';
import io from 'socket.io-client';
import Panel from './components/Panel.jsx';
import Charts from './components/Charts.jsx';
var socket = io('192.168.0.138:9000');

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      buttonState: false,
      button: false
    };
  };

  componentWillMount() {
    socket.on("click", (data) => {
      this.setState({ button: data.data }); 
    });
  }

  handleWelcome() {
    var bS = !this.state.buttonState
    socket.emit("welcome", { data: bS });
    this.setState({ buttonState: bS});
  }

  handleChange(e) {
    console.log(Math.round(2.55 * e.target.value));
    socket.emit("change", { data: Math.round(2.55 * e.target.value) });
  }

  render() {
    return(
      <div>
        <Charts />
        <Panel />
      </div>
    );
  }
}

export default App;
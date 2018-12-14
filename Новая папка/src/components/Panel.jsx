import React from 'react';
import ReactDOM from 'react-dom';
import io from 'socket.io-client';
import './index.css';

var socket = io('192.168.0.138:9000');

class Panel extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      buttonState: false,
      button: false,
      light: false
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

  handleChangeLight(e) {
    this.setState({ light: !this.state.light });
  }

  render() {
    return(
      <div className="container">
        <button className="btn_welcome" onClick={this.handleWelcome.bind(this)}>Weclome</button>
        <br/>
        <button className="btn_light"   onClick={this.handleChangeLight.bind(this)} style={{backgroundColor: (this.state.light ? "#fefe22" : "#efefef"), borderColor: (this.state.light ? "#fefe22" : "#efefef")}}>Lithg On/Off</button>
        <br/>
        <input className="btn_light_range" type="range" onChange={(e) => this.handleChange(e)}/>
        <br/>
        <div className="btn_state" style={{backgroundColor: (this.state.button ? "#57a639" : "#ff0033")}}>Button State</div>
      </div>
    );
  }
}

export default Panel;
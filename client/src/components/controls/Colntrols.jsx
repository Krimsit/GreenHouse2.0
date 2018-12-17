import React from "react";
import ReactDOM from 'react-dom';
import ToggleButton from 'react-toggle-button';

import ee from "../../events/ee.js";

class Control extends React.Component{
	constructor(props) {
    super(props);
    this.state = {
    	light: false,
    	temp: false,
    	pomp: false,
    	NORMS: {},
    	autoMode: false
    };
  }
  handleLightToggle(light){
  	this.setState({light: !light});
  	ee.emit("control", {type: "light", payload: !light})
  }
  handleTempToggle(temp){
  	this.setState({temp: !temp});
  	ee.emit("control", {type: "temp", payload: !temp})
  }
  handlePompaToggle(pomp){
  	this.setState({pomp: !pomp});
  	ee.emit("control", {type: "pomp", payload: !pomp})
  }
  handleChange(){
  	ee.emit('GIVE', {
  		Idr: +ReactDOM.findDOMNode(this.Idr).value,
  		Temp: +ReactDOM.findDOMNode(this.Temp).value,
  		HumSoil: +ReactDOM.findDOMNode(this.HumSoil).value,
  		HumAir: +ReactDOM.findDOMNode(this.HumAir).value
  	});
  }
  handleAutoMode(){
  	ee.emit('autoMode', {
  		payload: !this.state.autoMode
  	})
  	this.setState({ autoMode: !this.state.autoMode })
  	console.log(this.state.autoMode);
  }

  setValueInput(node, value) {
  	let _node = ReactDOM.findDOMNode(node)
  	if(_node) {
  		_node.value = value;
  	}
  }

  componentDidMount(){
  	let self = this;
  	ee.on('INIT', data => {
  		switch(data.type) {
  			case 'NORMS':{
  				this.setState({ NORMS: data.payload });
  				for(let i in data.payload) {
  					self.setValueInput(self[i], data.payload[i]);
  				} 
  			};
  			break;
  		}
  	});
  }

	render(){
		return (
			<div className="controls">
				<div className="control_panel">
					<div className="main_control">
						<div className="item_main_control light"><span>Свет: </span>
							<ToggleButton
						  value={this.state.light || false}
						  onToggle={(val) => this.handleLightToggle(val)} />
						</div>
						<div className="item_main_control temp"><span>Обогреватель: </span>
							<ToggleButton
						  value={this.state.temp || false}
						  onToggle={(val) => this.handleTempToggle(val)} /></div>
						<div className="item_main_control pomp"><span>Помпа: </span>
							<ToggleButton
						  value={this.state.pomp || false}
						  onToggle={(val) => this.handlePompaToggle(val)} /></div>
					</div>
					<div className="main_control_value">
						<div className="item">
							<p>Освещение</p>
							<input ref={(node) => this.Idr = node} type="number"/>
						</div>
						<div className="item">
							<p>Температура</p>
							<input ref={(node) => this.Temp = node} type="number"/>
						</div>
						<div className="item">
							<p>Влажность почвы</p>
							<input ref={(node) => this.HumSoil = node} type="number"/>
						</div>
						<div className="item">
							<p>Влажность воздуха</p>
							<input ref={(node) => this.HumAir = node} type="number"/>
						</div>
						<button className="button" onClick={this.handleChange.bind(this)}>Отправить</button>							
					</div>
				</div>
				<div className="auto">
					<p>Автономный режим: <input className="btn_auto" onChange={this.handleAutoMode.bind(this)} type="checkbox"/></p>
				</div>
			</div>
		);
	}
}
export default Control;
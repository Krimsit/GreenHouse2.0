import React from "react";
import ToggleButton from 'react-toggle-button';

import ee from "../../events/ee.js";

class Control extends React.Component{
	constructor(props) {
    super(props);
    this.state = {
    	light: false,
    	temp: false,
    	pomp: false
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
	render(){
		return (
			<div className="controls">
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
			</div>
		);
	}
}
export default Control;
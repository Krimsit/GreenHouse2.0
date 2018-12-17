import React from "react";
import ee from "../events/ee.js";

class Welcome extends React.Component{
	constructor(props){
		super(props);
	}


	render(){
		return (
		  <div>
		  		{
		  			this.props.text
		  		}
		  </div>
		);
	}
}
export default Welcome;
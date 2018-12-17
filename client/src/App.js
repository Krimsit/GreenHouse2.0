
import React from 'react';
import ReactDOM from 'react-dom';
import io from 'socket.io-client';

import Panel from './components/Panel.jsx';
import Charts from './components/Charts.jsx';
import Controls from './components/controls/Colntrols.jsx';
import Welcome from './components/welcome.jsx';

import "./App.css";


import ee from "./events/ee.js";

//192.168.1.230:9000 Пароль для Asus 1001: 89056489651
var socket = io('192.168.0.138:9000');

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      active: "Chart",
      NORMS: {}
    };
  };

  componentWillMount() {
    let self = this;
    // Events

    socket.on('INIT', (data) => {
      switch(data.type){
        case 'NORMS':
          ee.emit('INIT', data)
          this.setState({ NORMS: data.payload });
          break;
      }
    })

    ee.on('GIVE', data => {
      console.log(data)
      socket.emit('changeNORMS', data);
    });

    ee.on('autoMode', data => {
      socket.emit('autoMode', data)
    })

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
        case "Manual":
          self.setState({active: "Manual"});break;
        case "Team":
          self.setState({active: "Team"});break;
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
							return <Welcome text={<p>Добро пожаловать! <br/> Мы представляем вам программное обеспечение для умной теплицы 'SmartGreenHouse 2.0'</p>}/>
            case "Manual":
              return <Welcome text={<p>Ссылка на скачивание инструкции по управлению умной теплицей <br /> <a target="_blank" href="https://github.com/Krimsit/GreenHouse2.0/blob/dev/User_Manual.pdf">Инструкция</a></p>}/>
            case "Team":
              return <Welcome text={<div className="team_container" style={{width: "73%", float: "right"}}>
                                      <div className="contributor">
                                        <p className="team_name">Шенягин Даниил, Автор проекта<ul>
                                          <li>занимается серверной частью</li>
                                        </ul></p>
                                        <a className="team_link" target="_blank" href="https://vk.com/daniil00t"><i className="fab fa-vk"></i></a>
                                      </div><br/>
                                      <div className="contributor">
                                        <p className="team_name">Субботин Андрей<ul>
                                          <li>занимается клиентской частью</li>
                                        </ul></p>
                                        <a className="team_link" target="_blank" href="https://vk.com/krimsit"><i className="fab fa-vk"></i></a>
                                      </div><br/>
                                      <div className="contributor">
                                        <p className="team_name">Лукьянов Андрей<ul>
                                          <li>помогает Шенягину Даниилу</li>
                                        </ul></p>
                                        <a className="team_link" target="_blank" href="https://vk.com/andrey_luk"><i className="fab fa-vk"></i></a>
                                      </div>
                                    </div>}/>
					}
        })()}
       
      </div>
    );
  }
}

export default App;
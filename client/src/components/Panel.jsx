import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import ee from "../events/ee.js";


class Panel extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      main_list: [
        {
          name: "Графики",
          list: ["График освещенности", "График температуры", "График Влажности воздуха", "График Влажности Почвы"]
        },
        {
          name: "Управление умной теплицей",
          list: ["Управление"]
        },
        {
          name: "Полная статистика",
          list: ["Cтатистика"]
        },
        {
          name: "#OurFeatures",
          list: ["First Start", "OurTeam", "News"]
        }
      ],
      activeSubMenu: [-1, -1],
    };
  };

  componentDidMount() {
    let hash = window.location.hash;
    if(hash){
      let _hash = hash.substr(1, hash.length-1)
      switch(_hash){
        case "G_Idr":
          this.setState({activeSubMenu: [0, 0]});
          ee.emit("navigate", {payload: "Idr"});break;
        case "G_Temp":
          this.setState({activeSubMenu: [0, 1]});
          ee.emit("navigate", {payload: "Temp"});break;
      }
    }
  }
  handleClickLI(j){
  	if(j != this.state.activeSubMenu[0]){
	    this.setState({activeSubMenu: [j, this.state.activeSubMenu[1]]})
  	}
  }
  handleClickSubLI(j){
    console.log(this.state.activeSubMenu);
    switch(this.state.activeSubMenu[0]){
      case 0:
        switch(j){
          case 0:
            ee.emit("navigate", {payload: "Idr"});
            window.location.hash = "G_Idr";
            break;
          case 1:
            ee.emit("navigate", {payload: "Temp"});
            window.location.hash = "G_Temp";
            break;
        };break;
    }
    if(j != this.state.activeSubMenu[1]){
      this.setState({activeSubMenu: [this.state.activeSubMenu[0], j]})
    }

  }

  render() {
    return(
      <div className="container">
        <h1 className="welcome">SmartGreenHouse<span className="version">2.0</span></h1>
        <ul className="menu">
          {
            this.state.main_list.map((i, j) =>
              <li onClick={this.handleClickLI.bind(this, j)}>
                {i.name}
              <i className="fas fa-sort-down"></i>
              <ul className="subMenu" style={j == this.state.activeSubMenu[0] ? {display: "block"} : {display: "none"}}>
                {
                  i.list.map((l, p) => 
										<li onClick={this.handleClickSubLI.bind(this, p)} className={p == this.state.activeSubMenu[1] && j == this.state.activeSubMenu[0] ? "subMenuItem active" : "subMenuItem"}>{l}</li>
                  )
                }
              </ul>
              </li>
            )
          }
        </ul>
        <p className="CopyRight">&copy;2018 Andrey Subbotin <br/>Daniil Shenyagin</p>
      </div>
    );
  }
}

export default Panel;
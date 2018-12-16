import React from 'react';
import LineChart from './components/LineChart/LineChart';
import ee from "./../../events/ee.js";

Array.prototype.max = function() {
  return Math.max.apply(null, this);
};

Array.prototype.min = function() {
  return Math.min.apply(null, this);
};

class Idr extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      data: [
        { key: 'Idr', values: [ { x: 0, y: 1 } ] },
        { key: "min", values: [ {x: -1, y: -1}, {x: -1, y: -1} ] },
        { key: "middle", values: [ {x: -1, y: -1}, {x: -1, y: -1} ] },
        { key: "max", fill: "#000", values: [ {x: -1, y: -1}, {x: -1, y: -1} ] }
      ],
      __arr: [],
      statis: {
        _min: -1,
        _middle: -1,
        _max: -1
      },
      
      iter: 0,
      _max_time_showed: 60,
      show: true
    };
  };

  handlePlay() {
    this.setState({ show: true });
  }
  handleStop(){
    this.setState({ show: false });
  }
  calculations(arr){
    let statis = this.state.statis;
    let sum = arr.reduce(function(a, b) { return a + b; }, 0);
    let count = arr.length;

    statis._min = arr.min();
    statis._max = arr.max();
    statis._middle = sum / count;

    this.setState({statis: statis})
  }
  drawG(){
    let statis = this.state.statis;
    let data = this.state.data;
    let start;
    let finish;
    if(this.state.iter < this.state._max_time_showed){
      start = 0;
      finish = this.state.iter;
    }
    else{
      start = this.state.iter - this.state._max_time_showed;
      finish = this.state.iter;
    }
    // Min
    data[1].values[0].x = start;
    data[1].values[1].x = finish-1;

    data[1].values[0].y = statis._min;
    data[1].values[1].y = statis._min
    // Middle

    data[2].values[0].x = start;
    data[2].values[1].x = finish-1;

    data[2].values[0].y = statis._middle;
    data[2].values[1].y = statis._middle;

    // Max
    data[3].values[0].x = start;
    data[3].values[1].x = finish-1;

    data[3].values[0].y = statis._max;
    data[3].values[1].y = statis._max;

    this.setState({data: data});
  }
  componentWillMount(){
    var self = this;
    ee.on("GET_DATA", data => {
      if(data.type == "Idr" && self.state.show){
        var _arr = this.state.data;
        var __arr = this.state.__arr;
        var _iter = this.state.iter;

        if(self.state._max_time_showed){
          if(_arr[0].values.length >= self.state._max_time_showed) _arr[0].values.splice(0, 1);
        }

        _arr[0].values.push({x: _iter, y: data.payload});
        __arr.push(data.payload);

        _iter++;
        self.setState({data: _arr, iter: _iter, __arr: __arr});
        self.calculations(__arr);
        self.drawG();
      }
    })
  }

  render() {
    return(
      <div>
        <h1 className="text-center">График освещенности</h1>
        <LineChart 
          data={this.state.data}
          height={300}
          xAxis={{label: "Время(с)"}}
          yAxis={{label: "Освещенность(%)"}}
        />
        <i onClick={this.handleStop.bind(this)} className="fas fa-pause stop_chart chart_conf"></i>
        <i onClick={this.handlePlay.bind(this)} className="fas fa-play play_chart chart_conf"></i>
        <div className="main_cnt">
          <div className="statistics">
            <div className="stas_info _min">Минимум: <span className="mark">{this.state.statis._min}</span></div>
            <div className="stas_info _middle">Среднее значение: <span className="mark">{this.state.statis._middle.toFixed(2)}</span></div>
            <div className="stas_info _max">Максимум: <span className="mark">{this.state.statis._max}</span></div>
          </div>
        </div>
        
      </div>
    )
  }
}

export default Idr;
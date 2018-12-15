import React from 'react';
import ReactDOM from 'react-dom';
import io from 'socket.io-client';
import LineChart from './components/LineChart/LineChart';

var socket = io('192.168.0.138:9000');

class Idr extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      data: [
        { key: 'Idr', values: [ { x: 'A', y: 23 } ] }
      ],
      iter: 0,
      _max_time_showed: -1,
      show: true
    };
  };

  handleChange() {
    this.setState({ show: !this.state.show });
  }

  componentWillMount() {
    var _arr = this.state.data;
    var _iter = this.state.iter;

    this.setState({ _max_time_showed: this.props.data._max_time_showed });

    var self = this;
    socket.on("tmp", function(data){
      if(self.state._max_time_showed){

      if(_arr[0].values.length >= self.state._max_time_showed) {
        _arr[0].values.splice(0, 1);
          }
        }
        _arr[0].values.push({x: _iter, y: data.data});
        _iter++;
        if(self.state.show){

        self.setState({data: _arr, iter: _iter});
      }
      });
  }

  render() {
    return(
      <div>
        <LineChart 
          data={this.state.data}
        />
        <button onClick={this.handleChange.bind(this)}>Stop</button>
      </div>
    )
  }
}

export default Idr;
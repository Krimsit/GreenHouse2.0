import React from 'react';
import LineChart from './components/LineChart/LineChart';

class HumSoil extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      data: [
        { key: 'Idr', values: [ { x: 'A', y: 23 } ] }
      ],
      iter: 0
    };
  };

  // componentDidMount() {
  //   var _arr = this.state.data;
  //   var _iter = this.state.iter;
  //   console.log(_arr);
    
  //   var self = this;
  //   socket.on("tmp", function(data){
  //     console.log(data.data);
  //     _arr[0].values.push({x: _iter, y: data.data});
  //     _iter++;
  //     self.setState({data: _arr, iter: _iter});
  //   });
  //   console.log(this.state);
  // }

  render() {
    return(
      <LineChart 
        data={this.state.data}
      />
    )
  }
}

export default HumSoil;
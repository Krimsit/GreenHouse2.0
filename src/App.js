import React from 'react';
import ReactDOM from 'react-dom';
import { Line } from 'react-chartjs-2';
import ReactInterval from 'react-interval';

const chart1 = {
  labels: ['Team1', 'Team2', 'Team3', 'Team4', 'Team5'],
  datasets: [{
    label: 'Data',
    data: [503, 385, 270, 133, 65],
    fill: false,
    backgroundColor: [
      '#000000'
    ],
    borderColor: [
      '#4DB6AC'
    ]
  }],
  name: 'chart1'
};
const chart2 = {
  labels: ['Team1', 'Team2', 'Team3', 'Team4', 'Team5'],
  datasets: [{
    label: 'Data',
    data: [303, 185, 470, 313, 65],
    fill: false,
    backgroundColor: [
      '#000000'
    ],
    borderColor: [
      '#4DB6AC'
    ]
  }],
  name: 'chart2'
};
class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      chartData: chart1,
      nameChart: 1,
      updated: true
    }
  }

  // handleUpdate() {
  //   if (this.state.nameChart == 1){
  //     this.setState({chartData: chart2, nameChart: 2});

  //   }
  //   else{
  //     this.setState({chartData: chart1, nameChart: 1});
  //   }

  // }
  render() {
    return(
      <div>
        <Line data={this.state.chartData} width={650} height={400} />
        <ReactInterval timeout={5000} enabled={true}
          callback={() => this.setState({chartData: chart2, nameChart: 2})}/>
      </div>
    );
  }
}

export default App;

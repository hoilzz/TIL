import React, { Component } from 'react';
import logo from '../assets/logo.svg';
import '../css/App.css';
import ObjectiveContainer from '../containers/ObjectiveContainer';


class App extends Component {
  render() {
    return (
      <div className="App">
        <div className="App-header">
          <img src={logo} className="App-logo" alt="logo" />
          <h2>s u r v e y</h2>
        </div>
        <ObjectiveContainer/>
      </div>
    );
  }
}

export default App;

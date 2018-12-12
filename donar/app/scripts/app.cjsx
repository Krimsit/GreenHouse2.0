React = require 'react'
io = require "socket.io-client"
socket = io('192.168.100.9:3000')

App = React.createClass
  displayName: 'App'
  getInitialState: ->
    buttonState: false
    button: false
  handleWelcome: ->
    socket.emit "welcome", data: !@state.buttonState
    @setState buttonState: !@state.buttonState
  handleChange: (e)->
    console.log Math.round(2.55 * e.target.value)
    socket.emit "change", data: Math.round(2.55 * e.target.value)
  componentWillMount: ->
    socket.on "click", (data)=>
      @setState button: data.data
  render: ->
    <div>
      <button onClick={@handleWelcome}>Weclome</button>

      <br/>

      <input type="range" onChange={(e) => @handleChange e}/>

      <br />

      <div style={{width: "100px", heigth: "100px", backgroundColor: (if @state.button then "green" else "red"), color: "white"}}>Button State</div>
    </div>

module.exports = App
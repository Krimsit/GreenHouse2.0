React = require 'react'
Tabs = require './Tabs/Tabs'
Tab = require './Tabs/Tab'

App = React.createClass
  displayName: 'App'

  render: ->
    <div className="wrapper">
      <Tabs>
        <Tab label="Вкладка 1">
          <h3>Содержимое вкладки 1</h3>
          <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit...</p>
        </Tab>
        <Tab label="Вкладка 2">
          <h3>Содержимое вкладки 2</h3>
          <p>sed do eiusmod tempor incididunt ut labore et dolore...</p>
        </Tab>
      </Tabs>
    </div>

module.exports = App
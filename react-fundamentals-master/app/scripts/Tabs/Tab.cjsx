classSet = require 'react/lib/cx'
React = require 'react'

Tab = React.createClass
  displayName: 'Tab'

  propTypes:
    label: React.PropTypes.string.isRequired
    selected: React.PropTypes.bool.isRequired
    index: React.PropTypes.number.isRequired
    onClick: React.PropTypes.func.isRequired

  render: ->
    tabClass = classSet
      'mui-tab-item': true
      'mui-tab-is-active': @props.selected
      
    <div className={tabClass}
         onClick={@handleClick}>
      {@props.label}
    </div>

  handleClick: ->
    @props.onClick @props.index

module.exports = Tab
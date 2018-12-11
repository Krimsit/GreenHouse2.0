React = require 'react'

TabTemplate = React.createClass
  displayName: 'TabTemplate'

  render: ->
    <div className="mui-tab-template">
      <div className="tab-template-container">
        {@props.children}
      </div>
    </div>

module.exports = TabTemplate
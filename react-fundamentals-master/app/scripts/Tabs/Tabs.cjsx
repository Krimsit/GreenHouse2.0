React = require 'react'
cloneWithProps = require 'react/lib/cloneWithProps'
TabTemplate = require './TabTemplate'

Tabs = React.createClass
  displayName: 'Tabs'

  getInitialState: ->
    selectedIndex: 0

  render: ->
    currentTemplate = null
    tabs = React.Children.map @props.children, (tab, index) =>
      currentTemplate = tab.props.children if @state.selectedIndex == index
      cloneWithProps tab, {
        selected: @state.selectedIndex == index
        index: index
        onClick: @handleTabClick
      }
    <div className="mui-tabs-container">
      <div className="mui-tab-item-container">
        {tabs}
        <TabTemplate>
          {currentTemplate}
        </TabTemplate>
      </div>
    </div>

  handleTabClick: (tabIndex) ->
    @setState(selectedIndex: tabIndex)

module.exports = Tabs
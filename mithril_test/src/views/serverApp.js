// const m = require('mithril')
const Server = require('../models/Server')

module.exports = {
  oninit: function () {
    Server.init()
  },
  view: function () {
    Server.getText()
  }
}

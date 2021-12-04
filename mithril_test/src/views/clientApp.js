const m = require('mithril')
const Client = require('../models/Client')

module.exports = {
  oninit: function () {
    console.log('Client')
  },
  view: function () {
    return m('div', Client.getText())
  }
}

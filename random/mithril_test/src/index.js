const m = require('mithril')
const Layout = require('./views/Layout')
const serverApp = require('./views/serverApp')
const clientApp = require('./views/clientApp')

m.route(document.body, '/client', {
  '/server': { render: function () { return m(Layout, m(serverApp)) } },
  '/client': { render: function () { return m(Layout, m(clientApp)) } }
})

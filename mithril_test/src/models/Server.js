const m = require('mithril')
const Config = require('../../Config')
const server = require('http').createServer()
const io = require('socket.io')(server)

const Server = {
  getText: function () { return m('div', 'Hello Server!') },
  getConfig: function () { return Config.url },
  init: function () {
    io.on('connection', client => {
      client.on('event', data => { /* … */ })
      client.on('disconnect', () => { /* … */ })
    })
    server.listen(3000)
  }
  /* save: function () {
      const isNew = (Category.current.id === undefined)
      return m
        .request({
          method: (isNew ? 'POST' : 'PUT'),
          url: Config.url + '/category' +
          (isNew ? '' : ('/' + Category.current.id)),
          body: Category.current,
          headers: Login.headers_get()
        })
        .then(function () {
          return m.request({
            method: 'PUT',
            url: Config.url + '/lua',
            headers: Login.headers_get()
          })
        })
    } */
}

module.exports = Server

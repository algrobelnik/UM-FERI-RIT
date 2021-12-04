const m = require('mithril')
const Config = require('../../Config')

const Client = {
  getText: function () { return m('div', 'Hello Client!') },
  getConfig: function () { return Config.url }
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

module.exports = Client

const m = require('mithril')

module.exports = {
  view: function (vnode) {
    return m('main.layout', [
      m('nav.menu',
        [
          m(m.route.Link, { href: '/server' }, 'Server'),
          m(m.route.Link, { href: '/client' }, 'Client')
        ]),
      m('section', vnode.children)
    ])
  }
}

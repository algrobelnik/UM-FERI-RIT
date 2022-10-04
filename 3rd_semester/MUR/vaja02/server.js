const server = require('http').createServer()

const io = require('socket.io')(server)
const os = require('os')
const Encryption = require('node_triple_des')
const port = 3000

function formatDate (num) {
  return (num > 9 ? '' + num : '0' + num)
}

io.on('connection', (socket) => {
  console.log(`Client [${socket.id}] connected`)
  socket.on('message', (data, fn) => {
    try {
      const type = data[0]
      data = data.substring(1)
      switch (type) {
        case 'A': {
          if (data.length > 0) throw new Error('Only empty message supported')
          const address = socket.request.connection._peername
          console.log(`Hello [${address.address}:${address.port}]`)
          fn(`Hello [${address.address}:${address.port}]`)
          break
        }
        case 'B': {
          if (data.length > 0) throw new Error('Only empty message supported')
          const current = new Date()
          const cDate = formatDate(current.getFullYear()) + '-' + formatDate(current.getMonth() + 1) + '-' + formatDate(current.getDate())
          const cTime = formatDate(current.getHours()) + ':' + formatDate(current.getMinutes()) + ':' + formatDate(current.getSeconds())
          const dateTime = cDate + ' ' + cTime
          console.log('Current time: ' + dateTime)
          fn('Current time: ' + dateTime)
          break
        }
        case 'C': {
          if (data !== '') throw new Error('Only empty message supported')
          console.log(__dirname)
          fn(__dirname)
          break
        }
        case 'D': {
          if (data.trim() === '') throw new Error('Message should not be empty string')
          console.log('Received message: ' + data)
          fn('Received message: ' + data)
          break
        }
        case 'E': {
          console.log(`Name: ${os.hostname()}, os: ${os.version}`)
          fn(`Name: ${os.hostname()}, os: ${os.version}`)
          break
        }
        case 'F': {
          console.log('Received message: ' + data)
          const rows = data.split('/')
          const other = rows[rows.length - 1].split(' ')
          const arr = []
          rows[rows.length - 1] = other[0]
          other.shift()
          console.log()
          arr.push('\n')
          if (rows.length === 8) {
            for (let i = 0; i < rows.length; i++) {
              let str = ''
              for (let j = 0; j < rows[i].length; j++) {
                str += (rows[i][j] >= '0' && rows[i][j] <= '9' ? ' '.repeat(rows[i][j]) : rows[i][j])
              }
              console.log(str)
              arr.push(str)
            }
            console.log()
            arr.push('\n')
            console.log('It\'s ' + (other[0] === 'w' ? 'white' : 'black') + '\'s turn')
            arr.push('It\'s ' + (other[0] === 'w' ? 'white' : 'black') + '\'s turn')
            console.log()
            arr.push('\n')
            console.log('Castling rights: ')
            arr.push('Castling rights: ')
            for (let i = 0; i < other[1].length; i++) {
              if (other[1][i] === 'K') {
                console.log('White: King\'s side')
                arr.push('White: King\'s side')
              }
              if (other[1][i] === 'Q') {
                console.log('White: Queen\'s side')
                arr.push('White: Queen\'s side')
              }
              if (other[1][i] === 'k') {
                console.log('Black: King\'s side')
                arr.push('Black: King\'s side')
              }
              if (other[1][i] === 'q') {
                console.log('Black: Queen\'s side')
                arr.push('Black: Queen\'s side')
              }
              if (other[1][i] === '-') {
                console.log('None')
                arr.push('None')
                break
              }
            }
            console.log()
            arr.push('\n')
            console.log('En passant square: ' + (other[2][0] === '-' ? 'None' : other[2][0]))
            arr.push('En passant square: ' + (other[2][0] === '-' ? 'None' : other[2][0]))
            console.log('Halfmove clock: ' + other[3])
            arr.push('Halfmove clock: ' + other[3])
            console.log('Fullmove count: ' + other[4])
            arr.push('Fullmove count: ' + other[4])
            fn(JSON.stringify(arr))
          } else {
            throw new Error('FEN is not in correct format')
          }
          break
        }
        case 'G': {
          if (data.trim() === '') throw new Error('Message should not be empty string')
          console.log('Received message: ' + data)
          Encryption.encrypt('KrMočnoGeslo', data).then(eText => {
            console.log('Response message: ' + eText)
            fn('Response message: ' + eText)
            socket.emit('encryptedMessage', eText)
          })
          break
        }
        default: {
          throw new Error('unrecognisable request')
        }
      }
      socket.emit('request', 'OK')
    } catch (err) {
      console.error(err.toString())
      fn(err.toString())
      socket.emit('request', 'ERROR')
    }
  })
  socket.on('disconnect', () => { console.log(`Client [${socket.id}] disconnected `) })
})

server.listen(port, () => {
  console.log(`Listening on port ${port}:`)
})

const express = require('express')
const app = express()
const server = require('http').createServer(app)
const io = require('socket.io')(server)
const bodyParser = require('body-parser')
const path = require('path')
const client = require('socket.io-client')
const { getDiffieHellman } = require('crypto')
const fs = require('fs')
const cryptojs = require('crypto-js')

app.use(bodyParser.urlencoded({ extended: false }))
app.use(express.static(path.join(__dirname, 'src')))

if (process.argv.length < 3) {
  console.error('Missing port')
  process.exit(1)
}
if (process.argv.length > 3) {
  console.error('Too many arguments')
  process.exit(1)
}
if (parseInt(process.argv[2]) <= 0 || parseInt(process.argv[2]) < 1000 ||
  parseInt(process.argv[2]) > 9999) {
  console.error('Wrong port format')
  process.exit(1)
}
const PORT = process.argv[2]
if (PORT === undefined) {
  process.exit(1)
}

server.listen(PORT, () => {
  console.log(`listening on: ${server.address().address}:${PORT}`)
})

const prevDir = './transmited'
const dir = prevDir + '/' + PORT
try {
  if (!fs.existsSync(prevDir)) {
    fs.mkdirSync(prevDir)
  }
  if (!fs.existsSync(dir)) {
    fs.mkdirSync(dir)
  }
} catch (err) {
  if (err) {
    console.error(err)
  }
}

// const dh = getDiffieHellman('modp18') //8192 bit
const dh = getDiffieHellman('modp14')
dh.generateKeys()
let secKey = null

function sendFiles (fileName, port) {
  const link = 'http://127.0.0.1:' + port
  const sock = client.connect(link)
  sock.on('connect', () => {
    console.log(`Connected to peer at ${link}`)
  })

  sock.emit('pubk1', dh.getPublicKey())
  sock.on('pubk2', (pub) => {
    console.log(`Public key: ${pub}`)
    secKey = dh.computeSecret(pub, null, 'base64')
    console.log(`Secret generated: ${secKey}`)

    const rs = fs.createReadStream(`${dir}/${fileName}`)
    rs.on('data', chunk => {
      // console.log('BEFORE')
      // console.log(chunk)
      chunk = cryptojs.AES.encrypt(chunk.toString(), secKey).toString()
      // console.log('AFTER')
      // console.log(chunk)
      sock.emit('uploadFile', fileName, chunk, true)
    })

    rs.on('end', (data) => {
      console.log(`Transfer of ${fileName} has finished`)
    })
  })

  sock.on('disconnect', () => {
    console.log(`Disconnected: ${link}`)
  })
}

io.on('connection', socket => {
  socket.on('uploadFile', (fileName, data, enc) => {
    if (enc) {
      // console.log('BEFORE')
      // console.log(data)
      data = Buffer.from(cryptojs.AES.decrypt(data.toString(), secKey).toString(cryptojs.enc.Utf8))
      // console.log('AFTER')
      // console.log(data)
    }
    fs.appendFile(`${dir}/${fileName}`, data, { encoding: 'binary' }, (err) => {
      if (err) {
        console.error(err)
      }
    })
  })

  socket.on('pubk1', (pub) => {
    console.log(`Public key: ${pub}`)
    socket.emit('pubk2', dh.getPublicKey())
    secKey = dh.computeSecret(pub, null, 'base64')
    console.log(`Secret generated: ${secKey}`)
  })

  socket.on('transfer', (fileName, port) => {
    sendFiles(fileName, port)
  })
})

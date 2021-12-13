const express = require('express')
const app = express()
const server = require('http').createServer(app)
const path = require('path')
const io = require('socket.io')(server)
const CryptoJS = require('crypto-js')
const { generateKeyPair } = require("crypto");
const userArr = []
const priKey = []
const keywords = [
  'coffee', 'quarter', 'will', 'pop', 'able',
  'uniform', 'needle', 'control', 'commemorate', 'press',
  'contradiction', 'executive', 'fuel', 'cream', 'headquarters',
  'contrary', 'machinery', 'black', 'learn', 'party'
]
let gameState = false
let key = ''

function sendMessage (type, message, uname) {
  const msg = JSON.stringify({ message, uname })
  const encText = CryptoJS.AES.encrypt(msg, 'randomKeyWord#$#13').toString()
  console.log({ type, message, uname })
  io.emit(type, encText)
}

app.use(express.static(path.join(__dirname, '/layout')))
io.on('connection', socket => {
  try {
    socket.on('join', (uname, fn) => {
      let pubKey
      generateKeyPair('rsa', {
        modulusLength: 4096,
        publicKeyEncoding: {
          type: 'spki',
          format: 'pem'
        },
        privateKeyEncoding: {
          type: 'pkcs8',
          format: 'pem',
          cipher: 'aes-256-cbc',
          passphrase: 'randomKeyWord#$#13'
        }
      }, (err, publicKey, privateKey) => {
        priKey.push(privateKey)
        pubKey = publicKey
        console.log(privateKey)
        console.log(pubKey)
        console.log(err)
        // Handle errors and use the generated key pair.
        fn(pubKey)
      })
      sendMessage('join', 'join', uname)
      userArr.push(uname)
    })
  } catch (err) {
    sendMessage('msg', err, 'error')
  }

  try {
    socket.on('msg', (data) => {
      data = CryptoJS.AES.decrypt(data, 'randomKeyWord#$#13').toString(CryptoJS.enc.Utf8)
      data = JSON.parse(data)
      console.log({ message: data.message, uname: data.uname })
      sendMessage('msg', data.message, data.uname)
      if (data.message === '#GAMESTART' || data.message === '#GAMESTOP' || data.message === '#GAMENEW') {
        if (data.message === '#GAMESTART' || data.message === '#GAMENEW') {
          if (gameState || data.message === '#GAMENEW') throw Error('Game already exists')
          key = keywords[Math.floor(Math.random() * keywords.length)]
          let guess = key
          for (let i = 0; i < key.length / 2 + 1; i++) {
            guess = guess.replace(guess[((i + 1) * 2) - 1], '_')
          }
          sendMessage('msg', guess, 'server')
          gameState = true
        } else if (data.message === '#GAMENEW') {
          key = keywords[Math.floor(Math.random() * keywords.length)]
          gameState = true
        } else {
          gameState = false
        }
      } else {
        if (gameState) {
          if (key === data.message) {
            sendMessage('msg', 'Correct guess', 'server')
          }
        }
      }
    })
  } catch (err) {
    sendMessage('msg', err, 'error')
  }

  try {
    socket.on('leave', uname => {
      sendMessage('leave', 'leave', uname)
      delete userArr[userArr.indexOf(uname)]
      socket.disconnect(0)
    })
  } catch (err) {
    sendMessage('msg', err, 'error')
  }
})

const port = process.env.PORT || 3000
server.listen(port,
  () => {
    console.log(
      `listening on: ${server.address().address}:${port}`)
  })

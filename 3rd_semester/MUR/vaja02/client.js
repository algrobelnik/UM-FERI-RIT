const io = require('socket.io-client')
const client = io.connect('http://127.0.0.1:3000')
const readline = require('readline')
const Encryption = require('node_triple_des')

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
})

function sendMessage () {
  rl.question('Message: ', d => {
    client.send(d.toString().trim(), (data) => {
      console.log('Got response: ' + data)
    })
  })
}

client.on('request', d => {
  sendMessage()
})

client.on('encryptedMessage', (d) => {
  console.log('Raw message: ' + d)
  Encryption.decrypt('KrMočnoGeslo', d).then(dText => {
    console.log('Decrypted message: ' + dText)
  })
})

client.on('connect', () => {
  console.log(client.id)
  sendMessage()
  // client.send('r6r/ppp1k1pp/5n2/b4b2/5B2/2P1P1P1/PP1N2BP/2KR3R w - - 0 1')
})

client.on('disconnect', () => {
  console.log('Disconnected')
})

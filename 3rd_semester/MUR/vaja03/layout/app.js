const chat = document.createElement('div')
chat.classList.add('chat')
document.querySelector('body').appendChild(chat)

function drawJoinForm () {
  const input = document.createElement('input')
  const joinForm = document.createElement('form')
  joinForm.classList.add('joinForm')

  const label = document.createElement('label')
  const submit = document.createElement('input')
  label.innerText = 'Username: '
  input.type = 'text'
  input.classList.add('joinInput')
  submit.type = 'submit'
  submit.value = 'Join'
  label.appendChild(input)
  joinForm.appendChild(label)
  joinForm.appendChild(submit)
  document.querySelector('body').appendChild(joinForm)
  chat.innerText = ''
  console.log('EMPTY chat')
}

function message (data) { // destructure data, create new message div and add to chat
  data = CryptoJS.AES.decrypt(data, 'randomKeyWord#$#13').toString(CryptoJS.enc.Utf8)
  data = JSON.parse(data)
  const div = document.createElement('div')
  div.classList.add('message')
  const header = document.createElement('div')
  const body = document.createElement('div')
  header.classList.add('header')
  body.classList.add('body')
  header.innerText = data.uname
  body.innerText = data.message
  div.appendChild(header)
  div.appendChild(body)
  chat.appendChild(div)
}

function status (username, data) { // destructure data, create new join div and add to chat
  data = CryptoJS.AES.decrypt(data, 'randomKeyWord#$#13').toString(CryptoJS.enc.Utf8)
  data = JSON.parse(data)
  if (username === data.uname && data.message === 'leave') return
  const div = document.createElement('div')
  div.classList.add(data.message)
  div.innerText = data.uname
  chat.appendChild(div)
}

function chatting (uname, joinForm) {
  const socket = io()
  socket.emit('join', uname, (res) => {
    socket.disconnect()
    messageForm.parentNode.removeChild(messageForm)
    drawJoinForm()
    main()
    alert(res)
  })

  joinForm.parentNode.removeChild(joinForm)
  const messageForm = document.createElement('form')
  messageForm.classList.add('messageSendForm')
  const input = document.createElement('input')
  {
    const label = document.createElement('label')
    const submit = document.createElement('input')
    const disconnect = document.createElement('button')
    label.innerText = 'Enter a message: '
    input.type = 'text'
    input.classList.add('messageInput')
    submit.type = 'submit'
    submit.value = 'Send'
    disconnect.type = 'button'
    disconnect.classList.add('disconnect')
    disconnect.innerText = 'Disconnect'
    label.appendChild(input)
    messageForm.appendChild(label)
    messageForm.appendChild(submit)
    messageForm.appendChild(disconnect)
    document.querySelector('body').appendChild(messageForm)
  }
  // const messageForm = document.querySelector('.messageSendForm') // all required document objects
  messageForm.addEventListener('submit', e => { // on submit send data to
    e.preventDefault()
    const msg = JSON.stringify({ message: input.value, uname })
    const data = CryptoJS.AES.encrypt(msg, 'randomKeyWord#$#13').toString()
    socket.emit('msg', data)
    input.value = ''
  })

  const button = document.querySelector('.disconnect')
  button.addEventListener('click', e => { // on submit send data to
    e.preventDefault()
    socket.emit('leave', uname)
    messageForm.parentNode.removeChild(messageForm)
    drawJoinForm()
    main()
  })

  socket.on('join', data => { // on every message display new messages
    status(uname, data)
  })

  socket.on('msg', data => { // on every message display new messages
    message(data)
  })

  socket.on('leave', data => { // on every message display new messages
    status(uname, data)
  })
}
function main () {
  const joinForm = document.querySelector('.joinForm') // all required document objects
  joinForm.addEventListener('submit', e => { // on submit send data to
    e.preventDefault()
    const input = document.querySelector('.joinInput')
    if (input.value === '') return
    chatting(input.value, joinForm)
    input.value = ''
  })
}
drawJoinForm()
main()

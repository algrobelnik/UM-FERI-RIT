const divFile = document.createElement('div')
divFile.classList.add('divFile')
document.querySelector('body').appendChild(divFile)

function drawJoinForm () {
  const input = document.createElement('input')
  const form = document.createElement('form')
  form.classList.add('sendForm')

  const label = document.createElement('label')
  const submit = document.createElement('input')
  label.innerText = 'File: '
  input.type = 'file'
  input.classList.add('file')
  submit.type = 'submit'
  submit.value = 'Send'
  label.appendChild(input)
  form.appendChild(label)
  form.appendChild(submit)
  document.querySelector('body').appendChild(form)
  divFile.innerText = ''
}

function message (data) { // destructure data, create new message div and add to chat
  data = CryptoJS.AES.decrypt(data, 'randomKeyWord#$#13').toString(CryptoJS.enc.Utf8)
  data = JSON.parse(data)
}

function status (username, data) { // destructure data, create new join div and add to divFile
  data = CryptoJS.AES.decrypt(data, 'randomKeyWord#$#13').toString(CryptoJS.enc.Utf8)
  data = JSON.parse(data)
}

function transfer (uname, form) {
  const socket = io()
  socket.emit('join', uname, (res) => {
    console.log(res)
    socket.disconnect()
    main()
    drawJoinForm()
    alert(res)
  })
  form.parentNode.removeChild(form)
  /* messageForm.addEventListener('submit', e => { // on submit send data to
    e.preventDefault()
    const msg = JSON.stringify({ message: input.value, uname })
    const data = CryptoJS.AES.encrypt(msg, 'randomKeyWord#$#13').toString()
    socket.emit('msg', data)
    input.value = ''
  }) */

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
  const form = document.querySelector('.sendForm') // all required document objects
  form.addEventListener('submit', e => { // on submit send data to
    e.preventDefault()
    const input = document.querySelector('.file')
    if (input.files[0] === undefined) return
    transfer(input.files[0], form)
    input.files[0] = undefined
  })
}
drawJoinForm()
main()

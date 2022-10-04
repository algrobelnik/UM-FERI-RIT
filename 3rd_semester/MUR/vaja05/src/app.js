const socket = io()

$('#form1').submit(function (e) {
  e.preventDefault()
  const i1 = document.getElementById('nodeName')
  const i2 = document.getElementById('connectPort')
  socket.emit('join', i1.value, i2.value, (res) => {
    $('#status').text(`Status: ${res}`)
  })
  $('#connect').prop('disabled', true)
  $('#mine').prop('disabled', false)
})
$('#form2').submit(function (e) {
  e.preventDefault()
  socket.emit('mine', (res) => {
    console.log(res)
  })
  $('#mine').prop('disabled', true)
  $('#text').css('visibility', 'visible')
})

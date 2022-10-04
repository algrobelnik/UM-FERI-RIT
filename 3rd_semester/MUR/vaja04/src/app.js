const socket = io()

function sendFile (file, link) {
  const name = file.name
  const size = file.size
  const chunkSize = 65536
  let offset = 0
  const readChunk = (offset, size, file) => {
    const reader = new FileReader()
    const part = file.slice(offset, size + offset)
    reader.onload = eventHandler
    reader.readAsBinaryString(part)
  }

  const eventHandler = (event) => {
    if (event.target.error == null) {
      offset += event.target.result.length
      socket.emit('uploadFile', name, event.target.result, false)
    } else {
      console.log(`Error reading: ${event.target.error}`)
      return
    }
    if (offset >= size) {
      console.log('Finished')
      socket.emit('transfer', name, link)
      return
    }
    readChunk(offset, chunkSize, file)
  }
  readChunk(offset, chunkSize, file)
}

$('#form1').submit(function (e) {
  e.preventDefault()
  const i1 = document.getElementById('file')
  const i2 = document.getElementById('connectPort')
  sendFile(i1.files[0], i2.value)
})

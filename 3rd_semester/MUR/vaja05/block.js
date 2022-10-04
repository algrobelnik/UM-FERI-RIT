const crypto = require('crypto')

module.exports = class Block {
  constructor (index, data, timestamp, diff, prevHash, nonce) {
    this.index = index
    this.data = data
    this.timestamp = timestamp
    this.diff = diff
    this.prevHash = prevHash
    this.nonce = nonce
    this.hash = crypto.createHash('sha256').update(`${index}${timestamp}${data}${prevHash}${diff}${nonce}`).digest('hex')
    this.validity = false;
  }
}

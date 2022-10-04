const mongoose = require('mongoose');
const UserModel = require('./userModel.js')
const Schema = mongoose.Schema;

const answerSchema = new Schema({
  'text': String,
  'correct': Boolean,
  'ratio': Number,
  'qid': {type: Schema.Types.ObjectId, ref: 'question'},
  'uid': {type: Schema.Types.ObjectId, ref: 'user'},
},{
  timestamps: true
});

const Answer = mongoose.model('answer', answerSchema);
module.exports = Answer;


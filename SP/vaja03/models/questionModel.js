const mongoose = require('mongoose');
const UserModel = require('./userModel.js')
const Schema = mongoose.Schema;

const questionSchema = new Schema({
  'title': String,
  'description': String,
  'uid': {type: Schema.Types.ObjectId, ref: 'user'},
},{
  timestamps: true
});

const Question = mongoose.model('question', questionSchema);
module.exports = Question;


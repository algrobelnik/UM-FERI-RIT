const mongoose = require('mongoose');
const bcrypt = require('bcrypt');
const Schema = mongoose.Schema;

const userSchema = new Schema({
  'username' : String,
  'password' : String,
  'email' : String
});

userSchema.pre('save', function(next){
  const user = this;
  bcrypt.hash(user.password, 10, function(err, hash){
    if(err){
      return next(err);
    }
    user.password = hash;
    next();
  });
});

userSchema.statics.authenticate = function(username, password, cbk){
  User.findOne({username: username})
    .exec(function(err, user){
      if(err){
        return cbk(err);
      } else if(!user) {
        const err = new Error("User not found.");
        err.status = 401;
        return cbk(err);
      }
      bcrypt.compare(password, user.password, function(err, result){
        if(result === true){
          return cbk(null, user);
        } else{
          return cbk();
        }
      });
    });
}

const User = mongoose.model('user', userSchema);
module.exports = User;


const createError = require('http-errors')
const express = require('express')
const path = require('path')
const cookieParser = require('cookie-parser')
const logger = require('morgan')
const mongoose = require('mongoose')
const session = require('express-session')
const MongoStore = require('connect-mongo')
const methodOverride = require('method-override')
const hbs = require('hbs');

const indexRouter = require('./routes/index')
const usersRouter = require('./routes/userRoutes')
const questionRouter = require('./routes/questionRoutes')
const answerRouter = require('./routes/answerRoutes')
// const photosRouter = require('./routes/photoRoutes')

const config = require('./config/config')

const mongoDB = `mongodb+srv://${config.config.mongodb.username}:${config.config.mongodb.password}@cluster0.yxv8m.mongodb.net/myFirstDatabase?retryWrites=true&w=majority`
mongoose.connect(mongoDB)
mongoose.Promise = global.Promise
const db = mongoose.connection
db.on('error', console.error.bind(console, 'MongoDB connection error:'))


hbs.registerHelper('eq', function (a, b) {
  return a == b;
});

const app = express()

app.set('views', path.join(__dirname, 'views'))
app.set('view engine', 'hbs')

app.use(logger('dev'))
app.use(express.json())
app.use(express.urlencoded({ extended: false }))
app.use(cookieParser())
app.use(express.static(path.join(__dirname, 'public')))
app.use(methodOverride(function (req, res) {
  if (req.body && typeof req.body === 'object' && '_method' in req.body) {
    const method = req.body._method
    delete req.body._method
    return method
  }
}))

app.use(session({
  secret: config.config.secret,
  resave: true,
  saveUninitialized: false,
  store: MongoStore.create({ mongoUrl: mongoDB })
}))

app.use(function (req, res, next) {
  //const arr = req.session
  req.session.uid = `new ObjectId("${req.session.userId}")`
  res.locals.session = req.session
  next()
})

app.use('/', indexRouter)
app.use('/users', usersRouter)
app.use('/question', questionRouter)
app.use('/answer', answerRouter)

app.use(function (req, res, next) {
  next(createError(404))
})

app.use(function (err, req, res, next) {
  res.locals.message = err.message
  res.locals.error = req.app.get('env') === 'development' ? err : {}
  res.status(err.status || 500)
  res.render('error')
})

module.exports = app

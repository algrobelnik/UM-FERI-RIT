const QuestionModel = require('../models/questionModel.js');
const AnswerModel = require('../models/answerModel.js');

/**
 * questionController.js
 *
 * @description :: Server-side logic for managing questions.
 */
module.exports = {

  /**
   * questionController.list()
   */
  list: function(req, res) {
    QuestionModel.find(function(err, questions) {
      if (err) {
        return res.status(500).json({message: 'Error when getting question.', error: err});
      }
      return res.json(questions);
    });
  },

  /**
   * questionController.show()
   */
  show: function(req, res) {
    const id = req.params.id;

    QuestionModel.findOne({_id : id}, function(err, question) {
      if (err) {
        return res.status(500).json(
          {message : 'Error when getting question.', error : err});
      }

      if (!question) {
        return res.status(404).json({message : 'No such question'});
      }

      return res.json(question);
    });
  },

  /**
   * questionController.create()
   */
  create: function(req, res) {
    const question = new QuestionModel({
      title: req.body.title,
      description: req.body.description,
      uid: req.session.userId
    });

    question.save(function(err, question) {
      if (err) {
        return res.status(500).json(
          {message : 'Error when creating question', error : err});
      }

      // return res.status(201).json(question);
      return res.redirect('/question/user');
    });
  },

  /**
   * questionController.update()
   */
  update: function(req, res) {
    const id = req.params.id;

    QuestionModel.findOne({_id : id}, function(err, question) {
      if (err) {
        return res.status(500).json(
          {message : 'Error when getting question', error : err});
      }

      if (!question) {
        return res.status(404).json({message : 'No such question'});
      }

      question.title = req.body.title ?? question.title;
      question.description = req.body.description ?? question.description;

      question.save(function(err, question) {
        if (err) {
          return res.status(500).json(
            {message : 'Error when updating question.', error : err});
        }

        return res.redirect(`/question/show/${id}`);
      });
    });
  },



  /**
   * questionController.remove()
   */
  remove: function(req, res) {
    const id = req.params.id;

    AnswerModel.deleteMany({qid: id}).exec(function(error) {
      if (error) {
        return next(error);
      }
    });
    QuestionModel.findByIdAndRemove(id, function(err, question) {
      if (err) {
        return res.status(500).json(
          {message : 'Error when deleting the question.', error : err});
      }
      return res.redirect('/question/all');
    });
  },

  /**
   * questionController.showAll()
   */
  showAll: function(req, res) {
    QuestionModel.find().exec(async function(error, questions) {
      if (error) {
        return next(error);
      }
      if (questions === null) {
        const err = new Error('Something went wrong!');
        err.status = 400;
        return next(err);
      }
      for (const quest of questions) {
        
        const answer = await AnswerModel.find({qid: quest._id, correct: true, $limit: 1})
        if (answer.length == 1) {
          quest.answer = []
          quest.answer.push(answer[0]);
        }
      }
      return res.render('question/all', {data: questions});
    });
  },

  /**
   * questionController.showUser()
   */
  showUser: function(req, res) {
    QuestionModel.find({uid: req.session.userId}).exec(async function(error, questions) {
      if (error) {
        return next(error);
      }
      if (questions === null) {
        const err = new Error('Something went wrong!');
        err.status = 400;
        return next(err);
      }
      for (const quest of questions) {
        const answer = await AnswerModel.find({qid: quest._id, correct: true, $limit: 1})
        if (answer.length == 1) {
          quest.answer = []
          quest.answer.push(answer[0]);
        }
      }
      return res.render('question/all', {data: questions});
    });
  },

  showNewQuestion: function(req, res){
    res.render('question/create');
  },

  showQuestion: function(req, res) {
    const id = req.params.id;
    QuestionModel.findById(id).exec(async function(error, question) {
      if (error) {
        return next(error);
      }
      if (question === null) {
        const err = new Error('Wrong id specified!');
        err.status = 400;
        return next(err);
      }
      question.answers = []
      const answers = await AnswerModel.find({qid: id})
      if (answers != null) {
        let correct = false; 
        for (const ans of answers){
          if (ans.correct === true){
            correct = true;
            question.answers.unshift(ans);
          } else{
            question.answers.push(ans);
          }
        }
        question.correct = correct;
      }
      return res.render('question/show', question);
    });
  },

  showEdit: function(req, res) {
    const id = req.params.id;
    QuestionModel.findById(id).exec(function(error, question) {
      if (error) {
        return next(error);
      }
      if (question === null) {
        const err = new Error('Wrong id specified!');
        err.status = 400;
        return next(err);
      }
      return res.render('question/edit', {data: question});
    });
  },
}

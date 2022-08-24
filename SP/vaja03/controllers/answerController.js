const AnswerModel = require('../models/answerModel.js');
const QuestionModel = require('../models/questionModel.js');

/**
 * answerController.js
 *
 * @description :: Server-side logic for managing answers.
 */
module.exports = {

  /**
   * answerController.list()
   */
  list: function(req, res) {
    AnswerModel.find(function(err, answers) {
      if (err) {
        return res.status(500).json({message: 'Error when getting answer.', error: err});
      }
      return res.json(answers);
    });
  },

  /**
   * answerController.show()
   */
  show: function(req, res) {
    const id = req.params.id;

    AnswerModel.findOne({_id : id}, function(err, answer) {
      if (err) {
        return res.status(500).json(
          {message : 'Error when getting answer.', error : err});
      }

      if (!answer) {
        return res.status(404).json({message : 'No such answer'});
      }

      return res.json(answer);
    });
  },

  /**
   * answerController.create()
   */
  create: function(req, res) {
    console.log(req.body)
    const answer = new AnswerModel({
      text: req.body.text,
      correct: false,
      ratio: 0,
      qid: req.body.qid,
      uid: req.session.userId
    });

    answer.save(function(err, answer) {
      if (err) {
        return res.status(500).json(
          {message : 'Error when creating answer', error : err});
      }

      // return res.status(201).json(answer);
      return res.redirect(req.get('referer'));
    });
  },

  /**
   * answerController.update()
   */
  update: function(req, res) {
    const id = req.params.id;

    AnswerModel.findById(id, function(err, answer) {
      if (err) {
        return res.status(500).json(
          {message : 'Error when getting answer', error : err});
      }

      if (!answer) {
        return res.status(404).json({message : 'No such answer'});
      }

      answer.text = req.body.text ?? answer.text;
      answer.save(function(err, answer) {
        if (err) {
          return res.status(500).json(
            {message : 'Error when updating answer.', error : err});
        }

        return res.redirect(req.get('referer'));
      });
    });
  },



  /**
   * answerController.remove()
   */
  remove: function(req, res) {
    const id = req.params.id;

    AnswerModel.findByIdAndRemove(id, function(err, answer) {
      if (err) {
        return res.status(500).json(
          {message : 'Error when deleting the answer.', error : err});
      }
      return res.redirect(req.get('referer'));
    });
  },

  /**
   * answerController.correct()
   */
  correct: function(req, res) {
    const id = req.params.id;

    AnswerModel.findById(id, function(err, answer) {
      if (err) {
        return res.status(500).json(
          {message : 'Error when getting answer', error : err});
      }

      if (!answer) {
        return res.status(404).json({message : 'No such answer'});
      }

      answer.correct = true;
      answer.save(function(err, answer) {
        if (err) {
          return res.status(500).json(
            {message : 'Error when updating answer.', error : err});
        }

        return res.redirect(req.get('referer'));
      });
    });
  },

  /**
   * answerController.plus()
   */
  plus: function(req, res) {
    const id = req.params.id;

    AnswerModel.findById(id, function(err, answer) {
      if (err) {
        return res.status(500).json(
          {message : 'Error when getting answer', error : err});
      }

      if (!answer) {
        return res.status(404).json({message : 'No such answer'});
      }

      answer.ratio += 1;
      answer.save(function(err, answer) {
        if (err) {
          return res.status(500).json(
            {message : 'Error when updating answer.', error : err});
        }

        return res.redirect(req.get('referer'));
      });
    });
  },

  /**
   * answerController.minus()
   */
  minus: function(req, res) {
    const id = req.params.id;

    AnswerModel.findById(id, function(err, answer) {
      if (err) {
        return res.status(500).json(
          {message : 'Error when getting answer', error : err});
      }

      if (!answer) {
        return res.status(404).json({message : 'No such answer'});
      }

      answer.ratio -= 1;
      answer.save(function(err, answer) {
        if (err) {
          return res.status(500).json(
            {message : 'Error when updating answer.', error : err});
        }

        return res.redirect(req.get('referer'));
      });
    });
  },

  /**
   * answerController.showAll()
   */
  showAll: function(req, res) {
    AnswerModel.find({}).exec(function(error, answers) {
      if (error) {
        return next(error);
      }
      if (answers === null) {
        const err = new Error('Something went wrong!');
        err.status = 400;
        return next(err);
      }
      return res.render('answer/all', {data : answers});
    });
  },

  /**
   * answerController.showAnswer()
   */
  showAnswer: function(req, res){
    const id = req.params.id;
    AnswerModel.findById(id).exec(function(error, answer) {
      if (error) {
        return next(error);
      }
      if (answer === null) {
        const err = new Error('Something went wrong!');
        err.status = 400;
        return next(err);
      }
      return res.render('answer/show', {data: answer});
    });
  },

  showNewAnswer: function(req, res){
    const qid = req.params.qid;
    QuestionModel.findById(qid).exec(function(error, answers) {
      if (error) {
        return next(error);
      }
      if (answers === null) {
        const err = new Error('Something went wrong!');
        err.status = 400;
        return next(err);
      }
      console.log(qid)
      return res.render('answer/create', {qid});
    });
  },

  showEdit: function(req, res) {
    const id = req.params.id;
    AnswerModel.findById(id).exec(function(error, answer) {
      if (error) {
        return next(error);
      }
      if (answer === null) {
        const err = new Error('Wrong id specified!');
        err.status = 400;
        return next(err);
      }
      return res.render('answer/edit', {data : answer});
    });
  },
}

const express = require('express');
const router = express.Router();
const answerController = require('../controllers/answerController.js');

router.get('/', answerController.list);
router.get('/all', answerController.showAll);
router.get('/new/:qid', answerController.showNewAnswer);
router.get('/show/:id', answerController.showAnswer);
router.get('/edit/:id', answerController.showEdit);

router.post('/correct/:id', answerController.correct);
router.post('/plus/:id', answerController.plus);
router.post('/minus/:id', answerController.minus);
router.post('/create', answerController.create);
router.put('/:id', answerController.update);
router.delete('/:id', answerController.remove);

module.exports = router;

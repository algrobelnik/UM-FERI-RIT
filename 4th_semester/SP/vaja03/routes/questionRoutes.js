const express = require('express');
const router = express.Router();
const questionController = require('../controllers/questionController.js');

router.get('/', questionController.list);
router.get('/all', questionController.showAll);
router.get('/user', questionController.showUser);
router.get('/new', questionController.showNewQuestion);
router.get('/show/:id', questionController.showQuestion);
router.get('/edit/:id', questionController.showEdit);

router.post('/create', questionController.create);
router.put('/:id', questionController.update);
router.delete('/:id', questionController.remove);

module.exports = router;

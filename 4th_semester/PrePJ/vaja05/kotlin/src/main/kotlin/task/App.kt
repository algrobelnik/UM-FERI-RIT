package task

import java.io.File
import java.io.InputStream
import java.util.LinkedList

const val EOF_SYMBOL = -1
const val ERROR_STATE = 0
const val SKIP_VALUE = 0
const val NEWLINE = '\n'.code

interface Automaton {
  val states: Set<Int>
  val alphabet: IntRange
  fun next(state: Int,symbol: Int): Int
  fun value(state: Int): Int
  val startState: Int
  val finalStates: Set<Int>
}

object MinimalisticCPP : Automaton {
  override val states = setOf(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30)
  override val alphabet = 0..255
  override val startState = 1
  override val finalStates = setOf(2,3,4,5,6,7,8,9,10,11,12,13,15,16,19,21,23,25,30)

  private val numberOfStates = states.maxOrNull()!! + 1
  private val numberOfSymbols = alphabet.maxOrNull()!! + 1
  private val transitions = Array(numberOfStates) { IntArray(numberOfSymbols) }
  private val values: Array<Int> = Array(numberOfStates) { 0 }

  private fun setTransition(from: Int,symbol: Char,to: Int) {
    transitions[from][symbol.code] = to
  }

  private fun setTransition(from: Int,range: IntRange,to: Int) {
    for (i in range){
      transitions[from][i] = to
    }
  }

  private fun setValue(state: Int,terminal: Int) {
    values[state] = terminal
  }

  override fun next(state: Int,symbol: Int): Int =
    if (symbol == EOF_SYMBOL) ERROR_STATE
    else {
      assert(states.contains(state))
      assert(alphabet.contains(symbol))
      transitions[state][symbol]
    }

  override fun value(state: Int): Int {
    assert(states.contains(state))
    return values[state]
  }

  init {
    //Numbers
    setTransition(1, 48..57, 2)
    //Characters
    setTransition(1, 65..86, 4)
    setTransition(1, 88..90, 4)
    setTransition(1, 97..99, 4)
    setTransition(1, 'e', 4)
    setTransition(1, 103..115, 4)
    setTransition(1, 117..122, 4)
    //Operators
    setTransition(1,'+',6)
    setTransition(1,'-',7)
    setTransition(1,'*',8)
    setTransition(1,'/',9)
    setTransition(1,'^',10)
    //Brackets
    setTransition(1,'(',11)
    setTransition(1,')',12)
    //Numbers
    setTransition(2, 48..57, 2)
    setTransition(2,'.',3)
    //Numbers
    setTransition(3, 48..57, 3)
    //Characters
    setTransition(4, 65..90, 4)
    setTransition(4, 97..122, 4)
    //Numbers
    setTransition(4, 48..57, 5)
    //Numbers
    setTransition(5, 48..57, 5)

    setTransition(1,' ',13)
    setTransition(1,'\t',13)
    setTransition(1,'\n',13)
    setTransition(1,':',14)
    setTransition(14,'=',15)
    setTransition(1,';',16)
    setTransition(1, 'f', 17)
    setTransition(17, 65..90, 4)
    setTransition(17, 97..110, 4)
    setTransition(17, 112..122, 4)
    setTransition(17, 'o', 18)
    setTransition(18, 65..90, 4)
    setTransition(18, 97..113, 4)
    setTransition(18, 115..122, 4)
    setTransition(18, 'r', 19)
    setTransition(1, 't', 20)
    setTransition(20, 65..90, 4)
    setTransition(20, 97..110, 4)
    setTransition(20, 112..122, 4)
    setTransition(20, 'o', 21)
    setTransition(1, 'd', 22)
    setTransition(22, 65..90, 4)
    setTransition(22, 97..110, 4)
    setTransition(22, 112..122, 4)
    setTransition(22, 'o', 23)
    setTransition(23, 65..90, 4)
    setTransition(23, 97..109, 4)
    setTransition(23, 111..122, 4)
    setTransition(23,'n',24)
    setTransition(24, 65..90, 4)
    setTransition(24, 97..110, 4)
    setTransition(24, 112..122, 4)
    setTransition(24,'e',25)
    setTransition(1,'W',26)
    setTransition(26, 65..81, 4)
    setTransition(26, 82..90, 4)
    setTransition(26, 97..122, 4)
    setTransition(26,'R',27)
    setTransition(27, 65..72, 4)
    setTransition(27, 74..90, 4)
    setTransition(27, 97..122, 4)
    setTransition(27,'I',28)
    setTransition(28, 65..83, 4)
    setTransition(28, 85..90, 4)
    setTransition(28, 97..122, 4)
    setTransition(28,'T',29)
    setTransition(29, 65..68, 4)
    setTransition(29, 70..90, 4)
    setTransition(29, 97..122, 4)
    setTransition(29,'E',30)
    //Float
    setValue(2,1);
    setValue(3,1);
    //Variable
    setValue(4,2);
    setValue(5,2);
    //Operator
    setValue(6,3);
    setValue(7, 4);
    setValue(8,5);
    setValue(9,6);
    setValue(10,7);
    setValue(11,8);
    setValue(12,9);
    setValue(15,10);
    setValue(16,11);
    setValue(19,12);
    setValue(21,13);
    setValue(23,14);
    setValue(25,15);
    setValue(30,16);
  }
}

data class Token(val value: Int,val lexeme: String,val startRow: Int,val startColumn: Int)

class Scanner(private val automaton: Automaton,private val stream: InputStream) {
  private var state = automaton.startState
  private var last: Int? = null
  private var buffer = LinkedList<Byte>()
  private var row = 1
  private var column = 1

  private fun updatePosition(symbol: Int) {
    if (symbol == NEWLINE) {
      row += 1
      column = 1
    } else {
      column += 1
    }
  }

  private fun getValue(): Int {
    var symbol = last ?: stream.read()
    state = automaton.startState

    while (true) {
      updatePosition(symbol)

      val nextState = automaton.next(state,symbol)
      if (nextState == ERROR_STATE) {
        if (automaton.finalStates.contains(state)) {
          last = symbol
          return automaton.value(state)
        } else throw Error("Invalid pattern at ${row}:${column}")
      }
      state = nextState
      buffer.add(symbol.toByte())
      symbol = stream.read()
    }
  }

  fun eof(): Boolean =
    last == EOF_SYMBOL

  fun getToken(): Token? {
    if (eof()) return null

    val startRow = row
    val startColumn = column
    buffer.clear()

    val value = getValue()
    return if (value == SKIP_VALUE)
      getToken()
    else
      Token(value,String(buffer.toByteArray()),startRow,startColumn)
  }
}

fun name(value: Int) =
  when (value) {
    1 -> "float"
    2 -> "variable"
    3 -> "plus"
    4 -> "minus"
    5 -> "times"
    6 -> "divide"
    7 -> "pow"
    8 -> "lparen"
    9 -> "rparen"
    10 -> "assign"
    11 -> "semi"
    12 -> "for"
    13 -> "to"
    14 -> "do"
    15 -> "done"
    16 -> "write"
    else -> throw Error("Invalid value")
  }

fun printTokens(scanner: Scanner) {
  val token = scanner.getToken()
  if (token != null) {
    print("${name(token.value)}(\"${token.lexeme}\") ")
    printTokens(scanner)
  }
}

fun main(args: Array<String>) {
  val scanner = Scanner(
    MinimalisticCPP, File(args[0]).inputStream() //test.txt
  )
  printTokens(scanner)
}
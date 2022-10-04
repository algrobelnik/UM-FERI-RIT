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
    override val states = setOf(1,2,3,4,5,6,7,8,9,10,11,12,13)
    override val alphabet = 0..255
    override val startState = 1
    override val finalStates = setOf(2,3,4,5,6,7,8,9,10,11,12,13)

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
        setTransition(1, 65..90, 4)
        setTransition(1, 97..122, 4)
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
        //Float
        setValue(2,1)
        setValue(3,1)
        //Variable
        setValue(4,2)
        setValue(5,2)
        //Operator
        setValue(6,3)
        setValue(7, 4)
        setValue(8,5)
        setValue(9,6)
        setValue(10,7)
        setValue(11,8)
        setValue(12,9)
    }

}

data class Token(val value: Int, val lexeme: String, val startRow: Int, val startColumn: Int)

class Scanner(private val automaton: Automaton,private val stream: InputStream) {
    private var state = automaton.startState
    private var last: Int? = null
    private var buffer = LinkedList<Byte>()
    private var row = 1
    private var column = 1
    private var token: Token = Token(-1, "EOF", row, column)

    init {
        try {
            nextToken()
            E()
            if (name(token.value) != "EOF") throw Error("reject")
            println("accept")
        }catch (err: Error){
            println(err.message)
        }
    }

    private fun E() {
        T()
        EE()
    }

    private fun EE() {
        if (name(token.value) == "plus"){
            nextToken()
            T()
            EE()
        }else if (name(token.value) == "minus"){
            nextToken()
            T()
            EE()
        }
    }

    private fun T() {
        X()
        TT()
    }

    private fun X() {
        Y()
        XX()
    }

    private fun XX() {
        if (name(token.value) == "pow"){
            nextToken()
            X()
        }
    }

    private fun Y() {
        if (name(token.value) == "plus" ){
            nextToken()
        } else if(name(token.value) == "minus"){
            nextToken()
        }
        F()
    }

    private fun F() {
        if (name(token.value) == "lparen") {
            nextToken()
            E()
            if (name(token.value) == "rparen") {
                nextToken()
            }else {
                throw Error("reject")
            }
        }else if (name(token.value) == "float"){
            nextToken()
        }else if (name(token.value) == "variable"){
            nextToken()
        }else{
            throw Error("reject")
        }
    }

    private fun TT() {
        if (name(token.value) == "times"){
            nextToken()
            X()
            TT()
        }else if (name(token.value) == "divide"){
            nextToken()
            X()
            TT()
        }
    }

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

    private fun eof(): Boolean =
        last == EOF_SYMBOL

    private fun getToken(): Token {
        if (eof()) return Token(-1, "EOF", row, column)

        val startRow = row
        val startColumn = column
        buffer.clear()

        val value = getValue()
        return if (value == SKIP_VALUE)
            getToken()
        else
            Token(value,String(buffer.toByteArray()),startRow,startColumn)
    }

    private fun nextToken(){
        token = getToken()
    }
}

fun name(value: Int) =
    when (value) {
        -1 -> "EOF"
        1 -> "float"
        2 -> "variable"
        3 -> "plus"
        4 -> "minus"
        5 -> "times"
        6 -> "divide"
        7 -> "pow"
        8 -> "lparen"
        9 -> "rparen"
        else -> throw Error("Invalid value")
    }


fun main(args: Array<String>) {
    Scanner(MinimalisticCPP, File(args[0]).inputStream())
}

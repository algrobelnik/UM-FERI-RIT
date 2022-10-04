import java.math.BigDecimal
import java.math.MathContext
import java.time.LocalDateTime
import java.util.*

data class _Currency(
  var value: BigDecimal = BigDecimal.ZERO,
  val currency: Currency = Currency.getInstance("EUR")
) {
  private val id: UUID = UUID.randomUUID()
  private val created: LocalDateTime = LocalDateTime.now()
  private val updated: LocalDateTime = LocalDateTime.now()
  override fun toString() = "${value.round(MathContext(3))}${currency.symbol}"

  operator fun compareTo(bigDecimal: BigDecimal): Int {
    if (bigDecimal < value) return 1
    if (bigDecimal > value) return -1
    return 0
  }

  fun multiply(bigDecimal: BigDecimal): BigDecimal {
    return value.multiply(bigDecimal)
  }

  operator fun plusAssign(bigDecimal: BigDecimal) {
    value += bigDecimal
  }

  operator fun minusAssign(bigDecimal: BigDecimal) {
    value -= bigDecimal
  }
}
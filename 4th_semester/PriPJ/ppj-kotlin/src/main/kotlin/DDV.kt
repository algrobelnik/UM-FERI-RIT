import dao.mysql.MySqlPrice
import java.math.BigDecimal
import java.time.LocalDateTime
import java.util.UUID

data class DDV(
  val ddvType: DDVTYPE = DDVTYPE.EMPTY,
  val value: Price,
) {
  init {
    val sqlPrice = MySqlPrice()
    sqlPrice.insert(value)
  }
  val id: UUID = UUID.randomUUID()
  private val created: LocalDateTime = LocalDateTime.now()
  private val updated: LocalDateTime = LocalDateTime.now()
  override fun toString(): String {
    if (ddvType.isNotEmpty() && !value.equals(BigDecimal.ZERO)) {
      return "\n[${this.javaClass.simpleName} ${id.toString().takeLast(12)}] $ddvType $value"
    }
    return ""
  }
}
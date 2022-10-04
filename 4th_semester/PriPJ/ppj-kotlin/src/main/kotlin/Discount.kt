import java.math.BigDecimal
import java.time.LocalDateTime
import java.util.UUID

data class Discount(
  val text: String = String(),
  val value: Price = Price(),
) {
  private val id: UUID = UUID.randomUUID()
  private val created: LocalDateTime = LocalDateTime.now()
  private val updated: LocalDateTime = LocalDateTime.now()
  override fun toString(): String {
    if (text.isNotEmpty() && !value.equals(BigDecimal.ZERO)) {
      return "\n[${this.javaClass.simpleName} ${id.toString().takeLast(12)}] $text -$value"
    }
    return ""
  }
}
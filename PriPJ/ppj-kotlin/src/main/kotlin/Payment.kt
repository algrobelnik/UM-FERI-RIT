import java.time.LocalDateTime
import java.util.UUID

data class Payment(
  val payment: PAYMENTTYPE = PAYMENTTYPE.cash,
  val cardNumber: String? = null,
  val aid: String? = null,
  val apn: String? = null,
  val price: Price = Price(),
) {
  private val id: UUID = UUID.randomUUID()
  private val created: LocalDateTime = LocalDateTime.now()
  private val updated: LocalDateTime = LocalDateTime.now()
  override fun toString(): String {
    var ret = "[${this.javaClass.simpleName} ${id.toString().takeLast(12)}] $payment $created"
    if (payment != PAYMENTTYPE.cash) {
      ret += " $cardNumber $aid $apn $price"
    }
    return ret
  }
}
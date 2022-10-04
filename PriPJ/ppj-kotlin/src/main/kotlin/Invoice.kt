import java.time.LocalDateTime
import java.util.UUID

data class Invoice(
  val payment: Payment,
  val issuer: Company,
  val customer: Company? = null,
  val cashier: String,
  val invoiceNumber: String = "00-00000-01",
  val eor: String,
  val zoi: String,
) {
  val id: UUID = UUID.randomUUID()
  private val created: LocalDateTime = LocalDateTime.now()
  private val updated: LocalDateTime = LocalDateTime.now()

  fun print() {
    var ret = "[${this.javaClass.simpleName} ${
      id.toString().takeLast(12)
    }] $created $invoiceNumber $cashier\n$eor $zoi\n$issuer"
    if (customer != null) {
      ret += "\n$customer"
    }
    //ret += "\n$items$payment"
    ret += "\n$payment"
    println(ret)
  }
}
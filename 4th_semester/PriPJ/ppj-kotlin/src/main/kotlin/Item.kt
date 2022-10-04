import util.BarcodeUtil.isBarcodeValid
import java.math.BigDecimal
import java.math.MathContext
import java.time.LocalDateTime
import java.util.UUID

open class Item(
  val name: String,
  val price: Price = Price(),
  val discount: Discount = Discount(),
  var quantity: BigDecimal = BigDecimal(1),
  val ddvType: DDVTYPE = DDVTYPE.B,
  val gs1: String = MutableList(13) { (0..9).random() }.toString(),
  val invoice: Invoice,
) {
  val id: UUID = UUID.randomUUID()
  private val created: LocalDateTime = LocalDateTime.now()
  private val updated: LocalDateTime = LocalDateTime.now()
  var ddv: DDV = DDV(ddvType, Price(price.multiply(quantity).multiply(ddvType.percent)))
  var total = Price()

  init {
    check()
    total = Price(price.multiply(quantity));
  }

  fun check(): Boolean {
    if (name.isEmpty()) return false
    if (price < BigDecimal(0.0001)) return false
    if (quantity < BigDecimal(0)) return false
    try {
      if (gs1.isEmpty() || isBarcodeValid(gs1.toMutableList())) throw IllegalArgumentException("Barcode isn't valid");
    } catch (ex: IllegalArgumentException) {
      return false;
    }
    return true
  }

  override fun toString(): String {
    return "[${this.javaClass.simpleName} ${
      id.toString().takeLast(12)
    }] $name $price ${quantity.round(MathContext(2))} $total ${gs1.toMutableList().joinToString("").takeLast(12)} $ddv $discount"
  }
}
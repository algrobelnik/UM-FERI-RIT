import java.math.BigDecimal
import java.time.LocalDateTime
import java.util.*

class InternalItem(
  val item: Item,
) {
  val id: UUID = UUID.randomUUID()
  private val created: LocalDateTime = LocalDateTime.now()
  private val updated: LocalDateTime = LocalDateTime.now()
  var internalId = 0;
  var department = 0;

  init {
    try {
      val join = item.gs1.toMutableList().joinToString("");
      println(join);
      internalId = join.take(3).toInt();
      if (internalId.toInt() < 200 || department.toInt() > 299)
        throw IllegalArgumentException("Internal barcode is wrong")
      department = join.substring(3, join.length).take(4).toInt();
      val _quantity = BigDecimal(join.substring(7, join.length).take(5).toInt());
      item.total = Price(item.price.multiply(_quantity));
    } catch (ex: Exception) {
      println(ex);
    }
  }
  override fun toString(): String {
    return super.toString() + "\n$internalId $department";
  }
}

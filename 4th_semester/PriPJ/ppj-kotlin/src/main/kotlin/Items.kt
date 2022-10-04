import java.math.BigDecimal
import java.time.LocalDateTime
import java.util.UUID

data class Items(
  var items: ArrayList<Item> = ArrayList(),
) {
  private val id: UUID = UUID.randomUUID()
  private var gs1: MutableList<Int> = MutableList(32) { (0..9).random() }
  private val created: LocalDateTime = LocalDateTime.now()
  private var updated: LocalDateTime = LocalDateTime.now()
  private var total: Price = Price()

  fun addItem(item: Item) {
    items.add(item)
    total += item.price.multiply(item.quantity)
  }

  fun delItem(item: Item) {
    items.remove(item)
    total -= item.price.multiply(item.quantity)
    updated = LocalDateTime.now()
  }

  fun updateItem(wrong: Item, correct: Item) {
    if (wrong != correct) {
      updated = LocalDateTime.now()
      this.delItem(wrong)
      this.addItem(correct)
    }
  }

  override fun toString(): String {
    var tmp = HashMap<DDVTYPE, Price>()
    for (item in items) {
      if (tmp.containsKey(item.ddvType)) {
        tmp[item.ddvType]?.value = tmp[item.ddvType]?.value?.plus(item.ddv.value.value)!!
      } else {
        tmp[item.ddvType] = Price(BigDecimal(0));
        tmp[item.ddvType]?.value = item.ddv.value.value
      }
    }
    var ret =
      "[${this.javaClass.simpleName} ${id.toString().takeLast(12)}] $total ${gs1.joinToString("").takeLast(12)}\n"
    for (calc in tmp) {
      ret += "${calc.key}->${calc.value}\n"
    }
    for (item in items) {
      ret += "$item \n"
    }
    return ret
  }
}
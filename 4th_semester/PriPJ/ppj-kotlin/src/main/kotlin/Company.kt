import java.time.LocalDateTime
import java.util.UUID

data class Company(
  val name: String,
  val locations: ArrayList<Address>,
  val ddvId: String,
  val taxNumber: String,
  val registrationNumber: String,
  val taxPayer: Boolean
) {
  val id: UUID = UUID.randomUUID()
  private val created: LocalDateTime = LocalDateTime.now()
  private val updated: LocalDateTime = LocalDateTime.now()
  override fun toString(): String {
    var ret = "[${this.javaClass.simpleName} ${
      id.toString().takeLast(12)
    }] $name $ddvId $taxNumber $registrationNumber $taxNumber $registrationNumber ${
      if (taxPayer) {
        "YES"
      } else {
        "NO"
      }
    }"
    for (loc in locations) {
      ret += "\n$loc"
    }
    return ret
  }
}
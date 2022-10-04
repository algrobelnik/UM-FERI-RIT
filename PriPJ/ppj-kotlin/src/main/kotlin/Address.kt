import java.time.LocalDateTime
import java.util.UUID

data class Address(
  val name: String,
  val post: String,
  val city: String,
) {
  private val id: UUID = UUID.randomUUID()
  private val created: LocalDateTime = LocalDateTime.now()
  private val updated: LocalDateTime = LocalDateTime.now()
  override fun toString() = "[${this.javaClass.simpleName} ${id.toString().takeLast(12)}] $name, $post $city"
}
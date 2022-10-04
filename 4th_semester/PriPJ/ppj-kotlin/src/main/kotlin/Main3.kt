import dao.mysql.*
import java.math.BigDecimal
import java.nio.ByteBuffer
import java.util.*

fun main() {
  try {
    //TODO(check if UUID exists for specified table insert)
    val mutableList = "2116789002000"
    val price1 = Price(BigDecimal(7.8))
    val price2 = Price(BigDecimal(5.89))
    val price3 = Price(BigDecimal(3.16))
    val locationsIssuer = arrayListOf(
      Address(name = "Pobreška c. 18", post = "2000", city = "Maribor"),
      Address(name = "Letališka c. 26", post = "1000", city = "Ljubljana")
    )
    val locationsCustomer = arrayListOf(
      Address(name = "Neka ulica, 1", post = "2000", city = "Maribor")
    )
    val issuer = Company(
      name = "MEGAMARKET EUROPARK, Spar Slovenija d.o.o.",
      locations = locationsIssuer,
      ddvId = "89393686",
      taxNumber = "32156782",
      registrationNumber = "5571693000",
      taxPayer = true
    )
    val customer = Company(
      name = "Moje podjetje s.p.",
      locations = locationsCustomer,
      ddvId = "SI59123456",
      taxNumber = "12345678",
      registrationNumber = "1234567890",
      taxPayer = true,
    )
    val payment: Payment =
      Payment(PAYMENTTYPE.card, "############3761", "A0000000031010", "Visa", price3)
    val invoice = Invoice(
      issuer = issuer,
      payment = payment,
      customer = customer,
      cashier = "COAO4434",
      zoi = "16ac684097c0b3ffbb37b2781151777",
      eor = "6f2b8121-b7c3-471a-b33e-b03376e24d75",
    )

    val salad = Item(
      name = "S-Solata KG iz solatne",
      price = price1,
      quantity = BigDecimal(0.011),
      gs1 = mutableList,
      invoice = invoice
    )
    val internalSalad = InternalItem(salad)
    val meal = Item(name = "Študentsko kosilo Menu", price = price2, quantity = BigDecimal(1), invoice = invoice)
    val items = Items()
    items.addItem(meal)
    items.addItem(salad)
    val sqlPrice = MySqlPrice()
    sqlPrice.insert(price1)
    sqlPrice.insert(price2)
    sqlPrice.insert(price3)
    val sqlDDV = MySqlDDV()
    sqlDDV.insert(meal.ddv)
    sqlDDV.insert(salad.ddv)
    val sqlCompany = MySqlCompany()
    sqlCompany.insert(issuer)
    sqlCompany.insert(customer)
    val sqlItem = MySqlItem()
    sqlItem.insert(meal)
    val sqlInternalItem = MySqlInternalItem()
    sqlInternalItem.insert(internalSalad)
    //val sqlItems = MysqlItems()
    //sqlItems.insert(items)
    val sqlInvoice = MySqlInvoice()
    sqlInvoice.insert(invoice)
    val readInvoice = MySqlInvoice().getById(invoice.id);
    readInvoice?.print()
    println("printed")
  } catch (ex: Exception) {
    println(ex.message)
  }
}

fun UUID.asBytes(): ByteArray {
  val buff = ByteBuffer.wrap(ByteArray(16))
  buff.putLong(mostSignificantBits)
  buff.putLong(leastSignificantBits)
  return buff.array()
}

fun ByteArray.asUUID(): UUID {
  val buff = ByteBuffer.wrap(this)
  val high = buff.long
  val low = buff.long
  return UUID(high, low)
}
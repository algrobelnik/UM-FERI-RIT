import java.math.BigDecimal

fun main() {
  val invoice1 = Invoice(
    issuer = Company(
      name = "MEGAMARKET EUROPARK, Spar Slovenija d.o.o.",
      locations = arrayListOf(
        Address(name = "Pobreška c. 18", post = "2000", city = "Maribor"),
        Address(name = "Letališka c. 26", post = "1000", city = "Ljubljana")
      ),
      ddvId = "89393686",
      taxNumber = "32156782",
      registrationNumber = "5571693000",
      taxPayer = true
    ),
    payment = Payment(PAYMENTTYPE.card, "############3761", "A0000000031010", "Visa", Price(BigDecimal(3.16))),
    cashier = "COAO4434",
    zoi = "16ac684097c0b3ffbb37b2781151777",
    eor = "6f2b8121-b7c3-471a-b33e-b03376e24d75",
  )
  val salad = Item(
    name = "S-Solata KG iz solatne",
    price = Price(BigDecimal(7.8)),
    quantity = BigDecimal(0.011),
    invoice = invoice1
  )
  val meal =
    Item(name = "Študentsko kosilo Menu", price = Price(BigDecimal(5.89)), quantity = BigDecimal(1), invoice = invoice1)
  val items1 = Items()
  items1.addItem(meal)
  items1.addItem(salad)
  invoice1.print()
  println("---------------------------------")
  val invoice2 = Invoice(
    issuer = Company(
      name = "Lidl Slovenija d.o.o k.d.",
      locations = arrayListOf(Address(name = "Pod lipami, 1", post = "1218", city = "Komenda")),
      ddvId = "SI59314923",
      taxNumber = "59314923",
      registrationNumber = "1719947000",
      taxPayer = true,
    ),
    customer = Company(
      name = "Moje podjetje s.p.",
      locations = arrayListOf(Address(name = "Neka ulica, 1", post = "2000", city = "Maribor")),
      ddvId = "SI59123456",
      taxNumber = "12345678",
      registrationNumber = "1234567890",
      taxPayer = true,
    ),
    payment = Payment(PAYMENTTYPE.card, "############3761", "A0000000031010", "Visa", Price(BigDecimal(22.94))),
    cashier = "61706023",
    zoi = "230d2ca89ccbcc24361579856d98c32c",
    eor = "2e7056f5-2363-42fb-ae84-a44518dd05c6",
  )
  val homemadeSalami = Item(name = "Homemade dry salami", price = Price(BigDecimal(4.99)), invoice = invoice2)
  val chickenSalami = Item(name = "Chicken hill salami", price = Price(BigDecimal(1.19)), invoice = invoice2)
  val hillBread = Item(name = "Hills mixed bread", price = Price(BigDecimal(1.79)), invoice = invoice2)
  val bananaChips = Item(name = "Banana chips", price = Price(BigDecimal(1.19)), invoice = invoice2)
  val pears = Item(name = "Pears", price = Price(BigDecimal(1.29)), quantity = BigDecimal(2), invoice = invoice2)
  val greekYogurt = Item(name = "Greek yogurt", price = Price(BigDecimal(2.69)), invoice = invoice2)
  val panache = Item(name = "Panache", price = Price(BigDecimal(3.49)), ddvType = DDVTYPE.C, invoice = invoice2)
  val pizzaPork = Item(name = "pizzaPork", price = Price(BigDecimal(0.89)), invoice = invoice2)
  val wrongHungarianSalami = Item(name = "hungarianSalami", price = Price(BigDecimal(7.99)), invoice = invoice2)
  val hungarianSalami = Item(name = "hungarianSalami", price = Price(BigDecimal(5.99)), invoice = invoice2)
  val items2 = Items()
  items2.addItem(homemadeSalami)
  items2.addItem(chickenSalami)
  items2.addItem(hillBread)
  items2.addItem(bananaChips)
  items2.addItem(pears)
  items2.addItem(greekYogurt)
  items2.addItem(panache)
  items2.addItem(pizzaPork)
  items2.addItem(wrongHungarianSalami)
  items2.updateItem(wrongHungarianSalami, hungarianSalami)
  invoice2.print()
}
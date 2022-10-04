package dao

import Item
import java.util.*

interface ItemDao : DaoCrud<Item> {
  fun getByBarcode(barcode: String): Item?
  fun getAllInvoice(invoice_id: UUID): List<Item>
}
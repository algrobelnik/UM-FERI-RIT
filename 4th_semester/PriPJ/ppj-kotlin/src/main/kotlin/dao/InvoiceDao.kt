package dao

import Invoice

interface InvoiceDao : DaoCrud<Invoice> {
  fun getByInvoiceNumber(invoiceNumber: String): Invoice?
  fun getAllByCashier(name: String): List<Invoice>
}
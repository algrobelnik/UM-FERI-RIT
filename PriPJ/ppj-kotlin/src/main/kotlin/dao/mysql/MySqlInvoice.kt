package dao.mysql

import Address
import Company
import Invoice
import Payment
import asBytes
import asUUID
import dao.InvoiceDao
import util.DatabaseUtil
import java.sql.ResultSet
import java.sql.SQLException
import java.util.*

class MySqlInvoice : InvoiceDao {
  override fun getByInvoiceNumber(invoiceNumber: String): Invoice? {
    val conn = DatabaseUtil.getConnection() ?: return null
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_BY_INVOICE_NUMBER, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
        select.setString(1, invoiceNumber)
        val rs = select.executeQuery()
        if (rs.next()) return mapDataToObject(rs)
      } catch (ex: SQLException) {
        println(ex)
      }
    }
    if (!conn.isClosed) conn.close()
    return null
  }

  override fun getAllByCashier(name: String): List<Invoice> {
    val res = mutableListOf<Invoice>()
    val conn = DatabaseUtil.getConnection() ?: return res
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_ALL_BY_CASHIER, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
        select.setString(1, name)
        val rs = select.executeQuery()
        while (rs.next()) {
          res.add(mapDataToObject(rs));
        }
      } catch (ex: SQLException) {
        println(ex)
      }
    }
    if (!conn.isClosed) conn.close()
    return res
  }

  override fun getById(id: UUID): Invoice? {
    val conn = DatabaseUtil.getConnection() ?: return null
    conn.use {
      try {
        val select = it.prepareStatement(SQL_GET_BY_ID, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
        select.setBytes(1, id.asBytes())
        val rs = select.executeQuery()
        if (rs.next()) return mapDataToObject(rs)
      } catch (ex: SQLException) {
        println(ex)
      }
    }
    if (!conn.isClosed) conn.close()
    return null
  }

  override fun getAll(): List<Invoice> {
    var res = mutableListOf<Invoice>()
    val conn = DatabaseUtil.getConnection() ?: return res
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_ALL, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
        val rs = select.executeQuery()
        while (rs.next()) {
          res.add(mapDataToObject(rs));
        }
      } catch (ex: SQLException) {
        ex.printStackTrace()
      }
    }
    if (!conn.isClosed) conn.close()
    return res
  }

  override fun insert(obj: Invoice): Boolean {
    val item = getById(obj.id)
    if (item != null) {
      return false
    }
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      try {
        val insert = it.prepareStatement(SQL_INSERT)
        insert.setString(1, obj.invoiceNumber)
        insert.setString(2, obj.cashier)
        insert.setString(3, obj.eor)
        insert.setString(4, obj.zoi)
        insert.setBytes(5, obj.issuer.id.asBytes())
        insert.setBytes(6, obj.customer?.id?.asBytes())
        val rs = insert.executeUpdate()
        if (!conn.isClosed) conn.close()
        return rs == 1
      } catch (ex: SQLException) {
        ex.printStackTrace()
      }
    }
    return false
  }

  override fun update(obj: Invoice): Boolean {
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      val update = it.prepareStatement(SQL_UPDATE)
      update.setString(1, obj.invoiceNumber)
      update.setString(2, obj.cashier)
      update.setString(3, obj.eor)
      update.setString(4, obj.zoi)
      update.setBytes(5, obj.issuer.id.asBytes())
      update.setBytes(6, obj.customer?.id?.asBytes())
      update.setBytes(7, obj.id.asBytes())
      val rs = update.executeUpdate()
      if (!conn.isClosed) conn.close()
      return rs == 1
    }
  }

  override fun delete(obj: Invoice): Boolean {
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      try {
        val update = it.prepareStatement(SQL_DELETE)
        update.setBytes(1, obj.id.asBytes())
        val rs = update.executeUpdate()
        conn.close()
        return rs == 1
      } catch (ex: SQLException) {
        ex.printStackTrace()
      }
    }
    if (!conn.isClosed) conn.close()
    return false
  }

  companion object {
    private const val TABLE = "invoice"
    private const val SQL_GET_BY_INVOICE_NUMBER = "SELECT * FROM $TABLE WHERE invoice_number = ? LIMIT 1"
    private const val SQL_GET_ALL_BY_CASHIER = "SELECT * FROM $TABLE WHERE cashier = ?"
    private const val SQL_GET_BY_ID = "SELECT * FROM $TABLE WHERE uuid = ? LIMIT 1"
    private const val SQL_GET_ALL = "SELECT * FROM $TABLE"
    private const val SQL_INSERT =
      "INSERT INTO $TABLE (invoice_number, cashier, eor, zoi, issuer_id, customer_id) VALUES (?, ?, ?, ?, ?, ?)"
    private const val SQL_UPDATE =
      "UPDATE $TABLE SET invoice_number = ?, cashier = ?, eor = ?, zoi = ?, issuer_id = ?, customer_id = ?, updated = NOW() WHERE uuid = ?"
    private const val SQL_DELETE = "DELETE FROM $TABLE WHERE uuid = ?"
    private fun mapDataToObject(rs: ResultSet): Invoice {
      val issuer: Company = MySqlCompany().getById(rs.getBytes("issuer_id").asUUID())!!
      val customer: Company? = MySqlCompany().getById(rs.getBytes("customer_id").asUUID())
      return Invoice(
        //TODO(implement payment)
        Payment(),
        issuer,
        customer,
        rs.getString("cashier"),
        rs.getString("invoice_number"),
        rs.getString("eor"),
        rs.getString("zoi"),
      )
    }
  }
}
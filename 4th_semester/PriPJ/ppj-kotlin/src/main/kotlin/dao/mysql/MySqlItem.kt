package dao.mysql

import DDV
import DDVTYPE
import Discount
import Item
import Price
import asBytes
import asUUID
import dao.ItemDao
import util.DatabaseUtil
import java.sql.ResultSet
import java.sql.SQLException
import java.util.*

class MySqlItem : ItemDao {

  override fun getByBarcode(barcode: String): Item? {
    val conn = DatabaseUtil.getConnection() ?: return null
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_BY_BARCODE, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
        select.setString(1, barcode)
        val rs = select.executeQuery()
        if (rs.next()) return mapDataToObject(rs)
      } catch (ex: SQLException) {
        println(ex)
      }
    }
    if (!conn.isClosed) conn.close()
    return null
  }

  override fun getAllInvoice(invoice_id: UUID): List<Item> {
    val res = mutableListOf<Item>()
    val conn = DatabaseUtil.getConnection() ?: return res
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_ALL_INVOICE, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
        select.setBytes(1, invoice_id.asBytes())
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

  override fun getById(id: UUID): Item? {
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

  override fun getAll(): List<Item> {
    var res = mutableListOf<Item>()
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

  override fun insert(obj: Item): Boolean {
    val item = getById(obj.id)
    if (item != null) {
      return false
    }
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      try {
        if (MySqlPrice().getById(obj.price.id) != null) {
          return false
        }
        if (MySqlDDV().getById(obj.ddv.id) != null) {
          return false
        }
        var priceID = MySqlPrice().insert(obj.price)
        var ddvID = MySqlDDV().insert(obj.ddv)
        val insert = it.prepareStatement(SQL_INSERT)
        insert.setString(1, obj.name)
        insert.setBigDecimal(2, obj.quantity)
        insert.setString(3, obj.gs1)
        insert.setBytes(4, obj.price.id.asBytes())
        insert.setBytes(5, obj.ddv.id.asBytes())
        insert.setBytes(6, obj.invoice.id.asBytes())
        val rs = insert.executeUpdate()
        if (!conn.isClosed) conn.close()
        return rs == 1
      } catch (ex: SQLException) {
        ex.printStackTrace()
      }
    }
    return false
  }

  override fun update(obj: Item): Boolean {
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      if (MySqlPrice().getById(obj.price.id) == null) {
        return false
      }
      if (MySqlDDV().getById(obj.ddv.id) == null) {
        return false
      }
      val update = it.prepareStatement(SQL_UPDATE)
      update.setString(1, obj.name)
      update.setBigDecimal(2, obj.quantity)
      update.setString(3, obj.gs1)
      update.setBytes(4, obj.price.id.asBytes())
      update.setBytes(5, obj.ddv.id.asBytes())
      update.setBytes(6, obj.id.asBytes())
      val rs = update.executeUpdate()
      if (!conn.isClosed) conn.close()
      return rs == 1
    }
  }

  override fun delete(obj: Item): Boolean {
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
    private const val TABLE = "item"
    private const val SQL_GET_BY_BARCODE = "SELECT * FROM $TABLE WHERE barcode = ? LIMIT 1"
    private const val SQL_GET_ALL_INVOICE = "SELECT * FROM $TABLE WHERE invoice_id = ?"
    private const val SQL_GET_BY_ID = "SELECT * FROM $TABLE WHERE uuid = ? LIMIT 1"
    private const val SQL_GET_ALL = "SELECT * FROM $TABLE"
    private const val SQL_INSERT =
      "INSERT INTO $TABLE (name, quantity, gs1, price_id, ddv_id, invoice_id) VALUES (?, ?, ?, ?, ?, ?)"
    private const val SQL_UPDATE =
      "UPDATE $TABLE SET name = ?, quantity = ?, gs1 = ?, price_id = ?, ddv_id = ?, invoice_id = ?, updated = NOW() WHERE uuid = ?"
    private const val SQL_DELETE = "DELETE FROM $TABLE WHERE uuid = ?"
    private fun mapDataToObject(rs: ResultSet): Item {
      //TODO(implement discounts)
      //val discount: Discount = MysqlDiscount().getById(rs.getBytes("price"))
      val price: Price = MySqlPrice().getById(rs.getBytes("price_id").asUUID())!!
      val ddv: DDV = MySqlDDV().getById(rs.getBytes("ddv_id").asUUID())!!
      val invoice = MySqlInvoice().getById(rs.getBytes("invoice_id").asUUID())!!
      return Item(
        rs.getString("name"),
        price,
        Discount(),
        rs.getBigDecimal("quantity"),
        ddv.ddvType,
        rs.getString("gs1"),
        invoice
      )
    }
  }
}
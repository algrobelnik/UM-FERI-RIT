package dao.mysql

import Price
import asBytes
import dao.PriceDao
import util.DatabaseUtil
import java.sql.ResultSet
import java.sql.SQLException
import java.util.*

class MySqlPrice : PriceDao {
  override fun getByCurrency(currency: String): Price? {
    val conn = DatabaseUtil.getConnection() ?: return null
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_BY_CURRENCY, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
        select.setString(1, currency)
        val rs = select.executeQuery()
        if (rs.next()) return mapDataToObject(rs)
      } catch (ex: SQLException) {
        println(ex)
      }
    }
    if (!conn.isClosed) conn.close()
    return null
  }

  override fun getLast5Eur(currency: String): MutableList<Price> {
    val res = mutableListOf<Price>()
    val conn = DatabaseUtil.getConnection() ?: return res
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_LAST_5_EUR, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
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

  override fun getById(id: UUID): Price? {
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

  override fun getAll(): List<Price> {
    var res = mutableListOf<Price>()
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

  override fun insert(obj: Price): Boolean {
    val item = getById(obj.id)
    if (item != null) {
      return false
    }
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      try {
        val insert = it.prepareStatement(SQL_INSERT)
        insert.setBigDecimal(1, obj.value)
        insert.setString(2, obj.currency.currencyCode)
        val rs = insert.executeUpdate()
        if (!conn.isClosed) conn.close()
        return rs == 1
      } catch (ex: SQLException) {
        ex.printStackTrace()
      }
    }
    return false
  }

  override fun update(obj: Price): Boolean {
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      val update = it.prepareStatement(SQL_UPDATE)
      update.setBigDecimal(1, obj.value)
      update.setString(2, obj.currency.currencyCode)
      update.setBytes(3, obj.id.asBytes())
      val rs = update.executeUpdate()
      if (!conn.isClosed) conn.close()
      return rs == 1
    }
  }

  override fun delete(obj: Price): Boolean {
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
    private const val TABLE = "price"
    private const val SQL_GET_BY_CURRENCY = "SELECT * FROM $TABLE WHERE currency = ? LIMIT 1"
    private const val SQL_GET_LAST_5_EUR = "SELECT * FROM $TABLE WHERE currency = \"EUR\" ORDER BY updated DESC LIMIT 5"
    private const val SQL_GET_BY_ID = "SELECT * FROM $TABLE WHERE uuid = ? LIMIT 1"
    private const val SQL_GET_ALL = "SELECT * FROM $TABLE"
    private const val SQL_INSERT =
      "INSERT INTO $TABLE (value, currency) VALUES (?, ?)"
    private const val SQL_UPDATE =
      "UPDATE $TABLE SET value = ?, currency = ?, updated = NOW() WHERE uuid = ?"
    private const val SQL_DELETE = "DELETE FROM $TABLE WHERE uuid = ?"
    private fun mapDataToObject(rs: ResultSet): Price {
      return Price(
        rs.getBigDecimal("value"),
        Currency.getInstance(rs.getString("currency")),
      )
    }
  }
}
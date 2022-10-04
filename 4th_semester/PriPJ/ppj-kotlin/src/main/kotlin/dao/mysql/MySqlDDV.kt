package dao.mysql

import DDV
import DDVTYPE
import Price
import asBytes
import asUUID
import dao.DDVDao
import util.DatabaseUtil
import java.sql.ResultSet
import java.sql.SQLException
import java.util.*

class MySqlDDV : DDVDao {
  override fun getByDDVType(ddvtype: DDVTYPE): DDV? {
    val conn = DatabaseUtil.getConnection() ?: return null
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_BY_DDV_TYPE, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
        select.setString(1, ddvtype.name)
        val rs = select.executeQuery()
        if (rs.next()) return mapDataToObject(rs)
      } catch (ex: SQLException) {
        println(ex)
      }
    }
    if (!conn.isClosed) conn.close()
    return null
  }

  override fun getAllBTypeDDV(): List<DDV> {
    val res = mutableListOf<DDV>()
    val conn = DatabaseUtil.getConnection() ?: return res
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_ALL_B_TYPE_DDV, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
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

  override fun getById(id: UUID): DDV? {
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

  override fun getAll(): List<DDV> {
    var res = mutableListOf<DDV>()
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

  override fun insert(obj: DDV): Boolean {
    val item = getById(obj.id)
    if (item != null) {
      return false
    }
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      try {
        val insert = it.prepareStatement(SQL_INSERT)
        insert.setString(1, obj.ddvType.name)
        insert.setBytes(2, obj.value.id.asBytes())
        println(insert)
        val rs = insert.executeUpdate()
        if (!conn.isClosed) conn.close()
        return rs == 1
      } catch (ex: SQLException) {
        ex.printStackTrace()
      }
    }
    return false
  }

  override fun update(obj: DDV): Boolean {
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      val update = it.prepareStatement(SQL_UPDATE)
      update.setString(1, obj.ddvType.name)
      update.setBytes(2, obj.value.id.asBytes())
      update.setBytes(3, obj.id.asBytes())
      val rs = update.executeUpdate()
      if (!conn.isClosed) conn.close()
      return rs == 1
    }
  }

  override fun delete(obj: DDV): Boolean {
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
    private const val TABLE = "ddv"
    private const val SQL_GET_BY_DDV_TYPE = "SELECT * FROM $TABLE WHERE ddv_type = ? LIMIT 1"
    private const val SQL_GET_ALL_B_TYPE_DDV = "SELECT * FROM $TABLE WHERE ddv_type = 'B'"
    private const val SQL_GET_BY_ID = "SELECT * FROM $TABLE WHERE uuid = ? LIMIT 1"
    private const val SQL_GET_ALL = "SELECT * FROM $TABLE"
    private const val SQL_INSERT =
      "INSERT INTO $TABLE (ddv_type, price_id) VALUES (?, ?)"
    private const val SQL_UPDATE =
      "UPDATE $TABLE SET ddv_type = ?, price_id = ?, updated = NOW() WHERE uuid = ?"
    private const val SQL_DELETE = "DELETE FROM $TABLE WHERE uuid = ?"
    private fun mapDataToObject(rs: ResultSet): DDV {
      val price: Price = MySqlPrice().getById(rs.getBytes("price_id").asUUID())!!
      return DDV(
        DDVTYPE.valueOf(rs.getString("ddv_type")),
        price
      )
    }
  }
}
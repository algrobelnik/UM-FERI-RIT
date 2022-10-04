package dao.mysql

import InternalItem
import Item
import asBytes
import asUUID
import dao.InternalItemDao
import util.DatabaseUtil
import java.sql.ResultSet
import java.sql.SQLException
import java.util.*

class MySqlInternalItem : InternalItemDao {

  override fun getByInternalId(internalId: Int): InternalItem? {
    val conn = DatabaseUtil.getConnection() ?: return null
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_BY_INTERNAL_ID, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
        select.setInt(1, internalId)
        val rs = select.executeQuery()
        if (rs.next()) return mapDataToObject(rs)
      } catch (ex: SQLException) {
        println(ex)
      }
    }
    if (!conn.isClosed) conn.close()
    return null
  }

  override fun getAllByDepartment(department: Int): List<InternalItem> {
    val res = mutableListOf<InternalItem>()
    val conn = DatabaseUtil.getConnection() ?: return res
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_ALL_BY_DEPARTMENT, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
        select.setInt(1, department)
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

  override fun getById(id: UUID): InternalItem? {
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

  override fun getAll(): List<InternalItem> {
    var res = mutableListOf<InternalItem>()
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

  override fun insert(obj: InternalItem): Boolean {
    val item = getById(obj.id)
    if (item != null) {
      return false
    }
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      try {
        if (MySqlItem().getById(obj.item.id) != null) {
          return false
        }
        val insert = it.prepareStatement(SQL_INSERT)
        insert.setInt(1, obj.internalId)
        insert.setInt(2, obj.department)
        insert.setBytes(3, obj.item.id.asBytes())
        val rs = insert.executeUpdate()
        if (!conn.isClosed) conn.close()
        return rs == 1
      } catch (ex: SQLException) {
        ex.printStackTrace()
      }
    }
    return false
  }

  override fun update(obj: InternalItem): Boolean {
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      if (MySqlItem().getById(obj.item.id) != null) {
        return false
      }
      val update = it.prepareStatement(SQL_UPDATE)
      update.setInt(1, obj.internalId)
      update.setInt(2, obj.department)
      update.setBytes(3, obj.item.id.asBytes())
      update.setBytes(4, obj.id.asBytes())
      val rs = update.executeUpdate()
      if (!conn.isClosed) conn.close()
      return rs == 1
    }
  }

  override fun delete(obj: InternalItem): Boolean {
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
    private const val TABLE = "internal_item"
    private const val SQL_GET_BY_INTERNAL_ID = "SELECT * FROM $TABLE WHERE internal_id = ? LIMIT 1"
    private const val SQL_GET_ALL_BY_DEPARTMENT = "SELECT * FROM $TABLE WHERE department = ?"
    private const val SQL_GET_BY_ID = "SELECT * FROM $TABLE WHERE uuid = ? LIMIT 1"
    private const val SQL_GET_ALL = "SELECT * FROM $TABLE"
    private const val SQL_INSERT =
      "INSERT INTO $TABLE (internal_id, department, item_id) VALUES (?)"
    private const val SQL_UPDATE =
      "UPDATE $TABLE SET internal_id = ?, department = ?, item_id = ?, updated = NOW() WHERE uuid = ?"
    private const val SQL_DELETE = "DELETE FROM $TABLE WHERE uuid = ?"
    private fun mapDataToObject(rs: ResultSet): InternalItem {
      //TODO(implement discounts)
      //val discount: Discount = MySqlDiscount().getById(rs.getBytes("price"))
      val item: Item = MySqlItem().getById(rs.getBytes("item_id").asUUID())!!
      return InternalItem(
        item
      )
    }
  }
}
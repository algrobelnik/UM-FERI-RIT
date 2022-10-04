package dao.mysql

import Address
import Company
import Price
import asBytes
import asUUID
import dao.CompanyDao
import util.DatabaseUtil
import java.sql.ResultSet
import java.sql.SQLException
import java.util.*
import kotlin.collections.ArrayList

class MySqlCompany : CompanyDao {
  override fun getByDDV(ddv: String): Company? {
    val conn = DatabaseUtil.getConnection() ?: return null
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_BY_DDV, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
        select.setString(1, ddv)
        val rs = select.executeQuery()
        if (rs.next()) return mapDataToObject(rs)
      } catch (ex: SQLException) {
        println(ex)
      }
    }
    if (!conn.isClosed) conn.close()
    return null
  }

  override fun getAllTaxPayers(): List<Company> {
    val res = mutableListOf<Company>()
    val conn = DatabaseUtil.getConnection() ?: return res
    conn.use {
      try {
        val select =
          it.prepareStatement(SQL_GET_ALL_TAX_PAYERS, ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE)
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

  override fun getById(id: UUID): Company? {
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

  override fun getAll(): List<Company> {
    var res = mutableListOf<Company>()
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

  override fun insert(obj: Company): Boolean {
    val item = getById(obj.id)
    if (item != null) {
      return false
    }
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      try {
        val insert = it.prepareStatement(SQL_INSERT)
        insert.setString(1, obj.name)
        insert.setString(2, obj.ddvId)
        insert.setString(3, obj.taxNumber)
        insert.setString(4, obj.registrationNumber)
        insert.setBoolean(5, obj.taxPayer)
        val rs = insert.executeUpdate()
        if (!conn.isClosed) conn.close()
        return rs == 1
      } catch (ex: SQLException) {
        ex.printStackTrace()
      }
    }
    return false
  }

  override fun update(obj: Company): Boolean {
    val conn = DatabaseUtil.getConnection() ?: return false
    conn.use {
      val update = it.prepareStatement(SQL_UPDATE)
      update.setString(1, obj.name)
      update.setString(2, obj.ddvId)
      update.setString(3, obj.taxNumber)
      update.setString(4, obj.registrationNumber)
      update.setBoolean(5, obj.taxPayer)
      update.setBytes(6, obj.id.asBytes())
      val rs = update.executeUpdate()
      if (!conn.isClosed) conn.close()
      return rs == 1
    }
  }

  override fun delete(obj: Company): Boolean {
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
    private const val TABLE = "company"
    private const val SQL_GET_BY_DDV = "SELECT * FROM $TABLE WHERE ddv = ? LIMIT 1"
    private const val SQL_GET_ALL_TAX_PAYERS = "SELECT * FROM $TABLE WHERE tax_payer = true"
    private const val SQL_GET_BY_ID = "SELECT * FROM $TABLE WHERE uuid = ? LIMIT 1"
    private const val SQL_GET_ALL = "SELECT * FROM $TABLE"
    private const val SQL_INSERT =
      "INSERT INTO $TABLE (name, ddv, tax_number, registration_number, tax_payer) VALUES (?, ?, ?, ?, ?)"
    private const val SQL_UPDATE =
      "UPDATE $TABLE SET name = ?, ddv = ?, tax_number = ?, registration_number = ?, tax_payer = ?, updated = NOW() WHERE uuid = ?"
    private const val SQL_DELETE = "DELETE FROM $TABLE WHERE uuid = ?"
    private fun mapDataToObject(rs: ResultSet): Company {
      val price: Price = MySqlPrice().getById(rs.getBytes("price_id").asUUID())!!
      return Company(
        rs.getString("name"),
        //TODO(implement more addresses)
        ArrayList<Address>(),
        rs.getString("ddv"),
        rs.getString("tax_number"),
        rs.getString("registration_number"),
        rs.getBoolean("tax_payer")
      )
    }
  }
}
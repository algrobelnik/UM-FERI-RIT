package util

import Config
import com.fasterxml.jackson.module.kotlin.jacksonObjectMapper
import com.fasterxml.jackson.module.kotlin.readValue
import java.io.File
import java.sql.Connection
import java.sql.DriverManager
import java.sql.SQLException
import java.util.*

object DatabaseUtil {
  fun getConnection() : Connection? {
    val mapper = jacksonObjectMapper()
    val json = mapper.readValue<Config>(File("src/config.json"))
    val connectionProps = Properties()
    connectionProps.put("user", json.username)
    connectionProps.put("password", json.password)
    try {
      return DriverManager.getConnection("jdbc:mysql://${json.url}:${json.port}/${json.database}", connectionProps);
    } catch (ex: SQLException) {
      ex.printStackTrace()
    } catch (ex: Exception) {
      ex.printStackTrace()
    }
    return null
  }
}

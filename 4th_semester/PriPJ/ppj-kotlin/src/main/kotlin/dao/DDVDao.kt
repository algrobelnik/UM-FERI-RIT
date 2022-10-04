package dao

import DDV
import DDVTYPE

interface DDVDao : DaoCrud<DDV> {
  fun getByDDVType(ddvtype: DDVTYPE): DDV?
  fun getAllBTypeDDV(): List<DDV>
}
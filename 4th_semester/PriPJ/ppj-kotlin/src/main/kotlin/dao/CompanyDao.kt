package dao

import Company

interface CompanyDao : DaoCrud<Company> {
  fun getByDDV(ddv: String): Company?
  fun getAllTaxPayers(): List<Company>
}
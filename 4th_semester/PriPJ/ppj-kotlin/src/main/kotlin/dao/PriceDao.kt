package dao

import Price

interface PriceDao : DaoCrud<Price> {
  fun getByCurrency(currency: String): Price?
  fun getLast5Eur(currency: String): List<Price>
}
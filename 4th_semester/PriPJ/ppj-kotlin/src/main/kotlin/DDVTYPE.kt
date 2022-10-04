import java.math.BigDecimal

enum class DDVTYPE(val percent: BigDecimal) {
  A(BigDecimal(0)), B(BigDecimal(0.095)), C(BigDecimal(0.22)), D(BigDecimal(0)), E(BigDecimal(0.05)), EMPTY(BigDecimal(0));

  fun isNotEmpty(): Boolean {
    return this != EMPTY
  }
}

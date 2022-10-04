package util

object BarcodeUtil {
    fun isBarcodeValid(barcode: MutableList<Char>): Boolean{
      var sum1 = 0;
      var sum2 = 0;
      for ((index,c) in barcode.withIndex()) {
        if(index % 2 == 1){
          sum1 += c.digitToInt()
        }else {
          sum2 += c.digitToInt()
        }
      }
      sum1 *= 3
      sum1 += sum2
      return (sum1 + barcode[barcode.size - 1].digitToInt()) % 10 == 0
    }
  fun getCompanyCountryFromBarcode(barcode: MutableList<Int>): String{
    var str = barcode.joinToString("");
    when(str[0]){
      '0'->{return "USA AND CANADA"}
      '1'-> {
        return "USA"
      }
      '3' -> {
        when (str[1]) {
          '0', '1', '2', '3', '4', '5', '6', '7' -> return "FRANCE AND MONACO";
          '8' -> when (str[2]) {
            '0' -> return "BULGARIA"
            '3' -> return "SLOVENIA"
            '5' -> return "CROATIA"
            '7' -> return "BOSNIA AND HERZEGOVINA"
            '9' -> return "MONTENEGRO"
          }
        }
      }
      '4' -> {
        when (str[1]) {
          '0','1','2','3','4'-> return "GERMANY";
          '5','9'->return "JAPAN"
          '6'->return "RUSSIA"
          '7' -> when (str[2]) {
            '0' -> return "KYRGYZSTAN"
            '1' -> return "TAIWAN"
            '4' -> return "ESTONIA"
            '5' -> return "LATVIA"
            '6' -> return "AZERBAIJAN"
            '7' -> return "LITHUANIA"
            '8' -> return "UZBEKISTAN"
            '9' -> return "SRI LANKA"
          }
          '8' -> when (str[2]) {
            '0' -> return "PHILIPPINES"
            '1' -> return "BELARUS"
            '2' -> return "UKRAINE"
            '3' -> return "TURKMENISTAN"
            '4' -> return "MOLDOVA"
            '5' -> return "ARMENIA"
            '6' -> return "GEORGIA"
            '7' -> return "KAZAKHSTAN"
            '8' -> return "TAJIKISTAN"
            '9' -> return "HONK KONG"
          }
        }
      }
      '5' -> when (str[1]) {
        '0'->return "UNITED KINGDOM";
      }
    };
    return "UNKNOWN";
  }
}

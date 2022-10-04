#!/bin/awk

function gradeToString(num){
  switch (num) {
    case /5[[:digit:]]/: return "zadostno"
    case /6[[:digit:]]/: return "dobro"
    case /7[[:digit:]]/: return "prav dobro"
    case /8[[:digit:]]/: return "zelo dobro"
    case /9[[:digit:]]/:
    case 100: return "odlično"
    default: return "nezadostno"
 }
}

function abs(value){
  return (value<0?-value:value);
}

function avg(arr, num, start, i, count){
  count = 0
  for (i=0; i < NR; i++){
    if (arr[i] < num)
    count++
  }
  return abs(count - start)
}

BEGIN{
  print "Študent\tRezulta\tUspeh"
}

{
  sum[NR] = 0;
  for (i = 1; i <= NF-1; i++) sum[NR] += $i;
  sum[NR] /= NF-2;
  sum[NR] += $NF;
  sum[NR] /= 2;
  total_sum += sum[NR];
  printf "%s\t%.2f\t%s\n", $1, sum[NR], gradeToString(sum[NR]);
}

END{
  print "\nPovprečje razreda:\t" total_sum/NR
  print "Nadpovprečnih:\t" avg(sum, total_sum/NR, NR)
  print "Podpovprečnih:\t" avg(sum, total_sum/NR, 0)
}

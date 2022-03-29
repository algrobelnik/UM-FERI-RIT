function loto(arr, i, j, n, tmp) {
  n = length(arr)
  for (i=n; i>1; i--) {
    j = int(1 + rand()*i)
    tmp = arr[i]
    arr[i] = arr[j]
    arr[j] = tmp
  }
}

BEGIN {
  srand()
  for (i=1; i<=NUM; i++) {
    arr[i] = i
  }
  loto(arr)
  for (i=1; i<=MAX_NUM; i++) {
    print arr[i]
  }
}

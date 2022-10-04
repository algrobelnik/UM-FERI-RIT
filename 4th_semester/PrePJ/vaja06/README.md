# Razpoznavalnik 1
./gradlew run -q --args="$@"
diff <(cat - <<<"$output") "$tokens"

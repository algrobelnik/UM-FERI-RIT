# Avtomate 2
./gradlew run -q --args="$@"
diff <(cat - <<<"$output") "$tokens"

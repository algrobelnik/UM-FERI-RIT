#include <iostream>
#include <array>
using namespace std;

int main()
{    
		array<string,10> places = {"Celje", "Maribor", "Barcelona", "Paris", "New York", "Vancouver", "Rio de Janeiro", "Venezia", "Tokyo","Tunis"};
    array<int,10> weather_morning = {6,6,7,6,16,8,20,10,13,15};
    array<int,10> weather_evening = {8,8,18,12,22,12,26,15,16,24};
		array<string,10> urls = {"https://www.accuweather.com/en/si/celje/297396/daily-weather-forecast/297396?day=1",
		"https://www.accuweather.com/en/si/maribor/299438/current-weather/299438?lang=en-us&partner=wdg_operanrw_web",
		"https://www.accuweather.com/en/es/barcelona/307297/daily-weather-forecast/307297",
		"https://www.accuweather.com/en/fr/paris/623/weather-forecast/623",
		"https://www.accuweather.com/en/us/new-york/10007/weather-forecast/349727",
		"https://www.accuweather.com/en/ca/vancouver/v6c/daily-weather-forecast/53286",
		"https://www.accuweather.com/en/br/rio-de-janeiro/45449/daily-weather-forecast/45449",
		"https://www.accuweather.com/en/it/venice/1-216711_1_al/weather-forecast/1-216711_1_al",
		"https://www.accuweather.com/en/jp/tokyo/226396/daily-weather-forecast/226396",
		"https://www.accuweather.com/en/tn/tunis/321398/weather-forecast/321398"
		};
		string title = "Weather | Morning | Evening | Source";
		cout << title << "\n";
		for (int i = 0; i < places.size(); i++) {
			cout << places[i] << " | " << weather_morning[i] << "°C | " << weather_evening[i] << "°C | " << urls[i] << "\n";
		}
    return 0;
}
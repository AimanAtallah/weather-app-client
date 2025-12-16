//
//  main.cpp
//  WeatherAppinCPP
//
//  Created by Aiman Atallah on 12/14/25.
//

#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

//=============================================================================
// 
//   TODO: ADD A FRONT END TO IT USING SWIFT AND OBJ-C BRIDGE
//   TODO: CHECK FOR BUGS AND TEST CASES
//
//
//
//=====================Version 1 Weather App====================================

size_t writeToString(void* contents, size_t size, size_t numMembers, void* userp){
    size_t totalSize = size * numMembers;
    
    string* str = static_cast<string*>(userp);
    str->append(static_cast<char*>(contents), totalSize);
    
    return totalSize;
}
void userCityFormat(string& input){
        size_t findSpace = input.find(" ");
        string temp = "&q=";
        int spacePosition = 0;
        string space = " ";
        string replaceSpace = "%20";
        while((spacePosition = input.find(space, spacePosition + 1)) != string::npos){
                if(input[spacePosition] == ' '){
                    input.replace(spacePosition, 1, replaceSpace);
                }
        }
        input = temp + input;
        
}

int main() {
    string response;
    string userCity;
    bool finishedCheckingWeather = false;
    const string API_KEY = "";// API KEY IS OMMITED INTENTIONALLY
    CURL* curl = curl_easy_init();

    if(!curl){
        cout << "Failed to initialize";
        return 1;
    }
    
    while(!finishedCheckingWeather){
        cout << "Enter a city or E to exit: ";
        getline(cin, userCity);
        if(userCity == "E" || userCity == "e"){
            finishedCheckingWeather = true;
            continue;
        }
        
        userCityFormat(userCity);
        
 
        
        string url = "https://api.weatherapi.com/v1/current.json?key=" + API_KEY + userCity;
        
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        CURLcode result = curl_easy_perform(curl);
        if(result != CURLE_OK){ cout << "Rquest Failed\n"; }
        
        size_t tempPos = response.find("\"temp_f\":");
        tempPos += 9;
        size_t tempEnd = response.find(",", tempPos);
        string tempStr = response.substr(tempPos, tempEnd - tempPos);
        double tempF = stod(tempStr);
        
        cout << "Temperature (F): " << tempF << endl;
        
        size_t conditionPos = response.find("\"condition\":");
        conditionPos += 21;
        tempEnd = response.find(",", conditionPos);
        tempStr = response.substr(conditionPos, (tempEnd-1) - conditionPos);
        string condition = tempStr;
        
        cout << "Condition currently: " << tempStr << endl;
        
        size_t feelLikePos = response.find("\"feelslike_f\":");
        feelLikePos += 14;
        tempEnd = response.find(",", feelLikePos);
        string feelsLike_F = response.substr(feelLikePos, tempEnd - feelLikePos);
        
        cout << "It currently feels Like: " << feelsLike_F << endl;
        
        size_t windChillPos = response.find("\"windchill_f\":");
        windChillPos += 14;
        tempEnd = response.find(",", windChillPos);
        string windChill = response.substr(windChillPos, tempEnd - windChillPos);
        
        cout << "Current wind Chill: " << windChill << endl;
       
        response.clear();// clear response incase of new call
    }
    curl_easy_cleanup(curl);// delete curl
    
    return 0;
}

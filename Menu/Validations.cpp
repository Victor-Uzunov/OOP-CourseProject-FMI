
#include "Validations.h"

size_t stringSize(const char* str){
    size_t size = 0;
    while(str[size] != '\0'){
        size++;
    }
    return size;
}

bool correctName(const char* name){
    int i = 0;
    if(name[i] < 65 || name[i] > 90 || stringSize(name) < 2){
        return false;
    }
    i++;
    while(name[i] != '\0'){
        if(name[i] < 97 || name[i] > 122){
            return false;
        }
        i++;
    }
    return true;
}
bool correctRating(double rating){
    if(rating < 0 || rating > 10){
        return false;
    }
    return true;
}
bool correctPassengersCount(size_t count){
    if(count > 4){
        return false;
    }
    return true;
}
bool correctPhoneNumber(const char* number){
    if(stringSize(number) < 6){
        return false;
    }
    int i = 0;
    while(number[i] != '\0'){
        if(number[i] < 48 || number[i] > 57){
            return false;
        }
        i++;
    }
    return true;
}
bool correctCarNumber(const char* number){
    if(stringSize(number) != 7){
        return false;
    }
    if(number[0] < 65 || number[6] > 90){
        return false;
    }
    int i = 1;
    while(i < 7){
        if(i < 5) {
            if (number[i] < 48 || number[i] > 57) {
                return false;
            }
        }
        else{
            if(number[i] < 65 || number[i] > 90){
                return false;
            }
        }
        i++;
    }
    return true;
}
bool correctMinutes(size_t minutes){
    if(minutes > 30){
        return false;
    }
    return true;
}
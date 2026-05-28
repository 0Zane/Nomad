#include "tips.h"
#include "string"


std::string gettip(int question_ID){

    if (question_ID < 10) //will have to replace by a function called to return the size of the array
    return answers[question_ID];

    else {
        return "The answer is not available";
    }

}
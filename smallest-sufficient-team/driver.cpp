#include "dynamic.cpp"

#include <iostream>

/*
req_skills = ["algorithms","math","java","reactjs","csharp","aws"],
people = [
    ["algorithms","math","java"],
    ["algorithms","math","reactjs"],
    ["java","csharp","aws"],
    ["reactjs","csharp"],
    ["csharp","math"],
    ["aws","java"]
]
 */

int main() {
    std::vector<std::string> skills{"algorithms","math","java","reactjs","csharp","aws"};
    std::vector<std::vector<std::string>> people{
        {"algorithms","math","java"},
        {"algorithms","math","reactjs"},
        {"java","csharp","aws"},
        {"reactjs","csharp"},
        {"csharp","math"},
        {"aws","java"}
    };


    for (int index : Solution().smallestSufficientTeam(skills, people)) {
        std::cout << index << " ";
    }

    std::cout << "\n";
}

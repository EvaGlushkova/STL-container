/*
Glushkova Eva st108255@student.spbu.ru
*/

#include <iostream>
#include <string>
#include "CyclicalList.h"


template <typename T>
void showList(const CyclicalList<T>& lst) {
    for (const auto& i : lst) {
        std::cout << i <<' ';
    }
    std::cout << '\n';
}

int main() {
    CyclicalList<int> nums;
    nums.append(30);
    nums.append(239);
    nums.append(56);
    
    showList(nums);
    std::cout << "Front: " << nums.front() << ", Back: " << nums.back() << "\n";
    
    nums.prepend(5);
    showList(nums);
    
    nums.remove_front();
    showList(nums);
    
    nums.remove_back();
    showList(nums);
    
    std::cout << "\n\nString list test:\n";
    CyclicalList<std::string> words;
    words.append("hi");
    words.append("cat");
    
    showList(words);
    
    words.prepend("dog");
    showList(words);
    
    words.remove_front();
    showList(words);

    std::cout << "\n\nIterator test:\n";
    CyclicalList<int> iterList;
    for (int i = 1; i <= 3; i++) iterList.append(i * 10);
    
    showList(iterList);
    
    auto it = iterList.begin();
    ++it;
    iterList.insert(it, 25);
    showList(iterList);
    
    it = iterList.begin();
    ++it;
    iterList.erase(it);
    showList(iterList);
    
    std::cout << "\n\nCopy/clear test:\n";
    CyclicalList<int> original;
    original.append(10);
    original.append(20);
    
    CyclicalList<int> copy = original;
    showList(original);
    showList(copy);
    
    original.clear();
    showList(original);
    showList(copy);
    
    std::cout << "\nIt's all okay \n";
    return 0;
}

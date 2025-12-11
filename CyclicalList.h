/*
Glushkova Eva st108255@student.spbu.ru
*/

#ifndef CYCLICAL_LIST_H
#define CYCLICAL_LIST_H
/**
 * @file CyclicalList.h
 * @brief Implementation of an STL-style cyclic double-linked list
 */

#include <cstddef>
#include <stdexcept>
#include <concepts>
#include <utility>
#include <iterator>
#include <algorithm> 


/**
 * @class CyclicalList
 * @brief A cyclic bilinked list with an STL container interface
 *
 * @tparam T The type of elements stored in the list
 */
template <typename T>
class CyclicalList {
private:
    /**
    * @struct ListNode
    * @brief List node structure storing data and pointers
    */
    struct ListNode {
        T element_value;
        ListNode* next_node;
        ListNode* previous_node;

        explicit ListNode(const T& val) 
            : element_value(val), next_node(this), previous_node(this) {}
            
        explicit ListNode(T&& val) 
            : element_value(std::move(val)), next_node(this), previous_node(this) {}
    };

    ListNode* start_node = nullptr;
    size_t element_count = 0;
    
    /**
     * @brief Verifies the list contains elements
     * @throws std::out_of_range if list is empty
     */
    void verify_non_empty() const {
        if (is_empty()) {
            throw std::out_of_range("CyclicalList: operation on empty list :( ");
        }
    }

public:
    CyclicalList() noexcept = default;

    CyclicalList(const CyclicalList& source) {
        for (const T& elem : source) {
            append(elem);
        }
    }

    CyclicalList(CyclicalList&& source) noexcept
            : start_node(source.start_node), element_count(source.element_count) {
        source.start_node = nullptr;
        source.element_count = 0;
    }

    CyclicalList& operator=(const CyclicalList& source) {
        if (this != &source) {
            CyclicalList temp(source);
            exchange(temp);
        }
        return *this;
    }

    CyclicalList& operator=(CyclicalList&& source) noexcept {
        if (this != &source) {
            clear();
            start_node = source.start_node;
            element_count = source.element_count;
            source.start_node = nullptr;
            source.element_count = 0;
        }
        return *this;
    }

    ~CyclicalList() {
        clear();
    }
    
    /**
     * @class iterator
     * @brief Bidirectional iterator 

     */
    class iterator {
        friend class CyclicalList;

        ListNode* current_node = nullptr;
        const ListNode* list_start = nullptr;

        explicit iterator(ListNode* node_ptr, const ListNode* start_ptr) 
            : current_node(node_ptr), list_start(start_ptr) {}

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator() = default;

        reference operator*() const {
            if (!current_node) throw std::out_of_range("Dereferencing end iterator");
            return current_node->element_value;
        }

        pointer operator->() const {
            return std::addressof(operator*());
        }

        iterator& operator++() {
            if (!current_node) throw std::out_of_range("Incrementing end iterator");
            current_node = (current_node->next_node == list_start) 
                ? nullptr : current_node->next_node;
            return *this;
        }

        iterator operator++(int) {
            iterator previous = *this;
            ++(*this);
            return previous;
        }

        iterator& operator--() {
            if (!list_start) throw std::out_of_range("Decrementing in empty list");
            if (!current_node) current_node = const_cast<ListNode*>(list_start->previous_node);
            else current_node = current_node->previous_node;
            return *this;
        }

        iterator operator--(int) {
            iterator previous = *this;
            --(*this);
            return previous;
        }

        bool operator==(const iterator& other) const noexcept {
            return current_node == other.current_node;
        }

        bool operator!=(const iterator& other) const noexcept {
            return current_node != other.current_node;
        }
    };

    using const_iterator = iterator;

    iterator begin() noexcept {
        return iterator(start_node, start_node);
    }

    iterator end() noexcept {
        return iterator(nullptr, start_node);
    }

    const_iterator begin() const noexcept {
        return const_iterator(start_node, start_node);
    }

    const_iterator end() const noexcept {
        return const_iterator(nullptr, start_node);
    }

    bool is_empty() const noexcept {
        return element_count == 0;
    }
    
    bool empty() const noexcept {
        return element_count == 0;
    }

    size_t size() const noexcept {
        return element_count;
    }

    T& front() {
        verify_non_empty();
        return start_node->element_value;
    }

    const T& front() const {
        verify_non_empty();
        return start_node->element_value;
    }

    T& back() {
        verify_non_empty();
        return start_node->previous_node->element_value;
    }

    const T& back() const {
        verify_non_empty();
        return start_node->previous_node->element_value;
    }

    void append(const T& val) {
        ListNode* new_element = new ListNode(val);
        if (!start_node) {
            start_node = new_element;
        } else {
            ListNode* last_element = start_node->previous_node;
            last_element->next_node = new_element;
            new_element->previous_node = last_element;
            new_element->next_node = start_node;
            start_node->previous_node = new_element;
        }
        ++element_count;
    }
    
    void push_back(const T& val) {
        append(val);
    }

    void append(T&& val) {
        ListNode* new_element = new ListNode(std::move(val));
        if (!start_node) {
            start_node = new_element;
        } else {
            ListNode* last_element = start_node->previous_node;
            last_element->next_node = new_element;
            new_element->previous_node = last_element;
            new_element->next_node = start_node;
            start_node->previous_node = new_element;
        }
        ++element_count;
    }
    
    void push_back(T&& val) {
        append(std::move(val));
    }

    void prepend(const T& val) {
        append(val);
        start_node = start_node->previous_node;
    }
    
    void push_front(const T& val) {
        prepend(val);
    }

    void prepend(T&& val) {
        append(std::move(val));
        start_node = start_node->previous_node;
    }
    
    void push_front(T&& val) {
        prepend(std::move(val));
    }

    void remove_back() {
        verify_non_empty();
        ListNode* last_element = start_node->previous_node;
        if (last_element == start_node) {
            delete last_element;
            start_node = nullptr;
        } else {
            last_element->previous_node->next_node = start_node;
            start_node->previous_node = last_element->previous_node;
            delete last_element;
        }
        --element_count;
    }
    
    void pop_back() {
        remove_back();
    }

    void remove_front() {
        verify_non_empty();
        if (start_node->next_node == start_node) {
            delete start_node;
            start_node = nullptr;
        } else {
            ListNode* old_start = start_node;
            start_node->previous_node->next_node = start_node->next_node;
            start_node->next_node->previous_node = start_node->previous_node;
            start_node = start_node->next_node;
            delete old_start;
        }
        --element_count;
    }
    
    void pop_front() {
        remove_front();
    }

    iterator insert(iterator position, const T& val) {
        if (position.current_node == nullptr || start_node == nullptr) {
            append(val);
            return iterator(start_node->previous_node, start_node);
        }
        ListNode* current = position.current_node;
        ListNode* previous = current->previous_node;
        ListNode* new_element = new ListNode(val);
        new_element->next_node = current;
        new_element->previous_node = previous;
        previous->next_node = new_element;
        current->previous_node = new_element;
        if (current == start_node) start_node = new_element;
        ++element_count;
        return iterator(new_element, start_node);
    }

    iterator insert(iterator position, T&& val) {
        if (position.current_node == nullptr || start_node == nullptr) {
            append(std::move(val));
            return iterator(start_node->previous_node, start_node);
        }
        ListNode* current = position.current_node;
        ListNode* previous = current->previous_node;
        ListNode* new_element = new ListNode(std::move(val));
        new_element->next_node = current;
        new_element->previous_node = previous;
        previous->next_node = new_element;
        current->previous_node = new_element;
        if (current == start_node) start_node = new_element;
        ++element_count;
        return iterator(new_element, start_node);
    }

    iterator erase(iterator position) {
        if (is_empty())
            throw std::out_of_range("Erase on empty list");
        if (position.current_node == nullptr)
            throw std::out_of_range("Erase called with end iterator");

        ListNode* node_to_remove = position.current_node;
        iterator next_position(node_to_remove->next_node == start_node 
            ? nullptr : node_to_remove->next_node, start_node);
            
        if (node_to_remove->next_node == node_to_remove) {
            delete node_to_remove;
            start_node = nullptr;
        } else {
            node_to_remove->previous_node->next_node = node_to_remove->next_node;
            node_to_remove->next_node->previous_node = node_to_remove->previous_node;
            if (node_to_remove == start_node) start_node = node_to_remove->next_node;
            delete node_to_remove;
        }
        --element_count;
        return next_position;
    }

    void clear() noexcept {
        while (!is_empty()) {
            remove_front();
        }
    }

    void fill(size_t quantity, const T& val) {
        clear();
        for (size_t i = 0; i < quantity; ++i) {
            append(val);
        }
    }
    
    void assign(size_t quantity, const T& val) {
        fill(quantity, val);
    }

    void exchange(CyclicalList& other) noexcept {
        std::swap(start_node, other.start_node);
        std::swap(element_count, other.element_count);
    }
    
    void swap(CyclicalList& other) noexcept {
        exchange(other);
    }
    
    bool is_equal(const CyclicalList& other) const {
        if (element_count != other.element_count) return false;
        auto this_iter = begin();
        auto other_iter = other.begin();
        while (this_iter != end() && other_iter != other.end()) {
            if (*this_iter != *other_iter) return false;
            ++this_iter;
            ++other_iter;
        }
        return true;
    }
    
    bool operator==(const CyclicalList& other) const {
        return is_equal(other);
    }

    bool operator!=(const CyclicalList& other) const {
        return !is_equal(other);
    }
};

/**
 * @brief Swaps contents of two CyclicalList
 * @tparam T Type of elements in the list
 * @param first First list
 * @param second Second list
 */
template <typename T>
void swap(CyclicalList<T>& first, CyclicalList<T>& second) noexcept {
    first.exchange(second);
}

#endif
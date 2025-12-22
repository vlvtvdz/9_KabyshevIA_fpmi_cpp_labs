#include "forward_list.h"

ForwardList::ForwardList() : head_(nullptr), size_(0) {
}

ForwardList::ForwardList(const ForwardList& rhs) : head_(nullptr), size_(0) {
    Node* tail = nullptr;
    Node* current = rhs.head_;
    while (current != nullptr) {
        Node* node = new Node(current->value_);
        if (head_ == nullptr) {
            head_ = node;
        } else {
            tail->next_ = node;
        }
        tail = node;
        current = current->next_;
        ++size_;
    }
}

ForwardList::ForwardList(size_t count, int32_t value) : head_(nullptr), size_(0) {
    if (count == 0) {
        return;
    }
    Node* tail = nullptr;
    for (size_t i = 0; i < count; ++i) {
        Node* node = new Node(value);
        if (head_ == nullptr) {
            head_ = node;
        } else {
            tail->next_ = node;
        }
        tail = node;
        ++size_;
    }
}

ForwardList::ForwardList(std::initializer_list<int32_t> init) : head_(nullptr), size_(0) {
    Node* tail = nullptr;
    for (std::initializer_list<int32_t>::const_iterator it = init.begin(); it != init.end();
         ++it) {
        Node* node = new Node(*it);
        if (head_ == nullptr) {
            head_ = node;
        } else {
            tail->next_ = node;
        }
        tail = node;
        ++size_;
    }
}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this == &rhs) {
        return *this;
    }
    Clear();
    Node* tail = nullptr;
    Node* current = rhs.head_;
    while (current != nullptr) {
        Node* node = new Node(current->value_);
        if (head_ == nullptr) {
            head_ = node;
        } else {
            tail->next_ = node;
        }
        tail = node;
        current = current->next_;
        ++size_;
    }
    return *this;
}

ForwardList::~ForwardList() {
    Clear();
}

void ForwardList::PushFront(int32_t value) {
    Node* node = new Node(value);
    node->next_ = head_;
    head_ = node;
    ++size_;
}

void ForwardList::PopFront() {
    if (head_ == nullptr) {
        return;
    }
    Node* node = head_;
    head_ = head_->next_;
    delete node;
    --size_;
}

void ForwardList::Remove(int32_t value) {
    while (head_ != nullptr && head_->value_ == value) {
        Node* node_to_remove = head_;
        head_ = head_->next_;
        delete node_to_remove;
        --size_;
    }
    Node* previous = head_;
    Node* current = nullptr;
    if (previous != nullptr) {
        current = previous->next_;
    }
    while (current != nullptr) {
        if (current->value_ == value) {
            previous->next_ = current->next_;
            delete current;
            current = previous->next_;
            --size_;
        } else {
            previous = current;
            current = current->next_;
        }
    }
}

void ForwardList::Clear() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next_;
        delete current;
        current = next;
    }
    head_ = nullptr;
    size_ = 0;
}

bool ForwardList::FindByValue(int32_t value) {
    Node* current = head_;
    while (current != nullptr) {
        if (current->value_ == value) {
            return true;
        }
        current = current->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* current = head_;
    bool first = true;
    while (current != nullptr) {
        if (!first) {
            out << ' ';
        }
        out << current->value_;
        first = false;
        current = current->next_;
    }
}

int32_t ForwardList::Front() const {
    return head_->value_;
}

size_t ForwardList::Size() const {
    return size_;
}

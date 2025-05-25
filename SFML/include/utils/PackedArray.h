#pragma once
#include <vector>
#include <unordered_map>
#include <memory>

template<typename T>
class PackedArray {
    std::vector<std::shared_ptr<T>> dense;
    std::unordered_map<unsigned int, size_t> sparse;

public:
    void insert(unsigned int id, std::shared_ptr<T> entity) {
        sparse[id] = dense.size();
        dense.push_back(entity);
    }

    void remove(unsigned int id) {
        auto index = sparse[id];
        std::swap(dense[index], dense.back());
        sparse[dense[index]->getID()] = index;
        dense.pop_back();
        sparse.erase(id);
    }

    std::vector<std::shared_ptr<T>>& getDense() {
        return dense;
    }

    bool contains(unsigned int id) const {
        return sparse.find(id) != sparse.end();
    }
};
